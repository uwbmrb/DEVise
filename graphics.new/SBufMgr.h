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
  Revision 1.8  1996/11/11 15:50:57  jussi
  Removed IOTask virtual base class and substituted UnixIOTask for
  it. When SBufMgr accesses an IOTask, no separate process is
  created. A process is created only when a ReadStream() or WriteStream()
  function of IOTask is called. In Solaris, switched to using processes
  instead of threads.

  Revision 1.7  1996/11/08 15:42:24  jussi
  Removed IOTask::Initialize() and SetBuffering(). Added support
  for streaming via ReadStream() and WriteStream().

  Revision 1.6  1996/11/07 17:37:13  jussi
  Memory pool is no longer a separate process but a reentrant
  function library.

  Revision 1.5  1996/11/04 20:21:00  jussi
  Improved support for parallel writes.

  Revision 1.4  1996/11/01 20:11:59  jussi
  MemPool object now forks a separate memory pool process. Got rid
  of the option of having processes sharing data via pipes. (Pipes
  still used for sharing control information.) SBufMgr object now
  compatible with process/shared memory environment.

  Revision 1.3  1996/10/02 19:48:33  jussi
  Added support for writing data through an HTTP connection.
  Also made it possible to use simple POST/GET transactions
  using a single IOUnixWebTask.

  Revision 1.2  1996/09/26 20:29:07  jussi
  Made code compile in Linux without threads.

  Revision 1.1  1996/09/26 19:02:33  jussi
  Renamed file from ExtBufMgr -> SBufMgr. Added Web I/O task and
  changed buffer manager to allow more concurrency between I/Os.

  Revision 1.2  1996/09/07 01:43:31  jussi
  Method BufferDealloc() is used also when BUFFER is not defined.

  Revision 1.1  1996/08/01 22:45:27  jussi
  Initial revision.
*/

#ifndef SBufMgr_h
#define SBufMgr_h

//
// Configuration of the buffer manager
// -----------------------------------
//
// Choose one of the following feature combinations by uncommenting
// the corresponding #define's.
//
//   Processes, shared memory, with or without buffering
//   Threads, local memory, with or without buffering
//

//#define PROCESS_TASK
//#define THREAD_TASK
//#define SHARED_MEMORY

#if defined(SOLARIS)
//#define THREAD_TASK
#define PROCESS_TASK
#define SHARED_MEMORY
#else
#define PROCESS_TASK
#define SHARED_MEMORY
#endif

#if !defined(PROCESS_TASK) && !defined(THREAD_TASK)
#error "Must use either process or thread tasks"
#endif

#if defined(PROCESS_TASK) && defined(THREAD_TASK)
#error "Cannot use both process and thread tasks"
#endif

#if defined(PROCESS_TASK) && !defined(SHARED_MEMORY)
#error "Must have shared memory for process tasks"
#endif

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#ifdef THREAD_TASK
#include <pthread.h>
#endif

#include "tapedrive.h"
#include "DeviseTypes.h"
#include "HashTable.h"
#include "DCE.h"
#include "DList.h"

struct PageRange {
    int start;
    int end;
};

DefineDList(PageRangeList, PageRange);

// Memory manager

class MemMgr {
  public:
    MemMgr(int numPages, int pageSize, int &status);
    ~MemMgr();

    // Page types
    enum PageType { Cache, Buffer };

    int Allocate(PageType type, char *&page);
    int Release(PageType type, char *&page);
    int Deallocate(PageType type, char *page);
    int Convert(char *page, PageType oldType, PageType &newType);

    int FreeLeft() {
        AcquireMutex();
        int num = *_numFree;
        ReleaseMutex();
        return num;
    }

    int PageSize() { return _pageSize; }
    int NumPages() { return _numPages; }

    static MemMgr *Instance() { return _instance; }

  protected:
    // Initialization
    int Initialize();

    // Acquire and release mutex
    void AcquireMutex() { _sem->acquire(1); }
    void ReleaseMutex() { _sem->release(1); }

