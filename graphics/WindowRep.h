/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-1996
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
  Revision 1.45  1997/03/25 17:59:01  wenger
  Merged rel_1_3_3c through rel_1_3_4b changes into the main trunk.

  Revision 1.44  1997/03/19 19:41:09  andyt
  Embedded Tcl/Tk windows are now sized in data units, not screen pixel
  units. The old list of ETk window handles (WindowRep class) has been
  replaced by a list of ETkInfo structs, each with fields for the window
  handle, x-y coordinates, name of the Tcl script, and an "in_use"
  flag. Added an ETk_Cleanup() procedure that gets called inside
  View::ReportQueryDone and destroys all ETk windows that are not marked
  as in_use.

  Revision 1.43.4.1  1997/02/27 22:46:06  wenger
  Most of the way to having Tasvir images work in PostScript output;
  various WindowRep-related fixes; version now 1.3.4.

  Revision 1.43  1997/01/17 20:31:48  wenger
  Fixed bugs 088, 121, 122; put workaround in place for bug 123; added
  simulation of XOR drawing in PSWindowRep; removed diagnostic output
  from Tcl/Tk code; removed (at least for now) the ETk interface from
  the cslib versions of WindowRep classes so that the cslib will link
  okay; cslib server now tests XOR drawing.

  Revision 1.42  1997/01/09 18:41:18  wenger
  Added workarounds for some Tasvir image bugs, added debug code.

  Revision 1.41  1996/12/30 23:51:13  andyt
  First version with support for Embedded Tcl/Tk windows. WindowRep classes
  now have member functions for creating and destroying Tk windows.
  Interface to the EmbeddedTk server is in ETkIfc.h

  Revision 1.40  1996/12/15 20:22:30  wenger
  Changed pointSize in SetFont() from tenths of points to points.

  Revision 1.39  1996/12/11 18:05:38  wenger
  Arc() method now works in PSWindowRep class; put SetSmallFont() method
  back into WindowRep classes for backwards compatibility for Opossum;
  server example program tests more of the WindowRep methods than before;
  removed 'not yet implemented' warnings from some PSWindowRep methods.

  Revision 1.38  1996/12/04 22:38:54  wenger
  Fixed bug 087 (view removal crash); noted several other fixed bugs
  in the bug list.

  Revision 1.37  1996/12/03 17:00:26  jussi
  Added SetFont() for generic font support. Removed SetSmallFont().

  Revision 1.36  1996/11/26 16:47:48  ssl
  Added support for Stacked Opaque and Transparent views

  Revision 1.35  1996/11/26 15:44:12  wenger
  Added features and fixed bugs in PostScript-related parts of the
  client/server library and the PSWindowRep class; page size can now be
  set in PSDisplay; did some cleanup of the DeviseDisplay and WindowRep
  methods (allowed elimination of many typecasts).

  Revision 1.34  1996/11/13 16:56:17  wenger
  Color working in direct PostScript output (which is now enabled);
  improved ColorMgr so that it doesn't allocate duplicates of colors
  it already has, also keeps RGB values of the colors it has allocated;
  changed Color to GlobalColor, LocalColor to make the distinction
  explicit between local and global colors (_not_ interchangeable);
  fixed global vs. local color conflict in View class; changed 'dali'
  references in command-line arguments to 'tasvir' (internally, the
  code still mostly refers to Dali).

  Revision 1.33  1996/10/28 15:55:48  wenger
  Scaling and clip masks now work for printing multiple views in a window
  to PostScript; (direct PostScript printing still disabled pending correct
  text positioning and colors); updated all dependencies except Linux.

  Revision 1.32  1996/10/18 20:34:12  wenger
  Transforms and clip masks now work for PostScript output; changed
  WindowRep::Text() member functions to ScaledText() to make things
  more clear; added WindowRep::SetDaliServer() member functions to make
  Dali stuff more compatible with client/server library.

  Revision 1.31  1996/09/06 06:59:45  beyer
  - Improved support for patterns, modified the pattern bitmaps.
  - possitive pattern numbers are used for opaque fills, while
    negative patterns are used for transparent fills.
  - Added a border around filled shapes.
  - ShapeAttr3 is (temporarily) interpreted as the width of the border line.

  Revision 1.30  1996/09/04 21:24:50  wenger
  'Size' in mapping now controls the size of Dali images; improved Dali
  interface (prevents Dali from getting 'bad window' errors, allows Devise
  to kill off the Dali server); added devise.dali script to automatically
  start Dali server along with Devise; fixed bug 037 (core dump if X is
  mapped to a constant); improved diagnostics for bad command-line arguments.

  Revision 1.29  1996/08/29 22:03:31  guangshu
  Changed ExportGIF argument to FILE *

  Revision 1.28  1996/08/28 00:19:38  wenger
  Improved use of Dali to correctly free images (use of Dali is now fully
  functional with filenames in data).

  Revision 1.27  1996/08/23 16:55:56  wenger
  First version that allows the use of Dali to display images (more work
  needs to be done on this); changed DevStatus to a class to make it work
  better; various minor bug fixes.

  Revision 1.26  1996/08/04 21:05:35  beyer
  changed key handling

  Revision 1.25  1996/07/23 15:34:43  jussi
  Added mechanism for bypassing the Devise internal color map.

  Revision 1.24  1996/07/14 16:17:27  jussi
  Added destroyPending flag and IsDestroyPending() method.

  Revision 1.23  1996/07/14 04:03:24  jussi
  HandleWindowDestroy() now destroys the window, conditionally.
  Moved the destructor from the header file to the .c file.

  Revision 1.22  1996/07/10 18:59:22  jussi
  Moved 3D transform variables to WindowRep.

  Revision 1.21  1996/07/10 16:21:15  jussi
  Improvements and simplifications to the code.

  Revision 1.20  1996/06/21 19:28:02  jussi
  Moved all 3D-related code to Map3D.C and Map3D.h.

  Revision 1.19  1996/06/15 14:13:02  jussi
  Added yuc's 3D functions.

  Revision 1.18  1996/06/15 13:48:39  jussi
  Added SetWindowBgColor() which allows Devise to change
  the view background color at runtime.

  Revision 1.17  1996/05/31 15:32:10  jussi
  Added 'state' variable to HandleButton(). This tells the callee
  whether the shift/control keys were pressed in conjunction with
  the mouse button.

  Revision 1.16  1996/05/22 21:02:45  jussi
  Added ImportImage() method.

  Revision 1.15  1996/05/20 18:45:01  jussi
  Merged with ClientServer library code.

  Revision 1.14  1996/04/11 17:56:35  jussi
  Added Raise() and Lower().

  Revision 1.13  1996/02/28 17:46:21  yuc
  Added a bunch of public functions for 3D: MakeIdentity3,
  TopTransform3, PostMultiply, Transform, PrintTransform3,
  ClearTransformStack3, CompRhoPhiTheta, CompViewingTransf,
  CompLocationOnViewingSpace, MapAllPoints, and MapAllSegments, DrawRefAxis.
  Also added some protected variables: _rho, _phi, _theta, _twist_angle,
  _dvs, _camera, _TransformViewMatrix, _perspective, _NumXSegs, _AxisPt,
  and _Axis.

  Revision 1.12  1996/02/26 23:45:08  jussi
  Added GetSmallFontHeight().

  Revision 1.11  1996/02/05 23:55:15  jussi
  Added support for small fonts.

  Revision 1.10  1996/01/30 00:04:58  jussi
  Made code refer to ForegroundColor and BackgroundColor instead
  of black and white.

  Revision 1.9  1996/01/17 20:54:11  jussi
  Added support for additional image export formats.

  Revision 1.8  1996/01/11 21:57:00  jussi
  Replaced libc.h with stdlib.h.

  Revision 1.7  1995/12/28 20:45:38  jussi
  Changed the approach with which inverted lines and areas are
  drawn.

  Revision 1.6  1995/12/18 03:14:13  ravim
  Lines and Rectangles can be drawn with XOR display function.

  Revision 1.5  1995/12/02 21:33:14  jussi
  Added support for TK_WINDOW i.e. Tcl/Tk controls surrounding
  each view and window. This implementation was superseded by
  code in ViewWin.c and therefore was renamed TK_WINDOW_old.
  Added Reparent method to allow views and windows to become
  part of another window.

  Revision 1.4  1995/11/28  00:00:08  jussi
  Added WritePostscript() method.

  Revision 1.3  1995/11/24 21:26:21  jussi
  Added copyright notice and cleaned up code. Added PrintTransform
  method to help debugging.

  Revision 1.2  1995/09/05 21:13:35  jussi
  Added/updated CVS header.
