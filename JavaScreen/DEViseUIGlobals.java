// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2007
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class contains GUI-related constants and utility functions.
// It was split out from DEViseGlobals.java so that the jspop wouldn't
// need an X server to run.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.12.38.2  2007/07/25 18:25:17  wenger
// Moved cursor handling from DEViseUIGlobals to the new
// UI/DEViseMouseCursor class, in preparation for changing the cursor
// according to the toolbar mode.
//
// Revision 1.12.38.1  2007/07/24 21:50:28  wenger
// We now create (but don't use yet) mouse cursors corresponding to the
// various toolbar states.
//
// Revision 1.12  2001/05/11 20:36:09  wenger
// Set up a package for the JavaScreen code.
//
// Revision 1.11  2001/01/08 20:31:53  wenger
// Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
// back onto the trunk.
//
// Revision 1.10.4.3  2000/11/22 17:43:59  wenger
// Finished cleanup of static variables fix; re-changed CGI command code to
// match the current version of the CGI script.
//
// Revision 1.10.4.2  2000/11/21 01:51:33  xuk
// Change some non-final static variables to non-static. Add a new class, DEViseJSValues, to contain all these variables and attach to every JS, JSA, JSB instance.
//
// Revision 1.10.4.1  2000/11/16 17:30:52  wenger
// Made static variables into static final variables.
//
// Revision 1.10  2000/07/26 15:53:49  venkatan
// Hand - Mouse Cursor is used in the 3D view
//
// Revision 1.9  2000/07/19 20:11:38  wenger
// Code to read data from sockets is more robust (hopefully fixes BMRB/Linux
// problem); background color of upper left part of JS changed to red when a
// dialog is shown; more debug output added.
//
// Revision 1.8  2000/06/26 18:52:00  wenger
// Added class explanation in header.
//
// Revision 1.7  2000/06/22 20:51:25  wenger
// Changed colors and font in drill-down dialog to make text more
// readable.
//
// Revision 1.6  2000/05/24 14:07:10  wenger
// Cleaned up and commented 3D-related classes (DEViseCrystal, DEViseAtomType,
// DEViseAtomInCrystal, DEVise3DLCS).
//
// Revision 1.5  2000/05/22 17:52:50  wenger
// JavaScreen handles fonts much more efficiently to avoid the problems with
// GData text being drawn very slowly on Intel platforms.
//
// Revision 1.4  2000/05/11 20:59:50  wenger
// More comments.
//
// Revision 1.3  2000/05/11 20:19:33  wenger
// Cleaned up jsdevisec.java and added comments; eliminated
// jsdevisec.lastCursor (not really needed).
//
// Revision 1.2  2000/05/04 17:40:28  wenger
// Added new text object feature: GData Z value specifies max size of
// font in points (if > 1).  (Allows me to fix problems with BMRB 4096
// protein session.)
//
// Revision 1.1  2000/04/24 20:22:01  hongyu
// remove UI dependency of jspop and js
//

// This class contains a number of constants and utility functions.
// Note: all members are static.

// ------------------------------------------------------------------------

//TEMP package edu.wisc.cs.devise.js.jsc;
package JavaScreen;

import java.util.*;
import java.awt.*;
import java.applet.*;

public final class DEViseUIGlobals
{
    // global variables
    public static final String javaScreenTitle =
      "DEVise JavaScreen -- Version " + DEViseGlobals.VERSION;

    public static final int COLOR_MIN = 0; // min. integer RGB value
    public static final int COLOR_MAX = 255; // max. integer RGB value

    // DEVise font name
    public static final String[] DEViseFont = {"Monospaced", "Serif",
      "SanSerif"};

    public static Color convertColor(String str)
    {
        if (str == null || str.length() != 13 || !str.startsWith("#")) {
            return null;
        }

        String red = str.substring(1, 3), green = str.substring(5, 7), blue = str.substring(9, 11);
        try {
            int r = (Integer.valueOf(red, 16)).intValue(), g = (Integer.valueOf(green, 16)).intValue(), b = (Integer.valueOf(blue, 16)).intValue();
            Color color = new Color(r, g, b);
            return color;
        } catch (NumberFormatException e) {
            return null;
        }
    }

    // size = size in points
    // ff = font family (0 = "Monospaced", 1 = "Serif", 2 = "SanSerif")
    // fw = font weight (0 = plain, 1 = bold)
    // fs = font style (0 = plain, 1 = italic)
    public static Font getFont(int size, int ff, int fw, int fs)
    {
        return DEViseFonts.getFont(size, ff, fw, fs);
    }

    // Return a font that fits the given string within the given height
    // (specified in pixels).
    // ff = font family (0 = "Monospaced", 1 = "Serif", 2 = "SanSerif")
    // fw = font weight (0 = plain, 1 = bold)
    // fs = font style (0 = plain, 1 = italic)
    public static Font getFont(String str, int height, int ff, int fw, int fs, int maxPointSize)
    {
        return getFont(str, -1, height, ff, fw, fs, maxPointSize);
    }

    // Return a font that fits the given string within the given width and
    // height (specified in pixels).
    // ff = font family (0 = "Monospaced", 1 = "Serif", 2 = "SanSerif")
    // fw = font weight (0 = plain, 1 = bold)
    // fs = font style (0 = plain, 1 = italic)
    public static Font getFont(String str, int width, int height, int ff, int fw, int fs, int maxPointSize)
    {
        if (str == null || str.length() == 0 || height < 1) {
            return null;
        }

        boolean checkWidth = true;
        if (width < 0) {
            checkWidth = false;
        }

        // as of right now, I only recognize Courier (Monospaced), Times
    // (Serif) and Helvetica (SansSerif).
        // Default is Courier.
        if (ff < 0 || ff >= DEViseFont.length) {
            ff = 1;
        }

        int minSize = 1, maxSize = 100, fontSize = 12;
    Font okFont = null;

    if (maxPointSize > 1) maxSize = maxPointSize;
    if (fontSize > maxSize) fontSize = maxSize;

        int fontstyle = ((fw == 0)?Font.PLAIN:Font.BOLD) +
      ((fs == 0)?Font.PLAIN:Font.ITALIC);

        Toolkit tk = Toolkit.getDefaultToolkit();
    Font font = DEViseFonts.getFont(fontSize, ff, fw, fs);
        FontMetrics fm = tk.getFontMetrics(font);
        int h = fm.getHeight(), w = fm.stringWidth(str);

        if (h > height || (checkWidth && w > width)) {
        // First guess is too big.

            while (fontSize > minSize) {
                fontSize--;
        font = DEViseFonts.getFont(fontSize, ff, fw, fs);
                if (font == null) {
                    continue;
                }

                fm = tk.getFontMetrics(font);
                h = fm.getHeight();
                if (h < height) {
                    if (checkWidth) {
                        w = fm.stringWidth(str);
                        if (w < width) {
                // Current font is small enough.
                okFont = font;
                            break;
                        }
                    } else {
            // Current font is small enough.
            okFont = font;
                        break;
                    }
                }
            }
        } else {
        // First guess is not too big.

        okFont = font;

            while (fontSize < maxSize) {
                fontSize++;
        font = DEViseFonts.getFont(fontSize, ff, fw, fs);
                if (font == null) {
                    continue;
                }

                fm = tk.getFontMetrics(font);
                h = fm.getHeight();

                if (h > height) {
            // Current font is too big.
                    break;
                } else {
                    if (checkWidth) {
                        w = fm.stringWidth(str);
                        if (w > width) {
                // Current font is too big.
                            break;
                        }
                    }

            okFont = font;
                }
            }
        }

    return okFont;
    }
}
