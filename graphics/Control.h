/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2008
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
  Revision 1.33  2005/12/06 20:02:57  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.32  2003/01/13 19:25:09  wenger
  Merged V1_7b0_br_3 thru V1_7b0_br_4 to trunk.

  Revision 1.31.14.5  2005/09/28 17:14:42  wenger
  Fixed a bunch of possible buffer overflows (sprintfs and
  strcats) in DeviseCommand.C and Dispatcher.c; changed a bunch
  of fprintfs() to reportErr*() so the messages go into the
  debug log; various const-ifying of function arguments.

  Revision 1.31.14.4  2005/09/06 21:20:09  wenger
  Got DEVise to compile with gcc 4.0.1.

  Revision 1.31.14.3  2003/11/05 17:01:41  wenger
  First part of display modes for printing is implemented (view foreground
  and background colors work, haven't done anything for symbol colors yet).

  Revision 1.31.14.2  2002/09/17 23:34:11  wenger
  Fixed a bunch of memory leaks -- especially in DevError::ReportError()!

  Revision 1.31.14.1  2002/09/02 21:29:24  wenger
  Did a bunch of Purifying -- the biggest change is storing the command
  objects in a HashTable instead of an Htable -- the Htable does a bunch
  of ugly memory copying.

  Revision 1.31  2000/01/13 23:06:51  wenger
  Got DEVise to compile with new (much fussier) compiler (g++ 2.95.2).

  Revision 1.30  1999/10/18 15:36:28  wenger
  Window destroy events are handled better (DEVise doesn't crash); messages
  such as window destroy notifications are now passed to the client in
  client/server form.  (Parsing a string into arguments was moved from the
  Session class to the ArgList class.)

  Revision 1.29  1999/10/04 19:36:55  wenger
  Mouse location is displayed in "regular" DEVise.

  Revision 1.28  1999/09/08 20:56:08  wenger
  Removed all Tcl dependencies from the devised (main changes are in the
  Session class); changed version to 1.6.5.

  Revision 1.27  1998/09/22 17:23:39  wenger
  Devised now returns no image data if there are any problems (as per
  request from Hongyu); added a bunch of debug and test code to try to
  diagnose bug 396 (haven't figured it out yet); made some improvements
  to the Dispatcher to make the main loop more reentrant; added some error
  reporting to the xv window grabbing code; improved command-result
  checking code.

  Revision 1.26  1998/08/10 19:08:21  wenger
  Moved command result buffer from DeviseCommand class to ControlPanel
  class -- saves 7 MB of memory!

  Revision 1.25  1998/05/14 18:20:59  wenger
  New protocol for JavaScreen opening sessions works (sending "real" GIF)
  except for the problem of spaces in view and window names.

  Revision 1.24  1998/05/02 09:02:25  taodb
  Added support for command logging
  Added support for registering events with delay

  Revision 1.23  1998/02/02 18:25:53  wenger
  Strings file can now be loaded manually; name of strings file is now
  stored in session file; added 'serverExit' command and kill_devised
  script to cleanly kill devised; fixed bug 249; more info is now
  printed for unrecognized commands.

  Revision 1.22  1998/01/09 20:45:21  wenger
  Merged cleanup_1_4_7_br_5 thru cleanup_1_4_7_br_6; fixed error in
  previous merge.

  Revision 1.21  1998/01/07 19:28:24  wenger
  Merged cleanup_1_4_7_br_4 thru cleanup_1_4_7_br_5 (integration of client/
  server library into Devise); updated solaris, sun, linux, and hp
  dependencies.

  Revision 1.20.2.2  1998/01/09 16:33:48  wenger
  Updated copyright date and version number; minor mods to compile for
  hp and sun; fixed problem with _batchMode flag getting improperly
  reset in the ControlPanel class (prevented using pixmaps instead of
  X windows).

  Revision 1.20.2.1  1998/01/07 15:59:20  wenger
  Removed replica cababilities (since this will be replaced by collaboration
  library); integrated cslib into DEVise server; commented out references to
  Layout Manager in Tcl/Tk code; changed Dispatcher to allow the same object
  to be registered and unregistered for different file descriptors (needed
  for multiple clients); added command line argument to specify port that
  server listens on.

  Revision 1.20  1997/09/23 19:57:27  wenger
  Opening and saving of sessions now working with new scheme of mapping
  automatically creating the appropriate TData.

  Revision 1.19  1997/02/03 19:39:54  ssl
  1) Added a new Layout interface which handles user defined layouts
  2) Added functions to set geometry and remap views as changes in the
     layout editor
  3) Added a function to notify the front end of some change so that it
     can execute a Tcl command
  4) The old TileLayout.[Ch] files still exist but are commented out
     conditionally using #ifdef NEW_LAYOUT

  Revision 1.18  1996/11/20 20:34:51  wenger
  Fixed bugs 062, 073, 074, and 075; added workaround for bug 063; make
  some Makefile improvements so compile works first time; fixed up files
  to correspond to new query catalog name.

  Revision 1.17  1996/09/05 21:31:12  jussi
  Moved DestroySessionData to Control.c.

  Revision 1.16  1996/08/29 22:00:50  guangshu
  Added functions OpenDataChannel and getFd for DEVise Server to open
  data channel and get the fd of that socket.

  Revision 1.15  1996/08/07 19:25:32  jussi
  Added methods which allow query processor to control when
  a synchronization message is sent to client.

  Revision 1.14  1996/08/04 20:57:22  beyer
  Added Raise() method to bring the control panel to the top of the stacking
  order.

  Revision 1.13  1996/07/18 01:19:02  jussi
  DestroySessionData() now resets the _batchMode flag.

  Revision 1.12  1996/05/22 21:03:56  jussi
  ControlPanel::_controlPanel is now set by main program.

  Revision 1.11  1996/05/15 16:43:44  jussi
  Added support for the new server synchronization mechanism.

  Revision 1.10  1996/05/13 21:58:18  jussi
  Moved initialization of _mode to Control.c. Added support
  for changing _batchMode and querying it.

  Revision 1.9  1996/05/13 18:05:38  jussi
  Changed type of "flag" argument to ReturnVal().

  Revision 1.8  1996/05/11 19:10:30  jussi
  Added virtual function prototypes for replica management.

  Revision 1.7  1996/05/11 17:28:45  jussi
  Reorganized the code somewhat in order to match the ParseAPI
  interface.

  Revision 1.6  1996/05/11 03:11:32  jussi
  Removed all unnecessary ControlPanel methods like FileName(),
  FileAlias() etc.

  Revision 1.5  1996/05/09 18:12:02  kmurli
  No change to this makefile.

  Revision 1.4  1996/04/16 19:45:11  jussi
  Added DoAbort() method.

  Revision 1.3  1996/01/27 00:21:45  jussi
  Added ExecuteScript() method.

  Revision 1.2  1995/09/05 21:12:32  jussi
  Added/update CVS header.
