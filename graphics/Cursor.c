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
#include "View.h"

DeviseCursor::DeviseCursor(char *name, VisualFlag flag, Color color)
{
  _name = name;
  _visFlag = flag;
  _src = 0;
  _dst = 0;
  _color = color;

  View::InsertViewCallback(this);
}

DeviseCursor::~DeviseCursor()
{
  View::DeleteViewCallback(this);

  Boolean redrawCursors = false;

  if (_dst)
    redrawCursors = _dst->HideCursors();

  if (_dst)
    _dst->DeleteCursor(this);

  if (_dst && redrawCursors)
    (void)_dst->DrawCursors();
}

/* Set source view. Changing this view's visual filter
   changes in the cursor's position. Can also set to NULL */

void DeviseCursor::SetSource(View *view)
{
  Boolean redrawCursors = false;

  if (_dst)
    redrawCursors = _dst->HideCursors();

  _src = view;

  if (_dst && redrawCursors)
    (void)_dst->DrawCursors();
}

/* Set destination: this is where the cursor will be drawn.
   Can also set to NULL. */

void DeviseCursor::SetDst(View *view)
{
  Boolean redrawCursors = false;

  if (_dst)
    redrawCursors = _dst->HideCursors();

  if (_dst) {
    _dst->DeleteCursor(this);
    if (redrawCursors)
      (void)_dst->DrawCursors();        // redraw cursors at old destination
  }
  
  _dst = view;

  redrawCursors = false;
  if (_dst)
    redrawCursors = _dst->HideCursors();

  if (_dst)
    _dst->AppendCursor(this);

  if (_dst && redrawCursors)
    (void)_dst->DrawCursors();          // redraw cursors at new destination
}

/* Get current visual filter. return TRUE if it exists. */

Boolean DeviseCursor::GetVisualFilter(VisualFilter *&filter, Color &color)
{
  if (!_src)
    return false;
  
  _src->GetVisualFilter(_filter);
  _filter.flag = _visFlag;
  filter = &_filter;
  color = _color;
  return true;
}

void DeviseCursor::FilterAboutToChange(View *view)
{
  if (_dst && view == _src)
    (void)_dst->HideCursors();
}

void DeviseCursor::FilterChanged(View *view, VisualFilter &filter,
				 int flushed)
{
  if (_dst && view == _src)
    (void)_dst->DrawCursors();
}

void DeviseCursor::ViewDestroyed(View *view)
{
  if (_dst && (view == _src || view == _dst))
    (void)_dst->HideCursors();

  if (view == _src)
    _src = 0;

  if (view == _dst)
    _dst = 0;
}

void DeviseCursor::MoveSourceX(Coord x)
{
  if (!_src)
    return;

  if (_dst)
    (void)_dst->HideCursors();

  VisualFilter filter;
  _src->GetVisualFilter(filter);
  Coord width = filter.xHigh - filter.xLow;
  Coord newXLow = x - width / 2.0;
  Coord xMin;
  if (_src->GetXMin(xMin) && newXLow < xMin)
    newXLow = xMin;
  filter.xLow = newXLow;
  filter.xHigh = newXLow + width;
  _src->SetVisualFilter(filter);
}
