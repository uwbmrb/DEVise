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
  Revision 1.4  1995/11/24 21:24:39  jussi
  Fixed inconsistencies in computing xPerPixel vs. scaling done by
  View.

  Revision 1.3  1995/11/24 16:10:40  jussi
  Added copyright notice and cleaned up the code.

  Revision 1.2  1995/09/05 22:16:04  jussi
  Added CVS header.
*/

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
  _cMap = NULL;
  _totalGData = _numBatches = 0;
  _batchRecs = Init::BatchRecs();
}

void TDataViewX::InsertMapping(TDataMap *map)
{
  if ( _map) {
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
  
  _queryFilter = filter;
  
  _queryProc->BatchQuery(_map, _queryFilter, this, NULL, timestamp);
}

void TDataViewX::DerivedAbortQuery()
{
  _queryProc->AbortQuery(_map, this);
  _dataBin->Final();
}

/* Query data ready to be returned. Do initialization here.*/

void TDataViewX::QueryInit(void *userData)
{
  _dataBin->Init(_map, &_queryFilter, GetWindowRep()->TopTransform(),
		 (_cMap != NULL? true : false), _cMap, this);
}

void TDataViewX::ReturnGData(TDataMap *mapping, RecId recId,
			     void *gdata, int numGData)
{
  _totalGData += numGData;
  _numBatches++;
  
  if (_batchRecs) {
    _dataBin->InsertSymbol(recId, gdata, numGData);
#ifdef DEBUG
    _dataBin->PrintStat();
#endif
  } else {
    int gRecSize = mapping->GDataRecordSize();
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
  _dataBin->Final();
  ReportQueryDone(bytes);
}

void TDataViewX::ReturnGDataBinRecs(TDataMap *map, void **recs, int numRecs)
{
#ifdef DEBUG
  printf("TDataViewX %d recs buf start 0x%x\n", numRecs, recs);
#endif

  map->DrawGDataArray(GetWindowRep(), recs, numRecs);
}

void TDataViewX::ReturnGDataBinConnectors(TDataCMap *cmap,
					  Connector **connectors, int num)
{
  WindowRep *winRep = GetWindowRep();
  for(int i = 0; i < num; i++)
    ConnectorShapeRegistrar::DrawConnection(winRep, connectors[i]);
}

void TDataViewX::PrintStat()
{
  if (Init::PrintViewStat()) {
    View::PrintStat();
    printf("%d GData records, %d batches, %d per batch\n",
	   _totalGData, _numBatches, _totalGData/_numBatches);
    _dataBin->PrintStat();
  }
}
