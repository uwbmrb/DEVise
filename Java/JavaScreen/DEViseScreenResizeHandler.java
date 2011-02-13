// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2000-2010
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class is used to handle resize events from the JavaScreen
// non-embedded window.  The main reason we have this class is that
// it seems like there's no way to tell from the resize event whether
// the user is still dragging or has released the mouse, so we implement
// a time delay, because we can't deal with the resizes as they come
// while the user drags -- that would be way too slow.  So each time
// we get a resize event, we start a thread that sleeps for a fixed
// delay.  If the sleep is interrupted (by a new resize event) we
// don't do anything; if the delay elapses without an interrupt, we
// go ahead and re-size the visualization.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.2.4.2  2011/02/13 02:43:00  wenger
// Got rid of debug output.
//
// Revision 1.2.4.1  2011/02/09 18:31:44  wenger
// Okay, more test changes -- sleep in DEViseCanvas3DJmol.restoreJmoState()
// seems to fix things, but is not what I want for a "real" fix.
//
// Revision 1.2  2010/07/15 19:01:13  wenger
// Minor updates to the help page, etc., related to resizing.
//
// Revision 1.1  2010/07/01 17:32:59  wenger
// Implemented JavaScreen to-do 09.019 -- JS window can now be re-sized
// while a session is open, added new view menu options to enlarge and
// reduce by a fixed amount.
//

// ========================================================================

//TEMP package edu.wisc.cs.devise.js.jsc;
package JavaScreen;

public class DEViseScreenResizeHandler implements Runnable
{
    private jsdevisec _jsc = null;
    private Thread _thread = null;

    // Delay between when we get a resize event and when we actually
    // do the resize.
    private static final int DELAY = 1 * 1000; // 1 second

    private static final int DEBUG = 0; // 0-2

    //---------------------------------------------------------------------
    // Constructor
    public DEViseScreenResizeHandler(jsdevisec jsc)
    {
        _jsc = jsc;
    }

    //---------------------------------------------------------------------
    // Called when we get a resize event on the jsdevisec object.
    public void handleResize()
    {
	if (DEBUG >= 2) {
            System.out.println("DEViseScreenResizeHandler.handleResize()");
            _jsc.pn("DEViseScreenResizeHandler.handleResize()");
	}

	if (_thread != null) {
	    _thread.interrupt();
	}
	_thread = new Thread(this);
	_thread.setName("resize handler thread");
	_thread.start();
    }

    //---------------------------------------------------------------------
    // Run method for the thread to call.
    public void run()
    {
	if (DEBUG >= 2) {
        System.out.println("DEViseScreenResizeHandler.run()");
	}
        try {
	    Thread.sleep(DELAY);
	} catch (InterruptedException ex) {
	    if (DEBUG >= 2) {
	        System.out.println("DEViseScreenResizeHandler.run " +
		  "sleep interrupted");
	    }
	    return;
	}

	if (DEBUG >= 1) {
	    System.out.println("DEViseScreenResizeHandler.run doing resize");
	}

	// Since this is not triggered directly by the main GUI thread,
	// we wait here if the user has triggered a different command
	// while this thread has been sleeping.
	_jsc.dispatcher.waitForCmds();

	int width = _jsc.jscreen.getWidth();
	int height = _jsc.jscreen.getHeight();
	_jsc.jscreen.setScreenDim(width, height);
    }
}
