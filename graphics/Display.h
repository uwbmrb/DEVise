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
  Revision 1.34  2008/09/23 19:32:39  wenger
  Changed DispatchedName() to const char *.

  Revision 1.33  2002/02/05 19:32:33  wenger
  Fixed bug 750 (problem with child view/pile combinations with an X
  server with no backing store); added TEST_NO_BACKING_STORE code to
  test this case even if we really do have backing store on the server.

  Revision 1.32  2001/08/20 18:20:26  wenger
  Fixes to various font problems: XDisplay calculates point sizes correctly
  and uses screen resolution in specifying font; JS passes *its* screen
  resolution to the devised so that fonts show up correctly in the JS
  (JS protocol version now 7.0); changed DEVise version to 1.7.4.

  Revision 1.31  1998/12/15 18:47:11  wenger
  New option in fixed text symbol: if size is <=1, it is assumed to be a
  fraction of the screen height, rather than the font size in points.

  Revision 1.30  1998/05/14 18:21:01  wenger
  New protocol for JavaScreen opening sessions works (sending "real" GIF)
  except for the problem of spaces in view and window names.

  Revision 1.29  1997/11/24 23:14:20  weaver
  Changes for the new ColorManager.

  Revision 1.28  1997/11/12 15:45:12  wenger
  Merged the cleanup_1_4_7_br branch through the cleanup_1_4_7_br_2 tag
  into the trunk.

  Revision 1.27.4.1  1997/11/11 19:13:43  wenger
  Added getWindowImageAndSize and waitForQueries commands; fixed bug in
  WindowRep::ExportGIF() inheritance.

  Revision 1.27  1997/08/08 14:00:57  wenger
  Removed unnecessary dependency on ViewWin.h in cslib version.

  Revision 1.26  1997/07/22 19:44:28  wenger
  Removed extra dependencies that broke cslib link.

  Revision 1.25  1997/06/04 15:50:24  wenger
  Printing windows to PostScript as pixmaps is now implemented, including
  doing so when printing the entire display.

  Revision 1.24  1997/05/21 22:09:50  andyt
  Added EmbeddedTk and Tasvir functionality to client-server library.
  Changed protocol between devise and ETk server: 1) devise can specify
  that a window be "anchored" at an x-y location, with the anchor being
  either the center of the window, or the upper-left corner. 2) devise can
  let Tk determine the appropriate size for the new window, by sending
  width and height values of 0 to ETk. 3) devise can send Tcl commands to
  the Tcl interpreters running inside the ETk process.

  Revision 1.23.6.1  1997/05/21 20:39:37  weaver
  Changes for new ColorManager

  Revision 1.23  1997/05/05 16:53:42  wenger
  Devise now automatically launches Tasvir and/or EmbeddedTk servers if
  necessary.

  Revision 1.22  1997/03/25 17:58:50  wenger
  Merged rel_1_3_3c through rel_1_3_4b changes into the main trunk.

  Revision 1.21.4.1  1997/03/15 00:31:02  wenger
  PostScript printing of entire DEVise display now works; PostScript output
  is now centered on page; other cleanups of the PostScript printing along
  the way.

  Revision 1.21  1996/12/03 23:29:09  wenger
  Fixed PostScript bounding box to closely surround the image (fixed
  bug 089).

  Revision 1.20  1996/11/26 15:44:05  wenger
  Added features and fixed bugs in PostScript-related parts of the
  client/server library and the PSWindowRep class; page size can now be
  set in PSDisplay; did some cleanup of the DeviseDisplay and WindowRep
  methods (allowed elimination of many typecasts).

  Revision 1.19  1996/11/13 16:56:05  wenger
  Color working in direct PostScript output (which is now enabled);
  improved ColorMgr so that it doesn't allocate duplicates of colors
  it already has, also keeps RGB values of the colors it has allocated;
  changed Color to GlobalColor, LocalColor to make the distinction
  explicit between local and global colors (_not_ interchangeable);
  fixed global vs. local color conflict in View class; changed 'dali'
  references in command-line arguments to 'tasvir' (internally, the
  code still mostly refers to Dali).

  Revision 1.18  1996/09/18 20:11:54  guangshu
  Added function ExportView to save each view in a window to a separate gif
  file. Modified function ExportGIF.

  Revision 1.17  1996/09/13 23:02:42  guangshu
  Added ExportImageAndMap function.

  Revision 1.16  1996/09/10 20:07:08  wenger
  High-level parts of new PostScript output code are in place (conditionaled
  out for now so that the old code is used until the new code is fully
  working); changed (c) (tm) in windows so images are not copyrighted
  by DEVise; minor bug fixes; added more debug code in the course of working
  on the PostScript stuff.

  Revision 1.15  1996/09/09 14:31:41  jussi
  Added #ifdef LIBCS statements to make code compile in the
  ClientServer library target.

  Revision 1.14  1996/09/05 21:30:16  jussi
  Moved user-specified screen size to Display.

  Revision 1.13  1996/07/23 15:34:40  jussi
  Added mechanism for bypassing the Devise internal color map.

  Revision 1.12  1996/07/21 02:21:47  jussi
  Made Run() a public method which View::SubclassMapped() can call.

  Revision 1.11  1996/07/18 01:19:32  jussi
  Added ExportImage method.

  Revision 1.10  1996/06/24 19:36:43  jussi
  Removed unnecessary code that stored a pointer to the
  dispatcher in a member variable.

  Revision 1.9  1996/05/20 18:44:59  jussi
  Merged with ClientServer library code.

  Revision 1.8  1996/05/09 18:12:09  kmurli
  No change to this makefile.

  Revision 1.7  1996/04/09 18:05:49  jussi
  Added Flush() method.

  Revision 1.6  1996/04/08 16:56:44  jussi
  Minor fixes.

  Revision 1.5  1996/04/04 05:18:28  kmurli
  Major modification: The dispatcher now receives the register command
  from the displays directly (i.e. from XDisplay instead of from
  Display) corrected a bug in call to register function. Also now
  dispatcher uses socket number passed from the XDisplay class to
  select on it and call the relevant functions.

  Revision 1.4  1996/03/29 18:13:50  wenger
  Got testWindowRep to compile and run, added drawing in
  windows; fixed a few more compile warnings, etc.

  Revision 1.3  1996/01/30 00:02:31  jussi
  Made code refer to ForegroundColor and BackgroundColor instead
  of black and white.

  Revision 1.2  1995/09/05 21:12:44  jussi
  Added/update CVS header.
