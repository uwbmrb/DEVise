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

#include<iostream.h>
#include<memory.h>
#include<string.h>
#include<assert.h>
#include<math.h>
#include<stdlib.h>

#ifdef __GNUG__
#pragma implementation "queue.h"
#endif

#include "queue.h"
#include "myopt.h"
#include "site.h"
#include "types.h"
#include "exception.h"
#include "catalog.h"
#include "DevRead.h"
#include "Engine.h"
#include "listop.h"
#include "Aggregates.h"

const int DETAIL = 1;

extern int yyparse();
extern int yydebug;
Exception* currExcept;

List<BaseSelection*>* selectList = NULL;
List<TableAlias*>* tableList;
BaseSelection* predicates;
List<String*>* namesToResolve;
char* queryString;

LOG(ofstream logFile("log_file.txt");)

DefaultExceptHndl defaultExceptHndl;
ITimer iTimer;

void resolveNames(){
	if(tableList->cardinality() > 1){
		String msg = "cannot resolve referencies in: " + String(queryString);
		THROW(new Exception(msg), );
	}
	else{
		tableList->rewind();
		namesToResolve->rewind();
		String* replacement = tableList->get()->table;
		for(int i = 0; i < namesToResolve->cardinality(); i++){
			String* current = namesToResolve->get();
			*current = *replacement;
			namesToResolve->step();
		}
	}
}

int Engine::optimize(){
	queryString = strdup(query.chars());
	namesToResolve = new List<String*>;
	if(yyparse() != 0){
		String msg = "parse error in: " + String(queryString);
		THROW(new Exception(msg), 0);
	}
	assert(tableList);
	if(!namesToResolve->isEmpty()){
		TRY(resolveNames(), 0);
	}
	delete namesToResolve;
	LOG(logFile << "Query was:\n";)
	LOG(logFile << "   select ";)
	LOG(displayList(logFile, selectList, ", ");)
	LOG(logFile << endl << "   from ";)
	LOG(displayList(logFile, tableList);)
	List<BaseSelection*>* predicateList = new List<BaseSelection*>;
	if(predicates){
		LOG(logFile << endl << "   where ";)
		LOG(predicates->display(logFile);)
		LOG(logFile << endl;)
		LOG(logFile << "Predicates after cnf:\n";)
		BaseSelection* newPredicates = predicates->cnf();
		if(newPredicates){
			delete predicates;
			predicates = newPredicates;
		}
		LOG(logFile << "   ";)
		LOG(predicates->display(logFile);)
		if(predicates->insertConj(predicateList)){
			delete predicates;
		}
	}
	LOG(logFile << endl << "Predicate list:\n   ";)
	LOG(displayList(logFile, predicateList);)
	LOG(logFile << endl;)

	tableList->rewind();
	int numSites = 0;
	Catalog catalog;
	String catalogName;
	catalogName += getenv("DEVISE_SCHEMA");
	catalogName += "/catalog.dte";
	TRY(catalog.read(catalogName), 0);
     List<Site*>* sites = new List<Site*>;
	while(!tableList->atEnd()){
		TableAlias* ta = tableList->get();
          Catalog::Interface* interf = NULL;
		if(ta->isQuote()){
			TRY(interf = catalog.toInterface(*ta->table), 0);
		}
		else{
			TRY(interf = catalog.find(*ta->table), 0);
		}
		assert(interf);
		TRY(Site* site = interf->getSite(), 0);	// can be old site
		site->addTable(ta);
		if(!sites->exists(site)){
			sites->append(site);
			numSites++;
		}
		tableList->step();
	}
	Aggregates aggregates(selectList);
	if(aggregates.isApplicable()){
		cout << "Aggregates not implemented\n";
		exit(1);
	}
	LOG(logFile << "Decomposing query on " << numSites << " sites\n";)
     sites->rewind();
     while(!sites->atEnd()){
          Site* current = sites->get();
          current->filter(selectList, predicateList);
		LOG(logFile << current->getName());
          LOG(current->display(logFile));
		LOG(logFile << endl);
          sites->step();
     }
	TRY(checkOrphanInList(selectList), 0);
	TRY(checkOrphanInList(predicateList), 0);
	if(!selectList){
		APPLY(makeNonComposite(), predicateList);
	}
     LOG(logFile << "Global query:\n";)
	LOG(logFile << "   select ";)
     LOG(displayList(logFile, selectList, ", "));
     LOG(logFile << "\n   where ";)
     LOG(displayList(logFile, predicateList, ", "));
	LOG(logFile << endl;)
	String* types;
	String option = "execute";
	TRY(typifyList(sites, option), 0);
	sites->rewind();
	LOG(logFile << "Typified sites\n");
     while(!sites->atEnd()){
          Site* current = sites->get();
		List<Site*>* alters = current->generateAlternatives();
		LOG(logFile << current->getName());
          LOG(current->display(logFile));
		LOG(logFile << endl);
          sites->step();
     }
	if(!selectList){
		selectList = createGlobalSelectList(sites);
		// already typified
	}
	else{
		TRY(typifyList(selectList, sites), 0);
	}
	TRY(typifyList(predicateList, sites), 0);
	TRY(boolCheckList(predicateList), 0);
	sites->rewind();
	Site* inner = sites->get();
	sites->step();
	Site* siteGroup = NULL;
	while(!sites->atEnd()){
		Site* outer = sites->get();
		siteGroup = new SiteGroup(inner, outer);
		inner = siteGroup;
		siteGroup->filter(selectList, predicateList);
		siteGroup->typify(option);
		sites->step();
	}
	if(!siteGroup){
		siteGroup = inner;
	}
	LOG(logFile << "Plan: \n";)
	LOG(siteGroup->display(logFile, DETAIL);)
	LOG(logFile << endl;)
	assert(predicateList->cardinality() == 0);
	LOG(logFile << "Enumeration:\n";)
	typeIDs = getTypesFromList(siteGroup->getSelectList());
	attributeNames = getStringsFrom(selectList);
	TRY(siteGroup->enumerate(), 0);
	LOG(siteGroup->display(logFile, DETAIL);)
	LOG(logFile << endl;)
	numFlds = siteGroup->getNumFlds();
	topNode = siteGroup;
	stats = siteGroup->getStats();
	delete selectList;	// destroy list too
	selectList = NULL;
	delete predicateList;	// destroy list too
	predicateList = NULL;
	return 0;
}
