/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1998-2008
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  Declaration of ViewDir (view direction?).
 */

/*
  $Id$

  $Log$
  Revision 1.3  1998/08/21 22:16:50  wenger
  Got DEVise 1.5.4 to compile on SPARC/SunOS (sundance) -- to make statically-
  linked DEVise for distribution.

  Revision 1.2  1998/05/05 18:20:00  wenger
  Committed changes Zhenhai made, but his copy of this file wasn't in CVS
  somehow.

  Revision 1.1  1998/03/18 19:27:22  wenger
  Zhenhai forgot to commit this.

 */


#ifndef ViewDir_h_
#define ViewDir_h_

#include <string.h>
#if defined(SUN)
extern "C" int strcasecmp(const char *s1, const char *s2);
#endif

// viewing direction
// need modification later
enum ViewDir {PosX, PosY, PosZ, NegX, NegY, NegZ};
inline const char * ViewDir2Char(ViewDir const dir) {
  switch(dir) {
	case PosX: return "PosX";
	case PosY: return "PosY";
	case PosZ: return "PosZ";
	case NegX: return "NegX";
	case NegY: return "NegY";
	case NegZ: return "NegZ";
  	default:
		return 0;
  }
}

inline int Char2ViewDir(ViewDir &dir, char const * const x) {
  if (strcasecmp(x,"PosX")==0) {
	dir=PosX;
  }
  else if (strcasecmp(x,"PosY")==0) {
	dir=PosY;
  }
  else if (strcasecmp(x,"PosZ")==0) {
	dir=PosZ;
  }
  else if (strcasecmp(x,"NegX")==0) {
	dir=NegX;
  }
  else if (strcasecmp(x,"NegY")==0) {
	dir=NegY;
  }
  else if (strcasecmp(x,"NegZ")==0) {
	dir=NegZ;
  }
  else
      return 0;
  return 1;
}

#endif // ViewDir_h_
