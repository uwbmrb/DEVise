/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2005
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  Header file for DataSourceWeb class.
 */

/*
  $Id$

  $Log$
  Revision 1.4.14.1  2005/09/06 21:20:17  wenger
  Got DEVise to compile with gcc 4.0.1.

  Revision 1.4  2000/01/13 23:07:04  wenger
  Got DEVise to compile with new (much fussier) compiler (g++ 2.95.2).

  Revision 1.3  1996/07/14 20:34:16  jussi
  Rewrote class to fork a process that does all data transfers
  from the Web site.

  Revision 1.2  1996/07/12 19:39:02  jussi
  Web data source uses Timer services.

  Revision 1.1  1996/07/01 19:21:25  jussi
  Initial revision.
*/

#ifndef _DataSourceWeb_h_
#define _DataSourceWeb_h_

#include <sys/types.h>

#include "DataSourceFileStream.h"

class DataSourceWeb : public DataSourceFileStream
{
public:
    DataSourceWeb(char *url, const char *label, char *cache);
    virtual ~DataSourceWeb();

    virtual const char *objectType() { return "DataSourceWeb"; }
    
    virtual DevStatus Open(const char *mode);
    virtual DevStatus Close();

    virtual size_t Fwrite(const char *buf, size_t size, size_t itemCount);
    virtual size_t Write(const char *buf, size_t byteCount);

    virtual int append(void *buf, int recSize);
    
protected:
    virtual DevStatus ChildProc();

    char * _url;              // URL of data source
    pid_t _childPid;          // PID of child process
};

#endif /* _DataSourceWeb_h_ */

/*============================================================================*/
