// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1992-1998
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================
//
// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.
//

//
// Description of module.
//

//
// $Id$
//
// $Log$
// Revision 1.4  1998/07/09 17:38:40  hongyu
// *** empty log message ***
//
// Revision 1.3  1998/06/11 15:07:51  wenger
// Added standard header to Java files.
//
//
// ------------------------------------------------------------------------

import java.net.*;
import java.util.*;
import java.io.*;

public class js
{
    private static String usage = new String("usage: java js -host[hostname]"
        + " -cmdport[port] -imgport[port] -user[username] -pass[password] -session[filename]"
        + " -debug[number]");
    // -HOST[hostname]:
    //      hostname: The IP address of the machine where jspop or Devise Server
    //                is running, if bland, use the defaults
    //      default: "localhost"
    // -CMDPORT[port]:
    //      port: The command port, if blank, use the defaults
    //      default: 6666
    // -IMGPORT[port]:
    //      port: The img port, if blank, use the defaults
    //      default: 6688
    // -USER[username]:
    //      username: the name of user, if blank, use the defaults
    //      default: 'guest'
    // -PASS[password]:
    //      password: the password of the user, if blank, use the defaults,
    //                if username if blank, this field has no effect
    //      default: none
    // -SESSION[filename]:
    //      filename: the name of the session file need to be opened
    //      default: none
    // -NONAUTO:
    //      Determine whether or not the js is automatically connect to jspop,
    //      if filename is supplied, this option is automatically set to defaults
    //      default: AUTO
    // -DEBUG[number]:
    //      number: The debug level, no debug information is written if less than or equals to 0
    //      default: No Debug information is written
    //
    private static String hostname = null;
    private static boolean isAutoConnect = true;
    private static String sessionName = null;
    private static String username = null;
    private static String password = null;

    public static void main(String[] args)
    {
        String version = System.getProperty("java.version");
        if (version.compareTo("1.1") < 0)  {
            System.out.println("Error: Java version 1.1 or greater is needed to run this program\n"
                               + "The version you used is " + version);
            System.exit(1);
        }

        // force java VM to run every object's finalizer on normal or abnormal exit
        //System.runFinalizersOnExit(true);

        checkArguments(args);

        YGlobals.YISAPPLET = false;
        YGlobals.YISGUI = true;

        YGlobals.start();

        if (hostname == null)
            hostname = DEViseGlobals.DEFAULTHOST;
        if (username == null)
            username = DEViseGlobals.DEFAULTUSER;
        if (password == null)
            password = DEViseGlobals.DEFAULTPASS;

        if (sessionName != null)
            isAutoConnect = true;

        jsdevisec newClient = new jsdevisec(hostname, username, password, sessionName, null, isAutoConnect);
    }

    private static void checkArguments(String[] args)
    {
        for (int i = 0; i < args.length; i++) {
            if (args[i].startsWith("-host")) {
                if (!args[i].substring(5).equals("")) {
                    hostname = args[i].substring(5);
                }
            } else if (args[i].startsWith("-cmdport")) {
                if (!args[i].substring(8).equals("")) {
                    try {
                        int port = Integer.parseInt(args[i].substring(8));
                        if (port < 1024 || port > 65535) {
                            throw new NumberFormatException();
                        } 
                        DEViseGlobals.CMDPORT = port;
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid command port number " + args[i].substring(8) + " specified in arguments!\n");
                        System.out.println(usage);
                        System.exit(1);
                    }
                }
            } else if (args[i].startsWith("-imgport")) {
                if (!args[i].substring(8).equals("")) {
                    try {
                        int port = Integer.parseInt(args[i].substring(8));
                        if (port < 1024 || port > 65535) {
                            throw new NumberFormatException();
                        } 
                        DEViseGlobals.IMGPORT = port;
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid image port number " + args[i].substring(8) + " specified in arguments!\n");
                        System.out.println(usage);
                        System.exit(1);
                    }
                }
            } else if (args[i].startsWith("-user")) {
                if (!args[i].substring(5).equals("")) {
                    username = args[i].substring(5);
                }
            } else if (args[i].startsWith("-pass")) {
                if (!args[i].substring(5).equals("")) {
                    password = args[i].substring(5);
                }
            } else if (args[i].startsWith("-nonauto")) {
                isAutoConnect = false;
            } else if (args[i].startsWith("-session")) {
                if (!args[i].substring(8).equals("")) {
                    sessionName = args[i].substring(8);
                }
            } else if (args[i].startsWith("-debug")) {
                if (!args[i].substring(6).equals("")) {
                    try {
                        YGlobals.YDEBUG = Integer.parseInt(args[i].substring(6));
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid debug level " + args[i].substring(6) + " specified in arguments!\n");
                        System.out.println(usage);
                        System.exit(1);
                    }
                } else {
                    YGlobals.YDEBUG = 1;
                }
            } else {
                System.out.println("Invalid js option " + args[i] + " is given!\n");
                System.out.println(usage);
                System.exit(1);
            }
        }
    }
}
