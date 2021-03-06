/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2002
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
  Revision 1.5.14.1  2002/05/27 18:15:36  wenger
  Got DEVise to compile with gcc 2.96 (so I can compile it at NRG).

  Revision 1.5  1999/11/30 22:27:27  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.4  1998/07/29 14:19:43  wenger
  Mods to compile DEVise on Alpha/OSF again (partially successful); mods to
  allow static linking on Linux.

  Revision 1.3  1998/02/26 18:54:09  wenger
  Got everything to compile on haha -- still have a link problem, though.

  Revision 1.2  1998/02/12 17:14:52  wenger
  Merged through collab_br_2; updated version number to 1.5.1.

  Revision 1.1.2.2  1998/02/02 08:23:58  liping
  Added CVS header

*/

/* 
** Copyright 1997 Collaborator Design Team
** 
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted,
** provided that the above copyright notice appear in all copies and that
** both that copyright notice and this permission notice appear in
** supporting documentation, and that the names of the University of
** Wisconsin and the Collaborator Design Team not be used in advertising or
** publicity pertaining to distribution of the software without specific,
** written prior permission.  The University of Wisconsin and the Collaborator
** Design Team make no representations about the suitability of this
** software for any purpose.  It is provided "as is" without express
** or implied warranty.
** 
** THE UNIVERSITY OF WISCONSIN AND THE COLLABORATOR DESIGN TEAM DISCLAIM ALL
** WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE UNIVERSITY OF
** WISCONSIN OR THE COLLABORATOR DESIGN TEAM BE LIABLE FOR ANY SPECIAL, 
** INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING 
** FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
** NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION 
** WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
** 
** Author:  Ashish Thusoo
** 	         University of Wisconsin, Computer Sciences Dept.
** 
*/ 
#include <stdio.h>
#if defined(SGI)
#include <stdarg.h>
#endif
#include <stdlib.h>

#include "devise_varargs.h"
#include "error.h"

int ERRORLine;
char *ERRORFile;
int errcode=0;

void
GraceExit(int code) {
    printf("GraceExit(%d)\n", code);

	exit(code);
}

void
ErrorProc(int type, ...) {
	va_list argp;
	char *format;

	va_start(argp, type);
	format = va_arg(argp, char *);

	if (type == FATAL) {
		fprintf(stderr, "Fatal Error: ");
	}
	else {
		fprintf(stderr, "Error: ");
	}

	vfprintf(stderr, format, argp);
	fprintf(stderr, " at Line %d in File %s\n", ERRORLine, ERRORFile);

	va_end(argp);
	if (type == FATAL) {
		fprintf(stderr, "Exiting ...\n");
		GraceExit(1);
	}
}

