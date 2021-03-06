/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2010
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
  Revision 1.46  2010/09/01 18:44:10  wenger
  Merged fix_3d_cursor_br_0 thru fix_3d_cursor_br_1 to trunk.

  Revision 1.45.4.9  2010/08/31 19:14:42  wenger
  Fixed the cursor behavior problems in the ambiguity code and Pistachio
  visualizations by calling RestoreCursorState() at a different point.

  Revision 1.45.4.8  2010/08/31 17:28:22  wenger
  Changed the names of some of the new commands and methods to better
  reflect their functions; documented the new methods.  (Note: cursor
  mods still don't always work right for ambiguity code and Pistachio
  visualizations.)

  Revision 1.45.4.7  2010/08/24 21:01:28  wenger
  Added the setCursorProportions command to allow explicit setting of
  cursor proportions (to be used in session post scripts).

  Revision 1.45.4.6  2010/08/24 20:38:25  wenger
  Added the getViewSaveState, setViewSaveState, getCursorSaveState,
  setCursorSaveState, getCursorKeepProp, and setCursorKeepProp commands
  to control the new view and cursor properties.

  Revision 1.45.4.5  2010/08/19 18:28:30  wenger
  Added class variables to control the new cursor and view symbol
  behaviors (but not the commands to set them yet) -- Y stuff for the
  cursors are temporarily turned on.

  Revision 1.45.4.4  2010/08/19 17:12:43  wenger
  Got rid of a bunch of debug output, etc.

  Revision 1.45.4.3  2010/08/19 16:50:06  wenger
  Did some cleanup of the 3D cursor fixes -- no real functional changes,
  mainly changing some method and variable names to better match the
  current functionality.

  Revision 1.45.4.2  2010/08/19 15:39:58  wenger
  More work on 3D cursor fixes -- we now remember the cursor location for
  a given TData/parentVal combination; if you go to a new combination for
  the first time, the cursor stays the same proportion of the destination
  view that it was.  (Still needs options to turn this on and off for
  X and Y independently.)

  Revision 1.45.4.1  2010/08/18 21:10:17  wenger
  Working on 3D cursor fixes -- I have a (preliminary?) implementation
  here that saves the cursor proportions relative to the destination
  view when you change TData and/or parent value for the destination
  view.  (This commit also includes loads of debug code, and turning
  off the earlier feature of trying to save view filters by TData/
  parent value.)

  Revision 1.45  2010/02/23 22:05:31  wenger
  Merged devise_1_10_br_2 thru devise_1_10_br_3 to trunk.

  Revision 1.44.14.1  2010/02/16 23:16:01  wenger
  Fixed bug 996 (certain combinations of JavaScreen cursor actions
  crashed devised).

  Revision 1.44  2003/01/13 19:25:09  wenger
  Merged V1_7b0_br_3 thru V1_7b0_br_4 to trunk.

  Revision 1.43.10.1  2002/08/23 21:10:30  wenger
  Fixed a problem that sometimes caused a cursor with no source view
  to cause a core dump (fixes bug 679).

  Revision 1.43  2001/08/03 18:13:01  wenger
  Removed all OpenGL-related code.

  Revision 1.42  2001/01/08 20:32:41  wenger
  Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
  back onto the trunk.

  Revision 1.38.2.2  2000/12/27 19:38:54  wenger
  Merged changes from js_restart_improvements thru zero_js_cache_check from
  the trunk onto the js_cgi_br branch.

  Revision 1.41  2000/11/17 22:58:59  wenger
  Fixed problems with command logging of cursor movements and pile/stack
  flips.

  Revision 1.38.2.1  2000/10/18 20:31:52  wenger
  Merged changes from fixed_bug_616 through link_gui_improvements onto
  the branch.

  Revision 1.40  2000/09/14 19:38:45  wenger
  Added GUI to view and change cursor type (X, Y, or XY).

  Revision 1.39  2000/09/11 19:24:43  wenger
  Fixed bug 617 and some other problems with the cursor constraints code.

  Revision 1.38  2000/08/30 20:08:46  wenger
  Added the option of forcing a cursor to be entirely within its destination
  view; added control for whether a cursor must be at least partially within
  its destination view; generally improved implementation of cursor
  constraints.

  Revision 1.37  2000/05/16 13:54:32  wenger
  Found and fixed bug 587 (cursor size problem).

  Revision 1.36  2000/02/16 18:51:19  wenger
  Massive "const-ifying" of strings in ClassDir and its subclasses.

  Revision 1.35  2000/02/15 16:16:05  wenger
  Cursors in child views "remember" their size and location when
  switching TDatas or parent attributes.

  Revision 1.34  1999/12/27 19:33:06  wenger
  Cursor grids can now be applied to the edges of a cursor, rather than the
  center, if desired.

  Revision 1.33  1999/12/15 16:25:42  wenger
  Reading composite file /afs/cs.wisc.edu/p/devise/ext5/wenger/devise.dev2/solarisFixed bugs 543 and 544 (problems with cursor movement).

  Revision 1.32  1999/11/19 17:17:26  wenger
  Added View::SetVisualFilterCommand() method to clean up command-related
  code for filter setting.

  Revision 1.31  1999/10/01 21:08:34  wenger
  Fixed problem in DeviseCursor::IsOnCursor() that caused crash if cursor
  has no source view.

  Revision 1.30  1999/08/17 19:46:53  wenger
  Converted Condor UserMonth session from high/low symbols to piles for
  better representation of data; fixed some cursor/pile drawing bugs and
  TData switching bugs that I found in the process.

  Revision 1.29  1999/08/06 15:22:42  wenger
  DeviseCursor::MoveSource() now ensures that size does not change for
  fixed-size cursors -- fixes problem in Condor/UserMonth.ds session in
  JavaScreen.

  Revision 1.28  1999/08/05 21:42:33  wenger
  Cursor improvements: cursors can now be dragged in "regular" DEVise;
  cursors are now drawn with a contrasting border for better visibility;
  fixed bug 468 (cursor color not working).

  Revision 1.27  1999/07/30 21:26:49  wenger
  Partway to cursor dragging: code to change mouse cursor when on a DEVise
  cursor is in place (but disabled).

  Revision 1.26  1999/07/21 18:47:01  wenger
  Fixed bug with cursor grid when cursor location is negative.

  Revision 1.25  1999/04/29 17:36:32  wenger
  Implemented 'fixed cursor size' option (for the sake of the JavaScreen).

  Revision 1.24  1999/02/09 22:30:52  wenger
  Fixed bug in MoveSource() (wrong filter flag value).

  Revision 1.23  1999/02/08 20:06:24  wenger
  If a view is a dest. view of a cursor, and the view's visual filter
  gets changed such that the cursor is entirely outside the view, the
  cursor is moved to the center of the destination view.

  Revision 1.22  1999/02/02 17:14:26  wenger
  Fixed bug 422 (setting cursor dest w/o source causes crash).

  Revision 1.21  1999/01/29 21:09:41  wenger
  Fixed bug 451 (dragging cursor in JS bypasses cursor grid).

  Revision 1.20  1998/12/10 21:53:16  wenger
  Devised now sends GIFs to JavaScreen on a per-view rather than per-window
  basis; GIF "dirty" flags are now also referenced by view rather than by
  window.

  Revision 1.19  1998/09/25 22:07:07  wenger
  Found and fixed bug 397 (another problem with a cursor not connected to
  any views).

  Revision 1.18  1998/06/10 18:04:01  wenger
  Improved new cursor drawing (bug in Mesa implementation sometimes makes
  it look ugly); cursor color now saved in sessions.

  Revision 1.17  1998/06/09 20:05:59  wenger
  2D OpenGL cursor now drawn as shaded outline plus every-other-point
  "mesh"; OpenGL CursorStore and GLWindowRep on SGI now use color indices
  instead of RGB so that they work the same as the other architectures;
  added user interface to allow changing cursor color (merged through
  cursor_test_br_1).

  Revision 1.16.2.7  1998/06/09 18:15:27  wenger
  Added cursor color-changing capability.

  Revision 1.16.2.6  1998/06/08 22:10:09  wenger
  CursorStore pixmap is now correctly saved and restored.

  Revision 1.16.2.5  1998/06/08 21:49:10  wenger
  Cleaned up conditional-out code.

  Revision 1.16.2.4  1998/06/08 21:32:33  wenger
  2D OpenGL cursor now drawn as shaded outline plus every-other-point
  "mesh".

  Revision 1.16.2.3  1998/06/05 20:08:09  wenger
  Cursor in OpenGL now drawn as a shaded outline plus background color
  is changed.

  Revision 1.16.2.2  1998/06/05 17:55:16  wenger
  Cursor in OpenGL drawn as a shaded outline.

  Revision 1.16.2.1  1998/06/04 21:08:43  wenger
  Experimental drawing of 2D cursor in OpenGL by manipulating pixmap values.

  Revision 1.16  1998/05/28 15:04:56  wenger
  OpenGL cursors now drawn in view foreground color;
  fixes to OpenGL crashes with some sessions (bugs 342, 356?).

  Revision 1.15  1998/05/05 15:14:38  zhenhai
  Implemented 3D Cursor as a rectangular block in the destination view
  showing left, right, top, bottom, front and back cutting planes of the
  source view.

  Revision 1.14  1998/04/13 22:24:42  zhenhai
  Optimized 2D cursors to read and draw individual patches instead
  of patches for the whole region. Added 3D cursors to show directions.
  After adding a 3D cursor (same as adding 2D cursors by first
  creating the cursor, then selecting the source and destination),
  the direction of the cone (where its top is pointing to) in one graph shows the
  location and direction of the camera in another graph.

  Revision 1.13  1998/04/01 17:11:26  wenger
  4/left arrow, 5 (home), and 6/right arrow keys, and cursor movements
  now get sent to slaves during collaboration.

  Revision 1.12  1998/03/26 15:21:20  zhenhai
  The cursor drawings now use CursorStore as backup instead of using
  XOR mode for drawing and erasing.

  Revision 1.11  1997/11/24 23:14:11  weaver
  Changes for the new ColorManager.

  Revision 1.10  1997/06/09 14:46:33  wenger
  Added cursor grid; fixed bug 187; a few minor cleanups.

  Revision 1.9.10.1  1997/05/21 20:39:36  weaver
  Changes for new ColorManager

  Revision 1.9  1997/01/23 17:38:25  jussi
  Removed references to GetXMin().

  Revision 1.8  1996/11/13 16:56:04  wenger
  Color working in direct PostScript output (which is now enabled);
  improved ColorMgr so that it doesn't allocate duplicates of colors
  it already has, also keeps RGB values of the colors it has allocated;
  changed Color to GlobalColor, LocalColor to make the distinction
  explicit between local and global colors (_not_ interchangeable);
  fixed global vs. local color conflict in View class; changed 'dali'
  references in command-line arguments to 'tasvir' (internally, the
  code still mostly refers to Dali).

  Revision 1.7  1996/06/13 00:14:28  jussi
  Added support for XY cursors. All types of cursors can now
  be moved by clicking on their new location in the data area.
  Previously only the X label area was sensitive for cursor
  movement.

  Revision 1.6  1996/05/14 18:07:55  jussi
  Cursor now inserts itself into the view callback list at
  construction time, and removes itself at destruction time.
  There was a problem that a cursor was destroyed after
  a view was destroyed, and the if condition protecting
  the removal of the cursor from the view callback list
  failed to fire.

  Revision 1.5  1996/01/16 16:16:38  jussi
  Improved code that hides and draws cursors when source
  and/or destination changes.

  Revision 1.4  1995/12/29 18:26:53  jussi
  Added FilterAboutToChange() to facilitate new cursor mechanism.

  Revision 1.3  1995/12/14 16:55:42  jussi
  Small fix in GetVisualFilter.

  Revision 1.2  1995/09/05 21:12:33  jussi
  Added/updated CVS header.