    // Acquire and release free semaphore
    void AcquireFree() { _free->acquire(1); }
    void ReleaseFree() { _free->release(1); }

    // Number of memory pages and their size
    const int _numPages;
    const int _pageSize;

    // Base address of memory
    char *_buf;

    // Pointers and counters of free/used pages
    char **_freePage;
    int *_numFree;
    int *_numCache;
    int *_numBuffer;

    // Maximum ratio of buffer pages to total pages
    const float _maxBuff;

    // An instance of this class
    static MemMgr *_instance;

    // Mutex for synchronization
    SemaphoreV *_sem;
    SemaphoreV *_free;

#ifdef SHARED_MEMORY
    // Shared memory
    SharedMemory *_shm;
#endif
};

// Data Pipe

class DataPipe {
  public:
    DataPipe(int maxPages);
    ~DataPipe();

    int Consume(char *&buf);
    int Produce(char *buf, int bytes);

  protected:
    // Acquire and release mutex
    void AcquireMutex() { _sem->acquire(1); }
    void ReleaseMutex() { _sem->release(1); }

    // Acquire and release free semaphore
    void AcquireFree() { _free->acquire(1); }
    void ReleaseFree() { _free->release(1); }

    // Acquire and release data semaphore
    void AcquireData() { _data->acquire(1); }
    void ReleaseData() { _data->release(1); }

    SemaphoreV *_sem;                   // mutex for synchronization
    SemaphoreV *_free;
    SemaphoreV *_data;

#ifdef SHARED_MEMORY
    SharedMemory *_shm;                 // shared memory
#endif

    int _maxPages;                      // maximum pipe size

    char **_streamData;                 // stream data structures
    int *_streamBytes;
    int *_streamHead;
    int *_streamTail;
    int *_streamFree;
};

// I/O task

class IOTask {
  public:
    // Create and destroy I/O task
    IOTask(int blockSize = -1);
    virtual int WriteEOF() { return 0; }
    virtual ~IOTask();

    // Read specified byte range from file
    int Read(unsigned long long offset,
             unsigned long bytes,
             char *&addr);

    // Read specified block range
    int ReadP(int blockOffset, int blocks, char *&addr) {
        int result = Read(blockOffset * _blockSize, blocks * _blockSize, addr);
        if (result < 0 || (result % _blockSize) != 0)
            return -1;
        return result / _blockSize;
    }

    // Write specified byte range to file
    int Write(unsigned long long offset,
              unsigned long bytes,
              char *&addr);

    // Write specified block range
    int WriteP(int blockOffset, int blocks, char *&addr) {
        int result = Read(blockOffset * _blockSize, blocks * _blockSize, addr);
        if (result < 0 || (result % _blockSize) != 0)
            return -1;
        return result / _blockSize;
    }

    // Read stream
    int ReadStream(unsigned long bytes, int pipeSize);
    int Consume(char *&buf) {
        return _dataPipe->Consume(buf);
    }

    // Write stream
    int WriteStream(int pipeSize);
    int Produce(char *buf, int bytes) {
        return _dataPipe->Produce(buf, bytes);
    }

    // Terminate I/O stream
    int Terminate();

    // Return busy/idle status
    Boolean IsBusy();

  protected:
    int StartChild(int pipeSize);

    // Request types
    enum ReqType { ReadReq, WriteReq };

    // Request structure
    struct Request {
        ReqType type;
        unsigned long long offset;
        unsigned long bytes;
        char *addr;
        int result;
    };

    // Child process for streaming data
    static void *DoStream(void *arg);
    void *DoStream();

    // Function for handling actual I/O
    virtual void DeviceIO(Request &req, Request &reply) = 0;

    // Return current offset
    virtual unsigned long long Offset() = 0;

    // Read stream
    void _ReadStream(unsigned long bytes);

    // Write stream
    void _WriteStream();

    // Set/clear device busy flag
    void SetDeviceBusy() { _isBusy->acquire(1); }
    void SetDeviceIdle() { _isBusy->release(1); }

