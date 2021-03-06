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
  $Id$

  $Log$
  Revision 1.3.46.1  2005/09/06 21:20:17  wenger
  Got DEVise to compile with gcc 4.0.1.

  Revision 1.3  1996/05/31 15:40:36  jussi
  Cleaned up a bit. Added copyright notice.

  Revision 1.2  1995/09/05 22:14:43  jussi
  Added CVS header.
*/

/* supports page read/write operations */

#ifndef DiskFile_h
#define DiskFile_h

#include "DeviseTypes.h"

class DiskFile {
public:
  virtual ~DiskFile() {}

  /* Create a new file. Return NULL if file already exists */
  static DiskFile *CreateFile(char *name);

  /* Open an existing file. Return NULL if file does not exist */
  static DiskFile *OpenFile(char *name);

  /* Get data for this page and put it into buffer.
     If page does not already exist, return random data */
  virtual void ReadPage(int pageNum, void *buf) = 0;

  /* Write this page onto disk.*/
  virtual void WritePage(int pageNum, void *buf) = 0;
};

#endif
