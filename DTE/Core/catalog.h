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
  Revision 1.16  1997/06/30 23:05:05  donjerko
  CVS:

  Revision 1.15  1997/06/21 22:48:06  donjerko
  Separated type-checking and execution into different classes.

  Revision 1.14  1997/06/16 16:04:48  donjerko
  New memory management in exec phase. Unidata included.

  Revision 1.11  1997/02/25 22:14:53  donjerko
  Enabled RTree to store data attributes in addition to key attributes.

  Revision 1.10  1997/02/18 18:06:03  donjerko
  Added skeleton files for sorting.

  Revision 1.9  1997/02/03 04:11:34  donjerko
  Catalog management moved to DTE

  Revision 1.8  1996/12/24 21:00:52  kmurli
  Included FunctionRead to support joinprev and joinnext

  Revision 1.7  1996/12/21 22:21:47  donjerko
  Added hierarchical namespace.

  Revision 1.6  1996/12/15 06:41:07  donjerko
  Added support for RTree indexes

  Revision 1.5  1996/12/07 15:14:27  donjerko
  Introduced new files to support indexes.

  Revision 1.4  1996/12/05 16:06:01  wenger
  Added standard Devise file headers.

 */

#ifndef CATALOG_H
#define CATALOG_H

#include <assert.h>
#include <limits.h>
#include "queue.h"
#include "exception.h"
#include "site.h"
#include "Utility.h"
/*
#ifdef NO_RTREE
     #include "RTreeRead.dummy"
#else
     #include "RTreeRead.h"
#endif
*/

const int INFINITY = INT_MAX;

class Inserter;

class Catalog {
private:
	String fileName;
public:
	Catalog(String fileName) : fileName(fileName) {
	}
	Site* find(TableName* path);     // Throws Exception
	Interface* findInterface(TableName* path);	// Throws exception
	void write(String fileNm){
		ofstream out(fileNm);
		assert(!"not implemented");
	}
};

class Interface{
public:
	enum Type {UNKNOWN, CATALOG, QUERY};
	Interface() {}
	virtual Interface* duplicate() const = 0;
	virtual ~Interface(){}
	virtual Site* getSite() = 0;
	virtual istream& read(istream& in) = 0;
	virtual ostream* getOutStream(){
		assert(0);
	}
	virtual String getFileName(){
		assert(0);
	}
	virtual void write(ostream& out){
	}
	virtual Type getType(){
		return UNKNOWN;
	}
	virtual const ISchema* getISchema(TableName* table) = 0;	// throws
	virtual Inserter* getInserter(TableName* table){ // throws
		THROW(new Exception("Insertion not supported"), NULL);
	}
};

class DummyInterface : public Interface {
	String key;
	String schemaType;
	String schemaFile;
	String cacheFile;	// quoted
	int evaluation;
	int priority;
	String command;	// quoted
	String segment;	// quoted
public:
	DummyInterface() {}
	virtual ~DummyInterface(){}
	virtual DummyInterface* duplicate() const {
		return new DummyInterface(*this);	
	}
	virtual Site* getSite(){
		String err = "Operations on old DEVise table are not supported";
		THROW(new Exception(err), NULL);
	}
	virtual istream& read(istream& in){
		if(!in){
			THROW(new Exception("Wrong format"), in);
		}
		in >> key >> schemaType >> schemaFile;
		TRY(cacheFile = stripQuotes(in), in);
		in >> evaluation >> priority;
		TRY(command = stripQuotes(in), in);
		TRY(segment = stripQuotes(in), in);
		return in;
	}
	virtual void write(ostream& out){
		out << " " << key << " " << schemaType << " " << schemaFile; 
		out << " " << addQuotes(cacheFile) << " " << evaluation;
		out << " " << priority << " " << addQuotes(command);
		out << " " << addQuotes(segment);
	}
	virtual const ISchema* getISchema(TableName* table){
		String msg = "ISchema lookup not supported for UNIXFILEs";
		THROW(new Exception(msg), NULL);
	}
};