*/

#include "Cursor.h"
#include "ViewGraph.h"
#include "Color.h"
#include "XColor.h"
#include "Util.h"

//#define DEBUG

//******************************************************************************
// Constructors and Destructors
//******************************************************************************

DeviseCursor::DeviseCursor(char *name, VisualFlag flag,
						   Boolean useGrid, Coord gridX, Coord gridY,
						   Boolean edgeGrid)
{
  _name = name;
  _visFlag = flag;
  _src = 0;
  _dst = 0;
  _useGrid = useGrid;
  _gridX = gridX;
  _gridY = gridY;
  _edgeGrid = edgeGrid;
  _cursorColor = GetPColorID(whiteColor);
  _fixedSize = false;
  _partInDest = true;
  _allInDest = false;
  _oldPixelsValid = false;
  _inMoveSource = false;

  _saveStateX = false;
  _saveStateY = false;
  _keepPropX = false;
  _keepPropY = false;

  _stateValid = false;

  View::InsertViewCallback(this);
}

DeviseCursor::~DeviseCursor(void)
{
  View::DeleteViewCallback(this);

  Boolean redrawCursors = false;

  if (_dst) {
    redrawCursors = _dst->HideCursors();
  }

  if (_dst) {
    _dst->DeleteCursor(this);
  }

  if (_dst && redrawCursors) {
    (void)_dst->DrawCursors();
  }
}

