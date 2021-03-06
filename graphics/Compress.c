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
  Revision 1.7  1998/12/15 14:54:53  wenger
  Reduced DEVise memory usage in initialization by about 6 MB: eliminated
  Temp.c (had huge global arrays); eliminated Object3D class and greatly
  simplified Map3D; removed ViewLens class (unused); got rid of large static
  buffers in a number of other source files.

  Revision 1.6  1998/08/17 18:51:41  wenger
  Updated solaris dependencies for egcs; fixed most compile warnings;
  bumped version to 1.5.4.

  Revision 1.5  1995/12/28 18:39:36  jussi
  Minor fixes to remove compiler warnings.

  Revision 1.4  1995/12/14 16:53:50  jussi
  Small fix.

  Revision 1.3  1995/12/05 20:19:45  jussi
  Added copyright notice and cleaned up the code a bit.

  Revision 1.2  1995/09/05 21:12:29  jussi
  Added/updated CVS header.
*/

#include <stdio.h>
#include "Compress.h"
#include "Exit.h"
#include "DevError.h"

static const int COMPRESS_BUF_SIZE = 2048;
// Note: this buffer must be static.  RKW 1998-12-15.
static unsigned char _compressBuf[COMPRESS_BUF_SIZE];

SimpleCompress::SimpleCompress()
{
}

void SimpleCompress::Compress(CompressIO *cio)
{
  char *line;
  int count;

  cio->Begin();
  while ((line = cio->ReadLine(count)) != NULL){
    int outCount;
    char *outBuf = CompressLine(line, count, outCount);
    cio->WriteLine(outBuf, outCount);
  }
  cio->End();
}

void SimpleCompress::Decompress(CompressIO *cio)
{
  char *line;
  int count;

  cio->Begin();
  while ((line = cio->ReadLine(count))!= NULL) {
    int outCount;
    char *outBuf = DecompressLine(line, count, outCount);
    cio->WriteLine(outBuf, outCount);
  }
  cio->End();
}

char *SimpleCompress::CompressLine(char *line, int count, int &outCount)
{
  int outIndex = 0;
  int i = 0;

  while (i < count) {
    int j;
    for(j = i+1; j < count && line[i] == line[j] ; j++);
    /* line[i..j-1] are the same. Write out with run length
       encoding */
    int num = j - i;
    while (num > 0 ) {
      if (outIndex + 1 >= COMPRESS_BUF_SIZE) {
	fprintf(stderr,"SimpleCompress::Compress:buf overflow\n");
    reportErrNosys("Fatal error");//TEMP -- replace with better message
	Exit::DoExit(1);
      }
      int amount = num;
      if (amount > 255) amount = 255;
      _compressBuf[outIndex++] = (unsigned char)amount;
      _compressBuf[outIndex++] = (unsigned char)line[i];
      num -= amount;
    }
    i = j;
  }

  outCount = outIndex;
  return (char *)_compressBuf;
}

char *SimpleCompress::DecompressLine(char *line, int count, int &outCount)
{
  if (count & 1) {
    /* count should be odd */
    fprintf(stderr, "SimpleCompress::DecompressLine: error in input\n");
    reportErrNosys("Fatal error");//TEMP -- replace with better message
    Exit::DoExit(2);
  }
  
  int outIndex = 0;
  for(int i = 0; i < count; i += 2) {
    unsigned int num = (unsigned char)line[i];
    unsigned char c = (unsigned char)line[i + 1];
    if (outIndex + num > (unsigned int)COMPRESS_BUF_SIZE){
      fprintf(stderr, "SimpleCompress::Decompress:buf overflow %d\n",
	      outIndex + num);
      reportErrNosys("Fatal error");//TEMP -- replace with better message
      Exit::DoExit(1);
    }
    for(unsigned int j = 0; j < num; j++) {
      _compressBuf[outIndex++] = c;
    }
  }

  outCount = outIndex;
  return (char *)_compressBuf;
}
