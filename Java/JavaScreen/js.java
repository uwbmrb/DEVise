// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2001
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// Top-level class for the JavaScreen running as an application, not
// an applet.  This class parses command-line arguments, etc., and
// then creates a jsdevisec.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.45  2001/10/16 22:14:28  wenger
// Major cleanup of command playback code; fixed bug 711 (problem with
// command log playback).
//
// Revision 1.44  2001/10/10 19:28:25  xuk
// Added display control command line argument/parameter for auto playback.
// For JS application: command-line argument: -playbackdisplayoff to turn off display, default is turning on display;
// For JS applet: parameter playbackdisplay = true|false to turn on|off display.
//
// Revision 1.43  2001/10/05 15:51:35  wenger
// Minor cleanup: fixed usage messages, improved argument checking.
//
// Revision 1.42  2001/10/02 22:02:11  xuk
// Added new command-line option for client log playback.
// Modified checkArguments() to check -clientlog, -autoplayback and playbackoriginal arguments.
//
// Revision 1.41  2001/05/11 20:36:12  wenger
// Set up a package for the JavaScreen code.
//
// Revision 1.40  2001/05/07 21:53:26  wenger
// Found and fixed bug 670; jss checks for /tmp.X1-lock before starting
// Xvfb.
//
// Revision 1.39  2001/01/08 20:31:55  wenger
// Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
// back onto the trunk.
//
// Revision 1.38.4.9  2000/12/29 22:41:39  wenger
// Fixed problems with the JavaScreen client not getting destroyed
// properly, except that it still doesn't work right if you go to a
// different web page in the browser, then quit.
//
// Revision 1.38.4.8  2000/12/11 22:14:19  wenger
// Merged chagnes from link_gui_improvements thru js_restart_improvements
// onto the branch, removing imgport code from the restart scripts.
//
// Revision 1.38.4.7  2000/11/29 22:40:57  wenger
// Abstracted common code from jsa and jsb into new DEViseJSApplet
// superclass; other minor cleanups.
//
// Revision 1.38.4.6  2000/11/22 17:44:00  wenger
// Finished cleanup of static variables fix; re-changed CGI command code to
// match the current version of the CGI script.
//
// Revision 1.38.4.5  2000/11/21 01:51:34  xuk
// Change some non-final static variables to non-static. Add a new class, DEViseJSValues, to contain all these variables and attach to every JS, JSA, JSB instance.
//
// Revision 1.38.4.4  2000/11/16 17:30:52  wenger
// Made static variables into static final variables.
//
// Revision 1.38.4.3  2000/11/09 21:43:13  wenger
// js.cgi now uses CGI library, various other cleanups; changed CGI parameter
// names slightly; added -cgi argument to JS usage message.
//
// Revision 1.38.4.2  2000/10/28 19:29:59  xuk
// add argument -cgi cgiURL for cgi communication.
//
// Revision 1.38.4.1  2000/09/01 20:22:28  xuk
// In main() and checkArguments(), delete imgport checking.
//
// Revision 1.38  2000/07/19 20:11:38  wenger
// Code to read data from sockets is more robust (hopefully fixes BMRB/Linux
// problem); background color of upper left part of JS changed to red when a
// dialog is shown; more debug output added.
//
// Revision 1.37  2000/06/26 16:48:32  wenger
// Added client-side JavaScreen debug logging.
//
// Revision 1.36  2000/04/24 20:22:01  hongyu
// remove UI dependency of jspop and js
//
// Revision 1.35  2000/04/05 06:25:40  hongyu
// fix excessive memory usage problem associated with gdata
//
// Revision 1.34  2000/03/23 16:26:18  wenger
// Cleaned up headers and added requests for comments.
//
// Revision 1.33  2000/02/18 22:21:17  wenger
// Various changes to make cron scripts work better with new two-machine
// setup: added -id argument to devise, jspop, jss; updated cron scripts
// that check status of jspop, etc.; improved usage messages of jspop,
// jss, js; improved DEVise.kill script; removed obsolete sections of
// Java code.
//
// Revision 1.32  1999/10/10 08:49:54  hongyu
// Major changes to JAVAScreen have been commited in this update, including:
// 1. restructure of JavaScreen internal structure to adapt to vast changes
//    in DEVise and also prepare to future upgrade
// 2. Fix a number of bugs in visualization and user interaction
// 3. Add a number of new features in visualization and user interaction
// 4. Add support for complicated 3D molecular view
//
// Revision 1.31  1999/06/23 20:59:20  wenger
// Added standard DEVise header.
//

// ========================================================================

// js.java

//TEMP package edu.wisc.cs.devise.js.jsc;
package JavaScreen;

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.util.*;
import java.io.*;

