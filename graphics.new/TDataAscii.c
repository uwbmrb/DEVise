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
  Revision 1.41  1996/10/04 17:24:16  wenger
  Moved handling of indices from TDataAscii and TDataBinary to new
  FileIndex class.

  Revision 1.40  1996/10/02 15:23:50  wenger
  Improved error handling (modified a number of places in the code to use
  the DevError class).

  Revision 1.39  1996/08/27 19:03:26  flisakow
    Added ifdef's around some informational printf's.

  Revision 1.38  1996/08/04 21:59:53  beyer
  Added UpdateLinks that allow one view to be told to update by another view.
  Changed TData so that all TData's have a DataSource (for UpdateLinks).
  Changed all of the subclasses of TData to conform.
  A RecFile is now a DataSource.
  Changed the stats buffers in ViewGraph to be DataSources.

  Revision 1.37  1996/07/13 01:32:33  jussi
  Moved initialization of i to make older compilers happy.

  Revision 1.36  1996/07/13 00:22:39  jussi
  Fixed bug in Initialize().

  Revision 1.35  1996/07/12 23:42:51  jussi
  Derived data sources are compiled in only for non-ATTRPROJ executables.

  Revision 1.34  1996/07/12 21:54:00  jussi
  Buffer data sources are not checkpointed.

  Revision 1.33  1996/07/12 19:36:08  jussi
  Modified code to handle derived data sources whose data is
  in a buffer but whose 'type' is one of many possible derived
  data types.

  Revision 1.32  1996/07/12 18:24:52  wenger
  Fixed bugs with handling file headers in schemas; added DataSourceBuf
  to TDataAscii.

  Revision 1.31  1996/07/05 15:20:01  jussi
  Data source object is only deleted in the destructor. The dispatcher
  now properly destroys all TData objects when it shuts down.

  Revision 1.30  1996/07/03 23:13:55  jussi
  Added call to _data->Close() in destructor. Renamed
  _fileOkay to _fileOpen which is more accurate.

  Revision 1.29  1996/07/02 22:48:33  jussi
  Removed unnecessary dispatcher call.

  Revision 1.28  1996/07/01 20:23:15  jussi
  Added #ifdef conditionals to exclude the Web data source from
  being compiled into the Attribute Projection executable.

  Revision 1.27  1996/07/01 19:28:05  jussi
  Added support for typed data sources (WWW and UNIXFILE). Renamed
  'cache' references to 'index' (cache file is really an index).
  Added support for asynchronous interface to data sources.

  Revision 1.26  1996/06/27 18:12:37  wenger
  Re-integrated most of the attribute projection code (most importantly,
  all of the TData code) into the main code base (reduced the number of
  modules used only in attribute projection).

  Revision 1.25  1996/06/27 15:49:31  jussi
  TDataAscii and TDataBinary now recognize when a file has been deleted,
  shrunk, or has increased in size. The query processor is asked to
  re-issue relevant queries when such events occur.

  Revision 1.24  1996/06/24 19:45:42  jussi
  TDataAscii no longer passes the fd of the open file to the
  Dispatcher. TDataAscii only needs the Dispatcher to call
  it when it's time to shut down; Cleanup() -> Checkpoint()
  functions get called at that time.

  Revision 1.23  1996/06/04 19:58:47  wenger
  Added the data segment option to TDataBinary; various minor cleanups.

  Revision 1.22  1996/06/04 14:21:39  wenger
  Ascii data can now be read from session files (or other files
  where the data is only part of the file); added some assertions
  to check for pointer alignment in functions that rely on this;
  Makefile changes to make compiling with debugging easier.

  Revision 1.21  1996/05/31 15:02:25  jussi
  Replaced a couple of occurrences of _data->isTape with _data->isTape().

  Revision 1.20  1996/05/22 17:52:13  wenger
  Extended DataSource subclasses to handle tape data; changed TDataAscii
  and TDataBinary classes to use new DataSource subclasses to hide the
  differences between tape and disk files.

  Revision 1.19  1996/05/07 16:43:00  jussi
  Cache file name now based on file alias (TData name). Added parameter
  to the Decode() function call.

  Revision 1.18  1996/04/20 19:56:56  kmurli
  QueryProcFull now uses the Marker calls of Dispatcher class to call
  itself when needed instead of being continuosly polled by the Dispatcher.

  Revision 1.17  1996/04/18 17:12:04  jussi
  Added missing #include <errno.h>.

  Revision 1.16  1996/04/18 17:04:59  jussi
  Fixed Checkpoint() which produced an unnecessary error message
  when a very small file (less than FILE_CONTENT_COMPARE_BYTES)
  was checkpointed.

  Revision 1.15  1996/04/16 20:38:50  jussi
  Replaced assert() calls with DOASSERT macro.

  Revision 1.14  1996/03/27 15:31:01  jussi
  Small fixes for tape TData.

  Revision 1.13  1996/03/26 21:18:43  jussi
  Merged with TDataTape. Added magic number to cache file.

  Revision 1.12  1996/03/05 22:06:04  jussi
  Minor fix in debugging output.

  Revision 1.11  1996/02/01 18:04:41  jussi
  Disabled 'Ignoring invalid record.' because this message shouldn't
  appear for ignored comments.

  Revision 1.10  1996/01/25 20:22:34  jussi
  Improved support for data files that grow while visualization
  is being performed.

  Revision 1.9  1996/01/12 15:24:45  jussi
  Replaced libc.h with stdlib.h.

  Revision 1.8  1996/01/09 16:35:00  jussi
  Improved console output messages.

  Revision 1.7  1995/12/28 19:59:41  jussi
  Small fixes to remove compiler warnings.

  Revision 1.6  1995/12/14 21:19:31  jussi
  Replaced 0x%x with 0x%p.

  Revision 1.5  1995/12/14 17:57:37  jussi
  Small fixes to get rid of g++ -Wall warnings.

  Revision 1.4  1995/11/24 21:34:55  jussi
  Added _currPos scheme to eliminate most of the fseek() calls.
  This appears to speed up execution significantly.

  Revision 1.3  1995/11/22 17:51:35  jussi
  Added copyright notice and cleaned up the code. Optimized some
  routines a la TDataTape.C.

  Revision 1.2  1995/09/05 22:15:49  jussi
  Added CVS header.
