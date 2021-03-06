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
  Revision 1.3.46.1  2002/09/02 21:29:33  wenger
  Did a bunch of Purifying -- the biggest change is storing the command
  objects in a HashTable instead of an Htable -- the Htable does a bunch
  of ugly memory copying.

  Revision 1.3  1996/11/23 21:20:58  jussi
  Simplified code.

  Revision 1.2  1995/09/05 22:15:25  jussi
  Added CVS header.
*/

#ifndef RangeInfoArray_h
#define RangeInfoArray_h

#include "DeviseTypes.h"

class RangeInfo;
class MultiArray;

class RangeInfoArrays {
  public:
    /* constructor */
    RangeInfoArrays(int numArrays, int maxSize);

    /* destructor */
    ~RangeInfoArrays();

    /* Clear the arrays so that contain nothing.
       DO NOT delete the RangeInfo */
    void Clear();
    
    /* Return # of arrays */
    int NumArrays();

    /* size of each array */
    int Size(int arrayNum);

    /* iterator for an array */
    void InitIterator(int arrayNum);
    Boolean More(int arrayNum);
    RangeInfo *Next(int arrayNum);

    /* indexing */
    RangeInfo *GetRange(int arrayNum, int pos);

    /* moving elements */
    void Move(int fromArray, int fromPos, int toArray, int toPos);

    /* print statistics */
    void PrintStat();

protected:
    friend class BufMgrFull;

    /* insertion */
    void Insert(int arrayNum, int pos, RangeInfo *rangeInfo);

    /* delete and return the element */
    RangeInfo *Delete(int arrayNum, int pos);

private:
    MultiArray *_arrays;
    int _curBuf;		/* # of bytes for buffer */
    int _curData;		/* # of bytes in buffer containing data */
    int _maxBuf;		/* max buffer size */
    int _maxData;		/* max data */
    int _minBuf;		/* minimum buffer */
    int _minData;		/* minimum data */
    
    int _numInsert;		/* # of times inisert called */
    int _numDelete;		/* # of times deleted called */
    double _totalBuf;		/* for calculating average size of each 
                                   buffer inserted */
    double _totalData;		/* for average size of each data insert */
    double _totalBufInUse;	/* for average size of buffer space in use */
    double _totalDataInUse;	/* for average size of data in use */
};

#endif
