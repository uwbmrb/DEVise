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
  $Id$

  $Log$
  Revision 1.3  1997/03/28 16:09:27  wenger
  Added headers to all source files that didn't have them; updated
  solaris, solsparc, and hp dependencies.

  Revision 1.2  1995/09/05 21:13:08  jussi
  Added/update CVS header.
*/

#ifndef TimeStamp_h
#define TimeStamp_h

class TimeStamp {
public:
	static int NextTimeStamp() { return _timeStamp++; }
private:
	static int _timeStamp;
};
#endif
