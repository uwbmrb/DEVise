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
  Revision 1.2  1995/09/05 22:15:54  jussi
  Added CVS header.
*/

#include <stdio.h>
#if defined(SUN)||defined(PENTIUM)
#include <string.h>
#else
#include <strings.h>
#endif
#include "Config.h"
#include "Init.h"
#include "TDataMap.h"
#include "GData.h"
#include "GDataBin.h"
#include "Bitmap.h"
#include "TData.h"
#include "QueryProc.h"

/* counts how many TDataMaps have been created.
   Also used in creating the name of GData */
int TDataMap::_incarnation= 0; 

/* constructor */
TDataMap::TDataMap(char *name, TData *tdata, char *gdataName, 
		   int gdataRecSize,
		   VisualFlag dynamicArgs, int dynamicAttrs, int maxGDataPages,
		   VisualFlag *dimensionInfo, int numDimensions,
		   Boolean createGData)
{
  _incarnation++;

  _userData = NULL;

  _gdataAttrList = NULL;
  _createGData = createGData;
  
  _focusId = 0;
  _maxGDataPages = maxGDataPages;
  
#ifdef OLD_CODE
  /* should make it work even if NumPages in tdata > MAX_MAPPING_PAGES
     by checking for bounding box f those pages not in the bitmap */
  if (tdata->NumPages() > MAX_MAPPING_PAGES) {
    fprintf(stderr,"TDataMap can't handle tdata with %d pages, max = %d\n",
	    tdata->NumPages(), MAX_MAPPING_PAGES);
    Exit::DoExit(2);
  }
  
  _boundingBoxBitmap = new Bitmap(MAX_MAPPING_PAGES);
#endif
  
  /* set defaults */
  _dimensionInfo = dimensionInfo;
  _numDimensions = numDimensions;
  _mappingName = name;
  _pixelWidth = 1;
  _dynamicAttrs = dynamicAttrs;
  _dynamicArgs = dynamicArgs;
  _tdata = tdata;
  _gRecSize = gdataRecSize;
  
  _gdataName = gdataName;
  if (_gdataName == NULL)
    _gdataName = CreateGDataName(_tdata->GetName(), name);
  
  _gdataPath = CreateGDataPath(_gdataName);
  
  if (_createGData && _gRecSize < tdata->RecSize()) {
    _gdata = new GData(_tdata, _gdataPath, _gRecSize, 
		       maxGDataPages*DEVISE_PAGESIZE);
  } else {
    _gdata = NULL;
  }
  
  _x = 0.0; _y = 0.0; _color = BlackColor;
  _size = 1.0; _pattern = Pattern0; _orientation = 0.0;
  _shapeId = RectShapeID; 
  _numShapeAttr = MAX_MAPPING_SHAPE_ATTRS;
  _shapeAttrs = new Coord[MAX_MAPPING_SHAPE_ATTRS];
  for (int i=0; i < MAX_MAPPING_SHAPE_ATTRS; i++)
    _shapeAttrs[i] = 0.1;
  
  _boundWidth = 9.0; _boundHeight = 9.0;
  
  _hintInitialized = false;
}

void TDataMap::SetDimensionInfo(VisualFlag *dimensionInfo, int numDimensions)
{
  _dimensionInfo = dimensionInfo;
  _numDimensions = numDimensions;
}

/****************************************************************************
Map record to symbol by calling user defined Map() function.
Fill in the values for the symbol.  This is called by the query processor
****************************************************************************/

#ifdef TDATAMAP_MAP_TO_SYMBOL
void TDataMap::MapToSymbol(TData *tdata, RecId recId, void *rec, Symbol *sym)
{
  /* init default values */
  sym->recId = recId;
  sym->x = _x; sym->y = _y; sym->color = _color;
  sym->size = _size; sym->pattern = _pattern; 
  sym->orientation = _orientation; sym->shapeID = _shapeId;
  sym->numShapeAttr = _numShapeAttr;
  for(int i = 0; i < _numShapeAttr; i++)
    sym->shapeAttrs[i] = _shapeAttrs[i];
  
  /* call the user-defined mapping function */
  Map(tdata, recId, rec, sym);
  
  /*
     _sym->xLow = sym->x;
     _sym->yLow = sym->y;
     _sym->width = 0;
     _sym->height = 0;
  */

  /* find the bounding box for the symbol */
  ShapeRegistrar::SymbolBoundingBox(sym);
  
  /* update the maximum bounding box found so far */
  _deltaX = MinMax::max(sym->width, _deltaX);
  _deltaY = MinMax::max(sym->height, _deltaY);
}
#endif

