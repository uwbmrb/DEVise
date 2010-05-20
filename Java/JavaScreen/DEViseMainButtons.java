// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2003-2009
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// Create the buttons and associated menus for the main JavaScreen window.
// I'm switching to menus for most things so that we don't have so darn
// many buttons; I moved the code into this new class because there's
// so much stuff in jsdevisec already.  Kent Wenger (wenger) 2003-12-03.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.14  2009/09/10 22:06:39  wenger
// Fixed JavaScreen bug 985 (change 'Reset Filters' to 'Reset Axis Ranges');
// made other menu improvements; changed communication mode dialog to
// menu for simplification.
//
// Revision 1.13  2008/02/20 20:22:10  wenger
// JavaScreen now defaults to showing help in browser window (to
// get around problems on Mac with the Java window); added links
// and images to the help page because of this change.
//
// Revision 1.12  2008/02/08 21:03:12  wenger
// Changed version from 5.8.3 to 5.9.0 because the toolbar and associated
// stuff is such a big change; added JavaScreen help dialog (although the
// text is not yet complete, and some is commented out until I get html
// links to work in that dialog); added (currently disabled) menu item to
// show JS version history.
//
// Revision 1.11  2008/01/24 20:30:53  wenger
// Merged js_ie_fix_br_0 thru js_ie_fix_br_1 to the trunk.
//
// Revision 1.10  2008/01/22 20:02:38  wenger
// Fixed bug 954 (JavaScreen locks up IE for Miron); I tried backporting
// my fix to the pre-toolbar version of the JS, but it doesn't work for
// some reason (I suspect that some of the other cleanups since then
// also affect the fix).  Note that this commit has a bunch of temporary
// code still in place; I want to get a working version into CVS ASAP.
//
// Revision 1.9  2008/01/11 17:03:26  wenger
// Removed unnecessary swing import.
//
// Revision 1.8  2007/12/19 00:08:32  wenger
// Changed a bunch of JButton references to DEViseButtons to make things
// more consistent.
//
// Revision 1.7  2007/08/27 20:53:45  wenger
// Made separate menu items for showing and hiding view help, as requested
// by Chris Schulte.
//
// Revision 1.6  2007/08/27 19:16:39  wenger
// Merged andyd_gui_br_7 thru andyd_gui_br_8 to trunk.
//
// Revision 1.5  2007/04/20 19:42:35  wenger
// Merged andyd_gui_br_2 thru andyd_gui_br_5 to the trunk.
// merged-andyd_gui_br_2-thru-andyd_gui_br_5-to-trunk
//
// Revision 1.4.2.2  2007/08/24 16:51:42  wenger
// Removed elipses from "View Help" menu item; renamed "Toggle visual
// filter" tooltip to "Toggle axis ranges" (hopefully clearer).
//
// Revision 1.4.2.1  2007/03/16 17:12:46  adayton
// Add UI package
//
// Revision 1.4  2006/06/23 19:52:41  wenger
// Merged devise_jmol_br_1 thru devise_jmol_br_2 to the trunk.
//
// Revision 1.3  2006/05/26 16:22:16  wenger
// Merged devise_jmol_br_0 thru devise_jmol_br_1 to the trunk.
//
// Revision 1.2.4.2  2006/06/14 16:32:02  wenger
// Added new DEViseButton class to force the colors and font we want
// for buttons; cleaned up things in jsdevisec (made public members
// private, etc.); started on getting more of the Jmol menus actually
// working.
//
// Revision 1.2.4.1  2006/05/23 18:17:50  wenger
// Added initial Jmol menu with a menu item to show the tree selection
// window; destroying and re-creating the window currently doesn't
// preserve the existing selection, although I started on provision for
// that.
//
// Revision 1.2  2005/12/06 20:00:19  wenger
// Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
// be the end of the V1_7b0_br branch.)
//
// Revision 1.1.2.2  2003/12/22 22:47:15  wenger
// JavaScreen support for print color modes is now in place.
//
// Revision 1.1.2.1  2003/12/03 19:31:09  wenger
// Changed most buttons in the JavaScreen GUI to menus (to save space
// in preparation for adding new functionality).
//

// ------------------------------------------------------------------------

//TEMP package edu.wisc.cs.devise.js;
package JavaScreen;

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import JavaScreen.UI.*;

public class DEViseMainButtons
{
    //===================================================================
    // VARIABLES

    private static int DEBUG = 0;

    public static int MENU_X_OFFSET = 10;
    public static int MENU_Y_OFFSET = 10;

