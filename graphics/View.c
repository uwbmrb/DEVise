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
  Revision 1.86  1996/11/20 20:34:55  wenger
  Fixed bugs 062, 073, 074, and 075; added workaround for bug 063; make
  some Makefile improvements so compile works first time; fixed up files
  to correspond to new query catalog name.

  Revision 1.85  1996/11/20 16:49:56  jussi
  Added AbortQuery() and removed AbortAndReexecute().

  Revision 1.84  1996/11/18 23:11:19  wenger
  Added procedures to generated PostScript to reduce the size of the
  output and speed up PostScript processing; added 'small font' capability
  and trademark notice to PostScript output; improved text positioning in
  PostScript output (but still a ways to go); added a little debug code;
  fixed data/axis area bugs (left gaps); fixed misc. bugs in color handling.

  Revision 1.83  1996/11/18 18:12:53  donjerko
  Added DTE make stuff

  Revision 1.82  1996/11/13 16:56:13  wenger
  Color working in direct PostScript output (which is now enabled);
  improved ColorMgr so that it doesn't allocate duplicates of colors
  it already has, also keeps RGB values of the colors it has allocated;
  changed Color to GlobalColor, LocalColor to make the distinction
  explicit between local and global colors (_not_ interchangeable);
  fixed global vs. local color conflict in View class; changed 'dali'
  references in command-line arguments to 'tasvir' (internally, the
  code still mostly refers to Dali).

  Revision 1.81  1996/11/07 22:40:14  wenger
  More functions now working for PostScript output (FillPoly, for example);
  PostScript output also working for piled views; PSWindowRep member
  functions no longer do so much unnecessary rounding to integers (left
  over from XWindowRep); kept in place (but disabled) a bunch of debug
  code I added while figuring out piled views; added PostScript.doc file
  for some high-level documentation on the PostScript output code.

  Revision 1.80  1996/10/28 15:55:45  wenger
  Scaling and clip masks now work for printing multiple views in a window
  to PostScript; (direct PostScript printing still disabled pending correct
  text positioning and colors); updated all dependencies except Linux.

  Revision 1.79  1996/10/18 20:34:09  wenger
  Transforms and clip masks now work for PostScript output; changed
  WindowRep::Text() member functions to ScaledText() to make things
  more clear; added WindowRep::SetDaliServer() member functions to make
  Dali stuff more compatible with client/server library.

  Revision 1.78  1996/10/02 15:23:38  wenger
  Improved error handling (modified a number of places in the code to use
  the DevError class).

  Revision 1.77  1996/09/27 15:52:34  wenger
  Fixed a number of memory leaks.

  Revision 1.76  1996/09/19 20:11:53  wenger
  More PostScript output code (still disabled); some code for drawing
  view borders (disabled).

  Revision 1.75  1996/09/10 20:07:10  wenger
  High-level parts of new PostScript output code are in place (conditionaled
  out for now so that the old code is used until the new code is fully
  working); changed (c) (tm) in windows so images are not copyrighted
  by DEVise; minor bug fixes; added more debug code in the course of working
  on the PostScript stuff.

  Revision 1.74  1996/09/06 06:59:43  beyer
  - Improved support for patterns, modified the pattern bitmaps.
  - possitive pattern numbers are used for opaque fills, while
    negative patterns are used for transparent fills.
  - Added a border around filled shapes.
  - ShapeAttr3 is (temporarily) interpreted as the width of the border line.

  Revision 1.73  1996/09/05 22:18:12  jussi
  Fixed problem with system hanging in batch mode.

  Revision 1.72  1996/08/30 18:41:04  wenger
  Fixed bug 036 (problem with piled views with client/server software).

  Revision 1.71  1996/08/30 15:56:02  wenger
  Modified View and QueryProcessor code to work correctly with current
  dispatcher semantics (call back forever unless cancelled).

  Revision 1.70  1996/08/28 00:19:37  wenger
  Improved use of Dali to correctly free images (use of Dali is now fully
  functional with filenames in data).

  Revision 1.69  1996/08/23 16:55:50  wenger
  First version that allows the use of Dali to display images (more work
  needs to be done on this); changed DevStatus to a class to make it work
  better; various minor bug fixes.

  Revision 1.68  1996/08/09 22:39:00  wenger
  Fixed bug 027 (error in dispatcher code sometimes put callback into
  list twice); fixed error in View.c that caused compile failure.

  Revision 1.67  1996/08/08 20:59:11  beyer
  changed some #ifdefs #if defined

  Revision 1.66  1996/08/05 17:28:59  beyer
  Added is_safe() which checks to see if a double is safe value (ie, not
  NaN or Infinity).  Made SetVisualFilter check the new filter for safety.

  Revision 1.65  1996/08/05 16:35:16  beyer
  Made the _viewList statically allocated.  Sometimes the _viewList can
  be queried before any views (and, as was the case, the _viewList) are
  created.

  Revision 1.64  1996/08/04 21:03:35  beyer
  Added view-locks and changed key handling.

  Revision 1.63  1996/08/03 15:48:37  jussi
  Pixmaps are restored only for 2D views.

  Revision 1.62  1996/08/03 15:37:05  jussi
  Flag _solid3D now has three values.

  Revision 1.61  1996/07/25 14:22:58  jussi
  Added aborted parameter to ReportQueryDone().

  Revision 1.60  1996/07/23 21:18:02  jussi
  Added a couple of debugging statements, removed extra callback
  request to the dispatcher.

  Revision 1.59  1996/07/23 19:34:01  beyer
  Changed dispatcher so that pipes are not longer used for callback
  requests from other parts of the code.

  Revision 1.58  1996/07/23 17:16:28  jussi
  Added support for piled views.

  Revision 1.57  1996/07/21 02:21:22  jussi
  Added _xyZoom flag. Fixed problem when small exposures caused
  the whole view to be erased but not redrawn.

  Revision 1.56  1996/07/20 18:47:17  jussi
  Added solid3D flag.

  Revision 1.55  1996/07/15 21:33:47  jussi
  Added SetPattern(Pattern0) just before label is drawn.

  Revision 1.54  1996/07/14 16:51:36  jussi
  Added handling of special case where view is unmapped but is
  requested to unhighlight as if the highlighting was still on.

  Revision 1.53  1996/07/13 17:25:38  jussi
  When view is iconified, statistics are collected but data
  is not drawn. Added ViewRecomputed() callback interface.

  Revision 1.52  1996/07/12 23:41:30  jussi
  When View is destroyed, it is removed from the _viewList.
  Got rid of Init() method, integrated it with the constructor.

  Revision 1.51  1996/07/10 19:29:03  jussi
  Fixed problem with 3D focus points.

  Revision 1.50  1996/07/08 20:31:51  jussi
  Pixmaps are restored now only if view is not a master of a record
  link nor a slave of one.

  Revision 1.49  1996/07/05 17:10:33  jussi
  Added missing call to CompRhoPhiTheta().

  Revision 1.48  1996/06/27 19:04:48  jussi
  The user can now switch between 2D and 3D display, the
  data is refreshed and displayed accordingly.

  Revision 1.47  1996/06/27 15:43:55  jussi
  Added method AbortAndReexecuteQuery which allows the QueryProc
  to ask the view to re-issue queries when TData has changed.

  Revision 1.46  1996/06/24 19:35:39  jussi
  Added a win->Flush() call to strategic points so that view
  updates get propagated to the X server.

  Revision 1.45  1996/06/21 19:56:10  jussi
  Default 3D navigation is now radial instead of rectangular.

  Revision 1.44  1996/06/21 19:31:54  jussi
  Replaced MinMax calls with calls to MIN() and MAX().

  Revision 1.43  1996/06/20 21:40:14  jussi
  Added call to SetVisualFilter() to SetCamera() which causes the
  (non-existent) filter change to be reported to clients, including
  the 3D query dialog.

  Revision 1.42  1996/06/16 02:06:56  jussi
  Various improvements in debugging.

  Revision 1.41  1996/06/15 13:46:39  jussi
  X and Y axes now use the view foreground color as their color.
  The axis.color field was removed.

  Revision 1.40  1996/06/15 07:05:08  yuc
  Change CompRhoPhiTheta so it will display x vs y and z-axis into the
  screen, add spherical coordinate system to CompRhoPhiTheta also.

  Revision 1.39  1996/06/13 00:14:31  jussi
  Added support for XY cursors. All types of cursors can now
  be moved by clicking on their new location in the data area.
  Previously only the X label area was sensitive for cursor
  movement.

  Revision 1.38  1996/05/31 15:30:28  jussi
  Added support for tick marks in axes. The spacing and location
  of tick marks is set automatically to something reasonable,
  even if the axis range is not.

  Revision 1.37  1996/05/14 18:05:16  jussi
  Added initialization of view callback list. Added debugging
  statements.

  Revision 1.36  1996/05/09 18:12:19  kmurli
  No change to this makefile.

  Revision 1.35  1996/05/07 16:32:40  jussi
  Moved Action member variable to ViewGraph. Move implementation of
  HandleKey, HandlePress and HandlePopup to ViewGraph as well.

  Revision 1.34  1996/04/22 20:25:46  jussi
  Added calls to Dispatcher::InsertMarker() to a few additional places
  where a View redisplay must be initiated.

  Revision 1.33  1996/04/20 19:52:16  kmurli
  Changed Viex.c to use a pipe mechanism to call itself if it needs to be
  done again. The view now is not called contiously by the Dispatcher,instead
  only of there is some data in the pipe.
  The pipe mechanism is implemented transparently through static functions
  in the Dispatcher.c (InsertMarker,CreateMarker,CloseMarker,FlushMarker)

  Revision 1.32  1996/04/19 19:07:02  wenger
  Changed exit(1) to Exit::DoExit(1).

  Revision 1.31  1996/04/16 20:07:01  jussi
  Replaced assert() calls with DOASSERT macro.

  Revision 1.30  1996/04/09 22:51:44  jussi
  Added SetOverrideColor() and GetOverrideColor().

  Revision 1.29  1996/04/09 20:35:11  jussi
  Minor fixes.

  Revision 1.28  1996/04/09 18:05:28  jussi
  Minor improvements.

  Revision 1.27  1996/04/05 20:12:34  wenger
  Fixed error causing pure virtual function to be called
  if a session was closed during a query; fixed an error
  in one of the Linux Makefiles; updated other Makefiles
  to allow testWindowRep to be built on all architectures.

  Revision 1.26  1996/03/29 18:13:57  wenger
  Got testWindowRep to compile and run, added drawing in
  windows; fixed a few more compile warnings, etc.

  Revision 1.25  1996/03/06 19:35:40  jussi
  Added GetNumDimensions() and SetNumDimensions().

  Revision 1.24  1996/02/06 19:32:41  jussi
  Moved logo drawing to ViewWin.c.

  Revision 1.23  1996/02/05 23:56:57  jussi
  Added DEVise logo display.

  Revision 1.22  1996/02/02 21:53:45  jussi
  Removed SetFgColor() right after SetXorMode() which changed the
  effect of the xor function.

  Revision 1.21  1996/02/01 20:28:52  jussi
  Axis areas were cleared even if axes were not displayed. Fixed
  this.

  Revision 1.20  1996/01/30 21:11:21  jussi
  Replaced references to specific colors with references to
  BackgrounColor and ForegroundColor.

  Revision 1.19  1996/01/16 17:07:29  jussi
  Redefined computation of cursor area.

  Revision 1.18  1995/12/29 22:41:01  jussi
  Symbols are turned on and connectors off before a pixel map
  is saved.

  Revision 1.17  1995/12/29 18:33:13  jussi
  Forgot to comment out the #define DEBUG statement in last check-in.

  Revision 1.16  1995/12/29 18:27:52  jussi
  Added new cursor mechanism; cursors are drawn as inverted rectangles
  which are easier to see than the old cursor lines.

  Revision 1.15  1995/12/14 21:11:05  jussi
  Replaced 0x%x with 0x%p.

  Revision 1.14  1995/12/14 17:18:24  jussi
  More small fixes to get rid of g++ -Wall warnings.

  Revision 1.13  1995/12/14 17:14:56  jussi
  Small fixes.

  Revision 1.12  1995/12/06 21:18:12  jussi
  Minor improvements: X high label no longer gets overdrawn by the highlight
  rectangle when label is at top; erasing data area erases top pixel line
  as well; PushClip() and AbsoluteText() interface changed slightly, so
  now the caller has to decrement width and height by one if passing pixel
  coordinates.

  Revision 1.11  1995/12/05 22:05:00  jussi
  A constant integer value is saved at the head of a pixmap file
  to make sure that a machine which tries to load the pixmap has
  the same endianness.

  Revision 1.10  1995/12/05 17:02:00  jussi
  Moved _stats to ViewGraph (superclass) so that statistics can be
  turned on and displayed without having to redisplay the data itself.

  Revision 1.9  1995/12/04 18:06:05  jussi
  Added GetLabelParams and replaced ToggleStatDisplay with SetStatDisplay.

  Revision 1.8  1995/12/02 21:23:26  jussi
  Corrected code which was based on the assumption that a view
  always has origin 0,0 which is no longer true with margins
  surrounding the view. Fixed numerous other bugs.

  Revision 1.7  1995/11/28  05:08:24  ravim
  Support for statistics.

  Revision 1.6  1995/11/25 19:55:37  jussi
  Added debugging statement.

  Revision 1.5  1995/11/24 21:30:39  jussi
  Added copyright notice and cleaned up code. Added debugging
  statements.

  Revision 1.4  1995/09/26 23:05:12  jussi
  Made X low label left-justified.

  Revision 1.3  1995/09/14 19:19:51  jussi
  Corrected a couple of perror messages.

  Revision 1.2  1995/09/05 21:13:15  jussi
  Added/updated CVS header.
