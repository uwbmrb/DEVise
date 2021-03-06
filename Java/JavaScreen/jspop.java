// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2015
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class contains the main() method for the jspop.  The main this
// class does, besides various startup stuff, is to listen for new
// connections from JavaScreens.  It also maintains lists of all of
// the clients (JavaScreens) and servers (DEViseServers/deviseds).


// There is one instance of this class for a given jspop process.

// ------------------------------------------------------------------------

// ========================================================================

// jspop.java

package JavaScreen;

import  java.io.*;
import  java.net.*;
import  java.util.*;

public class jspop implements Runnable
{
    private static final String usage = new String(
        "Usage: java JavaScreen.jspop [options]\n" +
        "  -id<string>: ID for ps (default: none)\n" +
        "  -cmdport<number>: port for command socket from devised (default: " +
        DEViseGlobals.DEFAULTCMDPORT + ")\n" +
        "  -userfile<filename>: file containing user info (default: users.cfg)\n" +
        "  -logfile<filename>: client log info file (default: clients.log)\n" +
        "  -clientlog[on|off]: turn on|off client command logs (default: on)\n" +
        "  -jspopport<number>: port on which jspop listens for jss connections\n    (default: " + DEViseGlobals.JSPOPPORT + ")\n" +
        "  -maxclient<number>: maximum number of client objects (default: " +
        DEViseGlobals.DEFAULTMAXCLIENT + ")\n" +
        "  -killint<number>: client kill interval in hours (<= 0 to disable)\n" +
        "    (default: 24.0)\n" +
        "  -usage: print this message");
    // -CMDPORT[port]:
    //      port: The command port, if blank, use the defaults
    //      default: 6666
    // -IMGPORT[port]:
    //      port: The image port, if blank, use the defaults
    //      default: 6688
    // -LOGFILE[filename]:
    //      filename: The name of the file that contain client log information
    //      default: clients.log
    // -USERFILE[filename]:
    //      filename: The name of the file that contain users information
    //      default: users.cfg
    // -DEBUG[number]:
    //      number: The debug level for writing debug information to console
    //      default: No Debug information is written
    //

    private static final int SOCK_REC_TIMEOUT = 100 * 1000; // milliseconds

    private ServerSocket cmdServerSocket = null;
    //private ServerSocket dataServerSocket = null;

    private String userFileName = new String("users.cfg");
    private String logFileName = new String("clients.log");
    private int logLevel = 0;
    private YLogFile logFile = null;
    private static int _debugLvl = 1;
    private YLogConsole debugConsole = null;

    private Thread popThread = null;

    private JssHandler jssHandler = null;
    private int jspopPort = DEViseGlobals.JSPOPPORT;
    private DEViseClientDispatcher dispatcher = null;

    private Hashtable users = new Hashtable();
    private Vector servers = new Vector();

    private int _lastClientId = 0;

    // Clients that are not connected to a devised.
    private Vector suspendClients = new Vector();

    // Clients that are connected to a devised.
    private Vector activeClients = new Vector();

    // Sockets that are connected to a JS.
    private Vector activeSockets = new Vector();

    // Maximum number of client objects allowed.
    private int maxClient = DEViseGlobals.DEFAULTMAXCLIENT;

    // Number of milliseconds we can go without getting a client heartbeat
    // before we kill that client.
    private int _killInterval = DEViseGlobals.KILLINTERVAL;

    private int _popCmdPort = 0;

    private String _popId = null;
    private CircularLog _usageLog = null;

    private DEViseThreadChecker _threadChecker = null;
    private DEViseJspopDebug _debugThread = null;

    // enable client log or not
    public boolean clientLog = true;

    // saving temporary session files in one directory
    public String sessionDir = null;

    // all collaboration names
    public Vector collabNames = new Vector();

    //----------------------------------------------------------------------

    public static void main(String[] args) throws YException
    {
        String version = System.getProperty("java.version");
        if (version.compareTo("1.1") < 0)  {
            System.err.println("Error: Java version 1.1 or greater is needed to run this program\n"
                               + "The version you used is " + version + "\n");
            System.exit(0);
        }

        // Print JSPoP version information and arguments.
        System.out.println("JSPoP version " + DEViseGlobals.VERSION);
        System.out.println("Protocol version " +
                           DEViseGlobals.PROTOCOL_VERSION);
        System.out.println("Arguments:");
        for (int index = 0; index < args.length; index++) {
            System.out.println("  <" + args[index] + ">");
        }

        jspop popServer = new jspop(args);
        popServer.start();
    }

    // ------------------------------------------------------------------
    // Set the debug level for this class.
    public static void setDebugLvl(int level)
    {
        _debugLvl = level;
    }

    //----------------------------------------------------------------------

    public void pn(String msg, int level)
    {
        debugConsole.pn(msg, level);
    }

    public void pn(String msg)
    {
        pn(msg, 1);
    }

    public void p(String msg, int level)
    {
        debugConsole.p(msg, level);
    }

    public void p(String msg)
    {
        p(msg, 1);
    }

    public void logpn(String msg, int level)
    {
        if (logLevel > 0) {
            logFile.pn(msg, level, true);
        }
    }

    public void logpn(String msg)
    {
        logpn(msg, 1);
    }

    public void logp(String msg, int level)
    {
        if (logLevel > 0) {
            logFile.p(msg, level, true);
        }
    }

    public void logp(String msg)
    {
        logp(msg, 1);
    }

    public void logUsage(String msg)
    {
        if (_usageLog != null) {
            _usageLog.logMsg(msg);
        }
    }

    //----------------------------------------------------------------------

    public int getCmdPort()
    {
        return _popCmdPort;
    }

