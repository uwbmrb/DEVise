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
  Revision 1.3  1996/05/07 16:46:21  jussi
  This class now makes a copy of the attribute list so that attribute
  hi/lo values can be maintained per data stream, not per schema.
  Hi/lo values are now computed after composite parser is executed.

  Revision 1.2  1996/05/05 03:08:37  jussi
  Added support for composite attributes. Also added tape drive
  support.

  Revision 1.1  1996/01/23 20:54:51  jussi
  Initial revision.
*/

#ifndef TDataBinaryInterp_h
#define TDataBinaryInterp_h

#include "DeviseTypes.h"
#include "ClassDir.h"
#include "TDataBinary.h"
#include "AttrList.h"

class TDataBinaryInterpClassInfo: public ClassInfo {
public:
  TDataBinaryInterpClassInfo(char *className, AttrList *attrList, int recSize);
	
  TDataBinaryInterpClassInfo(char *className, char *name, char *alias,
			    TData *tdata);
  virtual ~TDataBinaryInterpClassInfo();

  /* Info for category */
  virtual char *CategoryName(){ return "tdata"; } 

  /* Info for class */
  virtual char *ClassName();    /* name of class */

  /* Get name of parameters and default/current values */
  virtual void ParamNames(int &argc, char **&argv);

  /* Create instance using the supplied parameters. Return
     the instance info if successful, otherwise return NULL. */
  virtual ClassInfo *CreateWithParams(int argc, char **argv);

  /**************************************************
    Instance Info.
  ***************************************************/
  virtual char *InstanceName();
  virtual void *GetInstance();

  /* Get parameters that can be used to re-create this instance */
  virtual void CreateParams(int &argc, char **&argv);

private:
  char *_className;
  char *_name;
  char *_alias;
  TData *_tdata;
  int _recSize;
  int _physRecSize;
  AttrList *_attrList;
};

class RecInterp;

class TDataBinaryInterp: public TDataBinary {
public:
  TDataBinaryInterp(char *name, char *alias, int recSize,
		    int physRecSize, AttrList *attrs);
  virtual ~TDataBinaryInterp();

  AttrList *GetAttrList() { return &_attrList; }

protected:
  /* Copy record to buffer. Return false if invalid record. */
  virtual Boolean Decode(void *recordBuf, int recPos, char *line);
  
  virtual void InvalidateCache();
  virtual Boolean WriteCache(int fd);
  virtual Boolean ReadCache(int fd);

private:
  AttrList _attrList;  /* list of attributes */
  Boolean hasComposite;
  char *_name;
  int _recSize;
  int _physRecSize;
  int _numAttrs;       /* number of attributes (including composite) */
  int _numPhysAttrs;   /* number of physical attributes */
  RecInterp *_recInterp;
};

#endif
