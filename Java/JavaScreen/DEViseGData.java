// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2011
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// There is once instance of this class for each GData record the
// JavaScreen is handling.

// An object in this class corresponds to a "decoded" GData record
// -- in other words, the values from the GData record have been pulled
// out and  put in the object according to the object type.

// Note: this is pretty bad design -- there really should be a subclass
// for each type of symbol, instead of this one class with a bunch of
// members that only apply to some symbol types.  However, I don't want
// to deal with that right now.  wenger 2006-02-21.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.43  2011/08/26 15:37:34  wenger
// Merged js_button_fix_br_0 thru js_button_fix_br_1 to trunk.
//
// Revision 1.42.8.12  2011/10/05 23:44:51  wenger
// Early version of "session-specific" menu working -- only works for
// showing URLs at this point.
//
// Revision 1.42.8.11  2011/09/29 17:55:16  wenger
// We now actually create embedded buttons in DEViseScreen instead of
// in DEViseGData, so that they're created by the event queue thread instead
// of a command thread (this didn't actually solve the Mac Jmol/button
// lockup problem, but it seems safer).  Also changed the DEViseCanvas
// class to extend JComponent rather than Container, in case this works
// better for adding JButtons to it.
//
// Revision 1.42.8.10  2011/09/27 20:27:48  wenger
// The movie generation dialog is mostly in place -- the layout needs to
// be fixed.
//
// Revision 1.42.8.9  2011/08/25 21:35:53  wenger
// Hopefully final cleanup of the JavaScreen embedded button fixes.
//
// Revision 1.42.8.8  2011/08/16 22:37:31  wenger
// JS client now has special code to append residue number to URL for
// BMRB dynamics video generation.
//
// Revision 1.42.8.7  2011/08/15 18:51:15  wenger
// Fixed a problem with "obsolete" buttons not getting removed correctly;
// cleaned up a few other things.
//
// Revision 1.42.8.6  2011/06/08 21:19:35  wenger
// We no longer change the mouse cursor to the disabled cursor in a
// view with a button in "standard" toolbar mode.
//
// Revision 1.42.8.5  2011/06/07 18:00:57  wenger
// More cleanup of no-longer-used code (including some test code I added
// temporarily).
//
// Revision 1.42.8.4  2011/06/06 21:50:11  wenger
// Cleaned up the code that actually displays a URL when an embedded button
// is clicked.
//
// Revision 1.42.8.3  2011/06/06 21:01:09  wenger
// Okay, I think I pretty much have things working -- done by adding the
// buttons to the appropriate *DEViseCanvas*, rather than directly to
// the DEViseScreen -- keeps the buttons on top.
//
// Revision 1.42.8.2  2011/06/03 23:21:28  wenger
// Cleaned up some of the junk that was just commented out previously.
//
// Revision 1.42.8.1  2011/06/03 23:10:51  wenger
// Working on getting embedded buttons in the JS working again -- big
// change so far is getting rid of the paint() method in DEViseScreen
// -- I think it was an error that that ever existed.  Lots of test/debug
// code in place right now as I play around with getting buttons to work.
//
// Revision 1.42  2010/04/21 17:10:10  wenger
// Merged devise_dist_rest_1003_br_0 thru devise_dist_rest_1003_br_1 to trunk.
//
// Revision 1.41.8.3  2010/04/19 16:15:01  wenger
// Changed the JavaScreen slightly to get coloring of ambiguous restraints
// working correctly.
//
// Revision 1.41.8.2  2010/04/05 20:24:43  wenger
// Got coloring of restraints working (at least for violated/non-violated;
// I haven't tested ambiguous/non-ambiguous yet).
//
// Revision 1.41.8.1  2010/04/01 21:03:44  wenger
// Woo hoo!  Display of restraints is partly working!  (We're not yet
// differentiating violated vs. non-violated, ambiguous vs. non-
// ambiguous; and the code needs lots of checking and cleanup.)
//
// Revision 1.41  2008/09/03 19:15:59  wenger
// Initial changes to JavaScreen client to support entity assembly
// IDs in 3D Jmol visualizations.  (Still needs some cleanup.)
//
// Revision 1.40  2006/05/26 16:22:15  wenger
// Merged devise_jmol_br_0 thru devise_jmol_br_1 to the trunk.
//
// Revision 1.39.36.3  2006/05/18 20:49:00  wenger
// Added backbone/side chains/protons selection tree.
//
// Revision 1.39.36.2  2006/02/23 22:08:39  wenger
// Added flag for whether or not 3D views should use Jmol.
//
// Revision 1.39.36.1  2006/02/23 16:57:42  wenger
// Cleaned up JavaScreen code that sends data to Jmol, including
// adding new DEViseJmolData class.
//
// Revision 1.39  2001/05/11 20:36:06  wenger
// Set up a package for the JavaScreen code.
//
// Revision 1.38  2001/05/07 21:53:25  wenger
// Found and fixed bug 670; jss checks for /tmp.X1-lock before starting
// Xvfb.
//
// Revision 1.37  2001/01/08 20:31:51  wenger
// Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
// back onto the trunk.
//
// Revision 1.36.4.2  2000/11/22 17:43:57  wenger
// Finished cleanup of static variables fix; re-changed CGI command code to
// match the current version of the CGI script.
//
// Revision 1.36.4.1  2000/11/21 01:51:32  xuk
// Change some non-final static variables to non-static. Add a new class, DEViseJSValues, to contain all these variables and attach to every JS, JSA, JSB instance.
//
// Revision 1.36  2000/07/20 15:42:59  wenger
// Fixed bug 603 (GData errors caused by problems in new parser); eliminated
// old parser.
//
// Revision 1.35  2000/07/14 21:13:08  wenger
// Speeded up 3D GData processing by a factor of 2-3: improved the parser
// used for GData; eliminated Z sorting for bonds-only 3D views; eliminated
// DEViseAtomTypes for atoms used only to define bond ends; reduced string-
// based processing; eliminated various unused variables, etc.
//
// Revision 1.34  2000/05/22 17:52:49  wenger
// JavaScreen handles fonts much more efficiently to avoid the problems with
// GData text being drawn very slowly on Intel platforms.
//
// Revision 1.33  2000/05/04 17:40:28  wenger
// Added new text object feature: GData Z value specifies max size of
// font in points (if > 1).  (Allows me to fix problems with BMRB 4096
// protein session.)
//
// Revision 1.32  2000/04/24 20:22:00  hongyu
// remove UI dependency of jspop and js
//
// Revision 1.31  2000/04/07 22:43:13  wenger
// Improved shading of atoms (it now works on white atoms); added comments
// based on meeting with Hongyu on 2000-04-06.
//
// Revision 1.30  2000/04/05 15:42:23  wenger
// Changed JavaScreen version to 3.3 because of memory fixes; other minor
// improvements in code; conditionaled out some debug code.
//
// Revision 1.29  2000/04/05 06:25:39  hongyu
// fix excessive memory usage problem associated with gdata
//
// Revision 1.28  2000/04/03 22:24:53  wenger
// Added named constants for GData symbol types; 3D GData symbols are now
// differentiated by symbol type instead of string; removed some commented-
// out code.
//
// Revision 1.27  2000/03/31 19:29:16  wenger
// Changed code so that views and GData objects get garbage collected when
// a session is closed; added debug code for tracking construction and
// finalization of DEViseView and DEViseGData objects; other minor GData-
// related improvements.
//
// Revision 1.26  2000/03/23 16:26:14  wenger
// Cleaned up headers and added requests for comments.
//
// Revision 1.25  2000/01/12 14:37:48  hongyu
// *** empty log message ***
//
// Revision 1.24  1999/11/03 15:29:44  wenger
// Fixed text alignment problems.
//
// Revision 1.23  1999/11/03 08:00:49  hongyu
// *** empty log message ***
//
// Revision 1.22  1999/11/02 21:37:39  wenger
// Made separate methods for constructing the different symbol types, without
// really changing the functionality, to clean things up and make fixes to
// text alignment, etc., easier to do.
//
// Revision 1.21  1999/10/28 17:48:46  wenger
// Fixed various JavaScreen/devised bugs (incorrect location of GData symbols
// in JS; incorrect location of child views; extra destroys of child GData
// views).
//
// Revision 1.20  1999/10/10 08:49:52  hongyu
// Major changes to JAVAScreen have been commited in this update, including:
// 1. restructure of JavaScreen internal structure to adapt to vast changes
//    in DEVise and also prepare to future upgrade
// 2. Fix a number of bugs in visualization and user interaction
// 3. Add a number of new features in visualization and user interaction
// 4. Add support for complicated 3D molecular view
//
// Revision 1.19  1999/09/24 17:11:47  hongyu
// adding support for 3-d molecule view
//
// Revision 1.18  1999/08/19 07:21:06  hongyu
// *** empty log message ***
//
// Revision 1.17  1999/08/17 06:15:16  hongyu
// *** empty log message ***
//
// Revision 1.16  1999/08/03 05:56:49  hongyu
// bug fixes    by Hongyu Yao
//
// Revision 1.14  1999/07/27 17:11:18  hongyu
// *** empty log message ***
//
// Revision 1.12  1999/06/23 20:59:16  wenger
// Added standard DEVise header.
//

