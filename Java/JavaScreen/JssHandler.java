
import java.io.*;
import java.net.*;
import java.util.*;

public class JssHandler implements Runnable
{
    private jspop pop = null;
    private int timestep = 500;

    private Thread handler = null;
    private int jspopPort = 0;
    private ServerSocket jssServerSocket = null;

    // status = 0, handler is not running
    // status = 1, handler is running
    private boolean status = false;

    public JssHandler(jspop j, int port) throws YException
    {
        jspopPort = port;
        if (port < 1024 || port > 65535)
            throw new YException("Invalid jspop port specified: " + port);

        pop = j;

        System.out.println("\nTry to start jss server socket at port " + jspopPort + " ...\n");
        try {
            jssServerSocket = new ServerSocket(jspopPort);
        } catch (IOException e) {
            jssServerSocket = null;
            throw new YException("Can not start jss server sokcet at port " + jspopPort);
        }

    }

    private synchronized void setStatus(boolean s)
    {
        status = s;
    }

    public synchronized boolean getStatus()
    {
        return status;
    }

    public void start()
    {
        if (!getStatus()) {
            if (jssServerSocket == null) {
                System.out.println("\nTry to restart jss server socket at port " + jspopPort + " ...\n");
                try {
                    jssServerSocket = new ServerSocket(jspopPort);
                    System.out.println("\nRestarting jss server socket succeed!\n");
                } catch (IOException e) {
                    System.out.println("\nRestarting jss server socket failed\n");
                    jssServerSocket = null;
                    return;
                }
            }

            status = true;
            handler = new Thread(this);
            handler.start();
        }
    }

    public void stop()
    {
        if (getStatus()) {
            if (handler != null) {
                handler.stop();
                handler = null;
            }

            if (jssServerSocket != null) {
                try {
                    jssServerSocket.close();
                } catch (IOException e) {
                }
                jssServerSocket = null;
            }

            pop.pn("Client handler thread is stopped");
            setStatus(false);
        }
    }

    public void run()
    {
        pop.pn("\nJss handler started ...\n");

        boolean isListen = true;
        String hostname = null;
        int cmdport, imgport, port;

        while (isListen) {
            Socket socket = null;
            DataInputStream is = null;
            try {
                socket = jssServerSocket.accept();
                hostname = socket.getInetAddress().getHostName();
                imgport = -1;
                cmdport = -1;
                port = -1;
                System.out.println("Connection request from " + hostname + " is accepted ...");

                try {
                    is = new DataInputStream(socket.getInputStream());
                    String msg = receiveFromJSS(is);

                    String[] cmd = DEViseGlobals.parseString(msg);
                    if (cmd == null) {
                        System.out.println("Invalid request received from jss \"" + msg + "\"");
                    } else {
                        if (cmd[0].startsWith("JSS_Add") && cmd.length == 4) {
                            try {
                                port = Integer.parseInt(cmd[1]);
                                cmdport = Integer.parseInt(cmd[2]);
                                imgport = Integer.parseInt(cmd[3]);
                            } catch (NumberFormatException e) {
                                port = -1;
                                cmdport = -1;
                                imgport = -1;
                                System.out.println("Invalid request received from jss \"" + msg + "\"");
                            }
                        } else {
                            System.out.println("Invalid request received from jss \"" + msg + "\"");
                        }
                    }

                    if (hostname != null && port > 1024 && port < 65535 && imgport > 1024 && imgport < 65535 && cmdport > 1024 && cmdport < 65535) {
                        pop.addServer(hostname, port, cmdport, imgport);
                    }
                } catch (IOException ex) {
                    pop.pn("IO Error while open connection to jss host " + hostname);
                } catch (YException ex) {
                    pop.pn(ex.getMessage());
                }

                if (is != null) {
                    try {
                        is.close();
                    } catch (IOException ex) {
                    }
                    is = null;
                }

                if (socket != null) {
                    try {
                        socket.close();
                    } catch (IOException ex) {
                    }
                    socket = null;
                }
            } catch (IOException e) {
                System.out.println("jss handler can not listen on jss socket so it is aborting!");
                break;
            }
        }
    }

    private String receiveFromJSS(DataInputStream is) throws YException
    {
        if (is == null) {
            throw new YException("Null jss input stream!", "JssHandler:receiveFromJSS()");
        }

        try {
            int length = is.readInt();
            byte[] data = new byte[length];
            is.readFully(data);
            return new String(data);
        } catch (IOException e) {
            throw new YException("IO Error while receive message from jss", "JssHandler:receiveFromJSS()");
        }
    }
}


