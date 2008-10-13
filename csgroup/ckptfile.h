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
  Implementation of Client (and CompDate) classes.
 */

/*
  $Id$

  $Log$
  Revision 1.3  1998/03/11 18:25:09  wenger
  Got DEVise 1.5.2 to compile and link on Linux; includes drastically
  reducing include dependencies between csgroup code and the rest of
  the code, and within the csgroup code.  (Note: running collaboration
  doesn't work yet.)

  Revision 1.2  1998/02/12 17:14:44  wenger
  Merged through collab_br_2; updated version number to 1.5.1.

  Revision 1.1.2.2  1998/02/02 08:23:52  liping
  Added CVS header

*/

#ifndef _CKPTFILE_H
#define _CKPTFILE_H
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

class	UniqueFileName {
	public:
		char	buf [200];
		UniqueFileName(char*& fname, const char* prefix)
		{
			sprintf(buf, "/tmp/%s_%ld_%ld",prefix, (long)getuid(),
				(long)getpid());
			fname = buf;
		}
};
extern char	*ServerCkptFile;
extern char *MasterCkptFile;
#endif
