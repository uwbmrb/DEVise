// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2000
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// Command dispatcher.  This class sends commands from the JavaScreen
// to the jspop/devised, and processes the commands that are sent
// back.

// There is one instance of this class for the entire JavaScreen.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.66  2000/09/12 20:51:22  wenger
// Did some cleanup of the command-related code, better error messages from JSS.
//
// Revision 1.65  2000/07/20 22:38:26  venkatan
// Mouse Location Format display:
// 1. Both X and Y axis formats are recognised.
// 2. "-" is recognised for "" String.
// 3. %.0f is now recognised.
//
// Revision 1.64  2000/07/20 16:26:06  venkatan
// Mouse Location Display format - is now controlled by printf type
// format strings specified by the VIEW_DATA_AREA command
//
// Revision 1.63  2000/07/20 15:42:59  wenger
// Fixed bug 603 (GData errors caused by problems in new parser); eliminated
// old parser.
//
// Revision 1.62  2000/07/19 20:11:36  wenger
// Code to read data from sockets is more robust (hopefully fixes BMRB/Linux
// problem); background color of upper left part of JS changed to red when a
// dialog is shown; more debug output added.
//
// Revision 1.61  2000/07/14 21:13:07  wenger
// Speeded up 3D GData processing by a factor of 2-3: improved the parser
// used for GData; eliminated Z sorting for bonds-only 3D views; eliminated
// DEViseAtomTypes for atoms used only to define bond ends; reduced string-
// based processing; eliminated various unused variables, etc.
//
// Revision 1.60  2000/07/11 16:39:18  venkatan
// *** empty log message ***
//
// Revision 1.59  2000/07/10 12:26:02  venkatan
// *** empty log message ***
//
// Revision 1.58  2000/06/26 16:48:31  wenger
// Added client-side JavaScreen debug logging.
//
// Revision 1.57  2000/06/12 22:13:55  wenger
// Cleaned up and commented DEViseServer, JssHandler, DEViseComponentPanel,
// DEViseTrafficLight, YImageCanvas; added debug output of number of
// bytes of data available to the JS.
//
// Revision 1.56  2000/05/11 20:19:33  wenger
// Cleaned up jsdevisec.java and added comments; eliminated
// jsdevisec.lastCursor (not really needed).
//
// Revision 1.55  2000/05/04 15:53:33  wenger
// Added consistency checking, added comments, commented out unused code
// in DEViseScreen.java, DEViseCanvas.java, DEViseView.java,
// DEViseCmdDispatcher.java.
//
// Revision 1.54  2000/04/27 20:15:24  wenger
// Added DEViseCommands class which has string constants for all command
// names; replaced all literal command names in code with the appropriate
// DEViseCommand constants.
//
// Revision 1.53  2000/04/27 15:56:54  wenger
// Added some comments and requests for comments.
//
// Revision 1.52  2000/04/24 20:21:59  hongyu
// remove UI dependency of jspop and js
//
// Revision 1.51  2000/04/05 15:42:22  wenger
// Changed JavaScreen version to 3.3 because of memory fixes; other minor
// improvements in code; conditionaled out some debug code.
//
// Revision 1.50  2000/04/05 06:25:38  hongyu
// fix excessive memory usage problem associated with gdata
//
// Revision 1.49  2000/04/03 21:21:22  wenger
// When new GData arrives for a view, we remove the old GData from the
// view and call the garbage collector before constructing the new
// GData objects, so that the old GData objects are at least hopefully
// destroyed before the new ones are created.
//
// Revision 1.48  2000/04/03 05:29:35  hongyu
// *** empty log message ***
//
// Revision 1.47  2000/03/31 19:29:04  wenger
// Changed code so that views and GData objects get garbage collected when
// a session is closed; added debug code for tracking construction and
// finalization of DEViseView and DEViseGData objects; other minor GData-
// related improvements.
//
// Revision 1.46  2000/03/23 16:26:13  wenger
// Cleaned up headers and added requests for comments.
//
// Revision 1.45  2000/02/23 21:12:12  hongyu
// *** empty log message ***
//
// Revision 1.44  2000/02/16 15:15:31  wenger
// Temporary change so that the JavaScreen accepts the current form
// of the JAVAC_DrawCursor command.
//
// Revision 1.43  2000/02/16 08:53:57  hongyu
// *** empty log message ***
//
// Revision 1.42  1999/12/10 15:30:12  wenger
// Molecule dragging greatly speeded up by drawing plain (unshaeded) circles
// during drag; split off protocol version from "main" version.
//
// Revision 1.41  1999/10/10 08:49:51  hongyu
// Major changes to JAVAScreen have been commited in this update, including:
// 1. restructure of JavaScreen internal structure to adapt to vast changes
//    in DEVise and also prepare to future upgrade
// 2. Fix a number of bugs in visualization and user interaction
// 3. Add a number of new features in visualization and user interaction
// 4. Add support for complicated 3D molecular view
//
// Revision 1.40  1999/09/24 17:11:46  hongyu
// adding support for 3-d molecule view
//
// Revision 1.39  1999/08/24 08:45:53  hongyu
// *** empty log message ***
//
// Revision 1.38  1999/08/17 06:15:16  hongyu
// *** empty log message ***
//
// Revision 1.37  1999/08/03 05:56:48  hongyu
// bug fixes    by Hongyu Yao
//
// Revision 1.36  1999/07/27 17:11:18  hongyu
// *** empty log message ***
//
// Revision 1.35  1999/06/23 20:59:15  wenger
// Added standard DEVise header.
//

