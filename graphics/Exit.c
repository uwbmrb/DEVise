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
  Revision 1.4  1996/04/16 19:45:35  jussi
  Added DoAbort() method and DOASSERT macro.

  Revision 1.3  1996/01/11 21:51:14  jussi
  Replaced libc.h with stdlib.h. Added copyright notice.

  Revision 1.2  1995/09/05 21:12:45  jussi
  Added/updated CVS header.
*/

#include <stdio.h>
#include <stdlib.h>

#include "Exit.h"
#include "Init.h"
#include "Control.h"

void Exit::DoExit(int code)
{
  if (Init::DoAbort()) {
    fflush(stdout);
    fflush(stderr);
    abort();
  }
  exit(code);
}

void Exit::DoAbort(char *reason, char *file, int line)
{
  char fulltext[256];
  sprintf(fulltext, "%s (%s:%d)", reason, file, line);

  fprintf(stderr, "An internal error has occurred. The reason is:\n");
  fprintf(stderr, "  %s\n", fulltext);

  ControlPanel::Instance()->DoAbort(fulltext);

  DoExit(2);
}
