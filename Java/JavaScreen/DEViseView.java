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

// This class holds view properties (such as location, cursors,
// pile information, and so on).  Methods of this class are mostly
// called by the DEViseCanvas class.

// There is one instance of this class for each view in the session.
// (This includes view symbols, piled views, etc.)

// ------------------------------------------------------------------------

// ========================================================================

// DEViseView.java

package JavaScreen;

import  java.awt.*;
import  java.util.*;
import  java.text.*;

// This class represent a image view in DEVise
public class DEViseView
{
    private static final int DEBUG = 0;

    public jsdevisec jsc = null;

    public DEViseCanvas canvas = null;

    public String viewName = null;
    public String curlyName = null;

    // For a top-level view, viewLoc is the location of the view relative
    // to the overall visualization.  For a child view, viewLoc is the
    // location of the view relative to its parent view.
    public Rectangle viewLoc = null;

    // The location of a view relative to the canvas it's drawn in.  For
    // a top-level view, x and y here are always 0; for a child view, they
    // are the same as for viewLoc.
    public Rectangle viewLocInCanvas = null;

    public float viewZ = 0.0f; // for piled views
    public int viewDimension = 0; // number of dimensions
    public int viewBg, viewFg; // background and foreground colors

    // The location of the view's data area relative to the view.
    public Rectangle viewDataLoc = null;

    public float viewDataXMin = 0.0f, viewDataXMax = 0.0f;
    public float viewDataYMin = 0.0f, viewDataYMax = 0.0f;

    // data type could be "real" or "date" or "none"
    public String viewDataXType = null, viewDataYType = null;

    //ven
    public String viewInfoFormatX = null;
    public String viewInfoFormatY = null;

    // Show value meanings: 0 = none; 1 = xy; 2 = x; 3 = y;
    // values are this way for backwards compatibility.
    private int showMouseLoc = 1;
    private boolean showMouseLocX = true;
    private boolean showMouseLocY = true;

    public String viewTitle = null;
    public int viewDTX, viewDTY; // title X and Y location
    public Font viewDTFont = null;

    public DEViseView parentView = null;

    // Base view of a piled view.  Note that this is null in the base view
    // itself.
    public DEViseView pileBaseView = null;

    public Vector viewPiledViews = new Vector();
    public Vector viewChilds = new Vector();
    public Vector viewGDatas = new Vector();
    public Vector viewCursors = new Vector();

    public boolean isRubberBand, isCursorMove, isDrillDown, isKey;

    // data units per pixel in the X and Y dimensions
    public float dataXStep, dataYStep;

    // public float gridx, gridy; // mouse movement grid -- not used

    public boolean isFirstTime = true;

    private boolean _useJmol = false;

    // Used by DEViseCanvas3DJmol to determine whether just the highlight
    // data, or *all* of the data, has changed.
    public boolean _gdataIsDirty = false;

    private static final boolean _debug = false;

    // mouse position multiply factors
    private float factorX = 1.0f;
    private float factorY = 1.0f;

    // label drawing info.
    private int labelXDraw = 0;
    private int labelYDraw = 0;
    private int fontTypeX = 0;
    private int fontTypeY = 0;
    private int fontSizeX = 0;
    private int fontSizeY = 0;
    private int fontBoldX = 0;
    private int fontBoldY = 0;
    private int fontItalicX = 0;
    private int fontItalicY = 0;

    // Smallest size to which we'll shrink font if axis labels don't fit.
    private static int FONT_SHRINK_LIMIT = 8;

    public DEViseView(jsdevisec panel, String pn, String name,
                      String piledname, String title, Rectangle loc, float Z, int dim,
                      int bg, int fg, Rectangle dl, String xt, String yt, float gx, float gy,
                      int rb, int cm, int dd, int ky)
    {
        jsc = panel;

        viewName = name;
        viewTitle = title;
        viewLoc = loc;
        viewZ = Z;
        viewDimension = dim;
        viewBg = bg;
        viewFg = fg;

        viewDataLoc = dl;
        //viewDataLoc.x += DEViseUIGlobals.screenEdge.width;
        //viewDataLoc.y += DEViseGlobals.
        viewDataXType = xt;
        viewDataYType = yt;

        parentView = jsc.jscreen.getView(pn);

        // Note that this will be null for the base view, because in this
        // constructor the DEViseScreen object doesn't know about this
        // view yet.
        pileBaseView = jsc.jscreen.getView(piledname);

        viewLocInCanvas = getLocInCanvas();

        // gridx = gx; // mouse movement grid -- not used
        // gridy = gy; // mouse movement grid -- not used

        isRubberBand = (rb == 1);

        isCursorMove = (cm == 1);

        isDrillDown = (dd == 1);

        isKey = (ky == 1);

        curlyName = "{" + viewName + "}";
    }

    protected void finalize() {
        if (_debug) {
            System.out.println("DEViseView(" + viewName + ").finalize()");
        }
        removeAllGData();
    }

    // Returns view name enclosed by curly brackets.
    public String getCurlyName()
    {
        return curlyName;
    }