    private jsdevisec _js = null;
    
    private Component[] _buttons = null;

    // DEViseButton that bring up menus.
    private DEViseButton sessionMenuButton;
    //TEMP private DEViseButton sessionMenuButton = new DEViseButton("Cursor Mode");
    private DEViseButton viewMenuButton;
    private DEViseButton helpMenuButton;

    // Menus.
    private PopupMenu sessionPM = new PopupMenu();
    //TEMP private PopupMenu cursorModePM = new PopupMenu();
    private PopupMenu viewPM = new PopupMenu();
    private PopupMenu helpPM = new PopupMenu();
    private Menu displayModeMenu = new PopupMenu("Display Mode");
    private Menu commModeMenu = new PopupMenu("Communication Mode");

    // DEViseButton that don't bring up menus.
    public  DEViseButton stopButton;

    // Menu items.
    private MenuItem openMenuItem = new MenuItem("Open/Switch...");
    private MenuItem closeMenuItem = new MenuItem("Close");
    private MenuItem restartMenuItem = new MenuItem("Restart");
    private MenuItem filterMenuItem = new MenuItem("Reset Axis Ranges");
    private MenuItem exitMenuItem = new MenuItem("Exit");

    private MenuItem normalDisplayMenuItem = new MenuItem("Normal");
    private MenuItem colorPrintDisplayMenuItem = new MenuItem("Color print");
    private MenuItem bwPrintDisplayMenuItem = new MenuItem("B/w print");

    private MenuItem setMenuItem = new MenuItem("Settings...");

    private MenuItem socketModeMenuItem = new MenuItem("Socket");
    private MenuItem cgiModeMenuItem = new MenuItem("CGI...");

    private MenuItem collabMenuItem = new MenuItem("Collaborate...");
    private MenuItem playbackMenuItem = new MenuItem("Playback...");

    public static final String displayLogStr = "Show Log...";
    public static final String closeLogStr = "Hide Log";
    private MenuItem logMenuItem = new MenuItem(displayLogStr);

    private MenuItem showViewHelpMenuItem = new MenuItem("Show View Help");
    private MenuItem hideViewHelpMenuItem = new MenuItem("Hide View Help");
    private MenuItem aboutMenuItem = new MenuItem("About JavaScreen...");
    private MenuItem versionHistMenuItem = new MenuItem(
      "JavaScreen version history...");

    private MenuItem jsHelpBrowserMenuItem = new MenuItem(
      "JavaScreen Help (in browser window)...");
    private MenuItem jsHelpInternalMenuItem = new MenuItem(
      "JavaScreen Help (in Java window)...");

    // Dialogs
    private DEViseHtmlWindow helpWindow;

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    /**
     * Constructor.
     * @param The jsdevisec object this object will be associated with.
     */
    public DEViseMainButtons(jsdevisec js)
    {
        if (DEBUG >= 1) {
	    System.out.println("DEViseMainButtons.DEViseMainButtons()");
	}

	_js = js;

        createButtons();
	addActions();
    }

    //-------------------------------------------------------------------
    /**
     * Get an array containing the buttons created in this object.
     * @return An array of Components (the buttons).
     */
    public Component[] getButtons()
    {
        if (DEBUG >= 1) {
	    System.out.println("DEViseMainButtons.getButtons()");
	}

	return _buttons;
    }

    //-------------------------------------------------------------------
    /**
     * Get the stop button (this is kind of a kludgey way to allow other
     * parts of the code to change its color).
     * @return The stop button.
     */
    public DEViseButton getStopButton()
    {
        if (DEBUG >= 1) {
	    System.out.println("DEViseMainButtons.getStopButton()");
	}

	return stopButton;
    }

    //===================================================================
    // PRIVATE METHODS

