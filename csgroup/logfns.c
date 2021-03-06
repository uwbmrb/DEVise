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
  Implementation of Client (and CompDate) classes.
 */

/*
  $Id$

  $Log$
  Revision 1.5.56.1  2014/01/17 21:46:00  wenger
  Fixed a bunch of possible buffer overflows.

  Revision 1.5  1998/03/30 22:32:54  wenger
  Merged fixes from collab_debug_br through collab_debug_br2 (not all
  changes from branch were merged -- some were for debug only)
  (committed stuff includes conditionaled-out debug code).

  Revision 1.4.2.1  1998/03/25 15:56:48  wenger
  Committing debug version of collaboration code.

  Revision 1.4  1998/03/11 18:25:14  wenger
  Got DEVise 1.5.2 to compile and link on Linux; includes drastically
  reducing include dependencies between csgroup code and the rest of
  the code, and within the csgroup code.  (Note: running collaboration
  doesn't work yet.)

  Revision 1.3  1998/02/26 18:54:11  wenger
  Got everything to compile on haha -- still have a link problem, though.

  Revision 1.2  1998/02/12 17:14:56  wenger
  Merged through collab_br_2; updated version number to 1.5.1.

  Revision 1.1.2.2  1998/02/02 08:24:01  liping
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
/* most of the code here is lifted from the Condor Source */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>

#include "colbrLog.h"
#include "logfns.h"

static int log_fd;

int
ReadLog(char *log_name)
{
	LogRecord		*log_rec;

	log_fd = open(log_name, O_RDWR | O_CREAT, 0600);
	if (log_fd < 0) {
		return log_fd;
	}
	// Read all of the log records
	while((log_rec = ReadLogEntry(log_fd)) != 0) {
		log_rec->Play();
		delete log_rec;
	}
	ReconnectAll();
	TruncLog(log_name);
	return 0;
}

int
TruncLog(char *log_name)
{
	char	tmp_log_name[PATH_MAX];
	int new_log_fd;

	int formatted = snprintf(tmp_log_name, sizeof(tmp_log_name),
	  "%s.tmp", log_name);
	assert(formatted < (int)sizeof(tmp_log_name));//TEMP
/*TEMP
	if (checkAndTermBuf2(tmp_log_name, formatted) != StatusOk) {
	    reportErrNosys("Buffer overflow!");
		exit(1);
	}
TEMP*/
	new_log_fd = open(tmp_log_name, O_RDWR | O_CREAT, 0600);
	if (new_log_fd < 0) {
		return new_log_fd;
	}
	LogState(new_log_fd);
	close(log_fd);
	log_fd = new_log_fd;
	if (rename(tmp_log_name, log_name) < 0) {
		return -1;
	}
	return 0;
}

int
LogState(int fd)
{
	Entry *entr = NULL;
	GroupKey *GroupName;
	DbEntry *master;
	Queue *servers;
	Queue *waiters;
	LogRecord* log;
	GroupInfo *gInfo;
	QueueElem *qElem;
	
	for(entr = GroupDB.getfirst(); entr; entr = GroupDB.getnext()) {
	      GroupName = new GroupKey;
	      memmove(GroupName->grpName, (entr->getKey())->data(),
		      (entr->getKey())->size());
	      gInfo = (GroupInfo *)(entr->getData())->data();
	      strncpy(GroupName->grpPwd, gInfo->pwd, sizeof(GroupName->grpPwd));
		  GroupName->grpPwd[sizeof(GroupName->grpPwd)-1] = '\0';
	      master = (DbEntry *)gInfo->leader ? 
		       (DbEntry *)gInfo->leader->data() : (DbEntry*)NULL;
	      servers = (Queue *)gInfo->followers;
	      waiters = (Queue *)gInfo->waitlist;
	      
	      log = new LogAddGroup(GroupName);
	      log->Write(fd);
	      delete log;
	      if (master) {
	      	log = new LogSetLeader(GroupName, master);
	      	log->Write(fd);
	      	delete log;
	      }
	     
	      for (qElem=servers->getfirst(); qElem; 
		   qElem = servers->getnext()) {
		     master = (DbEntry *)(qElem->getelement()->data());
		     log = new LogAppendFollower(GroupName, master);
		     log->Write(fd);
		     delete log;
	      }

	      delete GroupName;
	}
	
	fsync(fd);
        return 0; 
}