//******************************************************************************

//
// Note: I had thought of not allowing the source and destination to be
// set to the same view, since that doesn't really make any sense.
// However, I decided that it may be useful to allow that state to exist
// because you might have things that way temporarily while you're changing
// a cursor around, and it doesn't seem to hurt anything, so I'm leaving
// in the possibility of having the source and destination views be the
// same.  RKW 1999-02-02.
//

/* Set source view. Changing this view's visual filter
   changes in the cursor's position. Can also set to NULL */

void DeviseCursor::SetSource(View *view)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::SetSource(%s)\n", GetName(),
    view->GetName());
#endif

  // Don't do anything if the given view is already the source.
  if (view == _src) return;

  Boolean redrawCursors = false;

  if (_dst) {
    redrawCursors = _dst->HideCursors();
  }

  _src = view;

  if (_dst && redrawCursors) {
    (void)_dst->DrawCursors();
  }
}

/* Set destination: this is where the cursor will be drawn.
   Can also set to NULL. */

void DeviseCursor::SetDst(View *view)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::SetDst(%s)\n", GetName(),
    view->GetName());
#endif

  // Don't do anything if the given view is already the destination.
  if (view == _dst) return;

  Boolean redrawCursors = false;

  if (_dst) {
    redrawCursors = _dst->HideCursors();
    _dst->DeleteCursor(this);
    if (redrawCursors) {
      (void)_dst->DrawCursors();        // redraw cursors at old destination
    }
  }
  
  _dst = view;

  redrawCursors = false;
  if (_dst) {
    redrawCursors = _dst->HideCursors();
    _dst->AppendCursor(this);
    if (redrawCursors) {
      (void)_dst->DrawCursors();          // redraw cursors at new destination
    }
  }
}

void
DeviseCursor::SetFlag(VisualFlag flag)
{
#if defined(DEBUG)
  printf("DeviseCursor::SetFlag(%d)\n", flag);
#endif

  _visFlag = flag;

  // Force cursor to be redrawn in destination view.
  if (_dst) {
    (void)_dst->HideCursors();
    (void)_dst->DrawCursors();
  }
}

/* Get current visual filter. return TRUE if it exists. */

Boolean DeviseCursor::GetVisualFilter(const VisualFilter *&filter)
{
  if (!_src) {
    return false;
  }
  
  _src->GetVisualFilter(_filter);
  _filter.flag = _visFlag;
  filter = &_filter;
  return true;
}

void DeviseCursor::FilterAboutToChange(View *view)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::FilterAboutToChange(%s)\n", GetName(),
    view->GetName());
#endif

  if (_dst && view == _src) {
    (void)_dst->HideCursors();
  }
}

void DeviseCursor::FilterChanged(View *view, const VisualFilter &filter,
				 int flushed)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::FilterChanged(%s)\n", GetName(), view->GetName());
#endif

  // Only do the constraints check if a view relevant to this cursor has
  // changed.
  if ((_dst && view == _dst) || (_src && view == _src)) {
    SatisfyConstraints();
  }

  if (_dst && view == _src) {
    (void)_dst->DrawCursors();
  }
}

void DeviseCursor::ViewDestroyed(View *view)
{
  if (_dst && (view == _src || view == _dst)) {
    (void)_dst->HideCursors();
  }

  if (view == _src) {
    _src = 0;
  }

  if (view == _dst) {
    _dst = 0;
  }
}

void DeviseCursor::MoveSource(Coord x, Coord y, Coord width, Coord height,
    Boolean doCommand)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::MoveSource(%g, %g, %g, %g, %d)\n", GetName(),
      x, y, width, height, doCommand);
#endif

  if (!_src) {
    return;
  }

  if (_inMoveSource) {
	// Since MoveSource() calls View::SetVisualFilter(), which will eventually
	// call FilterChanged(), which calls SatisfyConstraints(), which calls
	// MoveSource(), keep ourselves from getting too tangled up here.
	// RKW 2000-09-11.
    return;
  }

  _inMoveSource = true;

  VisualFilter filter;
  // Note: we must get the filter directly from the source view here
  // so that the flag is correct.
  _src->GetVisualFilter(filter);
  VisualFilter oldFilter = filter;

  // If width or height is less than 0 (default argument value) keep it
  // the same.
  if (width < 0.0) {
    width = filter.xHigh - filter.xLow;
  }
  if (height < 0.0) {
    height = filter.yHigh - filter.yLow;
  }

  CursorLocation location;
  location.xCen = x;
  location.yCen = y;
  location.width = width;
  location.height = height;

  SatisfyConstraints(location);

  if (_visFlag & VISUAL_X) {
    filter.xLow = location.xCen - location.width / 2.0;
    filter.xHigh = location.xCen + location.width / 2.0;
  }
  if (_visFlag & VISUAL_Y) {
    filter.yLow = location.yCen - location.height / 2.0;
    filter.yHigh = location.yCen + location.height / 2.0;
  }

  if (!(filter == oldFilter)) {
    if (_dst) {
      (void)_dst->HideCursors();
    }

    if (doCommand) {
      _src->SetVisualFilterCommand(filter);
    } else {
      _src->SetVisualFilter(filter);
    }
  }

  _inMoveSource = false;
}