*/

//#define DEBUG

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Parse.h"
#include "TDataAscii.h"
#include "Exit.h"
#include "Util.h"
#include "DataSourceFileStream.h"
#include "DataSourceSegment.h"
#include "DataSourceTape.h"
#include "DataSourceBuf.h"
#include "DevError.h"
#include "DataSeg.h"
#include "QueryProc.h"

#ifdef ATTRPROJ
#   include "ApInit.h"
#else
#   include "Init.h"
#   include "DataSourceWeb.h"
#endif

# define  _STREAM_COMPAT

static const int INDEX_ALLOC_INC = 10000; // allocation increment for index
static const int LINESIZE = 4096;         // maximum size of each line

/* We cache the first FILE_CONTENT_COMPARE_BYTES from the file.
   The next time we start up, this cache is compared with what's in
   the file to determine if they are the same file. */

static const int FILE_CONTENT_COMPARE_BYTES = 4096;


static char fileContent[FILE_CONTENT_COMPARE_BYTES];
static char indexFileContent[FILE_CONTENT_COMPARE_BYTES];
static char *   srcFile = __FILE__;

TDataAscii::TDataAscii(char *name, char *type, char *param, int recSize)
: TData(name, type, param, recSize)
{
    DO_DEBUG(printf("TDataAscii::TDataAscii(0x%p)(%s, %s, %s, %d)\n",
		    this, name, type, param, recSize));
    DO_DEBUG(printf("_data = 0x%p\n", _data));

    _fileOpen = true;
    if (_data->Open("r") != StatusOk) {
	_fileOpen = false;
    }
    
    DataSeg::Set(NULL, NULL, 0, 0);
    
    _bytesFetched = 0;
    
    _lastPos = 0;
    _currPos = 0;
    _lastIncompleteLen = 0;

    _totalRecs = 0;

    _indexP = new FileIndex(INDEX_ALLOC_INC);

    Dispatcher::Current()->Register(this, 10, AllState, 
				    false, _data->AsyncFd());
}