*/

/* A WindowRep is an instantiation of a window.

   It has the following coordinates:
   (x,y)
   +----+
   |    | height
   +----+
   width
*/

#ifndef WindowRep_h
#define WindowRep_h

#include <stdio.h>
#include <stdlib.h>

#include "Geom.h"
#include "Transform.h"
#include "DList.h"
#include "Color.h"
#include "Pattern.h"
#include "Exit.h"
#include "DevisePixmap.h"
#include "VisualArg.h"
#include "DevError.h"

enum DisplayExportFormat { POSTSCRIPT, EPS, GIF };

class DeviseDisplay;

/* Callback from windowRep for processing window events. 
   Default: no event is handled. */
class WindowRep;

class WindowRepCallback {
public:
  /* draw in the exposed area */
  virtual void HandleExpose(WindowRep *w, int x, int y, 
			    unsigned width, unsigned height) {}

#ifdef RAWMOUSEEVENTS
  /* Handle button event */
  virtual void HandleButton(WindowRep *w, int x, int y,
			    int button, int state, int type) {}
#else
  /* Handle button press event */
  virtual void HandlePress(WindowRep *w, int xlow, int ylow,
                           int xhigh, int yhigh, int button) {}
#endif

  /* Handle resize */
  virtual void HandleResize(WindowRep *w, int xlow, int ylow,
                            unsigned width, unsigned height) {}
  
