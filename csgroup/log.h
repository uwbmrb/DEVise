/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-1997
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  Implementation of Client (and CompDate) classes.
 */

/*
  $Id$

  $Log$
  Revision 1.1.2.2  1998/02/02 08:24:01  liping
  Added CVS header

*/

/* Code lifted from Condor Source */
#ifndef _LOG_H
#define _LOG_H

/* This defines a base class for "logs" of operations.  These logs indicate
   operations which have been performed on a data structure (for example
   the job queue), and the log can be "replayed" to recreate the state of
   the data structure.
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

class LogRecord {
public:
	
	LogRecord();
	virtual ~LogRecord();
	LogRecord *get_next() { return next; }
	int get_op_type() { return op_type; }

	int Write(int fd);
/*	int Write(XDR *); */
	int Write(FILE *fp);

	int Read(int fd);
/*	int Read(XDR *); */
	int Read(FILE *fp);
	int ReadHeader(int fd);
/*	int ReadHeader(XDR *); */
	int ReadHeader(FILE *fp);
	virtual int ReadBody(int fd) { if (fd >= 0) return 0; else return -1;}
/*	virtual int ReadBody(XDR *xdrs) { return WriteBody(xdrs); } */
	virtual int ReadBody(FILE *fp) { if (fp != NULL) return 0; else return -1;}
	int ReadTail(int fd);
/*	int ReadTail(XDR *); */
	int ReadTail(FILE *fp);

	virtual int Play() { return 0; }

protected:
	int readstring(int, char *&);
	int readstring(FILE *fp, char *&);
	int op_type;	/* This is the type of operation being performed */
	int body_size;

private:
	WriteHeader(int fd);
	virtual WriteBody(int fd) { if (fd >= 0) return 0; else return -1; }
	WriteTail(int fd);

/*	WriteHeader(XDR *);
	virtual WriteBody(XDR *) {}
	WriteTail(XDR *); */

	WriteHeader(FILE *fp);
	virtual WriteBody(FILE *fp) { if (fp != NULL) return 0; else return -1; }
	WriteTail(FILE *fp);

	LogRecord *next;
	LogRecord *prev;
};

LogRecord *ReadLogEntry(int fd);
LogRecord *InstantiateLogEntry(int fd, int type);

LogRecord *ReadLogEntry(FILE *fp);
LogRecord *InstantiateLogEntry(FILE *fp, int type);
#endif
