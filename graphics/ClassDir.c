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
  Revision 1.12  1997/03/23 23:46:00  donjerko
  *** empty log message ***

  Revision 1.11  1997/03/21 22:15:37  guangshu
  Comment line ellimination.

  Revision 1.10  1997/03/21 16:15:42  guangshu
  Minor changes corresponding to DTE change in FindInstance.

  Revision 1.9  1996/10/08 21:49:00  wenger
  ClassDir now checks for duplicate instance names; fixed bug 047
  (problem with FileIndex class); fixed various other bugs.

  Revision 1.8  1996/09/27 21:08:59  wenger
  GDataBin class doesn't allocate space for connectors (no longer used
  anyhow); fixed some more memory leaks and made notes in the code about
  some others that I haven't fixed yet; fixed a few other minor problems
  in the code.

  Revision 1.7  1996/07/05 15:08:46  jussi
  Added debugging statement.

  Revision 1.6  1996/07/02 22:43:56  jussi
  Replaced Exit() calls with DOASSERT().

  Revision 1.5  1996/05/11 01:54:35  jussi
  Added DestroyAllInstances() method.

  Revision 1.4  1996/04/16 00:17:33  jussi
  Fixed bug in DestroyInstance() and DestroyTransientClasses(). The
  array of instances/classes was improperly shifted (one-off error).

  Revision 1.3  1996/04/14 00:15:35  jussi
  Added copyright notice and cleaned up the code quite a bit.
  Fixed bug in Print() method.

  Revision 1.2  1995/09/05 21:12:26  jussi
  Added/updated CVS header.
*/

#include <stdio.h>

#include "ClassDir.h"
#include "Exit.h"
#include "Util.h"

//#define DEBUG
#define CHECK_CLASS_RECS 0

ClassDir::ClassDir()
{
  _numCategories = 0;
}

void ClassDir::InsertCategory(char *name)
{
  DOASSERT(_numCategories < MaxCategories, "Too many categories");

  CategoryRec *rec = new CategoryRec;
  rec->name = name;
  rec->_numClasses = 0;
  _categories[_numCategories++] = rec;
#if CHECK_CLASS_RECS
  for (int classIndex = 0; classIndex < MaxClasses; classIndex++) {
    rec->_classRecs[classIndex] = NULL;
  }
#endif
}

void ClassDir::InsertClass(ClassInfo *cInfo)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name, cInfo->CategoryName())) {
      DOASSERT(catRec->_numClasses < MaxClasses, "Too many classes");
      ClassRec *classRec = new ClassRec;
      classRec->classInfo = cInfo;
      classRec->_numInstances = 0;
#if CHECK_CLASS_RECS
      DOASSERT(catRec->_classRecs[catRec->_numClasses] == NULL,
	"Leaked a ClassRec!");
#endif
      catRec->_classRecs[catRec->_numClasses++] = classRec;
      return;
    }
  }

  DOASSERT(0, "Could not find category");
}

#define ARG_ARRAY_SIZE 512
char *argArray[ARG_ARRAY_SIZE];

void ClassDir::ClassNames(char *category, int &num, char **&names)
{
  num = 0;
  names = argArray;

  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name, category)) {
      for(int j = 0; j < catRec->_numClasses; j++) {
	DOASSERT(num < ARG_ARRAY_SIZE, "ClassDir: argArray overflowed");
	argArray[num++] = catRec->_classRecs[j]->classInfo->ClassName();
      }
      return;
    }
  }
}

/* Get pointers to all instances */

void ClassDir::InstancePointers(char *category, char *className,
				int &num, char **&instanceNames)
{
  num = 0;
  instanceNames = argArray;

  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name, category)) {
      for(int j = 0; j < catRec->_numClasses; j++) {
	ClassRec *classRec = catRec->_classRecs[j];
	if (!strcmp(classRec->classInfo->ClassName(), className)) {
	  for(int k = 0; k < classRec->_numInstances; k++)
	    argArray[num++] = (char *)classRec->_instances[k]->GetInstance();
	  return;
	}
      }
    }
  }
}

