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
  Revision 1.6  1995/12/06 21:22:33  jussi
  Tries to allocate a color by using a close color approximation
  if requested color cannot be allocated.

  Revision 1.5  1995/12/02 21:30:11  jussi
  Tried if letting Tcl/Tk handle all X events and pass a copy
  of each event to us would solve the problem with TK_WINDOW_old.
  This event handling mechanism didn't turn out to work right
  so I renamed it TK_WINDOW_EV2.

  Revision 1.4  1995/11/29 15:30:09  jussi
  Disabled a debugging message.

  Revision 1.3  1995/11/29 15:12:07  jussi
  Added copyright notice and cleaned up the code a bit.

  Revision 1.2  1995/09/05 21:13:38  jussi
  Added/updated CVS header.
*/

#include <X11/Intrinsic.h>
#include "XDisplay.h"
#include "XWindowRep.h"
#include "Control.h"
#include "Journal.h"
#include "Init.h"

//#define DEBUG

#ifdef TK_WINDOW_EV2
static int HandleTkEvent(ClientData data, XEvent *event)
{
  return ((XDisplay *)data)->HandleXEvent(*event);
}
#endif

/*******************************************************************
Open a new X display
********************************************************************/

XDisplay::XDisplay(char *name)
{
  if (!(this->_display = XOpenDisplay(name))) {
    (void)fprintf(stderr,"can't open display\n");
    Exit::DoExit(1);
  }
  
  /* init colors from the color manager. */
  DeviseDisplay::InitializeColors();
  
  /* get font */
  if (!(_fontStruct = XLoadQueryFont(_display, "7x13"))) {
    fprintf(stderr, "XDisplay: can not load font\n");
    Exit::DoExit(1);
  }
  
  /* init stipples for patterns*/
  Window win = XCreateSimpleWindow(_display, DefaultRootWindow(_display),
				   (unsigned)0, (unsigned)0, (unsigned)10,
				   (unsigned)10, /* border width */ 5,
				   /* border */ 0, /* background */ 0);
  if (!win) {
    fprintf(stderr, "XDisplay::XDisplay() can't create window\n");
    Exit::DoExit(1);
  }

  for(int i = 0; i < XNumBitmaps; i++) {
    _stipples[i] = XCreateBitmapFromData(_display, win, xBitmaps[i],
					 XBitmapWidth, XBitmapHeight);
  }

  XDestroyWindow(_display, win);

#ifdef TK_WINDOW_EV2
  /* tell Tk to pass all X events to us */
  Tk_CreateGenericHandler(HandleTkEvent, (ClientData)this);
#endif
}

#ifdef TK_WINDOW_EV2
XDisplay::~XDisplay()
{
  /* tell Tk to pass all X events to us */
  Tk_DeleteGenericHandler(HandleTkEvent, (ClientData)this);
}
#endif

/*******************************************************************
Allocate closest matching color
********************************************************************/

Boolean XDisplay::ClosestColor(Colormap &map, XColor &color, Color &c)
{
  if (XAllocColor(_display, map, &color)) {
    c = color.pixel;
    return true;
  }

  // if exact color match is not found, try allocating a color that
  // is close enough; maxDeviation specifies maximum distance in each
  // of the RGB directions (X color values are between 0 and 65535);
  // increment specifies the hop size between each attempt

  const int maxDeviation = (int)(0.05 * 65535);   // 1% max deviation
  const int increment = (int)(maxDeviation / 4);
    
  for(int dev = increment; dev < maxDeviation; dev += increment) {
    for(int r = -1; r <= 1; r += 2) {
      for(int g = -1; g <= 1; g += 2) {
	for(int b = -1; b <= 1; b += 2) {
	  XColor ctry;
	  ctry.red   = color.red + r * dev;
	  ctry.green = color.green + g * dev;
	  ctry.blue  = color.blue + b * dev;
#ifdef DEBUG
	  printf("Trying to allocate color %d,%d,%d\n", ctry.red,
		 ctry.green, ctry.blue);
#endif
	  if (XAllocColor(_display, map, &ctry)) {
	    c = ctry.pixel;
	    return true;
	  }
	}
      }
    }
  }

  return false;
}

/*******************************************************************
Alloc color by name
********************************************************************/

void XDisplay::AllocColor(char *name, Color globalColor)
{
  Colormap cmap = DefaultColormap(this->_display,
				  DefaultScreen(this->_display));

  XColor color_def;

  if (!XParseColor(this->_display, cmap, name, &color_def)) {
    fprintf(stderr, "Cannot understand color %s.\n", name);
    Exit::DoExit(1);
  }

#ifdef DEBUG
  printf("XDisplay::AllocColor %s\n", name);
#endif

  Color color;
  if (ClosestColor(cmap, color_def, color)) {
    DeviseDisplay::MapColor(color, globalColor);
    return;
  }

  fprintf(stderr, "Cannot allocate color %s.\n", name);
  fprintf(stderr, "Try starting DEVise before any other color-intensive\n");
  fprintf(stderr, "applications (such as Netscape).\n");
  Exit::DoExit(1);
}