    public void setShowMouseLoc(int showMouseLocVal) {
        showMouseLoc = showMouseLocVal;
        showMouseLocX = ((showMouseLoc == 1) || (showMouseLoc == 2));
        showMouseLocY = ((showMouseLoc == 1) || (showMouseLoc == 3));
    }

    public boolean getUseJmol() {
        return _useJmol;
    }

    public void setUseJmol(boolean useJmol) {
        // Make sure the use of Jmol is consistent within a pile.
        if (pileBaseView != null) {
            if (pileBaseView.getUseJmol() != useJmol) {
                System.err.println("ERROR: View " + viewName +
                                   " useJmol value inconsistent with pile base view " +
                                   pileBaseView.viewName);
                return;
            }
        }

        _useJmol = useJmol;
    }

    // Add a child view to this view.
    public void addChild(DEViseView view) throws YError
    {
        if (view != null) {
            if (view.parentView != this) {
                throw new YError("Adding child view (" + view.viewName +
                                 ") to wrong parent(" + viewName + ")");
            }

            if (viewChilds.contains(view)) {
                throw new YError("Child view " + view.viewName +
                                 " is already in parent (" + viewName + ")");
            } else {
                viewChilds.addElement(view);
            }
        }
    }

    // Add a view to the base view of a pile.
    public void addPiledView(DEViseView view) throws YError
    {
        if (pileBaseView != null) {
            throw new YError("Adding piled view (" + view.viewName +
                             ") to non-base view (" + viewName + ")");
        }

        if (view != null) {
            if (view.pileBaseView != this) {
                throw new YError("Adding piled view (" + view.viewName +
                                 ") to wrong base view (" + viewName + ")");
            }
            if (viewPiledViews.contains(view)) {
                throw new YError("Pile " + viewName +
                                 "already contains view " + view.viewName);
            }

            for (int i = 0; i < viewPiledViews.size(); i++) {
                DEViseView v = (DEViseView)viewPiledViews.elementAt(i);
                if (view.viewZ < v.viewZ) {
                    viewPiledViews.insertElementAt(view, i);
                    return;
                }
            }

            viewPiledViews.addElement(view);
        }
    }

    // Add a cursor to this view.  Returns true iff cursor exists and is
    // not already in this view.
    public boolean addCursor(DEViseCursor cursor) throws YError
    {
        if (DEBUG >= 2) {
            System.out.println("DEViseView(" + viewName + ").addCursor(" +
                               cursor.name + ")");
        }

        if (cursor == null) {
            return false;
        }

        if (cursor.parentView != this) {
            throw new YError("Adding cursor (" + cursor.name +
                             ") to wrong view (" + viewName + ")");
        }

        for (int i = 0; i < viewCursors.size(); i++) {
            DEViseCursor c = (DEViseCursor)viewCursors.elementAt(i);
            if (DEBUG >= 4) {
                System.out.println("    Checking cursor " + c.name);
            }
            if (c.name.equals(cursor.name)) {
                if (c.isSame(cursor)) {
                    return false;
                } else {
                    if (DEBUG >= 4) {
                        System.out.println("  Removing old cursor: " +
                                           ((DEViseCursor)viewCursors.elementAt(i)).name +
                                           " from view " + viewName);
                    }
                    viewCursors.removeElementAt(i);
                }
            }
        }

        cursor.image = null;

        viewCursors.addElement(cursor);

        return true;
    }

    // Add a GData record to this view.
    public void addGData(DEViseGData gdata)
    {
        // Note: I'm not checking GData.parentView here for speed.
        // RKW 2000-05-3.
        if (gdata != null) {
            viewGDatas.addElement(gdata);
            _gdataIsDirty = true;
        }
    }

    // Remove a child view from this view.
    public void removeChild(DEViseView view)
    {
        if (view != null) {
            if (canvas != null) {
                if (canvas.activeView == view) {
                    canvas.activeView = null;
                }
            }

            viewChilds.removeElement(view);
        }
    }

