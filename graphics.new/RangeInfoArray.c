/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2002
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
  Revision 1.4.46.2  2002/09/04 13:58:01  wenger
  More Purifying -- fixed some leaks and mismatched frees.

  Revision 1.4.46.1  2002/09/02 21:29:33  wenger
  Did a bunch of Purifying -- the biggest change is storing the command
  objects in a HashTable instead of an Htable -- the Htable does a bunch
  of ugly memory copying.

  Revision 1.4  1996/11/23 21:20:58  jussi
  Simplified code.

  Revision 1.3  1995/12/28 21:18:57  jussi
  Small fixes to remove compiler warnings. Added copyright notice.

  Revision 1.2  1995/09/05 22:15:24  jussi
  Added CVS header.
*/

#include "RangeInfoArray.h"
#include "MultiArray.h"
#include "RangeInfo.h"

#define DEBUG 0

RangeInfoArrays::RangeInfoArrays(int numArrays, int maxSize)
{
#if (DEBUG >= 1)
    printf("RangeInfoArrays::RangeInfoArrays(%d, %d)\n", numArrays, maxSize);
#endif

    _arrays = new MultiArray(numArrays, maxSize);
    _numInsert = _numDelete = _curBuf = _curData = 0;
    _totalBuf = _totalData = 0.0;
    _totalBufInUse = _totalDataInUse = 0.0;
    _maxBuf = _maxData = 0;
    _minBuf = _minData = 1024000;
}

RangeInfoArrays::~RangeInfoArrays()
{
#if (DEBUG >= 1)
    printf("RangeInfoArrays::~RangeInfoArrays()\n");
#endif

    delete _arrays;
}

/* Return # of arrays */

int RangeInfoArrays::NumArrays()
{
    return _arrays->NumArrays();
}

/* size of each array */

int RangeInfoArrays::Size(int arrayNum)
{
    return _arrays->ArraySize(arrayNum);
}

/* iterator for an array */

void RangeInfoArrays::InitIterator(int arrayNum)
{
    _arrays->InitIterator(arrayNum);
}

Boolean RangeInfoArrays::More(int arrayNum)
{
    return _arrays->MoreElements(arrayNum);
}

RangeInfo *RangeInfoArrays::Next(int arrayNum)
{
    return (RangeInfo *)_arrays->NextElement(arrayNum);
}

/* indexing */

RangeInfo *RangeInfoArrays::GetRange(int arrayNum, int pos)
{
    return (RangeInfo *)_arrays->GetElement(arrayNum, pos);
}

/* moving elements */

void RangeInfoArrays::Move(int fromArray, int fromPos, int toArray, int toPos)
{
    _arrays->Move(fromArray,fromPos, toArray, toPos);
}

/* Insertion */

void RangeInfoArrays::Insert(int arrayNum, int pos, RangeInfo *data)
{
#if (DEBUG >= 1)
    printf("RangeInfoArrays::Insert(%d, %d, %p)\n", arrayNum, pos, data);
#endif

    _arrays->Insert(arrayNum, pos, data);
    int bufSize = data->BufSize();
    int dataSize = data->DataSize();
    _curBuf += bufSize;
    _curData += dataSize;
    
    if (bufSize > _maxBuf)
        _maxBuf = bufSize;
    if (dataSize > _maxData)
        _maxData = dataSize;
    if (bufSize < _minBuf)
        _minBuf = bufSize;
    if (dataSize < _minData)
        _minData = dataSize;
    
    _numInsert++;
    _totalBuf += bufSize;
    _totalData += dataSize;
    _totalBufInUse += _curBuf;
    _totalDataInUse += _curData;
}

RangeInfo *RangeInfoArrays::Delete(int arrayNum, int pos)
{
#if (DEBUG >= 1)
    printf("RangeInfoArrays::Delete(%d, %d)\n", arrayNum, pos);
#endif

    RangeInfo *info = (RangeInfo *)_arrays->Delete(arrayNum, pos);
    _numDelete++;
    _curBuf -= info->BufSize();
    _curData -= info->DataSize();
    
    _totalBufInUse += _curBuf;
    _totalDataInUse += _curData;
    
    return 0;
}

void RangeInfoArrays::PrintStat()
{
    int numUpdate = _numInsert + _numDelete;
    if (numUpdate == 0){
        printf("Buffer: not yet used\n");
    } else {
        printf("min buffer: %d, max buffer: %d\n", _minBuf, _maxBuf);
        printf("min data: %d, max data: %d\n", _minData, _maxData);
        printf("average buffer %f, average data %f\n",
               _totalBuf/(double)_numInsert, _totalData/(double)_numInsert);
        printf("average in use buffer %f, data %f\n",
               _totalBufInUse/(double)numUpdate,
               _totalDataInUse/(double)numUpdate);
    }
}

/* Clear the arrays so that contain nothing. DO NOT delete the RangeInfo. */

void RangeInfoArrays::Clear()
{
#if (DEBUG >= 1)
    printf("RangeInfoArrays::Clear()\n");
#endif

    _arrays->Clear();
}

