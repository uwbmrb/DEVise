// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2001-2002
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// JavaScreen client socket.  This class is used in the JSPoP to encapsulate
// a DEViseCommSocket connected to a client.  The main reason for having
// this class is to have a separate thread to read from each client, so
// one client cannot block others.

// Note: the thread should be in either of two states almost all of the
// time:
// - Sleeping, if we have received a command that hasn't been cleared yet;
// - Blocking on receiving a command from the socket, if we don't have a
//   pending command.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.4.2.1  2002/06/26 17:29:32  wenger
// Improved various error messages and client debug log messages; very
// minor bug fixes; js_log script is now part of installation.
//
// Revision 1.4  2002/02/06 18:59:37  wenger
// Got the JavaScreen to work on RedHat 7.2 (by running with Java 1.2,
// but still compiling with Java 1.1); added debug code.
//
// Revision 1.3  2001/11/13 17:57:01  xuk
// Could send command in String[] format, no need to compose a long command string before sending.
//
// Revision 1.2  2001/11/07 22:31:28  wenger
// Merged changes thru bmrb_dist_br_1 to the trunk (this includes the
// js_no_reconnect_br_1 thru js_no_reconnect_br_2 changes that I
// accidentally merged onto the bmrb_dist_br branch previously).
// (These changes include JS heartbeat improvements and the fix to get
// CGI mode working again.)
//
// Revision 1.1.2.2  2001/11/07 17:22:35  wenger
// Switched the JavaScreen client ID from 64 bits to 32 bits so Perl can
// handle it; got CGI mode working again (bug 723).  (Changed JS version
// to 5.0 and protocol version to 9.0.)
//
// Revision 1.1.2.1  2001/10/28 18:13:18  wenger
// Made msgType and cmdId private in DEViseCommSocket; other minor cleanups.
//
// Revision 1.1  2001/10/24 17:46:07  wenger
// Fixed bug 720 (one client can block others in the JSPoP).  The fix is that
// the JSPoP now has a separate thread to read from each client.
//

// ========================================================================

//TEMP package edu.wisc.cs.devise.js.jsc;
package JavaScreen;

import java.io.*;
import java.net.*;

public class DEViseClientSocket implements Runnable
{
    //===================================================================
    // VARIABLES
    private static final int DEBUG = 0;

    private DEViseCommSocket _socket = null;
    
    private String _command = null;
    private int _id;
    private int _cgiFlag;

    private boolean _isFirstCmd = true;

    private String _hostname = null;

    private Thread _thread = null;
    private volatile boolean _shutdown = false;
    private static int _objectCount = 0;

    //===================================================================
    // PUBLIC METHODS

    // ------------------------------------------------------------------
    // Constructor.
    public DEViseClientSocket(Socket sock, int timeout) throws YException
    {
        _socket = new DEViseCommSocket(sock, timeout);

	_thread = new Thread(this);
	_thread.setName("DEViseClientSocket" + _objectCount++);
	_thread.start();
    }

    // ------------------------------------------------------------------
    protected void finalize()
    {
        closeSocket();
    }

    // ------------------------------------------------------------------
    public void setHostname(String name)
    {
        _hostname = name;
    }

    // ------------------------------------------------------------------
    public String getHostname()
    {
        return _hostname;
    }

    // ------------------------------------------------------------------
    // Returns true iff the socket is open.
    public synchronized boolean isOpen()
    {
        return ((_socket != null) && _socket.isOpen());
    }

    // ------------------------------------------------------------------
    // Returns true iff there is a pending command.
    public synchronized boolean hasCommand()
    {
        return _command != null;
    }

    // ------------------------------------------------------------------
    // Returns true iff the pending command is the first command received
    // on this socket.  Note: this is only needed because of the special
    // cases for setting up collaboration, and we should eventuall get
    // rid of it. RKW 2001-10-22.
    public synchronized boolean isFirstCommand()
    {
	if (DEBUG >= 2) {
	    System.out.println(
	      "DEViseClientSocket.isFirstCommand() returning " + _isFirstCmd);
	}

        return _isFirstCmd;
    }

    // ------------------------------------------------------------------
    // Get the pending command, if any.
    public synchronized String getCommand()
    {
        if (DEBUG >= 2) {
	    System.out.println(
	      "DEViseClientSocket.getCommand() returning command <" +
	      _command + ">");
	}

	return _command;
    }

