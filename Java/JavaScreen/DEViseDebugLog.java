// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2000-2001
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class contains methods for logging debug info from the JavaScreen
// client.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.2.4.4  2001/01/05 19:15:45  wenger
// Updated copyright dates.
//
// Revision 1.2.4.3  2001/01/05 17:56:25  wenger
// Minor code cleanups.
//
// Revision 1.2.4.2  2000/11/22 17:43:57  wenger
// Finished cleanup of static variables fix; re-changed CGI command code to
// match the current version of the CGI script.
//
// Revision 1.2.4.1  2000/11/21 01:51:32  xuk
// Change some non-final static variables to non-static. Add a new class, DEViseJSValues, to contain all these variables and attach to every JS, JSA, JSB instance.
//
// Revision 1.2  2000/07/14 21:13:08  wenger
// Speeded up 3D GData processing by a factor of 2-3: improved the parser
// used for GData; eliminated Z sorting for bonds-only 3D views; eliminated
// DEViseAtomTypes for atoms used only to define bond ends; reduced string-
// based processing; eliminated various unused variables, etc.
//
// Revision 1.1  2000/06/26 16:48:32  wenger
// Added client-side JavaScreen debug logging.
//
//

// ------------------------------------------------------------------------

import  java.util.*;
import  java.text.*;
import  java.net.*;
import  java.io.*;

public class DEViseDebugLog
{
    private static final boolean DEBUG = false;
    private DEViseJSValues _jsVals = null;

    DEViseDebugLog(DEViseJSValues jsVals) {
        _jsVals = jsVals;
    }

    void send(String msg)
    {
        if (DEBUG) {
            System.out.println(msg);
        }

	try {
	    Date date = new Date();
	    DateFormat dtf = DateFormat.getDateTimeInstance(DateFormat.MEDIUM,
	      DateFormat.MEDIUM);
    
	    //TEMP -- I'd like to do this as GMT.
	    String stringToLog = URLEncoder.encode("(" + dtf.format(date) +
	      ") " + msg);

	    //TEMP -- eliminate hard-coded machine name.
            URL url = new URL(
	      "http://pumori.cs.wisc.edu/cgi-bin/devise/js_log");
	    URLConnection connection = url.openConnection();
	    connection.setDoOutput(true);

	    PrintWriter out = new PrintWriter(connection.getOutputStream());
    
            out.print("js_id=" + _jsVals.connection.connectionID + "&");
	    out.print("command=" + stringToLog);
	    out.close();

	    // For some reason, the CGI doesn't work right if we don't read
	    // output from it.
	    BufferedReader in = new BufferedReader(
	      new InputStreamReader(connection.getInputStream()));
	    String inputLine;

	    while ((inputLine = in.readLine()) != null) {
		if (!inputLine.equals("Logged")) {
	            System.out.println("Error in command logging CGI: " +
		      inputLine);
		}
	    }
	    in.close(); 
	} catch (Exception e) {
	    System.out.println("Error in log: " + e.getMessage());
	}
    }
}