    public String getPopId()
    {
        return _popId;
    }

    //----------------------------------------------------------------------

    public jspop(String[] args) throws YException
    {
        System.out.println("\nChecking command line arguments ...\n");
        checkArguments(args);
        System.out.println("\nmaxclient value is " + maxClient);

        String usageLogFile = "logs/jspop.usage." + _popId;
        try {
            // Note: we should probably eventually have command-line arguments
            // to specify the sizes here.  Size 0 means don't rotate
            // this log.
            _usageLog = new CircularLog(usageLogFile, 0, 1000);
            _usageLog.setAppendTime(true);
        } catch (IOException ex) {
            System.err.println("Unable open file: " + usageLogFile +
                               "; " + ex);
            throw new YException("Unable to create usage log");
        }

        pn("\nStarting command server socket on " + _popCmdPort + " ...\n");
        try {
            cmdServerSocket = new ServerSocket(_popCmdPort);
        } catch (IOException e) {
            System.err.println("Can not start command server socket at port " + _popCmdPort);
            System.err.println(e.getMessage());
            quit(1);
        }

        pn("\nStarting JSS handler ...\n");
        try {
            jssHandler = new JssHandler(this, jspopPort);
            jssHandler.start();
        } catch (YException e) {
            System.err.println("Can not start jss handler");
            System.err.println(e.getMessage());
            quit(1);
        }

        _threadChecker = new DEViseThreadChecker();
        _debugThread = new DEViseJspopDebug();

        pn("Starting client dispatcher ...\n");
        dispatcher = new DEViseClientDispatcher(this);
        dispatcher.start();
    }

    //----------------------------------------------------------------------

    public void start()
    {
        popThread = new Thread(this);
        popThread.setName("jspop");
        popThread.start();
    }

    // quit() will only be called in jspop server thread or in jspop()
    // initialization and all the stop() or close() methods of other
    // class are synchronized, so there is no need to synchronize quit()
    private synchronized void quit(int exitVal)
    {
        if (_debugLvl >= 2) {
            pn("jspop.quit()");
        }

        //
        // Stop the various threads.
        //

        pn("Stop jspop server thread...");
        if (popThread != null && Thread.currentThread() != popThread) {
            popThread.stop();
            popThread = null;
        }

        pn("Stop client dispatcher thread...");
        if (dispatcher != null) {
            dispatcher.stop();
            dispatcher = null;
        }

        pn("Stop jss handler thread ...");
        if (jssHandler != null) {
            jssHandler.stop();
            jssHandler = null;
        }

        //
        // Close sockets.
        //

        pn("Stop command server socket...");
        if (cmdServerSocket != null) {
            try {
                cmdServerSocket.close();
            } catch (IOException e) {
            }

            cmdServerSocket = null;
        }

        //TEMP -- why is this commented out?
        /*
        System.out.println("Stop DEViseServer thread...");
        for (int i = 0; i < servers.size(); i++) {
            DEViseServer server = (DEViseServer)servers.elementAt(i);
            if (server != null) {
                server.stop();
            }
        }
        servers.removeAllElements();
        */

        //
        // Close all clients.
        //

        pn("Close clients...");
        for (int i = 0; i < suspendClients.size(); i++) {
            DEViseClient client = (DEViseClient)suspendClients.elementAt(i);
            if (client != null) {
                client.close();
            }
        }
        suspendClients.removeAllElements();

        for (int i = 0; i < activeClients.size(); i++) {
            DEViseClient client = (DEViseClient)activeClients.elementAt(i);
            if (client != null) {
                client.close();
            }
        }
        activeClients.removeAllElements();

        //
        // Close the log file.
        //
        pn("Close log file...");
        if (logFile != null) {
            logFile.close();
            logFile = null;
        }

        System.exit(exitVal);
    }

    //----------------------------------------------------------------------

    // This basically listens for new connections from JavaScreens.
    // When a new connection is made, it creates a new DEViseClient object
    // corresponding to the JavaScreen that just connected.
    public void run()
    {
        pn("\nJSPOP Server started ...\n");

        int quitID = 0;

        Socket socket1 = null;

        while (true) {
            if (_debugLvl >= 1) pn("Starting jspop.run loop");
            try {
                // Note: probably *everything* here after the accept() call
                // should be in a separate thread for each connection.
                // wenger 2003-10-28.
                socket1 = cmdServerSocket.accept();
                if (_debugLvl >= 1) pn("Socket connection; client " +
                                           "host not yet known");
            } catch (IOException e) {
                pn("JSPOP server can not listen on command socket so " +
                   "it is aborting!");
                quitID = 1;
                break;
            }

            if (_debugLvl >= 1) pn("  Before handleConnection()");
            handleConnection(socket1);

            // client count?
            if (getClientCount() >= maxClient) {
                if (_debugLvl >= 1) pn("  Before killOldestClient()");
                killOldestClient();
            }

            //
            // Kill off any clients that we haven't gotten heartbeats from
            // for a while.
            //
            if (_debugLvl >= 1) pn("  Before checkHeartbeats()");
            checkHeartbeats();
            if (_debugLvl >= 1) pn("  After checkHeartbeats()");

        } // while

        quit(quitID);
    }

    // Send a stateless command (one that has nothing to do with client
    // state) to a randomly-selected server.
    public void sendStatelessCmd(String cmd) throws YException
    {
        if (_debugLvl >= 2) {
            pn("jspop.sendStatelessCmd(" + cmd + ")");
        }

        // Randomly pick a server.
        int serverCount = servers.size();
        int serverNum = (int)((new Random()).nextFloat() * serverCount);
        serverNum %= serverCount; // make *sure* it's legal

        // Send the command.
        DEViseServer server = (DEViseServer)servers.elementAt(serverNum);
        server.sendStatelessCmd(cmd);
    }