    // ------------------------------------------------------------------
    // Get the client ID corresponding to the pending command, if any.
    // TEMP -- maybe this should throw an exception if there is no
    // pending command
    public synchronized int getCmdId()
    {
        return _id;
    }

    // ------------------------------------------------------------------
    // Get the CGI flag corresponding to the pending command, if any.
    // TEMP -- maybe this should throw an exception if there is no
    // pending command
    public synchronized int getCmdCgiFlag()
    {
        return _cgiFlag;
    }

    // ------------------------------------------------------------------
    // Clear the pending command, if any.
    public synchronized void clearCommand()
    {
	if (DEBUG >= 2) {
	    System.out.println("DEViseClientSocket.clearCommand()");
	}

	_command = null;
	_isFirstCmd = false;
	_thread.interrupt();
    }

    // ------------------------------------------------------------------
    // Send the given command to the client.
    public synchronized void sendCommand(String cmd) throws YException
    {
        sendCommand(cmd, DEViseGlobals.API_JAVA, DEViseGlobals.DEFAULTID);
    }

    // ------------------------------------------------------------------
    // Send the given command to the client.
    public synchronized void sendCommand(String cmd, short msgType, int id)
      throws YException
    {
	if (DEBUG >= 1) {
	    System.out.println("DEViseClientCommand.sendCommand(<" + cmd +
	      ">, " + msgType + ", " + id + ")");
	}

        _socket.sendCmd(cmd, msgType, id);

        if (DEBUG >= 2) {
            System.out.println("  Done sending command");
        }
    }

    // ------------------------------------------------------------------
    // TEMP: send the given command in String[] format to the client.
    /*
    public synchronized void sendCommand(String[] cmds) throws YException
    {
        sendCommand(cmds, DEViseGlobals.API_JAVA, DEViseGlobals.DEFAULTID);
    }

    // ------------------------------------------------------------------
    public synchronized void sendCommand(String[] cmds, short msgType, int id)
      throws YException
    {
	if (DEBUG >= 1) {
	    System.out.println("DEViseClientCommand.sendCommand(<" + cmds +
	      ">, " + msgType + ", " + id + ")");
	}

        _socket.sendCmd(cmds, msgType, id);
    }
    */

    // ------------------------------------------------------------------
    // Send the given data to the client.
    public synchronized void sendData(byte[] data) throws YException
    {
	if (DEBUG >= 1) {
	    System.out.println("DEViseClientCommand.sendData()");
	}

        _socket.sendData(data);
    }

    // ------------------------------------------------------------------
    // Shut down the reading thread and close the socket.
    public void closeSocket()
    {
        if (DEBUG >= 1) {
            System.out.println("DEViseClientSocket.closeSocket()");
        }

	_shutdown = true;
	_thread.interrupt();
    }

    // ------------------------------------------------------------------
    // Read commands from the client on the socket.
    public void run()
    {
        if (DEBUG >= 1) {
	    System.out.println("DEViseClientSocket.run()");
	}

	String partCmd = "";

	while (!_shutdown) {
	    try {
		if (_command == null) {
	            String tmpCmd = _socket.receiveCmd();

		    // If we get here, we now have a complete command.
		    partCmd += tmpCmd;
		    _command = partCmd;
		    partCmd = "";

		    _id = _socket.getCmdId();
		    _cgiFlag = _socket.getFlag();

		    if (DEBUG >= 2) {
		        System.out.println("Got command <" + _command +
		          "> in DEViseClientSocket.run()");
		    }
		} else {
		    // Sleep will be interrupted when current command is
		    // cleared.  (Had problems with wait/notify.)
		    Thread.sleep(1000000); // a long time
		}

	    } catch (YException ex) {
	        System.err.println("Error receiving client " + _id +
		  " command: " + ex.getMessage());
		break;
	    } catch(InterruptedIOException ex) {
		if (!partCmd.equals("")) {
		    System.err.println(
		      "Interruption receiving client " + _id + " command: " +
		      ex.getMessage());
		}
	    } catch (InterruptedException ex) {
		// Getting interrupted from sleep() is normal.
	    }
	}

	_socket.closeSocket();

        if (DEBUG >= 1) {
	    System.out.println("  Done with DEViseClientSocket.run()");
	}
    }
}

// ========================================================================