*/

#include <time.h>

//#define DEBUG

#include "Util.h"
#include "View.h"
#include "Geom.h"
#include "WindowRep.h"
#include "FilterQueue.h"
#include "Control.h"
#include "TimeStamp.h"
#include "Parse.h"
#include "Map3D.h"
#ifdef JPEG
#include "Jpeg.h"
#endif
#include "Display.h"
#include "PSDisplay.h"
#include "Init.h"
#include "DaliIfc.h"
#include "DevError.h"

// Whether to draw view borders -- must eventually be controlled by GUI.
static const Boolean viewBorder = false;

/* width/height of sensitive area for cursor */
static const int VIEW_CURSOR_SENSE = 10;

/*
   pixel image must be at least 64K bytes before it is saved with the
   session file
*/
static const int VIEW_BYTES_BEFORE_SAVE = 64 * 1024;

static const Coord DELTA_X = .000000000001;
static const Coord DELTA_Y = .000000000001;

/* id for the next view created. view == NULL return id = 0. */

int View::_nextId = 0;
static ViewList theViewList;
ViewList *View::_viewList = &theViewList;   /* list of all views */

int View::_nextPos = 0;
ViewCallbackList *View::_viewCallbackList = 0;


View::View(char *name, VisualFilter &initFilter, 
	   GlobalColor fg, GlobalColor bg, AxisLabel *xAxisLabel,
	   AxisLabel *yAxisLabel,
	   int weight, Boolean boundary) :
	ViewWin(name, fg, bg, weight, boundary)
{
  DO_DEBUG(printf("View::View(%s, this = %p)\n", name, this));
  _jump = _zoomIn = _zoomOut = _scrollLeft = _scrollRight = _unknown = 0;

  _modeRefresh = false;

  /* init default filter */
  _filter = initFilter;
  _filterChanged = true;
  _hasTimestamp = true;
  _timeStamp = TimeStamp::NextTimeStamp();
  
  _hasExposure = false; /* no exposure rectangle yet */
  _querySent = false;	/* TRUE if query has been sent */
  
  _xAxisLabel = xAxisLabel;
  _yAxisLabel = yAxisLabel;
  
  xAxis.inUse = false;
  xAxis.width = 15;
  xAxis.numTicks = 8;
  xAxis.significantDigits = 6;
  xAxis.labelWidth = 60;
  
  yAxis.inUse = false;
  yAxis.width = 50;
  yAxis.numTicks = 8;
  yAxis.significantDigits = 6;
  yAxis.labelWidth = 40;
  
  _label.occupyTop = false;
  _label.extent = 12;
  _label.name = 0;
  
  _xAxisAttrType = FloatAttr;
  _yAxisAttrType = FloatAttr;

  _cursors = new DeviseCursorList;
  DOASSERT(_cursors, "Out of memory");

  _filterQueue = new FilterQueue();
  ReportViewCreated();
  
  int flushed = _filterQueue->Enqueue(initFilter);
  ReportFilterChanged(initFilter, flushed);
  _highlight = false; 

  _hasXMin = false;

  _view_locks = 0;

  _hasLastFilter = false;
  _updateTransform = true;
  _refresh = true;

  _pixmap = NULL;
  _pixmapIO = new PixmapIO();
  _compress = new SimpleCompress();

  _cursorsOn = false;
  _numDimensions = 2;
  _solid3D = 2;

  _xyZoom = true;
  _dispDataValues = false;
  _pileMode = false;
  _pileViewHold = true;

  _printing = false;

  _hasOverrideColor = false;
  _overrideColor = fg;

  _displaySymbol = true;

  _camera.x_ = 4.6;
  _camera.y_ = 4.0;
  _camera.z_ = -4.0;
  _camera.fx = 0.0;
  _camera.fy = 0.0;
  _camera.fz = 0.0;
  _camera._rho = 7.0;
  _camera._phi = 1.0;
  _camera._theta = 0.9;
  _camera._dvs = 250;
  _camera._twist_angle = deg_rad(0.0);
  _camera._perspective = 1;
  _camera.flag = 0;
  _camera.fix_focus = 1;
  _camera.spherical_coord = 1;
  _camera.H = 0;
  _camera.V = 0;

  _id = ++_nextId;
  
  _viewList->Insert(this);
  
  ControlPanel::Instance()->InsertCallback(this);

  _dispatcherID = Dispatcher::Current()->Register(this, 10, GoState);
  Dispatcher::Current()->RequestCallback(_dispatcherID);
}

View::~View()
{
  _viewList->Delete(this);

  Dispatcher::Current()->Unregister(this);

  DOASSERT(!_querySent, "Query still active");

  delete _label.name;
  delete _cursors;
  delete _filterQueue;

  Unmap();
  DeleteFromParent();
  ControlPanel::Instance()->DeleteCallback(this);

  ReportViewDestroyed();
}

/***************************************************************
Find view by name. Return NULL if not found.
****************************************************************/

View *View::FindViewByName(char *name)
{
  DOASSERT(_viewList, "Invalid view list");
  
  int index;
  for(index = _viewList->InitIterator(); _viewList->More(index); ) {
    View *view = _viewList->Next(index);
    if (strcmp(view->GetName(), name)== 0) {
      _viewList->DoneIterator(index);
      return view;
    }
  }
  _viewList->DoneIterator(index);
  
  fprintf(stderr, "View %s not found\n", name);
  return NULL;
}

/***************************************************************
Find view by id
****************************************************************/

View *View::FindViewById(int id)
{
  if (!id)
    return NULL;
  
  DOASSERT(_viewList, "Invalid view list");
  
  for(int index = _viewList->InitIterator(); _viewList->More(index); ) {
    View *view = _viewList->Next(index);
    if (view->GetId() == id) {
      _viewList->DoneIterator(index);
      return view;
    }
  }
  
  fprintf(stderr,"View %d not found\n", id);
  return NULL;
}

int View::FindViewId(View *view)
{
  if (!view)
    return 0;

  return view->GetId();
}

void View::SubClassMapped()
{
  _updateTransform = true;

  // cause pending Expose events to be retrieved from the X server
  DeviseDisplay::DefaultDisplay()->Run();

  // in batch mode, force Run() method to be called so that
  // (first) query gets properly started up
  Dispatcher::Current()->RequestCallback(_dispatcherID);
}
	
void View::SubClassUnmapped()
{
  AbortQuery();
}

void View::SetVisualFilter(VisualFilter &filter)
{
#if defined(DEBUG)
  printf("%s View::SetVisualFilter %f %f %f %f %f, %f, %f, %f\n", GetName(),
	 filter.xLow, filter.yLow,
	 filter.xHigh, filter.yHigh,_filter.xLow, _filter.yLow,
	 _filter.xHigh, _filter.yHigh);
#endif

  // check the new filter for safety & sanity
  if (is_safe(filter.xLow) && is_safe(filter.xHigh) &&
      is_safe(filter.yLow) && is_safe(filter.yHigh) &&
      filter.xLow < filter.xHigh && filter.yLow < filter.yHigh) {

    /* ignore new filter if same as current one */
    if (_filter.xLow != filter.xLow || _filter.xHigh != filter.xHigh
	|| _filter.yLow != filter.yLow || _filter.yHigh != filter.yHigh) {

#if defined(DEBUG)
      printf("filter changed\n");
#endif

      if (filter.xLow > _filter.xHigh || filter.xHigh < _filter.xLow)
	_jump++;
      else if (filter.xLow < _filter.xLow && filter.xHigh > _filter.xHigh)
	_zoomOut++;
      else if (filter.xLow > _filter.xLow && filter.xHigh < _filter.xHigh)
	_zoomIn++;
      else if (filter.xLow < _filter.xLow && filter.xHigh < _filter.xHigh)
	_scrollLeft++;
      else if (filter.xLow > _filter.xLow && filter.xHigh > _filter.xHigh)
	_scrollRight++;
      else
	_unknown++;
      
      ReportFilterAboutToChange();

      _filterChanged = true;
      if (!_hasTimestamp) {
	_timeStamp = TimeStamp::NextTimeStamp();
	_hasTimestamp = true;
      }
      _updateTransform = true;
      _filter = filter;

      int flushed = _filterQueue->Enqueue(filter);
      ReportFilterChanged(filter, flushed);
      
      Dispatcher::Current()->RequestCallback(_dispatcherID);
    }
  }
}

void View::GetVisualFilter(VisualFilter &filter)
{
  filter = _filter;
}

VisualFilter *View::GetVisualFilter()
{
  return &_filter;
}

void View::Mark(int index, Boolean marked)
{
  _filterQueue->Mark(index, marked);
}

Boolean View::CheckCursorOp(WindowRep *win, int x, int y, int button)
{
  // view has no cursors, so we can't move them either
  if (!_cursors->Size())
    return false;

  // can only move cursors in 2D views
  if (_numDimensions != 2)
    return false;

  // if view is not selected, no cursor movement is induced;
  // mouse click is intended for selecting the view as current;
  // the next mouse click in this view will move the cursor
  if (!_highlight)
    return false;

  /* change the X and Y coordinates of the cursor */
  Coord worldXLow, worldYLow, worldXHigh, worldYHigh;
  FindWorld(x, y, x + 1, y - 1, worldXLow, worldYLow, worldXHigh, worldYHigh);
  DeviseCursor *cursor = _cursors->GetFirst();
  DOASSERT(cursor, "Invalid cursor");
  cursor->MoveSource((worldXHigh + worldXLow) / 2.0,
		     (worldYHigh + worldYLow) / 2.0);

  return true;
}

