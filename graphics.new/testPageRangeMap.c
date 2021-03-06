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
  Revision 1.3  1997/03/28 16:10:32  wenger
  Added headers to all source files that didn't have them; updated
  solaris, solsparc, and hp dependencies.

  Revision 1.2  1995/09/05 22:16:46  jussi
  Added CVS header.
*/

//#include "PageRangeMap.h" 

const int MAX_PAGES = 100;

int inserted[MAX_PAGES];

main()
{
  PageRangeMap *range = new PageRangeMap();

  int i;
  for (i=0; i < MAX_PAGES; i++){
    if (range->NextUnprocessed(i) != i){
      fprintf(stderr,"next unprocessed should be %d\n", i);
      exit(2);
    }
    range->InsertRange(i,i,i,i,10);
  }
  range->Print();

  /* insert odd pages */
  delete range;
  printf("insert even pages\n");
  range = new PageRangeMap();
  for (i=0; i < MAX_PAGES; i += 2){
    if (range->NextUnprocessed(i) != i){
      fprintf(stderr,"next unprocessed should be %d\n", i);
      exit(2);
    }
    range->InsertRange(i,i,i,i,10);
  }
  range->Print();
  
  /* insert odd pages */
  printf("insert odd pages\n");
  PageRangeMapRec *rec;
  for (i=1; i < MAX_PAGES; i += 2){
    if (range->NextUnprocessed(i) != i){
      fprintf(stderr,"next unprocessed should be %d\n", i);
      exit(2);
    }
    rec = range->FindNoOverlap(i);
    range->InsertRange(i,i,i,i,10);
  }
  range->Print();
  
  /* test random insertion */
  delete range;
  printf("testing random insertion\n");
  range = new PageRangeMap();
  for (i=0; i < MAX_PAGES; i++)
    inserted[i] = 0;
  
  /* insert 1/2 of pages */
  for (i=0; i < MAX_PAGES/2; i++){
    int rnd = (int)(random() % MAX_PAGES);
    if (!inserted[rnd]){
      inserted[rnd] = 1;
      range->InsertRange(rnd,rnd,rnd,rnd,10);
    }
  }

  int next = 1;
  next = range->NextUnprocessed(next);
  while (next < MAX_PAGES){
    if (inserted[next]){
      /* inserted already processed */
      fprintf(stderr,"page %d already processed\n", next);
      exit(2);
    }
    range->InsertRange(next,next,next,next, 10);
    
    next = range->NextUnprocessed(next);
  }

  range->Print();
}