    private synchronized void handleConnection(Socket socket1)
    {
        if (_debugLvl >= 2) {
            pn("jspop.handleConnection() in thread " +
               Thread.currentThread());
        }

        try {
            //
            // If we get to here, we've connected on both the
            // command socket and data socket, so create a new
            // DEViseClient corresponding to the connection.
            //
            DEViseClientSocket clientSock = new DEViseClientSocket(socket1,
                    SOCK_REC_TIMEOUT, this);

            activeSockets.addElement(clientSock);
            if (_debugLvl >= 1) {
                pn(activeSockets.size() + " active client sockets in JSPoP");
            }
        } catch (YException e) {
            pn("\nEstablishing client connection failed: " + e.getMsg());
        }

        if (_debugLvl >= 2) {
            pn("DIAG done with jspop.handleConnection() " +
               "in thread " + Thread.currentThread());
        }
    }

    // Check the heartbeat times of all clients; if we haven't gotten a
    // heartbeat for _killInterval milliseconds, kill that client object (on
    // the assumption that the actual applet has died, or we've lost
    // communication with it).
    private synchronized void checkHeartbeats()
    {
        if (_debugLvl >= 2) {
            pn("jspop.checkHeartbeats()");
        }

        long presentTime = (new Date()).getTime();

        boolean killedAClient = false;

        //
        // Create a list of all clients so we can check both active and
        // suspended clients without having duplicate code.
        //
        Vector allClients = new Vector(activeClients.size() +
                                       suspendClients.size());

        for (int index = 0; index < activeClients.size(); index++) {
            allClients.addElement(activeClients.elementAt(index));
        }

        if (_debugLvl >= 4) {
            pn("DIAG before adding to suspended clients list");
        }
        for (int index = 0; index < suspendClients.size(); index++) {
            allClients.addElement(suspendClients.elementAt(index));
        }
        if (_debugLvl >= 4) {
            pn("DIAG after adding to suspended clients list");
        }

        //
        // Okay, now go through the list and kill off any clients that
        // haven't sent a heartbeat for a long time
        // (_killInterval milliseconds).
        //
        for (int index = 0; index < allClients.size(); index++) {
            DEViseClient client =
                (DEViseClient)allClients.elementAt(index);
            long sinceHeartbeat = presentTime-client.getHeartbeat();
            if (_killInterval > 0 && sinceHeartbeat > _killInterval) {
                pn("Killing client " + client.getConnectionID() +
                   " because heartbeat interval is too long");
                killedAClient = true;
                killClient(client);
            }
        }

        //
        // Note: killed clients will actually be removed from the client
        // list in getNextRequestingClient().  We don't *really* need
        // to call this here, because it will be called later, but it's
        // kind of weird to kill off a client and then still have it in
        // the clients list.  RKW 2002-04-11.
        //
        if (killedAClient) {
            getNextRequestingClient();
        }
    }

    //----------------------------------------------------------------------
    // Close the client that has been inactive for the longest period of
    // time.
    private synchronized void killOldestClient()
    {
        if (_debugLvl >= 1) {
            pn("jspop.killOldestClient()");
        }

        //
        // Note: we are checking both the active and suspended clients lists
        // here in case of the special case where maxclients is equal to
        // the number of servers.  If that's the case, and a new client
        // connects, the new client is the only client in the suspended
        // list, so if we only check that list, the new client will be
        // closed immediately.  RKW 2000-11-08.
        //
        DEViseClient oldestClient = null;
        long oldestHeartbeat = Long.MAX_VALUE;

        for (int i = 0; i < activeClients.size(); i++) {
            DEViseClient tmpClient =
                (DEViseClient) activeClients.elementAt(i);
            if (tmpClient != null) {
                if (tmpClient.getHeartbeat() < oldestHeartbeat) {
                    oldestClient = tmpClient;
                    oldestHeartbeat = oldestClient.getHeartbeat();
                }
            }
        }

        if (_debugLvl >= 4) pn("DIAG jspop 4210");
        for (int i = 0; i < suspendClients.size(); i++) {
            DEViseClient tmpClient =
                (DEViseClient) suspendClients.elementAt(i);
            if (tmpClient != null) {
                if (tmpClient.getHeartbeat() < oldestHeartbeat) {
                    oldestClient = tmpClient;
                    oldestHeartbeat = oldestClient.getHeartbeat();
                }
            }
        }
        if (_debugLvl >= 4) pn("DIAG jspop 4290");

        if (oldestClient != null) {
            pn("Killing client " +
               oldestClient.getConnectionID() +
               " because maxclients limit has been reached");
            killClient(oldestClient);

            //
            // Note: killed clients will actually be removed from the client
            // list in getNextRequestingClient().  We don't *really* need
            // to call this here, because it will be called later, but it's
            // kind of weird to kill off a client and then still have it in
            // the clients list.  RKW 2002-04-11.
            //
            getNextRequestingClient();
        }
    }

    //----------------------------------------------------------------------

    // Get the DEViseUser object corresponding to the given key and password.
    public DEViseUser getUser(String username, String password)
    {
        if (username == null || password == null) {
            return null;
        }

        if (users.containsKey(username)) {
            DEViseUser user = (DEViseUser)users.get(username);
            if (user != null) {
                if (password.equals(user.getPassword())) {
                    return user;
                }
            }

            return null;
        }

        return null;
    }

