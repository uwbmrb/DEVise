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
  Revision 1.2  1995/12/08 23:44:05  ravim
  Callbacks added.

  Revision 1.1  1995/12/06 05:40:25  ravim
  Initial version.
*/

#ifndef ViewKGraph_h
#define ViewKGraph_h

#include "DeviseTypes.h"
#include "ViewGraph.h"
#include "BasicStats.h"
#include "KGraph.h"

class ViewKGraph
{
public:
  ViewKGraph();
  ~ViewKGraph();

  void Init();
  
  // Specify all the views corr. to this graph - also specify the name of 
  // the window to be created for the graph.
  Boolean AddViews(ViewGraph **views, int num, char *name);

  // Return list of views currently displayed in Kiviat Graph
  void GetViews(char *&name, ViewGraph **&views, int &num) {
    name = _name;
    views = _view_list;
    num = _numviews;
  }

  // Call which displays the graph corr. to the specified statistic
  Boolean Display(int statnum);

  // CallBack from a statistic class object which means that some of the
  // data to be displayed has changed.
  void Callback(BasicStats *bs);

private:
  // Number of views displayed
  int _numviews;
  ViewGraph **_view_list;

  // The specific stat to be displayed
  int _statnum;

  // The KGraph display
  KGraph *_kg;

  // Devise display
  DeviseDisplay *_dis;

  // Window name
  char *_name;
};

#endif