void View::HandleExpose(WindowRep *w, int x, int y, unsigned width, 
			unsigned height)
{
#if defined(DEBUG)
  printf("View::HandleExpose %d,%d,%u,%u\n", x, y, width, height);
#endif

  if (!_hasExposure) {

    _hasExposure = true;
    _exposureRect.xLow = x;
    _exposureRect.yLow = y;
    _exposureRect.xHigh = x + width - 1;
    _exposureRect.yHigh = y + height - 1;

  } else {

    /* merge with existing exposed region */
    int minX1 = _exposureRect.xLow;
    int minY1 = _exposureRect.yLow;
    int maxX1 = _exposureRect.xHigh;
    int maxY1 = _exposureRect.yHigh;
    
    int minX2 = x;
    int minY2 = y;
    int maxX2 = x + width - 1;
    int maxY2 = y + height - 1;
    
    _exposureRect.xLow = MIN(minX1, minX2);
    _exposureRect.yLow = MIN(minY1, minY2);
    _exposureRect.xHigh = MAX(maxX1, maxX2);
    _exposureRect.yHigh = MAX(maxY1, maxY2);
  }

  Dispatcher::Current()->RequestCallback(_dispatcherID);
}

/* set dimensionality */

void View::SetNumDimensions(int d)
{
  if (d != 2 && d != 3) {
    fprintf(stderr, "View::SetNumDimensions %d invalid\n", d);
    return;
  }

  if (d == _numDimensions)
    return;

  _numDimensions = d;
  _updateTransform = true;

  Refresh();
}

/* set solid or wideframe 3D objects */

void View::SetSolid3D(int solid)
{
  if (solid == _solid3D)
    return;

  _solid3D = solid;

  Refresh();
}

/* set flag for data value display */

void View::SetDisplayDataValues(Boolean disp)
{
  if (disp == _dispDataValues)
    return;

  _dispDataValues = disp;

  Refresh();
}

/* set pile mode flag */

void View::SetPileMode(Boolean mode)
{
  if (mode == _pileMode)
    return;

  _pileMode = mode;
  _pileViewHold = true;

  Refresh();
}

/* set override color */

void View::SetOverrideColor(GlobalColor color, Boolean active)
{
  /* no change in color override? */
  if (_hasOverrideColor == active && color == _overrideColor)
    return;

  _overrideColor = color;

  /* color override still not enabled (but color may have changed)? */
  if (_hasOverrideColor == active && !active)
    return;

  _hasOverrideColor = active;

  Refresh();
}

/* get area for displaying label */

void View::GetLabelArea(int &x, int &y, int &width, int &height)
{
  unsigned int w, h;
  Geometry(x, y, w, h);

  if (_label.occupyTop) {
    width = w;
    height = _label.extent;
  } else {
    width = _label.extent;
    height = h;
  }
  
  if (width < 0)
    width = 1;
  if (height < 0)
    height = 1;

#if defined(DEBUG)
  printf("View::GetLabelArea %s %d %d %d %d\n", GetName(), x, y, width, height);
#endif
}

/********************************************************************
get area for displaying X axis. Assumes that X axis is in use.
area = x,y,width, height, and startX, as follows:

          +--+--------+
          |  |        |
          |  |        |
          |  |        |
     (x,y)+--+--------+
          |  ^        | <- height
          |  startX   |
          +-----------+
                ^
                |
	    	 width
************************************************************************/

void View::GetXAxisArea(int &x, int &y, int &width, int &height,
			int &startX)
{
  DOASSERT(_numDimensions == 2, "Invalid number of dimensions");

  unsigned int windW, winH;
  Geometry(x, y, windW, winH);

  y += winH - xAxis.width;
  width = windW;
  height = xAxis.width;
  
  if (!_label.occupyTop) {
    x += _label.extent;
    width -= _label.extent;
  }

  startX = x;
  if (yAxis.inUse)
    startX += yAxis.width;
  else {
    // no space space is really necessary, but add just a little bit
    // of space to separate label from the window border better
    startX += 2;
  }

  if (width < 0)
    width = 1;
  if (height < 0)
    height = 1;

#if defined(DEBUG)
  printf("View::GetXAxisArea %s %d %d %d %d\n", GetName(), x, y, width, height);
#endif
}

/********************************************************************
get area for displaying Y axis. Assumes that X axis is in use.
area = x,y,width, height, and startX, as follows:

          width
     (x,y)+--+--------+
          |  |        |
    height|  |        |
          |  |        |
          +--+--------+
          |           | 
          |           |
          +-----------+
********************************************************************/

void View::GetYAxisArea(int &x, int &y, int &width, int &height)
{
  DOASSERT(_numDimensions == 2, "Invalid number of dimensions");

  unsigned int winW, winH;
  Geometry(x, y, winW, winH);

  if (_label.occupyTop) {
    y += _label.extent;
    height = winH - _label.extent;
    width = yAxis.width;
  } else {
    x += _label.extent;
    width = yAxis.width;
    height = winH;
  }
  
  if (xAxis.inUse)
    height -= xAxis.width;
  
  if (width <= 0 )
    width = 1;
  if (height <= 0)
    height = 1;

#if defined(DEBUG)
  printf("View::GetYAxisArea %s %d %d %d %d\n", GetName(), x, y, width, height);
#endif
}

void View::GetDataArea(int &x, int &y, int &width,int &height)
{
  unsigned int winWidth, winHeight;
  Geometry(x, y, winWidth, winHeight);
  
#if defined(DEBUG)
  printf("View::GetDataArea: full area at %d,%d, size %d, %d\n",
	 x, y, winWidth, winHeight);
#endif

  if (_label.occupyTop) {
    /* _label occupies top of view */
    y +=  _label.extent; 
    /* 
       subtract 2 from left so that data doesn't draw
       over the highlight border
    */
    x += 2;
    width = winWidth - 2;
    height = winHeight - _label.extent;
  } else {
    /* _label occupies left of view */
    /* Have to add in two pixels here for some reason.  RKW 11/19/96. */
    x += _label.extent + 2;
    width = winWidth - (_label.extent + 2);
    height = winHeight;
  }
  
  if (_numDimensions == 2) {
    /* need to display axes */
    if (xAxis.inUse)
      height -= xAxis.width;
    else if (_label.occupyTop)
      height -= 2;
    
    if (yAxis.inUse) {
      /* Put back in the 2 pixels we took out for the highlight border. */
      x += (yAxis.width - 2);
      width -= (yAxis.width - 2);
    }
  }
  
  if (width <= 0) width = 1;
  if (height <= 0) height = 1;
  
#if defined(DEBUG)
  printf("View::GetDataArea %s %d %d %d %d\n", GetName(), x, y, width, height);
#endif
}

void View::DrawAxesLabel(WindowRep *win, int x, int y, int w, int h)
{
#if defined(DEBUG)
  printf("View::DrawAxesLabel %s %d %d %d %d\n", GetName(), x, y, w, h);
#endif

  int winX, winY; 
  unsigned int winW, winH;
  Geometry(winX, winY, winW, winH);
  
  /* Make it possible to update the label areas */
  win->PushClip(winX, winY, winW - 1, winH - 1);
  
  DrawLabel();

  /* Clear highlight area */
  win->SetFgColor(GetBgColor());
  DrawHighlight();

  if (_numDimensions == 2) {
    int axisX, axisY, axisWidth, axisHeight, startX;
    if (xAxis.inUse) {
      GetXAxisArea(axisX, axisY, axisWidth, axisHeight, startX);
      win->SetFgColor(GetBgColor());
      win->SetPattern(Pattern0);
      win->SetLineWidth(0);
      win->FillRect(axisX, axisY, axisWidth - 1, axisHeight - 1);
      DrawXAxis(win, x, y, w, h);
    }
    if (yAxis.inUse) {
      GetYAxisArea(axisX, axisY, axisWidth, axisHeight);
      win->SetFgColor(GetBgColor());
      win->SetPattern(Pattern0);
      win->SetLineWidth(0);
      win->FillRect(axisX, axisY, axisWidth - 1, axisHeight - 1);
      DrawYAxis(win, x, y, w, h);
    }
  }

  win->PopClip();
}

void View::DrawLabel()
{
  WindowRep *win = GetWindowRep();

  win->PushTop();
  win->MakeIdentity();
  
  if (_label.occupyTop) {
    /* draw label */
    int labelX, labelY, labelWidth, labelHeight;
    GetLabelArea(labelX, labelY, labelWidth, labelHeight);
    win->SetPattern(Pattern0);
    win->SetLineWidth(0);
    win->SetFgColor(GetBgColor());
    win->FillRect(labelX, labelY, labelWidth - 1, labelHeight - 1);
    win->SetFgColor(GetFgColor());
    win->AbsoluteText(_label.name, labelX, labelY, labelWidth - 1,
		      labelHeight - 1, WindowRep::AlignCenter, true);
  } else {
    /* draw square with cross mark in top-left corner of view */
    int x, y, w, h;
    GetLabelArea(x, y, w, h);
    win->SetPattern(Pattern0);
    win->SetFgColor(GetFgColor());
    win->AbsoluteLine(x, y, x + _label.extent - 1, y, 1);
    win->AbsoluteLine(x + _label.extent - 1, y,
		      x + _label.extent - 1, y + _label.extent - 1, 1);
    win->AbsoluteLine(x + _label.extent - 1, y + _label.extent - 1,
		      x, y + _label.extent - 1, 1);
    win->AbsoluteLine(x, y + _label.extent - 1, x, y, 1);
    win->AbsoluteLine(x, y, x + _label.extent - 1, y + _label.extent - 1, 1);
    win->AbsoluteLine(x + _label.extent - 1, y, x, y + _label.extent - 1, 1);
  }

  win->PopTransform();
}

