#ifndef SITE_H
#define SITE_H

#include <assert.h>
#include "myopt.h"
#include "queue.h"
#include "types.h"
#include "exception.h"
#include "GeneralRead.h"
#include "StandardRead.h"
#include "url.h"

List<BaseSelection*>* createSelectList(String nm, GeneralRead* iterator);

class Site {
friend class LocalTable;
friend class SiteGroup;
protected:
	String name;
	GeneralRead* iterator;
	int numFlds;
	List<String*>* tables;
	List<BaseSelection*>* mySelect;
	List<TableAlias*>* myFrom;
	List<BaseSelection*>* myWhere;
	friend ostream& operator<<(ostream& out, Site* site);
	Stats* stats;
public:
	Site(String nm = "") : name(nm), iterator(NULL) {
		numFlds = 0;
		tables = new List<String*>;
		mySelect = new List<BaseSelection*>;
		myFrom = new List<TableAlias*>;
		myWhere = new List<BaseSelection*>;
		stats = NULL;
	}
	virtual ~Site(){
		delete iterator;
		delete tables;
		delete mySelect;	// delete only list
		delete myFrom;
		delete myWhere;	// delete everything
	//	delete stats;	     // fix this
	}
	virtual void addTable(TableAlias* tabName){
		myFrom->append(tabName);
		String* alias = tabName->alias;
		if(alias){
			tables->append(alias);
		}
		else{
			tables->append(tabName->table);
		}
	}
	bool have(String* tabName){
		tables->rewind();
		while(!tables->atEnd()){
			if(*tables->get() == *tabName){
				return true;
			}
			tables->step();
		}
		return false;
	}
	virtual bool have(Site* siteGroup){
		return this == siteGroup;
	}
	void filter(List<BaseSelection*>* select, List<BaseSelection*>* where);
	virtual void display(ostream& out, int detail = 0){
		if(detail > 0){
			 out << "Site " << name << ":\n"; 
			 if(stats){
				 out	<< " stats: ";
				 stats->display(out);
			 }
			 out << "\n query:";
		}
		out << "   select ";
		displayList(out, mySelect, ", ", detail);
		out << "\n   from ";
		displayList(out, myFrom, ", ");
		if(!myWhere->isEmpty()){
			out << "\n   where ";
			displayList(out, myWhere, " and ", detail);
		}
		out << ';';
	}
	String getName(){
		return name;
	}
	virtual List<Site*>* getList(){
		List<Site*>* tmp = new List<Site*>;
		tmp->append(this);
		return tmp;
	}
	virtual void enumerate(){}
     virtual void typify(String option);	// Throws a exception
	virtual Tuple* getNext(){
		assert(iterator);
		return iterator->getNext();
	}
	virtual int getNumFlds(){
		return numFlds;
	}
	List<BaseSelection*>* getSelectList(){
		return mySelect;
	}
	virtual Stats* getStats(){
		return stats;
	}
	void reset(int lowRid, int highRid){
		TRY(iterator->reset(lowRid, highRid), );
	}
};

class DirectSite : public Site {
public:
	DirectSite(String nm, GeneralRead* iterator) : Site(nm) {
		
		// Used only for typifying LocalTable

		assert(iterator);
		Site::iterator = iterator;
		numFlds = iterator->getNumFlds();
		stats = iterator->getStats();
		assert(stats);
		mySelect = createSelectList(nm, iterator);
	}
};

class LocalTable : public Site {
	Site* directSite;
	void setStats(){
		double selectivity = listSelectivity(myWhere);
		assert(directSite);
		Stats* baseStats = directSite->getStats();
		assert(baseStats);
		int cardinality = int(selectivity * baseStats->cardinality);
		int* sizes = sizesFromList(mySelect);
		stats = new Stats(numFlds, sizes, cardinality);
	}
public:
     LocalTable(String nm, GeneralRead* marsh = NULL) : 
		Site(nm), directSite(NULL) {
		iterator = marsh;
	}
	virtual ~LocalTable(){}
	virtual void addTable(TableAlias* tabName){
		assert(myFrom->isEmpty());
		myFrom->append(tabName);
		String* alias = tabName->alias;
		if(alias){
			tables->append(alias);
			name = *alias;
		}
		else{
			tables->append(tabName->table);
			name = *tabName->table;
		}
	}
	virtual void enumerate(){
		assert(directSite);
		List<BaseSelection*>* baseSchema = directSite->getSelectList();
		TRY(enumerateList(mySelect, name, baseSchema), );
		TRY(enumerateList(myWhere, name, baseSchema), );
	}
	virtual void typify(String option){	// Throws exception
		
		// option is ignored since the execution = profile + getNext

		LOG(logFile << "Header: ");
		LOG(iterator->display(logFile));
		directSite = new DirectSite(name, iterator);
		List<Site*>* tmpL = new List<Site*>;
		tmpL->append(directSite);
          TRY(typifyList(myWhere, tmpL), );
		TRY(boolCheckList(myWhere), );
		if(mySelect == NULL){
			mySelect = createSelectList(name, iterator);
		}
		else{
			TRY(typifyList(mySelect, tmpL), );
		}
		numFlds = mySelect->cardinality();
		setStats();
     }
	virtual Tuple* getNext(){
		bool cond = false;
		Tuple* input = NULL;
		while(!cond){
			input = iterator->getNext();
			if(!input){
				return NULL;
			}
			cond = evaluateList(myWhere, input);
		}
		if(input){
			return tupleFromList(mySelect, input);
		}
		else{
			return NULL;
		}
	}
	virtual int getNumFlds(){
		return numFlds;
	}
};