/* Get names of all instances */

void ClassDir::InstanceNames(char *category, char *className,
			     int &num, char **&instanceNames)
{
  num = 0;
  instanceNames = argArray;

  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name,category)) {
      for(int j = 0; j < catRec->_numClasses; j++) {
	ClassRec *classRec = catRec->_classRecs[j];
	if (!strcmp(classRec->classInfo->ClassName(), className)) {
	  for(int k = 0; k < classRec->_numInstances; k++)
	    argArray[num++] = classRec->_instances[k]->InstanceName();
	  return;
	}
      }
    }
  }
}

/* Get creation parameters for a class */

void ClassDir::GetParams(char *category, char *className, 
			 int &numParams, char **&params)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name, category)) {
      for(int j = 0; j < catRec->_numClasses; j++) {
	ClassRec *classRec = catRec->_classRecs[j];
	if (!strcmp(classRec->classInfo->ClassName(), className)) {
	  classRec->classInfo->ParamNames(numParams, params);
	  return;
	}
      }
    }
  }

  /* not found */
  numParams = 0;
  params = NULL;
}

/* Set default values for class parameters*/

void ClassDir::SetDefault(char *category, char *className,
			  int numParams, char **params)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name, category)) {
      for(int j = 0; j < catRec->_numClasses; j++) {
	ClassRec *classRec = catRec->_classRecs[j];
	if (!strcmp(classRec->classInfo->ClassName(),className)) {
	  classRec->classInfo->SetDefaultParams(numParams, params);
	  return;
	}
      }
    }
  }
}

/* Create a new instance given the parameters */

char *ClassDir::CreateWithParams(char *category, char *className,
				 int numParams, char **paramNames)
{
#if defined(DEBUG) || 0
  for(int i = 0; i<numParams; i++) {
  	printf("In ClassDir: category=%s, className=%s, argv[%d]=%s\n", 
		 category, className, i, paramNames[i]);
  }
#endif
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name,category)) {
      for(int j = 0; j < catRec->_numClasses; j++) {
	ClassRec *classRec = catRec->_classRecs[j];
#if defined(DEBUG) || 0
	cout << "Comparing class " << className << " to "
		<< classRec->classInfo->ClassName() << endl;
#endif
	if (!strcmp(classRec->classInfo->ClassName(),className)) {
          DOASSERT(classRec->_numInstances < MaxInstances,
                   "Too many instances");
	  ClassInfo *iInfo = classRec->classInfo->CreateWithParams(numParams,
								   paramNames);
	  if (iInfo) {
	    if (FindInstance(iInfo->InstanceName()) != NULL) {
	      char errBuf[1024];
	      sprintf(errBuf, "Attempt to add duplicate instance name '%s'\n",
		iInfo->InstanceName());
	      Exit::DoAbort(errBuf, __FILE__, __LINE__);
	    }
	    classRec->_instances[classRec->_numInstances++] = iInfo;
	    return iInfo->InstanceName();
	  }
	  fprintf(stderr,
		  "Cannot create instance in class %s of category %s\n",
		  className, category);
	  return NULL;
	}
      }
      fprintf(stderr, "Cannot find class %s in category %s\n",
	      className, category);
      return NULL;
    }
  }

  fprintf(stderr, "Cannot find category %s\n", category);
  return NULL;
}

/* Find instance with given name */

void *ClassDir::FindInstance(char *name)
{
#if defined(DEBUG) || 0
  printf("Trying to find %s\n", name);
#endif
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    for(int j = 0; j < catRec->_numClasses; j++) {
      ClassRec *classRec = catRec->_classRecs[j];
      for(int k = 0; k < classRec->_numInstances; k++) {

//printf("In FindInstance, trying to compare with %s\n", classRec->_instances[k]->InstanceName());
	if (!strcmp(classRec->_instances[k]->InstanceName(), name)){
	  return classRec->_instances[k]->GetInstance();
	  }
	  else{
#ifdef DEBUG
	  	cout << "Comparing " << name << " to: " 
			<< classRec->_instances[k]->InstanceName()
			<< endl;
#endif
	}
      }
    }
  }

  return NULL;
}

