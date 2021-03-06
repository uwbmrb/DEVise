/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-1997
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
  Revision 1.2  1995/09/05 22:16:45  jussi
  Added CVS header.
*/

/* tests page range in a file */

#include <stdio.h>
#include "PageRange.h"

char *fname = "test.range";
const int MAX_PAGES = 100;
main()
{
  /* get rid of test file, in case it's there */
  unlink(fname);
  
  PageRange *pRange = new PageRange(fname);
  
  /* insert into the page range */
  int i;
  for (i=0; i < MAX_PAGES; i+= 2){
    void *left, *right;
    pRange->InsertPage(i,NULL,NULL,left,right);
  }
  
  printf("printing odd pages\n");
  pRange->Print();
  
  printf("deleting page range\n");
  delete pRange;
  
  printf("getting the page range back\n");
  pRange = new PageRange(fname);
  pRange->Print();
  
  /* insert a few more */
  printf("inserting odd pages\n");
  for (i=1; i < MAX_PAGES; i+= 2){
    void *left, *right;
    pRange->InsertPage(i,NULL,NULL,left,right);
  }
  pRange->Print();
  
  printf("deleting page range\n");
  delete pRange;
  
  printf("getting the page range back\n");
  pRange = new PageRange(fname);
  pRange->Print();
}