TDataAscii::~TDataAscii()
{
#ifdef DEBUG
  printf("TDataAscii destructor\n");
#endif

  if (_fileOpen)
    _data->Close();

  Dispatcher::Current()->Unregister(this);

  delete _indexP;
  delete _indexFileName;
}

Boolean TDataAscii::CheckFileStatus()
{
  CheckDataSource();
  // see if file is (still) okay
  if (!_data->IsOk()) {
    // if file used to be okay, close it
    if (_fileOpen) {
      Dispatcher::Current()->Unregister(this);
      printf("Data stream %s is no longer available\n", _name);
      _data->Close();
      TData::InvalidateTData();
      _fileOpen = false;
    }
    Boolean old = DevError::SetEnabled(false);
    if (_data->Open("r") != StatusOk) {
      // file access failure, get rid of index
      _indexP->Clear();
      _initTotalRecs = _totalRecs = 0;
      _initLastPos = _lastPos = 0;
      _lastIncompleteLen = 0;
      (void)DevError::SetEnabled(old);
      return false;
    }
    (void)DevError::SetEnabled(old);
    printf("Data stream %s has become available\n", _name);
    _fileOpen = true;
    Dispatcher::Current()->Register(this, 10, AllState,
                                    false, _data->AsyncFd());
  }

  return true;
}

int TDataAscii::Dimensions(int *sizeDimension)
{
  sizeDimension[0] = _totalRecs;
  return 1;
}

Boolean TDataAscii::HeadID(RecId &recId)
{
  recId = 0;
  return (_totalRecs > 0);
}

Boolean TDataAscii::LastID(RecId &recId)
{
  if (!CheckFileStatus()) {
    recId = _totalRecs - 1;
    return false;
  }

  if (!_data->isTape()) {
    // see if file has shrunk or grown
    _currPos = _data->gotoEnd();
#ifdef DEBUG
    printf("TDataAscii::LastID: currpos: %ld, lastpos: %ld\n", 
	   _currPos, _lastPos);
#endif
    if (_currPos < _lastPos) {
      // file has shrunk, rebuild index from scratch
#ifdef DEBUG
      printf("Rebuilding index...\n");
#endif
	InvalidateTData();
    } else if (_currPos > _lastPos) {
      // file has grown, build index for new records
#ifdef DEBUG
      printf("Extending index...\n");
#endif
      BuildIndex();
#ifndef ATTRPROJ
      QueryProc::Instance()->RefreshTData(this);
#endif
    }
  }
  
  recId = _totalRecs - 1;
  return (_totalRecs > 0);
}

void TDataAscii::InitGetRecs(RecId lowId, RecId highId,RecordOrder order)
{
  DOASSERT((long)lowId < _totalRecs && (long)highId < _totalRecs
	   && highId >= lowId, "Invalid record parameters");

  _lowId = lowId;
  _highId = highId;
  _nextId = lowId;
  _endId = highId;
}