void View::DrawXAxis(WindowRep *win, int x, int y, int w, int h)
{
#if defined(DEBUG)
  printf("View::DrawXAxis %s %d %d %d %d\n", GetName(), x, y, w, h);
#endif
  
  DOASSERT(_numDimensions == 2, "Invalid number of dimensions");

  int axisX, axisY, axisWidth, axisHeight, startX;
  GetXAxisArea(axisX, axisY, axisWidth, axisHeight, startX);
  int axisMaxX = axisX + axisWidth - 1;
  int axisMaxY = axisY + axisHeight - 1;
  int maxX = x + w - 1;
  int maxY = y + h - 1;
  if (!Geom::RectRectIntersect(x,y,maxX,maxY,axisX,axisY,axisMaxX,axisMaxY)) {
#if defined(DEBUG)
    printf("do not intersect\n");
#endif
    return;
  }
  
  win->SetFgColor(GetFgColor());
  win->SetPattern(Pattern0);

  /* draw a line from startX to the end of the view */
  win->Line(startX - 1, axisY, axisMaxX, axisY, 1);

  Coord drawWidth = axisWidth - (startX - axisX);
  int numTicks = (int)(drawWidth / xAxis.labelWidth);

  /* if custom labels requested, draw them and return */
  if (_xAxisLabel) {
    char *label = _xAxisLabel->GenerateLabel( _filter.xLow);
    win->AbsoluteText(label, startX, axisY, drawWidth / 2 - 1,
		      axisHeight - 1, WindowRep::AlignWest, true);
    label = _xAxisLabel->GenerateLabel(_filter.xHigh);
    win->AbsoluteText(label, startX + drawWidth / 2, axisY, drawWidth / 2 - 1,
		      axisHeight - 1, WindowRep::AlignEast, true);
    return;
  }

  /* if axis is date, draw values and return */
  if (_xAxisAttrType == DateAttr) {
    char *label = DateString((time_t)_filter.xLow);
    win->AbsoluteText(label, startX, axisY, drawWidth / 2 - 1,
		      axisHeight - 1, WindowRep::AlignWest, true);
    label = DateString((time_t)_filter.xHigh);
    win->AbsoluteText(label, startX + drawWidth / 2, axisY, drawWidth / 2 - 1,
		      axisHeight - 1, WindowRep::AlignEast, true);
    return;
  }

  /* if just two tick marks, draw start and end points */
  if (numTicks <= 2) {
    char buf[32];
    sprintf(buf, "%.*g", xAxis.significantDigits, _filter.xLow);
    win->AbsoluteText(buf, startX, axisY, drawWidth / 2 - 1,
		      axisHeight - 1, WindowRep::AlignWest, true);
    sprintf(buf, "%.*g", xAxis.significantDigits, _filter.xHigh);
    win->AbsoluteText(buf, startX + drawWidth / 2, axisY, drawWidth / 2 - 1,
		      axisHeight - 1, WindowRep::AlignEast, true);
    return;
  }

  /*
     since neither custom nor date labels are used, we can draw
     tick marks and label each tick with the corresponding value
  */

  Coord tickMark;
  int nTicks;
  Coord tickInc;
  OptimizeTickMarks(_filter.xLow, _filter.xHigh, numTicks,
		    tickMark, nTicks, tickInc);

  /* extract user transformation */
  win->PopTransform();
  Transform2D transform = *win->TopTransform();
  win->PushTop();
  win->MakeIdentity();

  /* draw tick marks */
  for(int i = 0; i < nTicks; i++) {
    Coord x, y;
    transform.Transform(tickMark, 0, x, y);
    win->Line(x, axisY, x, axisY + 3, 1);
    char buf[32];
    sprintf(buf, "%.*g", xAxis.significantDigits, tickMark);
    Coord xLeft = x - xAxis.labelWidth / 2;
    /* make sure label doesn't go past left or right edge */
    if (xLeft < startX) {
      xLeft = startX;
      win->AbsoluteText(buf, xLeft, axisY, xAxis.labelWidth,
			axisHeight - 1, WindowRep::AlignWest, true);
    } else if (xLeft + xAxis.labelWidth > axisX + axisWidth) {
      xLeft = axisX + axisWidth - xAxis.labelWidth;
      win->AbsoluteText(buf, xLeft, axisY, xAxis.labelWidth,
			axisHeight - 1, WindowRep::AlignEast, true);
    } else {
      win->AbsoluteText(buf, xLeft, axisY, xAxis.labelWidth,
			axisHeight - 1, WindowRep::AlignCenter, true);
    }
    tickMark += tickInc;
  }
}

void View::DrawYAxis(WindowRep *win, int x, int y, int w, int h)
{
#if defined(DEBUG)
  printf("View::DrawYAxis %s %d %d %d %d\n", GetName(), x, y, w, h);
#endif
  
  DOASSERT(_numDimensions == 2, "Invalid number of dimensions");

  int axisX, axisY, axisWidth, axisHeight;
  Coord startY;
  GetYAxisArea(axisX, axisY, axisWidth, axisHeight);
  startY = axisY;
  int axisMaxX = axisX + axisWidth - 1;
  int axisMaxY = axisY + axisHeight - 1;

  Coord maxX = x + w;
  Coord maxY = y + h;
  if (!Geom::RectRectIntersect(x, y, maxX, maxY, axisX, axisY,
			       axisMaxX, axisMaxY)) {
#if defined(DEBUG)
    printf("do not intersect\n");
#endif
    return;
  }

  win->SetFgColor(GetFgColor());
  win->SetPattern(Pattern0);

  /* draw a line from startY to the bottom of the view */
  win->Line(axisMaxX, startY, axisMaxX, axisMaxY + 1, 1.0);

  Coord drawHeight = axisHeight - (startY - axisY);
  int numTicks = (int)(drawHeight / yAxis.labelWidth);

  /* if custom labels requested, draw them and return */
  if (_yAxisLabel) {
    char *label = _yAxisLabel->GenerateLabel( _filter.yLow);
    win->AbsoluteText(label, axisX, startY + drawHeight / 2, axisWidth - 1,
		      drawHeight / 2 - 1, WindowRep::AlignSouth, true);
    label = _yAxisLabel->GenerateLabel(_filter.yHigh);
    win->AbsoluteText(label, axisX, startY, axisWidth - 1,
		      drawHeight / 2 - 1, WindowRep::AlignNorth, true);
    return;
  }

  /* if axis is date, draw values and return */
  if (_yAxisAttrType == DateAttr) {
    char *label = DateString((time_t)_filter.yLow);
    win->AbsoluteText(label, axisX, startY + drawHeight / 2, axisWidth - 1,
		      drawHeight / 2 - 1, WindowRep::AlignSouth, true);
    label = DateString((time_t)_filter.yHigh);
    win->AbsoluteText(label, axisX, startY, axisWidth - 1,
		      drawHeight / 2 - 1, WindowRep::AlignNorth, true);
    return;
  }

  /* if just two tick marks, draw start and end points */
  if (numTicks <= 2) {
    char buf[32];
    sprintf(buf, "%.*g", yAxis.significantDigits, _filter.yLow);
    win->AbsoluteText(buf, axisX, startY + drawHeight / 2, axisWidth - 1,
		      drawHeight / 2 - 1, WindowRep::AlignSouth, true);
    sprintf(buf, "%.*g", yAxis.significantDigits, _filter.yHigh);
    win->AbsoluteText(buf, axisX, startY, axisWidth - 1,
		      drawHeight / 2 - 1, WindowRep::AlignNorth, true);
    return;
  }

  /*
     since neither custom nor date labels are used, we can draw
     tick marks and label each tick with the corresponding value
  */

  Coord tickMark;
  int nTicks;
  Coord tickInc;
  OptimizeTickMarks(_filter.yLow, _filter.yHigh, numTicks,
		    tickMark, nTicks, tickInc);

  /* extract user transformation */
  win->PopTransform();
  Transform2D transform = *win->TopTransform();
  win->PushTop();
  win->MakeIdentity();

  /* draw tick marks */
  for(int i = 0; i < nTicks; i++) {
    Coord x, y;
    transform.Transform(0, tickMark, x, y);
    win->Line(axisMaxX, y, axisMaxX - 3, y, 1);
    char buf[32];
    sprintf(buf, "%.*g", yAxis.significantDigits, tickMark);
    Coord yTop = y - yAxis.labelWidth / 2;
    /* make sure label doesn't go past left or right edge */
    if (yTop < startY) {
      yTop = startY;
      win->AbsoluteText(buf, axisX, yTop, axisWidth - 1,
			yAxis.labelWidth, WindowRep::AlignNorth, true);
    } else if (yTop + yAxis.labelWidth > axisY + axisHeight) {
      yTop = axisY + axisHeight - yAxis.labelWidth;
      win->AbsoluteText(buf, axisX, yTop, axisWidth - 1,
			yAxis.labelWidth, WindowRep::AlignSouth, true);
    } else {
      win->AbsoluteText(buf, axisX, yTop, axisWidth - 1,
			yAxis.labelWidth, WindowRep::AlignCenter, true);
    }
    tickMark += tickInc;
  }
}

/* Optimize spacing and location of tick marks */

void View::OptimizeTickMarks(Coord low, Coord high, int numTicks,
			     Coord &start, int &num, Coord &inc)
{
  Coord tickIncrement = (high - low) / numTicks;

  /* adjust tick increment so that we get nice tick values */
  double exponent = log10(tickIncrement);
  int tickpow = (int)exponent;
  /* negative exponent must round down, not up */
  if (exponent < 0 && tickpow > exponent)
    tickpow--;
  double mantissa = tickIncrement / pow(10, tickpow);
  if (mantissa < 1.5)
    mantissa = 1.0;
  else if (mantissa < 2.25)
    mantissa = 2.0;
  else if (exponent >= 1 && mantissa < 2.75)
    mantissa = 2.5;
  else if (mantissa < 3.5)
    mantissa = 3.0;
  else if (mantissa < 4.5)
    mantissa = 4.0;
  else if (mantissa < 7.5)
    mantissa = 5.0;
  else
    mantissa = 10.0;

  inc = mantissa * pow(10, tickpow);
#if defined(DEBUG)
  printf("Old tickIncrement %g, new %g\n", tickIncrement, inc);
#endif

  /*
     adjust the midpoint of the tick marks so that tick marks end
     up on nice coordinate values
  */
  Coord midPoint = (low + high) / 2.0;
  Coord multTick = midPoint / inc;
  Coord newMidPoint = ((int)multTick) * inc;
  if (multTick - (int)multTick >= 0.5)
    newMidPoint += inc;
#if defined(DEBUG)
  printf("Old midpoint %g, new %g\n", midPoint, newMidPoint);
#endif

  /* calculate first tick mark */
  start = newMidPoint
          - ((int)((newMidPoint - low) / inc)) * inc;
  num = (int)((high - start) / inc) + 1;
#if defined(DEBUG)
  printf("%d ticks from %g to %g @ %g\n", num, start, high, inc);
#endif
}

/* Find world coord given screen coord */

void View::FindWorld(int sx1,int sy1, int sx2, int sy2,
		     Coord &xLow, Coord &yLow, Coord &xHigh, Coord &yHigh)
{
  Transform2D transform;
  CalcTransform(transform);

  Coord x1, x2, y1, y2;
  transform.InverseTransform(sx1, sy1, x1, y1);
  transform.InverseTransform(sx2, sy2, x2, y2);
  xLow = MIN(x1, x2);
  xHigh = MAX(x1, x2);
  yLow = MIN(y1, y2);
  yHigh = MAX(y1, y2);
}

/* Calculate the transformation matrix used to translate from
   world to screen coordinates */

void View::CalcTransform(Transform2D &transform)
{
  transform.MakeIdentity();

  int dataX, dataY, dataWidth, dataHeight;
  GetDataArea(dataX, dataY, dataWidth, dataHeight);

#if defined(DEBUG)
  printf("transform data: %d,%d,%d,%d\n", dataX, dataY,
	 dataWidth, dataHeight);
#endif
  
  /* translate to 0, 0 */
  transform.Translate(-_filter.xLow, -_filter.yLow);

  /* scale to size of the screen */
  transform.Scale((Coord)dataWidth / (_filter.xHigh -  _filter.xLow),
		  (Coord)(dataHeight) / (_filter.yHigh - _filter.yLow));

  /* invert the Y coord to fit (0,0) at top-left corner */
  transform.Scale(1.0, -1.0);
  transform.Translate(0.0, dataHeight);
  
  /* Translate to beginning of data area. */
  transform.Translate(dataX, dataY);
}

/* Calculate the transformation matrix used to translate from
   world to screen coordinates */

void View::CalcTransform(Transform3D &transform)
{
  CompRhoPhiTheta();
  GetWindowRep()->TopTransform3()->SetViewMatrix(_camera);

  int dx, dy, dw, dh;
  GetDataArea(dx, dy, dw, dh);
  SetViewDir(dw / 2, dh / 2);
}

/* For query processing */

void View::ReportQueryDone(int bytes, Boolean aborted)
{
#if defined(DEBUG)
  printf("View(%s)::ReportQueryDone(%d, %d)\n", _name, bytes, aborted);
#endif

  _bytes = bytes;
  _querySent = false;
  _hasLastFilter = false;

  /* if view is on top of a pile, it has to wake the other views
     up and ask them to refresh; the bottom views might not have
     received an Exposure or ConfigurationNotify event requesting
     them to redraw; also, first view erases window and draws
     axes and other decorations, so it has to go first */

  if (!aborted && _pileMode) {
    ViewWin *parent = GetParent();
    DOASSERT(parent, "View has no parent");
    int index = parent->InitIterator();
    DOASSERT(parent->More(index), "Parent view has no children");
    ViewWin *vw = parent->Next(index);
    if ((ViewWin *)this == vw) {        /* first view will refresh others */
      while(parent->More(index)) {
        vw = parent->Next(index);
        View *view = FindViewByName(vw->GetName());
        DOASSERT(view, "Cannot find view");
#if defined(DEBUG)
        printf("View %s refreshes view %s\n", GetName(), view->GetName());
#endif
        view->_pileViewHold = false;
        view->Refresh();
      }
    }
    parent->DoneIterator(index);
  }

  _cursorsOn = false;

  if (_numDimensions == 2)
    (void)DrawCursors();
  else
    Draw3DAxis();

  GetWindowRep()->PopClip();
  GetWindowRep()->Flush();

  if (_printing)
  {
    (void) PrintPSDone();
  }

  ControlPanel::Instance()->SetIdle();

#if defined(DEBUG)
  printf("View %s completed\n", GetName());
#endif

  // report to interested parties that view has been recomputed
  ReportViewRecomputed();
}

