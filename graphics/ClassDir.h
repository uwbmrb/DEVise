/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2000
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
  Revision 1.15  2000/03/30 16:26:57  wenger
  Added printInstances command; destroy command now reports an error
  if the instance is not found.

  Revision 1.14  2000/03/28 18:57:09  wenger
  Increased max instances per class to 1000.

  Revision 1.13  2000/02/16 18:51:19  wenger
  Massive "const-ifying" of strings in ClassDir and its subclasses.

  Revision 1.12  2000/01/13 23:06:50  wenger
  Got DEVise to compile with new (much fussier) compiler (g++ 2.95.2).

  Revision 1.11  1999/09/24 22:02:18  wenger
  C++ code no longer allows a session to be opened while one is already
  open.

  Revision 1.10  1998/11/11 14:30:41  wenger
  Implemented "highlight views" for record links and set links; improved
  ClassDir::DestroyAllInstances() by having it destroy all links before
  it destroys anything else -- this cuts down on propagation problems as
  views are destroyed; added test code for timing a view's query and draw.

  Revision 1.9  1998/05/14 18:20:58  wenger
  New protocol for JavaScreen opening sessions works (sending "real" GIF)
  except for the problem of spaces in view and window names.

  Revision 1.8  1998/05/06 22:04:40  wenger
  Single-attribute set links are now working except where the slave of
  one is the master of another.

  Revision 1.7  1998/04/14 21:03:06  wenger
  TData attribute links (aka set links) are working except for actually
  creating the join table, and some cleanup when unlinking, etc.

  Revision 1.6  1996/05/11 19:09:52  jussi
  Minor fix.

  Revision 1.5  1996/05/11 01:54:28  jussi
  Added DestroyAllInstances() method.

  Revision 1.4  1996/04/13 23:39:38  jussi
  Added copyright notice and cleaned up the code a bit.

  Revision 1.3  1995/09/09 00:24:52  jussi
  Increased MaxClasses from 50 to 100.

  Revision 1.2  1995/09/05 21:12:26  jussi
  Added/update CVS header.
*/

#ifndef ClassDir_h
#define ClassDir_h

#include "DeviseTypes.h"

/*
   class information. This is set up to store both class and instance
   information. For classInfo, only methods dealing with class are
   used. For instance info, methods dealing with instances are alos used
*/

class InstanceInfo;

class ClassInfo {
public:
	ClassInfo();
	virtual ~ClassInfo();

	/* Set/test transient status. A transient class is destroyed
	upon closing a session */
	void SetTransient(Boolean transient) { _transient = transient; }
	Boolean IsTransient() { return _transient; }

	/* Info for category */
	virtual const char *CategoryName() = 0;

	/* Info for class */
	virtual const char *ClassName()=0; 	/* name of class */

	/* Get name of parameters and default/current values */
	virtual void ParamNames(int &argc, const char **&argv) = 0;

	/* Create instance using the supplied parameters. Return 
	the instance info if successful, otherwise return NULL. */
	virtual ClassInfo *CreateWithParams(int argc,
	    const char * const *argv) = 0;

	/* Return true is parameters can be changed dynamically at run time */
	virtual Boolean Changeable() { return false; }

	/* Change parameters dynamically at run time */
	virtual void ChangeParams(int argc, const char * const *argv){};


	/* Set default parameters */
	void SetDefaultParams(int argc, const char * const *argv);

	/* Get default parameters */
	void GetDefaultParams(int &argc, const char **&argv);

	/* Get user info */
	virtual void *UserInfo() { return 0; }

	/**************************************************
	Instance Info. 
	***************************************************/
	virtual const char *InstanceName();
	virtual void *GetInstance();

	/* Get parameters that can be used to re-create this instance */
	virtual void CreateParams(int &argc, const char **&argv);

private:
	char **_defaultParams;
	int _numDefaultParams;
	Boolean _transient; /* true if a transient class */
};


const int MaxCategories = 10;	/* max # of categories */
const int MaxClasses = 100;	/* # of classes for each category */
const int MaxInstances = 1000;	/* # of instances for each class */

struct ClassRec {
	ClassInfo *classInfo;
	int _numInstances;
	ClassInfo *_instances[MaxInstances];
};

struct CategoryRec {
	const char *name;
	ClassRec *_classRecs[MaxClasses];
	int _numClasses;
};

class ClassDir {
public:
	ClassDir();

	void InsertCategory(const char *name);
	void InsertClass(ClassInfo *cInfo);

	/* Get name of all classes in a category */
	void ClassNames(const char *category, int &numClasses,
	                const char **&classNames);

	/* Get creation parameters for a class */
	void GetParams(const char *category, const char *className, 
		int &numParams, const char **&paramNames);
	void GetParams(const char *inst, int &numParams,
	    const char **&paramNames);

	/* Get user info for a class */
	void *UserInfo(const char *category, const char *className);

	/* Set default parameter values for a class */
	void SetDefault(const char *category, const char *className,
	                int numParams, char **params);

	/* Create a new instance with parameters. Return the name  of
	new instance, or NULL if not successful */
	const char *CreateWithParams(const char *category,
	    const char *className, int numParams,
	    const char * const *paramNames);


	/* Get name of all instances for a given class */
	void InstanceNames(const char *category, const char *className,
		int &num, const char **&instanceNames);

	/* Get pointer to all instances for a given class */
	void InstancePointers(const char *category, const char *className,
		int &num, char **&instancePointers);

	/* Find instance with given name */
	void *FindInstance(const char *name);

	/* Find name for instance */
	const char *FindInstanceName(const void *instance);

	/* Find ClassInfo object for a given instance */
	ClassInfo *FindClassInfo(const char *instanceName);

	/* Destroy all instances */
	void DestroyAllInstances();

	/* Destroy all classes and instances in at category */
	void DestroyCategory(const char *categoryName);

	/* Destroy an instance; returns true if okay */
	Boolean DestroyInstance(const char *instanceName);

	/* Destroy all transient classes */
	void DestroyTransientClasses();

	/* Return true if instance is changeable */
	Boolean Changeable(const char *name);

	/* Change with params */
	void ChangeParams(const char *instance, int num, char **paramNames);

	/* Get the creation parameters for an instance */
	void CreateParams(const char *category, const char *className,
	                  const char *instanceName, int &numParams,
			  const char **&params);

	void Print();

	int InstanceCount() { return _instanceCount; }

private:
	CategoryRec *_categories[MaxCategories];
	int _numCategories;
	Boolean _destroyingAll;
	int _instanceCount;
};

#endif