  /* Handle key press */
  virtual void HandleKey(WindowRep *w, int key, int x, int y) {}
  
#ifndef RAWMOUSEEVENTS
  /* handle pop-up */
  virtual Boolean HandlePopUp(WindowRep *w, int x, int y, int button,
			      char **&msgs, int &numMsgs) {
      return 0;
  }
#endif

  /* Handle map/unmap info.
     mapped : means window has been mapped.
     unmapped: means window has been unmapped. (This can also mean
     that window has been iconified) */
  virtual void HandleWindowMappedInfo(WindowRep *w, Boolean mapped) {}

  /* Handle window destroy events */
  virtual Boolean HandleWindowDestroy(WindowRep *w) { return true; }
};

const int WindowRepTransformDepth = 10;	/* max # of transforms in the stack */
const int WindowRepClipDepth = 10;	/* max # of clippings */

/* clipping rectangle */
struct ClipRect {
  Coord x, y, width, height;
};

DefinePtrDList(WindowRepCallbackList, WindowRepCallback *);
DefinePtrDList(ClipRectList, ClipRect *);

/* # of symbols that can be sent at once in a batched call */

const int WINDOWREP_BATCH_SIZE = 1024;

class WindowRep {
public:
  /* destructor */
  virtual ~WindowRep();

#ifdef TK_WINDOW_old
  /* Decorate window */
  virtual void Decorate(WindowRep *parent, char *name,
			unsigned int min_width,
			unsigned int min_height) = 0;

  /* Undecorate window */
  virtual void Undecorate() = 0;
#endif

  /* Reparent this window to 'other' or vice versa. */
  virtual void Reparent(Boolean child, void *other, int x, int y) = 0;

  /* Raise window to top of stacking order */
  virtual void Raise() = 0;

  /* Lower window to bottom of stacking order */
  virtual void Lower() = 0;

  /* Flush windowRep's content to display */
  virtual void Flush() = 0;

  /* Find out whether window has backing store. */
  virtual Boolean HasBackingStore() { return false; }
	
  /* Move and resize window, relative to the parent */
  virtual void MoveResize(int x, int y, unsigned int w, unsigned int h) = 0;

  /* Iconify window. Not guaranteed to succeed.  */
  virtual void Iconify() = 0;

