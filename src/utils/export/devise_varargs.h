/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1998
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  This file is just a means of grabbing the right header files for the
  damn varargs stuff according to what architecture we're on.
 */

/*
  $Id$

  $Log$
 */

#ifndef _devise_varargs_h_
#define _devise_varargs_h_

#if defined(OSF)
#   include <sys/param.h>
#   include <stdarg.h>
#elif defined(SGI) || defined(LINUX)
#   include <stdarg.h>
#else
#   include <sys/varargs.h>
#endif

#endif // _devise_varargs_h_

/*============================================================================*/