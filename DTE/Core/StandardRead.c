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
  Revision 1.22  1998/06/28 21:47:42  beyer
  major changes to the interfaces all of the execution classes to make it easier
  for the plan reader.

  Revision 1.21  1998/03/17 17:19:03  donjerko
  Added new namespace management through relation ids.

  Revision 1.20  1997/11/13 22:19:24  okan
  Changes about compilation on NT

  Revision 1.19  1997/11/12 23:17:34  donjerko
  Improved error checking.

  Revision 1.18  1997/11/05 00:19:41  donjerko
  Separated typechecking from optimization.

  Revision 1.17  1997/09/17 02:35:44  donjerko
  Fixed the broken remote DTE interface.

  Revision 1.16  1997/09/05 22:20:13  donjerko
  Made changes for port to NT.

  Revision 1.15  1997/08/22 23:13:04  okan
  Changed #include <string.h> 's to #include <string>

  Revision 1.14  1997/08/21 21:04:26  donjerko
  Implemented view materialization

  Revision 1.13  1997/08/12 19:58:42  donjerko
  Moved StandardTable headers to catalog.

  Revision 1.12  1997/06/30 23:05:03  donjerko
  CVS:

  Revision 1.11  1997/06/21 22:48:04  donjerko
  Separated type-checking and execution into different classes.

  Revision 1.10  1997/06/16 16:04:45  donjerko
  New memory management in exec phase. Unidata included.

  Revision 1.9  1997/04/10 21:50:25  donjerko
  Made integers inlined, added type cast operator.

  Revision 1.8  1997/03/23 23:45:21  donjerko
  Made boolean vars to be in the tuple.

  Revision 1.7  1997/02/18 18:06:02  donjerko
  Added skeleton files for sorting.

  Revision 1.6  1997/02/03 04:11:32  donjerko
  Catalog management moved to DTE

  Revision 1.5  1996/12/24 21:00:52  kmurli
  Included FunctionRead to support joinprev and joinnext

  Revision 1.4  1996/12/21 22:21:46  donjerko
  Added hierarchical namespace.

  Revision 1.3  1996/12/16 11:13:07  kmurli
  Changes to make the code work for separate TDataDQL etc..and also changes
  done to make Aggregates more robust

  Revision 1.2  1996/12/05 16:06:00  wenger
  Added standard Devise file headers.

 */

#include "sysdep.h"
//#include <strstream.h>   erased for sysdep.h
#include <string>
#include "StandardRead.h"
#include "exception.h"
#include "assert.h"
#include "url.h"
#include "ExecOp.h"

StandReadExec::StandReadExec(const TypeIDList& typeIDs, istream* in,
                             const string& url)
: types(typeIDs), in(in), url(url)
{
  numFlds = types.size();
  readPtrs = getReadPtrs(types);
  tuple = allocateTuple(types);
  first_pass = true;
}


StandReadExec::StandReadExec(const TypeIDList& typeIDs, const string& url)
: types(typeIDs), in(in), url(url)
{
  URL url(url);
  in = url.getInputStream();
  numFlds = types.size();
  readPtrs = getReadPtrs(types);
  tuple = allocateTuple(types);
  first_pass = true;
}


StandReadExec::StandReadExec(int numFlds, const TypeID* typeIDs, istream* in,
                             string url)
: types(), in(in), url(url)
{
  this->numFlds = numFlds;
  for(int i = 0 ; i < numFlds ; i++) {
    types.push_back(typeIDs[i]);
  }
  //kb: should typeIDs be deleted?? looks like sometimes yes, sometimes no
  // delete [] typeIDs;
  readPtrs = getReadPtrs(types);
  tuple = allocateTuple(types);
  first_pass = true;
}


StandReadExec::~StandReadExec()
{
  delete in;
  deleteTuple(tuple, types);
}


void StandReadExec::initialize()
{
  if( !first_pass ) {
    // check for first pass because this could fail...
    in->seekg(0, ios::beg);
    if( !in->good() ) {
      cerr << "attempt to rewind from bad stream in StandReadExec\n";
    }
  }
  first_pass = false;
  currentLine = 1;
}