/***********************************************************************
Send a query, if there is one.  Abort existing query if necessary. 
XXX: need to crop exposure against _filter before sending query.
**********************************************************************/

void View::Run()
{
  // This must be done at the beginning in case we request a callback
  // somewhere inside here.
  Dispatcher::Current()->CancelCallback(_dispatcherID);

#if defined(DEBUG)
  printf("\nView::Run for view '%s' (0x%p)\n", GetName(), _dispatcherID);
#endif

  /* if view is in pile mode but not the top view, it has to wait until
     the top view has erased the window and drawn axes and other
     decorations; the top view will send explicit refresh requests
     to the bottom views */

  if (_pileMode) {
    ViewWin *parent = GetParent();

    // If we're running client/server Devise, we may get here before this
    // view's parent has been created, so don't bomb out.  RKW 8/30/96.
    if (parent == NULL) return;
    //DOASSERT(parent, "View has no parent");

    int index = parent->InitIterator();
    DOASSERT(parent->More(index), "Parent view has no children");
    ViewWin *vw = parent->Next(index);
    parent->DoneIterator(index);
    if (this != vw) {
      if (_pileViewHold) {
#if defined(DEBUG)
        printf("View %s cannot continue\n", GetName());
#endif
        AbortQuery();
        return;
      }
#if defined(DEBUG)
      printf("Bottom pile view %s continues\n", GetName());
#endif
      _pileViewHold = true;
    } else {
#if defined(DEBUG)
      printf("Top pile view %s continues\n", GetName());
#endif
      /* make sure top view is visible */
      GetWindowRep()->Raise();
    }
  }

  ControlPanel::Mode mode = ControlPanel::Instance()->GetMode();
#if defined(DEBUGxxx)
  if (mode == ControlPanel::LayoutMode)
    printf("layout mode ");
  else
    printf("disp mode ");
  printf("exp %d flt %d ref %d upd %d\n", _hasExposure, _filterChanged,
	 _refresh, _updateTransform);
#endif
  
  if (mode == ControlPanel::LayoutMode && 
      (_hasExposure || _filterChanged || _refresh || _updateTransform)) { 
    /* keep track that events occurred while in LayoutMode */
    _modeRefresh = true;
  } else if (mode == ControlPanel::DisplayMode && _modeRefresh) {
    /* need to refresh in display mode because events occurred in
       LayoutMode */
    _refresh = true;
  }
  
  if (_querySent) {
    if (_hasExposure || _filterChanged || _refresh || _updateTransform
        || !Mapped()) {
#if defined(DEBUG)
      printf("View:: aborting\n");
#endif
      AbortQuery();
      _refresh = true;
    } else {
#if defined(DEBUG)
      printf("Query already sent, nothing to do\n");
#endif
      return;
    }
  }
  
  if (!Mapped()) {
#if defined(DEBUG)
    printf("Window not mapped, nothing to do\n");
#endif
    return;
  }

  if (Iconified()) {
    /* force "redrawing" of whole view (mainly for statistics and
       other derived data) when window iconified displayed */
    _refresh = true;
    _hasExposure = false;
  }

  if (!_hasExposure && !_filterChanged && !_refresh) {
#if defined(DEBUG)
    printf("View not refreshed and filter not changed, nothing to do\n");
#endif
    return;
  }

  WindowRep *winRep = GetWindowRep();
  int scrnX, scrnY, scrnWidth, scrnHeight;
  unsigned int sW, sH;
  Geometry(scrnX, scrnY, sW, sH);

  scrnWidth = sW;
  scrnHeight = sH;

  VisualFilter newFilter;
  
  if (!Iconified() && !_pileMode && _numDimensions == 2 &&
      RestorePixmap(_filter, newFilter) == PixmapTotal) {
#if defined(DEBUG)
    printf("View::Run: Restored complete pixmap for\n  %s\n", GetName());
#endif

    if (_updateTransform) {
      UpdateTransform(GetWindowRep());
      _updateTransform = false;
    }

    /* Set up identity transformation */
    winRep->PushTop();
    winRep->MakeIdentity();

    /* Draw axes */
    DrawAxesLabel(winRep, scrnX, scrnY, sW, sH);
    
    /* Draw view border. */
    if (viewBorder)
    {
      GlobalColor oldColor = winRep->GetFgColor();
      winRep->SetFgColor(RedColor/*TEMPTEMP*/);
      winRep->SetFgColor((GlobalColor) ((winRep->GetBgColor()+1) % 43)/*TEMPTEMP*/);
      DrawHighlight();
      winRep->SetFgColor(oldColor);
    }

    /* Draw highlight border */
    Boolean oldHighlight = _highlight;
    _highlight = false;
    Highlight(oldHighlight);
    
    /* Pop the transform */
    winRep->PopTransform();

    /* Draw cursors */
    _cursorsOn = false;
    if (_numDimensions == 2)
      (void)DrawCursors();
    else
      Draw3DAxis();

    _hasExposure = false;
    _filterChanged = false;
    _refresh = false;
    _hasLastFilter = false;

    return;
  }

  if (!_updateTransform && !_hasExposure && !_refresh && _filterChanged) {
    /* Do scroll, if we can  */
    UpdateFilterStat stat;
    stat = UpdateFilterWithScroll();
    if (stat == Scrolled) {
      /* did scrolling. Can keep this filter */
      /* update so that _hasFilter is no longer true,
	 and _hasExposure is true. */
      _hasExposure = true;
      _filterChanged = false;
      _hasLastFilter = true;
      _lastFilter = _filter;
    } else if (stat == SameFilter) {
      /* A sequence of scroll/zoom between updates
	 made the latest filter the same as the one being displayed */
      _filterChanged = false;
      _hasLastFilter = true;
      _lastFilter = _filter;
      return;
    }
  }
  
  /* Update the WindowRep's transformation matrix */
  if (_updateTransform) {
    UpdateTransform(GetWindowRep());
    _updateTransform = false;
  }
  
  Boolean piledDisplay = false;

  if (_pileMode) {
    ViewWin *parent = GetParent();
    DOASSERT(parent, "View has no parent");
    int index = parent->InitIterator();
    DOASSERT(parent->More(index), "Parent view has no children");
    ViewWin *firstChild = parent->Next(index);
    if (this != firstChild) {
#if defined(DEBUG)
      printf("View %s follows first child %s\n", GetName(),
             firstChild->GetName());
#endif
      piledDisplay = true;
    } else {
#if defined(DEBUG)
      printf("View %s is first child\n", GetName());
#endif
    }
    parent->DoneIterator(index);
  }
      
  if (piledDisplay || _filterChanged || _refresh) {
    /* Need to redraw the whole screen */
    _queryFilter = _filter;
    _hasLastFilter = true;
    _lastFilter = _queryFilter;
    _hasExposure = false;
  }

  if (_hasExposure) {
    /* limit exposure to the size of the window */
#if defined(DEBUG)
    printf("exposure (%d,%d),(%d,%d) ",
	   _exposureRect.xLow, _exposureRect.yLow,
	   _exposureRect.xHigh, _exposureRect.yHigh);
#endif
    
    _exposureRect.xLow = MAX(_exposureRect.xLow, 0);
    _exposureRect.xLow = MIN(_exposureRect.xLow, scrnWidth - 1);
    _exposureRect.xHigh = MAX(_exposureRect.xLow, _exposureRect.xHigh);
    _exposureRect.xHigh = MIN(_exposureRect.xHigh, scrnWidth - 1);
    
    _exposureRect.yLow = MAX(_exposureRect.yLow, 0);
    _exposureRect.yLow = MIN(_exposureRect.yLow, scrnHeight - 1);
    _exposureRect.yHigh = MAX(_exposureRect.yLow, _exposureRect.yHigh);
    _exposureRect.yHigh = MIN(_exposureRect.yHigh, scrnHeight - 1);
    
#if defined(DEBUG)
    printf("--> (%d,%d),(%d,%d)\n",
	   _exposureRect.xLow, _exposureRect.yLow,
	   _exposureRect.xHigh, _exposureRect.yHigh);
#endif
  
    _queryFilter.flag = VISUAL_LOC; 
    FindWorld(_exposureRect.xLow, _exposureRect.yLow,
	      _exposureRect.xHigh, _exposureRect.yHigh,
	      _queryFilter.xLow, _queryFilter.yLow, 
	      _queryFilter.xHigh, _queryFilter.yHigh);
    
#if defined(DEBUG)
    printf("exposure world %f,%f,%f,%f\n",
	   _queryFilter.xLow, _queryFilter.yLow,
	   _queryFilter.xHigh, _queryFilter.yHigh);
#endif
  }
  
  /* Decorate view with axes etc. */
  
  /* Set up identity transformation */
  winRep->PushTop();
  winRep->MakeIdentity();
  
  if (!piledDisplay) {
    /* Draw axes */
    DrawAxesLabel(winRep, scrnX, scrnY, scrnWidth, scrnHeight);

    /* Draw view border. */
    if (viewBorder)
    {
      GlobalColor oldColor = winRep->GetFgColor();
      winRep->SetFgColor(RedColor/*TEMPTEMP*/);
      GlobalColor junk = winRep->GetBgColor();
/*TEMPTEMP*/printf("Background color = %d\n", (int) junk);
      junk = (GlobalColor) ((junk + 1) % 43);
/*TEMPTEMP*/printf("  Highlight color = %d\n", (int) junk);
      winRep->SetFgColor(junk);
      DrawHighlight();
      winRep->SetFgColor(oldColor);
    }

    /* Draw highlight border */
    Boolean oldHighlight = _highlight;
    _highlight = false;
    Highlight(oldHighlight);
  }

  /* push clip region using this transform */
  int dataX, dataY, dataW, dataH;
  GetDataArea(dataX, dataY, dataW, dataH);

  /* use exposure rectangle if needed */
  if (_hasExposure) {
    int dataX2 = MIN(_exposureRect.xHigh, dataX + dataW - 1);
    int dataY2 = MIN(_exposureRect.yHigh, dataY + dataH - 1);
    dataX = MAX(_exposureRect.xLow, dataX);
    dataY = MAX(_exposureRect.yLow, dataY);
    dataW = dataX2 - dataX + 1;
    dataH = dataY2 - dataY + 1;
  }

  /* clip area to be drawn */
  winRep->PushClip(dataX, dataY, dataW - 1, dataH - 1);

  /* blank out area to be drawn */
  if (!piledDisplay) {
#if defined(DEBUG)
    printf("Clearing data area in window 0x%p\n", winRep);
#endif
    winRep->DaliFreeImages();
    winRep->SetFgColor(GetBgColor());
    winRep->SetPattern(Pattern0);
    winRep->SetLineWidth(0);
    winRep->FillRect(dataX, dataY, dataW - 1, dataH - 1);
  }
  
  /* pop the identity transform matrix */
  winRep->PopTransform();

  _hasExposure = false;
  _filterChanged = false;
  _refresh = false;

  if (mode == ControlPanel::DisplayMode) {
    _querySent = true;
    /* now sending query for events that occurred while in
       layout mode */
    _modeRefresh = false; 
    
    ControlPanel::Instance()->SetBusy();
    if (!_hasTimestamp)
      _timeStamp = TimeStamp::NextTimeStamp();
    _hasTimestamp = false;
    _bytes = 0;
    DerivedStartQuery(_queryFilter, _timeStamp);
  } else {
    winRep->PopClip();
  }

#if defined(DEBUG)
  printf("after Run %d %d %d %d\n",
	 _hasExposure, _filterChanged, _refresh, _updateTransform);
#endif
}