void
DeviseCursor::SaveState()
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::SaveState()\n", GetName());
#endif

  // Save the source view's current visual filter, indexed by TData
  // and parent value.
  ((ViewGraph *)_src)->SaveViewSymFilter();

  // Now save the source view's visual filter as a proportion of the
  // destination view's filter.
  VisualFilter srcFilter;
  _src->GetVisualFilter(srcFilter);
  VisualFilter dstFilter;
  _dst->GetVisualFilter(dstFilter);

  _proportions.xLow = (srcFilter.xLow - dstFilter.xLow) /
      (dstFilter.xHigh - dstFilter.xLow);
  _proportions.xHigh = (srcFilter.xHigh - dstFilter.xLow) /
      (dstFilter.xHigh - dstFilter.xLow);
  _proportions.yLow = (srcFilter.yLow - dstFilter.yLow) /
      (dstFilter.yHigh - dstFilter.yLow);
  _proportions.yHigh = (srcFilter.yHigh - dstFilter.yLow) /
      (dstFilter.yHigh - dstFilter.yLow);

  _stateValid = true;
}

void
DeviseCursor::RestoreState()
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::RestoreState()\n", GetName());
#endif
  if (_stateValid) {
    VisualFilter srcFilter;
    _src->GetVisualFilter(srcFilter);
    VisualFilter dstFilter;
    _dst->GetVisualFilter(dstFilter);

	if (_keepPropX) {
      srcFilter.xLow = _proportions.xLow *
          (dstFilter.xHigh - dstFilter.xLow) + dstFilter.xLow;
      srcFilter.xHigh = _proportions.xHigh *
          (dstFilter.xHigh - dstFilter.xLow) + dstFilter.xLow;
	}
	if (_keepPropY) {
      srcFilter.yLow = _proportions.yLow *
          (dstFilter.yHigh - dstFilter.yLow) + dstFilter.yLow;
      srcFilter.yHigh = _proportions.yHigh *
          (dstFilter.yHigh - dstFilter.yLow) + dstFilter.yLow;
    }

    _src->SetVisualFilter(srcFilter);

    // If we don't have an entry for the relevant TData/parent value
    // combination, this won't do anything; otherwise it will override
    // the the proportions.
    ((ViewGraph *)_src)->RestoreViewSymFilter(_saveStateX, _saveStateY);

    // We only want to do this once, otherwise the user won't be able
    // to change the cursor themselves...
    _stateValid = false;
  }
}

void
DeviseCursor::SetProportions(Coord xlo, Coord ylo, Coord xhi, Coord yhi)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::SetProportions((%g, %g), (%g, %g))\n",
      GetName(), xlo, ylo, xhi, yhi);
#endif

  VisualFilter srcFilter;
  _src->GetVisualFilter(srcFilter);
  VisualFilter dstFilter;
  _dst->GetVisualFilter(dstFilter);

  srcFilter.xLow = xlo * (dstFilter.xHigh - dstFilter.xLow) +
      dstFilter.xLow;
  srcFilter.xHigh = xhi * (dstFilter.xHigh - dstFilter.xLow) +
      dstFilter.xLow;
  srcFilter.yLow = ylo * (dstFilter.yHigh - dstFilter.yLow) +
      dstFilter.yLow;
  srcFilter.yHigh = yhi * (dstFilter.yHigh - dstFilter.yLow) +
      dstFilter.yLow;

  _src->SetVisualFilter(srcFilter);
}

void DeviseCursor::DrawCursorFill(WindowRep* w)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::DrawCursorFill()\n", _name);
#endif

  const VisualFilter *filter;
  GetVisualFilter(filter);

  if (_src && _src->GetNumDimensions()==2
   && _dst && _dst->GetNumDimensions()==2) {
    Coord xLowPix, yLowPix, xHighPix, yHighPix;
    w->Transform(filter->xLow, filter->yLow, xLowPix, yLowPix);
    w->Transform(filter->xHigh, filter->yHigh, xHighPix, yHighPix);

    //
    // Fill in "mesh" of the cursor color.
    //
    w->PushTop();
    w->MakeIdentity();
	w->SetForeground(_cursorColor);
    for (int line = (int)yLowPix; line <= (int)yHighPix; line+=1) {
      for (int column = (int)xLowPix + (line%2) * 2; column <= (int)xHighPix;
		  column+=4) {
	    w->DrawPixel((Coord)column, (Coord)line);
      }
    }
    w->PopTransform();
  }
}