void
AppendLog(int type, ...)
{
	LogRecord *log = NULL;
	GroupKey *GroupName;
	DbEntry *ServerAddr;
	va_list pvar;

	va_start(pvar, type);

	switch(type) {
		case COLBR_AddGroup:
			GroupName = va_arg(pvar, GroupKey *);
			log = new LogAddGroup(GroupName);
			break;
		case COLBR_DelGroup:
			GroupName = va_arg(pvar, GroupKey *);
			log = new LogDelGroup(GroupName);
			break;
		case COLBR_SetLeader:
			GroupName = va_arg(pvar, GroupKey *);
			ServerAddr = va_arg(pvar, DbEntry *);
			log = new LogSetLeader(GroupName, ServerAddr);
			break;
		case COLBR_AppendFollower:
			GroupName = va_arg(pvar, GroupKey *);
			ServerAddr = va_arg(pvar, DbEntry *);
			log = new LogAppendFollower(GroupName, ServerAddr);
			break;
		case COLBR_AppendWaiter:
			GroupName = va_arg(pvar, GroupKey *);
			ServerAddr = va_arg(pvar, DbEntry *);
			log = new LogAppendWaiter(GroupName, ServerAddr);
			break;
		case COLBR_DelFollower:
			GroupName = va_arg(pvar, GroupKey *);
			ServerAddr = va_arg(pvar, DbEntry *);
			log = new LogDelFollower(GroupName, ServerAddr);
			break;
		case COLBR_DelWaiter:
			GroupName = va_arg(pvar, GroupKey *);
			ServerAddr = va_arg(pvar, DbEntry *);
			log = new LogDelWaiter(GroupName, ServerAddr);
			break;
		case COLBR_DelLeader:
			GroupName = va_arg(pvar, GroupKey *);
			ServerAddr = va_arg(pvar, DbEntry *);
			log = new LogDelLeader(GroupName, ServerAddr);
			break;
		case COLBR_LeaderToFollower:
			GroupName = va_arg(pvar, GroupKey *);
			log = new LogLeaderToFollower(GroupName);
			break;
		case COLBR_WaitToFollower:
			GroupName = va_arg(pvar, GroupKey *);
			ServerAddr = va_arg(pvar, DbEntry *);
			log = new LogWaitToFollower(GroupName, ServerAddr);
			break;
		case COLBR_WaitToLeader:
			GroupName = va_arg(pvar, GroupKey *);
			log = new LogWaitToLeader(GroupName);
			break;
		case COLBR_FollowerToWait:
			GroupName = va_arg(pvar, GroupKey *);
			ServerAddr = va_arg(pvar, DbEntry *);
			log = new LogFollowerToWait(GroupName, ServerAddr);
			break;
		default:
			break;
	}
	va_end(pvar);
        log->Write(log_fd);
	fsync(log_fd);
}

void
ReconnectAll()
{
	Entry *entr = NULL;
	GroupKey *GroupName;
	Queue *servers;
	Queue *waiters;
	DbEntry *master;
	GroupInfo *gInfo;
	QueueElem *qElem;

	for(entr = GroupDB.getfirst(); entr; entr = GroupDB.getnext()) {
	      GroupName = new GroupKey;
	      memmove(GroupName->grpName, (entr->getKey())->data(),
		      (entr->getKey())->size());
	      gInfo = (GroupInfo *)(entr->getData())->data();
	      strncpy(GroupName->grpPwd, gInfo->pwd, sizeof(GroupName->grpPwd));
		  GroupName->grpPwd[sizeof(GroupName->grpPwd)-1] = '\0';
	      master = (DbEntry *)gInfo->leader ? 
		       (DbEntry *)gInfo->leader->data() : (DbEntry*)NULL;
	      servers = (Queue *)gInfo->followers;
	      waiters = (Queue *)gInfo->waitlist;
	      if (master != NULL) {
	            master->FileDesc = 
			ConnectServer(master->ServerAddr);
	            if (master->FileDesc < 0) {
			DeleteMaster(GroupName, master, 
				     LOG_DISABLE);
		    }	
	      }

	      for(qElem = servers->getfirst(); qElem; 
		  qElem = servers->getnext()) {
		     master = (DbEntry *)(qElem->getelement()->data());
		     master->FileDesc = 
			ConnectServer(master->ServerAddr);
		     if (master->FileDesc < 0) {
			DeleteServer(GroupName, master, 
				     LOG_DISABLE);
		     }
	      }
	      
	      for(qElem = waiters->getfirst(); qElem; 
		  qElem = waiters->getnext()) {
		     master = (DbEntry *)(qElem->getelement()->data());
		     master->FileDesc = 
			ConnectServer(master->ServerAddr);
		     if (master->FileDesc < 0) {
			DeleteWaiter(GroupName, master, 
				     LOG_DISABLE);
		     }
	      }
	      delete GroupName;
	}
}
