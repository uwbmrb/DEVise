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
  Declaration of Server class.
 */

/*
  $Id$

  $Log$
  Revision 1.4.14.1  2013/09/20 15:29:13  wenger
  More Centos 6 compile fixes.

  Revision 1.4  2008/10/13 20:03:21  wenger
  Const-ified cslib.

  Revision 1.3  2005/12/06 20:01:21  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.2.28.1  2005/09/28 17:14:28  wenger
  Fixed a bunch of possible buffer overflows (sprintfs and
  strcats) in DeviseCommand.C and Dispatcher.c; changed a bunch
  of fprintfs() to reportErr*() so the messages go into the
  debug log; various const-ifying of function arguments.

  Revision 1.2  1998/01/07 19:27:52  wenger
  Merged cleanup_1_4_7_br_4 thru cleanup_1_4_7_br_5 (integration of client/
  server library into Devise); updated solaris, sun, linux, and hp
  dependencies.

  Revision 1.1.2.3  1998/01/07 15:58:59  wenger
  Removed replica cababilities (since this will be replaced by collaboration
  library); integrated cslib into DEVise server; commented out references to
  Layout Manager in Tcl/Tk code; changed Dispatcher to allow the same object
  to be registered and unregistered for different file descriptors (needed
  for multiple clients); added command line argument to specify port that
  server listens on.

  Revision 1.1.2.2  1997/12/30 16:47:56  wenger
  Removed single-client compile option to simplify the code.

  Revision 1.1.2.1  1997/12/09 19:03:24  wenger
  deviseb now uses client/server library.

 */

#ifndef _Server_h_
#define _Server_h_

#include "ClientAPI.h"

//
// Each Server can serve multiple clients. Client state is stored
// in a ClientInfo object. A Server instance will have an array of
// ClientInfo objects, indexed by ClientID values.
//
class ClientInfo
{
  public:
    ClientInfo()
    : fd(-1), valid(false)
    {}
    int fd;
    bool valid;
};
typedef int ClientID;

class Server {
  public:
    Server(char *name, int port, int maxClients = 10);
    virtual ~Server();
    virtual void MainLoop();              // main loop of server
    virtual void SingleStep();            // once throught the body of MainLoop

    virtual int ReturnVal(		  // send result to client
	ClientID clientID, u_short flag, const char *result) {
	    return ReturnVal(clientID, flag, 1, &result, false); }

    virtual int ReturnVal(		  // send result to client
	ClientID clientID, u_short flag, int argc, const char * const *argv,
	    int addBraces = true);

    virtual int SendControl(		  // send command to all clients
	u_short flag, const char *command) {
	    return SendControl(flag, 1, &command, false); }

    virtual int SendControl(		  // send command to all clients
	u_short flag, int argc, const char * const *argv,
	  int addBraces = true);

  protected:
    virtual void DoAbort(char *reason);   // print error message and abort
    virtual void WaitForConnection();     // wait for client connection
    virtual void ReadCmd();               // read client command

    virtual void GetCmd(int argc,	  // get command from client into _cmd
	char **argv);

    char *_name;                          // name of server
    int _port;                            // port number of server
    int _listenFd;                        // fd of listen socket
    char *_cmd;				  // command from client

  private:
    void InitializeListenFd();             // initialize the fd for listening
    
  protected:
    virtual void BeginConnection(ClientID)
    {}                                     // executed when a connection starts
    virtual void EndConnection(ClientID)
    {}                                     // executed when a connection ends
    virtual void ExecClientCmds(fd_set *); // run incoming client commands
    virtual void ProcessCmd(ClientID,
			    int argc,
			    char **argv);  // process a single client command
    virtual void CloseClient(ClientID);    // close client connection

    ClientInfo *_clients;                  // array of ClientInfo structs
    int _numClients;                       // current number of clients
    int _maxClients;                       // maximum number of clients

  private:
    int FindIdleClientSlot();              // search for slot in client array
};

#endif