void DeviseCursor::DrawCursorBorder(WindowRep* w)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::DrawCursorBorder()\n", _name);
#endif

  const VisualFilter *filter;
  GetVisualFilter(filter);

  if (_dst) {
    w->SetForeground(_dst->GetForeground());
  }

  if (_src && _src->GetNumDimensions()==2
   && _dst&& _dst->GetNumDimensions()==2) {
    Coord xLowPix, yLowPix, xHighPix, yHighPix;
    w->Transform(filter->xLow, filter->yLow, xLowPix, yLowPix);
    w->Transform(filter->xHigh, filter->yHigh, xHighPix, yHighPix);

    //
    // Outline the cursor in the view foreground color.
    //
    w->SetForeground(_dst->GetForeground());
    w->AbsoluteLine((int)xLowPix+1, (int)yLowPix+1, (int)xLowPix+1,
	(int)yHighPix-1, 3);
    w->AbsoluteLine((int)xHighPix-1, (int)yLowPix+1, (int)xHighPix-1,
	(int)yHighPix-1, 3);

    w->AbsoluteLine((int)xLowPix+1, (int)yLowPix+1, (int)xHighPix-1,
	(int)yLowPix+1, 3);
    w->AbsoluteLine((int)xLowPix+1, (int)yHighPix-1, (int)xHighPix-1,
	(int)yHighPix-1, 3);

    //
    // Draw a highlight and shadow around the outline.
    //
    w->SetForeground(GetPColorID(whiteColor));
    w->AbsoluteLine((int)xLowPix, (int)yLowPix, (int)xLowPix,
	(int)yHighPix, 3);
    w->AbsoluteLine((int)xLowPix, (int)yHighPix, (int)xHighPix,
	(int)yHighPix, 3);

    w->SetForeground(GetPColorID(blackColor));
    w->AbsoluteLine((int)xHighPix, (int)yLowPix, (int)xHighPix,
	(int)yHighPix, 3);
    w->AbsoluteLine((int)xLowPix, (int)yLowPix, (int)xHighPix,
	(int)yLowPix, 3);

    w->SetForeground(_dst->GetForeground());
    w->Line(xHighPix/2+xLowPix/2, yLowPix+1,
              xHighPix/2+xLowPix/2, yHighPix-1, 1);
    w->Line(xLowPix-1, yLowPix/2+yHighPix/2,
              xHighPix-1, yLowPix/2+yHighPix/2, 1);
  }

  if (_src && _src->GetNumDimensions()==3
   && _dst&& _dst->GetNumDimensions()==3) {
    w->PushTop();
    w->SetCamCursorTransform(filter->camera);
    Coord x[8], y[8], z[8];
    x[0]=filter->camera.min_x;
    x[1]=filter->camera.max_x;
    x[2]=filter->camera.max_x;
    x[3]=filter->camera.min_x;

    x[4]=filter->camera.min_x;
    x[5]=filter->camera.max_x;
    x[6]=filter->camera.max_x;
    x[7]=filter->camera.min_x;

    y[0]=filter->camera.min_y;
    y[1]=filter->camera.min_y;
    y[2]=filter->camera.max_y;
    y[3]=filter->camera.max_y;

    y[4]=filter->camera.min_y;
    y[5]=filter->camera.min_y;
    y[6]=filter->camera.max_y;
    y[7]=filter->camera.max_y;

    z[0]=-filter->camera.near;
    z[1]=-filter->camera.near;
    z[2]=-filter->camera.near;
    z[3]=-filter->camera.near;

    z[4]=-filter->camera.far;
    z[5]=-filter->camera.far;
    z[6]=-filter->camera.far;
    z[7]=-filter->camera.far;

#define DRAWCURSORLINE(a,b) w->Line3D(x[a],y[a],z[a],x[b],y[b],z[b],1.0)
    DRAWCURSORLINE(0,1);
    DRAWCURSORLINE(1,2);
    DRAWCURSORLINE(2,3);
    DRAWCURSORLINE(3,0);

    DRAWCURSORLINE(4,5);
    DRAWCURSORLINE(5,6);
    DRAWCURSORLINE(6,7);
    DRAWCURSORLINE(7,4);

    DRAWCURSORLINE(0,4);
    DRAWCURSORLINE(1,5);
    DRAWCURSORLINE(2,6);
    DRAWCURSORLINE(3,7);

    w->PopTransform();
  }
}

void DeviseCursor::SetCursorColor(PColorID color)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::SetCursorColor(%ld)\n", _name, color);
#endif

  // Force all cursors in the destination view to be redrawn.
  if (_dst != NULL) {
    _dst->HideCursors();
  }

  _cursorColor = color;

  // Force all cursors in the destination view to be redrawn.
  if (_dst != NULL) {
    _dst->DrawCursors();
  }
}

CursorHit::HitType
DeviseCursor::IsOnCursor(Coord dataX, Coord dataY, Coord dataXTol,
    Coord dataYTol)
{
#if defined(DEBUG)
  printf("Cursor(%s)::IsOnCursor(%g, %g, %g, %g)\n", GetName(), dataX, dataY,
    dataXTol, dataYTol);
#endif

  CursorHit::HitType result = CursorHit::CursorNone;

  //
  // We may *not* have a source set for this cursor!
  //
  if (!_src) {
    return result;
  }

  dataXTol = ABS(dataXTol);
  dataYTol = ABS(dataYTol);

  VisualFilter filter;
  _src->GetVisualFilter(filter);

  //
  // Figure out whether we're on the cursor, and if so if we're on and
  // edge or corner.
  //
  Boolean outOfCursor = false;
  Boolean topEdge = false;
  Boolean bottomEdge = false;
  Boolean leftEdge = false;
  Boolean rightEdge = false;

  if ((_visFlag & VISUAL_X) &&
      (dataX < filter.xLow || dataX > filter.xHigh)) {
    outOfCursor = true;
  } else if ((_visFlag & VISUAL_Y) &&
      (dataY < filter.yLow || dataY > filter.yHigh)) {
    outOfCursor = true;
  } else {
    if (!_fixedSize && (_visFlag & VISUAL_X)) {
      if (dataX < filter.xLow + dataXTol) {
        leftEdge = true;
      } else if (dataX > filter.xHigh - dataXTol) {
        rightEdge = true;
      }
    }

    if (!_fixedSize && (_visFlag & VISUAL_Y)) {
      if (dataY < filter.yLow + dataYTol) {
        bottomEdge = true;
      } else if (dataY > filter.yHigh - dataYTol) {
        topEdge = true;
      }
    }
  }

  if (outOfCursor) {
    result = CursorHit::CursorNone;
  } else if (topEdge) {
    if (leftEdge) {
      result = CursorHit::CursorNW;
    } else if (rightEdge) {
      result = CursorHit::CursorNE;
    } else {
      result = CursorHit::CursorN;
    }
  } else if (bottomEdge) {
    if (leftEdge) {
      result = CursorHit::CursorSW;
    } else if (rightEdge) {
      result = CursorHit::CursorSE;
    } else {
      result = CursorHit::CursorS;
    }
  } else if (leftEdge) {
    result = CursorHit::CursorW;
  } else if (rightEdge) {
    result = CursorHit::CursorE;
  } else {
    result = CursorHit::CursorMid;
  }

  return result;
}