const Tuple* StandReadExec::getNext()
{
  assert(in);
  for(int i = 0; i < numFlds; i++) {
    readPtrs[i](*in, ((Type**)tuple)[i]);
    if(currExcept) {
      ostringstream tmp;
      tmp << "Line " << currentLine << " of " << url << ends;
      currExcept->append(tmp.str());
      return NULL;
    }
  }
  currentLine++;
  if(in->good()) {
    return tuple;
  }
  else {
    return NULL;
  }
}


const Tuple* StandReadExec::getThis(Offset offset)
{
  assert(in);
  if( offset.isNull() ) {
    return NULL;
  }
  currentLine = -9999999;
  streampos pos = offset.offset;
  in->seekg(pos, ios::beg);
  if( !in->good() ) {
    cerr << "attempt to seek from bad stream in StandReadExec\n";
    return NULL;
  }
  return StandReadExec::getNext();
}


Offset StandReadExec::getOffset()
{
  assert(in);
  streampos pos = in->tellg();
  if( !in->good() ) {
    cerr << "attempt to get offset from bad stream in StandReadExec\n";
    return Offset();
  }
  return Offset(pos);
}


const TypeIDList& StandReadExec::getTypes()
{
  return types;
}


//---------------------------------------------------------------------------


void StandardRead::open(istream* in, int numFlds, const TypeID* typeIDs){
	this->numFlds = numFlds;
	this->typeIDs = new TypeID[numFlds];
	assert(in && in->good());
	this->in = in;
	for(int i = 0; i < numFlds; i++){
		this->typeIDs[i] = typeIDs[i];
	}
}

void StandardRead::open(const ISchema& schema, istream* in, 
	const string& urlStr)
{
	this->numFlds = schema.getNumFlds();
	this->typeIDs = new TypeID[numFlds];
	this->attributeNames = new string[numFlds];
	this->urlStr = urlStr;
	for(int i = 0; i < numFlds; i++){
		typeIDs[i] = schema.getTypeIDs()[i];
		attributeNames[i] = schema.getAttributeNames()[i];
	}
	assert(in && in->good());
	this->in = in;
}

Iterator* RidAdder::createExec(){
	TRY(Iterator* inpIter = input->createExec(), NULL);
	return new RidAdderExec(inpIter);
}

void NCDCRead::open(istream* in){	// Throws exception
     char buff[100];
     ostringstream err;
     while(in->good()){
          in->read(buff, 100);
          err.write(buff, in->gcount());
     }
     err << ends;
     string response = err.str();
     char* tmp = strdup(response.c_str());

     // find the third occurence of "http:"

     assert(tmp);
     for(int i = 0; i < 3; i++){
          tmp = tmp + 1;
          tmp = strstr(tmp, "http:");
          if(!tmp){
               string msg = "Unexpected response from the NCDC server:\n" +
                    response;
               THROW(new Exception(msg), NVOID);
			// throw Exception(msg);
          }
     }
     int j = 0;
     while(tmp[j] != '"' && tmp[j]){
          j++;
     }
     assert(tmp[j]);
     tmp[j] = '\0';
     string tableUrlStr = string(tmp);
     URL* tableUrl = new URL(tableUrlStr);
	istream* tablein = NULL;
     TRY(tablein = tableUrl->getInputStream(), NVOID );
	delete tableUrl;

     // ignore first 8 lines

     for(int k = 0; k < 8; k++){
          assert(*tablein);
          tablein->getline(buff, 100);
     }

     numFlds = 2;
	typeIDs = new string[numFlds];
     typeIDs[0] = "int";
     typeIDs[1] = "int";
	attributeNames = new string[numFlds];
	attributeNames[0] = "day";
	attributeNames[1] = "temp";
	stats = new Stats(numFlds);
	in = tablein;
}

RidAdder::RidAdder(PlanOp* input) : input(input) {
	numFlds = input->getNumFlds() + 1;
	typeIDs = new TypeID[numFlds];
	attributeNames = new string[numFlds];
	const TypeID* inpTypes = input->getTypeIDs();
	const string* inpAttrs = input->getAttributeNames();
	typeIDs[0] = INT_TP;
	attributeNames[0] = RID_STRING;
	for(int i = 1; i < numFlds; i++){
		typeIDs[i] = inpTypes[i - 1];
		attributeNames[i] = inpAttrs[i - 1];
	}
}
