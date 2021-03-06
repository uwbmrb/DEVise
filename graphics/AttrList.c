/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2013
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
  Revision 1.26  2013/02/08 23:09:36  wenger
  Changed a bunch more sprintfs to snprintfs; fixed errors in the
  error return in JavaScreenCmd; added provision for other parts of
  the DEVise code to "register" errors in JavaScreenCmd (if they can't
  return an error code up the call stack) -- MappingInterp now uses
  this functionality.  Working on sprintf->snprintf conversion in
  GDataSock (not finished).

  Revision 1.25  2008/10/13 19:45:15  wenger
  More const-ifying, especially Control- and csgroup-related.

  Revision 1.24  2003/01/13 19:25:09  wenger
  Merged V1_7b0_br_3 thru V1_7b0_br_4 to trunk.

  Revision 1.23.10.2  2002/09/21 23:24:28  wenger
  Fixed a few more special-case memory leaks.

  Revision 1.23.10.1  2002/09/17 23:34:11  wenger
  Fixed a bunch of memory leaks -- especially in DevError::ReportError()!

  Revision 1.23  2001/04/03 19:57:28  wenger
  Cleaned up code dealing with GData attributes in preparation for
  "external process" implementation.

  Revision 1.22  2000/03/14 17:05:04  wenger
  Fixed bug 569 (group/ungroup causes crash); added more memory checking,
  including new FreeString() function.

  Revision 1.21  2000/01/13 23:06:50  wenger
  Got DEVise to compile with new (much fussier) compiler (g++ 2.95.2).

  Revision 1.20  1999/11/30 22:28:00  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.19  1999/06/30 17:38:26  wenger
  Data color of parent view's mapping (if specified) now controls the
  background color of view symbols; defined constant strings for GData
  attribute values to avoid potential problems.

  Revision 1.18  1998/11/25 22:31:00  wenger
  Reduced the amount of memory allocated in the MappingInterp constructor,
  mainly by improving the AttrList class.

  Revision 1.17  1998/10/13 19:40:35  wenger
  Added SetAttrs() function to TData and its subclasses to allow Liping to
  push projection down to the DTE.

  Revision 1.16  1997/05/28 20:01:41  andyt
  Shape attributes for 'Tcl/Tk Window' shape can now be variables, numeric
  constants, or string constants. Used to assume that all attributes except
  argc were strings.

  Revision 1.15  1997/05/03 19:53:42  wenger
  Fixed bug in AttrList class that caused Devise to crash on mappings
  that use recId; commented out debug code in UnixRecFile.c..

  Revision 1.14  1997/04/25 23:15:48  ssl
  turned off debug code.

  Revision 1.12  1997/03/11 22:49:46  donjerko
  *** empty log message ***

  Revision 1.11  1997/03/07 17:41:40  donjerko
  Added method Clear() that resets attrList to empty.

  Revision 1.10  1996/09/27 15:52:33  wenger
  Fixed a number of memory leaks.

  Revision 1.9  1996/07/23 20:12:39  wenger
  Preliminary version of code to save TData (schema(s) and data) to a file.

  Revision 1.8  1996/05/07 16:14:19  jussi
  Added copy constructor and GetVal() method.

  Revision 1.7  1996/01/10 00:38:16  jussi
  Minor changes.

  Revision 1.6  1995/12/20 07:04:08  ravim
  High and low values of attrs can be specified.

  Revision 1.5  1995/12/13 18:42:43  jussi
  Now iterator works even if attribute list has holes i.e. list is
  non-contiguous.

  Revision 1.4  1995/11/21 21:10:43  jussi
  Added copyright notice and cleaned up a bit.

  Revision 1.3  1995/09/05 21:12:22  jussi
  Added/updated CVS header.

  Revision 1.2  1995/09/05 20:39:21  jussi
  Added CVS header.
*/

#include <stdio.h>
#include <unistd.h>

#include "AttrList.h"
#include "Util.h"
#include "DevError.h"
#include "GDataRec.h"
#include "DList.h"

#define DEBUG 0

DefinePtrDList(AttrListList, AttrList *);
static AttrListList _lists;

