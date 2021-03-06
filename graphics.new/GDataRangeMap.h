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
  Revision 1.3  1996/01/13 21:27:22  jussi
  Added copyright notice and changed MAX_RANGE_REC_SIZE to use
  the MAX_GDATA_REC_SIZE value, not the GDataRec struct.

  Revision 1.2  1995/09/05 22:14:53  jussi
  Added CVS header.
*/

#ifndef GDataRangeMap_h
#define GDataRangeMap_h

#include <stdio.h>

#include "DeviseTypes.h"
#include "RecId.h"
#include "GDataRec.h"

const int MAX_RANGE_REC_SIZE = MAX_GDATA_REC_SIZE;

class GDataRangeMapRec {
  public:
    RecId tLow, tHigh;	                /* TData RecId ranges */
    RecId gLow, gHigh;	                /* GData internal RecId ranges */
    char firstRec[MAX_RANGE_REC_SIZE];
    char lastRec[MAX_RANGE_REC_SIZE];

  protected:
    friend class GDataRangeMap;
    struct GDataRangeMapRec *next, *prev;
};

class GDataRangeMap {
public:
    /* create range map with fname as the file to store the
       range map. trunc == true if we start with empty range */
    GDataRangeMap(int recSize, char *fname=NULL, Boolean trunc = false);
    ~GDataRangeMap();

    /*****************************************************************
      Find range map record with tLow <= tPage <= tHigh. 
      If no such record exists, find range map record whose TData page is
      the highest page number with tLow <= tPage .  (Greatest lower bound)
      Return NULL if no such record exists. 
    *******************************************************************/
    GDataRangeMapRec *FindMaxLower(RecId tId);

    /************************************************************************
      Find the range map record with tLow <= tPage <= tHigh. If
      no such record exists, find the range map record whose 
      TData page is the lowst such that tlow >= tPage.
      (Minimum Upper bound record). Return NULL if not found.
    *************************************************************************/
    GDataRangeMapRec *FindMinUpper(RecId tId);

    /* Find the range map record that contains gId,
       return NULL if not found.*/
    GDataRangeMapRec *FindGRange(RecId gId);

    /* find range map record with highest tdata RecId
       such that tHigh <= tId.
       Return NULL if no such record exists. 
       exit with error if tId overlaps with any range..*/
    GDataRangeMapRec *FindNoOverlap(RecId tId);

    /************************************************************
      Insert a new range.
      firstRec == first record in the tLow.
      lastRec == last record in tHigh.
      Use the following algorithm:
      1) Error:  if [tLow,tHigh] overlaps with existing range.
      2) Merge with existing range if:
        let e == existing range && tLow == e.tHigh+1 &&
        (gLow == e.gHigh || gLow == e.gHigh+1). This is extending the
        current range and should only be used to extend the beyond
        the end of GData file.
      3) Otherwise, create a new range.
      *********************************************************************/
    void InsertRange(RecId tLow, RecId tHigh, RecId gLow, RecId gHigh, 
                     void *firstRec, void *lastRec);

    /* Return next unprocessed t range >= tPage..
       Return true if opended range.*/
    Boolean NextUnprocessed(RecId tId, RecId &tLow, RecId &tHigh);
    
    /* print contents */
    void Print();
    
    /* Return next record in the list, or NULL if no more  */
    GDataRangeMapRec *NextRangeRec(GDataRangeMapRec *rec) {
        if (rec->next == &_head)
            return NULL;
        return rec->next;
    }
    
    /* get head of list */
    void InitListIterator() {
        _iteratorCurrent = _head.next;
    }
    GDataRangeMapRec *NextRec() {
        GDataRangeMapRec *rec;
        if (_iteratorCurrent != &_head) {
            rec = _iteratorCurrent;
            _iteratorCurrent = _iteratorCurrent->next;
            return rec;
        }
        return NULL;
    }

    /* Find the highest and lowest RecIds in the range.
       Return false none exists. */
    Boolean highID(RecId &id);
    Boolean lowID (RecId &id);

  private:
    /* Read all records from a file */
    void ReadRecords(char *fname);
    
    /* Write records to a file */
    void WriteRecords(char *fname);
    
    GDataRangeMapRec *_hint;
    GDataRangeMapRec _head;
    GDataRangeMapRec *_iteratorCurrent; /* for iterator */
    
    char *_fname;
    int _recSize;	                /* size of records */
};

#endif