    // Removed a piled view from its base view.
    public void removePiledView(DEViseView view) throws YError
    {
        if (pileBaseView != null) {
            throw new YError("Removing piled view from non-base view (" +
                             viewName + ")");
        }
        if (view != null) {
            viewPiledViews.removeElement(view);
        }
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Changes here are part of the (not totally complete) fix for bug
    // 968 (improper handling of cursors that go entirely outside the
    // destination view's visual filter).  The problem was that, when
    // a view is redrawn, the cursors in that view were removed (and if
    // the cursor was just getting moved withing the view, a new
    // DEViseCursor object corresponding to the same cursor on the
    // server would get created).  However, if the cursor went entirely
    // outside of the view's visual filter, no new DEViseCursor object
    // would get created in the client, because the server wouldn't
    // tell the client to draw the cursor.  So the fix is that, when the
    // view is redrawn, we just temporarily hide the cursors in the view,
    // so that getFirstCursor() still finds a cursor.  This allows the
    // user to move the cursor back into the destination view with a
    // single mouse click.  The old (hidden) DEVise cursor object is
    // never unhidden -- if and when the cursor is moved back within the
    // view's visual filter, a new DEViseCursor object will be added
    // with the addCursor() method, and the old (hidden) DEViseCursor
    // object will actually be removed from the cursor list at that time.
    // The limitation of the fix is that a cursor must be at least partially
    // within the destination view when the destination view is created.
    // If the cursor is entirely outside of the destination view's visual
    // filter at view creation time, the cursor will never be drawn, and
    // so the client will never find out about it.  (A total fix to
    // this bug would require changes on the server side, but I figure
    // this is good enough, since we can make sure any sessions start
    // out with all cursors visible.)  wenger 2008-07-15
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Hide the named cursor from this view; returns true iff the cursor
    // is in this view.
    public boolean hideCursor(String name)
    {
        if (DEBUG >= 2) {
            System.out.println("DEViseView(" + viewName + ").hideCursor(" +
                               name + ")");
        }

        if (name != null) {
            for (int i = 0; i < viewCursors.size(); i++) {
                DEViseCursor cursor = (DEViseCursor)viewCursors.elementAt(i);
                if (cursor.name.equals(name)) {
                    cursor.setInvisible();
                    return true;
                }
            }

            return false;
        } else {
            return false;
        }
    }

    // Remove all GData records from this view.
    public void removeAllGData()
    {
        if (_debug) {
            System.out.println("DEViseView(" + viewName +
                               ").removeAllGData()");
        }
        viewGDatas = new Vector();
    }

    // Remove all cursors from this view.
    public void removeAllCursor()
    {
        viewCursors.removeAllElements();
    }

    // Remove all child views from this view.
    public void removeAllChild()
    {
        if (canvas != null) {
            if (canvas.activeView != this) {
                canvas.activeView = null;
            }
        }

        viewChilds.removeAllElements();
    }

    // Set view foreground and background colors.
    public void setColors(int foreground, int background)
    {
        viewFg = foreground;
        viewBg = background;
    }

    // Paint the axis labels for this view.
    public void paintAxisLabels(Graphics gc, boolean isChildView)
    {
        if (DEBUG >= 1) {
            System.out.println("DEViseView(" + viewName +
                               ").printAxisLabels(" + isChildView + ")");
        }

        // Only draw axis labels for the base view of a pile.
        if (pileBaseView != null) return;

        Color labelColor = new Color(viewFg);
        if (DEBUG >= 2) {
            System.out.println("  labelColor: " + labelColor);
        }
        gc.setColor(labelColor);

        if (labelYDraw == 1) {

            int tickSpacing = 40;
            if (viewDataLoc.height < 100) {
                tickSpacing = 20;
            } else if (viewDataLoc.height > 600) {
                tickSpacing = 80;
            } else if (viewDataLoc.height > 400) {
                tickSpacing = 60;
            }
            if ((viewDataYType.toLowerCase()).equals("real")) {
                double[] ticks = calculateTickLocs(viewDataYMin * factorY,
                                                   viewDataYMax * factorY, viewDataLoc.height,
                                                   tickSpacing * dataYStep * factorY);
                for (int index = 0; index < ticks.length; index++) {
                    drawYAxisTick(gc, ticks[index]);
                }
            } else { // for "date"
                //TEMP -- this doesn't work -- see date_on_y_axis.ds
                /*TEMP
                            int currentYPos = 0;
                            float currentY = 0;
                            String labelY = null;
                            float displayY = 0;

                        while (currentYPos >= dataLoc.y + 20) {
                            currentY = viewDataYMin + (currentYPos - dataLoc.x) *  dataYStep;
                            displayY = currentY * factorY;
                            labelY = formatYValue(displayY);
                            if (DEBUG >= 2) {
                                System.out.println("  Drawing Y label: " + labelY);
                            }

                            gc.drawString(labelY, dataLoc.x-40, currentYPos+5);
                            gc.drawLine(dataLoc.x-5, currentYPos, dataLoc.x-2, currentYPos);
                            currentYPos -= 40;
                        }
                TEMP*/
            }
        }

        if (labelXDraw == 1) {

            if ((viewDataXType.toLowerCase()).equals("real")) {
                int tickSpacing = 100;
                if (viewDataLoc.width < 250) {
                    tickSpacing = 50;
                } else if (viewDataLoc.width > 1000) {
                    tickSpacing = 150;
                }
                double ticks[] = calculateTickLocs(viewDataXMin * factorX,
                                                   viewDataXMax * factorX, viewDataLoc.width,
                                                   tickSpacing * dataXStep * factorX);
                for (int index = 0; index < ticks.length; index++) {
                    drawXAxisTick(gc, ticks[index]);
                }

            } else { // for "date"
                String labelX = null;
                float displayX = 0;

                displayX = viewDataXMin * factorX;
                labelX = formatXValue(displayX);
                drawXAxisTick(gc, viewDataLoc.x, labelX);

                displayX = viewDataXMax * factorX;
                labelX = formatXValue(displayX);
                drawXAxisTick(gc, viewDataLoc.x + viewDataLoc.width, labelX);
            }
        }
    }

    /** -------------------------------------------------------------------
     * Calculate the locations (in terms of data) at which axis ticks
     * should be drawn.
     * @param The minimum data value for the relevant axis.
     * @param The maximum data value for the relevant axis.
     * @param The number of pixels on the relevant axis.
     * @param The preferred number of data units between ticks.
     * @return An array containing data values at which ticks should
     * be drawn.
     */
    private double[] calculateTickLocs(double dataMin, double dataMax,
                                       int pixels, double dataStepSize)
    {
        if (DEBUG >= 1) {
            System.out.println("DEViseView(" + viewName +
                               ").calculateTickLocs(" + dataMin +
                               ", " + dataMax + ",\n  " + pixels + ", " + dataStepSize + ")");
        }

        // Note: the code below doesn't really work very well for negative
        // step sizes, so this seems to be the easiest way to handle it.
        // wenger, 2003-02-27.
        if (dataStepSize < 0.0) {
            double[] ticks = calculateTickLocs(-dataMin, -dataMax, pixels,
                                               -dataStepSize);
            for (int index = 0; index < ticks.length; index++) {
                ticks[index] = -ticks[index];
            }
            return ticks;
        }

        dataStepSize = round2Nice(dataStepSize);
        if (DEBUG >= 2) {
            System.out.println("Rounded step size: " + dataStepSize);
        }

        int maxTickCount = (int)((dataMax - dataMin) / dataStepSize) + 1;
        double[] ticks = new double[maxTickCount];

        double currentTickVal = round2Step(dataMin, dataStepSize, true);
        int tickNum = 0;
        while (currentTickVal <= dataMax) {
            ticks[tickNum++] = currentTickVal;
            currentTickVal += dataStepSize;
            currentTickVal = round2Step(currentTickVal, dataStepSize, false);
        }

        // We may not generate the full maxTickCount ticks.
        if (ticks.length > tickNum) {
            int tickCount = tickNum;
            double[] tmpTicks = new double[tickCount];
            for (tickNum = 0; tickNum < tickCount; tickNum++) {
                tmpTicks[tickNum] = ticks[tickNum];
            }
            ticks = tmpTicks;
        }

        if (DEBUG >= 2) {
            System.out.println("  Ticks:");
            for (int index = 0; index < ticks.length; index++) {
                System.out.println("    " + ticks[index]);
            }
        }

        return ticks;
    }

    /** -------------------------------------------------------------------
     * Draw an X-axis tick and label at the given data value.
     * @param The Graphics object to draw to.
     * @param The value at which the tick should be drawn.
     */
    private void drawXAxisTick(Graphics gc, double value)
    {
        if (DEBUG >= 2) {
            System.out.println("  Drawing X label: " + value);
        }

        // Get the string for labeling this tick.
        String label = formatXValue(value);

        // Convert the tick's data value to pixels, relative to the
        // view origin.
        int pixelX = data2PixelX(value / factorX, false);

        drawXAxisTick(gc, pixelX, label);
    }

    /** -------------------------------------------------------------------
     * Draw the given X-axis tick mark and label.
     * @param The Graphics object to draw to.
     * @param The X location, in pixels relative to the view origin, where
     * the tick should be drawn.
     * @param The string that should be used to label the tick.
     */
    private void drawXAxisTick(Graphics gc, int pixelX, String label)
    {
        gc.setFont(DEViseFonts.getFont(fontSizeX, fontTypeX, fontBoldX,
                                       fontItalicX));
        drawXAxisTick(gc, pixelX, label, fontSizeX);
    }

    /** -------------------------------------------------------------------
     * Draw the given X-axis tick mark and label.
     * @param The Graphics object to draw to.
     * @param The X location, in pixels relative to the view origin, where
     * the tick should be drawn.
     * @param The string that should be used to label the tick.
     * @param The font size in points.
     */
    private void drawXAxisTick(Graphics gc, int pixelX, String label,
                               int fontSize)
    {
        if (DEBUG >= 2) {
            System.out.println("  Drawing X label: " + label +
                               " at " + pixelX);
        }

        int pixelY = viewDataLoc.y + viewDataLoc.height;

        // Align the label based on the string size.
        int width = gc.getFontMetrics().stringWidth(label);
        int height = gc.getFontMetrics().getHeight();
        int labelX = pixelX - width / 2 + 1;
        int labelY = pixelY + height;

        // Make sure we're within the view.
        if (labelX < 0) {
            labelX = 0;
        }

        int pastRightEdge = labelX + width - viewLoc.width;
        if (pastRightEdge > 0) {
            labelX -= pastRightEdge;
        }

        if (labelY > viewLoc.height) {
            int newFontSize = fontSize - 2;
            if (newFontSize < FONT_SHRINK_LIMIT) {
                labelY = viewLoc.height;
            } else {
                gc.setFont(DEViseFonts.getFont(newFontSize, fontTypeX,
                                               fontBoldX, fontItalicX));
                drawXAxisTick(gc, pixelX, label, newFontSize);
                return;
            }
        }

        // Translate coordinates to the canvas origin.
        pixelX += viewLocInCanvas.x;
        pixelY += viewLocInCanvas.y;
        labelX += viewLocInCanvas.x;
        labelY += viewLocInCanvas.y;

        // Draw the label and tick.
        gc.drawString(label, labelX, labelY);
        gc.drawLine(pixelX, pixelY, pixelX, pixelY + 3);
    }

    /** -------------------------------------------------------------------
     * Draw an Y-axis tick and label at the given data value.
     * @param The Graphics object to draw to.
     * @param The value at which the tick should be drawn.
     */
    private void drawYAxisTick(Graphics gc, double value)
    {
        if (DEBUG >= 2) {
            System.out.println("  Drawing Y label: " + value);
        }

        // Get the string for labeling this tick.
        String label = formatYValue(value);

        // Convert the tick's data value to pixels, relative to the
        // view origin.
        int pixelY = data2PixelY(value / factorY, false);

        drawYAxisTick(gc, pixelY, label);
    }

    /** -------------------------------------------------------------------
     * Draw the given Y-axis tick mark and label.
     * @param The Graphics object to draw to.
     * @param The Y location, in pixels relative to the view origin, where
     * the tick should be drawn.
     * @param The string that should be used to label the tick.
     * @param The font size in points.
     */
    private void drawYAxisTick(Graphics gc, int pixelY, String label)
    {
        gc.setFont(DEViseFonts.getFont(fontSizeY, fontTypeY, fontBoldY,
                                       fontItalicY));
        drawYAxisTick(gc, pixelY, label, fontSizeY);
    }

    /** -------------------------------------------------------------------
     * Draw the given Y-axis tick mark and label.
     * @param The Graphics object to draw to.
     * @param The Y location, in pixels relative to the view origin, where
     * the tick should be drawn.
     * @param The string that should be used to label the tick.
     * @param The font size in points.
     */
    private void drawYAxisTick(Graphics gc, int pixelY, String label,
                               int fontSize)
    {
        if (DEBUG >= 2) {
            System.out.println("  Drawing Y label: " + label +
                               " at " + pixelY);
        }

        int pixelX = viewDataLoc.x;

        // Align the label based on the string size.
        int width = gc.getFontMetrics().stringWidth(label);
        int height = gc.getFontMetrics().getHeight();
        int labelX = pixelX - width - 7;
        // 0.35 is empirically-derived kludge. RKW 2002-07-30.
        int labelY = pixelY + (int)(height * 0.35);

        // Make sure we're within the view.
        if (labelX < 0) {
            int newFontSize = fontSize - 2;
            if (newFontSize < FONT_SHRINK_LIMIT) {
                labelX = 0;
            } else {
                gc.setFont(DEViseFonts.getFont(newFontSize, fontTypeY,
                                               fontBoldY, fontItalicY));
                drawYAxisTick(gc, pixelY, label, newFontSize);
                return;
            }
        }

        if (labelY - height < 0) {
            // 0.8 is empirically-derived kludge. RKW 2002-07-30.
            labelY = (int)(height * 0.8);
        }

        if (labelY > viewLoc.height) {
            labelY = viewLoc.height;
        }

        // Translate coordinates to the canvas origin.
        pixelX += viewLocInCanvas.x;
        labelX += viewLocInCanvas.x;
        pixelY += viewLocInCanvas.y;
        labelY += viewLocInCanvas.y;

        // Draw the label and tick.
        gc.drawString(label, labelX, labelY);
        gc.drawLine(pixelX - 5, pixelY, pixelX - 2, pixelY);
    }

    // Get the canvas corresponding to this view (note that if this view
    // is a child view or a non-base piled view, the canvas returned is
    // not "owned" by this view).
    public DEViseCanvas getCanvas()
    {
        if (canvas == null) {
            if (parentView == null) {
                if (pileBaseView == null) { // this is a top view, but the canvas for it has not yet been set
                    return null;
                } else {
                    return pileBaseView.getCanvas();
                }
            } else {
                return parentView.getCanvas();
            }
        } else {
            return canvas;
        }
    }

    // Returns the location of this view relative to its canvas.
    // Relative to upper left corner of canvas?
    public Rectangle getLocInCanvas()
    {
        if (canvas == null) {
            Rectangle loc = null;

            if (parentView == null) {
                if (pileBaseView == null) {
                    // this is a top view, but the canvas for it has not yet been set
                    return new Rectangle(0, 0, viewLoc.width, viewLoc.height);
                } else {
                    loc = pileBaseView.getLocInCanvas();
                }
            } else {
                loc = parentView.getLocInCanvas();
                loc.x = loc.x + viewLoc.x;
                loc.y = loc.y + viewLoc.y;
                loc.width = viewLoc.width;
                loc.height = viewLoc.height;
            }

            return loc;
        } else {
            return new Rectangle(0, 0, viewLoc.width, viewLoc.height);
        }
    }

    // Returns the location of this view relative to the entire JavaScreen.
    // Relative to upper left corner of screen?
    public Rectangle getLocInScreen()
    {
        DEViseCanvas canvas = getCanvas();
        Rectangle loc = viewLocInCanvas;

        if (canvas == null) {
            DEViseView v = this;
            while (v.parentView != null) {
                v = v.parentView;
            }
            return new Rectangle(loc.x + v.viewLoc.x, loc.y + v.viewLoc.y,
                                 viewLoc.width, viewLoc.height);
        } else {
            return new Rectangle(loc.x + canvas.view.viewLoc.x,
                                 loc.y + canvas.view.viewLoc.y, viewLoc.width, viewLoc.height);
        }
    }

    // Update the data range of the given axis.
    void updateDataRange(String axis, float min, float max,
                         String format, float factor, int label,
                         int type, int size, int bold, int italic)
    throws YError
    {
        if (axis.equals("X")) {
            viewDataXMin = min;
            viewDataXMax = max;
            viewInfoFormatX = format;
            //  viewInfoFormatX = "-";

            dataXStep = 0.0f;
            if (viewDataLoc.width > 0) {
                dataXStep = (viewDataXMax - viewDataXMin) / (
                                viewDataLoc.width - 1);
            }
            factorX = factor;
            labelXDraw = label;
            fontTypeX = type;
            fontSizeX = size;
            fontBoldX = bold;
            fontItalicX = italic;

        } else if (axis.equals("Y")) {
            viewDataYMin = min;
            viewDataYMax = max;
            viewInfoFormatY = format;
            //  viewInfoFormatY = "-";

            dataYStep = 0.0f;
            if (viewDataLoc.height > 0) {
                dataYStep = (viewDataYMax - viewDataYMin) /
                            (viewDataLoc.height - 1);
            }
            factorY = factor;
            labelYDraw = label;
            fontTypeY = type;
            fontSizeY = size;
            fontBoldY = bold;
            fontItalicY = italic;
        } else {
            throw new YError("Illegal axis type (" + axis + ")");
        }

    }

    // --------------------------------------------------------------------
    // Convert mouse X coordinate (in pixels) to a String.
    // x is relative to this view's canvas
    public String getX(int x)
    {
        if(!showMouseLocX || viewDimension == 3 ||
                (viewInfoFormatX != null && viewInfoFormatX.equals("-"))) {
            return "";
        }
        Rectangle loc = viewLocInCanvas;

        if (x < loc.x || x > (loc.x + loc.width)) {
            return "";
        }

        x -= loc.x;

        float x0 = (float)pixel2DataX(x, true);

        return formatXValue(x0);
    }

    // --------------------------------------------------------------------
    // Convert mouse Y coordinate (in pixels) to a String.
    // y is relative to this view's canvas
    public String getY(int y)
    {
        if(!showMouseLocY || viewDimension == 3 ||
                (viewInfoFormatY != null && viewInfoFormatY.equals("-"))) {
            return "";
        }
        Rectangle loc = viewLocInCanvas;

        if (y < loc.y || y > (loc.y + loc.height)) {
            return "";
        }

        y -= loc.y;

        float y0 = (float)pixel2DataY(y, true);

        return formatYValue(y0);
    }

    // --------------------------------------------------------------------
    // Convert X pixel location to data value.
    // Pixel X is relative to the view origin.
    public double pixel2DataX(int pixelX, boolean useMultFactor)
    {
        if (pileBaseView != null) {
            return pileBaseView.pixel2DataX(pixelX, useMultFactor);
        } else {
            double dataX = (pixelX - viewDataLoc.x) * dataXStep + viewDataXMin;
            if (useMultFactor) {
                dataX *= factorX;
            }
            return dataX;
        }
    }

    // --------------------------------------------------------------------
    // Convert Y pixel location to data value.
    // Pixel Y is relative to the view origin.
    public double pixel2DataY(int pixelY, boolean useMultFactor)
    {
        if (pileBaseView != null) {
            return pileBaseView.pixel2DataY(pixelY, useMultFactor);
        } else {
            double dataY = viewDataYMax - (pixelY - viewDataLoc.y) * dataYStep;
            if (useMultFactor) {
                dataY *= factorY;
            }
            return dataY;
        }
    }

    // --------------------------------------------------------------------
    // Convert X data value to pixel location.
    // Pixel X is relative to the view origin.
    public int data2PixelX(double dataX, boolean useMultFactor)
    {
        if (pileBaseView != null) {
            return pileBaseView.data2PixelX(dataX, useMultFactor);
        } else {
            if (useMultFactor) {
                dataX /= factorX;
            }
            int pixelX = (int)Math.round((dataX - viewDataXMin) /
                                         dataXStep + viewDataLoc.x);
            return pixelX;
        }
    }

    // --------------------------------------------------------------------
    // Convert Y data value to pixel location.
    // Pixel Y is relative to the view origin.
    public int data2PixelY(double dataY, boolean useMultFactor)
    {
        if (pileBaseView != null) {
            return pileBaseView.data2PixelY(dataY, useMultFactor);
        } else {
            if (useMultFactor) {
                dataY /= factorY;
            }
            int pixelY = (int)Math.round((viewDataYMax - dataY) /
                                         dataYStep + viewDataLoc.y);
            return pixelY;
        }
    }

    // --------------------------------------------------------------------
    // check whether or not the point (relative to this view's canvas) is within the view area
    public boolean inView(Point p)
    {
        Rectangle loc = viewLocInCanvas;

        //jsc.pn("view name" + viewName + " = p " + p.x + " " + p.y + "  loc " + loc.x + " " + loc.y + " " + loc.width + " " + loc.height + "  viewloc" + viewLoc.x + " " + viewLoc.y);
        if (p.x >= loc.x && p.y >= loc.y && p.x <= loc.x + loc.width && p.y <= loc.y + loc.height) {
            return true;
        } else {
            return false;
        }
    }

    // --------------------------------------------------------------------
    // check whether or not the point (relative to this view's canvas) is
    // within the view's data area
    public boolean inViewDataArea(Point p)
    {
        Rectangle loc = viewLocInCanvas;

        int x0 = p.x - loc.x - viewDataLoc.x, y0 = p.y - loc.y - viewDataLoc.y;

        if (x0 >= 0 && y0 >= 0 && x0 <= viewDataLoc.width && y0 <= viewDataLoc.height) {
            return true;
        } else {
            return false;
        }
    }

    // --------------------------------------------------------------------
    // ADD COMMENT -- what is this doing?
    public int translateX(int x, int mode)
    {
        return translateX(x, mode, 0);
    }

    // --------------------------------------------------------------------
    // ADD COMMENT -- what is this doing?
    public int translateX(int x, int mode, int width)
    {
        Rectangle loc = viewLocInCanvas;

        if (mode == 1) { // adjust position x so it is within the range
            // of data area of this view
            if (x < loc.x + viewDataLoc.x) {
                // Off the left
                x = loc.x + viewDataLoc.x;
            } else if ((x + width) >
                       (loc.x + viewDataLoc.x + viewDataLoc.width - 1)) {
                // Off the right
                x = loc.x + viewDataLoc.x + viewDataLoc.width - 1 - width;
            }
        } else if (mode == 2) { // adjust position x so it is relative
            // to this view
            x = x - loc.x;
        }

        return x;
    }

    // --------------------------------------------------------------------
    // ADD COMMENT -- what is this doing?
    public int translateY(int y, int mode)
    {
        return translateY(y, mode, 0);
    }

    // --------------------------------------------------------------------
    // ADD COMMENT -- what is this doing?
    public int translateY(int y, int mode, int height)
    {
        Rectangle loc = viewLocInCanvas;

        if (mode == 1) { // adjust position y so it is within the range
            // of data area of this view
            if (y < loc.y + viewDataLoc.y) {
                // Off the top
                y = loc.y + viewDataLoc.y;
            } else if ((y + height) >
                       (loc.y + viewDataLoc.y + viewDataLoc.height - 1)) {
                // Off the bottom
                y = loc.y + viewDataLoc.y + viewDataLoc.height - 1 - height;
            }
        } else if (mode == 2) { // adjust position y so it is relative
            // to this view
            y = y - loc.y;
        }

        return y;
    }

    // --------------------------------------------------------------------
    // Get this first cursor in this view or this view's pile.  Note that
    // this method should only be called on a base view.
    public DEViseCursor getFirstCursor() throws YError
    {
        if (_debug) {
            System.out.println("DEViseView(" + viewName +
                               ").getFirstCursor()");
        }

        if (pileBaseView != null) {
            throw new YError("Calling getFirstCursor() on non-base view (" +
                             viewName + ")");
        }

        DEViseCursor cursor = doGetFirstCursor();

        if (_debug) {
            String cursorName = (cursor != null) ? cursor.name : "null";
            System.out.println("  getFirstCursor() returns: " + cursorName);
        }

        return cursor;
    }

    // --------------------------------------------------------------------
    private DEViseCursor doGetFirstCursor()
    {
        if (_debug) {
            System.out.println("DEViseView(" + viewName +
                               ").doGetFirstCursor()");

        }

        // Get any cursor in this view.
        if (viewCursors.size() > 0) {
            DEViseCursor cursor = (DEViseCursor)viewCursors.elementAt(0);
            return cursor;
        }

        // Return if this is a non-base view.
        // Note: we shouldn't really need to do this, because if this is a
        // non-base view viewPiledViews.size(); however, doing this seems to
        // avoid some lockups (maybe thread problems).  RKW 2000-08-07.
        if (pileBaseView != null) {
            return null;
        }

        // Check cursors in child views of this view.
        for (int i = 0; i < viewPiledViews.size(); i++) {
            DEViseView v = (DEViseView)viewPiledViews.elementAt(i);
            DEViseCursor cursor = v.doGetFirstCursor();
            if (cursor != null) {
                return cursor;
            }
        }

        return null;
    }

    // --------------------------------------------------------------------
    // round up the steps on axis labels
    // Round to a "nice" value.
    private static double round2Nice(double value)
    {
        if (DEBUG >= 3) {
            System.out.println("round2Nice(" + value + ")");
        }

        if (value < 0.0) {
            return -1.0 * round2Nice(-value);
        }

        double log = Math.floor(Math.log(value) / Math.log(10) + 0.0001);
        if (DEBUG >= 3) {
            System.out.println("  log = " + log);
        }

        double factor = Math.pow(10.0d, log);
        double temp = value / factor;
        if (DEBUG >= 3) {
            System.out.println("  temp = " + temp);
        }

        if (temp >= 7.5) {
            value = (double)(10.0d * factor);
        } else if (temp >= 3.5) {
            value = (double)(5.0d * factor);
        } else if (temp >= 1.5) {
            value = (double)(2.0d * factor);
        } else {
            value = (double)(1.0d * factor);
        }

        if (DEBUG >= 3) {
            System.out.println("  round2Nice() returns " + value);
        }

        return value;
    }

    // --------------------------------------------------------------------
    // Round the value to the nearest multiple of step; if roundUp is true,
    // the result will be not less than val.
    public static double round2Step(double val, double step, boolean roundUp)
    {
        if (DEBUG >= 3) {
            System.out.println("round2Step(" + val + ", " + step + ", " +
                               roundUp + ")");
        }

        long factor = Math.round(val / step);
        if (DEBUG >= 3) {
            System.out.println("  factor = " + factor);
        }

        double roundedVal = factor * step;
        if (DEBUG >= 3) {
            System.out.println("  roundedVal = " + roundedVal);
        }

        // Make sure zero is really zero.
        if (Math.abs(val / step) < 0.001) {
            roundedVal = 0.0d;
        }

        if (roundUp && roundedVal < val) {
            roundedVal += step;
        }

        if (DEBUG >= 3) {
            System.out.println("  round2Step() returns " + roundedVal);
        }

        return roundedVal;
    }

    // --------------------------------------------------------------------
    // get date label according to cftime format
    public String getDateLabel(float dataVal, String format)
    {
        if (DEBUG >= 2) {
            System.out.println("DEViseView.getDateLabel(" + dataVal +
                               ", " + format);
        }

        dataVal *= 1000.0f; // convert to milliseconds?
        Date date = new Date((long)dataVal);
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        int i = 0;
        char c;
        String result = new String("");

        while (i < format.length()) {
            String st = "";
            c = format.charAt(i);

            if (c == '%') {
                i++;
                c = format.charAt(i);

                if (c == 'b') {
                    int mon = cal.get(Calendar.MONTH);

                    switch (mon+1) {
                    case 1:
                        st = "Jan";
                        break;
                    case 2:
                        st = "Feb";
                        break;
                    case 3:
                        st = "March";
                        break;
                    case 4:
                        st = "April";
                        break;
                    case 5:
                        st = "May";
                        break;
                    case 6:
                        st = "June";
                        break;
                    case 7:
                        st = "July";
                        break;
                    case 8:
                        st = "Aug";
                        break;
                    case 9:
                        st = "Sep";
                        break;
                    case 10:
                        st = "Oct";
                        break;
                    case 11:
                        st = "Nov";
                        break;
                    case 12:
                        st = "Dec";
                        break;
                    }
                } else if (c == 'd') {
                    st = new Integer(cal.get(Calendar.DAY_OF_MONTH)).toString();
                } else if (c == 'Y') {
                    st = new Integer(cal.get(Calendar.YEAR)).toString();
                } else if (c == 'T') {
                    st = cal.get(Calendar.HOUR_OF_DAY) + ":"
                         + cal.get(Calendar.MINUTE) + ":"
                         + cal.get(Calendar.SECOND);
                } else if (c == 'm') {
                    st = new Integer(cal.get(Calendar.MONTH)+1).toString();
                } else if (c == 'H') {
                    st = new Integer(cal.get(Calendar.HOUR_OF_DAY)).toString();
                } else if (c == 'M') {
                    st = new Integer(cal.get(Calendar.MINUTE)).toString();
                } else if (c == ':') {
                    st = ":";
                } else if (c == ' ') {
                    st = " ";
                } else if (c == '-') {
                    st = "-";
                }
            } else {
                st = String.valueOf(c);
            }

            result = result.concat(st);
            i++;
        }

        if (DEBUG >= 2) {
            System.out.println("  DEViseView.getDateLabel returns " + result);
        }

        return result;
    }

    // --------------------------------------------------------------------
    // Convert a X-axis data value to a properly-formatted string for
    // mouse location display or axis labeling.
    private String formatXValue(double dataX) {
        return formatDataValue(dataX, viewDataXType, viewInfoFormatX);
    }

    // --------------------------------------------------------------------
    // Convert a Y-axis data value to a properly-formatted string for
    // mouse location display or axis labeling.
    private String formatYValue(double dataY) {
        return formatDataValue(dataY, viewDataYType, viewInfoFormatY);
    }

    // --------------------------------------------------------------------
    // Format a data value of the given type according to the given
    // format string.
    private String formatDataValue(double dataVal, String dataType,
                                   String dataFormat) {
        if (dataFormat.equals("-")) {
            return "";
        } else if ((dataType.toLowerCase()).equals("date")) {
            return getDateLabel((float)dataVal, dataFormat);
        } else {
            return DEViseViewInfo.viewParser((float)dataVal, dataFormat);
        }
    }
}