// ========================================================================

// DEViseCmdDispatcher.java

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.net.*;

public class DEViseCmdDispatcher implements Runnable
{
    private jsdevisec jsc = null;

    private Thread dispatcherThread = null;

    private String[] commands = null;

    private DEViseCommSocket commSocket = null;

    public String errMsg = null;

    // status = 0, dispatcher is not running
    // status = 1, dispatcher is running
    private int status = 0;

    // isOnline = true, successfully established connection to server, i.e.
    //                  get a valid connection ID
    // isOnline = false, connection to server is not established
    private boolean isOnline = false;

    // ADD COMMENT -- what does this mean?
    private boolean isAbort = false;

    private static final boolean _debug = false;


    public DEViseCmdDispatcher(jsdevisec what)
    {
        jsc = what;
    }

    public synchronized int getStatus()
    {
        return status;
    }

    private synchronized void setStatus(int arg)
    {
        status = arg;

        jsc.jscreen.reEvaluateMousePosition();
    }

    public synchronized boolean getOnlineStatus()
    {
        return isOnline && (commSocket != null);
    }

    private synchronized void setOnlineStatus(boolean flag)
    {
        isOnline = flag;
    }

    public synchronized boolean getAbortStatus()
    {
        return isAbort;
    }

    private synchronized void setAbortStatus(boolean flag)
    {
        isAbort = flag;
    }

    // it is assumed that status = 0 while method start() is called
    // it is also assumed that while status = 0, dispatcher thread is not running

    // Initiate a command from the JavaScreen to the jspop or devised.
    // Note that cmd may actually contain more than one command (separated
    // by newlines).
    public void start(String cmd)
    {
        if (getStatus() != 0) {
            jsc.showMsg("JavaScreen is busy working\nPlease try again later");
            return;
        }

        setStatus(1);
        jsc.animPanel.start();
        jsc.stopButton.setBackground(Color.red);
        jsc.stopNumber = 0;

	// If we don't have a socket to the jspop, attempt to create one.
        if (commSocket == null) {
            boolean isEnd = false;
            while (!isEnd) {
                if (!connect()) {
                    String result = jsc.confirmMsg(errMsg + "\n \nDo you wish to try again?");
                    if (result.equals(YMsgBox.YIDNO)) {
                        jsc.animPanel.stop();
                        jsc.stopButton.setBackground(DEViseUIGlobals.bg);
                        setStatus(0);
                        return;
                    }
                } else {
                    isEnd = true;
                }
            }
        }

	// If we don't have a connection yet, prepend a connection request
	// command to whatever was passed in.
        String command = cmd;
        if (!getOnlineStatus()) {
            command = DEViseCommands.CONNECT + " {" + DEViseGlobals.username + "} {"
                       + DEViseGlobals.password + "} {" + DEViseGlobals.PROTOCOL_VERSION + "}\n" + command;
        }

        commands = DEViseGlobals.parseStr(command);
        if (commands == null || commands.length == 0) {
            jsc.showMsg("Invalid command: \"" + cmd + "\"");
            jsc.animPanel.stop();
            jsc.stopButton.setBackground(DEViseUIGlobals.bg);
            setStatus(0);
            return;
        }

        jsc.jscreen.setLastAction(command);

	// Note: command(s) will actually be sent by the run() method
	// of this class.
        dispatcherThread = new Thread(this);
        dispatcherThread.start();
    }