// ========================================================================

// DEViseGData.java

//TEMP package edu.wisc.cs.devise.js.jsc;
package JavaScreen;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.net.*;

public class DEViseGData
{
    public jsdevisec jsc = null; //TEMP -- do we really need this for *every* GData record???
    public DEViseView parentView = null;

    public Rectangle GDataLoc = null;

    //TEMP -- why do we need x, y, etc, *and* GDataLoc
    // x, y, z are x0, y0, z0 converted from data units to pixels.
    public int x = 0, y = 0, z = 0, width = 0, height = 0;
    // x0, y0, z0 are the values in the GData (data units).
    public float x0, y0, z0, x1, y1, z1;

    //public String[] data = null;
    public Component symbol = null;
    public boolean isJavaSymbol = false;
    public String _buttonLabel;
    public String _buttonCmd;
    public String _menuType;
    public String _menuName;
    public int symbolType = 0;

    // Note: I should probably make subclasses of DEViseGData...

    // Values for symbolType.
    public static final int _symOval = 4;
    public static final int _symSegment = 7;
    public static final int _symText = 12;
    public static final int _symEmbeddedTk = 15;
    public static final int _symFixedText = 16;

    public String string = null;
    public Color color = null;
    public Font font = null;
    public int outline = 0;

    // Values for Jmol atoms
    public int atomNum;
    public String atomName;
    public String residueLabel; // amino acid
    public int entityAssemblyID;
    public int residueNum;
    public String atomType;
    public String structType;
    public String atomId;