class CGISite : public LocalTable {

	struct Entry{
		String option;
		String value;
		istream& read(istream& in);	// throws
	};

	Entry* entry;
	int entryLen;
	String urlString;
public:
	CGISite(String url, Entry* entry, int entryLen) : 
		LocalTable(""), entry(entry), entryLen(entryLen), urlString(url) {}
	virtual ~CGISite(){
		delete [] entry;
	}
	virtual void typify(String option);
};

class SiteGroup : public Site {
	List<Site*>* sites;
	Site* site1;
	Site* site2;
	List<Tuple*> innerRel;
	bool firstEntry;
	bool firstPass;
	Tuple* outerTup;
public:
	SiteGroup(Site* s1, Site* s2) : Site(""), site1(s1), site2(s2){
		sites = new List<Site*>;
		List<Site*>* tmp1 = site1->getList();
		List<Site*>* tmp2 = site2->getList();
		sites->addList(tmp1);
		sites->addList(tmp2);
		sites->rewind();
		assert(!sites->atEnd());
		name = sites->get()->getName();
		sites->step();
		while(!sites->atEnd()){
			name += "+" + sites->get()->getName();
			sites->step();
		}
		delete tmp1;
		delete tmp2;
		firstEntry = true;
		firstPass = true;
		outerTup = NULL;
	}
	virtual ~SiteGroup(){
//		delete sites;	// list only PROBLEm
		delete site1;
		delete site2;
	}
	virtual bool have(Site* siteGroup){
		List<Site*>* checkList = siteGroup->getList();
		checkList->rewind();
		while(!checkList->atEnd()){
			Site* checkSite = checkList->get();
			sites->rewind();
			while(true){
				if(sites->atEnd()){
					return false;
				}
				if(sites->get() == checkSite){
					break;
				}
				sites->step();
			}
			checkList->step();
		}
		delete checkList;
	     return true;	
	}
	virtual List<Site*>* getList(){
		return sites->duplicate();
	}
	virtual void enumerate(){
		TRY(enumerateList(mySelect, site1->getName(), site1->mySelect, 
			site2->getName(), site2->mySelect), );
		TRY(enumerateList(myWhere, site1->getName(), site1->mySelect, 
			site2->getName(), site2->mySelect), );
		TRY(site1->enumerate(), );
		TRY(site2->enumerate(), );
	}
	virtual void display(ofstream& out, int detail = 0){
		Site::display(out, detail);
		out << endl;
		out << "   children: " << site1->name << ", " << site2->name;
		out << endl;
		site1->display(out, detail);
		out << endl;
		site2->display(out, detail);
	}
	virtual Tuple* getNext(){
		bool cond = false;
		Tuple* innerTup = NULL;
		if(firstEntry){
			outerTup = site1->getNext();
			firstEntry = false;
		}
		while(cond == false){
			if(firstPass){
				innerTup = site2->getNext();
				if(innerTup){
					innerRel.append(innerTup);
				}
				else{
					firstPass = false;
					innerRel.rewind();
					if(innerRel.atEnd()){
						return NULL;
					}
					innerTup = innerRel.get();
					innerRel.step();
					outerTup = site1->getNext();
				}
			}
			else{
				if(innerRel.atEnd()){
					innerRel.rewind();
					outerTup = site1->getNext();
				}
				innerTup = innerRel.get();
				innerRel.step();
			}
			assert(innerTup);
			if(!outerTup){
				return NULL;
			}
			cond = evaluateList(myWhere, outerTup, innerTup);
		}
		assert(outerTup);
		return tupleFromList(mySelect, outerTup, innerTup);
	}
	virtual int getNumFlds(){
		return mySelect->cardinality();
	}
	virtual void typify(String option){	// Throws exception
		
		List<Site*>* tmpL = new List<Site*>;
		tmpL->append(site1);
		tmpL->append(site2);
		if(mySelect == NULL){
			mySelect = createSelectList(name, iterator);
		}
		else{
			TRY(typifyList(mySelect, tmpL), );
		}
		numFlds = mySelect->cardinality();
          TRY(typifyList(myWhere, tmpL), );
		double selectivity = listSelectivity(myWhere);
		int card1 = site1->getStats()->cardinality;
		int card2 = site2->getStats()->cardinality;
		int cardinality = int(selectivity * card1 * card2);
		int* sizes = sizesFromList(mySelect);
		stats = new Stats(numFlds, sizes, cardinality);
		TRY(boolCheckList(myWhere), );
     }
};

#endif
