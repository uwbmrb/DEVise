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
  Revision 1.1  1996/04/22 18:01:44  wenger
  First version of "attribute projection" code.  The parser (with
  the exception of instantiating any TData) compiles and runs.

*/

#ifndef ApInit_h
#define ApInit_h

#include "DeviseTypes.h"
#include "BufPolicy.h"

class Init {
public:
  static void DoInit(int &argc, char **argv);
  static Boolean DoPlayback() { return _doPlayback; }
  static char *PlaybackFileName(){ return _playbackFile; }
  
  /* get buffer manager policies.
     bufSize = buffer size, in # of pages
     prefetch: true if prefetch while idling.
     policy : buffer policy to use
     existing: true if pages already in mem should be checked first for
     an incoming query */
  static void BufPolicies(int &bufSize, Boolean &prefetch,
			  BufPolicy::policy &policy, Boolean &existing);
	
  static Boolean SavePopup() { return _savePopup;}
  static Boolean TDataQuery(){ return _tdataQuery; }
  static Boolean ConvertGData() { return _convertGData; }
  static int MaxGDataPages() { return _gdataPages; }
  static Boolean Randomize(){ return _randomize;}
  static Boolean DoAbort() { return _abort; }
  static char *ProgName() { return _progName; }
  static char *QueryProc(){ return _qpName;}

  static char *SessionName() { return _sessionName; }
  static void SetSessionName(char *name) {
    _sessionName = name;
  }

  /* true if windows are iconified when restoring a session */
  static Boolean Iconify() { return _iconify; }

  /* Return name of work directory */
  static char *WorkDir() { return _workDir; }

  /* Return name of Tmp directory */
  static char *TmpDir() { return _tmpDir; }
  
  static Boolean Restore() { return _restore; }
  static long ProgModTime();
  static int PageSize();
  static BufPolicy::policy Policy();
  static Boolean GetXLow(Coord &);
  static Boolean GetYLow(Coord &);
  static Boolean GetXHigh(Coord &);
  static Boolean GetYHigh(Coord &);
  static Boolean ElimOverlap() { return _elimOverlap; }
  
  static Boolean UseSimpleInterpreter() { return _simpleInterpreter; }
  static Boolean PrintTDataAttr() { return _printTDataAttr; }
  static Boolean DispGraphics() { return _dispGraphics; }
  static Boolean BatchRecs() { return _batchRecs; }
  static Boolean PrintViewStat() { return _printViewStat; }
  static Boolean DisplayLogo() { return _dispLogo; }

  /*
     return name of script file to be executed
     after system has become idle
  */
  static char *BatchFile() { return _batchFile; }

private:

  static Boolean _savePopup; /* true if pop-up window should be saved and
				wait for button even to remove it */
  static char *_playbackFile; /* name of the playback file */
  static Boolean _doPlayback;
  static Boolean _prefetch;
  static int _bufferSize;
  static BufPolicy::policy _policy;
  static Boolean _existing;
  static Boolean _tdataQuery;
  static Boolean _convertGData;
  static Boolean _abort;
  static int _gdataPages;
  static char *_progName;	/* name of program */
  static char *_tmpDir;    /* name of temp directory */
  static char *_workDir;    /* name of program */
  static char *_sessionName;
  static Boolean _dispLogo;
  static char *_batchFile;
  static long _progModTime; /* last time program was modified */
  static Boolean _randomize; /* TRUE if TData retrieval is randomized */
  static int _pageSize;
  static Boolean _restore;
  static Boolean _iconify;
  
  static Boolean _hasXLow, _hasYLow, _hasXHigh, _hasYHigh;
  static Coord _xLow, _yLow, _xHigh, _yHigh;
  static char *_qpName;
  static Boolean _simpleInterpreter;
  static Boolean _printTDataAttr;
  static Boolean _elimOverlap;
  static Boolean _dispGraphics;
  static Boolean _batchRecs;
  static Boolean _printViewStat;
};

#endif