    const int _pageSize;                // size of memory manager pages
    int _blockSize;                     // (user) data block size

    DataPipe *_dataPipe;                // data pipe
    Boolean _readStream;                // read streaming enabled
    Boolean _writeStream;               // write streaming enabled
    unsigned long _readStreamLength;

    unsigned long long int _readBytes;  // # bytes read
    unsigned long long int _writeBytes; // # bytes written
    unsigned long long int _seekBytes;  // total seek distance in bytes

#ifdef PROCESS_TASK
    pid_t _child;                       // pid of child process
#endif
#ifdef THREAD_TASK
    pthread_t _child;                   // thread id of child
#endif

    SemaphoreV *_isBusy;                // flag indicating busy device
};

// I/O task for Unix file descriptors

class FdIOTask : public IOTask {
  public:
    // Create I/O task using file descriptors
    FdIOTask(int fd, int blockSize = -1);

  protected:
    // Function for handling actual I/O
    virtual void DeviceIO(Request &req, Request &reply);

    // Return current offset
    virtual unsigned long long Offset() { return _offset; }

    int _fd;                            // fd of device
    unsigned long long _offset;         // current offset on device
};

// I/O task for Web connections

class WebIOTask : public FdIOTask {
  public:
    // Create Web I/O task
    WebIOTask(char *url, Boolean isInput, int blockSize = -1);
    virtual ~WebIOTask();

    // Finish writing to HTTP
    virtual int WriteEOF();

  protected:
    // Open connection to Web resource
    int OpenURL(char *url, Boolean isInput);

    // Write cached HTTP file to Web site
    void WriteHTTP();

    // Make unique cache file name for URL
    char *MakeCacheName(char *url);

    // Function for handling actual I/O
    virtual void DeviceIO(Request &req, Request &reply);

    int _webfd;                         // file descriptor for Web connection
    char *_url;                         // URL of Web resource
    Boolean _isInput;                   // true if input Web resource
    FILE *_cache;                       // cache file pointer
    char *_cacheName;                   // name of cache file
    unsigned long int _cacheSize;       // current size of cache file
};

// I/O task for TapeDrive objects

class TapeIOTask : public IOTask {
  public:
    // Create tape I/O task
    TapeIOTask(TapeDrive &tape);

  protected:
    // Function for handling actual I/O
    virtual void DeviceIO(Request &req, Request &reply);

    // Return current offset
    virtual unsigned long long Offset() { return _offset; }

    TapeDrive &_tape;                   // tape device
    unsigned long long _offset;         // current offset on tape
};

// Page address information

struct PageAddr {
    IOTask *stream;                     // stream pointer
    long pageNo;                        // page number within a stream
};

inline int operator==(PageAddr &addr1, PageAddr &addr2)
{
    if (addr1.stream == addr2.stream && addr1.pageNo == addr2.pageNo)
        return 1;
    return 0;
}

// Page frame information

class PageFrame {
  friend class CacheMgr;
  friend class CacheMgrLRU;

  public:
    PageFrame() {
        Clear();
        page = 0;
        size = 0;
    }
    
  protected:
    PageAddr addr;                      // address of page in frame
    char *page;                         // memory image of page
    int size;                           // page length (_pageSize for all
                                        // except last page in file)
    int pinCnt;                         // pin count of page
    unsigned valid: 1;                  // true if frame information is valid
    unsigned dirty: 1;                  // true if page is dirty
    unsigned refbit: 1;                 // true if page referenced recently
    unsigned iopending: 1;              // true if I/O pending for page

  // Initialize frame for page

  void Clear() {
      pinCnt = 0;
      addr.stream = 0;
      addr.pageNo = -1;
      valid = dirty = refbit = iopending = false;
  }

  // Set frame fields

  void Set(IOTask *stream, int pageNo) { 
      addr.stream = stream;
      addr.pageNo = pageNo;
      pinCnt = 1;
      valid = true;
      dirty = false;
      refbit = true;
  }
};

// Streaming buffer manager