    public void stop()
    {
        stop(false, false);
    }

    // ADD COMMENT -- what do isDisconnect and isExit mean?
    public void stop(boolean isDisconnect, boolean isExit)
    {
        if (isDisconnect) {
            if (getStatus() != 0 ) {
                String result = null;
                if (isExit) {
                    result = jsc.confirmMsg("JavaScreen still busy talking to server!\nDo you wish to exit anyway?");
                } else {
                    result = jsc.confirmMsg("Abort request already send to the server!\nAre you so impatient that you want to close the connection right away?");
                }

                if (result.equals(YMsgBox.YIDNO)) {
                    return;
                } else {
                    if (dispatcherThread != null) {
                        dispatcherThread.stop();
                        dispatcherThread = null;
                    }

                    disconnect();

                    jsc.animPanel.stop();
                    jsc.stopButton.setBackground(DEViseUIGlobals.bg);
                    jsc.jscreen.updateScreen(false);

                    setStatus(0);

                    return;
                }
            } else {
                if (isExit) {
                    if (commSocket != null) {
                        if (getOnlineStatus()) {
                            try {
                                jsc.pn("Sending: \"" + DEViseCommands.EXIT +
				  "\"");
                                commSocket.sendCmd(DEViseCommands.EXIT);
                            } catch (YException e) {
                                jsc.showMsg(e.getMsg());
                            }
                        }
                    }

                    disconnect();
                    jsc.jscreen.updateScreen(false);
                }

                return;
            }
        }

        if (getStatus() == 0) {
            return;
        } else {
            setAbortStatus(true);
        }
    }

    private synchronized boolean connect()
    {
        try {
            commSocket = new DEViseCommSocket(DEViseGlobals.hostname, DEViseGlobals.cmdport, DEViseGlobals.imgport);
            return true;
        } catch (YException e) {
            errMsg = e.getMessage() + " in " + e.getWhere();
            disconnect();
            return false;
        }
    }

    private synchronized void disconnect()
    {
        if (commSocket != null) {
            commSocket.closeSocket();
            commSocket = null;
        }

        isOnline = false;
        isAbort = false;
        DEViseGlobals.connectionID = DEViseGlobals.DEFAULTID;
    }

    public void run()
    {
        try {
            for (int i = 0; i < commands.length; i++) {
                if (getAbortStatus()) {
                    setAbortStatus(false);
                    break;
                }

                if (commands[i].length() == 0) {
                    continue;
                } else if (!commands[i].startsWith(DEViseCommands.JS_PREFIX)) {
                    jsc.pn("Invalid command: " + commands[i]);
                    continue;
                }

                if (commands[i].startsWith(DEViseCommands.CLOSE_SESSION)) {
                    jsc.jscreen.updateScreen(false);

                    try {
                        jsc.pn("Sending: \"" + commands[i] + "\"");
                        commSocket.sendCmd(commands[i]);
                    } catch (YException e1) {
                        jsc.showMsg(e1.getMsg());
                        disconnect();
                    }
                } else if (commands[i].startsWith(DEViseCommands.OPEN_SESSION)) {
                    jsc.jscreen.updateScreen(false);
                    processCmd(commands[i]);
                } else {
                    processCmd(commands[i]);
                }
            }

	    // Note: this is the "standard" place where the GUI gets
	    // changed to indicate that the command is finished.
            jsc.animPanel.stop();
            jsc.stopButton.setBackground(DEViseUIGlobals.bg);

            //jsc.jscreen.reEvaluateMousePosition();
        } catch (YException e) {
            jsc.animPanel.stop();
            jsc.stopButton.setBackground(DEViseUIGlobals.bg);

            // turn off the counter and the traffic light
            jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_IDLE, false);
            jsc.viewInfo.updateCount(0);

            // user pressed the stop button
            switch (e.getID()) {
            case 0: // low level communication error
                jsc.showMsg(e.getMsg());
                jsc.jscreen.updateScreen(false);
                disconnect();
                break;
            case 1: // invalid response from server
            case 2: // ill-formated command received from server
                jsc.showMsg(e.getMsg());
                jsc.jscreen.updateScreen(false);
                try {
                    jsc.pn("Sending: \"" + DEViseCommands.CLOSE_SESSION +
		      "\"");
                    commSocket.sendCmd(DEViseCommands.CLOSE_SESSION);
                } catch (YException e1) {
                    jsc.showMsg(e1.getMsg());
                    disconnect();
                }
                break;
            default:
                jsc.showMsg(e.getMsg());
                jsc.jscreen.updateScreen(false);
                disconnect();
                break;
            }
        }

