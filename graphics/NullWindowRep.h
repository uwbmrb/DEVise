/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-1995
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  $Id$

  $Log$
  Revision 1.6  1996/12/30 23:51:09  andyt
  First version with support for Embedded Tcl/Tk windows. WindowRep classes
  now have member functions for creating and destroying Tk windows.
  Interface to the EmbeddedTk server is in ETkIfc.h

  Revision 1.5  1996/12/15 20:22:29  wenger
  Changed pointSize in SetFont() from tenths of points to points.

  Revision 1.4  1996/12/11 18:05:36  wenger
  Arc() method now works in PSWindowRep class; put SetSmallFont() method
  back into WindowRep classes for backwards compatibility for Opossum;
  server example program tests more of the WindowRep methods than before;
  removed 'not yet implemented' warnings from some PSWindowRep methods.

  Revision 1.3  1996/12/03 16:02:05  jussi
  Removed SetSmallFont(). Added more generic SetFont().

  Revision 1.2  1996/10/18 20:34:06  wenger
  Transforms and clip masks now work for PostScript output; changed
  WindowRep::Text() member functions to ScaledText() to make things
  more clear; added WindowRep::SetDaliServer() member functions to make
  Dali stuff more compatible with client/server library.

  Revision 1.1  1996/07/10 16:40:40  jussi
  Initial revision.
*/

#ifndef NullWindowRep_h
#define NullWindowRep_h

#include "WindowRep.h"
#include "Display.h"
#include "DList.h"

class NullWindowRep;

DefinePtrDList(NullWindowRepList, NullWindowRep *);

class NullWindowRep: public WindowRep {
public:

    /* Reparent this window to 'other' or vice versa. */
    virtual void Reparent(Boolean child, void *other, int x, int y);

    /* Raise window to top of stacking order */
    virtual void Raise();

    /* Lower window to bottom of stacking order */
    virtual void Lower();

    /* Flush windowRep's content to display */
    virtual void Flush() {}

    /* Move and resize window, relative to the parent */
    virtual void MoveResize(int x, int y, unsigned w, unsigned h);

    /* Iconify window. Not guaranteed to succeed.  */
    virtual void Iconify();

    virtual void PushClip(Coord x, Coord y, Coord w, Coord h);
    virtual void PopClip();

    /* import other graphics and display in window */
    virtual void ImportImage(Coord x, Coord y,
                             DisplayExportFormat format, char *filename);

    /* export window image to other graphics formats */
    virtual void ExportImage(DisplayExportFormat format, char *filename);

#ifndef LIBCS
    /* Display embedded Tk (ETk) windows */
    virtual void SetETkServer(char *serverName) {
	reportError("Can't do SetETkServer() on this WindowRep object",
		    devNoSyserr);
    }
    virtual DevStatus ETk_CreateWindow(Coord centerX, Coord centerY,
				       Coord width, Coord height,
				       char *filename,
				       int argc, char **argv,
				       int &handle) {
	reportError("Can't do ETk_CreateWindow() on this WindowRep object",
		    devNoSyserr);
	return StatusFailed;
    }
    virtual DevStatus ETk_MoveWindow(int handle,
				     Coord centerX, Coord centerY) {
	reportError("Can't do ETk_MoveWindow() on this WindowRep object",
		    devNoSyserr);
	return StatusFailed;
    }
    virtual DevStatus ETk_FreeWindow(int handle)
    {
	reportError("Can't do ETk_FreeWindow() on this WindowRep object",
		    devNoSyserr);
	return StatusFailed;
    }
    virtual DevStatus ETk_MapWindow(int handle)
    {
	reportError("Can't do ETk_MapWindow() on this WindowRep object",
		    devNoSyserr);
	return StatusFailed;
    }
    virtual DevStatus ETk_UnmapWindow(int handle)
    {
	reportError("Can't do ETk_UnmapWindow() on this WindowRep object",
		    devNoSyserr);
	return StatusFailed;
    }
    virtual DevStatus ETk_FreeWindows() {
	reportError("Can't do ETk_FreeWindows() on this WindowRep object",
		    devNoSyserr);
	return StatusFailed;
    }
    virtual int ETk_WindowCount() {
	return 0;
    }
#endif
    
