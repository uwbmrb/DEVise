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
  Revision 1.2  1995/09/05 22:17:00  jussi
  Added CVS header.
*/

#include "DiskFile.h"
#include <stdio.h>

main()
{
  char buf[PAGESIZE];
  int i;

  DiskFile *pf = DiskFile::CreateFile("testfile");
  if (pf == NULL){
    fprintf(stderr,"can't create file. File already exists?\n");
    exit(1);
  }
  
  /* write 10 pages */
  printf("write 10 pages\n");
  for (i=0; i < 10; i++){
    buf[0] = 'a'+i;
    pf->WritePage(i,(void *)buf);
  }
  
  /* read them back */
  printf("read them back\n");
  for (i=0; i < 10; i++){
    pf->ReadPage(i,(void *)buf);
    printf("%c ",buf[0]);
  }
  printf("\n");
  
  /* write even number pages */
  printf("write even number pages\n");
  for (i=0; i < 10; i+=2){
    buf[0] = 'A'+i;
    pf->WritePage(10+i, (void *)buf);
  }
  
  /* read them back */
  printf("read them back \n");
  for (i=0; i < 10; i+=2){
    pf->ReadPage(10+i, (void *)buf);
    printf("%c ",buf[0]);
  }
  printf("\n");
  
  /* write even number pages */
  printf("write even number pages\n");
  for (i=1; i < 10; i+= 2){
    buf[0] = 'A'+i;
    pf->WritePage(10+i, (void *)buf);
  }
  
  /* read them back */
  printf("read them back\n");
  for (i=1; i < 10; i+= 2){
    pf->ReadPage(10+i, (void *)buf);
    printf("%c ",buf[0]);
  }
  printf("\n");
  
  /* read everything back */
  printf("read everything back\n");
  for (i=0; i < 20; i++){
    pf->ReadPage(i, (void *)buf);
    printf("%c ",buf[0]);
  }
  printf("\n");
}