void View::HandleResize(WindowRep *w, int xlow, int ylow,
			unsigned width, unsigned height)
{
#if defined(DEBUG)
  printf("View::HandleResize(%d,%d,%d,%d)\n", xlow, ylow, width, height);
#endif
  
  /* is this a real size change? */
  if (_hasGeometry && _x == xlow && _y == ylow &&
      _width == width && _height == height)
    return;

  /* base class should handle this, too */
  ViewWin::HandleResize(w, xlow, ylow, width, height);
  
  _updateTransform = true; /* need to update the transformation */
  
  Dispatcher::Current()->RequestCallback(_dispatcherID);
}

void View::UpdateTransform(WindowRep *winRep)
{
#if defined(DEBUG)
  printf("View::UpdateTransform %s\n", GetName());
#endif

  winRep->ClearTransformStack();

  if (_numDimensions == 2) {
     Transform2D transform;
     CalcTransform(transform);
     winRep->PostMultiply(&transform);
  } else {
     Transform3D transform;
     CalcTransform(transform);
     winRep->MakeIdentity();
  }
}

/* Get label parameters */

void View::GetLabelParam(Boolean &occupyTop, int &extent, char *&name)
{
  occupyTop = _label.occupyTop;
  extent = _label.extent;
  name = _label.name;
}

/* Set label parameters */

void View::SetLabelParam(Boolean occupyTop, int extent, char *name)
{
  delete _label.name;

  /* CopyString() now handles NULL okay. */
  _label.name = CopyString(name);

  if (!_label.name) {
    occupyTop = false;
  }

  Boolean oldOccupyTop = _label.occupyTop;
  _label.occupyTop = occupyTop;
  _label.extent = extent;

  /* If we're just changing the label string, not whether or not we
   * have a label, we can just re-draw the label.  Otherwise, we have
   * to re-draw the whole view. */
  if (occupyTop == oldOccupyTop) {
    if (_windowRep) {
      DrawLabel();
      _windowRep->Flush();
    }
  } else {
    _updateTransform = true;

    Refresh();
  }
}

void View::XAxisDisplayOnOff(Boolean stat)
{
  if (stat != xAxis.inUse) {
    xAxis.inUse = stat;
    _updateTransform = true;
  }

  Refresh();
}

void View::YAxisDisplayOnOff(Boolean stat)
{
  if (stat != yAxis.inUse) {
    yAxis.inUse = stat;
    _updateTransform  = true;
  }

  Refresh();
}

/* Find real window coords */

inline void FindRealCoord(WindowRep *winRep, Coord xlow, Coord ylow, 
			  Coord xhigh, Coord yhigh, int &txlow, int &tylow,
			  int &txhigh, int &tyhigh)
{
  Coord xl,yl, xh, yh;
  winRep->Transform(xlow, ylow, xl, yl);
  winRep->Transform(xhigh, yhigh, xh, yh);
  txlow = (int)MIN(xl, xh);
  txhigh = (int)MAX(xl, xh);
  tylow = (int)MIN(yl, yh);
  tyhigh = (int)MAX(yl,yh);
}

/* Update filter by scrolling.
Algorithm:
	If no exposure and can scroll, scroll the window. 
	Change _filterChanged into _hasExposure
Return:
	0: can not scroll.
	1: scroll was performed, and update the _exposureRect.
	2: can scroll, and no exposure left.
	true if filter was scrolled.
	false if not.
*/

View::UpdateFilterStat View::UpdateFilterWithScroll()
{
#if defined(DEBUG)
  printf("UpdateFilterWithScroll: _refresh %d, _filterChanged %d, _hasExposure %d\n",
	 _refresh, _filterChanged, _hasExposure);
#endif
  
  WindowRep *winRep = GetWindowRep();
  Coord xlow, ylow, xhigh, yhigh;
  xlow = _filter.xLow;
  ylow = _filter.yLow;
  xhigh = _filter.xHigh;
  yhigh = _filter.yHigh;

  if ( /* make sure we can scroll */
      winRep->Scrollable() 
      /* and have current and last filter available */
      && _hasLastFilter && _filterChanged
      /* and we are not refreshing the window by redraw */
      && !_refresh
      /* And did not zoom */
      &&fabs((_filter.xHigh - _filter.xLow)-
	     (_lastFilter.xHigh-_lastFilter.xLow)) <= DELTA_X
      &&fabs((_filter.yHigh - _filter.yLow)-
	     (_lastFilter.yHigh-_lastFilter.yLow)) <= DELTA_Y
      /* and the two filters overlap */
      && Geom::RectRectClip(xlow, ylow, xhigh, yhigh,_lastFilter.xLow,
			    _lastFilter.yLow, _lastFilter.xHigh, _lastFilter.yHigh)
      
      /* and scrollling to the right or scroll left */
      &&(	(_lastFilter.yLow == _filter.yLow &&
		 _lastFilter.yHigh == _filter.yHigh )
	 ||	(_lastFilter.xLow == _filter.xLow &&
		 _lastFilter.xHigh == _filter.xHigh ))) {
    
    /* Find the real window coord of the overlap region */
    int fxl, fyl, fxh, fyh; /* transformed filter coord */
    int lxl, lyl, lxh, lyh; /* xformed last filter */
    int oxl, oyl, oxh, oyh; /* xformed overlap */
    FindRealCoord(winRep, _filter.xLow, _filter.yLow, 
		  _filter.xHigh, _filter.yHigh, fxl, fyl, fxh, fyh);
    FindRealCoord(winRep, _lastFilter.xLow, _lastFilter.yLow, 
		  _lastFilter.xHigh, _lastFilter.yHigh, lxl, lyl, lxh, lyh);
    FindRealCoord(winRep, xlow, ylow, xhigh, yhigh, oxl, oyl, oxh, oyh);
    int overlapWidth = oxh-oxl+1;
    int overlapHeight = oyh-oyl+1;
    
    int dataX, dataY, dataW, dataH;
    GetDataArea(dataX, dataY, dataW, dataH);

#if defined(DEBUG)
    printf("data: x:%d, y:%d, w:%d, h:%d\n", dataX, dataY, dataW, dataH);
#endif

    winRep->ScrollAbsolute(oxl, oyl, overlapWidth, overlapHeight,
			oxl-fxl+lxl, oyl-fyl+lyl);
    
    /* Find exposed region for redraw */
    if (_filter.xLow > _lastFilter.xLow) {
      /* scrolling data left */
      _exposureRect.xLow = lxh-overlapWidth;
      _exposureRect.yLow = lyl;
      _exposureRect.xHigh = lxh;
      _exposureRect.yHigh = lyh;
    }
    else if (_filter.xLow < _lastFilter.xLow) {
      /* scrolling data right */
      _exposureRect.xLow = lxl;
      _exposureRect.yLow = lyl;
      _exposureRect.xHigh = lxl+overlapWidth;
      _exposureRect.yHigh = lyh;
    }
    else if (_filter.yLow > _lastFilter.yLow) {
      /* scroll data down */
      _exposureRect.xLow = lxl;
      _exposureRect.yLow = lyl;
      _exposureRect.xHigh = lxh;
      _exposureRect.yHigh = lyl+overlapHeight;
    }
    else if (_filter.yLow < _lastFilter.yLow) {
      /* scroll up */
      _exposureRect.xLow = lxl;
      _exposureRect.yLow = lyl+overlapHeight-1;
      _exposureRect.xHigh = lxh;
      _exposureRect.yHigh = lyh;
    }
    else {
      /* new filter same as old filter. */
      return SameFilter;
    }

#if defined(DEBUG)
    printf("after scroll exposure (%d,%d),(%d,%d)\n",
	   _exposureRect.xLow, _exposureRect.yLow,
	   _exposureRect.xHigh, _exposureRect.yHigh);
#endif
    
    return Scrolled;
  }
  return NotScrolled;
}

void View::AbortQuery()
{
  // If the View object is really anything other than a
  // TDataViewX, ViewRanges, or ViewScatter, and _querySent is true,
  // this will call a pure virtual function.

  if (_querySent) {
#if defined(DEBUG)
    printf("View %s aborting...\n", GetName());
#endif
    DerivedAbortQuery();
    ReportQueryDone(0, true);
  }
}

void View::Refresh()
{
  _refresh = true;
  Dispatcher::Current()->RequestCallback(_dispatcherID);
}

void View::ReportViewCreated()
{
  if (!_viewCallbackList)
    return;
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling ViewCreated callback 0x%p for view 0x%p\n",
	   callBack, this);
#endif
    callBack->ViewCreated(this);
  }
  _viewCallbackList->DoneIterator(index);
}

void View::ReportViewRecomputed()
{
  if (!_viewCallbackList)
    return;
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling ViewRecomputed callback 0x%p for view 0x%p\n",
	   callBack, this);
#endif
    callBack->ViewRecomputed(this);
  }
  _viewCallbackList->DoneIterator(index);
}

void View::ReportViewDestroyed()
{
  if (!_viewCallbackList)
    return;
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling ViewDestroyed callback 0x%p for view 0x%p\n",
	   callBack, this);
#endif
    callBack->ViewDestroyed(this);
  }
  _viewCallbackList->DoneIterator(index);
}

void View::ReportFilterAboutToChange()
{
  if (!_viewCallbackList)
    return;
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling FilterAboutToChange callback 0x%p for view 0x%p\n",
	   callBack, this);
#endif
    callBack->FilterAboutToChange(this);
  }
  _viewCallbackList->DoneIterator(index);
}

void View::ReportFilterChanged(VisualFilter &filter, int flushed)
{
  if (!_viewCallbackList)
    return;
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling FilterChanged callback 0x%p for view 0x%p\n",
	   callBack, this);
#endif
    callBack->FilterChanged(this, filter, flushed);
  }
  _viewCallbackList->DoneIterator(index);
}

void View::InsertViewCallback(ViewCallback *callBack)
{
  if (!_viewCallbackList)
    _viewCallbackList = new ViewCallbackList;
    
  DOASSERT(_viewCallbackList, "Invalid view callback list");

#if defined(DEBUG)
  printf("Inserting 0x%p to view callback list\n", callBack);
#endif

  _viewCallbackList->Append(callBack);
}

void View::DeleteViewCallback(ViewCallback *callBack)
{
  DOASSERT(_viewCallbackList, "Invalid view callback list");

#if defined(DEBUG)
  printf("Removing 0x%p from view callback list\n", callBack);
#endif

  _viewCallbackList->Delete(callBack);
}

void View::Iconify(Boolean iconified)
{
  if (iconified)
    AbortQuery();

  Refresh();
}

void View::ModeChange(ControlPanel::Mode mode)
{
#if defined(DEBUG)
  printf("Change mode %d,%d,%d,%d\n", _hasExposure,
	 _filterChanged, _refresh, _updateTransform);
#endif

  if (mode == ControlPanel::LayoutMode && _querySent) {
#if defined(DEBUG)
    printf("abort query from mode change\n");
#endif
    AbortQuery();
    _modeRefresh = true;
  }

  Refresh();
}