  /* Register a callback to be called when an event occurs */
  void RegisterCallback(WindowRepCallback *c){
    _callbackList->Append(c);
  }

  /* delete callback. Return TRUE if found */
  Boolean DeleteCallback(WindowRepCallback *c) {
    return _callbackList->Delete(c);
  }

  /* import other graphics and display in window */
  virtual void ImportImage(Coord x, Coord y,
			   DisplayExportFormat format, char *filename) {}

  /* export window image to other graphics formats */
  virtual void ExportImage(DisplayExportFormat format, char *filename) {}
  virtual void ExportGIF(FILE *fp) {}


  /* import graphics via Dali */
  virtual void SetDaliServer(char *serverName) { DOASSERT(false,
    "Can't do SetDaliServer() on this object"); }
  virtual DevStatus DaliShowImage(Coord centerX, Coord centerY, Coord width,
    Coord height, char *filename, int imageLen, char *image,
    float timeoutFactor = 1.0, Boolean maintainAspect = true)
    { reportErrNosys("This object does not support Tasvir operations");
      return StatusFailed; }
  virtual DevStatus DaliFreeImages()
    { reportErrNosys("This object does not support Tasvir operations");
      return StatusFailed; }
  virtual int DaliImageCount() { return 0; }

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
  virtual int ETk_FindWindow(Coord centerX, Coord centerY,
			     char *script)
  {
      reportError("Can't do ETk_FindWindow() on this WindowRep object",
		  devNoSyserr);
      return -1;
  }
  virtual DevStatus ETk_MoveWindow(int handle,
				   Coord centerX, Coord centerY) {
      reportError("Can't do ETk_MoveWindow() on this WindowRep object",
		  devNoSyserr);
      return StatusFailed;
  }
  virtual DevStatus ETk_ResizeWindow(int handle,
				     Coord width, Coord height) {
      reportError("Can't do ETk_ResizeWindow() on this WindowRep object",
		  devNoSyserr);
      return StatusFailed;
  }
  virtual DevStatus ETk_MoveResizeWindow(int handle,
					 Coord centerX, Coord centerY,
					 Coord centerX, Coord centerY) {
      reportError("Can't do ETk_MoveResizeWindow() on this WindowRep object",
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
  virtual DevStatus ETk_Cleanup() {
      reportError("Can't do ETk_Cleanup() on this WindowRep object",
		  devNoSyserr);
      return StatusFailed;
  }
  virtual DevStatus ETk_Mark(int handle, bool in_use) {
      reportError("Can't do ETk_Mark() on this WindowRep object",
		  devNoSyserr);
      return StatusFailed;
  }
  virtual DevStatus ETk_MarkAll(bool in_use) {
      reportError("Can't do ETk_MarkAll() on this WindowRep object",
		  devNoSyserr);
      return StatusFailed;
  }
  virtual int ETk_WindowCount() {
      return 0;
  }
#endif
  
  /* drawing primitives */

  /* Return TRUE if window is scrollable */
  virtual Boolean Scrollable() = 0;

  /* Scroll a region in the window, done in world coordinates */
  virtual void Scroll(Coord x, Coord y, Coord width, Coord height,
		      Coord dstX, Coord dstY) = 0;
	
  /* Scroll absolute */
  virtual void ScrollAbsolute(int x, int y, unsigned width, unsigned height,
			      int dstX, int dstY) = 0;

  /* Color selection interface using Devise colormap */
  virtual void SetFgColor(GlobalColor fg) { _fgndColor = fg; }
  virtual void SetBgColor(GlobalColor bg) { _bgndColor = bg; }
  virtual GlobalColor GetFgColor() { return _fgndColor; }
  virtual GlobalColor GetBgColor() { return _bgndColor; }
  virtual void SetWindowBgColor(GlobalColor bg) = 0;

#ifdef LIBCS
  /* Color selection interface using specific colors */
  virtual void SetFgRGB(float r, float g, float b) = 0;
  virtual void SetBgRGB(float r, float g, float b) = 0;
  virtual void GetFgRGB(float &r, float &g, float &b) = 0;
  virtual void GetBgRGB(float &r, float &g, float &b) = 0;
  virtual void SetWindowBgRGB(float r, float g, float b) = 0;
#endif

  virtual void SetPattern(Pattern p) { _pattern = p; }
  Pattern GetPattern(){ return _pattern; }

  virtual void SetLineWidth(int w) { _line_width = w; }
  int GetLineWidth(){ return _line_width; }
#ifdef LIBCS
  virtual void SetDashes(int dashCount, int dashes[], int startOffset) {}
#endif

  virtual void FillRect(Coord xlow, Coord ylow,
			Coord width, Coord height) = 0;

  /* Fill rectangles, variable width/height */
  virtual void FillRectArray(Coord *xlow, Coord *ylow, Coord *width, 
			     Coord *height, int num) = 0;
  /* Fill rectangles, same width/height */
  virtual void FillRectArray(Coord *xlow, Coord *ylow, Coord width, 
			     Coord height, int num) = 0;

  virtual void DrawPixel(Coord x, Coord y) = 0;
  virtual void DrawPixelArray(Coord *x, Coord *y, int num, int width) = 0;
  /* fill rectangle. All coordinates are in pixels. x and y are
     at the center of the rectangle */
  virtual void FillPixelRect(Coord x, Coord y, Coord width, Coord height,
			     Coord minWidth = 1.0, Coord minHeight = 1.0) = 0;
  virtual void FillPoly(Point *, int n) = 0;
  virtual void FillPixelPoly(Point *, int n) = 0;

  /* Draw an arc.  Angles are in radians, end is _relative_ to start. */
  virtual void Arc(Coord xCenter, Coord yCenter, Coord horizDiam,
		   Coord vertDiam, Coord startAngle, Coord endAngle) = 0;

  /* draw line. end points are in world coord, but the width is in pixels */
  virtual void Line(Coord x1, Coord y1, Coord x2, Coord y2, Coord width) = 0;
  virtual void AbsoluteLine(int x1, int y1, int x2, int y2, int width) = 0;

  /* draw and scaled text to fit inside box, according to alignment.
     If skipLeadingSpaces == TRUE, then the leading spaces are used to
     scale the text inside the box, but not used in alignment 
     calculations or for drawing. Padding all texts with leading spaces
     so that they are the same lenght and setting skipLeadingSpaces
     to TRUE ensures that the texts are draw with the same size */
  enum TextAlignment { AlignNorthWest, AlignNorth, AlignNorthEast, 
			 AlignWest, AlignCenter, AlignEast, AlignSouthWest,
			 AlignSouth, AlignSouthEast};
  virtual void ScaledText(char *text, Coord x, Coord y, Coord width,
		    Coord height, TextAlignment alignment = AlignCenter, 
		    Boolean skipLeadingSpaces = false) = 0;
  
  /* draw absolute text: one that does not scale the text */
  virtual void AbsoluteText(char *text, Coord x, Coord y, Coord width, 
			    Coord height,
			    TextAlignment alignment = AlignCenter, 
			    Boolean skipLeadingSpaces = false) = 0;

  /* Set XOR or normal drawing mode on */
  virtual void SetXorMode() = 0;
  virtual void SetCopyMode() = 0;
  virtual void SetOrMode() {}

  /* Set font or return to normal */
  virtual void SetFont(char *family, char *weight, char *slant,
                       char *width, float pointSize) = 0;
  virtual void SetNormalFont() = 0;
  virtual void SetSmallFont() { SetFont("Courier", "Medium", "r", "Normal",
					 8.0); }

  /* Get window rep dimensions */
  virtual void Dimensions(unsigned int &width, unsigned int &height ) = 0;

  /* Set window rep dimensions */
  virtual void SetDimensions(unsigned int width, unsigned int height) {}
  
  /* get window rep origin from parent */
  virtual void Origin(int &x, int &y) = 0;
  
  /* Get absolute window rep origin from upper left corner
     of the screen */
  virtual void AbsoluteOrigin(int &x,int &y) = 0;

  /* Set window rep absolute origin */
  virtual void SetAbsoluteOrigin(int x, int y) {}
  
  /* get display of this Window Rep */
  DeviseDisplay *GetDisplay() { return _display; };
  
  /* Get flag which indicates if window destroy is pending */
  static Boolean IsDestroyPending() { return _destroyPending; }

  // ---------------------------------------------------------- 

  /* Copy the "state" (2D transforms, 3D transforms, clip mask)
     of the given WindowRep. */
  void CopyState(WindowRep *winRepP);

  // ---------------------------------------------------------- 

  /* 2D transformation matrix operations */
  
  /* Push a copy of the top of stack onto the stack */
  void PushTop() {
    if (_current >= WindowRepTransformDepth-1 ){
      reportErrNosys("WindowRep::PushTop: overflow");
      Exit::DoExit(1);
    };
    _transforms[_current+1].Copy(_transforms[_current]);
    _current++;
  }
  
  /* pop transformation matrix */
  void PopTransform() {
    if (_current <= 0){
      reportErrNosys("WindowRep::PopTransform: underflow");
      Exit::DoExit(1);
    }
    _current--;
  }

  /* operations on current transformation matrix */
  void Scale(Coord sx, Coord sy) {
    _transforms[_current].Scale(sx,sy);
  }

  void Translate(Coord dx, Coord dy) {
    _transforms[_current].Translate(dx,dy);
  }

  void MakeIdentity() {
    _transforms[_current].MakeIdentity();
  }

  /* return the transform on top of the stack. */
  Transform2D *TopTransform() {
    return &_transforms[_current];
  }

  void PostMultiply(Transform2D *t) {
    _transforms[_current].PostMultiply(t);
  }

  virtual void Transform(Coord x, Coord y, Coord &newX, Coord &newY) {
    _transforms[_current].Transform(x, y, newX, newY);
  }

  void PrintTransform() {
    _transforms[_current].Print();
  }

  /* Clear the transformation stack and put an identity 
     matrix as top of the stack */
  void ClearTransformStack() {
    _current = 0;
    MakeIdentity();
  }

  // ---------------------------------------------------------- 

  /* 3D transformation matrix operations */
  
  /* Push a copy of the top of stack onto the stack */
  void PushTop3() {
    if (_current3 >= WindowRepTransformDepth-1 ){
      reportErrNosys("WindowRep::PushTop: overflow");
      Exit::DoExit(1);
    };
    _transforms3[_current3+1].Copy(_transforms3[_current3]);
    _current3++;
  }
  
  /* pop transformation matrix */
  void PopTransform3() {
    if (_current3 <= 0){
      reportErrNosys("WindowRep::PopTransform: underflow");
      Exit::DoExit(1);
    }
    _current3--;
  }

  /* operations on current transformation matrix */
  void Scale3(Coord sx, Coord sy, Coord sz) {
    _transforms3[_current3].Scale(sx,sy,sz);
  }

  void Translate3(Coord dx, Coord dy, Coord dz) {
    _transforms3[_current3].Translate(dx,dy,dz);
  }

  void MakeIdentity3() {
    _transforms3[_current3].MakeIdentity();
  }

  /* return the transform on top of the stack. */
  Transform3D *TopTransform3() {
    return &_transforms3[_current3];
  }

  void PostMultiply3(Transform3D *t) {
    _transforms3[_current3].PostMultiply(t);
  }

#if 0 // Not used -- RKW 10/12/96.
  virtual void Transform3(Coord x, Coord y, Coord z,
                  Coord &newX, Coord &newY, Coord &newZ) {
    _transforms3[_current3].Transform(x, y, z, newX, newY, newZ);
  }
#endif

  void PrintTransform3() {
    _transforms3[_current3].Print();
  }

  /* Clear the transformation stack and put an identity 
     matrix as top of the stack */
  void ClearTransformStack3() {
    _current3 = 0;
    MakeIdentity3();
  }

  // ---------------------------------------------------------- 

  /* push clipping onto stack. The coords are defined with respect to the
     current transformation matrix. */
  virtual void PushClip(Coord x, Coord y, Coord w, Coord h) = 0;
  /* pop the clip region. */
  virtual void PopClip() = 0;
  
  /* called by derived class to get current clip region */

  Boolean ClipTop(Coord &x, Coord &y, Coord &w, Coord &h){
    if (_clipCurrent < 0)
      return false;
    else {
      ClipRect *rect = &_clippings[_clipCurrent];
      x = rect->x; y = rect->y; w = rect->width; h = rect->height;
      return true;
    }
  }

  /******* Pixmap ***************/
  /* Generate pixmap for current window. Return NULL
     if insufficient memory. */
  virtual DevisePixmap *GetPixmap() = 0;
  
  /* Display pixmap in window */
  virtual void DisplayPixmap(DevisePixmap *pixmap) = 0;
  /* Free pixmap from memory */
  virtual void FreePixmap(DevisePixmap *pixmap) = 0;

//TEMPTEMP -- this is kind of X-specific
  /* called by derived class to get currennt local color from
     global color */
  LocalColor GetLocalColor(GlobalColor globalColor);
  

protected:

  /* called by derived class to cache current clip region */
  void _PushClip(Coord x, Coord y, Coord w, Coord h) {
    if (_clipCurrent >= WindowRepClipDepth - 1){
      reportErrNosys("WindowRep::PushClip: overflow");
      Exit::DoExit(1);
    };
    ClipRect *rect = &_clippings[++_clipCurrent];
    rect->x = x; rect->y = y; rect->width = w; rect->height = h;
  }
  
  /* called by derived class to pop clip region */
  void _PopClip(){
    if (_clipCurrent < 0){
      reportErrNosys("WindowRep::PopClip: underflow");
      Exit::DoExit(1);
    }
    _clipCurrent--;
  }

  /* called by derived classes to iterate through the callbacks */
  int InitIterator(){ return _callbackList->InitIterator();};
  Boolean More(int index) { return _callbackList->More(index);}
  WindowRepCallback *Next(int index) { return _callbackList->Next(index);}
  void DoneIterator(int index) { _callbackList->DoneIterator(index);};

  /* Called by derived class when part of window is exposed */
  virtual void HandleExpose(int x, int y, unsigned w, unsigned h);
  
  /* called by derived class to when window is resized or moved: 
     Update the current size and inform all callbacks. */
  virtual void HandleResize(int x, int y, unsigned width, unsigned height);
  
#ifdef RAWMOUSEEVENTS
  /* called by derived class with button even */
  virtual void HandleButton(int x, int y, int button, int state, int type);
#else
  /* called by derived class when button presssed: Report event to all
     callbacks */
  virtual void HandleButtonPress(int xlow, int ylow, 
				 int xhigh, int yhigh, int button);
#endif
  
  /* called by derived class when key pressed. report event to all
     callbacks */
  virtual void HandleKey(int key, int x, int y);
  
#ifndef RAWMOUSEEVENTS
  /* Called by derived class on pop-up event. Report to all callbacks */
  virtual Boolean HandlePopUp(int x, int y, int button, char **&msgs,
			      int &numMsgs);
#endif

  /* called by dervied class on window mapped info change event.
     Report to all callbacks */
  virtual void HandleWindowMappedInfo(Boolean mapped);
  
  /* called by derived class on window destroy event */
  virtual void HandleWindowDestroy();

  /* constructor */
  WindowRep(DeviseDisplay *disp, GlobalColor fgndColor = ForegroundColor,
	    GlobalColor bgndColor = BackgroundColor, Pattern p = Pattern0);
  
  WindowRepCallbackList  *_callbackList;

  Transform2D _transforms[WindowRepTransformDepth];
  int _current;         /* current index in the stack */
  ClipRect _clippings[WindowRepClipDepth];
  int _clipCurrent;	/* index of top of stack for _clippings*/

  Transform3D _transforms3[WindowRepTransformDepth];
  int _current3;        /* current index in the stack */

  ClipRectList  _damageRects;     /* damaged areas */
  Boolean _damaged;

#if 0 // Not used anywhere.  RKW 10/11/96.
  Coord _x, _y, _width, _height;  /* location and dimensions of window */
#endif
  GlobalColor _fgndColor, _bgndColor;   /* current fg and bg colors */
  Pattern _pattern;               /* current pattern */
  int _line_width;		  /* current border line width */
  DeviseDisplay *_display;        /* display object */

  static Boolean _destroyPending; /* true if window destroy is pending */
};

#endif