*/

#ifndef Control_h
#define Control_h

#include <sys/types.h>

#include "DeviseTypes.h"
#include "VisualArg.h"
#include "DList.h"
#include "ClassDir.h"

class Dispatcher;

struct CPViewList;
class View;

DefinePtrDList(CPViewListList,CPViewList *);

class ClassInfo;

class ControlPanelCallback;
class MapInterpClassInfo;
class GroupDir;

DefinePtrDList(ControlPanelCallbackList ,ControlPanelCallback *);

class DeviseDisplay;

class ControlPanel  {
public:
  enum Mode { DisplayMode, LayoutMode };

  virtual ~ControlPanel();

  void InsertCallback(ControlPanelCallback *callback);
  void DeleteCallback(ControlPanelCallback *callback);
  
  /* Register class with control panel.
     transient == true if it's a transient class to be removed
     when closing a session.*/
  static void RegisterClass(ClassInfo *cInfo, Boolean transient = false);

  /* Make view the current view */
  virtual void SelectView(View *view) = 0;

  /* Show mouse location. */
  virtual void ShowMouseLocation(const char *dataX, const char *dataY) = 0;

  /* Find pointer to instance with given name */
  static void *FindInstance(const char *name) {
    return GetClassDir()->FindInstance(name);
  }

  /* Get/set current mode */
  virtual Mode GetMode() { return _mode; }
  virtual void SetMode(Mode mode) { _mode = mode; }

  /* Set busy status, should be called in pairs. */
  virtual void SetBusy() = 0;
  virtual void SetIdle() = 0;

  /* Get current busy status */
  virtual Boolean IsBusy() = 0;

  /* Start/restart session */
  virtual void StartSession() {}
  virtual void DestroySessionData();
  virtual void RestartSession() {}

  /* Get/set batch mode */
  virtual Boolean GetBatchMode() { return _batchMode; }
  virtual void SetBatchMode(Boolean mode) { _batchMode = mode; }

  /* Set/clear/get sync notify status */
  virtual void SetSyncNotify() { _syncNotify = true; }
  virtual void ClearSyncNotify() { _syncNotify = false; }
  virtual Boolean GetSyncNotify() { return _syncNotify; }
  virtual void SyncNotify() = 0;

  /* Set/clear/get sync allowed status */

  virtual void SetSyncAllowed() { _syncAllowed = true; }
  virtual void ClearSyncAllowed() { _syncAllowed = false; }
  virtual Boolean GetSyncAllowed() { return _syncAllowed; }

  /* Raise the control panel */
  virtual void Raise() = 0;