Boolean TDataAscii::GetRecs(void *buf, int bufSize, 
			    RecId &startRid,int &numRecs, int &dataSize,
			    void **recPtrs)
{
#ifdef DEBUG
  printf("TDataAscii::GetRecs buf = 0x%p\n", buf);
#endif

  numRecs = bufSize / _recSize;
  DOASSERT(numRecs, "Not enough record buffer space");

  if (_nextId > _endId)
    return false;
  
  int num = _endId - _nextId + 1;
  if (num < numRecs)
    numRecs = num;
  
  ReadRec(_nextId, numRecs, buf);
  
  startRid = _nextId;
  dataSize = numRecs * _recSize;
  _nextId += numRecs;
  
  _bytesFetched += dataSize;
  
  return true;
}

void TDataAscii::GetRecPointers(RecId startId, int numRecs,
				void *buf, void **recPtrs)
{
  DOASSERT(0, "Feature not implemented");
}

void TDataAscii::GetIndex(RecId id, int *&indices)
{
  static int index[1];
  index[0] = id;
  indices = index;
}

int TDataAscii::GetModTime()
{
  if (!CheckFileStatus())
    return -1;

  return _data->GetModTime();
}

char *TDataAscii::MakeIndexFileName(char *name, char *type)
{
  char *fname = StripPath(name);
  int nameLen = strlen(Init::WorkDir()) + 1 + strlen(fname) + 1;
  char *fn = new char [nameLen];
  sprintf(fn, "%s/%s", Init::WorkDir(), fname);
  return fn;
}

void TDataAscii::Initialize()
{
  _indexFileName = MakeIndexFileName(_name, _type);

  if (!CheckFileStatus())
    return;

  if (_data->isBuf()) {
      BuildIndex();
      return;
  }

  if (!_indexP->Initialize(_indexFileName, _data, this, _lastPos,
    _totalRecs).IsComplete()) goto error;

  _initTotalRecs = _totalRecs;
  _initLastPos  = _lastPos;

  /* continue to build index */
  BuildIndex();
  return;

 error:
  /* recover from error by building index from scratch  */
#ifdef DEBUG
  printf("Rebuilding index...\n");
#endif
  RebuildIndex();
}

void TDataAscii::Checkpoint()
{
  if (!CheckFileStatus()) {
    printf("Cannot checkpoint %s\n", _name);
    return;
  }

  if (_data->isBuf())
      return;

  printf("Checkpointing %s: %ld total records, %ld new\n", _name,
	 _totalRecs, _totalRecs - _initTotalRecs);
  
  if (_lastPos == _initLastPos && _totalRecs == _initTotalRecs)
    /* no need to checkpoint */
    return;
  
  if (!_indexP->Checkpoint(_indexFileName, _data, this, _lastPos,
    _totalRecs).IsComplete()) goto error;

  _currPos = _data->Tell();

  return;
  
 error:
  _currPos = _data->Tell();
}


void TDataAscii::InvalidateTData()
{
    RebuildIndex();
    TData::InvalidateTData();
}


/* Build index for the file. This code should work when file size
   is extended dynamically. Before calling this function, position
   should be at the last place where file was scanned. */

void TDataAscii::BuildIndex()
{
  char buf[LINESIZE];
  char recBuf[_recSize];
  int oldTotal = _totalRecs;
  
  _currPos = _lastPos - _lastIncompleteLen;

  // First go to last valid position of file
  if (_data->Seek(_currPos, SEEK_SET) < 0) {
    reportErrSys("fseek");
    return;
  }

  _lastIncompleteLen = 0;

  while(1) {

    int len = 0;

    if (_data->Fgets(buf, LINESIZE) == NULL)
      break;

#ifdef DEBUG
	printf("read record: \"%s\"\n", buf);
#endif

    len = strlen(buf);

    if (len > 0 && buf[len - 1] == '\n') {
      buf[len - 1] = 0;
      if (Decode(recBuf, _currPos, buf)) {
	_indexP->Set(_totalRecs++, _currPos);
      } else {
#ifdef DEBUG
	printf("Ignoring invalid record: \"%s\"\n", buf);
#endif
      }
      _lastIncompleteLen = 0;
    } else {
#ifdef DEBUG
      printf("Ignoring incomplete record: \"%s\"\n", buf);
#endif
      _lastIncompleteLen = len;
    }

    _currPos += len;
  }

  // last position is > current position because TapeDrive advances
  // bufferOffset to the next block, past the EOF, when tape file
  // ends
  _lastPos = _data->Tell();
  DOASSERT(_lastPos >= _currPos, "Incorrect file position");

#ifdef    DEBUG
  printf("Index for %s: %ld total records, %ld new\n", _name,
	 _totalRecs, _totalRecs - oldTotal);
#endif

  if (_totalRecs <= 0) {
    char errBuf[1024];
    sprintf(errBuf, "No valid records for data stream %s\n"
      "    (check schema/data correspondence)\n", _name);
    Exit::DoAbort(errBuf, __FILE__, __LINE__);
  }
}

