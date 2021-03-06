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
  Revision 1.2  1995/09/05 22:16:56  jussi
  Added CVS header.
*/

#include <stdio.h>
#include <stdlib.h>
#include "VoidArray.h"
#include "Parse.h"

/* print array */
PrintArray(VoidArray *arr){
	printf("Array has %d elements\n", arr->Size());
	for (arr->InitIterator(); arr->More(); ){
		void *ele = arr->Next();
		printf("%d ",(int)ele);
	}
	printf("\n");
}
main(){

	/* print: enter command */
	VoidArray *arr = new VoidArray(10);
	for (; ;){
		char buf[256];
		printf("cmd: ");
		gets(buf);
		int numArgs;
		char **args;
		int num;
		int pos;
		void *retVal;
		Parse(buf, numArgs, args);
		switch(args[0][0]){
			case 'd':
				pos = atoi(args[1]);
				retVal = arr->Delete(pos);
				printf("%d deleted\n", (int)retVal);
				break;
			case 'i':
				num = atoi(args[1]);
				pos = atoi(args[2]);
				arr->Insert((void *)num, pos);
				break;
			case 'h':
				printf("commands are:\n");
				printf("d pos: delete from position pos\n");
				printf("i num  pos== insert num at position\n");
				printf("h == help\n");
				break;
		}
		PrintArray(arr);
	}
}