/* Destroy all instances */

void ClassDir::DestroyAllInstances()
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    for(int j = 0; j < catRec->_numClasses; j++) {
      ClassRec *classRec = catRec->_classRecs[j];
      for(int k = 0; k < classRec->_numInstances; k++) {
	ClassInfo *instRec = classRec->_instances[k];
#ifdef DEBUG
        printf("now destroying %s\n", instRec->InstanceName());
#endif
	delete instRec;
      }
      classRec->_numInstances = 0;
    }
  }
}

/* Destroy instance */

void ClassDir::DestroyInstance(char *name)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    for(int j = 0; j < catRec->_numClasses; j++) {
      ClassRec *classRec = catRec->_classRecs[j];
      for(int k = 0; k < classRec->_numInstances; k++) {
	ClassInfo *instRec = classRec->_instances[k];
	if (!strcmp(instRec->InstanceName(), name)) {
#ifdef DEBUG
          printf("now destroying %s\n", name);
#endif
	  delete instRec;
	  for(int l = k; l < classRec->_numInstances - 1; l++) {
	    classRec->_instances[l] = classRec->_instances[l + 1];
	  }
	  classRec->_numInstances--;
	  return;
	}
      }
    }
  }
}

/* Destroy all transient classes */

void ClassDir::DestroyTransientClasses()
{
#ifdef DEBUG
  printf("Before DestroyTransientClasses, ClassDir shows:\n");
  Print();
#endif

  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    int j = 0;
    while (j < catRec->_numClasses) {
      ClassRec *classRec = catRec->_classRecs[j];
      if (!classRec->classInfo->IsTransient()) {
	j++;
	continue;
      }
#ifdef DEBUG
      printf("Now destroying category %s, class %s\n", catRec->name,
	     classRec->classInfo->ClassName());
#endif
      for(int k = 0; k < classRec->_numInstances; k++) {
	ClassInfo *instRec = classRec->_instances[k];
#ifdef DEBUG
	printf("  Destroying instance %s\n", instRec->InstanceName());
#endif
	delete instRec;
      }
#ifdef DEBUG
      printf("  Destroying class %s\n", classRec->classInfo->ClassName());
#endif
      delete classRec->classInfo;
      delete classRec;
      for(int l = j; l < catRec->_numClasses - 1; l++) {
	catRec->_classRecs[l] = catRec->_classRecs[l + 1];
      }
#if CHECK_CLASS_RECS
      catRec->_classRecs[catRec->_numClasses - 1] = NULL;
#endif
      catRec->_numClasses--;
    }
  }
#ifdef DEBUG
  printf("After DestroyTransientClasses, ClassDir shows:\n");
  Print();
#endif
}

/* Get creation parameter for instance */

void ClassDir::CreateParams(char *category, char *className,
			    char *instanceName, 
			    int &numParams, char **&params)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name,category)) {
      for(int j = 0; j < catRec->_numClasses; j++) {
	ClassRec *classRec = catRec->_classRecs[j];
	if (!strcmp(classRec->classInfo->ClassName(), className)) {
	  for(int k = 0; k < classRec->_numInstances; k++) {
	    ClassInfo *iInfo = classRec->_instances[k];
	    if (!strcmp(iInfo->InstanceName(), instanceName)) {
	      /* found */
	      iInfo->CreateParams(numParams, params);
	      return;
	    }
	  }
	}
      }
    }
  }

  fprintf(stderr,"Instance %s not found\n", instanceName);

  numParams = 0;
  params = NULL;
}

ClassInfo::ClassInfo()
{
  _defaultParams = NULL;
  _numDefaultParams = 0;
}

ClassInfo::~ClassInfo()
{
  /*
     printf("ClassInfo destructor\n");
  */
}

char *ClassInfo::InstanceName()
{
  DOASSERT(0, "Invalid function call");
  return NULL; /* to keep compiler happy*/
}

