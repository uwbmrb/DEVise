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

// This class provides an interface to canvases in the JavaScreen.
// It puts images into canvases, and also does the drawing of cursors,
// GData, and so on.  It holds some information related to piles (pile
// information is divided between DEViseCanvas and DEViseView).  This
// class also handles events that occur in views.

// There is one instance of this class for each top-level view in
// the session (note that if top-level views are piled, there's only
// one DEViseCanvas for the entire pile).

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.68  2001/01/08 20:31:50  wenger
// Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
// back onto the trunk.
//
// Revision 1.66.2.6  2000/11/22 17:43:56  wenger
// Finished cleanup of static variables fix; re-changed CGI command code to
// match the current version of the CGI script.
//
// Revision 1.66.2.5  2000/11/21 01:51:29  xuk
// Change some non-final static variables to non-static. Add a new class, DEViseJSValues, to contain all these variables and attach to every JS, JSA, JSB instance.
//
// Revision 1.66.2.4  2000/10/18 20:28:09  wenger
// Merged changes from fixed_bug_616 through link_gui_improvements onto
// the branch.
//
// Revision 1.67  2000/10/03 19:23:26  wenger
// Fixed bugs 592 and 594 (JavaScreen sometimes missing keystrokes in views).
//
// Revision 1.66.2.3  2000/10/18 18:29:12  wenger
// Added a separate thread to the JavaScreen to send the heartbeat -- this
// is much simpler that the previous version that used an existing thread.
//
// Revision 1.66.2.2  2000/10/11 03:00:21  xuk
// Add notifyall() to wake up dispatcher thread.
//
// Revision 1.66.2.1  2000/10/09 16:32:47  xuk
// Change dispathcer.start() to dispatcher.command = cmd, since D
// EViseCmdDispatcher thread starts only once now.
//
// Revision 1.66  2000/08/07 20:21:23  wenger
// Fixed problems with DEViseView.getFirstCursor() method; cleanup of
// DEViseCanvas CVS log, and other minor cleanup.
//
// Revision 1.65  2000/08/07 17:15:39  wenger
// Removed the 'control-drag' to move a cursor without talking to the devised
// feature because it could end up causing an incorrect state; added
// workaround for bug 607 (problems with control-drag); documented X-only zoom
// in keyboard help; improved JavaScreen makefile; fixed up makejsa.
//
// Revision 1.64  2000/08/07 04:45:23  venkatan
// YError that occurs when mouse-clicked in misc/FamMed_visits.tk is fixed.
//
// Revision 1.63  2000/08/07 03:28:51  venkatan
// Zoom for X - only direction is now available - done with CTRL + Rubberband
//
// Revision 1.62  2000/07/26 15:53:41  venkatan
// Hand - Mouse Cursor is used in the 3D view
//
// Revision 1.61  2000/07/21 03:23:42  venkatan
// Help Display - Multiple lines are now in a single "panel"
//
// Revision 1.60  2000/07/20 15:51:12  wenger
// Fixed bug 586 (can't move cursors with spaces in the names).
//
// Revision 1.59  2000/07/19 20:11:35  wenger
// Code to read data from sockets is more robust (hopefully fixes BMRB/Linux
// problem); background color of upper left part of JS changed to red when a
// dialog is shown; more debug output added.
//
// Revision 1.58  2000/07/18 18:12:49  venkatan
// The highlighting of the border for the active view is disabled.
//
// Revision 1.57  2000/07/18 18:10:56  venkatan
// *** empty log message ***
//
// Revision 1.56  2000/07/14 21:13:07  wenger
// Speeded up 3D GData processing by a factor of 2-3: improved the parser
// used for GData; eliminated Z sorting for bonds-only 3D views; eliminated
// DEViseAtomTypes for atoms used only to define bond ends; reduced string-
// based processing; eliminated various unused variables, etc.
//
// Revision 1.55  2000/07/12 16:52:42  wenger
// F1 key now shows help without clicking mouse button.
//
// Revision 1.54  2000/07/11 16:39:18  venkatan
// *** empty log message ***
//
// Revision 1.53  2000/07/10 12:26:02  venkatan
// *** empty log message ***
//
// Revision 1.52  2000/06/27 16:44:34  wenger
// Considerably cleaned up and simplified the cursor-related code; moved
// cursor grid implementation from the DEViseCanvas class to the DEViseCursor
// class.
//
// Revision 1.51  2000/06/21 18:37:29  wenger
// Removed a bunch of unused code (previously just commented out).
//
// Revision 1.50  2000/06/21 18:10:14  wenger
// Changes to 3D requested by BMRB: removed axes; up/down mouse movement
// does zooming; molecule doesn't move when changing atoms; 'r' resets
// location and zoom as well as rotation.
//
// Revision 1.49  2000/05/25 15:37:15  wenger
// Fixed bug 590 (JavaScreen "forgets" that you have control or alt pressed
// after you release the mouse button).
//
// Revision 1.48  2000/05/25 14:47:27  wenger
// 3D coordinate system remains unchanged when new GData arrives; 'r' or 'R'
// in view resets to default coordinates.
//
// Revision 1.47  2000/05/24 18:52:28  wenger
// Fixed problem with grabbing of cursor edges not working well.
//
// Revision 1.46  2000/05/22 17:52:48  wenger
// JavaScreen handles fonts much more efficiently to avoid the problems with
// GData text being drawn very slowly on Intel platforms.
//
// Revision 1.45  2000/05/12 20:43:45  wenger
// Added more comments to the DEViseScreen, DEViseCanvas, and jsdevisec
// classes and cleaned up the code; commented out unused code; added
// named constants for location of mouse pointer on a DEVise cursor.
//
// Revision 1.44  2000/05/11 20:19:32  wenger
// Cleaned up jsdevisec.java and added comments; eliminated
// jsdevisec.lastCursor (not really needed).
//
// Revision 1.43  2000/05/08 16:40:39  wenger
// JavaScreen cursors are now drawn as frames rather than filled
// rectangles (so symbols, especially text, show up better within cursors).
//
// Revision 1.42  2000/05/04 15:53:22  wenger
// Added consistency checking, added comments, commented out unused code
// in DEViseScreen.java, DEViseCanvas.java, DEViseView.java,
// DEViseCmdDispatcher.java.
//
// Revision 1.41  2000/04/27 20:15:23  wenger
// Added DEViseCommands class which has string constants for all command
// names; replaced all literal command names in code with the appropriate
// DEViseCommand constants.
//
// Revision 1.40  2000/04/24 20:21:58  hongyu
// remove UI dependency of jspop and js
//
// Revision 1.39  2000/04/07 22:43:13  wenger
// Improved shading of atoms (it now works on white atoms); added comments
// based on meeting with Hongyu on 2000-04-06.
//
// Revision 1.38  2000/04/05 06:25:36  hongyu
// fix excessive memory usage problem associated with gdata
//
// Revision 1.37  2000/04/03 22:24:52  wenger
// Added named constants for GData symbol types; 3D GData symbols are now
// differentiated by symbol type instead of string; removed some commented-
// out code.
//
// Revision 1.36  2000/03/23 16:26:12  wenger
// Cleaned up headers and added requests for comments.
//
// Revision 1.35  2000/02/23 21:12:11  hongyu
// *** empty log message ***
//
// Revision 1.34  2000/02/23 10:44:01  hongyu
// *** empty log message ***
//
// Revision 1.33  2000/02/22 15:26:39  wenger
// Commented out debug output.
//
// Revision 1.32  2000/02/22 10:00:38  hongyu
// *** empty log message ***
//
// Revision 1.31  2000/02/16 08:53:48  hongyu
// *** empty log message ***
//
// Revision 1.29  2000/01/12 14:37:48  hongyu
// *** empty log message ***
//
// Revision 1.28  1999/12/10 15:30:12  wenger
// Molecule dragging greatly speeded up by drawing plain (unshaeded) circles
// during drag; split off protocol version from "main" version.
//
// Revision 1.27  1999/12/07 23:18:20  hongyu
// *** empty log message ***
//
// Revision 1.25  1999/12/06 23:22:22  hongyu
// *** empty log message ***
//
// Revision 1.24  1999/12/02 19:47:23  hongyu
// *** empty log message ***
//
// Revision 1.23  1999/11/11 18:11:51  hongyu
// *** empty log message ***
//
// Revision 1.22  1999/11/03 08:00:48  hongyu
// *** empty log message ***
//
// Revision 1.21  1999/11/01 17:40:15  hongyu
// *** empty log message ***
//
// Revision 1.20  1999/10/14 15:08:53  hongyu
// *** empty log message ***
//
// Revision 1.19  1999/10/12 22:00:03  hongyu
// *** empty log message ***
//
// Revision 1.17  1999/10/12 00:08:42  hongyu
// *** empty log message ***
//
// Revision 1.16  1999/10/10 08:49:51  hongyu
// Major changes to JAVAScreen have been commited in this update, including:
// 1. restructure of JavaScreen internal structure to adapt to vast changes
//    in DEVise and also prepare to future upgrade
// 2. Fix a number of bugs in visualization and user interaction
// 3. Add a number of new features in visualization and user interaction
// 4. Add support for complicated 3D molecular view
//
// Revision 1.15  1999/09/24 17:11:46  hongyu
// adding support for 3-d molecule view
//
// Revision 1.14  1999/08/24 08:45:52  hongyu
// *** empty log message ***
//
// Revision 1.13  1999/08/19 07:20:51  hongyu
// *** empty log message ***
//
// Revision 1.12  1999/08/17 06:15:16  hongyu
// *** empty log message ***
//
// Revision 1.11  1999/08/03 05:56:35  hongyu
// bug fixes    by Hongyu Yao
//
// Revision 1.9  1999/07/27 17:11:17  hongyu
// *** empty log message ***
//
// Revision 1.7  1999/06/23 20:59:14  wenger
// Added standard DEVise header.
//