/************************************************************************
Hint calculation
************************************************************************/
Boolean TDataMap::PageHint(TData *tdata, Coord x, Boolean isPrefetch,
			   RecId &hintId)
{
  return false;
#ifdef OLD_CODE
  if (!_hintInitialized || tdata != _hintTdata ||
      _numPages != tdata->NumPages() ) {
    /* initialize/reinit hint */
    
    _hintInitialized = false;	/* set to true later */
    _hintTdata = tdata;
    
    _numPages = tdata->NumPages();
    if (_numPages == 0)
      return false;
    
    /* get 1st page and last page and test */
    int numRecs; 
    RecId startRid;
    void **recs;
    tdata->GetPage(tdata->FirstPage(), numRecs, startRid,recs,isPrefetch);
    if (numRecs == 0) {
      tdata->FreePage(tdata->FirstPage(), Stay);
      return false;
    }
    ConvertToGData(recs,1, _tmpPtr);
    tdata->FreePage(tdata->FirstPage(), Stay);
    
    if (GetDynamicArgs() & VISUAL_X)
      _minX = ((GDataBinRec *)_tmpPtr[0])->x;
    else _minX = GetDefaultX();
    
    tdata->GetPage(tdata->LastPage(), numRecs, startRid, recs,isPrefetch);
    if (numRecs == 0) {
      tdata->FreePage(tdata->LastPage(), Stay);
      return false;
    }
    
    ConvertToGData(&recs[numRecs-1],1, _tmpPtr);
    tdata->FreePage(tdata->LastPage(), Stay);
    
    if (GetDynamicArgs() & VISUAL_X)
      _maxX = ((GDataBinRec *)_tmpPtr[0])->x;
    else
      _minX = GetDefaultX();
    
    _hintInitialized = true;
  }
  
  if ( x < _minX)
    pageNum = tdata->FirstPage();
  else if (x > _maxX)
    pageNum = tdata->LastPage();
  else {
    pageNum= ((int)((x-_minX)/(_maxX-_minX)*_numPages))+tdata->FirstPage();
    if (pageNum > tdata->LastPage())
      pageNum = tdata->LastPage();
  }
  
  return true;
#endif
}

/*******************************************************
Strip file name of preceding path name
*********************************************************/
static char *StripPath(char *name)
{
  char *last = strrchr(name,'/');
  if (last == NULL)
    return name;

  return (last+1);
}

/***********************************************************
Make a name for GData
************************************************************/
char *TDataMap::CreateGDataName(char *tdataName, char *mappingName)
{
  char *name;
  char *tname= StripPath(tdataName);
  name = new char[strlen(tname)+strlen(mappingName)+20];
  sprintf(name,"%s.%d.%s.G",tname, _incarnation,mappingName);
  return name;
}

/*********************************************************
Make a path for storing gdata
*********************************************************/
char *TDataMap::CreateGDataPath(char *gdataName)
{
  char *tmpDir = Init::TmpDir();
  char *name = new char[strlen(gdataName)+strlen(tmpDir)+2];
  sprintf(name,"%s/%s",tmpDir,gdataName);
  return name;
}

/* return the max bounding box found so far */
void TDataMap::MaxBoundingBox(Coord &width, Coord &height)
{
  /*
     printf("TDataMap::MaxBoundingBox\n");
  */
  width = _boundWidth; height = _boundHeight;
  /*
     _gdata->GetBoundingBox(width,height);
  */
}

void TDataMap::UpdateBoundingBox(Coord width, Coord height)
{
  _boundWidth = width;
  _boundHeight = height;
  /*
     _gdata->UpdateBoundingBox(width, height);
  */
}

int TDataMap::TDataRecordSize()
{
  return _tdata->RecSize();
}

/* Hint for current focus in GData */
void TDataMap::SetFocusId(RecId id) { _focusId = id; }
RecId TDataMap::GetFocusId() { return _focusId; }

void TDataMap::SetDefaultShapeAttr(int attrNum, Coord shapeAttr)
{
  if (attrNum < 0 || attrNum >= MAX_MAPPING_SHAPE_ATTRS) {
    fprintf(stderr,"Mapping::SetDefaultShapeAttr: attrNum %d\n",
	    attrNum);
    Exit::DoExit(1);
  }
  _shapeAttrs[attrNum] = shapeAttr;
}

void TDataMap::SetDefaultShape(ShapeID shapeID, int numAttr,
			       ShapeAttr *shapeAttr)
{
  if (numAttr > MAX_MAPPING_SHAPE_ATTRS) {
    fprintf(stderr,"Mapping::SetDefaultShape: too many attrs %d\n",
	    numAttr);
    Exit::DoExit(1);
  }
  
  _shapeId = shapeID;
  _numShapeAttr = numAttr;
  if (numAttr > 0) {
    for(int i=0; i < numAttr; i++)
      _shapeAttrs[i] = shapeAttr[i];
  }
}

void TDataMap::ResetGData(int gRecSize)
{
  if (_gdata != NULL) {
    QueryProc::Instance()->ClearGData(_gdata);
    delete _gdata;
    _gdata = NULL;
    _gRecSize = gRecSize;
    if (_createGData && _gRecSize < _tdata->RecSize()) {
      _gdata = new GData(_tdata, _gdataPath, _gRecSize,
			 _maxGDataPages*DEVISE_PAGESIZE);
      QueryProc::Instance()->ResetGData(_tdata,_gdata);
    }
  }
}
