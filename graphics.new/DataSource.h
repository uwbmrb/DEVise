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
  Header file for DataSource class.
 */

/*
  $Id$

  $Log$
  Revision 1.13  2000/01/13 23:07:02  wenger
  Got DEVise to compile with new (much fussier) compiler (g++ 2.95.2).

  Revision 1.12  1997/02/07 22:01:10  liping
  Fixed complile problem

  Revision 1.11  1997/02/03 19:45:20  ssl
  1) RecordLink.[Ch],QueryProcFull.[ch]  : added negative record links
  2) ViewLens.[Ch] : new implementation of piled views
  3) ParseAPI.C : new API for ViewLens, negative record links and layout
     manager

  Revision 1.10  1996/12/18 15:32:09  jussi
  Added synchronization methods and IsBusy() method.

  Revision 1.9  1996/12/03 20:36:02  jussi
  Added support for concurrent I/O.

  Revision 1.8  1996/11/18 22:29:01  jussi
  Added DataSize() method.

  Revision 1.7  1996/08/04 21:23:23  beyer
  DataSource's are now reference counted.
  Added Version() which TData now check to see if the DataSource has changed,
    and if it has, it rebuilds its index and invalidates the cache.
  DataSourceFixedBuf is a DataSourceBuf that allocates and destoyes its
    own buffer.
  DerivedDataSource functionality is now in the TData constructor.
  Added some defaults for virtual methods.

  Revision 1.6  1996/07/01 19:31:31  jussi
  Added an asynchronous I/O interface to the data source classes.
  Added a third parameter (char *param) to data sources because
  the DataSegment template requires that all data sources have the
  same constructor (DataSourceWeb requires the third parameter).

  Revision 1.5  1996/06/27 15:50:57  jussi
  Added IsOk() method which is used by TDataAscii and TDataBinary
  to determine if a file is still accessible. Also moved GetModTime()
  functionality from TDataAscii/TDataBinary to the DataSource
  classes.

  Revision 1.4  1996/05/22 17:51:59  wenger
  Extended DataSource subclasses to handle tape data; changed TDataAscii
  and TDataBinary classes to use new DataSource subclasses to hide the
  differences between tape and disk files.

  Revision 1.3  1996/05/07 22:28:19  jussi
  Reverted the changes made in the previous check-in because I
  found a better way to fix the problem where only the tail
  part of a schema file name is returned when a session is saved.

  Revision 1.2  1996/05/07 22:13:50  jussi
  Added virtual method getName() to DataSourceFile which returns
  the filename, not the regular name or alias. The filename is
  needed when a session file is saved.

  Revision 1.1  1996/05/07 16:04:18  wenger
  Added final version of code for reading schemas from session files;
  added an error-reporting class to improve error info.

 */

#ifndef _DataSource_h_
#define _DataSource_h_


#include <sys/types.h>

#include "Exit.h"
#include "MemMgr.h"
#include "DevStatus.h"


/* Select data source process to be implemented as a process or thread */

#define DS_PROCESS
//#define DS_THREAD

#if !defined(DS_PROCESS) && !defined(DS_THREAD)
#error "Must use either processes or threads"
#endif

#if defined(DS_PROCESS) && defined(DS_THREAD)
#error "Cannot use both processes and threads"
#endif


class ViewGraph;


class DataSource
{
      public:
        DataSource(const char *label = "", ViewGraph* controlling_view = NULL);

	virtual ~DataSource();

	virtual const char *objectType() {return "DataSource";};

	virtual char *getLabel();

	// These functions essentially do the same thing as the standard
	// functions of the same name.  The names are capitalized to avoid
	// conflicts with macros in some system header files that redefine
	// symbols such as ftell, etc.
	virtual DevStatus Open(const char *mode) = 0;
	virtual Boolean IsOk() = 0;
	virtual DevStatus Close() = 0;

	virtual char *Fgets(char *buffer, int size);
	virtual size_t Fread(char *buf, size_t size, size_t itemCount);
	virtual size_t Read(char *buf, int byteCount);