// ========================================================================

// DEViseCanvas.java

import  java.awt.*;
import  java.applet.*;
import  java.awt.event.*;
import  java.awt.image.*;
import  java.util.*;
import  java.net.*;
import  java.io.*;

public class DEViseCanvas extends Container
{

    private jsdevisec jsc = null;
    private DEViseScreen jscreen = null;
    private DEViseCmdDispatcher dispatcher = null;
    public int posZ = 0;

    public int oldHighlightAtomIndex = -1, highlightAtomIndex = -1;
    public Point point = new Point();
    public DEViseCrystal crystal = null;

    public DEViseView view = null; // base view if piled

    // ADD COMMENT -- we need clarification here as to why this is on a
    // per-canvas basis, since there can actually only be one active view
    // at a time in the entire JS; Hongyu says that this does not
    // necessarily get set to null when the active view becomes inactive.
    public DEViseView activeView = null;

    private Dimension canvasDim = null;

    private Image image = null;
    private Image offScrImg = null;
    private boolean isImageUpdated = false;

    public boolean isMouseDragged = false, isInViewDataArea = false,
      isInDataArea = false;
    private DEViseCursor selectedCursor = null;

    // See DEViseCursor.side* for values.
    private int whichCursorSide = DEViseCursor.sideNone;

    // Keep track of whether the mouse is actually in this canvas (part of
    // the fix for the "missing keystrokes" bugs.
    private boolean _mouseIsInCanvas = false;

    public String helpMsg = null;
    public int helpMsgX = -1, helpMsgY = -1;

    Point sp = new Point(), ep = new Point(), op = new Point();

    private int mouseDragCount = 0;

    //
    // This is a fix to a problem that seems to be in the JVM itself:
    // when a mouse button press is closely followed in time by moving
    // the mouse, Java calls the mouseMoved() method of the
    // MouseMotionListener as opposed to the mouseDragged() method,
    // even though it has already called mousePressed() in the
    // MouseListener.  RKW 2000-05-24.
    //
    private boolean buttonIsDown = false;

    private static final int DEBUG = 0; // 0 - 3

    // v is base view if there is a pile in this canvas.
    public DEViseCanvas(DEViseView v, Image img)
    {
        view = v;
        jsc = view.jsc;
        jscreen = jsc.jscreen;
        dispatcher = jsc.dispatcher;
        image = img;

        if (image != null) {
            canvasDim = new Dimension(image.getWidth(this), image.getHeight(this));
            view.viewLoc.width = canvasDim.width;
            view.viewLoc.height = canvasDim.height;
            view.viewLocInCanvas.width = canvasDim.width;
            view.viewLocInCanvas.height = canvasDim.height;
            isImageUpdated = true;
        }

        this.enableEvents(AWTEvent.MOUSE_EVENT_MASK);
        this.enableEvents(AWTEvent.MOUSE_MOTION_EVENT_MASK);
        this.enableEvents(AWTEvent.KEY_EVENT_MASK);
        addMouseListener(new ViewMouseListener());
        addMouseMotionListener(new ViewMouseMotionListener());
        addKeyListener(new ViewKeyListener());
        addFocusListener(new ViewFocusListener());
    }

    public Dimension getPreferredSize()
    {
        return canvasDim;
    }

    public Dimension getMinimumSize()
    {
        return canvasDim;
    }

    public Rectangle getLocInScreen()
    {
        return view.viewLoc;
    }

    public boolean mouseIsWithin()
    {
        return _mouseIsInCanvas;
    }

    // This function is used to draw cursors because direct XOR drawing
    // (with Graphics.setXORMode()) doesn't seem to work in Netscape.
    // loc is relative to this canvas.
    public Image getCroppedXORImage(Color c, Rectangle loc)
    {
        if (image == null)
            return null;

        CropImageFilter croppedFilter = new CropImageFilter(loc.x, loc.y,
	  loc.width, loc.height);
        FilteredImageSource source = new FilteredImageSource(
	  image.getSource(), croppedFilter);
        Image img = createImage(source);
        if (img == null) {
            return null;
        }

        source = new FilteredImageSource(img.getSource(),
	  new XORFilter(c, loc.width, loc.height, XORFilter.typeFrame));
        img = createImage(source);

        return img;
    }

    public synchronized void updateImage(Image img)
    {
        if (img != null) {
            image = img;
            canvasDim.width = image.getWidth(this);
            canvasDim.height = image.getHeight(this);
            view.viewLoc.width = canvasDim.width;
            view.viewLoc.height = canvasDim.height;
            view.viewLocInCanvas.width = canvasDim.width;
            view.viewLocInCanvas.height = canvasDim.height;

            isImageUpdated = true;
        }

        // Necessary to draw correct image because double-buffering is used
        //offScrImg = null;
    }

    // Enable double-buffering
    public void update(Graphics gc)
    {
        if (gc == null) {
            return;
        }

        if (offScrImg == null) {
            offScrImg = createImage(canvasDim.width, canvasDim.height);
        }

        if (offScrImg == null) {
            paint(gc);
        } else {
            Graphics og = offScrImg.getGraphics();
            paint(og);
            gc.drawImage(offScrImg, 0, 0, this);
            og.dispose();
        }
    }