/* Rebuild index */

void TDataAscii::RebuildIndex()
{
  InvalidateIndex();

  _indexP->Clear();
  _initTotalRecs = _totalRecs = 0;
  _initLastPos = _lastPos = 0;
  _lastIncompleteLen = 0;

  BuildIndex();
}

void TDataAscii::ReadRec(RecId id, int numRecs, void *buf)
{
#ifdef DEBUG
  printf("TDataAscii::ReadRec %ld,%d,0x%p\n", id, numRecs, buf);
#endif

  char line[LINESIZE];
  
  char *ptr = (char *)buf;

  for(int i = 0; i < numRecs; i++) {

    int len;
    if (_currPos != (long) _indexP->Get(id + i)) {
      if (_data->Seek(_indexP->Get(id + i), SEEK_SET) < 0) {
        perror("fseek");
        DOASSERT(0, "Cannot perform file seek");
      }
      _currPos = _indexP->Get(id + i);
    }
    if (_data->Fgets(line, LINESIZE) == NULL) {
      reportErrSys("fgets");
      DOASSERT(0, "Cannot read from file");
    }
    len = strlen(line);

    if (len > 0 ) {
      DOASSERT(line[len - 1] == '\n', "Data record too long");
      line[len - 1] = '\0';
    }

    Boolean valid = Decode(ptr, _currPos, line);
    DOASSERT(valid, "Inconsistent validity flag");
    ptr += _recSize;

    _currPos += len;
  }
}

void TDataAscii::WriteRecs(RecId startRid, int numRecs, void *buf)
{
  DOASSERT(!_data->isTape(), "Writing to tape not supported yet");

  _totalRecs += numRecs;

  _indexP->Set(_totalRecs - 1, _lastPos);
  int len = strlen((char *)buf);

  if (_data->append(buf, len) != len) {
    reportErrSys("append");
    DOASSERT(0, "Cannot append to file");
  }

  _lastPos = _data->Tell();
  _currPos = _lastPos;
}

void TDataAscii::WriteLine(void *line)
{
  DOASSERT(!_data->isTape(), "Writing to tape not supported yet");

  int len = strlen((char *)line);

  if (_data->append(line, len) != len) {
    reportErrSys("append");
    DOASSERT(0, "Cannot append to file");
  }

  _lastPos = _data->Tell();
  _currPos = _lastPos;
}

void TDataAscii::Run()
{
    int fd = _data->AsyncFd();
    _data->AsyncIO();
    if (_data->AsyncFd() != fd) {
        Dispatcher::Current()->Unregister(this);
        Dispatcher::Current()->Register(this, 10, AllState,
                                        false, _data->AsyncFd());
    }
}

void TDataAscii::Cleanup()
{
  Checkpoint();

  if (_data->isTape())
    _data->printStats();
}

void TDataAscii::PrintIndices()
{
  int cnt = 0;
  for(long i = 0; i < _totalRecs; i++) {
    printf("%ld ", _indexP->Get(i));
    if (cnt++ == 10) {
      printf("\n");
      cnt = 0;
    }
  }
  printf("\n");
}