  /* Miscellaneous Event Handlers to report events to front end*/
  /* Given a script which the frond end can execute -in our case 
   * a Tcl/Tk procedure
   * Note: sending multiple commands separated by newlines in a single
   * call works for monolithic but not client/server! wenger 2003-11-05.
   */
  virtual void NotifyFrontEnd(const char *script) = 0;

  /* Instantiate control panel into display */
  static void InsertDisplay(DeviseDisplay *disp,
			    Coord x = 0.0, Coord y = 0.4, 
			    Coord w = 0.15, Coord h = 0.59) {
    Instance()->SubclassInsertDisplay(disp, x, y, w, h);
  }

  /* Init control panel, before dispatcher starts running.
     Create control panel if not already created.
     Update contronl panel state to reflect current dispatcher
     */
  static void Init() {
    Instance()->SubclassDoInit();
  }

  /* return the one and only instance of control panel */
  static ControlPanel *Instance();

  /* report mode change */
  void ReportModeChange(Mode mode);

  /* quit */
  virtual void DoQuit();

  /* abort */
  virtual void DoAbort(const char *reason) {}

  /* return one or multiple values to caller of API */
  virtual int ReturnVal(u_short flag, const char *result) = 0;
  virtual int ReturnVal(int argc, const char * const *argv) = 0;
  virtual int ReturnVal(int flag, int argc, const char * const *argv,
    bool addBrace)
  {
		return ReturnVal(argc, argv);
  }

  // Find out whether a command value has been returned.
  void SetValueReturned(Boolean valueReturned) {
	_valueReturned = valueReturned; }
  Boolean GetValueReturned() { return _valueReturned; }
  
  /* Get ClassDir info */
  static ClassDir *GetClassDir();
  
  /* Get GroupDir info */
  virtual GroupDir *GetGroupDir() = 0;
  
  /* Get MapInterpClassInfo info */
  virtual MapInterpClassInfo *GetInterpProto() = 0;

  virtual void OpenDataChannel(int port) = 0;
  virtual int getFd() = 0;

  /* Control panel instance */
  static ControlPanel *_controlPanel;

  virtual int NumClients() { return 1; }

protected:
  friend class Dispatcher;
  friend class ControlPanelSimple;

  virtual void SubclassInsertDisplay(DeviseDisplay *disp,
				     Coord x, Coord y, 
				     Coord w, Coord h) = 0;
  virtual void SubclassDoInit() = 0;

  /* helper functions for derived classes */

  /* return */
  void DoReturn();

  /* Change context and reset current view */
  void DoContext() {}

  /* do go/stop */
  void DoGo(Boolean state);

  /* do single step */
  void DoStep();

  /* display symbols or connectors */
  void DoDisplaySymbols(Boolean state) {}
  void DoDisplayConnectors(Boolean state) {}

  /* display/not display axes for current view. */
  void DoDisplayCurrentAxes(Boolean stat) {}
  
  /* display/not display axes for all views in the dispatcher.*/
  void DoDisplayAxes(Boolean stat) {}

  /* change one of the visual filters. 
     on == TRUE means turn on the filter, otherwise, turn off the filter.
     flag is one of: VISUAL_COLOR or VISUAL_PATTERN */
  void ChangeIntVisualFilter(Boolean on, VisualFlag flag,int minVal,
			     int maxVal) {}

  /* change one of the visual filters. 
     on == TRUE means turn on the filter, otherwise, turn off the filter.
     flag is one of: VISUAL_SIZE or VISUAL_ORIENTATION.
     Note: input orientations are in degrees.
     */
  void ChangeFloatVisualFilter(Boolean on, VisualFlag flag,double minVal,
			       double maxVal) {}

  /* scrol current view by the amount proportional to its
     current width.
     0 <= abs(amount) <= 1, amount >0 means scroll right,
     otherwise, scroll left
     */
  void DoScrollX(double amount) {}
  void DoScrollY(double amount) {}

  /* zoom current width by the given amount */
  void DoZoomXY(double amount) {}
  void DoZoomX(double amount) {}
  void DoZoomY(double amount) {}

  /* do initialize before dispatche starts running. This is used
     to get control panel's notion of current dispatcher in synch
     with the dispatchers' notion of current dispatcher.
     Return control panel switched internally to a new current dispatcher */
  Boolean DoInit() { return false; }

  ControlPanel();
  Mode _mode;                    // layout or display mode
  Boolean _batchMode;            // true if we're in batch mode
  Boolean _syncNotify;           // true if sync notify needed
  Boolean _syncAllowed;          // true when qp allowed to synchronize

  Boolean _valueReturned;

private:
  void UpdateNewDispatcher() {}

  static ClassDir *_classDir; 

  ControlPanelCallbackList *_callbacks;
};

class ControlPanelCallback {
public:
  virtual ~ControlPanelCallback() {}
  virtual void ModeChange(ControlPanel::Mode mode) = 0;
};

extern ControlPanel *GetNewControl();

#endif