    private synchronized void addClient(DEViseClient client)
    {
        if (client != null) {
            pn("Client from " + client.getHostname() + " is added ...");
            client.setSuspend();
            if (_debugLvl >= 4) {
                pn("DIAG before adding to suspendClients");
            }
            suspendClients.addElement(client);
            if (_debugLvl >= 4) {
                pn("DIAG after adding to suspendClients");
            }
        }
    }

    public synchronized int getClientCount()
    {
        return suspendClients.size() + activeClients.size();
    }

    private synchronized DEViseClient findClientById(long id)
    {
        if (_debugLvl >= 2) {
            pn("findClientById(" + id + ") in thread " +
               Thread.currentThread());
        }

        for (int i = 0; i < activeClients.size(); i++) {
            DEViseClient tmpClient =
                (DEViseClient) activeClients.elementAt(i);
            if (tmpClient != null) {
                if (tmpClient.getConnectionID() == id) {
                    return tmpClient;
                }
            }
        }

        if (_debugLvl >= 4) {
            pn("Before checking suspended clients list");
        }
        for (int i = 0; i < suspendClients.size(); i++) {
            DEViseClient tmpClient =
                (DEViseClient) suspendClients.elementAt(i);
            if (tmpClient != null) {
                if (tmpClient.getConnectionID() == id) {
                    return tmpClient;
                }
            }
        }
        if (_debugLvl >= 4) {
            pn("After checking suspended clients list");
        }

        return null;
    }

    private synchronized DEViseClient findClientByCollabName(String name)
    {
        if (_debugLvl >= 2) {
            pn("findClientByCollabName(" + name + ") in thread " +
               Thread.currentThread());
        }

        for (int i = 0; i < activeClients.size(); i++) {
            DEViseClient tmpClient =
                (DEViseClient) activeClients.elementAt(i);
            if (tmpClient != null) {
                String collabName = tmpClient.getCollabName();
                pn("get collabname = " + collabName);
                if (collabName != null)
                    if (collabName.equals(name)) {
                        return tmpClient;
                    }
            }
        }

        if (_debugLvl >= 4) {
            pn("Before checking suspended clients list");
        }
        for (int i = 0; i < suspendClients.size(); i++) {
            DEViseClient tmpClient =
                (DEViseClient) suspendClients.elementAt(i);
            if (tmpClient != null) {
                String collabName = tmpClient.getCollabName();
                pn("get collabname = " + collabName);
                if (collabName != null)
                    if (collabName.equals(name)) {
                        return tmpClient;
                    }
            }
        }
        if (_debugLvl >= 4) {
            pn("After checking suspended clients list");
        }

        return null;
    }

    //----------------------------------------------------------------------

    // Get the client, if any, that has been waiting longest for a command
    // to be serviced (length of time multiplied by client priority).
    // This also removes any closed clients.
    //
    // this method will only be called in client dispatcher thread
    // this method will also check which client need to be removed and remove it

    // TEMP -- we should probably re-think this method because of the
    // new DEViseClientSocket class.  RKW 2001-10-24.
    public synchronized DEViseClient getNextRequestingClient()
    {
        if (_debugLvl >= 2) {
            pn("jspop.getNextRequestingClient() in thread " +
               Thread.currentThread());
        }

        //
        // Check all sockets for input; if there is input, read the command
        // and add it to the appropriate client.  (This changes the client's
        // state to REQUEST unless it's already connected to a server.)
        //
        try {
            if (_debugLvl >= 4) {
                pn("DIAG before checking sockets");
            }
            for (int i = 0; i < activeSockets.size(); i++) {
                if (_debugLvl >= 4) pn("DIAG jspop 1010");
                DEViseClientSocket clientSock =
                    (DEViseClientSocket)activeSockets.elementAt(i);
                if (_debugLvl >= 4) pn("DIAG jspop 1020");

                // Note: socket will never be null here; socket.is is null
                // if the socket has been closed. RKW 2001-10-22.
                if (clientSock.isOpen()) {
                    if (_debugLvl >= 4) pn("DIAG jspop 1030");
                    if (clientSock.hasCommand()) {
                        if (_debugLvl >= 4) pn("DIAG jspop 1040");
                        String cmd = clientSock.getCommand();

                        int id = clientSock.getCmdId();
                        int cgi = clientSock.getCmdCgiFlag();
                        clientSock.clearCommand();

                        processCommand(clientSock, cmd, id, cgi);
                    }
                    if (_debugLvl >= 4) pn("DIAG jspop 1045");
                } else { // !socket.isOpen
                    if (_debugLvl >= 2) {
                        pn("Removing client socket " +
                           clientSock.getObjectNum() +
                           " from active sockets list");
                    }
                    activeSockets.removeElement(clientSock);
                }
            } // for
            if (_debugLvl >= 4) {
                pn("DIAG after checking sockets");
            }
        } catch (YException e) {
            pn("Exception checking sockets " + e);
        }

        //
        // Find the suspended client that's been waiting the longest time
        // (weighted by client priority).
        //
        float time = -1.0F, clientTime = 0.0F;
        DEViseClient client = null;
        Vector removedClient = new Vector();

        if (_debugLvl >= 4) pn("DIAG jspop 1110");
        for (int i = 0; i < suspendClients.size(); i++) {
            if (_debugLvl >= 4) pn("DIAG jspop 1120");
            DEViseClient newclient = (DEViseClient)suspendClients.elementAt(i);
            if (_debugLvl >= 4) pn("DIAG jspop 1121");
            if (newclient != null) {
                if (_debugLvl >= 4) pn("DIAG jspop 1130");
                int status = newclient.getStatus();
                if (_debugLvl >= 4) pn("DIAG jspop 1131");
                if (status == DEViseClient.CLOSE) {
                    // this client need to be removed
                    if (_debugLvl >= 4) pn("DIAG jspop 1140");
                    removedClient.addElement(newclient);
                    if (_debugLvl >= 4) pn("DIAG jspop 1141");
                    continue;
                } else if (status == DEViseClient.REQUEST) {
                    //} else if (status == DEViseClient.REQUEST ||
                    //   ! newclient.cmdBuffer.isEmpty()) {
                    // only clients that are requesting service will be served
                    if (_debugLvl >= 4) pn("DIAG jspop 1150");
                    clientTime = (float)(newclient.getPriority() *
                                         newclient.getSuspendTime());
                    if (_debugLvl >= 4) pn("DIAG jspop 1151");

                    // Keep track of the client that's been waiting the
                    // longest (accounting for priority).
                    if (time < 0.0) {
                        time = clientTime;
                        client = newclient;
                    } else {
                        if (time < clientTime) {
                            time = clientTime;
                            client = newclient;
                        }
                    }
                    if (_debugLvl >= 4) pn("DIAG jspop 1160");
                }
            }
        }
        if (_debugLvl >= 4) pn("DIAG jspop 1190");

        //
        // Remove any closed clients.
        //
        if (removedClient.size() > 0) {
            for (int i = 0; i < removedClient.size(); i++) {
                DEViseClient newclient =
                    (DEViseClient)removedClient.elementAt(i);
                if (newclient != null) {
                    if (_debugLvl >= 1) {
                        pn("Removing client " + newclient.getConnectionID());
                    }
                    suspendClients.removeElement(newclient);
                    if (_debugLvl >= 4) pn("DIAG jspop 1250");
                }
            }
            removedClient.removeAllElements();

            // Objects don't seem to get reliably garbage collected without
            // this.  RKW 2000-11-07.
            System.gc();

            if (_debugLvl >= 1) {
                pn("jspop state in getNextRequestingClient: " +
                   getServerState(true));
            }
        }

        if (_debugLvl >= 4) {
            pn("DIAG at end of getNextRequestingClient(); " +
               "client is " + ((client != null) ?
                               (new Long(client.getConnectionID()).toString()) : "null"));
        }

        return client;
    }