static const char *GetTypeString(AttrType type);
static void WriteVal(int fd, AttrVal *aval, AttrType atype);

AttrList::AttrList(const char *name, int startSize)
{
#if (DEBUG >= 1)
  printf("AttrList::AttrList(%s, %d)\n", name, startSize);
#endif

  startSize = MAX(startSize, MIN_ATTRLIST_SIZE);
  _attrs = new AttrInfo *[startSize];
  DOASSERT(_attrs, "Out of memory");
  _arraySize = startSize;

  for(int i = 0; i < _arraySize; i++)
    _attrs[i] = NULL;
  _size = 0;
  _name = CopyString(name);

  _lists.Insert(this);
}

void AttrList::Clear(){
#if (DEBUG >= 1)
  printf("AttrList(%s)::Clear()\n", _name);
#endif

  for(int i = 0; i < _arraySize; i++){
    if (_attrs[i] != NULL) {
#if (DEBUG >= 2)
      printf("  Freeing %s\n", _attrs[i]->name);
#endif
	  FreeString(_attrs[i]->name);
      delete _attrs[i];
      _attrs[i] = NULL;
    }
  }
  _size = 0;
}

AttrList::~AttrList()
{
#if (DEBUG >= 1)
  printf("AttrList(%s)::~AttrList()\n", _name);
#endif

  Clear();
  delete [] _attrs;
  _attrs = NULL;
  FreeString(const_cast<char *>(_name));

  _lists.Delete(this);
}

/* Copy constructor */
AttrList::AttrList(AttrList &attrs)
{
#if (DEBUG >= 1)
  printf("AttrList()::AttrList(copy %s)\n", attrs.GetName());
#endif

  _attrs = new AttrInfo *[attrs.NumAttrs()];
  DOASSERT(_attrs, "Out of memory");
  _arraySize = attrs.NumAttrs();

  for(int i = 0; i < _arraySize; i++) {
    _attrs[i] = NULL;
  }
  _size = 0;
  _name = CopyString(attrs.GetName());

  /* copy attributes from attrs to this list */

  attrs.InitIterator();
  while(attrs.More()) {
    AttrInfo *info = attrs.Next();
    InsertAttr(info->attrNum, info->name, info->offset,
	       info->length, info->type, info->hasMatchVal,
	       &info->matchVal, info->isComposite, info->isSorted,
	       info->hasHiVal, &info->hiVal, info->hasLoVal,
	       &info->loVal);
  }
  attrs.DoneIterator();

  _lists.Insert(this);
}

void
AttrList::DestroyAllInstances()
{
    while (_lists.Size() > 0) {
        AttrList *list = _lists.GetFirst();
	delete list;
    }
}

Boolean
AttrList::SetAttrs(const AttrList &newAttrs)
{
  Clear();

  // Bypass interator to preserve 'const' on newAttrs.
  int index = 0;
  while(index < newAttrs._size) {
    AttrInfo *info = newAttrs._attrs[index];
    InsertAttr(info->attrNum, info->name, info->offset,
	       info->length, info->type, info->hasMatchVal,
	       &info->matchVal, info->isComposite, info->isSorted,
	       info->hasHiVal, &info->hiVal, info->hasLoVal,
	       &info->loVal);
    index++;
  }

  return true;
}