public class js extends Frame
{
    private static final String usage = new String(
        "Usage: java JavaScreen.js [options]\n" +
	"  -host[string]: host the jspop is running on (default: localhost)\n" +
	"  -cmdport[number]: port for command socket from jspop (default: " +
	  DEViseGlobals.DEFAULTCMDPORT + ")\n" +
	"  -user[string]: name of user (default: " + DEViseGlobals.DEFAULTUSER
	  + ")\n" +
	"  -pass[string]: password of user (default: " +
	  DEViseGlobals.DEFAULTPASS + ")\n" +
	"  -session[filename]: session to load at startup (default: none)\n" +
	"  -fgcolor[number+number+number]: RGB for JavaScreen foreground\n" +
	  "    (default: 255+255+255)\n" +
	"  -bgcolor[number+number+number]: RGB for JavaScreen background\n" +
	  "    (default: 64+96+0)\n" +
	"  -rubberbandlimit[widthxheight]: minimum size for rubberband to " +
	  "have any effect\n    (default: 4x4)\n" +
	"  -screensize[widthxheight]: window size in pixels\n" +
	  "    (default: display width-80xdisplay height-120)\n" +
	"  -log: turn on debug logging (default: off)\n" +
	"  -usecgi: forces the JS to use CGI communication (default: off)\n" +
	"  -cgiurl: URL for CGI communcation (default: none)\n" +
	"  -debug[number]: set debug level (default: 0)\n" +
	"  -clientlog[logfile]: specify log to play back (default: none)\n" +
	"  -autoplayback: automatically start playing back client log file\n" +
	  "    (default: false)\n" +
	"  -playbackoriginal: play back client log file at original speed\n" +
	  "    (default: false)\n" +
	"  -playbackdisplayoff: turn off display during command log playback\n" +
	"  -usage: print this message");

    // -host[hostname]:
    //      hostname: The IP address of the machine where jspop or DEVise Server
    //                is running, if bland, use the defaults
    //      default: "localhost"
    //      example: "hostbiron.cs.wisc.edu"
    // -cmdport[port]:
    //      port: The command port, if blank, use the defaults
    //      default: 6666
    //      example: "cmdport6666"
    // -user[username]:
    //      username: the name of user, if blank, use the defaults
    //      default: 'guest'
    //      example: "-userguest"
    // -pass[password]:
    //      password: the password of the user, if blank, use the defaults,
    //                if username if blank, this field has no effect
    //      default: none
    //      example: "-passnone"
    // -session[filename]:
    //      filename: the name of the session file need to be opened
    //      default: none
    //      example: "-sessionCOD1.ds"
    // -debug[number]:
    //      number: The debug level, no debug information is written if less
    //              than or equals to 0
    //      default: No Debug information is written
    //      example: "-debug0"
    // -bgcolor[number+number+number]
    //      number: RGB values, from 0 to 255 in r,g,b order
    //      default: 64+96+0
    //      example: "-bgcolor64+96+0
    // -fgcolor[number+number+number]
    //      number: RGB values, from 0 to 255 in r,g,b order
    //      default: 255+255+255
    //      example: "-bgcolor255+255+255
    // -rubberbandlimit[widthxheight]
    //      width, height: positive integer, rubber band dimension must larger
    //                     than these values before it is actually be considered
    //                     as a rubberband
    //      default: 0x0
    //      example: "-rubberbandlimit0x0"
    // -screensize[widthxheight]
    //      width, height: The assumed physical screen size, can not exceed the
    //                     real physical screen size, mininum is 320x200
    //      default: real physical screen size
    //      example: "-screensize640x480
    //
    public DEViseJSValues jsValues = null;
    public jsdevisec jsc = null;

