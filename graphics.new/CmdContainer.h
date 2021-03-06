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
  Revision 1.16.14.1  2013/09/20 15:29:34  wenger
  More Centos 6 compile fixes.

  Revision 1.16  2008/01/24 22:08:31  wenger
  Got rid of a bunch of compile warnings.

  Revision 1.15  2005/12/06 20:03:44  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.14  2003/01/13 19:25:21  wenger
  Merged V1_7b0_br_3 thru V1_7b0_br_4 to trunk.

  Revision 1.13.10.2  2005/09/06 22:04:55  wenger
  Added proper const-ness to HashTable.

  Revision 1.13.10.1  2002/09/02 21:29:33  wenger
  Did a bunch of Purifying -- the biggest change is storing the command
  objects in a HashTable instead of an Htable -- the Htable does a bunch
  of ugly memory copying.

  Revision 1.13  2001/10/08 19:21:02  wenger
  Fixed bug 702 (JavaScreen locks up on unrecognized command in DEVised).

  Revision 1.12  2001/01/08 20:32:52  wenger
  Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
  back onto the trunk.

  Revision 1.10.2.1  2000/12/27 19:39:19  wenger
  Merged changes from js_restart_improvements thru zero_js_cache_check from
  the trunk onto the js_cgi_br branch.

  Revision 1.11  2000/11/17 22:59:06  wenger
  Fixed problems with command logging of cursor movements and pile/stack
  flips.

  Revision 1.10  1999/12/06 18:41:03  wenger
  Simplified and improved command logging (includes fixing bug 537, command
  logs are now human-readable); added standard header to debug logs.

  Revision 1.9  1999/12/02 15:06:57  wenger
  Fixed bug 538 (slow session saving).

  Revision 1.8  1999/11/24 15:44:21  wenger
  Removed (unnecessary) CommandObj class; commands are now logged for the
  monolithic form, not just the client/server form; other command-related
  cleanups; added GUI for playing back command logs.

  Revision 1.7  1999/11/19 17:17:41  wenger
  Added View::SetVisualFilterCommand() method to clean up command-related
  code for filter setting.

  Revision 1.6  1998/08/17 17:12:02  wenger
  Devised now responds to KeyAction commands from JavaScreen.

  Revision 1.5  1998/05/02 09:00:38  taodb
  Added support for JAVA Screen and command logging

  Revision 1.4  1998/04/07 14:30:18  wenger
  Reduced unnecessary include dependencies.

  Revision 1.3  1998/03/27 15:08:53  wenger
  Added dumping of logical session description, added GUI for dumping
  logical or physical description; cleaned up some of the command code
  a little.

 */

#ifndef _CmdContainer_h_
#define _CmdContainer_h_

#include <iostream>

#include "Control.h"
#include "DeviseCommand.h"
#include "DeviseServer.h"
#include "HashTable.h"

class ControlPanel;
class DeviseCommand;

class CmdContainer 
{
  	friend ostream& operator <<(ostream& os, const CmdContainer& cc);
	public:
		typedef enum {MONOLITHIC=0,CSGROUP} Make;

		static CmdContainer *GetCmdContainer();

		// Generate a command internally (used so that actions get logged/
		// passed to collaborators as appropriate).
		static void GenerateCommand(int argc, const char* const *argv);

		CmdContainer(ControlPanel* control, Make make, DeviseServer* server);
		~CmdContainer();

		int	Run(int argc, const char* const *argv, ControlPanel* control, 
			CmdDescriptor& cmdDes);
		int	RunInternal(int argc, const char* const *argv,
		    ControlPanel* control);

		void insertCmd(const char*, DeviseCommand *,int cmdsize);		
		DeviseCommand* lookupCmd(const char*);
		void deleteCmd(char* cmdName);

		Make	getMake(){return make;}

		void DisableCollab() { _collabEnabled = false; }

		DeviseServer* getDeviseServer(){ return _server;}

	protected:
	    friend class Session;

		int	RunOneCommand(int argc, const char* const *argv,
		    ControlPanel* control);

	private:
		long	logCommand(int argc, char** argv, CmdDescriptor& cmdDes);
		//bool	playCommand(long logId1, long logId2);

		static int CmdHash(char * const &index, int numBuckets);
		static int CmdComp(char * const &index1, char * const &index2);

		Make	make;
		DeviseServer*	_server;
		Boolean _collabEnabled;

		HashTable<char *, DeviseCommand *> *_commands;
};
ostream& operator <<(ostream& os, const CmdContainer& cc);

#endif // _CmdContainer_h_