    public void paint(Graphics gc)
    {
        if (jsc.jsValues.canvas.isInteractive) {
            if (jsc.jsValues.canvas.sourceCanvas != this) {
                return;
            }
        }

        // draw 3D molecular view
        if (paintCrystal(gc)) {
            paintBorder(gc);
            paintHelpMsg(gc);
            return;
        }

        // draw the background image
        paintBackground(gc);

        // draw titles for all views, including view symbols but not piled views
        paintTitle(gc);

        // draw all the cursors
        paintCursor(gc);

        // draw all the GDatas
        paintGData(gc, view);

        // draw rubber band
        paintRubberBand(gc);

        // draw highlight border
        paintBorder(gc);

        paintHelpMsg(gc);
    }

/* - untouched
    private void paintHelpMsg(Graphics gc)
    {
        if (helpMsg == null) {
            return;
        }

        if (helpMsgX < 0) {
            helpMsgX = 0;
        }
        if (helpMsgY < 0) {
            helpMsgY = 0;
        }
 
        Toolkit tk = Toolkit.getDefaultToolkit();
        FontMetrics fm = tk.getFontMetrics(DEViseUIGlobals.textFont);
        int ac = fm.getAscent(), dc = fm.getDescent(), height = ac + dc + 12;
        int width = fm.stringWidth(helpMsg) + 12;
	int charInCol = width/100  * 12;
        int scrWidth = 	this.getLocInScreen().width;
	int scrHeight = this.getLocInScreen().height;
	if(helpMsg.length()/12 * height >  scrHeight){ 
		return; 
	}
        if(scrWidth > width ||( scrWidth > 200  &&  scrHeight > 60)){ 			 
            StringTokenizer helper = new StringTokenizer(helpMsg, "\n");
	    while(helper.hasMoreTokens()){
	        String smallhelp = helper.nextToken();
	        String sh1 = smallhelp;
                if((fm.stringWidth(sh1)+12) > scrWidth){ 
	            sh1= smallhelp.substring(0, smallhelp.length()/2);
                    gc.setColor(Color.black);
                    gc.drawRect(helpMsgX, helpMsgY, width - 1, height - 1);
                    gc.setColor(new Color(255, 255, 192));
                    gc.fillRect(helpMsgX + 1, helpMsgY + 1, width - 2, height - 2);
                    gc.setColor(Color.black);
                    gc.setFont(DEViseUIGlobals.textFont);
                    gc.drawString(sh1, helpMsgX + 6, helpMsgY + height - dc - 6);
	            helpMsgY += 30;
	            smallhelp= smallhelp.substring(smallhelp.length()/2, smallhelp.length());
	  }
          gc.setColor(Color.black);
          gc.drawRect(helpMsgX, helpMsgY, width - 1, height - 1);
          gc.setColor(new Color(255, 255, 192));
          gc.fillRect(helpMsgX + 1, helpMsgY + 1, width - 2, height - 2);
          gc.setColor(Color.black);
          gc.setFont(DEViseUIGlobals.textFont);
          gc.drawString(smallhelp, helpMsgX + 6, helpMsgY + height - dc - 6);
	  helpMsgY += 30;
	  }
	}
        helpMsgX = 0; helpMsgY = 0;

        //helpMsg = null;
    } 

*/


    private synchronized void paintBackground(Graphics gc)
    {
        if (image != null) {
            gc.drawImage(image, 0, 0, canvasDim.width, canvasDim.height, this);
        } else {
            gc.setColor(new Color(view.viewBg));
            gc.fillRect(0, 0, canvasDim.width, canvasDim.height);
        }
    }
// Venpaint

    private void paintHelpMsg(Graphics gc)
    {
	boolean testPrint = false;
        if (helpMsg == null) {
            return;
        }

        if (helpMsgX < 0) {
            helpMsgX = 0;
        }
        if (helpMsgY < 0) {
            helpMsgY = 0;
        }
	helpMsgX = 0; helpMsgY = 0;
 
        Toolkit tk = Toolkit.getDefaultToolkit();
        FontMetrics fm = tk.getFontMetrics(jsc.jsValues.uiglobals.textFont);
        int ac = fm.getAscent(), dc = fm.getDescent(), height = ac + dc + 12;
        int width = fm.stringWidth(helpMsg) + 12;
	int minHeight = height + height/3; int minWidth = fm.stringWidth("THIS IS THE MINIMUM");

	if(canvasDim.width < minWidth || canvasDim.height < minHeight){
	   return;
        }
     
        StringTokenizer st = new StringTokenizer(helpMsg, "\n");
	Vector sv = new Vector();
	String back = "";

        while(st.hasMoreTokens()|| !back.equals("")){
	      String tmp = back + " ";
	   if(st.hasMoreTokens()){
	       tmp  +=  st.nextToken(); 
           }
	   
	   int tokenWidth = fm.stringWidth(tmp) + 12;
	   if(tokenWidth > canvasDim.width){
	     // testPrint = true;
             String[] a = stringSplit(tmp, fm);
	     tmp = a[0];
	     back = a[1];
	     // System.out.println(tmp);
	     // System.out.println(back);
	     sv.addElement(tmp);

           }
	   else{
	      sv.addElement(tmp);
	      back = "";
	   }    
        }

	if(testPrint){
	   // System.out.println(helpMsg);
	}

	if( back.equals("")); 
	else{
	   sv.addElement(back);
        }
	   
        int totHeight = height * sv.size() ;
        if( sv.size () > 3 ){ 
	   totHeight += sv.size() * (-5);
        }

	int allowedHeight = 4* canvasDim.height/5;
        if(totHeight> allowedHeight ){
	   // may want to put some message;
	   return;
         }


//      int dispLength = canvasDim.width;	
//      computing display length

        int dispLength = 0;
        for(int i = 0; i < sv.size(); i++){
	  String s = (String) sv.elementAt(i);
	  int w = fm.stringWidth(s);
	  if(dispLength < w ){
	     dispLength = w;
          } 
        }   
        dispLength += 12;
        if( dispLength < canvasDim.width){
	 int j = canvasDim.width - dispLength;
	 if( j  > 6){
	     dispLength +=6;
         }
	 else{
	     dispLength += j;
         }
        } 

        // setting up the color background and text color.

        gc.setColor(Color.black);
        gc.drawRect(helpMsgX, helpMsgY, dispLength -1, totHeight);
        gc.setColor(new Color(255, 255, 192));
        gc.fillRect(helpMsgX + 1, helpMsgY + 1,dispLength - 2, totHeight- 1);
        gc.setColor(Color.black);
        gc.setFont(jsc.jsValues.uiglobals.textFont);

        // printing each of the line from the Vector of lines.
        for( int i = 0 ; i < sv.size(); i++){	
           gc.drawString(((String) sv.elementAt(i)), helpMsgX + 6, helpMsgY + height - dc - 6);
	   helpMsgY += (height - dc -6);
	}
	  

    }	

   private String[]  stringSplit(String a, FontMetrics fm){
       StringTokenizer st = new StringTokenizer(a, " "); 
       int defWidth = 0;
       String tmp ="";
       String[] res = new String[2];
       res[0] = ""; res[1] = "";
       while( st.hasMoreTokens()){
	 tmp = st.nextToken();
	 defWidth = fm.stringWidth(res[0]) + fm.stringWidth(tmp + " ") ;
	 if((defWidth + 5) > canvasDim.width){
           break;
         }
	 else{
	    res[0] = res[0] + " " + tmp;
         }
       }
       res[1] = tmp + " " ;
       while( st.hasMoreTokens()){
	  res[1] += (st.nextToken() + " "); 
       }
       // System.out.println( a + " split as " + res[0] + " and " + res[1]);

       return res;
   }

	   
          

    private synchronized boolean paintCrystal(Graphics gc)
    {
        if (view.viewDimension != 3) {
            return false;
        }

	if (jsc.jsValues.debug._debugLevel >= 2) {
            jsc.pn("Crystals have been painted " +
	      jsc.jsValues.canvas.crystalPaintCount++ + " times");
        }

        if (crystal == null) {
            createCrystal();
            if (crystal == null) {
                paintBackground(gc);
                return true;
            }
        }

        paintBackground(gc);
        crystal.paint(this, gc, isMouseDragged);

        return true;
    }