    public synchronized void activateClient(DEViseClient c)
    {
        if (_debugLvl >= 2) {
            pn("jspop.activateClient(" +
               c.getConnectionID() + ")");
        }

        if (c != null) {
            if (_debugLvl >= 4) pn("DIAG jspop 2110");
            if (!suspendClients.removeElement(c)) {
                System.err.println("Warning: client " +
                                   c.getConnectionID() +
                                   " is not in suspended clients list");
            }
            if (_debugLvl >= 4) pn("DIAG jspop 2120");

            if (activeClients.contains(c)) {
                System.err.println("Warning: client " +
                                   c.getConnectionID() +
                                   " is already in active clients list");
            } else {
                activeClients.addElement(c);
            }
            c.setActive();
        }
    }

    public synchronized void suspendClient(DEViseClient c)
    {
        if (_debugLvl >= 2) {
            pn("jspop.suspendClient(" +
               c.getConnectionID() + ")");
        }

        if (c != null) {
            if (!activeClients.removeElement(c)) {
                System.err.println("Warning: client " +
                                   c.getConnectionID() +
                                   " is not in active clients list");
            }

            if (_debugLvl >= 4) pn("DIAG jspop 3110");
            if (suspendClients.contains(c)) {
                System.err.println("Warning: client " +
                                   c.getConnectionID() +
                                   " is already in suspended clients list");
            } else {
                suspendClients.addElement(c);
            }
            if (_debugLvl >= 4) pn("DIAG jspop 3120");
            c.setSuspend();
        }
    }

    //----------------------------------------------------------------------

    public synchronized void addServer(String name, int port, int cmdport,
                                       int imgport)
    {
        DEViseServer newserver = new DEViseServer(this, name, port,
                cmdport, imgport);
        servers.addElement(newserver);

        try {
            newserver.start();
        } catch (YException e) {
            pn("Removing server because startup failed");
            removeServer(newserver);
            pn(e.getMsg());
        }
    }

    public synchronized void removeServer(DEViseServer server)
    {
        if (server == null) {
            return;
        }

        servers.removeElement(server);

        try {
            Socket socket = new Socket(server.hostname, server.jssport);
            DataOutputStream os = new DataOutputStream(
                new BufferedOutputStream(socket.getOutputStream()));
            String msg = DEViseCommands.S_RESTART + " " + server.cmdPort;
            pn("Trying to send restart request to " +
               server.hostname + " ...");
            os.writeInt(msg.length());
            os.writeBytes(msg);
            os.flush();
            os.close();
            socket.close();
            System.out.println("Message \"" + msg +
                               "\" successfully sent to JSS server at " + server.hostname);
        } catch (UnknownHostException e) {
            pn("Can not find jss host " + server.hostname);
        } catch (NoRouteToHostException e) {
            pn("Can not find route to jss host " + server.hostname +
               ", may caused by an internal firewall");
        } catch (IOException e) {
            pn("IO Error while connecting to jss host " + server.hostname);
        }
    }