/* Insert attribute into list of attributes */
void AttrList::InsertAttr(int attrNum, const char *name, int offset, int length,
			  AttrType type, Boolean hasMatchVal,
			  AttrVal *matchVal, Boolean isComposite,
			  Boolean isSorted, Boolean hasHiVal, AttrVal *hiVal,
			  Boolean hasLoVal, AttrVal *loVal)
{
  if (attrNum < 0) {
    fprintf(stderr,"AttrList::InsertAttr: invalid attrNum %d\n", attrNum);
    reportErrNosys("Fatal error");//TEMP -- replace with better message
    Exit::DoExit(1);
  }

  if (attrNum >= _arraySize) {
    EnlargeArray();
  }

  if (_attrs[attrNum] != NULL) {
    fprintf(stderr,"AttrList::InsertAttr: attrNum %d already exists\n",
	    attrNum);
    reportErrNosys("Fatal error");//TEMP -- replace with better message
    Exit::DoExit(1);
  }

  AttrInfo *info = new AttrInfo;
  info->attrNum = attrNum;
  info->name = CopyString(name);
  info->offset = offset;
  info->length = length;
  info->type = type;
  info->hasMatchVal = hasMatchVal;
  if (hasMatchVal) {
    info->matchVal = *matchVal;
  }
  info->isComposite = isComposite;
  info->isSorted = isSorted;
  info->hasHiVal = hasHiVal;
  if (hasHiVal) {
    info->hiVal = *hiVal;
  }
  info->hasLoVal = hasLoVal;
  if (hasLoVal) {
    info->loVal = *loVal;
  }
  
  if (_size < attrNum+1) {
    _size = attrNum+1;
  }
  _attrs[attrNum] = info;
}

void AttrList::InitIterator()
{
  _index = 0;
}

Boolean AttrList::More()
{
  return (_index < _size);
}

AttrInfo *AttrList::Next()
{
  AttrInfo *info;

  do {
    info = _attrs[_index];
    _index++;
  } while (!info && _index < _size);

  return info;
}

void AttrList::DoneIterator()
{
}

AttrInfo *AttrList::Find(const char *name)
{
  for(int index = 0; index < _size; index++) {
    AttrInfo *info = _attrs[index];
    if (info && !strcmp(info->name, name))
      return info;
  }
  return NULL;
}

AttrInfo *AttrList::FindShapeAttr(int i)
{
    char attrName[40];
    int formatted = snprintf(attrName, sizeof(attrName), "%s%d",
      gdataShapeAttrName, i);
    checkAndTermBuf2(attrName, formatted);
    return Find(attrName);
}

int AttrList::GetAttrNum(char *name)
{
  for(int index = 0; index < _size; index++) {
    AttrInfo *info = _attrs[index];
    if (info && !strcmp(info->name, name))
      return index;
  }
  return -1;
}


AttrInfo *AttrList::Get(int n)
{
  if (n >= 0  && n < _size) {
    return _attrs[n];
  } else {
    /* Note: -1 is used to mean recId. */
    if (n != -1
#if (DEBUG >= 1)
      || true
#endif
    )
    {
      char errBuf[256];
      int formatted = snprintf(errBuf, sizeof(errBuf),
        "Attribute %d does not exist", n);
      checkAndTermBuf2(errBuf, formatted);
      reportErrNosys(errBuf);
    }
    return NULL;
  }
}


double AttrList::GetVal(const AttrVal *aval, AttrType atype)
{
  switch(atype) {
    case IntAttr:
      return aval->intVal;
    case FloatAttr:
      return aval->floatVal;
      break;
    case DoubleAttr:
      return aval->doubleVal;
    case StringAttr:
      DOASSERT(0, "Cannot get value of string attribute");
      break;
    case DateAttr:
      return aval->dateVal;
    default:
      DOASSERT(0, "Unknown attribute type");
      break;
  }

  /* make compiler happy */
  return -1;
}

void AttrList::Print()
{
  printf("AttrList:\n");
  for (InitIterator(); More(); ){
    AttrInfo *info = Next();
    PrintAttr(info);
  }

  DoneIterator();
}

void AttrList::PrintAttr(const AttrInfo *info)
{
  printf("  name %s, num %d, offset %d, length %d, composite %d, ",
      info->name, info->attrNum, info->offset, info->length,
      (info->isComposite? 1 : 0));
  printf("%s", GetTypeString(info->type));
  if (info->hasHiVal) {
    printf(", hi ");
    PrintVal(&(info->hiVal), info->type);
  }
  if (info->hasLoVal) {
    printf(", lo ");
    PrintVal(&(info->loVal), info->type);
  }
  printf("\n");
}