/*********************************************************************
Alloc color by RGB
*********************************************************************/

void XDisplay::AllocColor(double r, double g, double b, Color globalColor)
{
#ifdef DEBUG
  printf("XDisplay::AllocColor(%f,%f,%f,)\n",r,g,b);
#endif

  Colormap cmap = DefaultColormap(this->_display,
				  DefaultScreen(this->_display));
  XColor color_def;
  
  /* convert from (0.0,1.0) to (0,65535)*/
  color_def.red = (unsigned short)(r * 65535); 
  color_def.green = (unsigned short)(g * 65535);
  color_def.blue = (unsigned short)(b * 65535);

#ifdef DEBUG
  printf("XDisplay::AllocColor red %d, green %d, blue %d\n",
	 color_def.red, color_def.green, color_def.blue);
#endif

  Color color;
  if (ClosestColor(cmap, color_def, color)) {
    DeviseDisplay::MapColor(color, globalColor);
    return;
  }

  fprintf(stderr, "Cannot allocate color %.2f,%.2f,%.2f.\n", r, g, b);
  fprintf(stderr, "Try starting DEVise before any other color-intensive\n");
  fprintf(stderr, "applications (such as Netscape).\n");
}

/*
 * This structure forms the WMHINTS property of the window,
 * letting the window manager know how to handle this window.
 * See Section 9.1 of the Xlib manual.
 */

XWMHints xwmh = {
  (InputHint | StateHint | IconPositionHint),	/* flags */
  False,					/* input */
  NormalState,					/* initialstate */
  0,						/* icon pixmap */
  0,						/* icon window */
  0, 0,						/* icon location */
  0,						/* icon mask */
  0						/* Window group */
};

/*************************************************************
Create a new window 
***************************************************************/

WindowRep *XDisplay::CreateWindowRep(char *name, Coord x, Coord y,
				     Coord width, Coord height, 
				     Color fgnd, Color bgnd, 
				     WindowRep *parentRep,
				     Coord min_width, Coord min_height,
				     Boolean relative, Boolean winBoundary)
{
  Window w, parent;
  XSetWindowAttributes attr;
  XSizeHints xsh;
  XWindowRep *xParentRep = (XWindowRep *)parentRep;

  if (!parentRep)
    parent = DefaultRootWindow(_display);
  else
    parent = xParentRep->GetWin();

  Color realFgnd, realBgnd;
  realFgnd = GetLocalColor(fgnd);
  realBgnd = GetLocalColor(bgnd);

  attr.background_pixmap 	= None;
  attr.background_pixel  	= realBgnd;
  attr.border_pixmap  		= CopyFromParent;
  attr.border_pixel  		= realFgnd;
  attr.bit_gravity  		= ForgetGravity /*CenterGravity*/;
  attr.win_gravity  		= NorthWestGravity;
  attr.backing_store  		= Always /* NotUseful*/ ;
  attr.backing_planes  		= AllPlanes;
  attr.backing_pixel  		= 0;
  attr.save_under  		= False;
  attr.event_mask  		= 0;
  attr.do_not_propagate_mask	= 0;
  attr.override_redirect  	= False;
  attr.colormap	= DefaultColormap(_display, DefaultScreen(_display));
  attr.cursor  			= None;

  /* Deal with providing the window with an initial position & size.
   * Fill out the XSizeHints struct to inform the window manager. See
   * Sections 9.1.6 & 10.3.
   */

  Coord realX, realY, realWidth, realHeight;
  Coord real_min_width, real_min_height;
  if (relative) {
    RealWindowDimensions(parent,x,y,width,height,realX,realY,realWidth,
			 realHeight);
    RealWindowWidthHeight(parent,min_width,min_height,real_min_width,
			  real_min_height);
  } else {
    realX = x;
    realY = y;
    realWidth = width;
    realHeight = height;
    real_min_width = min_width;
    real_min_height = min_height;
  }

  xsh.flags 	= PPosition | PSize | PMinSize;
  xsh.height 	= (int)realHeight;
  xsh.width 	= (int)realWidth;
  xsh.x 	= (int)realX;
  xsh.y 	= (int)realY;
  xsh.min_width = (int)real_min_width;
  xsh.min_height = (int)real_min_height;

  /* Create the window. */
  unsigned int border_width;

  if (winBoundary)
    border_width = (!parent ? 5 : 1);
  else
    border_width = (!parent ? 5 : 0);

  if ((w = XCreateWindow(_display, parent, (unsigned)realX, (unsigned)realY, 
			 (unsigned)realWidth, (unsigned)realHeight,
			 border_width, 0, InputOutput, CopyFromParent,
			 AllPlanes, &attr)) == 0) {
    fprintf(stderr,"XDisplay::CreateWindowRep: can't create window\n");
    Exit::DoExit(1);
  }

#ifdef DEBUG
  printf("XDisplay: Created X window 0x%p to parent 0x%p at %u,%u,\n",
	 w, parent, (unsigned)realX, (unsigned)realY);
  printf("          size %u,%u, borderwidth %d\n", (unsigned)realWidth,
	 (unsigned)realHeight, border_width);
#endif

  XSelectInput(_display, w, ExposureMask | ButtonPressMask 
	       | ButtonReleaseMask | Button1MotionMask | Button2MotionMask
	       | Button3MotionMask | StructureNotifyMask | KeyPressMask |
	       VisibilityChangeMask);
  
  /*
   * Set the standard properties for the window managers. See Section
   * 9.1.
   */

  XSetStandardProperties(_display, w, name, name, None, 0, 0, &xsh);
  if (ControlPanel::Instance()->Restoring() && Init::Iconify()) {
    xwmh.flags = InputHint | StateHint | IconPositionHint;
    xwmh.input = true;
    xwmh.initial_state = IconicState;
    xwmh.icon_x = (unsigned)realX;
    xwmh.icon_y = (unsigned)realY;
  } else {
    xwmh.flags = InputHint | StateHint;
    xwmh.input = true;
    xwmh.initial_state = NormalState;
  }
  XSetWMHints(_display, w, &xwmh);
  
  /* Map the window so that it appears on the display. */
  if (XMapWindow(_display, w) < 0)
    return NULL;

  /* Do a sync to force the window to appear immediately */
  XSync(_display, false);

#if 0
  XEvent e;
  e.event = 0;
  while (e.event != MapNotify) {
    XNextEvent(_display, &e);
  }
#endif

  /* return the XWindowRep structure */
  XWindowRep *xwin = new XWindowRep(_display, w, this, fgnd, bgnd, false);
  _winList.Insert(xwin);
  
  return xwin;
}

