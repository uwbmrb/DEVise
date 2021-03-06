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
  Declaration of DeviseServer class.

  Note: DeviseServer class currently allows only one client, although
  the client/server library supports multiple clients.  The DeviseServer
  class could be changed to support multiple clients when and if the rest
  of DEVise is changed in such a way that this makes sense.
 */

/*
  $Id$

  $Log$
  Revision 1.14  2008/09/23 19:32:46  wenger
  Changed DispatchedName() to const char *.

  Revision 1.13  2008/09/11 20:55:37  wenger
  A few more compile warning fixes...

  Revision 1.12  2005/12/06 20:03:54  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.11  2003/01/13 19:25:22  wenger
  Merged V1_7b0_br_3 thru V1_7b0_br_4 to trunk.

  Revision 1.10.14.2  2005/09/06 21:20:17  wenger
  Got DEVise to compile with gcc 4.0.1.

  Revision 1.10.14.1  2002/09/02 21:29:33  wenger
  Did a bunch of Purifying -- the biggest change is storing the command
  objects in a HashTable instead of an Htable -- the Htable does a bunch
  of ugly memory copying.

  Revision 1.10  2000/01/13 23:07:07  wenger
  Got DEVise to compile with new (much fussier) compiler (g++ 2.95.2).

  Revision 1.9  1999/11/24 15:44:23  wenger
  Removed (unnecessary) CommandObj class; commands are now logged for the
  monolithic form, not just the client/server form; other command-related
  cleanups; added GUI for playing back command logs.

  Revision 1.8  1998/05/02 09:00:43  taodb
  Added support for JAVA Screen and command logging

  Revision 1.7  1998/02/26 20:48:39  taodb
  Replaced ParseAPI() with Command Object Interface

  Revision 1.6  1998/02/12 17:16:29  wenger
  Merged through collab_br_2; updated version number to 1.5.1.

  Revision 1.5  1998/02/03 23:46:33  wenger
  Fixed a problem Hongyu had with getting GData on socket; fixed bugs
  283 and 285 (resulted from problems in color manager merge);
  conditionaled out some debug output.

  Revision 1.4  1998/02/02 18:26:10  wenger
  Strings file can now be loaded manually; name of strings file is now
  stored in session file; added 'serverExit' command and kill_devised
  script to cleanly kill devised; fixed bug 249; more info is now
  printed for unrecognized commands.

  Revision 1.3  1998/01/30 02:17:00  wenger
  Merged cleanup_1_4_7_br_7 thru cleanup_1_4_7_br_8.

  Revision 1.2.2.1  1998/01/28 22:43:44  taodb
  Added support for group communicatoin

  Revision 1.2  1998/01/07 19:28:57  wenger
  Merged cleanup_1_4_7_br_4 thru cleanup_1_4_7_br_5 (integration of client/
  server library into Devise); updated solaris, sun, linux, and hp
  dependencies.

  Revision 1.1.2.2  1998/01/16 23:41:39  wenger
  Fixed some problems that Tony found with the client/server communication
  and GIF generation; fixed problem that session files specified on the
  command line were still opened by the Tcl code.

  Revision 1.1.2.1  1998/01/07 15:59:43  wenger
  Removed replica cababilities (since this will be replaced by collaboration
  library); integrated cslib into DEVise server; commented out references to
  Layout Manager in Tcl/Tk code; changed Dispatcher to allow the same object
  to be registered and unregistered for different file descriptors (needed
  for multiple clients); added command line argument to specify port that
  server listens on.

 */

#ifndef _DeviseServer_h_
#define _DeviseServer_h_

#include "Server.h"
#include "Control.h"
#include "Dispatcher.h"
#include "CmdDescriptor.h"


class CmdContainer;

class DeviseServer : public Server {
public:
  DeviseServer(const char *name, int image_port, int swt_port, int clnt_port,
	const char* switchname, int maxclients, ControlPanel *control);
  virtual ~DeviseServer();

  virtual const char *DispatchedName() { return "DeviseServer"; }
  virtual void Run();
  virtual void WaitForConnection();
  virtual void CloseClient();
  virtual void CloseImageConnection();


  virtual int CurrentClientFd();
  virtual void RunCmd(int argc, char** argv, CmdDescriptor& cmdDes);

  virtual int NumClients() { return _numClients; }
  virtual void setCurrentClient(ClientID cid){ _currentClient = cid;}
  virtual int getCurrentClient(){ return _currentClient;}
  virtual int WriteImagePort(const void* buf, int nsize);

  virtual int ReturnVal(ClientID cid, u_short flag, const char *result){
	return Server::ReturnVal(cid, flag, 1, &result, false);
  }

  virtual int ReturnVal(u_short flag, const char *result){
	return Server::ReturnVal(_currentClient, flag, 1, &result, false);
  }

  virtual int ReturnVal(int argc, const char * const *argv){
	return Server::ReturnVal(_currentClient, API_ACK , argc, argv, true);
 }	 

  virtual int ReturnVal(int flag, int argc, const char * const *argv,
      bool addBrace){
	return Server::ReturnVal(_currentClient, flag, argc, argv, addBrace);
 }	 

protected:
  virtual void BeginConnection(ClientID clientID);
  virtual void EndConnection(ClientID clientID);

  virtual void ProcessCmd(ClientID,	// process a single client command
      int argc, char **argv);
private:
  ClientID _currentClient;
  ClientID _previousClient;
  ControlPanel *_control;
  DispatcherID *_clientDispIDs;
  CmdContainer *_cmdCont;
};

#endif /* _DeviseServer_h_ */

/*============================================================================*/
