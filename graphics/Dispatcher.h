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
  Revision 1.42  2005/12/06 20:03:01  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.41.12.1  2005/09/06 21:20:10  wenger
  Got DEVise to compile with gcc 4.0.1.

  Revision 1.41  2001/01/08 20:32:41  wenger
  Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
  back onto the trunk.

  Revision 1.39.2.1  2000/10/18 20:31:52  wenger
  Merged changes from fixed_bug_616 through link_gui_improvements onto
  the branch.

  Revision 1.40  2000/10/16 16:11:39  wenger
  Link creation GUI now gives a choice of positive or negative record
  links; fixed bug 622 (record link type not saved in session files);
  fixed bug 623 (record link update problem); other link-related cleanups.

  Revision 1.39  1999/12/15 20:03:58  wenger
  Command log now includes information about how many times we went through
  the dispatcher, to try to allow reproducing timing-dependent bugs.

  Revision 1.38  1999/11/19 21:29:15  wenger
  Removed Journal class and related code (no longer works); removed various
  other unused or unnecessary code.

  Revision 1.37  1999/10/12 17:59:26  wenger
  Fixed bug in code for checking if the mouse is on a cursor that caused
  devised to crash with JavaScreen; fixed Dispatcher problem that sometimes
  caused core dump when DEVise is killed with INT signals; WindowRep
  remembers last cursor hit type to avoid changing the mouse cursor unless
  really necessary.

  Revision 1.36  1999/07/19 19:46:32  wenger
  If Devise gets hung, it now detects this and kills itself (mainly for
  the sake of JavaScreen support).

  Revision 1.35  1998/11/24 19:31:19  wenger
  Fixed problem with soil science sessions sometimes locking up the
  JavaScreen by disallowing input from file descriptors while waiting for
  queries to finish; JavaScreen support code now omits sending windows for
  which the print exclusion flag is set (allows "control windows") to not
  be displayed in the JavaScreen.

  Revision 1.34  1998/09/22 17:23:41  wenger
  Devised now returns no image data if there are any problems (as per
  request from Hongyu); added a bunch of debug and test code to try to
  diagnose bug 396 (haven't figured it out yet); made some improvements
  to the Dispatcher to make the main loop more reentrant; added some error
  reporting to the xv window grabbing code; improved command-result
  checking code.

  Revision 1.33  1998/08/28 22:01:09  wenger
  Made Dispatcher::WaitForQueries() function -- improved over earlier
  versions because it also checks the callback list (this fixes bug 367);
  fixed other piled-related JavaScreen support problems; JAVAC_OpenSession
  closes any existing session before opening the new one.

  Revision 1.32  1998/06/23 17:51:37  wenger
  Added client timeout to Devise -- quits if no commands from client
  within specified period.

  Revision 1.31  1998/05/02 09:02:27  taodb
  Added support for command logging
  Added support for registering events with delay

  Revision 1.30  1998/03/10 19:52:34  wenger
  Merged cleanup_1_4_7_br_10 through cleanup_1_4_7_br_11 (fixes callback
  list problems on SGIs).

  Revision 1.29  1998/02/26 00:18:54  zhenhai
  Implementation for spheres and line segments in OpenGL 3D graphics.

  Revision 1.28  1998/01/07 19:28:28  wenger
  Merged cleanup_1_4_7_br_4 thru cleanup_1_4_7_br_5 (integration of client/
  server library into Devise); updated solaris, sun, linux, and hp
  dependencies.

  Revision 1.27.4.2  1998/03/10 17:58:29  wenger
  Changes to Dispatcher and Timer classes to fix problems (excessive
  timer wakes and inconsistent callback lists) on SGIs.

  Revision 1.27.4.1  1998/01/07 15:59:22  wenger
  Removed replica cababilities (since this will be replaced by collaboration
  library); integrated cslib into DEVise server; commented out references to
  Layout Manager in Tcl/Tk code; changed Dispatcher to allow the same object
  to be registered and unregistered for different file descriptors (needed
  for multiple clients); added command line argument to specify port that
  server listens on.

  Revision 1.27  1997/09/05 22:35:57  wenger
  Dispatcher callback requests only generate one callback; added Scheduler;
  added DepMgr (dependency manager); various minor code cleanups.

  Revision 1.26  1997/08/28 18:21:40  wenger
  Eliminated unnecessary include dependencies in Dispatcher.h.

  Revision 1.25  1997/01/11 18:19:08  jussi
  Added handling of severe errors (SIGSEGV etc.).

  Revision 1.24  1996/12/12 22:01:23  jussi
  Cleaned up termination code and added CheckUserInterrupt() method.

  Revision 1.23  1996/08/14 21:22:48  wenger
  Minor dispatcher cleanups, etc.  Fixed release script to release
  statically-linked executables for HP and Sun.

  Revision 1.22  1996/08/07 15:15:19  guangshu
  Add include string.h.

  Revision 1.21  1996/08/04 21:00:41  beyer
  Reorganized and simplified the dispatcher.  Multiple dispatchers are no
  longer allowed.  Inserting and removing callbacks uses one list.

  Revision 1.20  1996/07/29 15:44:36  wenger
  Corrected compile warnings on HP.

  Revision 1.19  1996/07/24 03:36:03  wenger
  Fixed dispatcher to compile for HP.

  Revision 1.18  1996/07/23 19:33:55  beyer
  Changed dispatcher so that pipes are not longer used for callback
  requests from other parts of the code.

  Revision 1.17  1996/06/24 20:04:35  jussi
  Added inclusion of sys/select.h for SOLARIS and AIX.

  Revision 1.16  1996/06/24 19:40:06  jussi
  Cleaned up the code a little.

  Revision 1.15  1996/06/23 20:36:17  jussi
  Minor fix with header files.

  Revision 1.14  1996/06/23 20:31:21  jussi
  Cleaned up marker and pipe mechanism. Moved a couple #defines to
  the .c file so that not all of Devise needs to be recompiled when
  one of them is changed.

  Revision 1.13  1996/06/12 14:55:34  wenger
  Added GUI and some code for saving data to templates; added preliminary
  graphical display of TDatas; you now have the option of closing a session
  in template mode without merging the template into the main data catalog;
  removed some unnecessary interdependencies among include files; updated
  the dependencies for Sun, Solaris, and HP; removed never-accessed code in
  ParseAPI.C.

  Revision 1.12  1996/05/09 18:12:06  kmurli
  No change to this makefile.

  Revision 1.11  1996/04/30 15:58:46  jussi
  Added #ifdef USE_SELECT which can be used to disable the use
  of select(). The display update problem still plagues the
  system when select() is used. The query processor also seems
  slower.

  Revision 1.10  1996/04/20 19:52:07  kmurli
  Changed Viex.c to use a pipe mechanism to call itself if it needs to be
  done again. The view now is not called contiously by the Dispatcher,instead
  only of there is some data in the pipe.
  The pipe mechanism is implemented transparently through static functions
  in the Dispatcher.c (InsertMarker,CreateMarker,CloseMarker,FlushMarker)

  Revision 1.9  1996/04/09 18:56:00  jussi
  Minor change to make this file compile under HP-UX.

  Revision 1.8  1996/04/09 18:04:09  jussi
  Collection of fd's (fdset) now assembled and disassembled in
  Register/Unregister instead of Run1. Callbacks to be deleted
  are first appended to a delete list, and collectively removed
  at the beginning of Run1.

  Revision 1.7  1996/04/08 16:56:14  jussi
  Changed name of DisplaySocketId to more generic 'fd'.

  Revision 1.6  1996/04/04 05:18:26  kmurli
  Major modification: The dispatcher now receives the register command
  from the displays directly (i.e. from XDisplay instead of from
  Display) corrected a bug in call to register function. Also now
  dispatcher uses socket number passed from the XDisplay class to
  select on it and call the relevant functions.

  Revision 1.5  1996/01/27 00:20:31  jussi
  QuitNotify() is now defined in .c file.

  Revision 1.4  1996/01/11 21:57:08  jussi
  Replaced libc.h with stdlib.h.

  Revision 1.3  1995/12/28 18:15:54  jussi
  Added copyright notice and fixed for loop variable scope.

  Revision 1.2  1995/09/05 21:12:42  jussi
  Added/updated CVS header.
*/

#ifndef Dispatcher_h
#define Dispatcher_h

#include <sys/types.h>

#include "DeviseTypes.h"
#include "DList.h"
#include "ObjectValid.h"


class DispatcherCallback {
public:
  virtual ~DispatcherCallback() {}
  virtual const char *DispatchedName() = 0;
  virtual void Run() {}
  virtual void Cleanup() {}
};

typedef unsigned StateFlag;
const unsigned GoState   = 0x1;
const unsigned StopState = 0x2;
const unsigned AllState  = 0xffffffff;

class DispatcherInfo {
protected:
  friend class Dispatcher;
  friend class Scheduler;

  DispatcherCallback *callBack;
  StateFlag flag;		// if flag is zero, this info will be deleted
  int priority;
  int fd;
  long delay;			// delayed callback, using absolute EPOCH time
						// set to 0, if no delay.
  bool callback_requested;
};

/* pointers to the DispatcherInfo are used as identifiers when the
   user registers a callback, but they should not be peeked at! */
typedef DispatcherInfo* DispatcherID;

//class DeviseWindow;
class Dispatcher;
class View;

//DefinePtrDList(DeviseWindowList, DeviseWindow *);
DefinePtrDList(DispatcherInfoList, DispatcherInfo *);


class Dispatcher {
public:
  Dispatcher(StateFlag state = GoState );

  ~Dispatcher();

protected:
  friend class Scheduler;

  /* schedule a callback
     note: it doesn't matter how many times this is called, the callback
     will only be made once & one cancel can kill 10 requests.
     Also, once the callback is made, it will not be made again unless
     the callback reschedules itself.
   */
  void RequestCallback(DispatcherID info);
  void RequestTimedCallback(DispatcherID info, long time);

  /* cancel a scheduled callback */
  void CancelCallback(DispatcherID info);

public:
  /* Register callback */
  DispatcherID Register(DispatcherCallback *c, int priority = 10,
			StateFlag flag = GoState, 
			Boolean ignored = false, // parameter no longer used
			int fd = -1); 
  
  /* Unregister callback */
  void Unregister(DispatcherCallback *c);
  void Unregister(DispatcherID id);

  /* Change the state of the dispatcher */
  void ChangeState(StateFlag flag) { _stateFlag = flag; }

  /* CGet the state of the dispatcher */
  StateFlag GetState() { return _stateFlag; }

  /* Single step */
  void Run1();
  
  /* Print what's in the queue */
  void Print();

  /* Wait for all pending queries to finish */
  void WaitForQueries();

  /* Number of pending callbacks */
  int CallbacksPending();

  /* Check callback list for self-consistency. */
  Boolean CallbacksOk();

  // For HangCheck class to use to try to figure out if DEVise is hung.
  int GetTag() { return _tag; }

  /***********************************************************************
    the following static functions are no longer needed, since there
    is only one dispatcher. I left them here to avoid changing a lot of
    code... KSB
  ***********************************************************************/

  /* Return the current dispatcher */
  static Dispatcher *Current();

  /* Run once, for single step */
  static void SingleStepCurrent();

  /* Run, no return */
  static void RunNoReturn();

  /* Run continuously, but can return after ReturnCurrent() is called. */
  static void RunCurrent();

  /* Return from Run() */
  static void ReturnCurrent();
  
  /* Catch interrupts from the user and terminate program if necessary */
  static void Terminate(int dummy);

  /* Terminate program immediately */
  static void ImmediateTerminate(int dummy);

  /* Cleanup dispatcher */
  static void Cleanup();

  /* Check if user has hit interrupt (Control-C) */
  static void CheckUserInterrupt();

  /***********************************************************************/

  // These functions are for use by the command logging, so the logs can
  // record how many times we went through the dispatcher between
  // commands.
  void ResetRunCount() { _runCount = 0; }
  int GetRunCount() { return _runCount; }
  void SetMaxRunCount(int maxRunCount);

private:

  /* Clean up before quitting */
  void DoCleanup();

  /* process any callbacks that have an fd set in fdread or fdexc,
     or any callbacks that have callback_requested set */
  long ProcessCallbacks(fd_set& fdread, fd_set& fdexc);

  void Unregister(DispatcherCallback *c, DispatcherID id);

  /* Callback list for this dispatcher */
  DispatcherInfoList _callbacks;
  int                _callback_requests;

  StateFlag _stateFlag;
  Boolean _returnFlag;	/* TRUE if we should quit running and return */
  Boolean _firstIntr;	/* Set to true when dispatcher received interrupt */
  Boolean _quit;	/* Set to true when dispatcher should quit */
  
  /* Set of file descriptors to inspect for potential input */
  fd_set _fdset;
  int _maxFdCheck;

  time_t _lastCmdTime;

  int _processingDepth;
  Boolean _waitingForQueries;

  int _tag;

  int _runCount;
  int _maxRunCount;

  ObjectValid _objectValid;
};

#endif