class CacheMgr {
  public:
    CacheMgr(MemMgr &mgr, int frames);
    virtual ~CacheMgr();  

    // Request types
    enum ReqType { PinPageReq, UnPinPageReq, UnPinReq, TerminateReq };

    // Request structure
    struct Request {
        ReqType type;                   // request type
        IOTask *stream;                 // I/O stream
        int pageNo;                     // page number
        char *page;                     // page address
        int size;                       // size of page
        Boolean read;                   // true if allocate new page
        Boolean dirty;                  // true if page is dirty
        Boolean force;                  // true if page must be forced out
    };

    // Direct (same process) interface to memory manager
    int AllocPage(IOTask *stream, int pageNo, char *&page) {
        return PinPage(stream, pageNo, page, false);
    }
    int PinPage(IOTask *stream, int pageNo,
                char *&page, Boolean read = true) {
        AcquireMutex();
        int result = _PinPage(stream, pageNo, page, read);
        ReleaseMutex();
        return result;
    }
    int UnPinPage(IOTask *stream, int pageNo, Boolean dirty,
                  int size = -1, Boolean force = false) {
        AcquireMutex();
        int result = _UnPinPage(stream, pageNo, dirty, size, force);
        ReleaseMutex();
        return result;
    }
    int UnPin(IOTask *stream, Boolean dirty) {
        AcquireMutex();
        int result = _UnPin(stream, dirty);
        ReleaseMutex();
        return result;
    }
    int InMemory(IOTask *stream, int pageStart, int pageEnd,
                 PageRangeList *&inMemory) {
        AcquireMutex();
        int result = _InMemory(stream, pageStart, pageEnd, inMemory);
        ReleaseMutex();
        return result;
    }

    static CacheMgr *Instance() { return _instance; }

 protected:
    // Initialization
    virtual int Initialize();

    // Acquire and release mutex
    void AcquireMutex() { _mutex->acquire(); }
    void ReleaseMutex() { _mutex->release(); }

    int _PinPage(IOTask *stream, int pageNo,
                 char *&page, Boolean read = true);
    int _UnPinPage(IOTask *stream, int pageNo, Boolean dirty,
                   int size = -1, Boolean force = false);
    int _UnPin(IOTask *stream, Boolean dirty);
    int _InMemory(IOTask *stream, int pageStart, int pageEnd,
                  PageRangeList *&inMemory);

    // An instance of this class
    static CacheMgr *_instance;

    void _AllocMemory();
    void _DeallocMemory();

#ifdef NEWSTUFF
    // Request interface
    int SendReq(Request &req, Request &reply);

    // Child process for communicating with parent
    static void *ProcessReq(void *arg);
    void *ProcessReq();

    // Fd's of pipes for requests
    int _reqFd[2];
    int _replyFd[2];

#ifdef PROCESS_TASK
    pid_t _child;                       // pid of child process
#endif
#ifdef THREAD_TASK
    pthread_t _child;                   // thread id of child
#endif
#endif

    // Pick a free frame; pick victim page if necessary
    int AllocFrame();
    virtual int PickVictim() = 0;

    // Hash function for page address hash table
    static int AddrHash(PageAddr &addr, int numBuckets);

    // Print diagnostic information
    virtual void Dump();

    // Memory manager
    MemMgr &_mgr;

    // Number of frames and page size
    const int _numFrames;
    const int _pageSize;

    // Page frames
    PageFrame *_frames;
#ifdef SHARED_MEMORY
    SharedMemory *_frmShm;
#else
    // Hash table of page addresses
    HashTable<PageAddr, int> _ht;
#endif

    // Mutexes for synchronization
    SemaphoreV *_mutex;
};

// LRU buffer manager

class CacheMgrLRU : public CacheMgr {
  public:
    CacheMgrLRU(MemMgr &mgr, int frames);
    virtual ~CacheMgrLRU() {}

 protected:
    // Pick victim for replacement
    virtual int PickVictim();

    // Clock hand for Clock page replacement algorithm
    int _clockHand;
};

#endif