    public js(DEViseJSValues jv)
    {
	jsValues = jv;

       	Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension dim = kit.getScreenSize();
        jsValues.uiglobals.maxScreenSize.width = dim.width - 80;
        jsValues.uiglobals.maxScreenSize.height = dim.height - 120;
        jsValues.uiglobals.minScreenSize.width = 300;
        jsValues.uiglobals.minScreenSize.height = 240;

        // get the animation symbol images from server
        MediaTracker tracker = new MediaTracker(this);
        Toolkit toolkit = this.getToolkit();
        Vector images = new Vector();
        Image image = null;
        for (int i = 0; i < 11; i++) {
            image = toolkit.getImage("devise" + i + ".gif");
            tracker.addImage(image, 0);
            try  {
                tracker.waitForID(0);
            }  catch (InterruptedException e)  {
            }

            if (tracker.isErrorID(0)) {
                YMsgBox box = new YMsgBox(this, true, true, "Cannot get JavaScreen "
                    + "animation symbols!\nDo you wish to continue without "
                    + "animation effects?", "Confirm", YMsgBox.YMBXYESNO, null,
                    null, null);
                box.open();
                String result = box.getResult();
                if (result.equals(YMsgBox.YIDYES)) {
                    images = null;
                    break;
                } else {
                    System.exit(1);
                }
            }

            images.addElement(image);
        }

        // start JavaScreen
        jsc = new jsdevisec(null, this, images, jsValues);
        add(jsc);
        setTitle(DEViseUIGlobals.javaScreenTitle);
        pack();

        // reposition JavaScreen so it is in the center of the screen
        Point loc = new Point(0, 0);
        Dimension size = getSize();
        loc.y = loc.y + dim.height / 2 - size.height / 2;
        loc.x = loc.x + dim.width / 2 - size.width / 2;
        if (loc.y < 0)
            loc.y = 0;
        if (loc.x < 0)
            loc.x = 0;

        setLocation(loc);

        // necessary for processEvent method to work
        this.enableEvents(AWTEvent.WINDOW_EVENT_MASK);
/*
        System.out.println("Memory: " +
	    Runtime.getRuntime().freeMemory() + "/" +
	    Runtime.getRuntime().totalMemory());
*/
    }

    protected void processEvent(AWTEvent event)
    {
        if (event.getID() == WindowEvent.WINDOW_CLOSING)  {
            jsc.destroy();
            return;
        }

        super.processEvent(event);
    }

    public static void main(String[] args)
    {
        String version = System.getProperty("java.version");
        if (version.compareTo("1.1") < 0)  {
            System.out.println("Error: Java version 1.1 or greater is needed to run this program\nThe version you used is " + version);
            System.exit(1);
        }

	DEViseJSValues jv = new DEViseJSValues();

        checkArguments(args, jv);

        jv.uiglobals.isApplet = false;
	jv.uiglobals.inBrowser = false;
        jv.connection.connectionID = DEViseGlobals.DEFAULTID;

        if (jv.connection.hostname == null)
	  jv.connection.hostname = DEViseGlobals.DEFAULTHOST;
        if (jv.connection.username == null)
	   jv.connection.username = DEViseGlobals.DEFAULTUSER;
        if (jv.connection.password == null)
	   jv.connection.password = DEViseGlobals.DEFAULTPASS;
        if (jv.connection.cmdport < 1024)
	  jv.connection.cmdport = DEViseGlobals.DEFAULTCMDPORT;

        js frame = new js(jv);
        frame.show();
    }

