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
  Revision 1.9  1996/06/20 17:10:24  guangshu
  Added support for color statistics.

  Revision 1.8  1995/12/22 02:36:12  ravim
  Vertical lines for maximum and minimum.

  Revision 1.7  1995/12/18 03:12:21  ravim
  Confidence intervals displayed.

  Revision 1.6  1995/12/15 03:40:16  ravim
  Added "count" stat.

  Revision 1.5  1995/12/08 23:46:12  ravim
  Callbacks added.

  Revision 1.4  1995/12/07 02:20:10  ravim
  Stats displayed based on the specification string in ViewGraph class.

  Revision 1.3  1995/12/06 05:41:29  ravim
  New function which returns specific stat values.

  Revision 1.2  1995/11/30 02:47:01  ravim
  X and Y values are tracked. Max and Min computed too.

  Revision 1.1  1995/11/28 05:26:07  ravim
  Support for statistics.
*/

#ifndef BasicStats_h
#define BasicStats_h

#include "DList.h"
#include "ViewStats.h"

class ViewKGraph;

// List of stats collected here
#define STAT_MEAN   0
#define STAT_MAX    1
#define STAT_MIN    2
#define STAT_COUNT  3
#define ZVAL85      4
#define ZVAL90      5
#define ZVAL95      6
#define STAT_NONE   7

// Total number of stats
#define STAT_NUM    7

// Maximum length of the name of any stat
#define STATNAMELEN 10

// The following are only used for retrieving
// clow[NUM_Z_VALS], chigh[NUM_Z_VALS]

#define STAT_ZVAL85L 11
#define STAT_ZVAL85H 12
#define STAT_ZVAL90L 13
#define STAT_ZVAL90H 14
#define STAT_ZVAL95L 15
#define STAT_ZVAL95H 16

// Number of confidence intervals
#define NUM_Z_VALS 3

const double zval[NUM_Z_VALS] = { 1.464, 1.645, 1.960 };
const int num_per_batch = 1;

class BasicStats: public ViewStats
{
public:
  BasicStats();
  ~BasicStats();

  virtual void Init(ViewGraph *vw);
  virtual void Sample(double x, double y);
  virtual void Done();
  virtual void Report();
  
  virtual Coord GetStatVal(int statnum);
  virtual char *GetStatName(int statnum);

private:
  double ysum, xsum;
  double ysum_sqr, xsum_sqr;
  double ymin, xmin, ymax, xmax;
  double xatymax, xatymin;
  double int_x, int_y;
  int nsamples, nval;

  // Stat values
  double avg, var, std;
  double clow[NUM_Z_VALS], chigh[NUM_Z_VALS];
};
#endif