    private synchronized void paintBorder(Graphics gc)
    {
       // Border for Active view is disabled. - no highlighting
       /* if (activeView != null && activeView == jscreen.getCurrentView()) {
            Rectangle loc = activeView.viewLocInCanvas;

            gc.setColor(Color.red);
            gc.drawRect(loc.x, loc.y, loc.width - 1, loc.height - 1);
            gc.drawRect(loc.x + 1, loc.y + 1, loc.width - 3, loc.height - 3);
        }
	*/
    }

    // only top views get title drawn
    // TEMP -- child views of piled views should probably have titles drawn
    private synchronized void paintTitle(Graphics gc)
    {
	//TEMP -- should probably reverse the order here

        // handling child view
        for (int i = 0; i < view.viewChilds.size(); i++) {
            DEViseView v = (DEViseView)view.viewChilds.elementAt(i);

            if (v.viewDTFont != null && v.viewTitle != null) {
                gc.setColor(new Color(v.viewFg));
                gc.setFont(v.viewDTFont);
                gc.drawString(v.viewTitle, v.viewDTX, v.viewDTY);
            }
        }

        // handling itself
        if (view.viewDTFont != null && view.viewTitle != null) {
            gc.setColor(new Color(view.viewFg));
            gc.setFont(view.viewDTFont);
            gc.drawString(view.viewTitle, view.viewDTX, view.viewDTY);
        }
    }

    // every view will have its cursor properly drawn
    private synchronized void paintCursor(Graphics gc)
    {
        paintCursor(gc, view);

        isImageUpdated = false;
    }

    private synchronized void paintCursor(Graphics gc, DEViseView v)
    {
	//TEMP -- should probably reverse the order here

        // handling child views
        for (int i = 0; i < v.viewChilds.size(); i++) {
            DEViseView vv = (DEViseView)v.viewChilds.elementAt(i);

            paintCursor(gc, vv);
        }

        // handling itself
        Rectangle loc = null;
        DEViseCursor cursor = null;
        for (int i = 0; i < v.viewCursors.size(); i++) {
            cursor = (DEViseCursor)v.viewCursors.elementAt(i);
            loc = cursor.getLocInCanvas();

            if (selectedCursor == cursor && isMouseDragged) { // draw cursor movement box
                if (loc.width < 4)
                    loc.width = 4;
                if (loc.height < 4)
                    loc.height = 4;

                gc.setColor(Color.yellow);
                gc.drawRect(loc.x, loc.y, loc.width - 1, loc.height - 1);
                gc.setColor(Color.red);
                gc.drawRect(loc.x + 1, loc.y + 1, loc.width - 3, loc.height - 3);

                continue;
            }

            if (cursor.image == null || isImageUpdated) {
                cursor.image = getCroppedXORImage(cursor.color, loc);
            }

            if (cursor.image != null) {
                gc.drawImage(cursor.image, loc.x, loc.y, this);
            }
        }

        // handling piled views
        for (int i = 0; i < v.viewPiledViews.size(); i++) {
            DEViseView vv = (DEViseView)v.viewPiledViews.elementAt(i);

            paintCursor(gc, vv);
        }
    }

    private synchronized void paintGData(Graphics gc, DEViseView v)
    {
	//TEMP -- should probably reverse the order here

        // handling child views
        for (int i = 0; i < v.viewChilds.size(); i++) {
            DEViseView vv = (DEViseView)v.viewChilds.elementAt(i);

            paintGData(gc, vv);
        }

        // handling itself
        DEViseGData gdata = null;
	Color tmpColor = null;
	Font tmpFont = null;
        for (int i = 0; i < v.viewGDatas.size(); i++) {
            gdata = (DEViseGData)v.viewGDatas.elementAt(i);

            if (gdata.string != null && (gdata.symbolType == gdata._symText ||
	      gdata.symbolType == gdata._symFixedText)) {

		// Set the color and font only when necessary.
		if (!gdata.color.equals(tmpColor)) {
                    gc.setColor(gdata.color);
		    tmpColor = gdata.color;
		}
		if (!gdata.font.equals(tmpFont)) {
                    gc.setFont(gdata.font);
		    tmpFont = gdata.font;
		}

                gc.drawString(gdata.string, gdata.x, gdata.y);
            }
        }

        // handling piled views
        for (int i = 0; i < v.viewPiledViews.size(); i++) {
        //for (int i = v.viewPiledViews.size() - 1; i >= 0; i--) {
            DEViseView vv = (DEViseView)v.viewPiledViews.elementAt(i);

            paintGData(gc, vv);
        }
    }

    private synchronized void paintRubberBand(Graphics gc)
    {
        if (isInViewDataArea && isMouseDragged && selectedCursor == null) {
            int x0, y0, w, h;

            if (sp.x > ep.x)  {
                x0 = ep.x;
                w = sp.x - x0;
            }  else  {
                x0 = sp.x;
                w = ep.x - x0;
            }

            if (sp.y > ep.y)  {
                y0 = ep.y;
                h = sp.y - y0;
            }  else  {
                y0 = sp.y;
                h = ep.y - y0;
            }

            if (w < 4)
                w = 4;
            if (h < 4)
                h = 4;

            gc.setColor(Color.yellow);
            gc.drawRect(x0, y0, w - 1, h - 1);
            gc.setColor(Color.red);
            gc.drawRect(x0 + 1, y0 + 1, w - 3, h - 3);
        }
    }

    protected void processMouseEvent(MouseEvent event)
    {
        int id = event.getID();

        if (DEBUG >= 1) {
            System.out.println("DEViseCanvas(" + view.viewName +
	      ").processMouseEvent()");
            if (id == MouseEvent.MOUSE_PRESSED) System.out.println(
	      "  Mouse pressed");
            if (id == MouseEvent.MOUSE_CLICKED) System.out.println(
	      "  Mouse clicked");
            if (id == MouseEvent.MOUSE_RELEASED) System.out.println(
	      "  Mouse released");
        }

        jsc.jscreen.finalMousePosition.x = view.viewLoc.x + event.getX();
        jsc.jscreen.finalMousePosition.y = view.viewLoc.y + event.getY();
	//jsc.pn("DEViseCanvas.processMouseEvent()");
        if (id == MouseEvent.MOUSE_PRESSED || id == MouseEvent.MOUSE_RELEASED
	  || id == MouseEvent.MOUSE_CLICKED) {
            if (dispatcher.getStatus() != 0) {
                if (id == MouseEvent.MOUSE_PRESSED) {
                    jsc.showMsg("JavaScreen still talking to the Server!\nPlease try again later or press STOP button!");
                }

                return;
            }
        }

        super.processMouseEvent(event);
    }

    protected void processMouseMotionEvent(MouseEvent event)
    {
        if (DEBUG >= 2) {
            System.out.println("DEViseCanvas(" + view.viewName +
	      ").processMouseMotionEvent()");
        }

        int id = event.getID();

        jsc.jscreen.finalMousePosition.x = view.viewLoc.x + event.getX();
        jsc.jscreen.finalMousePosition.y = view.viewLoc.y + event.getY();

        if (id == MouseEvent.MOUSE_DRAGGED) {
            if (dispatcher.getStatus() != 0) {
                return;
            }
        }

        super.processMouseMotionEvent(event);
    }

    protected void processKeyEvent(KeyEvent event)
    {
        if (view.viewDimension != 3) {
            if (dispatcher.getStatus() != 0) {
                //if (event.getID() == KeyEvent.KEY_PRESSED) {
                //    jsc.showMsg("Java Screen still talking to the Server!\nPlease try again later or press STOP button!");
                //}

                return;
            }
        }

        super.processKeyEvent(event);
    }

