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

  $Log$*/

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
  
  // Specify all the views corr. to this graph
  Boolean AddViews(ViewGraph **v, int num);

  // Call which displays the graph corr. to the specified statistic
  Boolean Display(int statnum);

private:
  BasicStats **_stats_list;
  // Number of Stat classes being displayed
  int _numstats;

  // The specific stat to be displayed
  int _statnum;

  // The KGraph display
  KGraph *_kg;
  // Devise display
  DeviseDisplay *_dis;
};

#endif