class ViewInterface : public Interface {
	String tableNm;
	int numFlds;
	String* attributeNames;
	String query;
public:
	ViewInterface(String tableNm) : tableNm(tableNm), attributeNames(NULL) {
		// cout << "ViewInterface constructor" << endl;
	}
	ViewInterface(int numFlds, String* attributeNames, String query) 
		: numFlds(numFlds), attributeNames(attributeNames), query(query) {
		// cout << "ViewInterface constructor" << endl;
	}
	ViewInterface(const ViewInterface& a){
		tableNm = a.tableNm;
		numFlds = a.numFlds;
		attributeNames = new String[numFlds];
		for(int i = 0; i < numFlds; i++){
			attributeNames[i] = a.attributeNames[i];
		}
		query = a.query;
	}
	virtual ~ViewInterface(){
		// cout << "~ViewInterface destuctor" << endl;
		delete [] attributeNames;
	}
	virtual ViewInterface* duplicate() const {
		return new ViewInterface(*this);
	}
	virtual Site* getSite();
	virtual istream& read(istream& in);
	virtual void write(ostream& out);
	virtual const ISchema* getISchema(TableName* table){
		assert(table);
		assert(table->isEmpty());
		assert(attributeNames);
		String* retVal = attributeNames;
		attributeNames = NULL;
		return new ISchema(retVal, numFlds);
	}
};

class DeviseInterface : public Interface{
	String tableNm;
	String schemaNm;
	String dataNm;
	String viewNm;
public:
	DeviseInterface(String tableNm) : tableNm(tableNm){}
	virtual ~DeviseInterface(){}
	virtual DeviseInterface* duplicate() const {
		return new DeviseInterface(*this);
	}
	virtual Site* getSite();
	virtual istream& read(istream& in){
		in >> schemaNm >> dataNm;
		viewNm = stripQuotes(in);
		return in;
	}
	virtual void write(ostream& out){
		out << " " << schemaNm << endl;
		out << "\t" << dataNm << endl;
		out << "\t" << addQuotes(viewNm);
		Interface::write(out);
	}
	virtual const ISchema* getISchema(TableName* table);
};

class StandardInterface : public Interface{
	String urlString;
public:
	StandardInterface() {}
	StandardInterface(String urlString) : urlString(urlString){}
	virtual StandardInterface* duplicate() const {
		return new StandardInterface(*this);
	}
	virtual Site* getSite();
	virtual istream& read(istream& in){
		return in >> urlString;
	}
	virtual void write(ostream& out){
		out << " " << urlString;
		Interface::write(out);
	}
	virtual const ISchema* getISchema(TableName* table);	// throws exception
	virtual Inserter* getInserter(TableName* table); // throws
};

class QueryInterface : public Interface{
	String urlString;
	Site* site;	// not the owner? has to fix this
public:
	QueryInterface(){}
	virtual ~QueryInterface(){}
	virtual QueryInterface* duplicate() const {
		return new QueryInterface(*this);
	}
	virtual Site* getSite(){
		return site;
	}
	virtual istream& read(istream& in){
		in >> urlString;
		site = new Site(urlString);
		return in;
	}
	virtual void write(ostream& out){
		out << " " << urlString;
		Interface::write(out);
	}
	virtual Type getType(){
		return QUERY;
	}
	virtual const ISchema* getISchema(TableName* table);	// throws exception
};

class CGIInterface : public Interface{
	String tableNm;
	String urlString;
	int entryLen;
	CGISite::Entry* entries;
public:
	CGIInterface(String tableNm) : tableNm(tableNm), entries(NULL) {}
	virtual ~CGIInterface(){
		delete [] entries;
	}
	CGIInterface(const CGIInterface& a){
		tableNm = a.tableNm;
		urlString = a.urlString;
		entryLen = a.entryLen;
		entries = new CGISite::Entry[entryLen];
		for(int i = 0; i < entryLen; i++){
			entries[i] = a.entries[i];
		}
	}
	virtual CGIInterface* duplicate() const {
		return new CGIInterface(*this);
	}
	virtual Site* getSite(){
		assert(entries);
		Site* site = new CGISite(urlString, entries, entryLen);
		// CGISite is the owner of the entries
		return site;
	}
	virtual istream& read(istream& in);  // throws
	virtual void write(ostream& out){
		assert(entries);
		out << " " << urlString << " " << entryLen;
		for(int i = 0; i < entryLen; i++){
			out << endl;
			out << "\t";
			entries[i].write(out);
		}
		Interface::write(out);
	}
	virtual const ISchema* getISchema(TableName* table){
		String msg = "ISchema lookup not yet implemented for CGIs";
		THROW(new Exception(msg), NULL);
	}
};

class CatalogInterface : public Interface {
	String fileName;
public:
	CatalogInterface() {}
	virtual CatalogInterface* duplicate() const {
		return new CatalogInterface(*this);
	}
	virtual String getFileName(){
		return fileName;
	}
	virtual Site* getSite();
	virtual istream& read(istream& in){
		return in >> fileName;
	}
	virtual void write(ostream& out){
		out << " " << fileName;
		Interface::write(out);
	}
	virtual String getCatalogName(){	// throws
		return fileName;
	}
	virtual Type getType(){
		return CATALOG;
	}
	virtual const ISchema* getISchema(TableName* table);	// throws exception
};

#endif
