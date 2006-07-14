// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2006
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// 3D specific aspects of a DEViseCanvas that are not tied to either
// the Jmol or "plain" 3D implementations.

// ------------------------------------------------------------------------

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.1.2.2  2006/03/31 22:41:14  wenger
// Finished splitting up DEViseCanvas class.
//
// Revision 1.1.2.1  2006/03/30 20:51:25  wenger
// Partially done splitting up the DEViseCanvas class.
//

// ========================================================================

// DEViseCanvas3D.java

//TEMP package edu.wisc.cs.devise.js.jsc;
package JavaScreen;

import  java.awt.*;
import  java.awt.event.*;

public class DEViseCanvas3D extends DEViseCanvas
{
    // v is base view if there is a pile in this canvas.
    public DEViseCanvas3D (DEViseView v, Image img)
    {
	super(v, img);
    }

    protected void doMousePressed()
    {
        // setCursor(DEViseUIGlobals.rbCursor);  - Ven modified
        setCursor(DEViseUIGlobals.hdCursor);

        activeView = view;
        jsc.viewInfo.updateInfo(activeView.viewName,
          activeView.getX(sp.x), activeView.getY(sp.y));
        if (jscreen.getCurrentView() != activeView) {
            jscreen.setCurrentView(activeView);
        }
    }
}