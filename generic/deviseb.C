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
  Revision 1.15  2013/09/20 16:53:57  wenger
  Merged devise_1_11_3_centos6_br_2 thru devise_1_11_3_centos6_br_3 to trunk.

  Revision 1.14  2013/06/13 22:03:04  wenger
  Merged devise_1_11_3_centos6_br_0 thru devise_1_11_3_centos6_br_2 to trunk.

  Revision 1.13.56.2  2013/09/20 15:29:20  wenger
  More Centos 6 compile fixes.

  Revision 1.13.56.1  2013/06/13 21:02:47  wenger
  Changes to get DEVise to compile/link on CentOS6 (with comments for
  a bunch of unfixed warnings); minor mods to get this version to also
  compile on RHEL5...

  Revision 1.13.46.1  2014/01/17 21:46:12  wenger
  Fixed a bunch of possible buffer overflows.

  Revision 1.13  1999/11/30 22:27:53  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.12  1998/01/07 19:28:17  wenger
  Merged cleanup_1_4_7_br_4 thru cleanup_1_4_7_br_5 (integration of client/
  server library into Devise); updated solaris, sun, linux, and hp
  dependencies.

  Revision 1.11.16.1  1997/12/09 19:03:38  wenger
  deviseb now uses client/server library.

  Revision 1.11  1996/08/04 23:08:10  jussi
  Added line numbering.

  Revision 1.10  1996/07/16 23:34:36  jussi
  Improved parsing and added handling of comment lines, blank
  lines, and lines prefixed with the DEVise keyword.

  Revision 1.9  1996/07/09 15:59:37  wenger
  Added master version number and compile date to C++ code (also displayed
  in the user interface); added -usage and -version command line arguments;
  updated usage message.

  Revision 1.8  1996/05/20 18:46:37  jussi
  Merged with ClientServer library code.

  Revision 1.7  1996/05/15 16:40:09  jussi
  Improved support for idle scripts; the client now uses the
  new server synchronization mechanism.

  Revision 1.6  1996/05/14 18:56:21  jussi
  Added checking of return value from DeviseOpen().

  Revision 1.5  1996/05/13 21:56:57  jussi
  Removed idleScript variable. Return value of program is 1
  if script file execution succeeded, otherwise 2.

  Revision 1.4  1996/05/13 20:23:51  jussi
  Added support for synchronization points.

  Revision 1.3  1996/05/13 18:07:38  jussi
  The code now accepts API_CTL type messages but ignores them.

  Revision 1.2  1996/05/11 17:23:24  jussi
  Added command line options for setting host name and port number.

  Revision 1.1  1996/05/11 01:51:42  jussi
  Initial revision.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ClientAPI.h"
#include "DeviseBatchClient.h"
#include "Version.h"
#include "Util.h"

// Because we can't call Exit::DoAbort() here...
#ifdef DOASSERT
#  undef DOASSERT
#endif
#define DOASSERT(c,r) { if (!(c)) DoAbort(r); }
//#define DEBUG

static const char *_deviseKeyword = "DEVise ";
static char _commentChar = '#';

static char *_progName = 0;
static const char *_hostName = "localhost";
static int   _portNum = DefaultNetworkPort;
static DeviseBatchClient *_client;

static char *_scriptFile = 0;

void DoAbort(const char *reason)
{
  fprintf(stderr, "An internal error has occurred. Reason:\n  %s\n", reason);
  delete _client;
  exit(2);
}

int DEViseCmd(int argc, char **argv)
{
#ifdef DEBUG	
  printf("Function %s, %d args\n", argv[0], argc);
#endif

  return _client->ServerCmd(argc, argv);
}

