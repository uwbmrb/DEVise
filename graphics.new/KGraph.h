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
  Revision 1.4  1995/12/16 00:48:20  ravim
  Handles window events for popup and resize.

  Revision 1.3  1995/12/08 23:44:53  ravim
  Polygon filled.

  Revision 1.2  1995/12/06 05:44:38  ravim
  Initial version.
*/

#ifndef KGraph_h
#define KGraph_h

#include "Geom.h"
#include "Display.h"

class KGraph: protected WindowRepCallback
{
public:
  KGraph(DeviseDisplay *dis);
  virtual ~KGraph();

  // Initialize the settings
  void Init(char *winname, char *statname);

  // Set the number of axes to display
  void setAxes(int num);

  // Specify points along the axes = number of axes in the graph
  void setPoints(Coord *pts, int num);

  // Display on the graph
  void Display();

private:
  DeviseDisplay *_dis;
  WindowRep *_win;
  char *_winame;
  char *_statname;
  int _naxes;
  Coord *_pts;
  Point *_xyarr;

  // Coords of center of circle and diameter
  Coord cx, cy;
  int diam;

  void ClearGraph();
  void DrawCircle();
  void DrawAxes();
  void PlotPoints();
  void ShowVal();
  void Rotate(Coord xval, int degree, Coord &retx, Coord &rety);
  Coord Scale(Coord xval, Coord max);

  // Handle window events
  virtual void HandlePress(WindowRep *w, int xlow, int ylow, int xhigh,
			   int yhigh, int button);
  
  virtual Boolean HandlePopUp(WindowRep *w, int x, int y, int button, 
			      char **&msgs, int &numMsgs);
  virtual void HandleResize(WindowRep *w, int xlow, int ylow, unsigned width,
			    unsigned height);

  char **msgBuf;
};

#endif