    private static void checkArguments(String[] args, DEViseJSValues jsValues)
    {
        for (int i = 0; i < args.length; i++) {
            if (args[i].startsWith("-host")) {
                if (!args[i].substring(5).equals("")) {
                    jsValues.connection.hostname = args[i].substring(5);
                }
            } else if (args[i].startsWith("-cmdport")) {
                if (!args[i].substring(8).equals("")) {
                    try {
                        int port = Integer.parseInt(args[i].substring(8));
                        if (port < 1024 || port > 65535) {
                            throw new NumberFormatException();
                        }
                        jsValues.connection.cmdport = port;
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid command port number "
                            + args[i].substring(8) + " in arguments!\n"
                            + "Command port number must larger than 1023"
                            + " and smaller than 65536!\n");
                        System.exit(1);
                    }
                }
            } else if (args[i].startsWith("-bgcolor")) {
                if (!args[i].substring(8).equals("")) {
                    try {
                        String[] str = DEViseGlobals.parseStr(args[i].substring(8), "+");
                        if (str == null || str.length != 3) {
                            throw new NumberFormatException();
                        }

                        int r = Integer.parseInt(str[0]);
                        int g = Integer.parseInt(str[1]);
                        int b = Integer.parseInt(str[2]);

                        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
                            throw new NumberFormatException();
                        }

                        Color c = new Color(r, g, b);
                        jsValues.uiglobals.bg = c;
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid RGB values specified for"
                            + " bgcolor \"" + args[i].substring(8) + "\"!\n"
                            + " Please use format \"R+G+B\" where R,G,B must"
                            + " be non-negative integer and smaller than 256!\n");
                        System.exit(1);
                    }
                }
            } else if (args[i].startsWith("-fgcolor")) {
                if (!args[i].substring(8).equals("")) {
                    try {
                        String[] str = DEViseGlobals.parseStr(args[i].substring(8), "+");
                        if (str == null || str.length != 3) {
                            throw new NumberFormatException();
                        }

                        int r = Integer.parseInt(str[0]);
                        int g = Integer.parseInt(str[1]);
                        int b = Integer.parseInt(str[2]);

                        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
                            throw new NumberFormatException();
                        }

                        Color c = new Color(r, g, b);
                        jsValues.uiglobals.fg = c;
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid RGB values specified for"
                            + " fgcolor \"" + args[i].substring(8) + "\"!\n"
                            + " Please use format \"R+G+B\" where R,G,B must"
                            + " be non-negative integer and smaller than 256!\n");
                        System.exit(1);
                    }
                }
            } else if (args[i].startsWith("-rubberbandlimit")) {
                if (!args[i].substring(16).equals("")) {
                    try {
                        String[] str = DEViseGlobals.parseStr(args[i].substring(16), "x");
                        if (str == null || str.length != 2) {
                            throw new NumberFormatException();
                        }

                        int width = Integer.parseInt(str[0]);
                        int height = Integer.parseInt(str[1]);

                        if (width < 0 || height < 0) {
                            throw new NumberFormatException();
                        }

                        jsValues.uiglobals.rubberBandLimit.width = width;
                        jsValues.uiglobals.rubberBandLimit.height = height;
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid width or height values"
                            + " specified for rubberbandlimit: \""
                            + args[i].substring(16) + "\"!\n"
                            + "Please use format \"WxH\" where W, H must be"
                            + " positive integer!\n");
                        System.exit(1);
                    }
                }
            } else if (args[i].startsWith("-screensize")) {
                if (!args[i].substring(11).equals("")) {
                    try {
                        String[] str = DEViseGlobals.parseStr(args[i].substring(11), "x");
                        if (str == null || str.length != 2) {
                            throw new NumberFormatException();
                        }

                        int width = Integer.parseInt(str[0]);
                        int height = Integer.parseInt(str[1]);

                        if (width < 1 || height < 1) {
                            throw new NumberFormatException();
                        }

                        jsValues.uiglobals.screenSize.width = width;
                        jsValues.uiglobals.screenSize.height = height;
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid width or height values "
                            + "specified for screen size: \""
                            + args[i].substring(11) + "\"!\n"
                            + "Please use format \"WxH\" where W, H must be"
                            + " positive integer!\n");
                        System.out.println(usage);
                        System.exit(1);
                    }
                }
            } else if (args[i].startsWith("-user")) {
                if (!args[i].substring(5).equals("")) {
                    jsValues.connection.username = args[i].substring(5);
                }
            } else if (args[i].startsWith("-pass")) {
                if (!args[i].substring(5).equals("")) {
                    jsValues.connection.password = args[i].substring(5);
                }
            } else if (args[i].startsWith("-session")) {
                if (!args[i].substring(8).equals("")) {
		    jsValues.session.defaultName = args[i].substring(8);
                }
            } else if (args[i].startsWith("-debug")) {
                if (!args[i].substring(6).equals("")) {
                    try {
                        jsValues.debug._debugLevel = Integer.parseInt(args[i].substring(6));
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid debug level \""
                            + args[i].substring(6) + "\" in arguments!\n");
                        System.exit(1);
                    }
                } else {
                    jsValues.debug._debugLevel = 1;
                }
            } else if (args[i].startsWith("-usage")) {
                System.out.println(usage);
                System.exit(0);
            } else if (args[i].startsWith("-log")) {
	        jsValues.debug._logEnabled = true;
            } else if (args[i].startsWith("-usecgi")) {
	        jsValues.connection.cgi = true;
            } else if (args[i].startsWith("-cgiurl")) {
		jsValues.connection.cgiURL = args[i].substring(7);
	    } else if (args[i].startsWith("-clientlog")) {
		jsValues.session.clientLogName = args[i].substring(10);
	    } else if (args[i].startsWith("-autoplayback")) {
		jsValues.session.autoPlayback = true;
	    } else if (args[i].startsWith("-playbackoriginal")) {
		jsValues.session.playbackOriginal = true;
	    } else if (args[i].startsWith("-playbackdisplayoff")) {
		jsValues.session.playbackDisplay = false;
	    } else if (args[i].startsWith("-collableadername")) {
		jsValues.session.collabLeaderName = 
		    args[i].substring(17);
	    } else if (args[i].startsWith("-collableaderpass")) {
		jsValues.session.collabLeaderPass = 
		    args[i].substring(17);
	    } else if (args[i].startsWith("-collabname")) {
		jsValues.session.collabName = 
		    args[i].substring(11);
	    } else if (args[i].startsWith("-collabpass")) {
		jsValues.session.collabPass = 
		    args[i].substring(11);
            } else {
                System.out.println("Invalid js option \"" + args[i]
                    + "\" is given!\n");
                System.out.println(usage);
                System.exit(1);
            }
        }
    }
}