    // Get the server that has been inactive for the longest time (accounting
    // for client priority).
    public synchronized DEViseServer getNextAvailableServer()
    {
        if (_debugLvl >= 2) {
            pn("jspop.getNextAvailableServer() in thread " +
               Thread.currentThread());
        }

        DEViseServer server = null;
        DEViseClient client = null;
        float time = -1.0F, clientTime = 0.0F;

        for (int i = 0; i < servers.size(); i++) {
            DEViseServer newserver = (DEViseServer)servers.elementAt(i);
            if (newserver != null) {
                if (newserver.getStatus() == DEViseServer.STATUS_STOPPED) {
                    try {
                        newserver.start();
                    } catch (YException e) {
                        pn("Removing server because restart failed");
                        removeServer(newserver);
                        pn(e.getMsg());
                        continue;
                    }
                } else {
                    if (!newserver.isAvailable()) {
                        continue;
                    }

                    client = (DEViseClient)newserver.getCurrentClient();
                    if (client == null) { // this server is idle
                        server =  newserver;
                        break;
                    }

                    // Keep track of the server that's been inactive the
                    // longest (accounting for client priority).
                    clientTime = (float)client.getActiveTime() /
                                 (float)client.getPriority();
                    if (time < 0.0) {
                        time = clientTime;
                        server = newserver;
                    } else {
                        if (time < clientTime) {
                            time = clientTime;
                            server = newserver;
                        }
                    }
                }
            }
        }

        if (_debugLvl >= 4) {
            String name = ((server != null) ? server.hostname : "null");
            pn("DIAG server is " + name);
        }

        return server;
    }

    //----------------------------------------------------------------------
    public String getServerState()
    {
        return getServerState(false);
    }

    // State string contains the following info (if not verbose):
    //   - number of servers
    //   - hostname and client ID of each server
    //   - total number of client objects
    //   - number of active clients
    //   - ID and hostname of each active client
    //   - number of suspended clients
    //   - ID and hostname of each suspended client, and whether the client's
    //     command buffer is empty
    public synchronized String getServerState(boolean verbose)
    {
        String state = "{";

        state += servers.size() + " ";
        if (verbose) state += " servers: ";
        for (int i = 0; i < servers.size(); i++) {
            state += "{";
            DEViseServer server = (DEViseServer)servers.elementAt(i);
            if (server == null) {
                state = state + "null ";
            } else {
                state = state + server.hostname + " ";
                DEViseClient client = server.getCurrentClient();
                if (client == null) {
                    state += "null";
                } else {
                    state += client.getConnectionID();
                }
            }
            state += "} ";
        }

        int totalClients = activeClients.size() + suspendClients.size();
        state += totalClients + " ";
        if (verbose) state += "total clients ";

        state = state + activeClients.size() + " ";
        if (verbose) state += "active clients: ";
        for (int i = 0; i < activeClients.size(); i++) {
            DEViseClient client = (DEViseClient)activeClients.elementAt(i);
            state += "{" + client.getConnectionID() + " ";
            if (client == null) {
                state = state + "null";
            } else {
                state = state + client.getHostname();
            }
            state += "} ";
        }

        if (_debugLvl >= 4) pn("DIAG jspop 4110");
        state = state + suspendClients.size() + " ";
        if (verbose) state += "suspended clients: ";
        for (int i = 0; i < suspendClients.size(); i++) {
            DEViseClient client = (DEViseClient)suspendClients.elementAt(i);
            state += "{" + client.getConnectionID() + " ";
            if (client == null) {
                state = state + "null";
            } else {
                state = state + client.getHostname();
                state = state + " " + client.getStatus() + " " + client.cmdBuffer.isEmpty();

            }
            state += "} ";
        }
        if (_debugLvl >= 4) pn("DIAG jspop 4190");

        if (verbose) {
            state += DEViseClient.getObjectCount() + " client objects ";
        }

        state = state + "}";
        return state;
    }

    //----------------------------------------------------------------------
    public int getServerCount()
    {
        return servers.size();
    }

    //----------------------------------------------------------------------
    private DEViseClient createClient(String clientHost,
                                      DEViseClientSocket clientSock, boolean cgi)
    {
        DEViseClient client = new DEViseClient(this, clientHost, clientSock,
                                               getID(), cgi);

        // Note: a new client gets added into the suspended clients list;
        // eventually it gets moved from there to the active clients list.
        addClient(client);

        pn("jspop state in createClient: " + getServerState(true));

        return client;
    }

    //----------------------------------------------------------------------

    // Get a unique ID for a client.
    private synchronized int getID()
    {
        // we use timestamp as client's id now.
        // xuk 10/10/01
        Date date = new Date();
        long time = date.getTime();

        // Make this fit into an int.
        time /= 100; // truncate to tenths of seconds
        time %= Integer.MAX_VALUE;

        int id = (int)time;

        //
        // Make sure there's no chance of duplicate IDs.
        //
        if (id <= _lastClientId) {
            id = _lastClientId + 1;
        }

        _lastClientId = id;

        if (_debugLvl >= 1) {
            pn("  New client ID: " + id);
        }

        return id;
    }

    //----------------------------------------------------------------------