    // start of class ViewKeyListener
    class ViewKeyListener extends KeyAdapter
    {
        // event sequence: 1. keypressed 2.keytyped 3.keyreleased
        public void keyPressed(KeyEvent event)
        {
            if (DEBUG >= 1) {
                System.out.println("DEViseCanvas(" + view.viewName +
		  ").keyPressed(" + event.getKeyChar() + ")");
	    }
            jsc.jsValues.canvas.lastKey = event.getKeyCode();
        }

	// If this is not a 3D-view, send the appropriate key action
	// to the devised.
        public void keyReleased(KeyEvent event)
        {
            if (DEBUG >= 1) {
                System.out.println("DEViseCanvas(" + view.viewName +
		  ").keyReleased(" + event.getKeyChar() + ")");
	    }
            jsc.jsValues.canvas.lastKey = KeyEvent.VK_UNDEFINED;

            char keyChar = event.getKeyChar();
            int keyCode = event.getKeyCode();

	    // F1 key shows or hides view help.
            if (keyCode == KeyEvent.VK_F1) {
                    helpMsg = null;
	            //
	            // Show this view's help within a dialog box.
	            //
                    jsc.jsValues.connection.helpBox = true;
                    String cmd = DEViseCommands.GET_VIEW_HELP + " " +
		      activeView.getCurlyName() + " " + helpMsgX + " "
		      + helpMsgY;
		    // jscreen.guiAction = true;
     		    dispatcher.start(cmd);
                    return;
            }

            if (view.viewDimension == 3) {
		if ((keyChar == 'r' || keyChar == 'R') && crystal != null) {
                    crystal.totalShiftedX = 0;
                    crystal.totalShiftedY = 0;
		    crystal.totalX = 0.0f;
		    crystal.totalY = 0.0f;
		    crystal.totalZ = 0.0f;
		    crystal.totalXRotation = 0.0f;
		    crystal.totalYRotation = 0.0f;
		    crystal.totalScaleFactor = 1.0f;
		    crystal.resetAll(true);
		    repaint();

		    // send command to collaborations if necessary
		    if (jsc.specialID == -1) {
			String cmd = DEViseCommands.COLLAB_3DVIEW + 
			    " {1} " + activeView.getCurlyName();
			dispatcher.start(cmd);	
		    }		
		}
                return;
            }

            int actualKey = 0;

            if (keyChar != KeyEvent.CHAR_UNDEFINED) {
                actualKey = (int)keyChar;
            } else {
                switch (keyCode) {
                case KeyEvent.VK_NUMPAD0:
                    actualKey = 0x40000 + 28;
                    break;
                case KeyEvent.VK_NUMPAD1:
                    actualKey = 0x40000 + 29;
                    break;
                case KeyEvent.VK_NUMPAD2:
                    actualKey = 0x40000 + 30;
                    break;
                case KeyEvent.VK_NUMPAD3:
                    actualKey = 0x40000 + 31;
                    break;
                case KeyEvent.VK_NUMPAD4:
                    actualKey = 0x40000 + 32;
                    break;
                case KeyEvent.VK_NUMPAD5:
                    actualKey = 0x40000 + 33;
                    break;
                case KeyEvent.VK_NUMPAD6:
                    actualKey = 0x40000 + 34;
                    break;
                case KeyEvent.VK_NUMPAD7:
                    actualKey = 0x40000 + 35;
                    break;
                case KeyEvent.VK_NUMPAD8:
                    actualKey = 0x40000 + 36;
                    break;
                case KeyEvent.VK_NUMPAD9:
                    actualKey = 0x40000 + 37;
                    break;
                //case KeyEvent.VK_F1:
                 //   actualKey = 0x50000 + 1;
                 //   break;
                //case KeyEvent.VK_F2:
                 //   actualKey = 0x50000 + 2;
                  //  break;
                case KeyEvent.VK_F3:
                    actualKey = 0x50000 + 3;
                    break;
                case KeyEvent.VK_F4:
                    actualKey = 0x50000 + 4;
                    break;
                case KeyEvent.VK_F5:
                    actualKey = 0x50000 + 5;
                    break;
                case KeyEvent.VK_F6:
                    actualKey = 0x50000 + 6;
                    break;
                case KeyEvent.VK_F7:
                    actualKey = 0x50000 + 7;
                    break;
                case KeyEvent.VK_F8:
                    actualKey = 0x50000 + 8;
                    break;
                case KeyEvent.VK_F9:
                    actualKey = 0x50000 + 9;
                    break;
                case KeyEvent.VK_F10:
                    actualKey = 0x50000 + 10;
                    break;
                case KeyEvent.VK_F11:
                    actualKey = 0x50000 + 11;
                    break;
                case KeyEvent.VK_F12:
                    actualKey = 0x50000 + 12;
                    break;
                case KeyEvent.VK_HOME:
                    actualKey = 0x20000 + 1;
                    break;
                case KeyEvent.VK_LEFT:
                    actualKey = 0x20000 + 2;
                    break;
                case KeyEvent.VK_UP:
                    actualKey = 0x20000 + 3;
                    break;
                case KeyEvent.VK_RIGHT:
                    actualKey = 0x20000 + 4;
                    break;
                case KeyEvent.VK_DOWN:
                    actualKey = 0x20000 + 5;
                    break;
                case KeyEvent.VK_PAGE_UP:
                    actualKey = 0x20000 + 7;
                    break;
                case KeyEvent.VK_PAGE_DOWN:
                    actualKey = 0x20000 + 9;
                    break;
                case KeyEvent.VK_END:
                    actualKey = 0x20000 + 10;
                    break;
                default:
                    actualKey = 0;
                    break;
                }
            }

            if (actualKey != 0 && activeView != null && activeView.isKey) {
                String cmd = "";
                cmd = cmd + DEViseCommands.KEY_ACTION + " " + activeView.getCurlyName() + " " + actualKey;
                jscreen.guiAction = true;
                dispatcher.start(cmd);
            }
        }
    }
    // end of class ViewKeyListener

    // start of class ViewMouseListener
    class ViewMouseListener extends MouseAdapter
    {
        // event sequence: 1. mousePressed 2. mouseReleased 3. mouseClicked
        public void mousePressed(MouseEvent event)
        {
            if (DEBUG >= 1) {
                System.out.println(
		  "DEViseCanvas(" + view.viewName +
		    ").ViewMouseListener.mousePressed()");
            }

	    // Bug fix -- see notes at variable declaration.
            buttonIsDown = true;

            // The starting point will be in this view, otherwise this event
	    // will not be caught.

            // Each mouse click will be here once, so double click actually
	    // will enter this twice.

            // The position of this event will be relative to this view, and
	    // will not exceed the range of this view, ie, p.x >= 0 &&
	    // p.x < view.width ...

            Point p = event.getPoint();
            ep.x = op.x = sp.x = p.x;
            ep.y = op.y = sp.y = p.y;

            if (view.viewDimension == 3) {
                // setCursor(DEViseUIGlobals.rbCursor);  - Ven modified
		   setCursor(DEViseUIGlobals.hdCursor);

                activeView = view;
                jsc.viewInfo.updateInfo(activeView.viewName,
		  activeView.getX(sp.x), activeView.getY(sp.y));
                if (jscreen.getCurrentView() != activeView) {
                    jscreen.setCurrentView(activeView);
                }

		// send command to collaborations if necessary
		
		if (jsc.specialID == -1) {
		    String cmd = DEViseCommands.COLLAB_3DVIEW + 
			" {2} " + activeView.getCurlyName() + 
			" {" + p.x + "}" + " {" + p.y + "}";
		    dispatcher.start(cmd);	
		}	
			
                return;
            }

            checkMousePos(sp, true);
        }