void AttrList::Write(int fd)
{
  for (InitIterator(); More(); )
  {
    AttrInfo *infoP = Next();

    const char *string;

    // Sorted?
    if (infoP->isSorted)
    {
      string = "sorted ";
      write (fd, string, strlen(string));
    }

    // Composite or normal attribute?
    if (infoP->isComposite)
    {
      string = "compattr ";
    }
    else
    {
      string = "attr ";
    }
    write (fd, string, strlen(string));

    // Name.
    write (fd, infoP->name, strlen(infoP->name));
    write (fd, " ", 1);

    // Type.
    string = GetTypeString(infoP->type);
    write (fd, string, strlen(string));
    write (fd, " ", 1);

    // Length.
    if (infoP->type == StringAttr)
    {
      char buf[100];
      int formatted = snprintf(buf, sizeof(buf), "%d ", infoP->length);
      checkAndTermBuf2(buf, formatted);
      write (fd, buf, strlen(buf));
    }

    // Match value.  TEMP -- before or after length??
    if (infoP->hasMatchVal)
    {
      string = "= ";
      write (fd, string, strlen(string));

      WriteVal(fd, &infoP->matchVal, infoP->type);
    }

    // Hi.
    if (infoP->hasHiVal)
    {
      string = "hi ";
      write (fd, string, strlen(string));

      WriteVal(fd, &infoP->hiVal, infoP->type);
    }

    // Lo.
    if (infoP->hasLoVal)
    {
      string = "lo ";
      write (fd, string, strlen(string));

      WriteVal(fd, &infoP->loVal, infoP->type);
    }

    write (fd, "\n", 1);
  }

  DoneIterator();
}

void AttrList::PrintVal(const AttrVal *aval, AttrType atype)
{
  switch(atype) {
    case IntAttr:
      printf(" %d ", aval->intVal);
      break;
    case FloatAttr:
      printf(" %f ", aval->floatVal);
      break;
    case DoubleAttr:
      printf(" %f ", aval->doubleVal);
      break;
    case StringAttr:
      printf(" %s ", aval->strVal);
      break;
    case DateAttr:
      printf(" %ld ", static_cast<long>(aval->dateVal));
      break;
    default:
      break;
  }
}

void
AttrList::EnlargeArray()
{
  int newArraySize = _arraySize * 2;
  AttrInfo **newAttrs = new AttrInfo *[newArraySize];
  DOASSERT(newAttrs, "Out of memory");

  int index;
  for (index = 0; index < _size; index++) {
    newAttrs[index] = _attrs[index];
    _attrs[index] = NULL;
  }
  for (index = _size; index < newArraySize; index++) {
    newAttrs[index] = NULL;
  }

  delete [] _attrs;

  _attrs = newAttrs;
  _arraySize = newArraySize;
}

static const char *
GetTypeString(AttrType type)
{
  switch(type)
  {
  case IntAttr:
    return "int";
    break;

  case FloatAttr:
    return "float";
    break;

  case DoubleAttr:
    return "double";
    break;

  case StringAttr:
    return "string";
    break;

  case DateAttr:
    return "date";
    break;

  default:
    DOASSERT(0, "Unknown attribute type");
    return ""; // So compiler is happy.
    break;
  }
}

static void
WriteVal(int fd, AttrVal *aval, AttrType atype)
{
  char buf[100];

  int formatted;
  switch(atype)
  {
  case IntAttr:
    formatted = snprintf(buf, sizeof(buf), "%d ", aval->intVal);
    checkAndTermBuf2(buf, formatted);
    break;

  case FloatAttr:
    formatted = snprintf(buf, sizeof(buf), "%f ", aval->floatVal);
    checkAndTermBuf2(buf, formatted);
    break;

  case DoubleAttr:
    formatted = snprintf(buf, sizeof(buf), "%f ", aval->doubleVal);
    checkAndTermBuf2(buf, formatted);
    break;

  case StringAttr:
    formatted = snprintf(buf, sizeof(buf), "%s ", aval->strVal);
    checkAndTermBuf2(buf, formatted);
    break;

  case DateAttr:
    formatted = snprintf(buf, sizeof(buf), "%ld ", static_cast<long>(aval->dateVal));//TEMP?
    checkAndTermBuf2(buf, formatted);
    break;

  default:
    DOASSERT(0, "Unknown attribute type");
    break;
  }

  write (fd, buf, strlen(buf));

  return;
}