        setAbortStatus(false);
        setStatus(0);
    }

    private void processCmd(String command) throws YException
    {
        // sending command to server, and wait until server finish processing and
        // returned a list of commands
        String[] rsp = sendCommand(command);

        // turn on the 'process' light
        jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_PROCESSING, true);

        for (int i = 0; i < rsp.length; i++) {
            // adjust the counter
            jsc.viewInfo.updateCount(rsp.length - 1 - i);

	    jsc.pn("Processing command (" + (rsp.length - 1 - i) + ") " +
	      rsp[i]);
            DEViseDebugLog.log("Processing command (" +
	      (rsp.length - 1 - i) + ") " + rsp[i]);

	    processReceivedCommand(command, rsp[i]);

	    jsc.pn("  Done with command " + rsp[i]);
	    jsc.pn("  Free mem: " + Runtime.getRuntime().freeMemory() +
	      " Total mem: " + Runtime.getRuntime().totalMemory());
	    DEViseDebugLog.log("  Done with command " + rsp[i]);
        }

        // turn off the 'process' light
        jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_PROCESSING, false);

        System.gc();

        //System.out.println("Memory: " +
	    //Runtime.getRuntime().freeMemory() + "/" +
	    //Runtime.getRuntime().totalMemory());
    }

    // command is the command we sent; response is the command we got
    // in response.
    private void processReceivedCommand(String command, String response)
      throws YException
    {
        String[] args = DEViseGlobals.parseString(response);
        if (args == null || args.length < 1) {
            throw new YException(
              "Ill-formated command received from server \"" +
              response + "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

        if (args[0].equals(DEViseCommands.DONE)) {
            // this command will guaranteed to be the last
            if (command.startsWith(DEViseCommands.OPEN_SESSION)) {
                jsc.jscreen.updateScreen(true);
            }

        } else if (args[0].equals(DEViseCommands.FAIL)) {
            jsc.showMsg(response);
            jsc.jscreen.updateScreen(false);

        } else if (args[0].equals(DEViseCommands.ERROR)) {
            // this command will guaranteed to be the last
            if (!command.startsWith(DEViseCommands.GET_SESSION_LIST)) {
                jsc.showMsg(response);
            } else {
                jsc.showSession(new String[] {response}, false);
            }

        } else if (args[0].equals(DEViseCommands.UPDATE_SERVER_STATE)) {
            if (args.length != 2) {
                throw new YException(
                  "Ill-formated command received from server \"" +
                  response + "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }

            jsc.showServerState(args[1]);

        } else if (args[0].equals(DEViseCommands.CREATE_VIEW)) {
	    createView(response, args);

        } else if (args[0].equals(DEViseCommands.UPDATE_VIEW_IMAGE)) {
	    updateViewImage(response, args);

        } else if (args[0].equals(DEViseCommands.UPDATE_GDATA)) {
	    updateGData(response, args);

        } else if (args[0].equals(DEViseCommands.UPDATE_SESSION_LIST)) {
	    // Number of arguments is variable.
            jsc.showSession(args, true);

        } else if (args[0].equals(DEViseCommands.DRAW_CURSOR)) {
	    drawCursor(response, args);

        } else if (args[0].equals(DEViseCommands.ERASE_CURSOR)) {
            if (args.length != 3) {
                throw new YException(
                  "Ill-formated command received from server \"" + response +
                  "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }

            jsc.jscreen.removeCursor(args[1], args[2]);

        } else if (args[0].equals(DEViseCommands.UPDATE_RECORD_VALUE)) {
	    // Number of arguments is variable.
            jsc.showRecord(args);

        } else if (args[0].equals(DEViseCommands.VIEW_DATA_AREA)) {
	    viewDataArea(response, args);

        } else if (args[0].equals(DEViseCommands.DELETE_VIEW)) {
            if (args.length != 2) {
                throw new YException(
                  "Ill-formated command received from server \"" + response +
                  "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }

            jsc.jscreen.removeView(args[1]);

        } else if (args[0].equals(DEViseCommands.DELETE_CHILD_VIEWS)) {
            if (args.length != 2) {
                throw new YException(
                  "Ill-formated command received from server \"" + response +
                  "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }

            jsc.jscreen.removeChildViews(args[1]);

        } else if (args[0].equals(DEViseCommands.USER)) {
	    user(args);

        } else if (args[0].equals(DEViseCommands.SHOW_VIEW_HELP)) {
            if (args.length != 3) {
                throw new YException(
                  "Ill-formated command received from server \"" + response +
                  "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }

            // Modified - Ven
            if (!DEViseGlobals.helpBox) {
               jsc.jscreen.showHelpMsg(args[1], args[2]);
            } else {
               jsc.showViewDialogHelp(args[2]);
               DEViseGlobals.helpBox = false ;
            }

        } else {
            throw new YException("Unsupported command (" + response +
              ")received from server", "DEViseCmdDispatcher::processCmd()", 2);
        }
    }

    private void createView(String command, String[] args) throws YException
    {
        if (args.length < 25) {
            throw new YException(
              "Ill-formated command received from server \"" +
              command + "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

        String viewname = args[1];
        String parentname = args[2];
        String piledname = args[3];
        try {
            int x = Integer.parseInt(args[4]);
            int y = Integer.parseInt(args[5]);
            int w = Integer.parseInt(args[6]);
            int h = Integer.parseInt(args[7]);
            float z = (Float.valueOf(args[8])).floatValue();
            int dim = Integer.parseInt(args[9]);
            Rectangle viewloc = new Rectangle(x, y, w, h);
            x = Integer.parseInt(args[10]);
            y = Integer.parseInt(args[11]);
            w = Integer.parseInt(args[12]);
            h = Integer.parseInt(args[13]);
            Rectangle dataloc = new Rectangle(x, y, w, h);

            int bg, fg;
            Color color = DEViseUIGlobals.convertColor(args[14]);
            if (color != null) {
                fg = color.getRGB();
            } else {
                throw new NumberFormatException();
            }
            color = DEViseUIGlobals.convertColor(args[15]);
            if (color != null) {
                bg = color.getRGB();
            } else {
                throw new NumberFormatException();
            }
            //int bg = (Color.white).getRGB();
            //int fg = (Color.black).getRGB();

            String xtype = args[16], ytype = args[17];

            // Mouse movement grid -- not yet used.
            float gridx = (Float.valueOf(args[18])).floatValue();
            float gridy = (Float.valueOf(args[19])).floatValue();

            int rb = Integer.parseInt(args[20]);
            int cm = Integer.parseInt(args[21]);
            int dd = Integer.parseInt(args[22]);
            int ky = Integer.parseInt(args[23]);

            String viewtitle = args[24];
            int dtx = 0, dty = 0;
            Font dtf = null;

            int dvinfo = 1; // whether to show mouse location
            if (args.length == 26) {
                // When viewtitle is empty, then arg 25 is the show mouse
                // location - dvinfo

                if (args[25].equals("")) {
                    dvinfo = 1;
                } else{
                    dvinfo = Integer.parseInt(args[25]);
                }
            }

            if (viewtitle.length() > 0) {
                if (args.length < 31 || args.length > 32) {
                    throw new YException(
                      "Ill-formated command received from server \"" +
                      command + "\"",
                      "DEViseCmdDispatcher::processCmd()", 2);
                }

                dtx = Integer.parseInt(args[25]);
                dty = Integer.parseInt(args[26]);

                int dtff;
                if (args[27].equals("")) {
                    dtff = 0;
                } else {
                    dtff = Integer.parseInt(args[27]);
                }

                int dtfs;
                if (args[28].equals("")) {
                    dtfs = 14;
                } else {
                    dtfs = Integer.parseInt(args[28]);
                }

                int dtb;
                if (args[29].equals("")) {
                    dtb = 0;
                } else {
                    dtb = Integer.parseInt(args[29]);
                }

                int dti;
                if (args[30].equals("")) {
                    dti = 0;
                } else {
                    dti = Integer.parseInt(args[30]);
                }

                if (args.length == 32) {
                    if(args[31].equals("")){
                        dvinfo = 1;
                    } else {
                        dvinfo = Integer.parseInt(args[31]);
                    }
                }

                dtf = DEViseUIGlobals.getFont(dtfs, dtff, dtb, dti);
                if (dtf != null) {
                    Toolkit tk = Toolkit.getDefaultToolkit();
                    FontMetrics fm = tk.getFontMetrics(dtf);

                    int ac = fm.getAscent();
                    int dc = fm.getDescent();
                    int ld = fm.getLeading();

                    ac = ac + ld / 2;
                    dc = dc + ld / 2;

                    int sh = fm.getHeight();
                    int sw = fm.stringWidth(viewtitle);

                    int height = 0, width = 0;

                    dty = dty + height / 2 + ac - sh / 2;
                    dtx = dtx + width / 2 - sw / 2;
                }
            }

            DEViseView view = new DEViseView(jsc, parentname, viewname,
              piledname, viewtitle, viewloc, z, dim, bg, fg, dataloc,
              xtype, ytype, gridx, gridy, rb, cm, dd, ky);
            if (view != null) {
                view.viewDTFont = dtf;
                view.viewDTX = dtx + view.viewLocInCanvas.x;
                view.viewDTY = dty + view.viewLocInCanvas.y;
                view.isViewInfo = (dvinfo == 1);
            }

            jsc.jscreen.addView(view);
        } catch (NumberFormatException e) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

    }

    private void updateViewImage(String command, String[] args)
      throws YException
    {
        if (args.length != 3) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

        String viewname = args[1];
        int imageSize;
        try {
            imageSize = Integer.parseInt(args[2]);
            if (imageSize <= 0) {
                throw new YException(
                  "Ill-formated command received from server \"" +
                  command + "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }
        } catch (NumberFormatException e) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

        byte[] imageData = receiveData(imageSize);

        MediaTracker tracker = new MediaTracker(jsc);
        Toolkit kit = jsc.getToolkit();
        Image image = kit.createImage(imageData);
        tracker.addImage(image, 0);
        try {
            tracker.waitForID(0);
        }  catch (InterruptedException e) {
        }

        if (tracker.isErrorID(0)) {
            throw new YException("Invalid image data for view \"" +
              viewname + "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

        jsc.jscreen.updateViewImage(viewname, image);
    }

    private void updateGData(String command, String[] args) throws YException
    {
        if (args.length != 7) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

        String viewname = args[1];
        DEViseView view = jsc.jscreen.getView(viewname);

        // Remove the old GData from the view and hopefully free it.
        //        DEViseView view = jsc.jscreen.getView(viewname);
        //if (view != null) {
        //    view.removeAllGData();
        //    System.gc();
        //}

        float xm, xo, ym, yo;
        int gdataSize;
        try {
            xm = (Float.valueOf(args[2])).floatValue();
            xo = (Float.valueOf(args[3])).floatValue();
            ym = (Float.valueOf(args[4])).floatValue();
            yo = (Float.valueOf(args[5])).floatValue();
            gdataSize = Integer.parseInt(args[6]);
            if (gdataSize <= 0) {
                throw new YException(
                  "Ill-formated command received from server \"" +
                  command + "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }
        } catch (NumberFormatException e) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

//          System.out.println("Free memory(before new GData): " +
//            Runtime.getRuntime().freeMemory() + "/" +
//            Runtime.getRuntime().totalMemory());

        byte[] gdata = receiveData(gdataSize);

        String gdataStr = new String(gdata);
        if (gdataStr.equals("\u0004")) {
            jsc.jscreen.updateGData(viewname, null);
        } else {
            // This is used to handle the case when JSPoP sending
            // all the GData in one command (I know currently devised
            // is sending one
            // GData per command) and separate them use \x04.
            String[] GData = DEViseGlobals.parseStr(gdataStr, "\u0004",
              false);
            if (GData == null) {
                throw new YException(
                  "Invalid GData received for view \"" + viewname +
                  "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }

            Vector gdList = new Vector();
            for (int j = 0; j < GData.length; j++) {
                if (GData[j] == null) {
                    throw new YException(
                      "Invalid GData received for view \"" + viewname +
                      "\"", "DEViseCmdDispatcher::processCmd()", 2);
                }

                // Split the GData into records.
                String[] results = DEViseGlobals.parseStr(GData[j]);
                if (results == null || results.length == 0) {
                    throw new YException(
                      "Invalid GData received for view \"" + viewname +
                      "\"", "DEViseCmdDispatcher::processCmd()", 2);
                }

                DEViseGData.defaultFont = null;

                for (int k = 0; k < results.length; k++) {
                    DEViseGData data = null;
                    //jsc.pn("Received gdata is: \"" + results[k] + "\"");
                    try {
                        data = new DEViseGData(jsc, view, results[k], xm,
                          xo, ym, yo);
                    } catch (YException e1) {
                        //throw new YException("Invalid GData received for view \"" + viewname + "\"", "DEViseCmdDispatcher::processCmd()", 2);
                        throw new YException(e1.getMsg(), 2);
                    }

                    gdList.addElement(data);
                    results[k] = null;
                }

                if (_debug) {
                    System.out.println("number of new gdata: " +
                      results.length);
                }

                jsc.jscreen.updateGData(viewname, gdList);
                results = null;
                gdList = null;
            }
        }

        gdata = null;

//          System.gc();

//          System.out.println("Free memory(after new GData): " +
//              Runtime.getRuntime().freeMemory() + "/" +
//              Runtime.getRuntime().totalMemory());
    }

    private void drawCursor(String command, String[] args) throws YException
    {
        if (args.length != 14) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

        try {
            String cursorName = args[1];
            String viewname = args[2];

            int x0 = Integer.parseInt(args[3]);
            int y0 = Integer.parseInt(args[4]);
            int w = Integer.parseInt(args[5]);
            int h = Integer.parseInt(args[6]);
            String move = args[7];
            String resize = args[8];
            Rectangle rect = new Rectangle(x0, y0, w, h);
            float gridx = (Float.valueOf(args[9])).floatValue();
            float gridy = (Float.valueOf(args[10])).floatValue();
            int isedge = Integer.parseInt(args[11]);
            Color color = DEViseUIGlobals.convertColor(args[12]);
            //TEMP int type = Integer.parseInt(args[13]);
            int type = 0;//TEMP

            DEViseCursor cursor = null;
            try {
                cursor = new DEViseCursor(jsc, cursorName, viewname,
                  rect, move, resize, gridx, gridy, isedge, type, color);
            } catch (YException e1) {
                throw new YException(
                  "Invalid cursor data received for view \"" + viewname +
                  "\"", "DEViseCmdDispatcher::processCmd()", 2);
            }

            jsc.jscreen.updateCursor(viewname, cursor);
        } catch (NumberFormatException e) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }
    }

    private void viewDataArea(String command, String[] args) throws YException
    {
        if (args.length < 5 || args.length > 6) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }

        try {
            String viewname = args[1];
            String viewaxis = args[2];
            float min = (Float.valueOf(args[3])).floatValue();
            float max = (Float.valueOf(args[4])).floatValue();

            // Ven - for mouse display format string
            String format = null;
            if (args.length == 6) {
               format = args[5];
            } 

            jsc.jscreen.updateViewDataRange(viewname, viewaxis, min, max,
              format);
        } catch (NumberFormatException e) {
            throw new YException(
              "Ill-formated command received from server \"" + command +
              "\"", "DEViseCmdDispatcher::processCmd()", 2);
        }
    }

    private void user(String[] args) throws YException
    {
        if (args.length != 2) {
            throw new YException(
              "Invalid connection ID received from server",
              "DEViseCmdDispatcher::processCmd()", 2);
        }

        try {
            int id = Integer.parseInt(args[1]);
            if (id < 0 && id != DEViseGlobals.DEFAULTID) {
                throw new NumberFormatException();
            } else {
                DEViseGlobals.connectionID = id;
                setOnlineStatus(true);
            }
        } catch (NumberFormatException e) {
            throw new YException(
              "Invalid connection ID received from server",
              "DEViseCmdDispatcher::processCmd()", 2);
        }
    }

    private byte[] receiveData(int size) throws YException
    {
        byte[] imgData = null;

        // turn on the receive light
        jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_RECEIVING, true);

        jsc.pn("Trying to receive data (" + size + ") from socket ...");
	jsc.pn("  Bytes available: " + commSocket.dataAvailable());
        DEViseDebugLog.log("Trying to receive data (" + size +
	  ") from socket ...");
	DEViseDebugLog.log("  Bytes available: " + commSocket.dataAvailable());

        imgData = commSocket.receiveData(size);

        jsc.pn("Successfully received data (" + size + ") from socket ...");
	jsc.pn("  Last byte = " + imgData[imgData.length - 1]);
	jsc.pn("  Bytes available: " + commSocket.dataAvailable());
        DEViseDebugLog.log("Successfully received data (" + size +
	  ") from socket ...");

        // turn off the receive light
        jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_RECEIVING, false);

        if (imgData == null) {
            throw new YException("Invalid response received from server", "DEViseCmdDispatcher::receiveData()", 1);
        }

        return imgData;
    }

    private String[] sendCommand(String command) throws YException
    {
        String response = null;
        boolean isEnd = false, isFinish = false;
        Vector rspbuf = new Vector();

        // turn on the 'send' light
        jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_SENDING, true);
        // sending command to server, and expect an immediate response of "JAVAC_Ack"
        jsc.pn("Sending: \"" + command + "\"");
        commSocket.sendCmd(command);
        // turn off the 'send' light
        jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_SENDING, false);

        // turn on the counter
        jsc.viewInfo.updateCount(0);
        // turn on the 'receive' light
        jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_RECEIVING, true);

        // wait to receive the response from server

	// isEnd is true when we have finished receiving *all* commands.
        while (!isEnd) {
	    // isFinish is true when we have finished receiving the current
	    // command.
            isFinish = false;

            while (!isFinish) {
                try {
                    response = commSocket.receiveCmd();
                    jsc.pn("Receive: \"" + response + "\"");
                    isFinish = true;
                } catch (InterruptedIOException e) {
                    if (getAbortStatus()) {
                        commSocket.sendCmd(DEViseCommands.ABORT);
                        setAbortStatus(false);
                    }
                }
            }

            if (response == null || response.length() == 0) {
                throw new YException("Unexpected response received from server", "DEViseCmdDispatcher::sendCommand()", 1);
            } else {
                String[] cmds = DEViseGlobals.parseString(response);
                if (cmds == null || cmds.length == 0) {
                    throw new YException("Ill-formated command received from server \"" + response + "\"", "DEViseCmdDispatcher::sendCommand()", 2);
                } else {
                    String cmd = cmds[0];
                    // Rip off the { and } around the command but not the arguments
                    for (int j = 1; j < cmds.length; j++)
                        cmd = cmd + " {" + cmds[j] + "}";

                    if (cmd.startsWith(DEViseCommands.JS_PREFIX)) {
                        if (cmd.startsWith(DEViseCommands.ACK)) {
                            jsc.animPanel.setActiveImageNumber(5);
                        } else {
                            if (cmd.startsWith(DEViseCommands.DONE) ||
			      cmd.startsWith(DEViseCommands.ERROR) ||
			      cmd.startsWith(DEViseCommands.FAIL)) {
                                isEnd = true;
                            }

                            rspbuf.addElement(cmd);

                            jsc.viewInfo.updateCount(rspbuf.size());
                        }
                    } else {
                	throw new YException("Unsupported command (" +
			  response + ")received from server",
		          "DEViseCmdDispatcher::processCmd()", 2);
                    }
                }
            }
        }

        String[] rspstr = new String[rspbuf.size()];
        for (int i = 0; i < rspbuf.size(); i++)
            rspstr[i] = (String)rspbuf.elementAt(i);

        // turn off the 'receive' light
        jsc.viewInfo.updateImage(DEViseTrafficLight.STATUS_RECEIVING, false);

        return rspstr;
    }
}

