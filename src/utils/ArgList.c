/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1998
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  Implementation of ArgList class.
 */

/*
  $Id$

  $Log$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArgList.h"
#include "Util.h"
#include "DevError.h"

//#define DEBUG

/*------------------------------------------------------------------------------
 * function: ArgList::ArgList
 * Constructor.
 */
ArgList::ArgList(int size)
{
#if defined(DEBUG)
  printf("ArgList(0x%p)::ArgList(%d)\n", this, size);
#endif

  _argc = 0;

  _argv = new char *[size];
  if (_argv == NULL) {
    reportErrSys("Out of memory!!");
  } else {
    _argvSize = size;
    _objectValid.Set();
  }
}

/*------------------------------------------------------------------------------
 * function: ArgList::~ArgList
 * Destructor.
 */
ArgList::~ArgList(int size)
{
#if defined(DEBUG)
  printf("ArgList(0x%p)::~ArgList()\n", this);
#endif

  for (int index = 0; index < _argc; index++) {
    delete [] _argv[index];
    _argv[index] = NULL;
  }

  delete [] _argv;
  _argv = NULL;

  _argc = 0;
}

/*------------------------------------------------------------------------------
 * function: ArgList::AddArg
 * Add an argument to the list.
 */
DevStatus
ArgList::AddArg(const char *arg)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("ArgList(0x%p)::AddArg(%s)\n", this, arg);
#endif

  DOASSERT(_argc <= _argvSize, "Argument list overflow!!");

  DevStatus result = StatusOk;

  if (_argc == _argvSize) {
    result += Enlarge();
    if (!result.IsComplete()) {
      return result;
    }
  }

  _argv[_argc++] = CopyString(arg);

  return result;
}

static int
compare(char **arg1, char **arg2)
{
  return strcmp(*arg1, *arg2);
}

/*------------------------------------------------------------------------------
 * function: ArgList::Sort
 * Sort (alphabetically) the arguments within the given range.
 */
DevStatus
ArgList::Sort(int firstArg, int lastArg)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("ArgList(0x%p)::Sort(%d, %d)\n", this, firstArg, lastArg);
#endif

  DevStatus result = StatusOk;

  if (lastArg == 0) lastArg = _argc - 1;

  if (lastArg > firstArg) {
    qsort(&_argv[firstArg], lastArg - firstArg + 1, sizeof(_argv[0]), compare);
  }

  return result;
}

/*------------------------------------------------------------------------------
 * function: ArgList::Enlarge
 * Enlarge the argument vector.
 */
DevStatus
ArgList::Enlarge()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("ArgList(0x%p)::Enlarge()\n", this);
#endif

  DevStatus result = StatusOk;

  int newSize = _argvSize * 2;
  char **newArgv = new char *[newSize];
  if (newArgv == NULL) {
    reportErrSys("Out of memory!!");
    result = StatusFailed;
  } else {
    for (int index = 0; index < _argc; index++) {
      newArgv[index] = _argv[index];
    }

    delete [] _argv;
    _argv = newArgv;
    _argvSize = newSize;
  }

  return result;
}

/*============================================================================*/