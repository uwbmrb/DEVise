// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2001
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class checks whether other threads may be hung, and reports
// a warning if so.

// This class maintains the state for each client (JavaScreen).  It is
// also used to read commands from the client, and send commands and
// data to the client.

// There is one instance of this class for a JSPoP.

// ------------------------------------------------------------------------

// $Id$

// $Log$

// ========================================================================

// DEViseThreadChecker.java

import  java.util.*;

public class DEViseThreadChecker implements Runnable
{
    private static final int DEBUG = 0;
    private static final int CHECK_INTERVAL = 10 * 1000; // millisec
    private static final int HUNG_INTERVAL = 60 * 1000; // millisec

    private Thread _thread = null;

    private Vector _threadList = null;

    private static DEViseThreadChecker _instance = null;

    public static DEViseThreadChecker getInstance()
    {
        return _instance;
    }

    public DEViseThreadChecker()
    {
	_instance = this;

	_threadList = new Vector();

        _thread = new Thread(this);
	_thread.start();
    }

    public void register(DEViseCheckableThread thread)
    {
        if (DEBUG >= 1) {
	    System.out.println("DEViseThreadChecker.register(" +
	      thread + ")");
	}
        _threadList.addElement(thread);
    }

    public void unregister(DEViseCheckableThread thread)
    {
        _threadList.removeElement(thread);
    }

    public void run()
    {
        while (true) {
            try {
	        Thread.sleep(CHECK_INTERVAL);
	    } catch (InterruptedException ex) {
	    }

            if (DEBUG >= 1) {
	        System.out.println("Checking threads");
	    }

	    Date date = new Date();
	    long currentTime = date.getTime();

	    for (int index = 0; index < _threadList.size(); index++) {
	        DEViseCheckableThread thread = (DEViseCheckableThread)
		  _threadList.elementAt(index);
	        long lastRun = thread.lastRunTime();
		if (currentTime - lastRun > HUNG_INTERVAL) {
		    System.err.println(thread + " may be hung");
		    //TEMP -- force a stack track of the thread if possible
		    thread.intThread();
		}
	    }
	}
    }
}