void View::Highlight(Boolean flag)
{
#if defined(DEBUG)
  printf("Highlight view %s %d\n", GetName(), flag);
#endif

  if (_highlight == flag)
    return;

  _highlight = flag;

  WindowRep *winRep = GetWindowRep();
  if (!winRep) {
    /* View is unmapped but is still selected, and we're told by the
       client to unhighlight the view. This may occur when a window
       is destroyed by the window manager and all views are unmapped,
       but if a view among those is selected, it will stay selected. */
    return;
  }

  winRep->SetXorMode();
  DrawHighlight();
  winRep->SetCopyMode();
}

void View::DrawHighlight()
{
  if (!Mapped())
    return;

  WindowRep *winRep = GetWindowRep();

  int x,y;
  unsigned int w,h;
  
  if (_label.occupyTop) {
    Geometry(x, y, w, h);
    winRep->AbsoluteLine(x, y, w - 1, x, 3);
    winRep->AbsoluteLine(x + w - 1, y, x + w - 1, y + h - 1, 3);
    winRep->AbsoluteLine(x + w - 1, y + h - 1, x, y + h - 1, 3);
    winRep->AbsoluteLine(x, y + h - 1, x, y, 3);
  } else {
    int labelW, labelH;
    GetLabelArea(x, y, labelW, labelH);
    winRep->AbsoluteLine(x + _label.extent / 2, y + _label.extent, 
			 x + _label.extent / 2, labelH, _label.extent);
  }
  winRep->Flush();
}

void View::SetXAxisAttrType(AttrType type)
{ 
  _xAxisAttrType = type;
}

void View::SetYAxisAttrType(AttrType type)
{
  _yAxisAttrType = type;
}

char *View::DispatchedName()
{
  return "View";
}

void View::AppendCursor(DeviseCursor *cursor)
{
  _cursors->Append(cursor);
}

void View::DeleteCursor(DeviseCursor *cursor)
{
  _cursors->Delete(cursor);
}

Boolean View::DrawCursors()
{
  DOASSERT(_numDimensions == 2, "Invalid number of dimensions");

#if defined(DEBUG)
  printf("DrawCursors for %s\n", GetName());
#endif

  if (!Mapped()) {
#if defined(DEBUG)
    printf("not mapped\n");
#endif
    return false;
  }

  if (!_cursorsOn) {
    DoDrawCursors();
    _cursorsOn = true;
    return false;
  }

  return true;
}

Boolean View::HideCursors()
{
#if defined(DEBUG)
  printf("HideCursors for %s\n", GetName());
#endif

  if (!Mapped()) {
#if defined(DEBUG)
    printf("not mapped\n");
#endif
    return false;
  }

  if (_cursorsOn) {
    DoDrawCursors();
    _cursorsOn = false;
    return true;
  }

  return false;
}

void View::DoDrawCursors()
{
#if defined(DEBUG)
  printf("DoDrawCursors\n");
#endif

  WindowRep *winRep = GetWindowRep();
  winRep->SetPattern(Pattern0);
  winRep->SetLineWidth(0);
  winRep->SetXorMode();
  
  int index;
  for(index = _cursors->InitIterator(); _cursors->More(index);) {
    DeviseCursor *cursor = _cursors->Next(index);
    VisualFilter *filter;
    GlobalColor color;
    cursor->GetVisualFilter(filter, color);

    Coord xLow, yLow, xHigh, yHigh;
    xLow = MAX(_filter.xLow, filter->xLow);
    xHigh = MIN(_filter.xHigh, filter->xHigh);
    yLow = MAX(_filter.yLow, filter->yLow);
    yHigh = MIN(_filter.yHigh, filter->yHigh);

    if ((filter->flag & VISUAL_X) && (filter->flag & VISUAL_Y)) {
#if defined(DEBUG)
      printf("DoDrawCursors: Drawing XY cursor in\n  %s\n", GetName());
#endif
      if (!(filter->xHigh < _filter.xLow || filter->xLow > _filter.xHigh
	    || filter->yHigh < _filter.yLow || filter->yLow > _filter.yHigh))
	winRep->FillRect(xLow, yLow, xHigh - xLow, yHigh - yLow);
    } else if (filter->flag & VISUAL_X) {
#if defined(DEBUG)
      printf("DoDrawCursors: Drawing X cursor in\n  %s\n", GetName());
#endif
      if (!(filter->xHigh < _filter.xLow || filter->xLow > _filter.xHigh))
	winRep->FillRect(xLow, _filter.yLow, xHigh - xLow,
			 _filter.yHigh - _filter.yLow);
    } else if (filter->flag & VISUAL_Y) {
#if defined(DEBUG)
      printf("DoDrawCursors: Drawing Y cursor in\n  %s\n", GetName());
#endif
      if (!(filter->yHigh < _filter.yLow || filter->yLow > _filter.yHigh))
	winRep->FillRect(_filter.xLow, yLow,
			 _filter.xHigh - _filter.xLow, yHigh - yLow);
    }
  }

  _cursors->DoneIterator(index);

  winRep->SetCopyMode();
}

void View::ClearHistory()
{
  _filterQueue->Clear();
}

void View::InsertHistory(VisualFilter &filter)
{
  (void)_filterQueue->Enqueue(filter, filter.marked);
}

/* Put current pixmap into buffer. bytes == # of bytes
   used to create the pixmap. */

void View::CachePixmap(int bytes)
{
}

/* Look into pixmap buffer for pixmap that we can use for drawing
   filter. Restore the pixmap, and return a new visual filter. */

View::PixmapStat View::RestorePixmap(VisualFilter filter,
				     VisualFilter &newFilter)
{
  int x, y;
  unsigned int width, height;
  Geometry(x, y, width, height);

#if defined(DEBUG)
  if (_pixmap) {
    printf("RestorePixmap %s\n", GetName());
    printf("cur filter: %f,%f,%f,%f\n", filter.xLow, filter.xHigh,
	   filter.yLow, filter.yHigh);
    printf("pix filter: %f,%f,%f,%f\n",
	   _pixmap->filter.xLow, _pixmap->filter.xHigh,
	   _pixmap->filter.yLow, _pixmap->filter.yHigh);
    printf("cur width %d, height %d, pix %d, %d\n", width, height,
	   _pixmap->width, _pixmap->height);
  }
#endif

  if (!PixmapEnabled())
    return PixmapNone;

  if (Mapped() && _pixmap && 
      filter.xLow ==  _pixmap->filter.xLow &&
      filter.yLow == _pixmap->filter.yLow &&
      filter.xHigh == _pixmap->filter.xHigh &&
      filter.yHigh == _pixmap->filter.yHigh &&
      _pixmap->width == (int)width && _pixmap->height == (int)height) {
    GetWindowRep()->DisplayPixmap(_pixmap);
    return PixmapTotal;
  }

  return PixmapNone;
}

void View::InvalidatePixmaps()
{
  if (!_pixmap)
    return;

  free(_pixmap->data);
  delete _pixmap;
  _pixmap = NULL;
}

void View::SavePixmaps(FILE *file)
{
#if defined(DEBUG)
  printf("SavePixmap at bytes %ld\n", ftell(file));
  printf("View SavePixmaps bytes %d\n", _bytes);
#endif

  // Store a known 4-byte integer at head of file to distinguish
  // the byte order (little/big endian) used on this machine; at
  // load time, check the value of the integer.

  unsigned long int magic = 0xdeadbeef;
  if (fwrite(&magic, sizeof magic, 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }
  
  /* Disable cursors if currently displayed */
  Boolean cursorState = HideCursors();
  Boolean dispSymbol = DisplaySymbols(true);
  Boolean dispConnector = DisplayConnectors(false);

#ifndef JPEG

  //
  // Save pixmap in run-length-encoded format
  //

  int saved = 0;
  DevisePixmap *pixmap = 0;
  if (Iconified() || !Mapped() ||_refresh || _bytes < VIEW_BYTES_BEFORE_SAVE) {
    if (_pixmap) {
      /* save old pixmap */
      saved = 1;
      pixmap = _pixmap;
    } else
      saved = 0;
  } else {
    /* save current pixmap */
    saved = 1;
    WindowRep *winRep = GetWindowRep();
    pixmap = winRep->GetPixmap();
    if (!pixmap) {
      saved = 0;
    }
  }
  
  if (fwrite(&saved, sizeof(saved), 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }

  if (!saved) {
    /* Return cursors to original state */
    if (cursorState)
      (void)DrawCursors();
    (void)DisplaySymbols(dispSymbol);
    (void)DisplayConnectors(dispConnector);
    return;
  }
  
  DOASSERT(pixmap, "No pixmap");

#if defined(DEBUG)
  printf("Saving Pixmap for %s, data %d bytes\n", GetName(), _bytes);
#endif

  pixmap->dataBytes = _bytes; /* # of data bytes used to create pixmap*/
  pixmap->filter = _filter;
  if (GetXAxisAttrType() == DateAttr) {
    /* Convert to date and back to be consistent with control panel's
       date format. Otherwise, we might get round-off errors */
    (void)ParseFloatDate(DateString(pixmap->filter.xLow),
			 pixmap->filter.xLow);
    (void)ParseFloatDate(DateString(pixmap->filter.xHigh),
			 pixmap->filter.xHigh);
  }
  if (GetYAxisAttrType() == DateAttr) {
    (void)ParseFloatDate(DateString(pixmap->filter.yLow),
			 pixmap->filter.yLow);
    (void)ParseFloatDate(DateString(pixmap->filter.yHigh),
			 pixmap->filter.yHigh);
  }
  
#if defined(DEBUG)
  printf("SavePixmap filter %f,%f,%f,%f\n",
	 pixmap->filter.xLow, pixmap->filter.xHigh,
	 pixmap->filter.yLow, pixmap->filter.yHigh);
#endif
		
  if (fwrite(pixmap, sizeof(*pixmap), 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }
  if (fwrite(pixmap->data, pixmap->compressedBytes, 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }

#else

  //
  // Save pixmap in JPEG format
  //

  int num[2] = {0, 0};
  int pos = ftell(file);
  if (!Mapped() || _bytes < 0 * VIEW_BYTES_BEFORE_SAVE || _refresh) {
    num[1] = pos + 2 * sizeof(int);
    if (fwrite(num, sizeof(num), 1, file) != 1) {
      reportErrSys("fwrite");
      DOASSERT(0, "Cannot write pixmap file");
    }
    /* Return cursors to original state */
    if (cursorState)
      (void)DrawCursors();
    (void)DisplaySymbols(dispSymbol);
    (void)DisplayConnectors(dispConnector);
    return;
  }
  
  /* Save window pixmap */
  num[0] = 1;

#if 0
  if (fwrite(&num, sizeof(num), 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }
#endif

  WindowRep *winRep = GetWindowRep();
  DevisePixmap *pixmap = winRep->GetPixmap();
  pixmap->dataBytes = _bytes;
  pixmap->filter = _filter;
  
#if defined(DEBUG)
  printf("pixMap dataBytes %d, imageBytes %d, width %d, height %d, bpl %d, pad %d\n",
	 pixmap->dataBytes, pixmap->imageBytes, pixmap->width,
	 pixmap->height, pixmap->bytes_per_line, pixmap->padding);
#endif
  
#if 0
  if (fwrite(pixmap, sizeof(*pixmap), 1, file) != 1 ) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }
#endif
  
#if defined(DEBUG)
  printf("before compress, at %d\n", ftell(file));
#endif

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  JSAMPROW row_pointer[1];
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo,file);
  cinfo.image_width = pixmap->width;
  cinfo.image_height = pixmap->height;
  cinfo.input_components = pixmap->bytes_per_line/pixmap->width;
  cinfo.in_color_space = JCS_GRAYSCALE;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 100, TRUE);
  jpeg_start_compress(&cinfo, TRUE);
  
  unsigned char *data = (unsigned char *)pixmap->data;
  for(int i = 0; i < pixmap->height; i++) {
    row_pointer[0] = &data[i * pixmap->bytes_per_line];
    (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
  
  int posNow = ftell(file);
  fseek(file, pos + sizeof(int), 0);
  fwrite(&posNow, sizeof(int), 1, file);
  fseek(file, posNow, 0);
  
#if defined(DEBUG)
  printf("after compress, at %d\n", ftell(file));
#endif
#endif

  /* Return cursors to original state */
  if (cursorState)
    (void)DrawCursors();
  (void)DisplaySymbols(dispSymbol);
  (void)DisplayConnectors(dispConnector);
}

/* Restore pixmaps from an open file into pixmap buffer */

void View::LoadPixmaps(FILE *file)
{
  // The first 4-byte integer contains a known value. Check the value
  // to make sure we're reading data stored in the same endian order
  // as this machine is using.

  unsigned long int check;
  if (fread(&check, sizeof check, 1, file) != 1) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }

  if (check != 0xdeadbeef) {
    printf("Note: Pixel image for %s not in compatible format.\n",
	   GetName());
    _pixmap = NULL;
    return;
  }
  
#ifndef JPEG

  //
  // Load image stored in run-length-encoded format
  //

  int saved;
  if (fread(&saved, sizeof(saved), 1, file) != 1 ) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }
  if (!saved) {
#if defined(DEBUG)
    printf("View::LoadPixmaps: %s not saved\n", GetName());
#endif
    _pixmap = NULL;
    return;
  }

#if defined(DEBUG)
  printf("Loading pixmap for %s\n", GetName());
#endif

  DevisePixmap *pixmap = new DevisePixmap;
  DOASSERT(pixmap, "Out of memory");

  if (fread(pixmap, sizeof(*pixmap), 1, file) != 1 ) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }

#if defined(DEBUG)
  printf("LoadPixmap filter %f,%f,%f,%f\n",
	 pixmap->filter.xLow, pixmap->filter.xHigh,
	 pixmap->filter.yLow, pixmap->filter.yHigh);
#endif
		
  if (!(pixmap->data = (unsigned char *)malloc(pixmap->compressedBytes))) {
    fprintf(stderr,"View::LoadPixmaps out of memory\n");
    DOASSERT(0, "Cannot read pixmap file");
  }
  
  if (fread(pixmap->data, pixmap->compressedBytes, 1, file) != 1) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }
  _pixmap = pixmap;
  
#else

  //
  // Load image stored in JPEG format
  //

  fseek(file, _nextPos, 0);
  printf("Load pixmap at bytes %d\n", ftell(file));

  int num[2];
  if (fread(num, sizeof(num), 1, file) != 1) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }
  _nextPos = num[1];
  
  if (num[0] <= 0 )
    return;
  
  DOASSERT(num[0] <= 1, "Too many pixmaps");
  
  _pixmap = new DevisePixmap;
  DOASSERT(_pixmap, "Out of memory");

  if (fread(_pixmap, sizeof(*_pixmap), 1, file) != 1) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }

#if defined(DEBUG)
  printf("pixMap dataBytes %d, imageBytes %d, width %d, height %d, bpl %d pad %d\n",
	 _pixmap->dataBytes, _pixmap->imageBytes, _pixmap->width,
	 _pixmap->height, _pixmap->bytes_per_line, _pixmap->padding);
#endif
  
#if defined(DEBUG)
  printf("before decompress, at %d\n", ftell(file));
#endif

  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  
  jpeg_stdio_src(&cinfo,file);
  (void)jpeg_read_header(&cinfo,TRUE);
  jpeg_start_decompress(&cinfo);

#if defined(DEBUG)
  printf("allocating %d bytes\n", _pixmap->imageBytes);
#endif

  unsigned char *data = (unsigned char *)malloc(_pixmap->imageBytes);
  DOASSERT(data, "Out of memory");

  _pixmap->data = data;
  unsigned char *buffer[1];
  for(int i = 0; i < _pixmap->height; i++) {
    buffer[0] = &data[i * _pixmap->bytes_per_line];
#if defined(DEBUG)
    printf("reading line %d\n", i);
#endif
    jpeg_read_scanlines(&cinfo,buffer,1);
  }

  (void)jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

#if defined(DEBUG)
  printf("after decompress, at %d\n", ftell(file));
#endif
#endif
}

/* Print view statistics */

void View::PrintStat()
{
  int total = _jump + _zoomIn + _zoomOut + _scrollLeft + _scrollRight
              + _unknown;
  printf("View %s: total operationss %d\n", GetName(), total);

  if (total <= 0)
    return;

  printf("  Jump %d, %.2f%%\n", _jump, 100.0 * _jump / total);
  printf("  ZoomIn %d, %.2f%%\n", _zoomIn, 100.0 * _zoomIn / total);
  printf("  ZoomOut %d, %.2f%%\n", _zoomOut, 100.0 * _zoomOut / total);
  printf("  ScrollLeft %d, %.2f%%\n", _scrollLeft,
	 100.0 * _scrollLeft / total);
  printf("  ScrollRight %d, %.2f%%\n", _scrollRight,
	 100.0 * _scrollRight / total);
  printf("  Unknown %d, %.2f%%\n", _unknown, 100.0 * _unknown / total);
}

void View::CompRhoPhiTheta()
{
#if defined(DEBUG)
  printf("<<<< x = %f y = %f z = %f\n",
         _camera.x_, _camera.y_, _camera.z_);
  printf("<<<< fx = %f fy = %f fz = %f\n",
         _camera.fx, _camera.fy, _camera.fz);
  printf("<<<< rho = %f phi = %f theta = %f\n\n",
         _camera._rho, _camera._phi, _camera._theta);
#endif

  if (!_camera.spherical_coord) {
    double X = _camera.x_ - _camera.fx;
    double Y = _camera.y_ - _camera.fy;
    double Z = -(_camera.z_ - _camera.fz);

    _camera._rho = sqrt(SQUARE(X) + SQUARE(Y) + SQUARE(Z));

    if (_camera._rho > 0)
      _camera._phi = acos(Y / _camera._rho);
    else {
      _camera._phi = 0.0;
#if defined(DEBUG)
      printf("*********** WARNING *****************\n");
#endif
    }

    if (_camera._rho == 0)
      _camera._theta = 0.0;

    // ------------- on yz-axis
    else if (X == 0 && Z >= 0)  // on +z axis
      _camera._theta = 0.0;
    else if (X == 0 && Z < 0)   // on -z axis
      _camera._theta = M_PI;
    
    // ------------- on xy-axis
    else if (Z == 0 && X > 0) // on +x axis
      _camera._theta = M_PI_2;
    else if (Z == 0 && X < 0) // on -x axis
      _camera._theta = M_PI_2 + M_PI;    // pi * 2 / 3
    
    // ------------- four quadrants
    else if (X > 0 && Z > 0)
      _camera._theta = atan(X / Z);
    else if (X > 0 && Z < 0)
      _camera._theta = M_PI + atan(X / Z);
    else if (X < 0 && Z < 0)
      _camera._theta = M_PI + atan(X / Z);
    else if (X < 0 && Z > 0)
      _camera._theta = (M_PI_2 + M_PI) + fabs(atan(Z / X));

    else {
      printf("cx = %f cy = %f cz = %f\n", X, Y, Z);
      DOASSERT(0, "Invalid coordinates");
    }
  } else {
    _camera.x_ = _camera._rho * sin(_camera._phi) * sin(_camera._theta);
    _camera.x_ += _camera.fx;
    _camera.y_ = _camera._rho * cos(_camera._phi);
    _camera.y_ += _camera.fy;
    _camera.z_ = -_camera._rho * sin(_camera._phi) * cos(_camera._theta);
    _camera.z_ += _camera.fz;
  }

#if defined(DEBUG)
  printf(">>>> x = %f y = %f z = %f\n",
         _camera.x_, _camera.y_, _camera.z_);
  printf(">>>> fx = %f fy = %f fz = %f\n",
         _camera.fx, _camera.fy, _camera.fz);
  printf(">>>> rho = %f phi = %f theta = %f\n\n",
         _camera._rho, _camera._phi, _camera._theta);
#endif
}

void View::SetCamera(Camera new_camera)
{
  /* see if 3D mapping needs to be updated */
  Boolean newMap = false;
  if (new_camera.x_ != _camera.x_ ||
      new_camera.y_ != _camera.y_ || 
      new_camera.z_ != _camera.z_ ||
      new_camera._dvs != _camera._dvs ||
      new_camera._rho != _camera._rho || 
      new_camera._phi != _camera._phi || 
      new_camera._theta != _camera._theta || 
      new_camera.fx != _camera.fx ||
      new_camera.fy != _camera.fy ||
      new_camera.fz != _camera.fz || 
      new_camera._perspective != _camera._perspective || 
      new_camera._twist_angle != _camera._twist_angle || 
      new_camera.H != _camera.H ||
      new_camera.V != _camera.V)
    newMap = true;

  _camera = new_camera;

  if (newMap) {
    CompRhoPhiTheta();
    _updateTransform = true;
    Refresh();
  }

  /* these calls cause the user interface to update the 3D query dialog */
  ReportFilterAboutToChange();
  ReportFilterChanged(_filter, false);
}

void View::Draw3DAxis()
{
#if defined(DEBUG)
  printf("Drawing 3D axis\n");
#endif

  WindowRep *win = GetWindowRep();
  win->SetFgColor(GetFgColor());
  Map3D::DrawRefAxis(win, _camera);
}

void View::SetViewDir(int H, int V)
{
  _camera.H = H;
  _camera.V = V;
}

DevStatus
View::PrintPS()
{
#if defined(DEBUG)
  printf("View(0x%p)::PrintPS(%s)\n", this, _name);
#endif
  DevStatus result(StatusOk);

  _printing = true;

  DeviseDisplay *psDispP = DeviseDisplay::GetPSDisplay();

  // Switch this view over to PostScript drawing mode.
  Rectangle viewGeom;
  int xVal, yVal;
  /* Get the origin from the XWindowRep instead of the ViewWin because
   * the ViewWin's origin is always set to (0, 0) for some reason. */
  _winReps.GetScreenWinRep()->Origin(xVal, yVal);
  viewGeom.x = xVal;
  viewGeom.y = yVal;
  viewGeom.width = _width;
  viewGeom.height = _height;

  Rectangle parentGeom;
  unsigned int width, height;
#if defined(MARGINS) || defined(TK_WINDOW)
  _parent->RealGeometry(xVal, yVal, width, height);
#else
  _parent->Geometry(xVal, yVal, width, height);
#endif
  parentGeom.x = xVal;
  parentGeom.y = yVal;
  parentGeom.width = width;
  parentGeom.height = height;

  /* If we're in piled mode, the drawing will actually be done using
   * the WindowRep of the _top_ view in the pile, so that's the one
   * that has to be set for file output. */
  if (_pileMode) {
    GetFirstSibling()->SetFileOutput(viewGeom, parentGeom);
  } else {
    SetFileOutput(viewGeom, parentGeom);
  }

  // Force a refresh to print the PostScript.
  fprintf(psDispP->GetPrintFile(), "\n%% Start of view '%s'\n", _name);
  Refresh();

  return result;
}

DevStatus
View::PrintPSDone()
{
#if defined(DEBUG)
  printf("View::PrintPSDone(%s)\n", _name);
#endif
  DevStatus result(StatusOk);

  DeviseDisplay *psDispP = DeviseDisplay::GetPSDisplay();

  fprintf(psDispP->GetPrintFile(), "%% End of view '%s'\n", _name);

  // Switch this view back to screen drawing mode.
  if (_pileMode) {
    GetFirstSibling()->SetScreenOutput();
  } else {
    SetScreenOutput();
  }

  // Continue printing any more views that need to be printed.
  result += ViewWin::PrintPS();

  _printing = false;

  return result;
}