    // Check command-line arguments and set variables accordingly.
    private void checkArguments(String[] args) throws YException
    {
        for (int i = 0; i < args.length; i++) {
            StringBuffer argValue = new StringBuffer();

            if (DEViseGlobals.checkArgument(args[i], "-cmdport", true,
                                            argValue)) {
                try {
                    int port = Integer.parseInt(argValue.toString());
                    if (port < 1024 || port > 65535) {
                        throw new NumberFormatException();
                    }
                    _popCmdPort = port;
                } catch (NumberFormatException e) {
                    throw new YException("Please use a positive integer " +
                                         "between 1024 and 65535 as the cmdport number");
                }

            } else if (DEViseGlobals.checkArgument(args[i], "-jspopport", true,
                                                   argValue)) {
                try {
                    jspopPort = Integer.parseInt(argValue.toString());
                    if (jspopPort < 1024 || jspopPort > 65535) {
                        throw new NumberFormatException();
                    }
                } catch (NumberFormatException e) {
                    throw new YException("Please use a positive integer " +
                                         "between 1024 and 65535 as the jspop port number");
                }

            } else if (DEViseGlobals.checkArgument(args[i], "-logfile", true,
                                                   argValue)) {
                // Note: nothing ever seems to get logged to this file.
                // RKW 2000-11-07.
                logFileName = argValue.toString();

            } else if (DEViseGlobals.checkArgument(args[i], "-userfile", true,
                                                   argValue)) {
                userFileName = argValue.toString();

            } else if (DEViseGlobals.checkArgument(args[i], "-id", true,
                                                   argValue)) {
                _popId = argValue.toString();

            } else if (DEViseGlobals.checkArgument(args[i], "-maxclient",
                                                   true, argValue)) {
                try {
                    maxClient = Integer.parseInt(argValue.toString());
                    if (maxClient < 1) {
                        System.err.println("Warning: illegal maxclient value ("
                                           + maxClient + "); using default");
                        maxClient = DEViseGlobals.DEFAULTMAXCLIENT;
                    }
                } catch (NumberFormatException e) {
                    throw new YException("Please specify a numerical value " +
                                         "for the -maxclient argument");
                }

            } else if (DEViseGlobals.checkArgument(args[i], "-clientlog",
                                                   true, argValue)) {
                // enable client log files?
                String s = argValue.toString();
                if (s.equals("on")) {
                    clientLog = true;
                } else if (s.equals("off")) {
                    clientLog = false;
                } else {
                    throw new YException("Please specify 'on' or 'off' for " +
                                         "the -clientlog argument");
                }

            } else if (DEViseGlobals.checkArgument(args[i], "-killint", true,
                                                   argValue)) {
                try {
                    float hours = Float.valueOf(argValue.toString()).
                                  floatValue();
                    if (hours < 0.0) {
                        // Infinite time.
                        _killInterval = 0;
                    } else {
                        // Hours to milliseconds conversion.
                        _killInterval = (int)(hours * 60 * 60 * 1000);
                    }
                } catch (NumberFormatException e) {
                    throw new YException("Please specify a numerical " +
                                         "value for the -killint argument");
                }

            } else if (DEViseGlobals.checkArgument(args[i], "-usage", false,
                                                   argValue)) {
                System.out.println(usage);
                System.exit(0);

            } else {
                throw new YException("Invalid jspop option \"" + args[i] +
                                     "\"is given\n" + usage);
            }
        }

        logLevel = 1;

        if (_popCmdPort < 1024) {
            _popCmdPort = DEViseGlobals.DEFAULTCMDPORT;
        }
        if (logLevel > 0) {
            logFile = new YLogFile(logFileName, logLevel, true);
        }

        debugConsole = new YLogConsole(100);

        System.out.println("Loading user configuration file ...");
        readCFGFile(userFileName);
    }

    // Read user configuration file.
    private void readCFGFile(String filename)
    {
        RandomAccessFile uf = null;
        try {
            uf = new RandomAccessFile(filename, "r");
        } catch (IOException e) {
            System.out.println("Invalid user configuration file \"" +
                               filename + "\"");
            System.exit(1);
        }

        try {
            String str = uf.readLine();
            while (str != null) {
                str = str.trim();
                // skip comment line
                if (!str.startsWith("#") && !str.equals("")) {
                    String[] line = DEViseGlobals.parseStr(str, ":");
                    DEViseUser user = new DEViseUser(line);
                    users.put(user.getName(), user);
                }

                str = uf.readLine();
            }
        } catch (IOException e) {
            try {
                uf.close();
            } catch (IOException e1) {
            }

            System.out.println("Can not read from user configuration file \""
                               + filename + "\"");
            System.exit(1);
        } catch (YException e) {
            try {
                uf.close();
            } catch (IOException e1) {
            }

            System.out.println(e.getMsg());
            System.exit(1);
        }

        try {
            uf.close();
        } catch (IOException e) {
        }
    }

    private void processCommand(DEViseClientSocket clientSock,
                                String cmd, long id, int flag) throws YException
    {
        if (_debugLvl >= 1) {
            pn("jspop.processCommand(" + cmd + ")");
        }

        boolean cgi;
        if (flag == 1) {
            cgi = true;
            pn("Receiving command CGI.");
        } else {
            cgi  = false;
            pn("Receiving command via socket.");
        }

        pn("Received command from client(" + id + ") :  \"" + cmd + "\"");
        if (id == DEViseGlobals.DEFAULTID) { // new JS
            pn("New client");
            DEViseClient client = createClient(clientSock.getHostname(),
                                               clientSock, cgi);
            client.addNewCmd(cmd);
        } else { // old JS
            pn("Existing client");
            // Vector methods -- if so, what's the other thread holding
            // the lock?  Hmm -- it pretty much looks like the client
            // dispatcher thread must get stuck here or in
            // DEViseClient.sendCmd() -- with a heartbeat there just
            // isn't much place for it to get stuck.
            DEViseClient client = findClientById(id);
            if (client != null) {
                // set cgi flag; added for mode changing
                client.setCgi(cgi);
                client.setSocket(clientSock);
                client.addNewCmd(cmd);

                if ((cmd.startsWith(DEViseCommands.SAVE_CUR_SESSION)) &&
                        (client.isAbleCollab)) {
                    // disable collaboration
                    // Why? -- RKW 2001-11-09.
                    client.isAbleCollab = false;
                    pn("Disable collaboration." + client.isAbleCollab);
                }
            } else {
                clientSock.sendCommand(DEViseCommands.ERROR +
                                       " {Client connection is invalid.  Please exit " +
                                       "the JavaScreen.}");
                clientSock.closeSocket();
                throw new YException("No client for ID: " + id);
            }
        }
    }

