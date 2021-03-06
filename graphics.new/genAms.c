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
  Revision 1.4  1997/03/28 16:10:30  wenger
  Added headers to all source files that didn't have them; updated
  solaris, solsparc, and hp dependencies.

  Revision 1.3  1996/10/02 15:23:53  wenger
  Improved error handling (modified a number of places in the code to use
  the DevError class).

  Revision 1.2  1995/09/05 22:16:27  jussi
  Added CVS header.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ams.h"
#include "DevError.h"

#define NUMRECORDS 100
#define outfile "AmsOut"
main(){
int i;
struct AmsData data;
double time = 0.0;
int fd;

	if ((fd=open(outfile,O_CREAT|O_TRUNC|O_WRONLY, 0666))<0){
		reportErrSys("open");
        reportErrNosys("Fatal error");//TEMP -- replace with better message
		exit(2);
	}
	for (i=0; i < NUMRECORDS; i++){
		data.time = time;
		data.solDn = (double)(((int)i) % 10)+ 10;
		data.windU= 0.0;
		data.windV= 0.0;
		data.windW= 0.0;
		data.tempWet= 0.0;
		data.tempDry= 0.0;
		data.rain = (double)(((int)i)% 10) ;

		if (write(fd,(char *)&data,sizeof(data))!=sizeof(data)){
			reportErrSys("write");
			exit(2);
		}

		time += 30.0;
	}
	close(fd);
}

