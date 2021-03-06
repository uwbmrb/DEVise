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
  Revision 1.11  2005/12/06 20:01:03  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.10.14.1  2005/09/12 19:41:57  wenger
  Got DEVise to compile on basslet.bmrb.wisc.edu (AMD 64/gcc
  4.0.1).

  Revision 1.10  1999/09/02 17:25:20  wenger
  Took out the ifdefs around the MARGINS code, since DEVise won't compile
  without them; removed all of the TK_WINDOW code, and removed various
  unnecessary includes of tcl.h, etc.

  Revision 1.9  1996/05/11 03:23:23  jussi
  Minor improvements for robustness.

  Revision 1.8  1996/04/16 20:57:10  jussi
  Replaced assert() calls with DOASSERT macro.

  Revision 1.7  1995/12/28 18:25:32  jussi
  Removed warnings related to for loop variable scope.

  Revision 1.6  1995/11/20 22:39:58  jussi
  Base tape offset received from calling program.

  Revision 1.5  1995/11/17 04:41:02  ravim
  Fix bug.

  Revision 1.4  1995/11/17 04:05:57  ravim
  Extracts only first 6 chars of cusip for comparison.

  Revision 1.3  1995/11/15 21:11:39  ravim
  Fix bug in extract routine.

  Revision 1.2  1995/11/15 07:00:56  ravim
  Outputs crsp data file.

  Revision 1.1  1995/11/10 18:49:48  jussi
  Initial revision.
*/

// File containing routine that extracts a security from a CRSP tape

using namespace std;

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <tcl.h>

#include "sec.h"
#include "tapedrive.h"
#include "Exit.h"

//#define DEBUG

static Tcl_Interp *globalInterp = 0;

#define UPDATE_TCL { (void)Tcl_Eval(globalInterp, "update"); }

/*-------------------------------------------------------------------*/

/*
   Searches through the index file and finds the entry for the given 
   CUSIP number. Then, returns the tape offset for this security.
*/

static long int find_offset(FILE *idxfile, const char cval[])
{
  unsigned long int offval;
  char fval[10];	// stores CUSIP in this

  while(fscanf(idxfile, "%lu,%*d,%*d,%6s,%*[^\n]\n", &offval, fval) == 2) {
    if (!strcmp(cval, fval))
      return offval;
  }

  printf("ERROR: could not find CUSIP %s in the index file\n", cval);
  return -1;
}

/*-------------------------------------------------------------------*/

/*
   This is a wrapper function that makes the assumption that data files
   are to be created based on the CUSIP code. This function takes
   as parameter pairs of <CUSIP, cachefilename>. It reads the
   index file and arranges these symbols in the increasing order of offsets
   of the corresponding records (since the records are on tape) and extracts
   every security in turn.
*/

static int crsp_create(const char *tapeDrive, const char *tapeFile,
		const char *tapeOff, const char *tapeBsize,
		const char *idxFile, const char **argv, int argc)
{
  DOASSERT(argc % 2 == 0, "Invalid parameters");
  int num = argc / 2;

  // Get the index file pointer
  FILE *idxfile;
  if (!(idxfile = fopen(idxFile, "r"))) {
    printf("Error: could not open index file: %s\n", idxFile);
    return TCL_ERROR;
  }
  
  // We will retrieve num offsets and sort them
  long int *offset_arr = (long int *)malloc(num * sizeof(long int));
  int *spos_arr = (int *)malloc(num * sizeof(int));

  int i;
  for(i = 0; i < num; i++) {
    spos_arr[i] = i * 2;
    // find offset for this security by looking through the index file
    offset_arr[i] = find_offset(idxfile, argv[i * 2]);
    // add offset of beginning of tape file
    offset_arr[i] += atol(tapeOff);
    rewind(idxfile);
  }

  fclose(idxfile);

  // Now sort offset_arr - bubble sort for now
  for(i = 0; i < num; i++) {
    for(int j = i+1; j < num; j++) {
      if (offset_arr[i] > offset_arr[j]) {
	unsigned long int tmp = offset_arr[i];
	offset_arr[i] = offset_arr[j];
	offset_arr[j] = tmp;
	tmp = spos_arr[i];
	spos_arr[i] = spos_arr[j];
	spos_arr[j] = tmp;
      }
    }
  }

  TapeDrive tape(tapeDrive, "r", atoi(tapeFile), atoi(tapeBsize));
  if (!tape) {
    fprintf(stderr, "Error: could not open tape device %s\n", tapeDrive);
    return TCL_ERROR;
  }

  // Extract every security in turn
  for(i = 0; i < num; i++) {
    if (offset_arr[i] < atol(tapeOff))
      continue;
#ifdef DEBUG
    cout << "Seeking to offset " << offset_arr[spos_arr[i]] << endl;
#endif
    if (tape.seek(offset_arr[spos_arr[i]]) != offset_arr[spos_arr[i]]) {
      cerr << "Error in seeking to tape position "
           << offset_arr[spos_arr[i]] << endl;
      perror("seek");
    } else {
      Security s(tape);
      ofstream outfile(argv[spos_arr[i] + 1], ios::out);
      if (!outfile) {
	cerr << "Cannot create file " << argv[spos_arr[i] + 1] << endl;
	perror("create");
      } else {
#ifdef DEBUG
	cout << "Extracting " << argv[spos_arr[i] + 1] << endl;
#endif
	s.print_security(outfile);
	outfile.close();
      }
    }
  }
  free(offset_arr);
  free(spos_arr);

  return TCL_OK;
}

/*-------------------------------------------------------------------*/

/*
   This function interfaces the CRSP extraction routines to TCL/TK.
*/

int crsp_extract(ClientData cd, Tcl_Interp *interp, int argc,
#if TCL_MAJOR_VERSION > 8 || (TCL_MAJOR_VERSION == 8 && TCL_MINOR_VERSION > 3)
		const
#endif
		char **argv)
{
  // Allow other functions to UPDATE_TCL

  globalInterp = interp;

  DOASSERT(argc >= 8, "Invalid parameters");

  // Get parameter values from TCL script

  const char *tapeDrive = argv[1];
  const char *tapeFile = argv[2];
  const char *tapeOff = argv[3];
  const char *tapeBsize = argv[4];
  const char *idxFile = argv[5];

  printf("Reading from %s:%s:%s (%s)\n",
	 tapeDrive, tapeFile, tapeOff, tapeBsize);

  // pass pairs of <CUSIP, cachefilename> to extraction routine

  return crsp_create(tapeDrive, tapeFile, tapeOff, tapeBsize, idxFile,
#if TCL_MAJOR_VERSION < 8 || (TCL_MAJOR_VERSION == 8 && TCL_MINOR_VERSION <= 3)
		     (const char **)
#endif
		     &argv[6], argc - 6);
}
