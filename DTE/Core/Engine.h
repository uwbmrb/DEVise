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
  Revision 1.3  1996/12/07 15:14:25  donjerko
  Introduced new files to support indexes.

  Revision 1.2  1996/12/05 16:05:59  wenger
  Added standard Devise file headers.

 */

#ifndef ENGINE_H
#define ENGINE_H

#include "types.h"
#include "site.h"
#include <strstream.h>

class Engine {
	String query;
	Site* topNode;
public:
	Engine(String query) : query(query), topNode(NULL) {}
	virtual ~Engine(){
		delete topNode;	// should delete all the sites
	}
	int optimize();	// throws
     virtual int getNumFlds(){
		return topNode->getNumFlds();
     }
     virtual String* getTypeIDs(){
          return topNode->getTypeIDs();
     }
	virtual Tuple* getNext(){
		return topNode->getNext();
	}
	virtual String* getAttributeNames(){
		return topNode->getAttributeNames();
	}
	Stats* getStats(){
		return topNode->getStats();
	}
	void reset(int lowRid, int highRid){
		TRY(topNode->reset(lowRid, highRid), );
	}
	virtual void initialize(){
		topNode->initialize();
	}
};

#endif