    /* drawing primitives */
    /* Return TRUE if window is scrollable */
    virtual Boolean Scrollable() { return false; }

    /* Scroll a region in the window */
    virtual void Scroll(Coord x, Coord y, Coord width, Coord height,
                        Coord dstX, Coord dstY) {}

    /* Scroll absolute */
    virtual void ScrollAbsolute(int x, int y, unsigned width,
                                unsigned height, int dstX, int dstY) {}

    virtual void SetWindowBgColor(Color bg);

    virtual void FillRect(Coord xlow, Coord ylow, Coord width, Coord height);
    /* Fill rectangles, variable width/height */
    virtual void FillRectArray(Coord *xlow, Coord *ylow, Coord *width, 
                               Coord *height, int num);
    /* Fill rectangles, same width/height */
    virtual void FillRectArray(Coord *xlow, Coord *ylow, Coord width,
                               Coord height, int num);

    virtual void DrawPixel(Coord x, Coord y);
    virtual void DrawPixelArray(Coord *x, Coord *y, int num, int width);

    /* Fill rectangle. All coordinates are in pixels. x and y are
       at the center of the rectangle */
    virtual void FillPixelRect(Coord x, Coord y, Coord width, Coord height,
                               Coord minWidth = 1.0, Coord minHeigh = 1.0);
    virtual void FillPoly(Point *, int n);
    virtual void FillPixelPoly(Point *, int n);

    /* Draw an arc.  Angles are in radians. */
    virtual void Arc(Coord xCenter, Coord yCenter, Coord horizDiam,
                     Coord vertDiam, Coord startAngle, Coord endAngle);

    virtual void Line(Coord x1, Coord y1, Coord x2, Coord y2, Coord width);
    virtual void AbsoluteLine(int x1, int y1, int x2, int y2, int width);

    virtual void ScaledText(char *text, Coord x, Coord y, Coord width,
                      Coord height, TextAlignment alignment = AlignCenter,
                      Boolean skipLeadingSpaces = false);
    
    virtual void AbsoluteText(char *text, Coord x, Coord y, Coord width, 
                              Coord height,
                              TextAlignment alignment = AlignCenter,
                              Boolean skipLeadingSpaces = false);

    /* Set XOR or normal drawing mode on */
    virtual void SetXorMode();
    virtual void SetCopyMode();

    /* Set font or return to normal font */
    virtual void SetFont(char *family, char *weight, char *slant,
                         char *width, float pointSize);
    virtual void SetNormalFont();

    /* Draw rubberbanding rectangle */
    virtual void DrawRubberband(int x1, int y1, int x2, int y2);

    /* Get window rep dimensions */
    virtual void Dimensions(unsigned int &width, unsigned int &height);

    /* get window rep origin */
    virtual void Origin(int &x, int &y);

    /* Get absolute window rep origin from upper left corner of the screen */
    virtual void AbsoluteOrigin(int &x, int &y);

    /* Return contents of window as a pixmap */
    virtual DevisePixmap *GetPixmap() { return 0; }

    /* Display pixmap in window */
    virtual void DisplayPixmap(DevisePixmap *pixmap) {}

    /* Free pixmap from memory */
    virtual void FreePixmap(DevisePixmap *pixmap) {}

protected:
    friend class NullDisplay;

    /* called by NullDisplay to create new window */
    NullWindowRep(DeviseDisplay *display,
                  Color fgndColor, Color bgndColor,
                  NullWindowRep *parent, int x, int y); 

    /* called by constructors to initialize object */
    void Init();

    /* destructor */
    ~NullWindowRep();

private:
    /* Update window dimensions; globals: _x, _y, _width, _height */
    void UpdateWinDimensions();

    /* current dimensions of window */
    int _x, _y;
    unsigned int _width, _height;

    /* child/parent links for windows */
    NullWindowRep    *_parent;
    NullWindowRepList _children;
};

#endif