void *ClassInfo::GetInstance()
{
  DOASSERT(0, "Invalid function call");
  return NULL; /* to keep compiler happy*/
}

/* Get parameters that can be used to re-create this instance */

void ClassInfo::CreateParams(int &argc, char **&argv)
{
  DOASSERT(0, "Invalid function call");
}

/* Set default parameters */

void ClassInfo::SetDefaultParams(int argc, char **argv)
{
  if (argc == 0)
    return;

  if (_defaultParams) {
    /* free parameters */
    for(int i = 0; i < _numDefaultParams; i++) {
      delete _defaultParams[i];
      delete _defaultParams;
    }
  }

  _defaultParams = new char *[argc];
  _numDefaultParams = argc;
  for(int i = 0; i < argc; i++) {
    _defaultParams[i] = CopyString(argv[i]);
  }
}

/* Get default parameters */

void ClassInfo::GetDefaultParams(int &argc, char **&argv)
{
  argc = _numDefaultParams;
  argv = _defaultParams;
}

/* Find instance with given name */

Boolean ClassDir::Changeable(char *name)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    for(int j = 0; j < catRec->_numClasses; j++) {
      ClassRec *classRec = catRec->_classRecs[j];
      for(int k = 0; k < classRec->_numInstances; k++) {
	if (!strcmp(classRec->_instances[k]->InstanceName(), name))
	  return classRec->_instances[k]->Changeable();
      }
    }
  }

  return false;
}

/* Change params */

void ClassDir::ChangeParams(char *name, int num, char **paramNames)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    for(int j = 0; j < catRec->_numClasses; j++) {
      ClassRec *classRec = catRec->_classRecs[j];
      for(int k = 0; k < classRec->_numInstances; k++) {
	if (!strcmp(classRec->_instances[k]->InstanceName(), name))
	  classRec->_instances[k]->ChangeParams(num, paramNames);
      }
    }
  }
}

/* Get params */

void ClassDir::GetParams(char *name, int &num, char **&paramNames)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    for(int j = 0; j < catRec->_numClasses; j++) {
      ClassRec *classRec = catRec->_classRecs[j];
      for(int k = 0; k < classRec->_numInstances; k++) {
	if (!strcmp(classRec->_instances[k]->InstanceName(), name)) {
	  classRec->_instances[k]->ParamNames(num, paramNames);
	  return;
	}
      }
    }
  }
}

/* Get user info for a class */

void *ClassDir::UserInfo(char *category, char *className)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    if (!strcmp(catRec->name,category)) {
      for(int j = 0; j < catRec->_numClasses; j++) {
	ClassRec *classRec = catRec->_classRecs[j];
	if (!strcmp(classRec->classInfo->ClassName(), className)) {
	  return classRec->classInfo->UserInfo();
	}
      }
    }
  }

  return NULL;
}

/* Print name of all instances */

void ClassDir::Print()
{
  printf("%d categories\n", _numCategories);
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    printf("Category %s: %d classes\n", catRec->name, catRec->_numClasses);
    for(int j = 0; j < catRec->_numClasses; j++) {
      ClassRec *classRec = catRec->_classRecs[j];
      printf("  Class %s: %d instances\n", classRec->classInfo->ClassName(),
	     classRec->_numInstances);
      for(int k = 0; k < classRec->_numInstances; k++) {
	printf("    %s\n", classRec->_instances[k]->InstanceName());
      }
    }
  }
}

/* Find name of instance */

char *ClassDir::FindInstanceName(void *inst)
{
  for(int i = 0; i < _numCategories; i++) {
    CategoryRec *catRec = _categories[i];
    for(int j = 0; j < catRec->_numClasses; j++) {
      ClassRec *classRec = catRec->_classRecs[j];
      for(int k = 0; k < classRec->_numInstances; k++) {
	if (classRec->_instances[k]->GetInstance() == inst)
	  return classRec->_instances[k]->InstanceName();
      }
    }
  }

  return NULL;
}