	virtual size_t Fwrite(const char *buf, size_t size, size_t itemCount);
	virtual size_t Write(const char *buf, size_t byteCount);

	// Returns -1 if error, 0 otherwise.
	virtual int Seek(long offset, int from) = 0;
	virtual long Tell() = 0;

	// Go to the end of the data, and return that location.
	virtual int gotoEnd() = 0;

	// Append to the end of the data.
	virtual int append(void *buf, int recSize);

	// Get modification time of object.  The default ModTime is -1.
	virtual int GetModTime();

	// TData can keep track of the version that was last used by it
	// and if it changed, then it knows that it must invalidate its
	// index & gdata.  The default version is to always return 0.
	int Version() { return _version; }

	// Print statistics about this object.
	virtual void printStats();

	// Is this object a (disk) file?  Default: false
	virtual Boolean isFile();

	// Is this object a buffer?  Default: false
	virtual Boolean isBuf();

	// Is this object a tape?  Default: false
	virtual Boolean isTape();

	// This data source is generated by _view (used by stats)
	void SetControllingView(ViewGraph* v) { _controlling_view = v; }
	ViewGraph* ControllingView() { return _controlling_view; }
	void RemoveControllingView(ViewGraph* v) {
	    DOASSERT(_controlling_view == v, 
		     "View was not the controlling view");
	    _controlling_view = NULL;
	}

	void AddRef();

	// Returns true if the caller should delete this object
	bool DeleteRef();

        // Return (estimated) data size
        virtual bytecount_t DataSize() { return 0; }

        // Initialize and terminate data source process.
        int InitializeProc();
        int TerminateProc();
        Boolean SupportsAsyncIO() { return (_child >= 0 ? true : false); }
        
        // Read and write from/to data source process.
        int ReadProc(streampos_t offset, iosize_t bytes);
        int WriteProc(streampos_t offset, iosize_t bytes);

        // Produce or consume data to/from data pipe.
        int Produce(char *buf, streampos_t offset, iosize_t bytes) {
	    DOASSERT(_dpipe, "Invalid data pipe");
            return _dpipe->Produce(buf, offset, bytes);
        }
        int Consume(char *&buf, streampos_t &offset, iosize_t &bytes) {
	    DOASSERT(_dpipe, "Invalid data pipe");
            return _dpipe->Consume(buf, offset, bytes);
        }
        int NumPipeData() {
	    DOASSERT(_dpipe, "Invalid data pipe");
            return _dpipe->NumData();
        }
        Boolean IsBusy();

      protected:
        
	int             _ref_count;
	char *		_label;
	int             _version;
	ViewGraph*      _controlling_view;

        //
        // The remaining variables and methods are used when DataSource
        // operates as a separate process and communicates with Devise
        // through pipes.
        //

        // Statistics of request types and data traffic.
        bytecount_t  _totalCount;       // total # requests processed
        bytecount_t _readBytes;         // # bytes read
        bytecount_t _writeBytes;        // # bytes written
        bytecount_t _seekBytes;         // total seek distance in bytes
        
        // Request types
        enum ReqType { ReadReq, WriteReq, ReadStreamReq,
                       WriteStreamReq, TerminateReq };

        // Request structure
        struct Request {
            ReqType type;
            streampos_t offset;
            iosize_t bytes;
        };

        // Reply structure
        struct Reply {
            int handle;
        };

        // Current request handle value
        int _handle;

        // Child process for communicating with parent
        static void *ProcessReq(void *arg);
        void *ProcessReq();

        // Read and write streaming
        void ReadStream(streampos_t offset, iosize_t bytes);
        void WriteStream(streampos_t offset, iosize_t bytes);
        DataPipe *_dpipe;

        // Fd's of pipes for requests
        int _reqFd[2];
        int _replyFd[2];

#ifdef DS_PROCESS
        pid_t _child;                   // pid of child process
#endif
#ifdef DS_THREAD
        pthread_t _child;               // thread id of child
#endif
};


#endif /* _DataSource_h_ */

/*============================================================================*/
