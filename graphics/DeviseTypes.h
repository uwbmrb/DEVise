/*
  $Id$

  $Log$
  Revision 1.9  1996/08/05 17:28:58  beyer
  Added is_safe() which checks to see if a double is safe value (ie, not
  NaN or Infinity).  Made SetVisualFilter check the new filter for safety.

  Revision 1.8  1996/08/04 23:33:16  beyer
  Added #define for NULL

  Revision 1.7  1996/07/31 19:34:30  wenger
  Added AttrProj member functions for reading entire records (no projection).

  Revision 1.6  1996/07/13 04:59:31  jussi
  Added conditional for Linux.

  Revision 1.5  1996/06/21 19:29:11  jussi
  Cleaned up file and replaced MinMax class with simpler MIN/MAX macros.

  Revision 1.4  1996/05/20 18:44:40  jussi
  Replaced PENTIUM flag with SOLARIS.

  Revision 1.3  1996/04/15 19:32:05  wenger
  Consolidated the two (nearly identical) functions for
  reading/parsing physical schema, and cleaned up the
  ParseCat.c module quite a bit.  As part of this, I added
  a new enum DevStatus (StatusOk, StatusFailed, etc.).

  Revision 1.2  1995/09/05 21:12:39  jussi
  Added/update CVS header.
*/

#ifndef DeviseTypes_h
#define DeviseTypes_h

#include <values.h>


typedef double Coord;
typedef char Boolean;

#if defined(HPUX) || defined(SUN) || defined(SOLARIS) || defined(LINUX)
inline int trunc(float num) {
  return (int)num;
}
inline int trunc(double num) {
  return (int)num;
}
#endif

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MIN3
#define MIN3(a,b,c) ((a) < (b) ? MIN(a,c) : MIN(b,c))
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MAX3
#define MAX3(a,b,c) ((a) > (b) ? MAX(a,c) : MAX(b,c))
#endif

// Status information (to be returned by a function, for example) and
// functions to get information about the status.
enum DevStatus {
  StatusInvalid = 0,
  StatusOk = 10000,	// Everything is OK.
  StatusFailed,		// Failure -- the function did not complete.
  StatusWarn,		// There was an error, but the function completed.
  StatusCancel,		// The function was cancelled.
  StatusWarnCancel	// There was a warning, and the function was cancelled.
};

// Did the function complete successfully?
inline Boolean StatIsComplete(DevStatus status)
{
  return (status == StatusOk) || (status == StatusWarn);
}

// Was there an error?
inline Boolean StatIsError(DevStatus status)
{
  return (status == StatusFailed) || (status == StatusWarn) ||
    (status == StatusWarnCancel);
}

// Was there a warning?
inline Boolean StatIsWarn(DevStatus status)
{
  return (status == StatusWarn) || (status == StatusWarnCancel);
}

// Was the function cancelled (for example, by the user)?
inline Boolean StatIsCancel(DevStatus status)
{
  return (status == StatusCancel) || (status == StatusWarnCancel);
}

// Combine two statuses.
inline DevStatus StatusCombine(DevStatus status1, DevStatus status2)
{
  DevStatus result = StatusOk;

  if ((status1 == StatusFailed) || (status2 == StatusFailed))
  {
    result = StatusFailed;
  }
  else if (StatIsCancel(status1) || StatIsCancel(status2))
  {
    if (StatIsWarn(status1) || StatIsWarn(status2))
    {
      result = StatusWarnCancel;
    }
    else
    {
      result = StatusCancel;
    }
  }
  else if (StatIsWarn(status1) || StatIsWarn(status2))
  {
    result = StatusWarn;
  }
  else
  {
    result = StatusOk;
  }

  return result;
}


#ifndef NULL
#define NULL 0
#endif


inline bool is_safe(double x)
{
  return x < MAXDOUBLE && x > -MAXDOUBLE;
}


#endif