        public void mouseReleased(MouseEvent event)
        {
	    if (DEBUG >= 1) {
	        System.out.println(
		  "DEViseCanvas(" + view.viewName +
		    ").ViewMouseListener.mouseReleased()");
	    }

	    // Bug fix -- see notes at variable declaration.
	    buttonIsDown = false;

            // Each mouse click will be here once, so double click actually
	    // will enter this twice. Also, this event will always reported
	    // with each mouse click and before the mouseClick event is
	    // reported.

            jsc.jsValues.canvas.isInteractive = false;

            if (view.viewDimension == 3) {
                isMouseDragged = false;
                repaint();

		// send command to collaborations if necessary
		Point p = event.getPoint();		
		
		if (jsc.specialID == -1) {
		    String cmd = DEViseCommands.COLLAB_3DVIEW + 
			" {3} " + activeView.getCurlyName() + 
			" {" + p.x + "}" + " {" + p.y + "}";
		    dispatcher.start(cmd);	
		}	

                return;
            }

            if (isMouseDragged && isInViewDataArea) {
                Point p = event.getPoint();
                String cmd = "";

                if (selectedCursor != null) { // move or resize cursor
                    ep.x = activeView.translateX(p.x, 1);
                    ep.y = activeView.translateY(p.y, 1);

                    jsc.viewInfo.updateInfo(activeView.getX(ep.x),
		      activeView.getY(ep.y));

                    int dx = ep.x - sp.x, dy = ep.y - sp.y;
                    DEViseCursor cursor = selectedCursor;

                    cursor.updateCursorLoc(dx, dy, whichCursorSide, true);

                    cursor.image = null;

                    cmd = cmd + DEViseCommands.CURSOR_CHANGED + " {" +
		      cursor.name + "} " + cursor.x + " " + cursor.y +
		      " " + cursor.width + " " + cursor.height;

                    jscreen.guiAction = true;
                    dispatcher.start(cmd);
                } else { // rubber band
                    ep.x = activeView.translateX(p.x, 1);
                    ep.y = activeView.translateY(p.y, 1);

                    jsc.viewInfo.updateInfo(activeView.getX(ep.x),
		      activeView.getY(ep.y));

                    int w = ep.x - sp.x, h = ep.y - sp.y;
                    if (w < 0)
                        w = -w;
                    if (h < 0)
                        h = -h;

                    if (w > jsc.jsValues.uiglobals.rubberBandLimit.width ||
		      h > jsc.jsValues.uiglobals.rubberBandLimit.height) {
                        cmd = cmd + DEViseCommands.MOUSE_RUBBERBAND +
			  " " + activeView.getCurlyName() + " " +
			  activeView.translateX(sp.x, 2) + " " +
			  activeView.translateY(sp.y, 2) + " " +
			  activeView.translateX(ep.x, 2) + " " +
			  activeView.translateY(ep.y, 2);

                        if (jsc.jsValues.canvas.lastKey == KeyEvent.VK_ALT) {
                            cmd = cmd + " 1";
                        } else {
                            cmd = cmd + " 0";
                        }

			//Zoom in X only direction - modified by Ven

                        if (jsc.jsValues.canvas.lastKey == KeyEvent.VK_CONTROL) {
                            cmd = cmd + " 1";
                        } else {
                            cmd = cmd + " 0";
                        } 

                        jscreen.guiAction = true;
                        dispatcher.start(cmd);
                    }
                }

                isInViewDataArea = false;
                selectedCursor = null;
                whichCursorSide = DEViseCursor.sideNone;
                isMouseDragged = false;

                repaint();

		// Workaround for bug 607.  Note that this means that things
		// will *not* work correctly if you do two consecutive drags
		// while holding down the control key the whole time.
		// RKW 2000-08-07.
		jsc.jsValues.canvas.lastKey = KeyEvent.VK_UNDEFINED;
            }
        }

        public void mouseClicked(MouseEvent event)
        {
            if (DEBUG >= 1) {
                System.out.println(
		  "DEViseCanvas(" + view.viewName +
		    ").ViewMouseListener.mouseClicked()");
            }

            if (view.viewDimension == 3) {
                return;
            }

            if (!isMouseDragged && isInViewDataArea) {
                String cmd = null;
                Point p = event.getPoint();

                if (jsc.jsValues.canvas.lastKey == KeyEvent.VK_SHIFT) {
		    if (activeView.isDrillDown) {
                        cmd = DEViseCommands.SHOW_RECORDS + " " +
			  activeView.getCurlyName() + " " +
			  activeView.translateX(p.x, 2) + " " +
			  activeView.translateY(p.y, 2);
		    }
                } else {
                    DEViseCursor cursor = activeView.getFirstCursor();

                    if (cursor != null && (cursor.isXMovable ||
		      cursor.isYMovable)) {
                        Rectangle loc = cursor.cursorLocInCanvas;

                        int dx = p.x - loc.x - loc.width / 2;
                        int dy = p.y - loc.y - loc.height / 2;

                        cursor.updateCursorLoc(dx, dy, whichCursorSide,
			  true);

                        cmd = DEViseCommands.CURSOR_CHANGED + " {" +
			  cursor.name + "} " + cursor.x + " " + cursor.y + " "
			  + cursor.width + " " + cursor.height;

                        cursor.image = null;
                    }
                }

                if (cmd != null) {
                    jscreen.guiAction = true;
                    dispatcher.start(cmd);
                }

                isInViewDataArea = false;
                selectedCursor = null;
                whichCursorSide = DEViseCursor.sideNone;
                isMouseDragged = false;

                repaint();
            }
        }

        public void mouseEntered(MouseEvent event)
	{
	    if (DEBUG >= 1) {
	        System.out.println("Mouse entered view " + view.curlyName);
	    }
	    _mouseIsInCanvas = true;
	}

        public void mouseExited(MouseEvent event)
	{
	    if (DEBUG >= 1) {
	        System.out.println("Mouse exited view " + view.curlyName);
	    }
	    _mouseIsInCanvas = false;
	}
    }
    // end of class ViewMouseListener

    // start of class ViewMouseMotionListener
    class ViewMouseMotionListener extends MouseMotionAdapter
    {
        // When you drag a mouse, all the following mouse positions are
	// relative to the view where you first start the dragging (so we
	// might have value that is less than zero), and the dragging event
	// is still send back to the view where you first start dragging.

        public void mouseDragged(MouseEvent event)
        {

            if (DEBUG >= 2) {
                System.out.println("DEViseCanvas(" + view.viewName +
		  ").ViewMouseMotionListener.mouseDragged()");
            }

            Point p = event.getPoint();
            isMouseDragged = true;

            if (view.viewDimension == 3 && crystal != null) {
                int dx = p.x - op.x, dy = p.y - op.y;
                op.x = p.x;
                op.y = p.y;

                jsc.viewInfo.updateInfo(activeView.getX(p.x),
		  activeView.getY(p.y));

                if (jsc.jsValues.canvas.lastKey == KeyEvent.VK_ALT) {
                    crystal.translate(dx, dy);
                } else if (jsc.jsValues.canvas.lastKey == KeyEvent.VK_CONTROL) {
                    crystal.scale(dx, dy);
                } else {
                    crystal.rotate(dx, dy);
                }

                jsc.jsValues.canvas.isInteractive = true;
                jsc.jsValues.canvas.sourceCanvas = DEViseCanvas.this;
                repaint();

		// send command to collaborations if necessary
		mouseDragCount++;

		if ((mouseDragCount % 10) == 0) {
		    if (jsc.specialID == -1) {
			String cmd = DEViseCommands.COLLAB_3DVIEW + 
			    " {4} " + activeView.getCurlyName() + 
			    " {" + p.x + "}" + " {" + p.y + "}";
			dispatcher.start(cmd);	
		    }	
		}
                return;
            }

            if (isInViewDataArea) {
                ep.x = activeView.translateX(p.x, 1);
                ep.y = activeView.translateY(p.y, 1);

                jsc.viewInfo.updateInfo(activeView.getX(ep.x),
		  activeView.getY(ep.y));

                if (selectedCursor != null) {

                    DEViseCursor cursor = selectedCursor;

                    int dx = ep.x - sp.x, dy = ep.y - sp.y;

                    cursor.updateCursorLoc(dx, dy, whichCursorSide, false);
                }

                jsc.jsValues.canvas.isInteractive = true;
                jsc.jsValues.canvas.sourceCanvas = DEViseCanvas.this;
                repaint();
            }
        }

