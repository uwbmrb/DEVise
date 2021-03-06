/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2008
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  Description of module.
 */

/*
  $Id$
 */
#ifndef _CMD_SERIALIZE_H
#define _CMD_SERIALIZE_H

using namespace std;

#include <string>
#include <vector>

class Serializable
{
	static	const char* intMarker;
	public:
		enum{
			UNDEFINED = 0,
			TYP_COMPOSITE,
			TYP_INT, 
			TYP_LONG, 
			TYP_BOOL, 
			TYP_CHAR, 
			TYP_FLOAT,
			TYP_STRING,
		};
		enum{
			INT_SIZE = 16
		};
		Serializable();
		virtual ~Serializable(){}

	protected:
		virtual string raw_serialize(int);
		virtual string composite_serialize(int argc, string body);
		virtual string composite_serialize(int argc, ...);
		virtual int composite_deserialize(string body, vector<string>& vec);

		virtual string serialize(int);
		virtual string serialize(long);
		virtual string serialize(bool);
		virtual string serialize(char);
		virtual string serialize(float);
		virtual string serialize(string);
		virtual string serialize(int, const char**);
		virtual void deserialize(string& str, int& typeId, string& value);
	private:
		void check(int);
};
#endif