    // Distance restraint values for Jmol
    public String atom1Id;
    public String atom2Id;
    public boolean isViolated;
    public boolean isAmbiguous;

    private static final boolean _debug = false;

    // GData format: <x> <y> <z> <color> <size> <pattern> <orientation>
    // <symbol type> <shape attr 0> ... <shape attr 14>
    // xm is x multiplier (GData to pixel conversion)
    // xo is x offset (GData to pixel conversion)
    // ym is y multiplier (GData to pixel conversion)
    // yo is y offset (GData to pixel conversion)
    public DEViseGData(jsdevisec panel, DEViseView view, String gdata, float xm,
      float xo, float ym, float yo) throws YException
    {
        jsc = panel;

	jsc.jsValues.gdata._gdCount++;
	if (_debug) {
            System.out.println("DEViseGData constructor " +
	      jsc.jsValues.gdata._gdCount + "(" + gdata + ")");
            System.out.println("Free memory: " +
	      Runtime.getRuntime().freeMemory() + "/" +
	      Runtime.getRuntime().totalMemory());
	}

        parentView = view;
        if (parentView == null) {
            throw new YException("Invalid parent view for GData!");
        }

        String[] data = DEViseGlobals.parseString(gdata, '{', '}', false);
	if (_debug) {
            System.out.println("GData string = <" + gdata + ">");
	    System.out.print("Parsed GData: ");
	    for (int index = 0; index < data.length; index++) {
	        System.out.print("<" + data[index] + "> ");
	    }
	    System.out.println("");
	}
        if (data == null || data.length != 23) {
            throw new YException("Invalid GData: {" + gdata + "}");
	}
        gdata = null;

        float size = 0;
        try {
	    // ADD COMMENT about conversion here
            x0 = (Float.valueOf(data[0])).floatValue();
            x = (int)(x0 * xm + xo);
            y0 = (Float.valueOf(data[1])).floatValue();
            y = (int)(y0 * ym + yo);
            z0 = (Float.valueOf(data[2])).floatValue();
	    z = (int)z0;
            size = (Float.valueOf(data[4])).floatValue();
            symbolType = Integer.parseInt(data[7]);
        } catch (NumberFormatException e) {
            throw new YException("Invalid GData: (" + gdata + ")");
        }

	//TEMP -- perhaps this should be done when the symbol is
	// drawn, instead of now
        if (symbolType == _symEmbeddedTk) { // check symbol type
	    EmbeddedTk(data, size, xm, ym);

	} else if (symbolType == _symText) {
	    TextLabel(data, size, xm, ym);

        } else if (symbolType == _symFixedText) {
	    FixedTextLabel(data, size);

        } else if (symbolType == _symOval) {
	    if (view.getUseJmol() && view.viewDimension == 3) {
	        JmolOval(data, size, xm, ym);
	    } else {
	    	Oval(data, size, xm, ym);
	    }

	} else if (symbolType == _symSegment) {
	    if (view.getUseJmol() && view.viewDimension == 3) {
		JmolSegment(data, size, xm, ym);
	    } else {
                Segment(data, size, xm, ym);
	    }

        } else {
	    DefaultSymbol(data, size, xm, ym);
        }

        GDataLoc = new Rectangle(x, y, width, height);
    }

