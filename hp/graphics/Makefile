#  ========================================================================
#  DEVise Data Visualization Software
#  (c) Copyright 1992-1995
#  By the DEVise Development Group
#  Madison, Wisconsin
#  All Rights Reserved.
#  ========================================================================
#
#  Under no circumstances is this software to be copied, distributed,
#  or altered in any way without prior permission from the DEVise
#  Development Group.

############################################################

#  $Id$

#  $Log$
#  Revision 1.7  1997/09/23 20:01:34  wenger
#  Opening and saving of sessions now working with new scheme of mapping
#  automatically creating the appropriate TData.
#
#  Revision 1.6  1997/04/03 21:31:21  wenger
#  Eliminated unnecessary tcl dependencies in graphics directory.
#
#  Revision 1.5  1997/03/20 19:56:55  wenger
#  Minor mods to get latest version to compile on HP and SunOS; cleaned
#  up DTE makefiles (moved all targets from architecture-specific makefiles
#  to DTE/Makefile.base).
#
#  Revision 1.4  1996/04/05 20:14:00  wenger
#  Fixed error causing pure virtual function to be called
#  if a session was closed during a query; fixed an error
#  in one of the Linux Makefiles; updated other Makefiles
#  to allow testWindowRep to be built on all architectures.
#
#  Revision 1.3  1996/01/12 18:00:16  jussi
#  Switched to newer compiler version with all necessary header files.
#
#  Revision 1.2  1996/01/12 16:06:41  jussi
#  Gcc header files for HP-UX seem to have vanished; substituted
#  Sun header file directory instead.
#
#  Revision 1.1  1995/10/15 19:12:18  jussi
#  Initial revision.
#

############################################################

ARCH_FLAGS = -DHPUX -I/s/tcl/include
ARCH_LDFLAGS =

VPATH = ../../graphics
include $(VPATH)/Makefile.base
include Makefile.depend