    // Get a list of possible collaboration leaders
    public synchronized String getCollabLeaders()
    {
        if (_debugLvl >= 4) pn("DIAG jspop 5110");
        String command = new String(DEViseCommands.CLIENTS);

        for (int i = 0; i < activeClients.size(); i++) {
            DEViseClient tmpClient =
                (DEViseClient) activeClients.elementAt(i);
            if (tmpClient != null && tmpClient.isAbleCollab) {
                command = command + " {" + tmpClient.getConnectionID() +
                          "} {  " + tmpClient.getCollabName() + "} {  " +
                          tmpClient.hostname + ":}" + " { " +
                          tmpClient.sessionName + "}";
            }
        }

        if (_debugLvl >= 4) pn("DIAG jspop 5120");
        for (int i = 0; i < suspendClients.size(); i++) {
            DEViseClient tmpClient =
                (DEViseClient) suspendClients.elementAt(i);
            if (tmpClient != null && tmpClient.isAbleCollab) {
                command = command + " {" + tmpClient.getConnectionID() +
                          "} {  " + tmpClient.getCollabName() + "} {  " +
                          tmpClient.hostname + ":}" +
                          " { " + tmpClient.sessionName + "}";
            }
        }
        if (_debugLvl >= 4) pn("DIAG jspop 5130");

        command = command.trim();

        return (command);
    }

    // Set up the client as a collaboration follower.
    public void setUpCollab(DEViseClient client, String cmd, String hostname)
    {
        if (_debugLvl >= 1) {
            pn("jspop.setUpCollab(" + client + ", " + cmd +
               ", " + hostname + ")");
        }

        DEViseClient leaderClient = null;
        long id = 0;

        String[] cmds = DEViseGlobals.parseString(cmd);
        int flag = new Integer(cmds[1]).intValue();

        if (flag == 2) { // use collab-name to identify leader
            String name = cmds[3];
            leaderClient = findClientByCollabName(name);
            if (leaderClient != null) {
                id = leaderClient.getConnectionID();
            }
            pn("We got collabortion name: " + name);
            pn("We got collabortion id: " + id);
        } else {         // use id to identify leader
            id = new Long(cmds[2]).longValue();
            pn("We got collaboration id: " + id);
            // find the proper client;
            leaderClient = findClientById(id);
        }

        try {
            if (leaderClient != null) {
                // check for enable collaboration status
                if (leaderClient.isAbleCollab) {

                    String collabPass = new String(cmds[4]);
                    pn("We got collaboration passwd: " + collabPass);

                    if (leaderClient.checkPass(collabPass)) {
                        // TEMP -- if you have > 1 server, might this cause
                        // an unnecessary client switch, if you happen to get
                        // the server that's connected to the other client??
                        // RKW 2001-10-23.
                        leaderClient.addCollabClient(client, hostname);
                        client.collabLeader = leaderClient;

                        //TEMP -- ideally, the JSPoP would initiate the
                        // saving of the pre-collaboration session in here
                        // somewhere; however, for now this is still done
                        // by the client. RKW 2001-11-13.

                        client.sendCmd(DEViseCommands.INIT_COLLAB + " " + id);

                        client.sendCmd(DEViseCommands.SET_DISPLAY_SIZE + " " +
                                       leaderClient.screenDimX + " " +
                                       leaderClient.screenDimY+ " " +
                                       leaderClient.screenResX+ " " +
                                       leaderClient.screenResY);
                        client.sendCmd(DEViseCommands.DONE);

                        // Make sure the leader client has a server so it
                        // can save and reload the current session to generate
                        // the commands and data to initialize the collaborator.
                        DEViseServer server = getNextAvailableServer();
                        if (server != null &&
                                (server.getCurrentClient()) != leaderClient) {
                            server.setCurrentClient(leaderClient);
                        }
                    } else { // wrong passwd
                        pn("Incorrect password.");
                        client.sendCmd(DEViseCommands.ERROR +
                                       " {Incorrect password. Please try again.}");
                    }
                } else { // disable collaboration
                    pn("Disabled to collaborate with client.");
                    client.sendCmd(DEViseCommands.ERROR +
                                   " {Client " + id + " does not allow collaboration.}");
                }
            } else {
                pn("No client is found.");
                client.sendCmd(DEViseCommands.ERROR + " {Incorrect client id or collaboration name. Please try again.}");
            }
        } catch (YException e) {
            pn(e.getMsg());
        }
    }

    // Cleanly kill the specified client, whether it's active or suspended.
    private synchronized void killClient(DEViseClient client)
    {
        if (_debugLvl >= 2) {
            pn("jspop.killClient(" +
               client.getConnectionID() + ")");
        }

        if (activeClients.contains(client)) {
            if (_debugLvl >= 4) {
                pn("  Killing active client");
            }

            DEViseServer server = findServerOfClient(client);
            if (server != null) {
                try {
                    server.cmdExit();
                } catch (YException e) {
                    System.err.println("Error closing client " +
                                       client.getConnectionID() + ": " + e.getMessage());
                }
            } else {
                System.err.println(
                    "Error: no server found for client in active clients list!");
            }
        } else {
            if (_debugLvl >= 4) {
                pn("  Killing suspended client");
            }

            client.close();
        }
    }

    // Find the server (if any) of the given client.
    DEViseServer findServerOfClient(DEViseClient client)
    {
        DEViseServer result = null;

        for (int index = 0; index < servers.size(); index++) {
            DEViseServer server = (DEViseServer)servers.elementAt(index);
            if (server.getCurrentClient() == client) {
                result = server;
                break;
            }
        }

        return result;
    }
}