    protected void finalize() {
	jsc.jsValues.gdata._gdCount--;
	if (_debug) {
            System.out.println("DEViseGData.finalize() " + jsc.jsValues.gdata._gdCount);
            System.out.println("Free memory: " +
	      Runtime.getRuntime().freeMemory() + "/" +
	      Runtime.getRuntime().totalMemory());
        }
    }

    public Rectangle getLocInScreen()
    {
        Rectangle loc = parentView.getLocInScreen();

        Rectangle r = new Rectangle(x + loc.x, y + loc.y, width, height);
        if (r.x < loc.x) {
            r.width = r.width + r.x - loc.x;
            r.x = loc.x;
        } else if (r.x > loc.x + loc.width - r.width) {
            r.width = r.width + r.x - loc.x - loc.width + r.width;
            r.x = loc.x + loc.width - r.width;
        }
        if (r.y < loc.y) {
            r.height = r.height + r.y - loc.y;
            r.y = loc.y;
        } else if (r.y > loc.y + loc.height - r.height) {
            r.height = r.height + r.y - loc.y - loc.height + r.height;
            r.y = loc.y + loc.height - r.height;
        }

        return r;
    }

    protected void TextLabel(String[] data, float size, float xm, float ym)
      throws YException
    {
        isJavaSymbol = false;

        string = data[8];

        float w = 0.0f, h = 0.0f;
        int align, ff, fw, fs;

	// Note: format is ignored for now.  RKW 1999-11-03.

        // default font is courier, regular, nonitalic
        try {
            w = (Float.valueOf(data[10])).floatValue();
            h = (Float.valueOf(data[11])).floatValue();

            if (data[12].equals("")) {
                outline = 0;
            } else {
                outline = Integer.parseInt(data[12]);
            }

            if (data[13].equals("")) {
                align = 0;
            } else {
                align = Integer.parseInt(data[13]);
                if (align < -4 || align > 4) {
                    align = 0;
                }
            }

            if (data[14].equals("")) {
                ff = 0;
            } else {
                ff = Integer.parseInt(data[14]);
            }

            if (data[15].equals("")) {
                fw = 0;
            } else {
                fw = Integer.parseInt(data[15]);
            }

            if (data[16].equals("")) {
                fs = 0;
            } else {
                fs = Integer.parseInt(data[16]);
            }
        } catch (NumberFormatException e) {
            throw new YException("Invalid Gdata!");
        }

        width = (int)(w * size * xm);
        height = (int)(h * size * ym);
        if (width < 0) {
            width = -width;
	}
        if (height < 0) {
            height = -height;
	}

        color = DEViseUIGlobals.convertColor(data[3]);

        // Note: not using the default font here is probably less
        // efficient, but the previous version of this code failed
        // if we needed different fonts for different symbols.
        // RKW 1999-11-02.
        if (w < 0.0f) {
	    // Note: Z value in GData (if > 1) is max point size of font.
            font = DEViseUIGlobals.getFont(string, height, ff, fw, fs, (int)z0);
        } else {
	    // Note: Z value in GData (if > 1) is max point size of font.
            font = DEViseUIGlobals.getFont(string, width, height, ff, fw, fs, (int)z0);
        }

        if (color == null || font == null) {
            string = null;
            return;
        }

	AlignText(align);

        x = parentView.viewLocInCanvas.x + x;
        y = parentView.viewLocInCanvas.y + y;
    }

