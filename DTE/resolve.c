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
 */

#include "myopt.h"
#include "site.h"
#include "machdep.h"

BaseSelection* PrimeSelection::filter(Site* site){
	Path* endPath = NULL;
	Path* nextGlobal = NULL;
	if(!site->have(alias)){
		if(nextPath){
			nextPath->propagate(site);
		}
		return NULL;
	}
	if(nextPath){
		endPath = nextPath->filter(site);
	}
	if(endPath){
		nextGlobal = endPath->nextPath;
		endPath->nextPath = NULL;
	}
	return new GlobalSelect(site, this, nextGlobal);
}

bool PrimeSelection::exclusive(Site* site){
	if(site->have(alias)){
		if(nextPath){
			return nextPath->exclusive(site);
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}

void GlobalSelect::display(ostream& out, int detail = 0){
	out << "{" << site->getName() << ": ";
	selection->display(out, detail);
	out << "}";
	BaseSelection::display(out, detail);
}

BaseSelection* GlobalSelect::filter(Site* siteGroup){
	if(siteGroup->have(site)){
		Path* endPath = NULL;
		Path* nextGlobal = NULL;
		if(nextPath){
			endPath = nextPath->filter(siteGroup);
		}
		if(endPath){
			nextGlobal = endPath->nextPath;
			endPath->nextPath = NULL;
		}
		return new GlobalSelect(siteGroup, this, nextGlobal);
	}
	else{
		if(nextPath){
			nextPath->propagate(siteGroup);
		}
		return NULL;
	}
}

bool GlobalSelect::exclusive(Site* s){
	if(s->have(site)){
		if(nextPath){
			return nextPath->exclusive(s);
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}

BaseSelection* GlobalSelect::enumerate(
     String site1, List<BaseSelection*>* list1,
     String site2, List<BaseSelection*>* list2){

     List<BaseSelection*>* selList;
     int leftRight = 0;
	if(site->getName() == site1){
          selList = list1;
          leftRight = 0;
     }
     else if(site->getName() == site2){
          selList = list2;
          leftRight = 1;
     }
     else{
          cerr << "Could not find site: " << site->getName() << endl;
          cerr << "Options were: " << site1 << " and " << site2 << endl;
          assert(0);
	}
	selList->rewind();
	int i = 0;
	while(!selList->atEnd()){
		Path* upTo = NULL;
		if(selection->match(selList->get(), upTo)){
			Path* newNext = NULL;
			if(upTo){
				assert(!"not implemented");
			}
			BaseSelection* retVal = new ExecSelect(leftRight, i, newNext);
			TRY(BaseSelection::enumerate(site1, list1, site2, list2), NULL);
			return retVal;
		}
		selList->step();
		i++;
	}
	cout << "Could not find: ";
	selection->display(cout);
	cout << endl;
	assert(0);
}

TypeID GlobalSelect::typify(List<Site*>* sites){
	String myName = site->getName();
	sites->rewind();
	Site* currSite = NULL;
	while(true){
		currSite = sites->get();
		if(myName == currSite->getName()){
			break;
		}
		sites->step();
		if(sites->atEnd()){
			cerr << "Could not find site: " << myName << endl;
			assert(0);
		}
	}
	List<BaseSelection*>* selList = currSite->getSelectList();
	selList->rewind();
	while(!selList->atEnd()){
		Path* upTo = NULL;
		if(selection->match(selList->get(), upTo)){
			Path* newNext = NULL;
			if(upTo){
				assert(!"not implemented");
			}
			TRY(BaseSelection::typify(sites), "Unknown");
			typeID = selList->get()->getTypeID();
			avgSize = selList->get()->getSize();
			return typeID;
		}
		selList->step();
	}
	cout << "Could not find: ";
	selection->display(cout);
	cout << endl;
	assert(0);
}

bool GlobalSelect::match(BaseSelection* x, Path*& upTo){
	if(!(selectID() == x->selectID())){
		return false;
	}
	GlobalSelect* y = (GlobalSelect*) x;
	if(site->getName() != y->site->getName()){
		return false;
	}
	if(!selection->match(y->selection, upTo)){
		return false;
	}
	return BaseSelection::match(y, upTo);
}

BaseSelection* Operator::enumerate(
	String site1, List<BaseSelection*>* list1,
     String site2, List<BaseSelection*>* list2){
	BaseSelection* l;
     TRY(l = left->enumerate(site1, list1, site2, list2), NULL);
	BaseSelection* r;
     TRY(r = right->enumerate(site1, list1, site2, list2), NULL);
	return new ExecOperator(name, l, r, opPtr);
}

TypeID PrimeSelection::typify(List<Site*>* sites){
     assert(sites->cardinality() == 1);
     sites->rewind();
     Site* current = sites->get();
	List<BaseSelection*>* selList = current->getSelectList();
	selList->rewind();
	while(!selList->atEnd()){
		Path* upTo = NULL;
		if(match(selList->get(), upTo)){
			if(upTo){
				assert(!"not implemented");
			}
			typeID = selList->get()->getTypeID();
			avgSize = selList->get()->getSize();
			return typeID;
		}
		selList->step();
	}
	ostrstream tmp;
	displayList(tmp, selList);
	tmp << ends;
	char* tmpc = tmp.str();
	String msg = "Table " + *alias + "(" + String(tmpc) + ")" +
		" does not have attribute " +
		*nextPath->path;
	delete tmpc;
	THROW(new Exception(msg), NULL);
}

BaseSelection* Operator::distributeWrapper(Site* site){
	BaseSelection* leftG = left->distributeWrapper(site);
	BaseSelection* rightG = right->distributeWrapper(site);
	if(leftG){
		left = leftG;	// nothing is lost
	}
	if(rightG){
		right = rightG;	// nothing is lost
	}
	BaseSelection::distributeWrapper(site);
	return this;
}