int ExecuteCommands()
{
  FILE *fp = stdin;

  const int MAXARGC = 64;
  const int ARGSIZE = 64;
  char *argv[MAXARGC];
  int i;
  for(i = 0; i < MAXARGC; i++) {
    argv[i] = new char [ARGSIZE];
    DOASSERT(argv[i], "Out of memory");
  }

#ifdef DEBUG
  printf("Setting server to batch mode\n");
#endif

#if 0 //TEMP
  if (nice_strncpy(argv[0], "setBatchMode", ARGSIZE) != StatusOk) {
    fprintf(stderr, "Buffer overflow!");
    return -1;
  }
  if (nice_strncpy(argv[1], "1", ARGSIZE) != StatusOk) {
    fprintf(stderr, "Buffer overflow!");
    return -1;
  }
#else //TEMP
  strncpy(argv[0], "setBatchMode", ARGSIZE);
  strncpy(argv[1], "1", ARGSIZE);
#endif //TEMP
  if (DEViseCmd(2, argv) < 0) {
    fprintf(stderr, "Error setting server to batch mode\n");
    return -1;
  }

  char line[1024];
  int lineno = 1;

  while(fgets(line, sizeof line, fp)) {
    if (line[strlen(line) - 1] != '\n') {
      fprintf(stderr, "Line %d too long in script\n", lineno);
      return -1;
    }
    line[strlen(line) - 1] = 0;
    lineno++;

    char *ptr = line;
    while(isspace(*ptr)) ptr++;

    if (*ptr == _commentChar) {
#ifdef DEBUG
      printf("Read comment line: \"\%s\"\n", ptr);
#endif
      continue;
    }

    if (*ptr == _deviseKeyword[0]
        && !strncmp(ptr, _deviseKeyword, strlen(_deviseKeyword))) {
      ptr += strlen(_deviseKeyword);
      while(isspace(*ptr)) ptr++;
    }

    if (!*ptr) {
#ifdef DEBUG
      printf("Read blank line (maybe with DEVise keyword)\n");
#endif
      continue;
    }

    int argc = 0;
    for(i = 0; i < MAXARGC; i++)
      argv[i][0] = 0;

    int braces = 0;
    int inarg = 0;
    char *argPtr = argv[0];

    while(*ptr) {
      if (*ptr == '{') {
	if (braces > 0)
          *argPtr++ = '{';
	++braces;
        inarg = 1;
        ptr++;
      } else if (*ptr == '}') {
	--braces;
	if (braces > 0)
          *argPtr++ = '}';
        inarg = 1;
        ptr++;
      } else if (*ptr == ' ') {
	if (!braces) {
          *argPtr = 0;
#ifdef DEBUG
	  printf("Argument %d is \"%s\"\n", argc, argv[argc]);
#endif
	  ++argc;
	  if (argc >= MAXARGC) {
	    fprintf(stderr, "Line has too many elements: %s\n", line);
	    return -1;
	  }
          argPtr = argv[argc];            
          while(isspace(*ptr)) ptr++;
          inarg = 0;
	} else {
          *argPtr++ = ' ';
          inarg = 1;
          ptr++;
        }
      }	else {
        *argPtr++ = *ptr++;
        inarg = 1;
      }
    }

    if (inarg) {
      *argPtr = 0;
#ifdef DEBUG
      printf("Argument %d is \"%s\"\n", argc, argv[argc]);
#endif
      ++argc;
    }

    if (argc == 1 && !strcmp(argv[0], "sync")) _client->SetSyncDone(false);

#ifdef DEBUG
    printf("Sending %d elements\n", argc);
#endif
    if (DEViseCmd(argc, argv) < 0) {
      fprintf(stderr, "Error executing command %s\n", argv[0]);
      return -1;
    }

    if (argc == 1 && !strcmp(argv[0], "sync")) {
      printf("Waiting for server synchronization.\n");
      while(!_client->SyncDone()) {
	_client->ReadServer();
      }
      printf("Continuing.\n");
    }
  }

  for(i = 0; i < MAXARGC; i++)
    delete argv[i];

  return 1;
}

void Usage()
{
  fprintf(stderr, "Usage: %s [-h host] [-p port]\n", _progName);
}

int main(int argc, char **argv)
{
  _progName = argv[0];

  for(int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-h")) {
      if (i + 1 >= argc) {
	fprintf(stderr, "No host name specified with -h option.\n");
	Usage();
	exit(4);
      }
      _hostName = argv[i + 1];
      i++;
    } else if (!strcmp(argv[i], "-p")) {
      if (i + 1 >= argc) {
	fprintf(stderr, "No port number specified with -p option.\n");
	Usage();
	exit(4);
      }
      _portNum = atoi(argv[i + 1]);
      i++;
    } else {
      Usage();
      exit(4);
    }
  }

  Version::PrintInfo();
  printf("\n");

  printf("Batch client running.\n");
  printf("\n");

  _client = new DeviseBatchClient("DEVise", _hostName, _portNum);

  if (ExecuteCommands() < 0) {
    exit(5);
  }

  printf("Closing connection.\n");

  delete _client;

  return 1;
}