    protected void FixedTextLabel(String[] data, float size) throws YException
    {
        isJavaSymbol = false;

        string = data[8];

        float w = 0.0f, h = 0.0f;
        int align, ff, fw, fs;

        // default font is courier, regular, nonitalic
        try {
            if (data[10].equals("")) {
                align = 0;
            } else {
                align = Integer.parseInt(data[10]);
                if (align < -4 || align > 4) {
                    align = 0;
                }
            }

            if (data[11].equals("")) {
                ff = 0;
            } else {
                ff = Integer.parseInt(data[11]);
            }

            if (data[12].equals("")) {
                fw = 0;
            } else {
                fw = Integer.parseInt(data[12]);
            }

            if (data[13].equals("")) {
                fs = 0;
            } else {
                fs = Integer.parseInt(data[13]);
            }
        } catch (NumberFormatException e) {
            throw new YException("Invalid Gdata!");
        }

        width = 0;
        height = 0;

        color = DEViseUIGlobals.convertColor(data[3]);

        // Note: not using the default font here is probably less
        // efficient, but the previous version of this code failed
        // if we needed different fonts for different symbols.
        // RKW 1999-11-02.
        int fsize;
        if (size > 1.0f) {
            fsize = (int)(size + 0.25f);
        } else {
            fsize = (int)(size * jsc.jsValues.uiglobals.screenSize.height + 0.25f);
        }
        font = DEViseUIGlobals.getFont(fsize, ff, fw, fs);

        if (color == null || font == null) {
            string = null;
            return;
        }

	AlignText(align);

        x = parentView.viewLocInCanvas.x + x;
        y = parentView.viewLocInCanvas.y + y;
    }

    protected void EmbeddedTk(String[] data, float size, float xm, float ym)
    {
        isJavaSymbol = true;

        width = (int)(size * xm);
        height = (int)(size * ym);
        if (width < 0) {
            width = -width;
	}
        if (height < 0) {
            height = -height;
	}

        x = x - width / 2;
        y = y - height / 2;
        /* Don't force the entire rectangle to be within the view.
         * RKW 1999-10-28.
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        */

	_buttonLabel = data[11];
	_buttonCmd = data[10];
	if (data[12].equals("bmrb_dynamics_movie") && !data[13].equals("")) {
	    _buttonCmd += "&residues=" + data[13];
	}
        _menuType = data[21];
        _menuName = data[22];
    }