        public void mouseMoved(MouseEvent event)
        {
            if (DEBUG >= 2) {
                System.out.println("DEViseCanvas(" + view.viewName +
		  ").ViewMouseMotionListener.mouseMoved()");
            }

	    // Bug fix -- see notes at variable declaration.
	    if (buttonIsDown) {
	        mouseDragged(event);
		return;
	    }

            // the position of this event will be relative to this view
	    // and will not exceed the range of this view, ie, p.x >= 0 &&
	    // p.x < view.width, p.y >= 0 && p.y < view.height

            Point p = event.getPoint();

            if (view.viewDimension == 3 && crystal != null) {
                point.x = p.x;
                point.y = p.y;

               //  setCursor(DEViseUIGlobals.rbCursor); - Ven modified
		   setCursor(DEViseUIGlobals.hdCursor);

                activeView = view;
                jsc.viewInfo.updateInfo(activeView.viewName,
		  activeView.getX(p.x), activeView.getY(p.y));
                if (jscreen.getCurrentView() != activeView) {
                    jscreen.setCurrentView(activeView);
                }

		return;
            }

            checkMousePos(p, true);
        }
    }
    // end of class ViewMouseMotionListener

    //
    // Note: we don't absolutely need this class; it's here just to help
    // debug the problem with input focus sometimes improperly getting
    // taken away from a DEViseCanvas.
    //
    class ViewFocusListener extends FocusAdapter
    {
        public void focusGained(FocusEvent event)
	{
	    if (DEBUG >= 2) {
	        System.out.println("View " + view.curlyName + " gained focus");
	    }
	}

	public void focusLost(FocusEvent event)
	{
	    if (DEBUG >= 2) {
	        System.out.println("View " + view.curlyName + " lost focus");
	        System.out.println("_mouseIsInCanvas = " + _mouseIsInCanvas);
	    }

	    if (_mouseIsInCanvas) {
	        if (DEBUG >= 1) {
	            System.err.println("WARNING: view " + view.viewName +
		      " lost focus while mouse is in it!");
                }
	    }
	}
    } // end of class ViewFocusListener

    // Update the shape of the mouse cursor based on whether the mouse
    // is on a DEVise cursor, etc.
    public synchronized void checkMousePos(Point p, boolean checkDispatcher)
      throws YError
    {
        if (DEBUG >= 3) {
            System.out.println("DEViseCanvas(" + view.viewName +
	      ").checkMousePos(" + p.x + ", " + p.y + ")");
        }

        // initialize value
        whichCursorSide = DEViseCursor.sideNone;
        selectedCursor = null;
        isInViewDataArea = false;
        activeView = null;

        if (checkMousePos(p, view)) { // activeView will not be null
	    Cursor tmpCursor = null;
            if (checkDispatcher && jsc.dispatcher.getStatus() != 0) {
                // dispatcher still busy
                tmpCursor = DEViseUIGlobals.waitCursor;
            } else if (isInViewDataArea && selectedCursor == null) {
                // inside the data area but not within any cursor, you
		// can draw rubber band or get the records at that data point
                 tmpCursor = DEViseUIGlobals.rbCursor; 
            } else if( isInViewDataArea && view.viewDimension == 3){
		 tmpCursor = DEViseUIGlobals.defaultCursor;
	    } else if (isInViewDataArea && selectedCursor != null) {
                switch (whichCursorSide) {
                case DEViseCursor.sideNone:
		    // Not on a cursor, do nothing.
		    break;

                case DEViseCursor.sideMiddle:
		    // Inside a cursor, you can move this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideMiddle");
                    tmpCursor = DEViseUIGlobals.moveCursor;
                    break;

                case DEViseCursor.sideLeft:
		    // On left side of a cursor, you can resize this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideLeft");
                    tmpCursor = DEViseUIGlobals.lrsCursor;
                    break;

                case DEViseCursor.sideRight:
		    // On right side of a cursor, you can resize this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideRight");
                    tmpCursor = DEViseUIGlobals.rrsCursor;
                    break;

                case DEViseCursor.sideTop:
		    // On top side of a cursor, you can resize this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideTop");
                    tmpCursor = DEViseUIGlobals.trsCursor;
                    break;

                case DEViseCursor.sideBottom:
		    // On bottom side of a cursor, you can resize this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideBottom");
                    tmpCursor = DEViseUIGlobals.brsCursor;
                    break;

                case DEViseCursor.sideTopLeft:
		    // On left-top corner of a cursor, you can resize
		    // this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideTopLeft");
                    tmpCursor = DEViseUIGlobals.tlrsCursor;
                    break;

                case DEViseCursor.sideBottomLeft:
		    // On left-bottom corner of a cursor, you can resize
		    // this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideBottomLeft");
                    tmpCursor = DEViseUIGlobals.blrsCursor;
                    break;

                case DEViseCursor.sideTopRight:
		    // On right-top corner of a cursor, you can resize
		    // this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideTopRight");
                    tmpCursor = DEViseUIGlobals.trrsCursor;
                    break;

                case DEViseCursor.sideBottomRight:
		    // 0n right-bottom corner of a cursor, you can resize
		    // this cursor.
                    if (DEBUG >= 3) System.out.println(
		      "whichCursorSide = DEViseCursor.sideBottomRight");
                    tmpCursor = DEViseUIGlobals.brrsCursor;
                    break;

		default:
		    throw new YError("Illegal whichCursorSide value: " +
		      whichCursorSide);
                }
            } else { // inside the view but not within the data area of that view
                tmpCursor = DEViseUIGlobals.defaultCursor;
            }

            setCursor(tmpCursor);

            if (activeView.pileBaseView != null) {
                activeView = activeView.pileBaseView;
            }

            if (jscreen.getCurrentView() != activeView) {
                jscreen.setCurrentView(activeView);
            }

            // show the data at current mouse position
            jsc.viewInfo.updateInfo(activeView.viewName, activeView.getX(p.x), activeView.getY(p.y));

        } else { // activeView is null and all other values will be initialized value before
            whichCursorSide = DEViseCursor.sideNone;
            selectedCursor = null;
            isInViewDataArea = false;
            activeView = null;

	    Cursor tmpCursor = null;
            if (!checkDispatcher || jsc.dispatcher.getStatus() == 0) {
                tmpCursor = DEViseUIGlobals.defaultCursor;
            } else {
                tmpCursor = DEViseUIGlobals.waitCursor;
            }

            setCursor(tmpCursor);

            if (jscreen.getCurrentView() != activeView) {
                jscreen.setCurrentView(activeView);
            }

            jsc.viewInfo.updateInfo();
        }
    }

