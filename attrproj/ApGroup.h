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

#ifndef _GROUP_H_
#define _GROUP_H_

#include <stdlib.h>

#if 0
#include "TkControl.h"
#include "ClassDir.h"
#include "ViewGraph.h"
#include "View.h"
#include "TData.h"
#include "TDataMap.h"
#include "Init.h"
#include "Util.h"
#include "MapInterpClassInfo.h"
#endif

#define MAX_STR_LEN 200

#define TOPGRP 1
#define SUBGRP 2
#define ITEM 3

class Group;
class ItemList;

class Group
{
public:
  char *name;
  ItemList *subgrps;
  Group *parent;
  int type;

  Group(char *name, Group *par, int typ);
  ~Group();
  Group *insert_item(char *name);
  Group *insert_group(char *name);
  Group *parent_group();
#if 0 /*TEMPTEMP*/
  void subitems(Tcl_Interp *interp);
#endif
};

#endif