void
DeviseCursor::FindNewPosition(int pixX1, int pixY1, int pixX2, int pixY2, 
    CursorHit::HitType hitType, Coord &dataXLow, Coord &dataYLow,
    Coord &dataXHigh, Coord &dataYHigh)
{
#if defined(DEBUG)
  printf("DeviseCursor::FindNewPosition((%d, %d), (%d, %d), %d)\n", pixX1, pixY1,
      pixX2, pixY2, hitType);
#endif

  if (!_src) {
    const int bufLen = 1024;
    char buf[bufLen];
    int formatted = snprintf(buf, bufLen, "Calling DeviseCursor::"
      "FindNewPosition on cursor %s which has no source view", GetName());
    checkAndTermBuf(buf, bufLen, formatted);
    reportErrNosys(buf);
    return;
  }

  VisualFilter filter;
  _src->GetVisualFilter(filter);

#if defined(DEBUG)
  printf("  Old filter = (%g, %g), (%g, %g)\n", filter.xLow, filter.yLow,
      filter.xHigh, filter.yHigh);
#endif

  Coord dataX1, dataY1, dataX2, dataY2;
  WindowRep *winRep = _dst->GetWindowRep();
  winRep->InverseTransform(pixX1, pixY1, dataX1, dataY1);
  winRep->InverseTransform(pixX2, pixY2, dataX2, dataY2);

#if defined(DEBUG)
  printf("  Transformed points = (%g, %g), (%g, %g)\n", dataX1, dataY1,
      dataX2, dataY2);
#endif

  VisualFilter oldFilter = filter;

  switch (hitType) {
  case CursorHit::CursorNone:
    DOASSERT(false, "Function shouldn't be called if no cursor hit");
    break;

  case CursorHit::CursorNW:
    filter.xLow += (dataX2 - dataX1);
    filter.yHigh += (dataY2 - dataY1);
    break;

  case CursorHit::CursorN:
    filter.yHigh += (dataY2 - dataY1);
    break;

  case CursorHit::CursorNE:
    filter.xHigh += (dataX2 - dataX1);
    filter.yHigh += (dataY2 - dataY1);
    break;

  case CursorHit::CursorW:
    filter.xLow += (dataX2 - dataX1);
    break;

  case CursorHit::CursorMid:
    filter.xLow += (dataX2 - dataX1);
    filter.yLow += (dataY2 - dataY1);
    filter.xHigh += (dataX2 - dataX1);
    filter.yHigh += (dataY2 - dataY1);
    break;

  case CursorHit::CursorE:
    filter.xHigh += (dataX2 - dataX1);
    break;

  case CursorHit::CursorSW:
    filter.xLow += (dataX2 - dataX1);
    filter.yLow += (dataY2 - dataY1);
    break;

  case CursorHit::CursorS:
    filter.yLow += (dataY2 - dataY1);
    break;

  case CursorHit::CursorSE:
    filter.xHigh += (dataX2 - dataX1);
    filter.yLow += (dataY2 - dataY1);
    break;

  default:
    DOASSERT(false, "Illegal/invalid CursorHit::HitType value");
    break;
  }

  if (!(GetFlag() & VISUAL_X)) {
    filter.xLow = oldFilter.xLow;
    filter.xHigh = oldFilter.xHigh;
  }
  if (!(GetFlag() & VISUAL_Y)) {
    filter.yLow = oldFilter.yLow;
    filter.yHigh = oldFilter.yHigh;
  }

  CursorLocation location;
  location.xCen = (filter.xLow + filter.xHigh) / 2.0;
  location.width = filter.xHigh - filter.xLow;
  location.yCen = (filter.yLow + filter.yHigh) / 2.0;
  location.height = filter.yHigh - filter.yLow;

  SatisfyConstraints(location);

  dataXLow = location.xCen - location.width / 2.0;
  dataXHigh = location.xCen + location.width / 2.0;
  dataYLow = location.yCen - location.height / 2.0;
  dataYHigh = location.yCen + location.height / 2.0;

#if defined(DEBUG)
  printf("  New filter = (%g, %g), (%g, %g)\n", dataXLow, dataYLow, dataXHigh,
      dataYHigh);
#endif
}

Boolean
DeviseCursor::GetDestPixels(int &pixX1, int &pixY1, int &pixX2, int &pixY2)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::GetDestPixels()\n", GetName());
#endif

  Boolean result = true;

  if (_src) {
    VisualFilter cFilter;
    _src->GetVisualFilter(cFilter);
    result = GetDestPixels(cFilter.xLow, cFilter.yLow, cFilter.xHigh,
        cFilter.yHigh, pixX1, pixY1, pixX2, pixY2);
  } else {
#if defined(DEBUG)
    printf("  Cursor has no source\n");
#endif
    result = false;
  }

  return result;
}

Boolean
DeviseCursor::GetDestPixels(Coord dataXLow, Coord dataYLow, Coord dataXHigh,
    Coord dataYHigh,int &pixX1, int &pixY1, int &pixX2, int &pixY2)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::GetDestPixels()\n", GetName());
#endif

  Boolean result = true;

  VisualFilter cFilter, vFilter;

  cFilter.xLow = dataXLow;
  cFilter.yLow = dataYLow;
  cFilter.xHigh = dataXHigh;
  cFilter.yHigh = dataYHigh;

