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
  Revision 1.9  1995/12/14 21:20:00  jussi
  Replaced 0x%x with 0x%p.

  Revision 1.8  1995/12/05 17:07:34  jussi
  Statistics are now part of ViewGraph, the subclass of TDataViewX.

  Revision 1.7  1995/11/29 17:11:21  jussi
  Relaxed condition which determines which GData records are included
  in statistics computation. Bar graphs may have y values beyond
  filter.yHigh, and the bar still appears on the screen and so should
  be included in statistics.

  Revision 1.6  1995/11/28  05:23:00  ravim
  Support for statistics.

  Revision 1.5  1995/11/25 01:20:18  jussi
  This code now uses Transform matrix operations to convert user/world
  coordinates to screen pixel coordinates. This is to avoid any future
  inconsistencies in how the different code locations compute the
  conversion. xPerPixel and yPerPixel are now obsolete coefficients.

  Revision 1.4  1995/11/24 21:24:39  jussi
  Fixed inconsistencies in computing xPerPixel vs. scaling done by
  View.

  Revision 1.3  1995/11/24 16:10:40  jussi
  Added copyright notice and cleaned up the code.

  Revision 1.2  1995/09/05 22:16:04  jussi
  Added CVS header.
*/

#include <assert.h>
#include "Init.h"
#include "TDataViewX.h"
#include "TDataMap.h"
#include "ConnectorShape.h"

//#define DEBUG

TDataViewX::TDataViewX(char *name, 
		       VisualFilter &initFilter, QueryProc *qp, 
		       Color fg, Color bg,
		       AxisLabel *xAxis, AxisLabel *yAxis,
		       Action *action) :
	ViewGraph(name,initFilter, xAxis, yAxis, fg, bg, action)
{
  _dataBin = new GDataBin();
  _queryProc = qp;
  _map = NULL;
  _totalGData = _numBatches = 0;
  _batchRecs = Init::BatchRecs();

  _dispSymbols = true;
  _dispConnectors = false;
  _cMap = NULL;
}

void TDataViewX::InsertMapping(TDataMap *map)
{
  if (_map) {
    fprintf(stderr,"TDataViewX: can't handle > 1 mapping\n");
    return;
  }

  ViewGraph::InsertMapping(map);
  _map = map;
  
  Coord xMin;
  if (_queryProc->GetMinX(map, xMin))
    View::SetXMin(true, xMin);
  
  Refresh();
}

void TDataViewX::DerivedStartQuery(VisualFilter &filter, int timestamp)
{
#ifdef DEBUG
  printf("start query\n");
#endif

  if (_map == NULL) {
    printf("NULL map\n");
    ReportQueryDone(0);
    return;
  }
  
  // Init stats class
  _stats.Init(this);

  _queryFilter = filter;
  
  _queryProc->BatchQuery(_map, _queryFilter, this, NULL, timestamp);
}

void TDataViewX::DerivedAbortQuery()
{
  _queryProc->AbortQuery(_map, this);
  _dataBin->Final();
}

Boolean TDataViewX::DisplaySymbols(Boolean state)
{
  if (state == _dispSymbols)
    return state;

  Boolean oldState = _dispSymbols;
  _dispSymbols = state;

#ifdef DEBUG
  printf("DisplaySymbols now %s\n", (_dispSymbols ? "on" : "off"));
#endif

  InvalidatePixmaps();
  Refresh();

  return oldState;
}

Boolean TDataViewX::DisplayConnectors(Boolean state)
{
  if (state == _dispConnectors)
    return state;

  if (!state) {
    assert(_cMap);
    delete _cMap;
    _cMap = NULL;
  } else {
    assert(!_cMap);
    _cMap = new TDataCMap;
    assert(_cMap);
    _cMap->SetDefaultColor(GetFgColor());
  }

  Boolean oldState = _dispConnectors;
  _dispConnectors = state;

#ifdef DEBUG
  printf("DisplayConnectors now %s\n", (_dispConnectors ? "on" : "off"));
#endif

  InvalidatePixmaps();
  Refresh();

  return oldState;
}

/* Query data ready to be returned. Do initialization here.*/

void TDataViewX::QueryInit(void *userData)
{
  _dataBin->Init(_map, &_queryFilter, GetWindowRep()->TopTransform(),
		 _dispSymbols, _dispConnectors, _cMap, this);
}

void TDataViewX::ReturnGData(TDataMap *mapping, RecId recId,
			     void *gdata, int numGData)
{
  _totalGData += numGData;
  _numBatches++;
  int gRecSize = mapping->GDataRecordSize();

  // Update stats based on gdata
  char *tp = (char *)gdata;
  for(int tmp = 0; tmp < numGData; tmp++) {
    GDataBinRec *gt = (GDataBinRec *)tp;

    // eliminate records which won't appear on the screen
    //
    // for bar graphs, a vertical line is drawn from y = 0 to
    //   y = gt->y, so we should eliminate record if 0 > filter.yHigh
    //
    // for scatter plots, we should eliminate record if gt->y > filter.yHigh
    //
    // plot type is known only later (may even depend on a record field)
    // so the above elimination can't be done yet

    if (gt->x >= _queryFilter.xLow &&
	gt->x <= _queryFilter.xHigh &&
	gt->y >= _queryFilter.yLow)
      _stats.Sample(gt->x, gt->y);

    tp += gRecSize;
  }
  
  if (_batchRecs) {
    _dataBin->InsertSymbol(recId, gdata, numGData);
#ifdef DEBUG
    _dataBin->PrintStat();
#endif
  } else {
    char *ptr = (char *)gdata;
    for(int i = 0; i < numGData; i++) {
      _dataBin->InsertSymbol(recId, ptr, 1);
      recId++;
      ptr += gRecSize;
    }
  }
}

/* Done with query */

void TDataViewX::QueryDone(int bytes, void *userData)
{
  _stats.Done();
  _stats.Report();
  _dataBin->Final();
  ReportQueryDone(bytes);
}

void TDataViewX::ReturnGDataBinRecs(TDataMap *map, void **recs, int numRecs)
{
#ifdef DEBUG
  printf("TDataViewX %d recs buf start 0x%p\n", numRecs, recs);
#endif

  map->DrawGDataArray(GetWindowRep(), recs, numRecs);
}

void TDataViewX::ReturnGDataBinConnectors(TDataCMap *cmap,
					  Connector **connectors, int num)
{
#ifdef DEBUG
  printf("TDataViewX drawing %d connectors\n", num);
#endif

  for(int i = 0; i < num; i++)
    ConnectorShapeRegistrar::DrawConnection(GetWindowRep(), connectors[i]);
}

void TDataViewX::PrintStat()
{
  if (Init::PrintViewStat()) {
    View::PrintStat();
    printf("%d GData records, %d batches, %.2f per batch\n",
	   _totalGData, _numBatches, 1.0 * _totalGData / _numBatches);
    _dataBin->PrintStat();
  }
}
