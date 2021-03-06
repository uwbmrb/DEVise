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
  Revision 1.2  1995/09/05 22:16:53  jussi
  Added CVS header.
*/

#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>

Tcl_Interp *_interp;
double result = 5.0;
double parm= 10.0;

main()
{
  int code;

  /* Init tcl */
  _interp = Tcl_CreateInterp();
  if (Tcl_Init(_interp) == TCL_ERROR){
    fprintf(stderr,"MappingINterp: can't init tcl\n");
    exit(2);
  }
  
  /* link interpreter variables with tcl variables */
  /* first, the result variable */
  Tcl_LinkVar(_interp,"result",(char *)&result, TCL_LINK_DOUBLE);
  Tcl_LinkVar(_interp,"parm",(char *)&parm, TCL_LINK_DOUBLE);
  
  char cmd1[] = "set tcl_precision 17";
  Tcl_Eval(_interp,cmd1);
  
  parm = atof("783377600.0");
  char cmd[]= "set result $parm";
  code = Tcl_Eval(_interp,cmd);
  printf("parm = %f, result = %f, code = %d\n", parm, result, code);
  char *ptr;
  printf("strtod %f\n", strtod("783377600.0",&ptr));
}
