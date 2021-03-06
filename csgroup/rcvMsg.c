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
  Revision 1.9  2005/12/06 20:01:13  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.8  2002/06/17 19:40:40  wenger
  Merged V1_7b0_br_1 thru V1_7b0_br_2 to trunk.

  Revision 1.7.14.2  2003/12/19 18:07:07  wenger
  Merged redhat9_br_0 thru redhat9_br_1 to V1_7b0_br.

  Revision 1.7.14.1.6.1  2003/12/17 00:17:42  wenger
  Merged gcc3_br_1 thru gcc3_br_2 to redhat9_br (just fixed conflicts,
  didn't actually get it to work).

  Revision 1.7.14.1.4.1  2003/12/16 16:07:57  wenger
  Got DEVise to compile with gcc 3.2.3 (with lots of deprecated-header
  warnings).  It runs on RedHat 7.2, but not on Solaris 2.8 (some kind
  of dynamic library problem).

  Revision 1.7.14.1  2002/05/27 18:15:37  wenger
  Got DEVise to compile with gcc 2.96 (so I can compile it at NRG).

  Revision 1.7  2000/03/23 19:58:39  wenger
  Updated dependencies, got everything to compile on pumori (Linux 2.2.12,
  g++ 2.95.2).

  Revision 1.6  1999/11/30 22:27:28  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.5  1998/08/21 22:16:10  wenger
  Got DEVise 1.5.4 to compile on SPARC/SunOS (sundance) -- to make statically-
  linked DEVise for distribution.

  Revision 1.4  1998/03/30 22:32:56  wenger
  Merged fixes from collab_debug_br through collab_debug_br2 (not all
  changes from branch were merged -- some were for debug only)
  (committed stuff includes conditionaled-out debug code).

  Revision 1.3.2.1  1998/03/25 15:56:51  wenger
  Committing debug version of collaboration code.

  Revision 1.3  1998/03/11 18:25:17  wenger
  Got DEVise 1.5.2 to compile and link on Linux; includes drastically
  reducing include dependencies between csgroup code and the rest of
  the code, and within the csgroup code.  (Note: running collaboration
  doesn't work yet.)

  Revision 1.2  1998/02/12 17:15:02  wenger
  Merged through collab_br_2; updated version number to 1.5.1.

  Revision 1.1.2.3  1998/02/02 08:24:06  liping
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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#if defined(SUN)
#   include "machdep.h"
#endif
#include <stdlib.h>

#include "rcvMsg.h"
#include "codec.h"
#include "serverInterface.h"
#include "callBks.h"
#include "netfns.h"
#include "timeOut.h"
#include "ckptfile.h"
#include "DevError.h"

extern int MySocketfd;
char *MasterCkptFile;
UniqueFileName masterUnf(MasterCkptFile,"master");

int
TransferCkpt(int sockfd) {
	int ckptfd;
	int netfd;
	struct sockaddr Address;
#if defined(LINUX) || defined(SOLARIS)
        socklen_t
#else
	int
#endif
	    size = sizeof(Address);
	char ch;
	int nbytes;

	if ((netfd = accept(sockfd, &Address, &size)) < 0) {
		return ER_CKPTACPTFAILED;
	}

	ckptfd = open(ServerCkptFile, O_RDWR|O_TRUNC|O_CREAT, 0600);
	while ((nbytes = read(netfd, &ch, 1)) > 0) {
		if (nbytes > 0) {
			write(ckptfd, &ch, 1);
			if (ch == EOF) {
				break;
			}	
		}
	}
	
	close(netfd);
	close(ckptfd);
	if (nbytes < 0) {
		return ER_CKPTXFERFAILED;
	}
	return 0;
}

int
SpawnCkptXfer(CallBackHandler ckptfn, char *ckptfile, ConnectInfo *cInfo) {
	int netfd;
	int ckptfd;
	pid_t pid;
	char ch;
	int nbytes;
	struct timeval timeout = CLB_CONNECTTIME;

	(*ckptfn)(ckptfile, NULL);

	pid = fork();
	if (pid < 0) {
		return ER_FORKFAILED;
	}
	if (pid > 0) {
		return 0;
	}
	
	if ((netfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        reportErrNosys("Fatal error");//TEMP -- replace with better message
		exit(ER_CONNECTFAILED);
	}

	if (ConnectWithTimeout(netfd, (struct sockaddr *)cInfo, 
			       sizeof(*cInfo), &timeout) < 0) {
        reportErrNosys("Fatal error");//TEMP -- replace with better message
		exit(ER_CONNECTFAILED);
	}

	if ((ckptfd = open(ckptfile, O_RDONLY, 0600)) < 0) {
        reportErrNosys("Fatal error");//TEMP -- replace with better message
		exit(ER_OPENFAILED);
	}
	
	while ((nbytes = read(ckptfd, &ch, 1)) > 0) {
		if (nbytes == 0) {
			continue;
		}
		if (ch == EOF) {
			break;
		}
		write(netfd, &ch, 1);
	}
	close(netfd);
	close(ckptfd);
    reportErrNosys("Fatal error");//TEMP -- replace with better message
	exit(0);
}
	
int
RecvMsg(int fd, char *buf, int size) {
	int type;
	int nbytes;
	ConnectInfo cInfo;
	GroupKey gName;
	int cInfoLength;
	int gNameLength;
	CallBackHandler cbkfn;

	nbytes = XferMsgType(fd, MSG_DECODE, &type);
	if (nbytes <= 0) {
		return -1;
	}

	switch (type) {
		case CTRL_DATA:
			nbytes = XferMsg(fd, MSG_DECODE, 1,
				  TYP_STRING, &gNameLength, buf);
			if (nbytes <= 0 ) {
				return -1;
			}
			return gNameLength;
		case CTRL_RELINQUISH:
			bzero((char *)&gName, sizeof(gName));
			nbytes = XferMsg(fd, MSG_DECODE, 2,
				   TYP_STRING, &cInfoLength, (char *)&cInfo,
				   TYP_STRING, &gNameLength, (char *)&gName);
			if (nbytes <= 0) { 
			   return -1;
			}
			cbkfn = CBak((int) ceil(log((double)CTRL_RELINQUISH)/log((double)2)));
			if (cbkfn != NULL) {
				(*cbkfn)(gName.grpName, &cInfo);
			}
			/*		Leadership(&gName, cInfo, CRM_RELINQUISH); */
			return 0;
		case CTRL_GRABBED:
			bzero((char *)&gName, sizeof(gName));
			nbytes = XferMsg(fd, MSG_DECODE, 1,
				   TYP_STRING, &gNameLength, (char *)&gName);
			if (nbytes <= 0) { 
			   return -1;
			}
			MkStateLeader(&gName);
			cbkfn = CBak((int) ceil(log((double)CTRL_GRABBED)/log((double)2)));
			if (cbkfn != NULL) {
				(*cbkfn)(gName.grpName, NULL);
			}
			return 0;
		case CTRL_CKPTSERVER:
			bzero((char *)&gName, sizeof(gName));
			nbytes = XferMsg(fd, MSG_DECODE, 2,
				    TYP_STRING, &cInfoLength, (char *)&cInfo,
			            TYP_STRING, &gNameLength, (char *)&gName);
			if (nbytes <= 0) { 
			   return -1;
			}
			cbkfn = CBak((int) ceil(log((double)CTRL_CKPTSERVER)/log((double)2)));
			ExecCkpt(&gName, cInfo);
			SpawnCkptXfer(cbkfn, MasterCkptFile, &cInfo);
			return 0;
		case CTRL_EXECCKPT:
			cbkfn = CBak((int) ceil(log((double)CTRL_EXECCKPT)/log((double)2)));
			TransferCkpt(MySocketfd);
			if (cbkfn != NULL) {
				(*cbkfn)(ServerCkptFile, NULL);
			}
			return 0;
		default:
			return 0;
	}
}