#if defined(DEBUG)
  printf("  cFilter = (%g, %g), (%g, %g)\n", cFilter.xLow, cFilter.yLow,
      cFilter.xHigh, cFilter.yHigh);
#endif

  if (_dst) {
    if (!_dst->GetWindowRep()) {
#if defined(DEBUG)
      printf("  Cursor has no destination WindowRep\n");
#endif
      result = false;
    } else {
      _dst->GetVisualFilter(vFilter);
    }
  } else {
#if defined(DEBUG)
    printf("  Cursor has no destination\n");
#endif
    result = false;
  }

#if defined(DEBUG)
  printf("  vFilter = (%g, %g), (%g, %g)\n", vFilter.xLow, vFilter.yLow,
      vFilter.xHigh, vFilter.yHigh);
#endif

  // Make sure at least part of the cursor is within the destination view.
  if (result) {
    if (GetFlag() & VISUAL_X) {
      if (cFilter.xHigh < vFilter.xLow || cFilter.xLow > vFilter.xHigh) {
        result = false;
      }
    }
    if (GetFlag() & VISUAL_Y) {
      if (cFilter.yHigh < vFilter.yLow || cFilter.yLow > vFilter.yHigh) {
        result = false;
      }
    }
  }

  if (result) {
    Coord dataXLow = MAX(cFilter.xLow, vFilter.xLow);
    Coord dataYLow = MAX(cFilter.yLow, vFilter.yLow);
    Coord dataXHigh = MIN(cFilter.xHigh, vFilter.xHigh);
    Coord dataYHigh = MIN(cFilter.yHigh, vFilter.yHigh);

    if (!(GetFlag() & VISUAL_X)) {
      dataXLow = vFilter.xLow;
      dataXHigh = vFilter.xHigh;
    }

    if (!(GetFlag() & VISUAL_Y)) {
      dataYLow = vFilter.yLow;
      dataYHigh = vFilter.yHigh;
    }

#if defined(DEBUG)
  printf("  cursor data = (%g, %g), (%g, %g)\n", dataXLow, dataYLow,
      dataXHigh, dataYHigh);
#endif

    WindowRep *winRep = _dst->GetWindowRep();
    Coord pixX1C, pixY1C, pixX2C, pixY2C;
    winRep->Transform(dataXLow, dataYLow, pixX1C, pixY1C);
    winRep->Transform(dataXHigh, dataYHigh, pixX2C, pixY2C);
    pixX1 = (int)floor(pixX1C + 0.5);
    pixY1 = (int)floor(pixY1C + 0.5);
    pixX2 = (int)floor(pixX2C + 0.5);
    pixY2 = (int)floor(pixY2C + 0.5);

	int dstX, dstY;
	unsigned dstWidth, dstHeight;
	_dst->Geometry(dstX, dstY, dstWidth, dstHeight);
	if (MAX(pixX1, pixX2) < 0 || MIN(pixX1, pixX2) > (int)dstWidth ||
	    MAX(pixY1, pixY2) < 0 || MIN(pixY1, pixY2) > (int)dstHeight) {
#if defined(DEBUG)
	  char errBuf[1024];
	  int formatted = snprintf(errBuf, sizeof(errBuf),
	      "Cursor <%s> is in view <%s> according to visual "
	      "filters but not according to pixels -- WindowRep transform may "
		  "be incorrect", GetName(), _dst->GetName());
	  checkAndTermBuf2(errBuf, formatted);
	  reportErrNosys(errBuf);
#endif
	  result = false;
	}

#if defined(DEBUG)
    printf("  Pixels: (%d, %d), (%d, %d)\n", pixX1, pixY1, pixX2, pixY2);
#endif
  }

#if defined(DEBUG)
    printf("  Returning %d\n", result);
#endif

  return result;
}

void
DeviseCursor::MatchGrid(CursorLocation &location)
{
  if (_visFlag & VISUAL_X) {
    if (_useGrid && (_gridX != 0.0)) {
      /* Round location to nearest grid point. */
	  if (_edgeGrid) {
	    Coord xLow = location.xCen - location.width / 2.0;
	    Coord xHi = location.xCen + location.width / 2.0;

		// The extra 0.5s here put the cursor edges halfway between multiples
		// of the grid size.
        int tmp = (int)floor((xLow / _gridX) + 0.5 - 0.5);
		xLow = _gridX * (tmp + 0.5);
        tmp = (int)floor((xHi / _gridX) + 0.5 + 0.5);
		xHi = _gridX * (tmp - 0.5);

		location.width = ABS(xHi - xLow); // ABS() just to be safe.
		location.xCen = (xLow + xHi) / 2.0;
	  } else {
        int tmp = (int)floor((location.xCen / _gridX) + 0.5);
        location.xCen = _gridX * tmp;
	  }
    }
  }

  if (_visFlag & VISUAL_Y) {
    if (_useGrid && (_gridY != 0.0)) {
      /* Round location to nearest grid point. */
	  if (_edgeGrid) {
	    Coord yLow = location.yCen - location.height / 2.0;
	    Coord yHi = location.yCen + location.height / 2.0;

		// The extra 0.5s here put the cursor edges halfway between multiples
		// of the grid size.
        int tmp = (int)floor((yLow / _gridY) + 0.5 - 0.5);
		yLow = _gridY * (tmp + 0.5);
        tmp = (int)floor((yHi / _gridY) + 0.5 + 0.5);
		yHi = _gridY * (tmp - 0.5);

		location.height = ABS(yHi - yLow); // ABS() just to be safe.
		location.yCen = (yLow + yHi) / 2.0;
	  } else {
        int tmp = (int)floor((location.yCen / _gridY) + 0.5);
        location.yCen = _gridY * tmp;
	  }
    }
  }
}

void
DeviseCursor::SetOldDestPixels(int pixX1, int pixY1, int pixX2, int pixY2)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::SetOldDestPixels(%d, %d, %d, %d)\n", GetName(),
      pixX1, pixY1, pixX2, pixY2);
