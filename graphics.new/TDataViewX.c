/*
  $Id$

  $Log$*/

#include "Init.h"
#include "TDataViewX.h"
#include "TDataMap.h"
#include "ConnectorShape.h"

TDataViewX::TDataViewX(char *name, 
	VisualFilter &initFilter, QueryProc *qp, 
	Color fg, Color bg,
	AxisLabel *xAxis, AxisLabel *yAxis,
	Action *action):
	ViewGraph(name,initFilter, xAxis, yAxis, fg, bg, action){
	_dataBin = new GDataBin();
	_queryProc = qp;
	_map = NULL;
	_cMap = NULL;
	_totalGData = _numBatches = 0;
	_batchRecs = Init::BatchRecs();
}

void TDataViewX::InsertMapping(TDataMap *map){
	if ( _map != NULL){
		fprintf(stderr,"TDataViewX: can't handle > 1 mapping\n");
		return;
	}
	ViewGraph::InsertMapping(map);
	_map = map;

	Coord xMin;
	if (_queryProc->GetMinX(map,xMin)){
		View::SetXMin(true,xMin);
	}

	Refresh();
}

void TDataViewX::DerivedStartQuery(VisualFilter &filter, int timestamp){
/*
printf("start query\n");
*/
	if (_map == NULL){
		printf("NULL map\n");
		ReportQueryDone(0);
		return;
	}

	_queryFilter = filter;

	/* find amount of X and Y per pixel */
	int scrnX,scrnY; unsigned int scrnWidth, scrnHeight;
	VisualFilter filter;
	GetVisualFilter(filter);
	Geometry(scrnX,scrnY,scrnWidth,scrnHeight);
	_xPerPixel = (filter.xHigh-filter.xLow+1)/scrnWidth;
	_yPerPixel= (filter.yHigh-filter.yLow+1)/scrnHeight;

	_queryProc->BatchQuery(_map,_queryFilter,this,NULL, timestamp);
}

void TDataViewX::DerivedAbortQuery(){
	_queryProc->AbortQuery(_map, this);
	_dataBin->Final();
}

/* Query data ready to be returned. Do initialization here.*/
void TDataViewX::QueryInit(void *userData){
    _dataBin->Init(_map, _queryFilter.yLow, _queryFilter.yHigh, 
		_queryFilter.xLow, _queryFilter.xHigh,
		_yPerPixel, _xPerPixel, (_cMap != NULL? true: false), _cMap,this);
}

void TDataViewX::ReturnGData(TDataMap *mapping, RecId recId,
	void *gdata, int numGData){
	_totalGData += numGData;
	_numBatches++;

	if (_batchRecs){
		_dataBin->InsertSymbol(recId, gdata, numGData);
	} else {
		int gRecSize = mapping->GDataRecordSize();
		char *ptr = (char *)gdata;
		int i;
		for (i=0; i < numGData; i++){
			_dataBin->InsertSymbol(recId, ptr , 1);
			recId++;
			ptr += gRecSize;
		}
	}
}

/* Done with query */
void TDataViewX::QueryDone(int bytes, void *userData){
	_dataBin->Final();
	ReportQueryDone(bytes);
}

void TDataViewX::ReturnGDataBinRecs(TDataMap *map, void **recs, int numRecs){
	map->DrawGDataArray(GetWindowRep(),recs,numRecs, _xPerPixel, _yPerPixel);
}

void TDataViewX::ReturnGDataBinConnectors(TDataCMap *cmap,
			Connector **connectors, int num){
	int i;
	WindowRep *winRep = GetWindowRep();
	for (i=0; i < num; i++)
		ConnectorShapeRegistrar::DrawConnection(winRep, connectors[i]);
}


void TDataViewX::PrintStat(){
	if (Init::PrintViewStat()){
		View::PrintStat();
		printf("%d GData records, %d batches, %d per batch\n",
			_totalGData, _numBatches, _totalGData/_numBatches);
		_dataBin->PrintStat();
	}
}
