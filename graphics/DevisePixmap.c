/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-1995
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
  Revision 1.7  1999/03/01 23:08:58  wenger
  Fixed a number of memory leaks and removed unused code.

  Revision 1.6  1998/12/15 14:54:53  wenger
  Reduced DEVise memory usage in initialization by about 6 MB: eliminated
  Temp.c (had huge global arrays); eliminated Object3D class and greatly
  simplified Map3D; removed ViewLens class (unused); got rid of large static
  buffers in a number of other source files.

  Revision 1.5  1996/10/02 15:23:36  wenger
  Improved error handling (modified a number of places in the code to use
  the DevError class).

  Revision 1.4  1995/12/05 21:55:18  jussi
  Added #include <stdlib.h> to get malloc() prototype.

  Revision 1.3  1995/12/05 20:19:11  jussi
  Added copyright notice and cleaned up the code a bit.

  Revision 1.2  1995/09/05 21:12:38  jussi
  Added/updated CVS header.
*/

#include <stdio.h>
#include <stdlib.h>

#include "Exit.h"
#include "DevisePixmap.h"
#include "DevError.h"

#if 0 // Not used.  RKW 1999-03-01.
PixmapIO::PixmapIO()
{
}

void PixmapIO::SetDecompress(FILE *file)
{
  _compress = false;
  _file = file;
}

void PixmapIO::SetCompress(FILE *file, DevisePixmap *pixmap)
{
  _compress = true;
  _file = file;
  _pixmap = pixmap;
}

/* beginning/ending of encoding */

void PixmapIO::Begin()
{
  if (_compress) {
#ifdef DEBUG
    printf("Begin Compress\n");
#endif
    if (fwrite(_pixmap, sizeof(*_pixmap), 1, _file) != 1) {
      reportErrSys("PixmapIO::WritePixmap");
      Exit::DoExit(1);
    }
#ifdef DEBUG
    printf("PixmapIO::Begin: compressing %d bytes\n", _pixmap->imageBytes);
#endif
  } else {
    /* decompress */
#ifdef DEBUG
    printf("Begin Decompress\n");
#endif
    _pixmap = new DevisePixmap();
    if (fread(_pixmap, sizeof(*_pixmap), 1, _file) != 1) {
      reportErrSys("PixmapIO::LoadPixmap");
    Exit::DoExit(1);
    }
#ifdef DEBUG
    printf("PixmapIO::Begin: allocating %d bytes\n", _pixmap->imageBytes);
#endif
    unsigned char *data = (unsigned char *)malloc(_pixmap->imageBytes);
    if (!data) {
      fprintf(stderr, "PixmapIO::LoadPixmap: no memory\n");
      reportErrNosys("Fatal error");//TEMP -- replace with better message
      Exit::DoExit(1);
    }
    _pixmap->data = data;
  }

  _line = 0;
}

void PixmapIO::End()
{
}

const int PIXMAPIO_BUFSIZE = 5120;
// Note: this buffer must be static.  RKW 1998-12-15.
static char pixBuf[PIXMAPIO_BUFSIZE];

/* Read next line. return NULL if no more */

char *PixmapIO::ReadLine(int &length)
{
#ifdef DEBUG
  printf("ReadLine\n");
#endif
  if (_line == _pixmap->height)
    return NULL;

  char *data;
  if (_compress) {
    data = (char *)&_pixmap->data[_line * _pixmap->bytes_per_line];
    length = _pixmap->bytes_per_line;
  } else {
    int numBytes;
    if (fread(&numBytes, sizeof(numBytes), 1, _file) != 1
	|| numBytes > PIXMAPIO_BUFSIZE) {
      reportErrSys("PixmapIO::LoadPixmap numBytes");
      Exit::DoExit(1);
    }
    if (fread(pixBuf, numBytes, 1, _file) != 1) {
      reportErrSys("PixmapIO::LoadPixmap read data");
      Exit::DoExit(1);
    }
    data = pixBuf;
    length = numBytes;
  }

#ifdef DEBUG
  printf("PixmapIO::ReadLine %d bytes\n", length);
#endif

  return data;
}

/* write line out */

void PixmapIO::WriteLine(char *line, int length)
{
#ifdef DEBUG
  printf("PixmapIO::WriteLine len=%d\n",length);
#endif

  if (_compress) {
    if (fwrite(&length, sizeof(length), 1, _file) != 1) {
      reportErrSys("PixmapIO::WritePixmap numBytes");
      Exit::DoExit(1);
    }
    if (fwrite(line, length, 1, _file) != 1) {
      reportErrSys("PixmapIO::WritePixmap data");
      Exit::DoExit(1);
    }
  } else {
    if (_line == _pixmap->height) {
      fprintf(stderr,"PixmapIO::LoadPixmap: pixmap buf overflow\n");
      reportErrNosys("Fatal error");//TEMP -- replace with better message
      Exit::DoExit(1);
    }
    char *data = (char *)&_pixmap->data[_line * _pixmap->bytes_per_line];
    memcpy(data, line, length);
  }
  _line++;
}

#endif
