/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2000
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
  Revision 1.5  1999/11/30 22:28:05  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.4  1997/01/18 18:34:02  jussi
  Added missing stdio.h to inclusion list.

  Revision 1.3  1996/01/11 21:46:59  jussi
  Replaced libc.h with stdlib.h. Added copyright notice.

  Revision 1.2  1995/09/05 21:13:04  jussi
  Added/update CVS header.
*/

#ifndef StringArray_h
#define StringArray_h

#include <stdio.h>
#include <stdlib.h>

#include "DevError.h"

unsigned const int StringArrayIncrement = 20;

class StringArray {
public:
  StringArray() {
    _numStrings = 0;
    _arraySize = 20;
    _array = new char *[20];
  }

  /* append a string */
  void Append(char *string) {
    if (_numStrings == _arraySize) {
      char **temp = new char *[_arraySize + StringArrayIncrement];
      for(int i=0; i < _numStrings; i++) {
	temp[i] = _array[i];
      }
      delete _array;
      _array = temp;
    }
    _array[_numStrings++] = string;
  }

  /* delete a string */
  void Delete(int index) {
    if (index < 0 || index >= _numStrings) {
      fprintf(stderr,"StringArray:Delete invalid index %d\n",index);
      reportErrNosys("Fatal error");//TEMP -- replace with better message
      exit(2);
    }
    /* move rest of the array up.*/
    if (index < _numStrings - 1) {
      for(int i = index+1; i < _numStrings-1; i++)
	_array[i] = _array[i+1];
    }
    _numStrings--;
  }

  /* find 1st index of a string, or -1 if not found  */
  int Find(char *string) {
    for(int i = 0; i < _numStrings; i++)
      if (!strcmp(string, _array[i]))
	return i;
    return -1;
  }
  
  void Get(char **&strings, int &num) {
    strings = _array; 
    num = _numStrings;
  }
  
private:
  int _numStrings;
  int _arraySize;
  char **_array;
};
#endif