    // Returns some kind of information about p in terms of what it's
    // on or in.  However, the logic is so complicated I haven't figured out
    // any easy way to summarize it.  
    // It also has side effects of setting activeView, selectedCursor,
    // whichCursorSide, and isInViewDataArea.
    // RKW 2000-05-12.
    public synchronized boolean checkMousePos(Point p, DEViseView v)
    {
        if (!v.inView(p)) {
            return false;
        }

        if (!v.inViewDataArea(p)) {
            if (v.pileBaseView != null) {
		// v is a non-base view in a pile.
                return false;
            } else {
                activeView = v;
                selectedCursor = null;
                whichCursorSide = DEViseCursor.sideNone;
                isInViewDataArea = false;
                return true;
            }
        }

        for (int i = 0; i < v.viewChilds.size(); i++) {
            DEViseView vv = (DEViseView)v.viewChilds.elementAt(i);
            if (checkMousePos(p, vv)) {
                return true;
            }
        }

        for (int i = 0; i < v.viewCursors.size(); i++) {
            DEViseCursor cursor = (DEViseCursor)v.viewCursors.elementAt(i);
            int cursorSide = cursor.inCursor(p);
	    if (cursorSide != DEViseCursor.sideNone) {
                activeView = v;
                whichCursorSide = cursorSide;
                if (DEBUG >= 3) System.out.println(
		  "Setting selected cursor to " + cursor.name);
                selectedCursor = cursor;
                isInViewDataArea = true;
                return true;
            }
        }

        for (int i = 0; i < v.viewPiledViews.size(); i++) {
            DEViseView vv = (DEViseView)v.viewPiledViews.elementAt(i);

            if (checkMousePos(p, vv)) {
                return true;
            }
        }

        if (v.pileBaseView != null) {
	    // v is a non-base view in a pile.
            return false;
        } else {
            activeView = v;
            isInViewDataArea = true;
            selectedCursor = null;
            whichCursorSide = DEViseCursor.sideNone;
            return true;
        }
    }

    // Create "crystal" (used for drawing in 3D views/piles).  Note that
    // in a 3D pile there is only one crystal for the entire pile.
    public void createCrystal()
    {
        if (view.viewDimension != 3) {
            return;
        }

        if (view.viewGDatas.size() == 0) {
            return;
        }

        if (crystal == null) {
            int size = view.viewGDatas.size();
            //float[][] atomPos = new float[size][3];
            //float[][][] bondPos = new float[size][
            //String[] atomName = new String[size];
            Vector aPos = new Vector(size), aName = new Vector(size),
			  aColor = new Vector(size), bPos = new Vector(size),
			  bColor = new Vector(size);
            for (int i = 0; i < size; i++) {
                DEViseGData gdata = (DEViseGData)view.viewGDatas.elementAt(i);
				if (gdata.symbolType == gdata._symSegment) {
                    float[][] pos = new float[2][3];
                    pos[0][0] = gdata.x0;
                    pos[0][1] = gdata.y0;
                    pos[0][2] = gdata.z0;
                    pos[1][0] = gdata.x1;
                    pos[1][1] = gdata.y1;
                    pos[1][2] = gdata.z1;
                    bPos.addElement(pos);
                    bColor.addElement(gdata.color);
                } else {
                    aName.addElement(gdata.string);
                    float[] pos = new float[3];
                    pos[0] = gdata.x0;
                    pos[1] = gdata.y0;
                    pos[2] = gdata.z0;
                    aPos.addElement(pos);
                    aColor.addElement(gdata.color);
                }
            }

            String[] atomName = null;
            float[][] atomPos = null;
            float[][][] bondPos = null;
            Color[] bondColor = null;
            Color[] atomColor = null;
            if (aName.size() > 0) {
                atomName = new String[aName.size()];
                for (int i = 0; i < atomName.length; i++) {
                    atomName[i] = (String)aName.elementAt(i);
                }
            }

            if (aPos.size() > 0) {
                atomPos = new float[aPos.size()][3];
                for (int i = 0; i < atomPos.length; i++) {
                    atomPos[i] = (float[])aPos.elementAt(i);
                }
            }

            if (aColor.size() > 0) {
                atomColor = new Color[aColor.size()];
                for (int i = 0; i < atomColor.length; i++) {
                    atomColor[i] = (Color)aColor.elementAt(i);
                }
            }

            if (bPos.size() > 0) {
                bondPos = new float[bPos.size()][2][3];
                for (int i = 0; i < bondPos.length; i++) {
                    bondPos[i] = (float[][])bPos.elementAt(i);
                }
            }

            if (bColor.size() > 0) {
                bondColor = new Color[bColor.size()];
                for (int i = 0; i < bondColor.length; i++) {
                    bondColor[i] = (Color)bColor.elementAt(i);
                }
            }

            try {
                DEVise3DLCS lcs = new DEVise3DLCS();
                crystal = new DEViseCrystal(canvasDim.width - 10, canvasDim.height - 10, 5, lcs, -1, -1, atomName, atomPos, atomColor, bondPos, bondColor);
            } catch (YException e) {
                jsc.pn(e.getMessage());
                crystal = null;
                return;
            }
        }

        if (view.viewPiledViews.size() > 0) {
            crystal.setSelect();

            for (int i = 0; i < view.viewPiledViews.size(); i++) {
	        DEViseView v = (DEViseView)view.viewPiledViews.elementAt(i);
		for (int j = 0; j < v.viewGDatas.size(); j++) {
		    DEViseGData gdata = (DEViseGData)v.viewGDatas.elementAt(j);
		    if (gdata.symbolType == gdata._symSegment) {
		        crystal.setSelect(gdata.x0, gdata.y0, gdata.z0,
			  gdata.color, true);
                        crystal.setSelect(gdata.x1, gdata.y1, gdata.z1,
			  gdata.color, true);
                    } else {
                        crystal.setSelect(gdata.x0, gdata.y0, gdata.z0,
			  gdata.color, false);
                    }
                }
            }
        }
    }
}

// this class is used to create XOR of part of image
class XORFilter extends RGBImageFilter
{
    Color color = Color.white;
    int red, green, blue;
    int _width, _height;
    int _drawType;

    public static final int typeFilledRect = 1;
    public static final int typeFrame = 2;
    public static final int typeFrameAndDots = 3;

    public XORFilter(Color c, int width, int height, int drawType)
    {
        if (c != null) {
            color = c;
        }

        red = color.getRed() << 16;
        green = color.getGreen() << 8;
        blue = color.getBlue();

	_width = width;
	_height = height;

        //System.out.println("r = " + red + " g = " + green + " b = " + blue);

	if (drawType == typeFilledRect) {
            canFilterIndexColorModel = true;
	}
	_drawType = drawType;
    }

    public int filterRGB(int x, int y, int rgb) throws YError
    {
	int rgbOut = rgb;
	if (_drawType == typeFilledRect) {
            rgbOut = ((rgb & 0xff000000) | ((rgb & 0xff0000) ^ red) |
	      ((rgb & 0xff00) ^ green) | ((rgb & 0xff) ^ blue));
	} else if (_drawType == typeFrame) {
	    if (x < 3 || y < 3 || x > _width - 4 || y > _height - 4) {
                rgbOut = ((rgb & 0xff000000) | ((rgb & 0xff0000) ^ red) |
	          ((rgb & 0xff00) ^ green) | ((rgb & 0xff) ^ blue));
	    }
	} else if (_drawType == typeFrameAndDots) {
	    if (x < 3 || y < 3 || x > _width - 4 || y > _height - 4) {
                rgbOut = ((rgb & 0xff000000) | ((rgb & 0xff0000) ^ red) |
	          ((rgb & 0xff00) ^ green) | ((rgb & 0xff) ^ blue));
	    } else if ((x % 6 == 0) && (y % 6 == 0)) {
                rgbOut = ((rgb & 0xff000000) | ((rgb & 0xff0000) ^ red) |
	          ((rgb & 0xff00) ^ green) | ((rgb & 0xff) ^ blue));
	    }
	} else {
	    throw new YError("Illegal draw type (" + _drawType + ")");
	}

	return rgbOut;
    }
}
