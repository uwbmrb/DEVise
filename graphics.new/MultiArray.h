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
  Revision 1.4.14.1  2002/09/02 21:29:33  wenger
  Did a bunch of Purifying -- the biggest change is storing the command
  objects in a HashTable instead of an Htable -- the Htable does a bunch
  of ugly memory copying.

  Revision 1.4  1999/11/30 22:28:23  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.3  1995/12/28 21:18:51  jussi
  Small fixes to remove compiler warnings. Added copyright notice.

  Revision 1.2  1995/09/05 22:15:04  jussi
  Added CVS header.
*/

/* Multiple arrays of pointers to void */

#ifndef MultiArray_h
#define MultiArray_h

#include <stdio.h>
#include "DeviseTypes.h"
#include "VoidArray.h"
#include "Exit.h"
#include "DevError.h"

class MultiArray {
public:
  /* constructor */
  MultiArray(int numArrays, int arraySize);

  /* destructor */
  ~MultiArray();

  /* Clear so there is no element left */
  void Clear();

  /* Iterator */
  int InitIterator(int listNum) {
    CheckListNum(listNum);
    _arrays[listNum]->InitIterator();
    return 0;
  }
  Boolean MoreElements(int listNum) {
    return (_arrays[listNum]->More());
  }
  void *NextElement(int listNum) {
    return (_arrays[listNum]->Next());
  }

  /* indexing into the list */
  void *GetElement(int listNum, int pos) {
    CheckListNum(listNum);
    return _arrays[listNum]->Get(pos);
  }
  
  /* size of each array */
  int ArraySize(int arrayNum) {
    CheckListNum(arrayNum);
    return _arrays[arrayNum]->Size();
  }

  /* # of arrays */
  int NumArrays() { return _numArrays; }

  /* Move elements within lists */
  void Move(int fromList, int fromPos, int toList, int toPos) {
    CheckListNum(fromList);
    CheckListNum(toList);
    void *elem = _arrays[fromList]->Delete(fromPos);
    _arrays[toList]->Insert(elem,toPos);
  }

  /* Insert into a list */
  void Insert(int list, int pos, void *data) {
    CheckListNum(list);
    _arrays[list]->Insert(data, pos);
  }
  
  /* Delete from a list. return the deleted value.
     If pos == 0, make deletion act like a queue .
     If pos == ListSize -1, acts like a stack 
     If pos is somewhere in the middle, move the last element to
     cover its place.
     */
  void *Delete(int listNum, int pos) {
    CheckListNum(listNum);
    return _arrays[listNum]->Delete(pos);
  }
  
private:
  void CheckListNum(int listNum) {
    if (listNum < 0 || listNum >= _numArrays) {
      fprintf(stderr,"MultiArray : invalid list %d\n", listNum);
      reportErrNosys("Fatal error");//TEMP -- replace with better message
      Exit::DoExit(2);
    }
  }

  int _numArrays;
  int _maxSize;		/* max size of each array */
  VoidArray **_arrays;
};

#endif