/**************************************************************
 Destroy a window. Parameter "win" better be of type XwindowRep *.
**************************************************************/

void XDisplay::DestroyWindowRep(WindowRep *win)
{
  XWindowRep *xwin = (XWindowRep *)win;
  if (!_winList.Delete(xwin)) {
    fprintf(stderr, "XDisplay:Window to be deleted not found\n");
    Exit::DoExit(1);
  }

#ifdef DEBUG
  printf("XDisplay::DestroyWindowRep 0x%p, X Window 0x%p\n",
	 xwin, xwin->GetWin());
#endif

  XDestroyWindow(_display, xwin->GetWin());

  delete xwin;

  XSync(_display, false);
}

/******************************************************************
Internal non-blocking event processing .
********************************************************************/

void XDisplay::InternalProcessing()
{
#ifdef TK_WINDOW_EV2
  // X events handled in HandleTkEvent
  return;
#endif

#if 0
  static first = true;
  if (first) {
    printf("first XDisplay::InternalProcessing\n");
    first = false;
  }
#endif

  while (XPending(_display) > 0) {
    /* There are events on the queue */
    XEvent event;
    XNextEvent(_display, &event);

    /* dispatch event to appropriate window.*/
    Boolean found = false;
    for(int index = _winList.InitIterator(); _winList.More(index);) {
      XWindowRep *win = _winList.Next(index);
      if (win->_win == event.xany.window) {
	/* Note: got to be careful here. We need to
	   call DoneIterator() before informing the WindowRep
	   because it might trigger a call to DestroyWindowRep() to
	   delete the window. Delete() can't be called
	   when the iterator is active. */
	_winList.DoneIterator(index);
	found = true;
#ifdef DEBUG
	printf("XDisplay::Dispatching event %d to XWindowRep 0x%p\n",
	       event.type, win);
#endif
	win->HandleEvent(event);
	break;
      }
    }
    if (!found) {
      _winList.DoneIterator(index);
#ifdef DEBUG
      printf("XDisplay::InternalProcessing: window for event %d not found\n",
	     event.type);
#endif
    }
  }
}

#ifdef TK_WINDOW_EV2
int XDisplay::HandleXEvent(XEvent &event)
{
#ifdef DEBUG
  printf("XDisplay received X event %d from Tk\n", event.type);
#endif

  /* dispatch event to appropriate window.*/
  Boolean found = false;
  for(int index = _winList.InitIterator(); _winList.More(index);) {
    XWindowRep *win = _winList.Next(index);
    if (win->_win == event.xany.window) {
      /* Note: got to be careful here. We need to
	 call DoneIterator() before informing the WindowRep
	 because it might trigger a call to DestroyWindowRep() to
	 delete the window. Delete() can't be called
	 when the iterator is active. */
      _winList.DoneIterator(index);
      found = true;
      win->HandleEvent(event);
      break;
    }
  }

  if (!found) {
    _winList.DoneIterator(index);
#ifdef DEBUG
    printf("XDisplay::InternalProcessing: window for event %d not found\n",
	   event.type);
#endif
    return 0;
  }

  return 1;
}
#endif