    //-------------------------------------------------------------------
    /**
     * Create the buttons.
     */
    private void createButtons()
    {
        if (DEBUG >= 2) {
	    System.out.println("DEViseMainButtons.createButtons()");
	}

        sessionMenuButton = new DEViseButton("Session", _js.jsValues);
        viewMenuButton = new DEViseButton("View", _js.jsValues);
        helpMenuButton = new DEViseButton("Help", _js.jsValues);
        stopButton = new DEViseButton("Stop", _js.jsValues);

        _buttons = new Component[4];
        _buttons[0] = sessionMenuButton;
        _buttons[1] = viewMenuButton;
        _buttons[2] = stopButton;
        _buttons[3] = helpMenuButton;

	// Set up session menu.
        if (!_js.jsValues.uiglobals.inBrowser) {
	    sessionPM.add(openMenuItem);
	    sessionPM.add(closeMenuItem);
	}
	sessionPM.add(restartMenuItem);
	sessionPM.add(filterMenuItem);
        if (!_js.jsValues.uiglobals.inBrowser) {
	    sessionPM.add(exitMenuItem);
	}
	sessionMenuButton.add(sessionPM);

	// Set up display mode menu.
	displayModeMenu.add(normalDisplayMenuItem);
	displayModeMenu.add(colorPrintDisplayMenuItem);
	displayModeMenu.add(bwPrintDisplayMenuItem);

	// Set up communication mode menu.
	commModeMenu.add(socketModeMenuItem);
	commModeMenu.add(cgiModeMenuItem);

	// Set up view menu.
	viewPM.add(displayModeMenu);
	viewPM.add(setMenuItem);
	viewPM.add(commModeMenu);
	viewPM.add(collabMenuItem);
	viewPM.add(playbackMenuItem);
	viewPM.add(logMenuItem);
	viewMenuButton.add(viewPM);

	// Set up help menu.
	helpPM.add(jsHelpBrowserMenuItem);
	helpPM.add(showViewHelpMenuItem);
	helpPM.add(hideViewHelpMenuItem);
	//TEMP helpPM.add(aboutMenuItem);
	//TEMP helpPM.add(versionHistMenuItem);
	helpPM.add(jsHelpInternalMenuItem);
	helpMenuButton.add(helpPM);
	if (_js._parentApplet == null) {
            jsHelpBrowserMenuItem.setEnabled(false);
        }
    }

    //-------------------------------------------------------------------
    /**
     * Add action listeners to the buttons and menu items.
     */
    private void addActions()
    {
        if (DEBUG >= 2) {
	    System.out.println("DEViseMainButtons.addActions()");
	}

        sessionMenuButton.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
			sessionPM.show(sessionMenuButton, MENU_X_OFFSET,
			  MENU_Y_OFFSET);
                }
            });

        viewMenuButton.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
			viewPM.show(viewMenuButton, MENU_X_OFFSET,
			  MENU_Y_OFFSET);
                }
            });

        helpMenuButton.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
			helpPM.show(helpMenuButton, MENU_X_OFFSET,
			  MENU_Y_OFFSET);
                }
            });

        openMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.getSessionList();
                }
            });

        closeMenuItem.addActionListener(new ActionListener()
	    {
	        public void actionPerformed(ActionEvent event)
	        {
	            _js.closeSession();
	        }
	    });


        restartMenuItem.addActionListener(new ActionListener()
	    {
	        public void actionPerformed(ActionEvent event)
	        {
	            _js.restartSession();
	        }
	    });

        filterMenuItem.addActionListener(new ActionListener()
	    {
	        public void actionPerformed(ActionEvent event)
	        {
		    _js.resetFilters();
	        }
            });

        exitMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    _js.checkQuit();
                }
            });

        normalDisplayMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.setDisplayMode(0);
                }
            });

        colorPrintDisplayMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.setDisplayMode(1);
                }
            });

        bwPrintDisplayMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.setDisplayMode(2);
                }
            });

        socketModeMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.jsValues.connection.cgi = false;
		    _js.socketMode();

                }
            });

        cgiModeMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.jsValues.connection.cgi = true;
		    _js.cgiMode();
		    _js.setCgiUrl();
                }
            });

        setMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    _js.showSetting();
                }
            });

        collabMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.showCollab();
                }
            });	

        playbackMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.setLogFile();
                }
            });	

        logMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.setLog(logMenuItem);
                }
            });

        stopButton.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
	            _js.stopCommand();
                }
            });

        jsHelpBrowserMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.showHelpInBrowser();
                }
            });

        jsHelpInternalMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    String htmlText = DEViseHtmlWindow.getTextFromFile(
		      _js.jsValues, DEViseGlobals.JS_HELP_URL);
		    helpWindow = new DEViseHtmlWindow(
		      "DEVise JavaScreen help", htmlText);
                }
            });

        showViewHelpMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.showViewHelp();
                }
            });

        hideViewHelpMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    _js.hideViewHelp();
                }
            });

        aboutMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    System.out.println("DIAG about");//TEMP
                }
            });

        versionHistMenuItem.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
		    System.out.println("DIAG version history");//TEMP
                }
            });
    }
}

// ========================================================================
