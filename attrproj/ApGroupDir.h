/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-1995
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

#ifndef _GROUPDIR_H_
#define _GROUPDIR_H_

#include "ApItemList.h"

class GroupDir
{
public:
  struct SchemaList
  {
    char *sname;
    ItemList *topgrps;
    SchemaList *next;
  };

  SchemaList *list;

  GroupDir();
  ~GroupDir();

  void add_entry(char *schema);

  void add_topgrp(char *schema, Group *gp);
#if 0
  void top_level_groups(Tcl_Interp *interp, char *schema);
#endif
  
#if 0
  void get_items(Tcl_Interp *interp, char *schema, char *topgname, char *gname);
#endif
  int find_entry(char *schema);
  int num_topgrp(char *schema);

private:
  Group *find_grp(Group *gp, char *gname);
};

#endif
