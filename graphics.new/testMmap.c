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
  Revision 1.2  1995/09/05 22:16:43  jussi
  Added CVS header.
*/

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

extern int errno;
main()
{
  char *name = "g2123";
  int fd;
  struct stat sbuf;
  caddr_t addr;
  if ((fd= open(name,O_RDONLY,0666))< 0){
    perror("open file");
    exit(2);
  }
  if (fstat(fd,&sbuf) < 0){
    perror("fstat");
    exit(2);
  }
  
  printf("file size  = %d\n",sbuf.st_size);
  addr = mmap((caddr_t)0,sbuf.st_size,PROT_READ,MAP_FIXED,fd,(off_t)0);
  if (addr == (caddr_t)-1){
    perror("mmap");
    printf("errno = %d\n", errno);
    exit(2);
  }
  
  printf("mapped file %s, address 0x%p, length %d\n",
	 name, addr, sbuf.st_size);
}
