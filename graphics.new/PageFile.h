/*
  $Id$

  $Log$*/

/* Page file that uses a buffer manager to for I/O */

#ifndef PageFile_h
#define PageFile_h
#include "BufHint.h"
class BufMgr;
class BufPage;
class DiskFile;
class PageRange;
struct RangeData;

struct PageFileHeader {
	int numPages;	/* # of pages in the page file, gap included */
	int pagesAlloc;	/* # of non-gap gapes allocated */
	int maxAlloc;	/* max # of pages allowed, or -1 if no limit */
};

class PageFile {
public:
	PageFile(char *name, BufMgr *mgr, int maxAlloc = -1);
	~PageFile();

	/* Return max # of pages to allocated, or -1 if no maximum */
	int MaxAlloc() { return _header.maxAlloc; }

	/* Get size of the file in pages. For a page file with hole,
	it's the maximum size */
	int NumPages() { return _header.numPages;}

	/* Get the data for the given page and fix it in
	memory. Pages numbers start from 1 .. NUmPages().
	isPrefetch = TRUE if doing prefetch.*/
	BufPage *GetPage(int pageNum, Boolean isPrefetch = false);

	Boolean PageInMem(int pageNum);

	/* Create a new page and fix it in memory.
	Return the buffer page and the new page number.
	Note: Even if there is a gap, this will always return NumPages()+1
	as the next new page. Return NULL is pages size limit is 
	exceeded */
	BufPage *CreatePage(int &pageNum);


	/* Mark page dirty. flush == true if page is to be
	flushed immediately.*/
	void DirtyPage(BufPage *bpage, Boolean flush= false);

	/* Unfix page. Hint tells where to put the page in the buffer.*/
	void UnfixPage(BufPage *bpage, BufHint hint);

	/* Get page number of pages currently in memory.*/
	void PagesInMem(int &num, int *&pages);

	/* File header is data stored witht the file, but not
	inside the pages. It can be used by caller to store
	data such as head of free list of pages, or # of records
	in the file, etc */

	/* Copy file header into given data area */
	void ReadHeader(void *data, int length);

	/* Write page header into page */
	void WriteHeader(void *data, int length);

private:
	DiskFile *_diskFile;
	BufMgr *_mgr;
	PageFileHeader _header;
};
#endif
