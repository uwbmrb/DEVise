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
  Revision 1.3  1996/01/15 16:56:31  jussi
  Added copyright notice and cleaned up the code a bit.

  Revision 1.2  1995/09/05 22:15:14  jussi
  Added CVS header.
*/

#include "QueryProc.h"
#include "DispQueryProc.h"
#include "Init.h"
#include "Exit.h"

QueryProc *QueryProc::_queryProc = NULL;
int QueryProc::_numQueryProcs = 0;      /* number of query processors */
QPRec QueryProc::_qpArray[MAX_QUERYPROCS];

void QueryProc::Register(char *name, QueryProcGen *gen)
{
  if (_numQueryProcs == MAX_QUERYPROCS) {
    fprintf(stderr,"too many query processors\n");
    Exit::DoExit(1);
  }

  _qpArray[_numQueryProcs].name = name;
  _qpArray[_numQueryProcs++].gen = gen;
}

QueryProc *QueryProc::Instance()
{
  if (_queryProc == NULL) {
    char *qpName = Init::QueryProc();
    if (!strcmp(qpName,"default")) {
      _queryProc = new DispQueryProcFull();
    } else {
      Boolean found = false;
      for(int i = 0; i < _numQueryProcs; i++) {
	if (!strcmp(_qpArray[i].name,qpName)) {
	  _queryProc = (*_qpArray[i].gen)();
	  found = true;
	  break;
	}
      }
      if (!found){
	fprintf(stderr, "can't find query proc %s\n", qpName);
	Exit::DoExit(1);
      }
    }
  }

  return _queryProc;
}
