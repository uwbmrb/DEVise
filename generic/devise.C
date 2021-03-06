/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2013
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
  Revision 1.27  2013/09/20 16:53:57  wenger
  Merged devise_1_11_3_centos6_br_2 thru devise_1_11_3_centos6_br_3 to trunk.

  Revision 1.26  2013/06/13 22:03:04  wenger
  Merged devise_1_11_3_centos6_br_0 thru devise_1_11_3_centos6_br_2 to trunk.

  Revision 1.25.2.2  2013/06/14 14:49:21  wenger
  More cleanups from CentOS6 compile...

  Revision 1.25.2.1  2013/06/13 21:02:47  wenger
  Changes to get DEVise to compile/link on CentOS6 (with comments for
  a bunch of unfixed warnings); minor mods to get this version to also
  compile on RHEL5...

  Revision 1.25  2013/02/08 23:09:28  wenger
  Changed a bunch more sprintfs to snprintfs; fixed errors in the
  error return in JavaScreenCmd; added provision for other parts of
  the DEVise code to "register" errors in JavaScreenCmd (if they can't
  return an error code up the call stack) -- MappingInterp now uses
  this functionality.  Working on sprintf->snprintf conversion in
  GDataSock (not finished).

  Revision 1.24.12.1  2014/01/17 21:46:12  wenger
  Fixed a bunch of possible buffer overflows.

  Revision 1.24  2005/12/06 20:02:51  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.23.12.3  2005/09/28 17:14:36  wenger
  Fixed a bunch of possible buffer overflows (sprintfs and
  strcats) in DeviseCommand.C and Dispatcher.c; changed a bunch
  of fprintfs() to reportErr*() so the messages go into the
  debug log; various const-ifying of function arguments.

  Revision 1.23.12.2  2005/09/12 19:42:02  wenger
  Got DEVise to compile on basslet.bmrb.wisc.edu (AMD 64/gcc
  4.0.1).

  Revision 1.23.12.1  2003/12/19 18:07:22  wenger
  Merged redhat9_br_0 thru redhat9_br_1 to V1_7b0_br.

  Revision 1.23.30.1  2003/12/17 00:17:54  wenger
  Merged gcc3_br_1 thru gcc3_br_2 to redhat9_br (just fixed conflicts,
  didn't actually get it to work).

  Revision 1.23.28.1  2003/12/16 16:08:10  wenger
  Got DEVise to compile with gcc 3.2.3 (with lots of deprecated-header
  warnings).  It runs on RedHat 7.2, but not on Solaris 2.8 (some kind
  of dynamic library problem).

  Revision 1.23  2001/01/08 20:32:34  wenger
  Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
  back onto the trunk.

  Revision 1.21.2.1  2000/09/01 18:26:34  wenger
  Merged changes from js_cgi_base to fixed_bug_616 onto the branch.

  Revision 1.22  2000/09/01 17:33:14  wenger
  Fixed bug 616 (problem with socket-reading code causing heavy CPU usage
  in certain cases).

  Revision 1.21  2000/03/23 20:34:27  wenger
  Updated dependencies, got everything to compile on pumori (Linux 2.2.12,
  g++ 2.95.2).

  Revision 1.20  1999/11/30 22:27:52  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.19  1999/07/12 19:01:58  wenger
  Got DEVise to compile and run again on Linux (including Tcl/Tk 8.0).

  Revision 1.18  1998/02/12 17:15:46  wenger
  Merged through collab_br_2; updated version number to 1.5.1.

  Revision 1.17  1998/01/30 02:16:32  wenger
  Merged cleanup_1_4_7_br_7 thru cleanup_1_4_7_br_8.

  Revision 1.16.2.2  1998/02/12 05:19:11  taodb
  Updated dependency list

  Revision 1.16.2.1  1998/01/28 22:43:19  taodb
  Added support for group communicatoin

  Revision 1.16  1998/01/07 19:28:17  wenger
  Merged cleanup_1_4_7_br_4 thru cleanup_1_4_7_br_5 (integration of client/
  server library into Devise); updated solaris, sun, linux, and hp
  dependencies.

  Revision 1.15  1997/12/16 18:02:04  zhenhai
  Added OpenGL features.

  Revision 1.14.16.5  1998/01/20 18:38:49  wenger
  Fixed compile on SGI.

  Revision 1.14.16.4  1998/01/16 23:41:13  wenger
  Fixed some problems that Tony found with the client/server communication
  and GIF generation; fixed problem that session files specified on the
  command line were still opened by the Tcl code.

  Revision 1.14.16.3  1998/01/07 15:59:10  wenger
  Removed replica cababilities (since this will be replaced by collaboration
  library); integrated cslib into DEVise server; commented out references to
  Layout Manager in Tcl/Tk code; changed Dispatcher to allow the same object
  to be registered and unregistered for different file descriptors (needed
  for multiple clients); added command line argument to specify port that
  server listens on.

  Revision 1.14.16.2  1997/12/09 19:03:37  wenger
  deviseb now uses client/server library.

  Revision 1.14.16.1  1997/12/09 16:03:38  wenger
  Devise client now uses client/server library.

  Revision 1.14  1996/09/05 21:33:11  jussi
  Devise command 'connectData' was renamed getDisplayImage.
  Minor other improvements.

  Revision 1.13  1996/08/29 21:43:39  guangshu
  Added Tcl command SetGetImage to set up data channel then ask server
  to ship the gif files. The gif files can be either put to stdout,
  stderr or saved to files.
  Added -q option for DEVise client to make it quiet. So the gif files
  can be sent to web browser directly.

  Revision 1.12  1996/07/15 14:22:38  jussi
  This code is now compatible with Tcl 7.5 and Tk 4.1. Compatibility
  with older Tcl/Tk code maintained for a short while.

  Revision 1.11  1996/07/11 19:38:27  jussi
  The Tcl variable 'file' is set to the name of the session file
  before the session file is executed. Exported session files
  with data use the 'file' variable.'

  Revision 1.10  1996/07/11 18:18:04  jussi
  In batch mode, the Tcl client no longer uses any Tk or X11 features.
  The client operates in batch mode when an idle script is specified.
  The idle script is interpreted with Tcl. Tk is not needed.

  Revision 1.9  1996/07/09 15:59:36  wenger
  Added master version number and compile date to C++ code (also displayed
  in the user interface); added -usage and -version command line arguments;
  updated usage message.

  Revision 1.8  1996/05/20 18:46:36  jussi
  Merged with ClientServer library code.

  Revision 1.7  1996/05/15 16:40:01  jussi
  Improved support for idle scripts; the client now uses the
  new server synchronization mechanism.

  Revision 1.6  1996/05/14 19:06:28  jussi
  Added checking of return value from DeviseOpen().

  Revision 1.5  1996/05/14 15:08:34  jussi
  Added support for idle scripts, that is, scripts which are
  executed when the server becomes idle. Typically this means
  that the server has drawn all views and they are ready to
  be extracted as images.

  Revision 1.4  1996/05/13 18:08:17  jussi
  The code now accepts API_CTL type messages in between API_CMD
  and API_ACK/API_NAK messages. Control channel was merged with
  the regular socket pair.

  Revision 1.3  1996/05/11 21:30:01  jussi
  Fixed problem with interp->result overrun.

  Revision 1.2  1996/05/11 17:23:14  jussi
  Added command line options for setting host name and port number.

  Revision 1.1  1996/05/11 01:52:02  jussi
  Initial revision.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <tcl.h>
#include <tk.h>
#include <sys/param.h>

#include "ClientAPI.h"
#include "DeviseClient.h"
#include "Version.h"
#include "Util.h"

// Because we can't call Exit::DoAbort() here...
#if defined(DOASSERT)
#  undef DOASSERT
#endif
#ifdef DOASSERT
#  undef DOASSERT
#endif
#define  DOASSERT(c,r) {if (!(c)) DoAbort(r); } 
#undef	DEBUG

static char *_progName = 0;
static const char *_hostName = "localhost";
static int _portNum = DefaultNetworkPort;
static DeviseClient *_client;
static int _dataFd = -1;
static int _dataNewFd = -1;
static int _quiet = 0;

static char *_idleScript = 0;

static char *_restoreFile = 0;

int _useopengl = 0;

static void DoAbort(const char *reason)
{
    fprintf(stderr, "An internal error has occurred. Reason:\n  %s\n", reason);
    char cmd[256];
    int formatted = snprintf(cmd, sizeof(cmd), "AbortProgram {%s}", reason);
    //TEMP checkAndTermBuf2(cmd, formatted);
    (void) _client->EvalCmd(cmd);
    delete _client;
    exit(1);
}

int DEViseCmd(ClientData clientData, Tcl_Interp *interp,
	      int argc,
#if TCL_MAJOR_VERSION > 8 || (TCL_MAJOR_VERSION == 8 && TCL_MINOR_VERSION > 3)
	      const
#endif
	      char *argv[])
{
#ifdef DEBUG	
    printf("Function %s, %d args\n", argv[1], argc - 1);
#endif

    // do not send the DEVise command verb
    return _client->ServerCmd(argc - 1, &argv[1]);
}

int SetGetImage(ClientData clientData, Tcl_Interp *interp,
                int argc,
#if TCL_MAJOR_VERSION > 8 || (TCL_MAJOR_VERSION == 8 && TCL_MINOR_VERSION > 3)
		const
#endif
		char *argv[]) 
{ 
   _dataFd = socket(AF_INET, SOCK_STREAM, 0);
   if(_dataFd < 0) 
      perror("socket");
   DOASSERT(_dataFd >= 0, "Cannot create socket");

   struct sockaddr_in dataAddr;
   memset(&dataAddr, 0, sizeof dataAddr);
   dataAddr.sin_family = AF_INET;

   dataAddr.sin_port = htons(DefaultDataPort);
#ifdef DEBUG
   printf("Client Listening at port%u.\n", DefaultDataPort);
#endif

   dataAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   
   int result = bind(_dataFd, (struct sockaddr *)&dataAddr,
			sizeof(struct sockaddr));
   if (result < 0) {
       perror("bind");
       close(_dataFd);
   }
   DOASSERT(result >= 0, "Cannot bind to address");

   result = listen(_dataFd, 1);
   if (result < 0) {
       perror("listen");
       close(_dataFd);
   }
   DOASSERT(result >= 0, "Cannot listen");

#ifdef DEBUG
   printf("\nData client waiting for server to connect\n");
#endif

   const char *mArgv[3] = { "getDisplayImage", "0", argv[1] };
   // Note: this bypasses the client/server library.  RKW Jan. 6, 1998.
   if (NetworkSend(_client->ServerFd(), API_CMD, 0, 3, mArgv) < 0) {
       fprintf(stderr, "Server has terminated. Client exits.\n");
       close(_dataFd);
       exit(1);
   }

   struct sockaddr_in servAddr;
   memset(&servAddr, 0, sizeof(struct sockaddr));
#if defined(LINUX) || defined(SOLARIS)
   socklen_t
#else
   int
#endif
       len = sizeof(servAddr);

#ifdef DEBUG
   printf("Waiting for server to connect data channnel.\n");
#endif
   do {
      _dataNewFd = accept(_dataFd, (struct sockaddr *)&servAddr, &len);
   } while (_dataNewFd < 0 && errno == EINTR);

   close(_dataFd);

   if (_dataNewFd < 0) {
      perror("data accept");
      close(_dataFd);
      DOASSERT(0, "Error in network interface when connecting data channel");
   }
#ifdef DEBUG
   printf("Data channel established.\n");
#endif
   
   int file;
   if (!strcmp(argv[2], "stderr"))
       file = 2;
   else if(!strcmp(argv[2],"stdout"))
       file = 1; 
   else
       file = open(argv[2], O_WRONLY | O_CREAT, 0644);

   if (file < 0) {
     perror("Can't open image file");
   } else {
     char buf[BUF_SIZE];

     do {
        result = read(_dataNewFd, buf, BUF_SIZE);
#ifdef DEBUG
        printf("Client got data %s\n", buf);
#endif
        if (result > 0) write(file, buf, result);
     } while (result > 0);

     close(file);
   }
   close(_dataNewFd);

   if (result < 0) {
      perror("Read error when read data from the data channel.\n");
      return TCL_ERROR;
   }
#ifdef DEBUG
   printf("Done getting GIF file");
#endif

   u_short flag;
   int rargc;
   char **rargv;
   do {
     // Note: this bypasses the client/server library.  RKW Jan. 6, 1998.
     if (NetworkReceive(_client->ServerFd(), 1, flag, rargc, rargv, 10) <= 0) {
         fprintf(stderr, "Server has terminated. Client exits.\n");
         exit(1);
     }
     if (flag == API_CTL)
         _client->ControlCmd(rargc, rargv);
   } while (flag != API_ACK && flag != API_NAK);
    
   char *res = NetworkPaste(rargc, rargv);
   DOASSERT(res, "Out of memory");
#ifdef DEBUG
   printf("Received reply: \"%s\"\n", res);
#endif
   Tcl_SetResult(_client->Interp(), res, TCL_VOLATILE);
   delete res;
    
   if (flag == API_NAK)
     return TCL_ERROR;
   
   return TCL_OK;
}

void
ReadServer(ClientData cd, int mask)
{
#ifdef DEBUG
    printf("Receiving command from server\n");
#endif
    
  _client->ReadServer();
}

void SetupConnection()
{
    if(!_quiet) {
      Version::PrintInfo();
      printf("\n");
    }

    _client = new DeviseClient("DEVise", _hostName, _portNum, !_idleScript, 
		"NULL");

    Tcl_LinkVar(_client->Interp(), "argv0", (char *)&_progName,
	TCL_LINK_STRING);
    Tcl_LinkVar(_client->Interp(), "quiet", (char *)&_quiet, TCL_LINK_INT);
    Tcl_CreateCommand(_client->Interp(), "DEVise", DEViseCmd, 0, 0);
    Tcl_CreateCommand(_client->Interp(), "DEViseGetImage", SetGetImage, 0, 0);
    
    if(!_quiet) {
	 printf("Client running.\n");
         printf("\n");
    }
    
    if(!_quiet) printf("Connecting to server %s:%d.\n", _hostName, _portNum);
    
    if (!_idleScript) {
#if TK_MAJOR_VERSION == 4
#  if TK_MINOR_VERSION == 0
        Tk_CreateFileHandler(_client->ServerFd(), TK_READABLE, ReadServer, 0);
#  else
        Tcl_CreateFileHandler(Tcl_GetFile((void *)_client->ServerFd(),
	    TCL_UNIX_FD), TCL_READABLE, ReadServer, 0);
#  endif
#else
        Tcl_CreateFileHandler(_client->ServerFd(), TCL_READABLE,
	    ReadServer, 0);
#endif
    }
    
    if(!_quiet) printf("Connection established.\n\n");
    
    const char *controlFile = "groupcontrol.tk";
    if (_idleScript) {
        controlFile = "batch.tcl";
        //TEMP -- get rid of cast
        (void) _client->EvalCmd((char *)"DEVise setBatchMode 1");
    }
    
    char *envPath = getenv("DEVISE_LIB");
    const char *control;
    char buf[256];
    if (envPath) {
        int formatted = snprintf(buf, sizeof(buf), "%s/%s", envPath,
	  controlFile);
    	//TEMP checkAndTermBuf2(buf, formatted);
        control = buf;
    } else {
        control = controlFile;
    }
    
    if(!_quiet) printf("Control panel file is: %s\n", control);
    
#if TCL_MAJOR_VERSION > 8 || (TCL_MAJOR_VERSION == 8 && TCL_MINOR_VERSION > 4)
    int code = Tcl_EvalFile(_client->Interp(), control);
#else
    int code = Tcl_EvalFile(_client->Interp(), (char *)control);
#endif
    if (code != TCL_OK) {
        fprintf(stderr, "Cannot start up control panel.\n");
        fprintf(stderr, "%s\n", _client->Interp()->result);
        exit(1);
    }
    
    if (_restoreFile) {
        if(!_quiet) printf("Restoring session file %s\n", _restoreFile);
        char buf[MAXPATHLEN + 256];
        int formatted = snprintf(buf, sizeof(buf),
	  "DEVise openSession %s", _restoreFile);
    	//TEMP checkAndTermBuf2(buf, formatted);
        int code = Tcl_Eval(_client->Interp(), buf);
        if (code != TCL_OK) {
            fprintf(stderr, "Cannot restore session file %s\n", _restoreFile);
            fprintf(stderr, "%s\n", _client->Interp()->result);
        } else {
            Tcl_SetVar(_client->Interp(), "sessionName", _restoreFile, 0);
        }
    }
}

void Usage()
{
    fprintf(stderr, "Usage: %s [-h host] [-p port] [session] [idlescript]\n",
            _progName);
}

int main(int argc, char **argv)
{
    _progName = argv[0];

    for(int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            if (i + 1 >= argc) {
                fprintf(stderr, "No host name specified with -h option.\n");
                Usage();
                exit(1);
            }
            _hostName = argv[i + 1];
            i++;
        } else if (!strcmp(argv[i], "-p")) {
            if (i + 1 >= argc) {
                fprintf(stderr, "No port number specified with -p option.\n");
                Usage();
                exit(1);
            }
            _portNum = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(argv[i], "-q")) {
	    _quiet = 1;
//	    i ++;
	} else if (!strcmp(argv[i], "-gl")) {
            _useopengl=1;
        }
	else {
            if (!_restoreFile)
                _restoreFile = argv[i];
            else if(!_idleScript)
                _idleScript = argv[i];
            else {
                Usage();
                exit(1);
            }
        }
    }

    SetupConnection();

    if (_idleScript) {
        if (!_quiet) printf("Waiting for server synchronization.\n");
        //TEMP -- get rid of cast
        (void) _client->EvalCmd((char *)"DEVise sync");
        while(!_client->SyncDone()) {
	    _client->ReadServer();
        }
        if (!_quiet) printf("Executing batch file %s\n", _idleScript);
        int code = Tcl_EvalFile(_client->Interp(), _idleScript);
        if (code != TCL_OK) {
            fprintf(stderr, "Cannot execute script file %s\n", _idleScript);
            fprintf(stderr, "%s\n", _client->Interp()->result);
	    delete _client;
	    _client = NULL;
            return 2;
        }
    } else {
	_client->MainLoop();
    }
    
    if (!_idleScript) {
#if TK_MAJOR_VERSION == 4
#  if TK_MINOR_VERSION == 0
        Tk_DeleteFileHandler(_client->ServerFd());
#  else
        Tcl_DeleteFileHandler(Tcl_GetFile((void *)_client->ServerFd(),
	    TCL_UNIX_FD));
#  endif
#else
        Tcl_DeleteFileHandler(_client->ServerFd());
#endif
    }

    delete _client;
    _client = NULL;
    
    return 1;
}
