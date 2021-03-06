/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2008
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
  Revision 1.18  1998/02/20 06:16:55  beyer
  resurected histograms

  Revision 1.17  1997/03/20 22:04:42  guangshu
  Added function SetnumBucks.

  Revision 1.16  1996/08/07 15:23:20  guangshu
  Simplified the calculation of statistics and Added support for regression lines.

  Revision 1.15  1996/08/04 21:14:40  beyer
  Changed histogram code a little.

  Revision 1.14  1996/07/26 16:10:55  guangshu
  Modified the function Histogram.

  Revision 1.13  1996/07/22 23:42:42  guangshu
  Added statistics for gdata. The statistics includes count, ysum, max, mean, min.

  Revision 1.12  1996/07/19 18:00:28  guangshu
  Added support for histograms.

  Revision 1.11  1996/07/14 04:06:48  jussi
  Added #include of DeviseTypes.h.

  Revision 1.10  1996/07/13 17:29:07  jussi
  ViewKGraph now uses the more general ViewCallback interface.

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
#include "DeviseTypes.h"
#include "ViewStats.h"

class ViewKGraph;

// List of stats collected here
#define STAT_MEAN   0
#define STAT_MAX    1
#define STAT_MIN    2
#define STAT_LINE   3
#define STAT_COUNT  4
#define ZVAL85      5
#define ZVAL90      6
#define ZVAL95      7
#define STAT_NONE   8

// Total number of stats
#define STAT_NUM   8 
//Total number of classes for histogram
#define DEFAULT_HISTOGRAM_BUCKETS    10

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

//The following is used for in GData Stat
#define STAT_YSUM    17
#define STAT_XMIN    18
#define STAT_XMAX    19

#define STAT_A 	     20
#define STAT_B 	     21

// Number of confidence intervals
#define NUM_Z_VALS 3

const double zval[NUM_Z_VALS] = { 1.464, 1.645, 1.960 };
const int num_per_batch = 1;

class BasicStats: public ViewStats
{
public:
  BasicStats();
  ~BasicStats();

  virtual void Init(ViewGraph *vw = 0);
  virtual void Sample(double x, double y);
  virtual void Histogram(double y);
  virtual void Done();
  virtual void Report();
  virtual void ReturnHist();

  virtual Coord GetStatVal(int statnum);
  virtual int GetHistVal(int index);
  virtual Coord GetHistWidth();
  virtual Coord GetHistMin();
  virtual Coord GetHistMax();
  virtual void SetHistogram(Coord min, Coord max, int buckets);
  virtual int GetnumBuckets(){ return numBuckets;}
  virtual const char *GetStatName(int statnum);

protected:

private:
  double ysum, xsum, xysum;
  double ysum_sqr, xsum_sqr;
  double ymin, xmin, ymax, xmax;
  double xatymax, xatymin;
  double int_x, int_y;
  int nsamples, nval;

  int numBuckets;
  int *hist;		// the histogram counts for each class, 
			// make it static for now 
  double width;		// width of each histogram bucket
  double hist_min, hist_max; // min and max 
  
  // Stat values
  double avg, var, std;
  double avg_x, var_x, std_x, avg_xy;
  double cov_xy;
  double line_a, line_b;
  double clow[NUM_Z_VALS], chigh[NUM_Z_VALS];
};
#endif
