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
  Implementation of Client (and CompDate) classes.
 */

/*
  $Id$

  $Log$
  Revision 1.1.2.2  1998/02/02 08:24:02  liping
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
#include <stdlib.h>

#include "netfns.h"
#include "error.h"

int
CheckOpenfds(int maxfds, fd_set *openfds, fd_set *brokenfds) {
	struct timeval timeout = {0, 0};
	int ret;
	int i;

	memmove(brokenfds, openfds, sizeof(fd_set));
	ret = select(maxfds, brokenfds, (fd_set *)0, 
		     (fd_set *)0, &timeout);

	return ret;
}
	
int
ConnectWithTimeout(int sockfd, struct sockaddr *Address, 
		   int size, struct timeval *timeout) {
	char code;
	fd_set fdset;

	code = 1;
	if (ioctl(sockfd, FIONBIO, &code) < 0) {
	         printf("IOCTL failed\n");
		 return -1;
	} 
	if (connect(sockfd, Address, size) < 0) {
		 perror("Connect: ");
		if (errno != EINPROGRESS) {
		        ERROR(NON_FATAL, "Connect Failed");
			return -1;
		 }
		 FD_ZERO(&fdset);
		 FD_SET(sockfd, &fdset);
		 if (select(sockfd+1, 
			    (fd_set *)0, &fdset, 
			    (fd_set *)0, timeout) == 0) {
			 close(sockfd);
			 printf("Select 	Timesout\n");
			 fflush(stdout);
            		 return -1;
		 }
		 if (!FD_ISSET(sockfd, &fdset)) {
	   	      printf("Desc not set when returned from select\n");
			 fflush(stdout);
	 	}
	 	else {
	 		printf("Connected \n");
	 		fflush(stdout);
	 	}
	 	code = 0;
	 	if (ioctl(sockfd, FIONBIO, &code) < 0) {
			 printf("IOCTL failed\n");
			 close(sockfd);
			 return -1;
	 	}
	}
	return 0;
}