    protected void Oval(String[] data, float size, float xm, float ym)
    {
        isJavaSymbol = false;

        width = (int)(size * xm);
        height = (int)(size * ym);
        if (width < 0)
            width = -width;
        if (height < 0)
            height = -height;

        color = DEViseUIGlobals.convertColor(data[3]);

	// ADD COMMENT -- is this the name of the element??
        string = data[10];
    }

    protected void JmolOval(String[] data, float size, float xm, float ym)
    {
        isJavaSymbol = false;

        width = (int)(size * xm);
        height = (int)(size * ym);
        if (width < 0)
            width = -width;
        if (height < 0)
            height = -height;

        color = DEViseUIGlobals.convertColor(data[3]);

	atomNum = (Integer.valueOf(data[10])).intValue();
	atomName = data[11];
	residueLabel = data[14];
	residueNum = (Integer.valueOf(data[13])).intValue();
	atomType = data[15];
	structType = data[16];
	// Get Entity_assembly_ID (pre 11.4.0 versions of Peptide-CGI
	// don't send that).
	String entityAssemblyIDTmp = data[21];
	if (entityAssemblyIDTmp.equals("")) {
	    entityAssemblyID = 1;
	} else {
	    entityAssemblyID =
	      (Integer.valueOf(entityAssemblyIDTmp)).intValue();
	}
	atomId = data[22];
    }

    // This is a distance restraint...
    protected void JmolSegment(String[] data, float size, float xm, float ym)
    {
        isJavaSymbol = false;

	atom1Id = data[17].trim();
	atom2Id = data[18].trim();
	isViolated = data[19].trim().equals("Violated");
	isAmbiguous = data[22].trim().equals("Ambiguous");
    }

    protected void Segment(String[] data, float size, float xm, float ym)
    {
        isJavaSymbol = false;

        width = (int)(size * xm);
        height = (int)(size * ym);
        if (width < 0)
            width = -width;
        if (height < 0)
            height = -height;

        color = DEViseUIGlobals.convertColor(data[3]);

        x1 = x0 + size * (Float.valueOf(data[8])).floatValue();
        y1 = y0 + size * (Float.valueOf(data[9])).floatValue();
        z1 = z0 + size * (Float.valueOf(data[10])).floatValue();
        //z1 = (int)(z0 + size * ym * z1 );
    }

    protected void DefaultSymbol(String[] data, float size, float xm, float ym)
    {
        isJavaSymbol = false;

        width = (int)(size * xm);
        height = (int)(size * ym);
        if (width < 0) {
            width = -width;
        }
        if (height < 0) {
            height = -height;
        }

        x = x - width / 2;
        y = y - height / 2;
        /* Don't force the entire symbol to be within the view.
         * RKW 1999-10-28.
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        */
    }

    protected void AlignText(int align)
    {
        Toolkit tk = Toolkit.getDefaultToolkit();
        FontMetrics fm = tk.getFontMetrics(font);
        int ac = fm.getAscent(), dc = fm.getDescent();
        int sw = fm.stringWidth(string);

        switch (align) {
        case -4: // northwest
            y = y + ac;
            break;
        case -3: // west
            y = y + (ac - dc) / 2;
            break;
        case -2: // southwest
            y = y - dc;
            break;
        case -1: // north
            x = x - sw / 2;
            y = y + ac;
            break;
        case 0: // center
            x = x - sw / 2;
            y = y + (ac - dc) / 2;
            break;
        case 1: // south
            x = x - sw / 2;
            y = y - dc;
            break;
        case 2: // northeast
            x = x - sw;
            y = y + ac;
            break;
        case 3: // east
            x = x - sw;
            y = y + (ac - dc) / 2;
            break;
        case 4: // southeast
            x = x - sw;
            y = y - dc;
            break;
        }
    }
}