*/

#ifndef Display_h
#define Display_h

#include "DeviseTypes.h"
#include "Geom.h"
#ifndef LIBCS
#include "Dispatcher.h"
#include "ViewWin.h"
#endif
#include "DList.h"
#include "WindowRep.h"

#define TEST_NO_BACKING_STORE 0

class DeviseDisplay;

DefinePtrDList(DeviseDisplayList, DeviseDisplay *);

#ifdef LIBCS
class DeviseDisplay {
#else
class DeviseDisplay: public DispatcherCallback {
#endif
public:
  DeviseDisplay();

  virtual ~DeviseDisplay();

  /* get the default display */
  static DeviseDisplay *DefaultDisplay();

  /* get the PostScript display */
  static DeviseDisplay *GetPSDisplay();

  /* get file descriptor for connection */
  virtual int fd() = 0;

  virtual int NumPlanes() = 0;
  virtual void Dimensions(Coord &width, Coord &height) =0;

  /* Create a new window rep, 
     relative == 1 if in relative dimensions.*/
  virtual WindowRep* CreateWindowRep(const char *name, Coord x, Coord y,
				     Coord width, Coord height, 
				     WindowRep *parentRep = NULL,
				     Coord min_width = 0.05,
				     Coord min_height = 0.05,
				     Boolean relative = true,
				     Boolean winBoundary = true) = 0;
	
  /* Destroy a window rep*/
  virtual void DestroyWindowRep(WindowRep *c) = 0;

  /* Do internal event processing, but do not block*/
  virtual void InternalProcessing() = 0;

  /* Flush buffered window operations to screen */
  virtual void Flush() = 0;

#ifndef LIBCS
  /* Export display image to other graphics formats */
  virtual void ExportImage(DisplayExportFormat format, char *filename) = 0;
  virtual void ExportImageAndMap(DisplayExportFormat format, char *gifFilename, 
			char *mapFileame, char *url, char *defaultUrl) = 0;
  virtual void ExportGIF(FILE *fp, int isView = 0) = 0;
  virtual void ExportView(DisplayExportFormat format, char *filename) = 0;
  virtual void ExportToPS(DisplayExportFormat format, char *filename);
#endif


  virtual DevStatus OpenPrintFile(const char *filename) { return StatusFailed; }
  virtual DevStatus ClosePrintFile() { return StatusFailed; }
  virtual FILE *GetPrintFile() { return NULL; }
#ifndef LIBCS
  virtual DevStatus ImportWindow(ViewWin *window,
    DisplayExportFormat format) { return StatusFailed; }
#endif

  virtual void PrintPSHeader(const char *title, const Rectangle &screenPrintRegion,
    Boolean maintainAspect = true) {}
  virtual void PrintPSTrailer() {}
  virtual void GetBoundingBox(Rectangle &boundingBox) {}
  virtual void GetScreenPrintRegion(Rectangle &screenPrintRegion) {}

  /* Set page geometry in inches. */
  virtual void SetUserPageGeom(Coord width, Coord height, Coord xMargin,
    Coord yMargin) {}

  /* Get page geometry -- units depend on which class you actually have. */
  virtual void GetPageGeom(Coord &width, Coord &height, Coord &xMargin,
    Coord &yMargin) {}

  /* Iterator to go through all displays */
  static int InitIterator() { return _displays.InitIterator(); }
  static Boolean More(int index){ return _displays.More(index); }
  static DeviseDisplay *Next(int index) { return _displays.Next(index); }
  static void DoneIterator(int index) { _displays.DoneIterator(index); }

  /* Process windowing events */
  void Run() { InternalProcessing(); }

  virtual void SetTasvirServer(const char *server) = 0;

#ifndef LIBCS
/* Get/set desired screen size and resolution */
  virtual int &DesiredScreenWidth() { return _desiredScreenWidth; }
  virtual int &DesiredScreenHeight() { return _desiredScreenHeight; }

  // Resolution is dots per inch.
  virtual int DesiredScreenXRes() { return _desiredScreenXRes; }
  virtual int DesiredScreenYRes() { return _desiredScreenYRes; }

  virtual void SetDesiredScreenXRes(int resolution) { _desiredScreenXRes =
    resolution; }
  virtual void SetDesiredScreenYRes(int resolution) { _desiredScreenYRes =
    resolution; }
#endif

  virtual Coord PointsPerPixel() = 0;

protected:
#ifndef LIBCS
  /*
     This is to force the derived classes to register themselves
     with the dispatcher
 */
  virtual void Register() = 0;
#endif

  friend class WindowRep;

  virtual const char *DispatchedName();
  
  static DeviseDisplayList _displays; /* list of all displays */
    static DeviseDisplay *_defaultDisplay;
  static DeviseDisplay *_psDisplay;

#ifndef LIBCS
  int _desiredScreenWidth;
  int _desiredScreenHeight;
  int _desiredScreenXRes;
  int _desiredScreenYRes;
#endif
};

#endif