#endif

  _oldPixX1 = pixX1;
  _oldPixY1 = pixY1;
  _oldPixX2 = pixX2;
  _oldPixY2 = pixY2;
  _oldPixelsValid = true;
}

Boolean
DeviseCursor::GetOldDestPixels(int &pixX1, int &pixY1, int &pixX2, int &pixY2)
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::GetOldDestPixels()\n", GetName());
#endif

  if (_oldPixelsValid) {
    pixX1 = _oldPixX1;
    pixY1 = _oldPixY1;
    pixX2 = _oldPixX2;
    pixY2 = _oldPixY2;
  }

  return _oldPixelsValid;
}

void
DeviseCursor::InvalidateOldDestPixels()
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::InvalidateOldDestPixels()\n", GetName());
#endif

  _oldPixelsValid = false;
}

void
DeviseCursor::SetGrid(Boolean useGrid, Coord gridX, Coord gridY,
    Boolean edgeGrid)
{
  _useGrid = useGrid;
  _gridX = gridX;
  _gridY = gridY;
  _edgeGrid = edgeGrid;

  if (_useGrid) {
    SatisfyConstraints();
  }
}

void
DeviseCursor::SetPartInDest(Boolean partInDest)
{
  _partInDest = partInDest;

  if (_partInDest) {
    SatisfyConstraints();
  }
}

void
DeviseCursor::SetAllInDest(Boolean allInDest)
{
  _allInDest = allInDest;

  if (_allInDest) {
    SatisfyConstraints();
  }
}

void
DeviseCursor::SatisfyConstraints()
{
#if defined(DEBUG)
  printf("DeviseCursor(%s)::SatisfyConstraints()\n", GetName());
#endif

  if (!_src) {
    return;
  }

  VisualFilter filter;
  _src->GetVisualFilter(filter);

  Coord xCen = (filter.xLow + filter.xHigh) / 2.0;
  Coord yCen = (filter.yLow + filter.yHigh) / 2.0;
  Coord width = filter.xHigh - filter.xLow;
  Coord height = filter.yHigh - filter.yLow;

  MoveSource(xCen, yCen, width, height, false);
}

void
DeviseCursor::SatisfyConstraints(CursorLocation& location)
{
  if (_fixedSize) {
    VisualFilter filter;
    _src->GetVisualFilter(filter);

    // Force the new width and height to be the same as the old ones.
    location.width = filter.xHigh - filter.xLow;
    location.height = filter.yHigh - filter.yLow;
  }

  if (_partInDest) {
    PartInDest(location);
  }

  if (_allInDest) {
    AllInDest(location);
  }

  MatchGrid(location);
}

// Make sure at least part of the cursor is within the destination view.
void
DeviseCursor::PartInDest(CursorLocation& location)
{
  if (_dst) {
    Coord xLo = location.xCen - (location.width / 2.0);
    Coord xHi = location.xCen + (location.width / 2.0);
	Coord yLo = location.yCen - (location.height / 2.0);
	Coord yHi = location.yCen + (location.height / 2.0);

    //
    // Figure out whether any part of the cursor is within the destination
    // view's new visual filter.
    //
    const VisualFilter *dFilter = _dst->GetVisualFilter();
    Boolean outside = false;
    if ((_visFlag & VISUAL_X) &&
        (xHi < dFilter->xLow ||
        xLo > dFilter->xHigh)) {
      outside = true;
    }
    if ((_visFlag & VISUAL_Y) &&
        (yHi < dFilter->yLow ||
        yLo > dFilter->yHigh)) {
      outside = true;
    }

    //
    // Don't do this if destination view is unmapped because we're probably
    // in the middle of changing around child views.
    //
    if (outside && _dst->Mapped()) {
      // The cursor is outside the visual filter -- move it to the center
      // of the destination view.
      if (_visFlag & VISUAL_X) {
        location.xCen = (dFilter->xLow + dFilter->xHigh) / 2.0;
	  }
      if (_visFlag & VISUAL_Y) {
        location.yCen = (dFilter->yLow + dFilter->yHigh) / 2.0;
	  }
    }
  }
}

// Make sure all of the cursor is within the destination view.
void
DeviseCursor::AllInDest(CursorLocation &location)
{
  if (_dst) {
    const VisualFilter *filter = _dst->GetVisualFilter();

    if (_visFlag & VISUAL_X) {
      Coord xLo = location.xCen - (location.width / 2.0);
      Coord xHi = location.xCen + (location.width / 2.0);

	  Boolean changed = false;

      if (location.width > filter->xHigh - filter->xLow) {
	    xLo = filter->xLow;
	    xHi = filter->xHigh;
		changed = true;
	  } else if (xLo < filter->xLow) {
	    xLo = filter->xLow;
	    xHi = xLo + location.width;
		changed = true;
	  } else if (xHi > filter->xHigh) {
	    xHi = filter->xHigh;
	    xLo = xHi - location.width;
		changed = true;
	  }

	  if (changed) {
	    location.xCen = (xLo + xHi) / 2.0;
	    location.width = xHi - xLo;
	  }
	}

    if (_visFlag & VISUAL_Y) {
	  Coord yLo = location.yCen - (location.height / 2.0);
	  Coord yHi = location.yCen + (location.height / 2.0);

	  Boolean changed = false;

      if (location.height > filter->yHigh - filter->yLow) {
	    yLo = filter->yLow;
	    yHi = filter->yHigh;
		changed = true;
	  } else if (yLo < filter->yLow) {
	    yLo = filter->yLow;
	    yHi = yLo + location.height;
		changed = true;
	  } else if (yHi > filter->yHigh) {
	    yHi = filter->yHigh;
	    yLo = yHi - location.height;
		changed = true;
	  }

	  if (changed) {
	    location.yCen = (yLo + yHi) / 2.0;
	    location.height = yHi - yLo;
	  }
	}
  }
}

//******************************************************************************
