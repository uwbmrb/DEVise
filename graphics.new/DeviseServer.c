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
  Implementation of DeviseServer class.
 */

/*
  $Id$

  $Log$
  Revision 1.2  1998/01/07 19:28:56  wenger
  Merged cleanup_1_4_7_br_4 thru cleanup_1_4_7_br_5 (integration of client/
  server library into Devise); updated solaris, sun, linux, and hp
  dependencies.

  Revision 1.1.2.2  1998/01/16 23:41:38  wenger
  Fixed some problems that Tony found with the client/server communication
  and GIF generation; fixed problem that session files specified on the
  command line were still opened by the Tcl code.

  Revision 1.1.2.1  1998/01/07 15:59:42  wenger
  Removed replica cababilities (since this will be replaced by collaboration
  library); integrated cslib into DEVise server; commented out references to
  Layout Manager in Tcl/Tk code; changed Dispatcher to allow the same object
  to be registered and unregistered for different file descriptors (needed
  for multiple clients); added command line argument to specify port that
  server listens on.

 */

#include <stdio.h>
#include <stdlib.h>

#include "DeviseServer.h"
#include "DevError.h"
#include "Scheduler.h"

//#define DEBUG

/*------------------------------------------------------------------------------
 * function: DeviseServer::DeviseServer
 * Constructor.
 */
DeviseServer::DeviseServer(char *name, int port, ControlPanel *control) :
  Server(name, port, 10)
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::DeviseServer(%s, %d)\n", this, name, port);
#endif

  _currentClient = CLIENT_INVALID;
  _previousClient = CLIENT_INVALID;
  _control = control;

  _clientDispIDs = new DispatcherID[_maxClients];
  int client;
  for (client = 0; client < _maxClients; client++) {
    _clientDispIDs[client] = NULL;
  }

  // Note: we have to do WaitForConnection(), or _listenFd isn't valid.
  WaitForConnection();
  (void) Dispatcher::Current()->Register(this, 10, AllState, true, _listenFd);
}

/*------------------------------------------------------------------------------
 * function: DeviseServer::~DeviseServer
 * Destructor.
 */
DeviseServer::~DeviseServer()
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::~DeviseServer()\n", this);
#endif

  int client;
  for (client = 0; client < _maxClients; client++) {
    if (_clientDispIDs[client] != NULL) {
      Dispatcher::Current()->Unregister(_clientDispIDs[client]);
    }
  }

  delete [] _clientDispIDs;

  Dispatcher::Current()->Unregister(this);
}

/*------------------------------------------------------------------------------
 * function: DeviseServer::Run
 * Called by Dispatcher when there is something for this object to do
 * (a command from a client).
 */
void
DeviseServer::Run()
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::Run()\n", this);
#endif

  if (_numClients < 1) {
    WaitForConnection();
    if (_numClients < 1) {
    }
  } else {
    // Note: SingleStep() receives a command and/or sets up a new connection.
    SingleStep();
  }
}

/*------------------------------------------------------------------------------
 * function: DeviseServer::WaitForConnection
 * Waits for a client connection.
 */
void
DeviseServer::WaitForConnection()
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::WaitForConnection()\n", this);
#endif

  Server::WaitForConnection();
}


/*------------------------------------------------------------------------------
 * function: DeviseServer::CloseClient
 * Closes a client connection (of the current client or the one that
 * most recently executed a command).
 */
void
DeviseServer::CloseClient()
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::CloseClient()\n", this);
#endif

  if (_currentClient != CLIENT_INVALID) {
    Server::CloseClient(_currentClient);
  } else if (_previousClient != CLIENT_INVALID) {
    Server::CloseClient(_previousClient);
  } else {
    reportErrNosys("No client to close");
  }
}

/*------------------------------------------------------------------------------
 * function: DeviseServer::BeginConnection
 * Begin the connection for a given client.
 */
void
DeviseServer::BeginConnection(ClientID clientID)
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::BeginConnection(%d)\n", this, clientID);
#endif

  // Register with the dispatcher to get called when anything comes in on
  // the appropriate file descriptor.
  _clientDispIDs[clientID] = Dispatcher::Current()->Register(this, 10, AllState,
      true, _clients[clientID].fd);
}

/*------------------------------------------------------------------------------
 * function: DeviseServer::EndConnection
 * End the connection for a given client.
 */
void
DeviseServer::EndConnection(ClientID clientID)
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::EndConnection(%d)\n", this, clientID);
  printf("  _numClients = %d\n", _numClients);
#endif

  // We need to unregister by DispatcherID rather than by the address of
  // this object, because we may have registered this object for more than
  // one file descriptor.
  Dispatcher::Current()->Unregister(_clientDispIDs[clientID]);
  _clientDispIDs[clientID] = NULL;

  // Note: Server class decrements _numClients *after* this function is
  // called.
  if (_numClients <= 1) {
    ControlPanel::Instance()->DestroySessionData();
  }

  if (_currentClient == clientID) _currentClient = CLIENT_INVALID;
  if (_previousClient == clientID) _previousClient = CLIENT_INVALID;
}

/*------------------------------------------------------------------------------
 * function: DeviseServer::ProcessCmd
 * Process a command from a client.
 */
void
DeviseServer::ProcessCmd(ClientID clientID, int argc, char **argv)
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::ProcessCmd(%d)\n", this, clientID);
  printf("  Command: ");
  for (int num = 0; num < argc; num++) {
    printf("<%s> ", argv[num]);
  }
  printf("\n");
#endif

#if defined(DEBUG)
  printf("  _currentClient = %d\n", _currentClient);
#endif

  if (_currentClient == CLIENT_INVALID) {
    // Not currently processing a command.
    _currentClient = clientID;
#if defined(DEBUG)
  printf("  Before ParseAPI(): _currentClient = %d\n", _currentClient);
#endif

    if (ParseAPI(argc, argv, _control) < 0) {
      char errBuf[1024];
      sprintf(errBuf, "Devise API command error (command %s).", argv[0]);
      reportErrNosys(errBuf);
    }
  } else {
    // Currently processing another command.
    reportErrNosys("Command while server is busy");
    (void) Server::ReturnVal(clientID, API_NAK, "Server is busy");
  }

#if defined(DEBUG)
  printf("  After ParseAPI(): _currentClient = %d\n", _currentClient);
#endif
}

/*------------------------------------------------------------------------------
 * function: DeviseServer::ReturnVal
 * Return command value to the proper client.
 */
int
DeviseServer::ReturnVal(u_short flag, int argc, char **argv, Boolean addBraces)
{
#if defined(DEBUG)
  printf("DeviseServer(0x%p)::ReturnVal()\n", this);
#endif

  int status;

  if (_currentClient != CLIENT_INVALID) {
    status = Server::ReturnVal(_currentClient, flag, argc, argv, addBraces);
    _previousClient = _currentClient; // For CloseClient().
    _currentClient = CLIENT_INVALID;
  } else {
    reportErrNosys("No current client");
    status = -1;
  }

#if defined(DEBUG)
  printf("  _currentClient = %d\n", _currentClient);
#endif

  return status;
}

/*============================================================================*/
