/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2013
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  Implementation of Session class (for opening as saving sessions).
 */

/*
  $Id$

  $Log$
  Revision 1.115  2010/09/01 18:44:10  wenger
  Merged fix_3d_cursor_br_0 thru fix_3d_cursor_br_1 to trunk.

  Revision 1.114.6.2  2010/08/31 17:28:22  wenger
  Changed the names of some of the new commands and methods to better
  reflect their functions; documented the new methods.  (Note: cursor
  mods still don't always work right for ambiguity code and Pistachio
  visualizations.)

  Revision 1.114.6.1  2010/08/24 20:38:26  wenger
  Added the getViewSaveState, setViewSaveState, getCursorSaveState,
  setCursorSaveState, getCursorKeepProp, and setCursorKeepProp commands
  to control the new view and cursor properties.

  Revision 1.114  2009/09/23 17:05:37  wenger
  Partial implementation of the 'filter change command' idea -- view
  has command it's saved in sessions, parsed, but not actually
  executed.  GUI for creating the command is partly done (but
  commented out).

  Revision 1.113  2009/05/15 20:29:38  wenger
  Implemented to-do 04.001 (be able to exclude views from drill-down;
  this is needed to fix Peptide-CGI bug 071); also fixed some dangerous
  code (strcpy, strcat) in Session.c; added GUI for setting drill-down
  exclusion and copying it when copying a view.

  Revision 1.112  2009/05/13 22:41:23  wenger
  Merged x86_64_centos5_br_0 thru x86_64_centos5_br_1/dist_1_9_1x2 to
  the trunk.

  Revision 1.111.2.2  2009/05/06 20:19:13  wenger
  Got rid of extra debug output, cleaned up a few things.

  Revision 1.111.2.1  2009/05/04 19:16:54  wenger
  Fixed some memory problems found by valgrind (looking for the problems
  that are causing core dumps on swordfish@bmrb).

  Revision 1.111  2008/10/13 19:45:16  wenger
  More const-ifying, especially Control- and csgroup-related.

  Revision 1.110  2008/09/11 20:55:31  wenger
  A few more compile warning fixes...

  Revision 1.109  2006/07/11 20:53:30  wenger
  Added info about mapping, view, and window creation parameters
  to saving of session files; updated all example sessions accordingly.

  Revision 1.108  2006/05/26 16:22:57  wenger
  Merged devise_jmol_br_0 thru devise_jmol_br_1 to the trunk.

  Revision 1.107  2006/05/10 19:04:36  wenger
  Added the new setDoHomeOnVisLinkIfInvisible and
  getDoHomeOnVisLinkIfInvisible commands (to fix a problem with the
  example session for Luis Populin), and fixed a bug in
  getDoHomeOnVisLink.

  Revision 1.106.4.1  2006/02/23 22:08:57  wenger
  Added flag for whether or not 3D views should use Jmol.

  Revision 1.106  2005/12/06 20:03:07  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.105  2003/01/13 19:25:11  wenger
  Merged V1_7b0_br_3 thru V1_7b0_br_4 to trunk.

  Revision 1.104  2002/06/17 19:41:00  wenger
  Merged V1_7b0_br_1 thru V1_7b0_br_2 to trunk.

  Revision 1.103.4.14  2005/02/15 22:49:30  wenger
  Added comment to session file (in the view section) that tells what
  mapping a view uses.

  Revision 1.103.4.13  2005/01/03 21:08:21  wenger
  Fixed bug 911 (DEVise can't open DOS-format session files).

  Revision 1.103.4.12  2004/02/25 21:48:01  wenger
  Cleaned up session files by putting blank lines between objects.

  Revision 1.103.4.11  2003/11/26 18:50:44  wenger
  Improved error reporting in Session::CreateTData().

  Revision 1.103.4.10  2003/11/19 19:40:14  wenger
  Display modes now work for symbol colors; also added some missing
  commands to the (horrible) Tcl code for copying views; minor
  improvement to error reporting.

  Revision 1.103.4.9  2003/11/05 19:09:08  wenger
  Changed all sprintfs in Session.c to snprintfs.

  Revision 1.103.4.8  2003/11/05 17:01:43  wenger
  First part of display modes for printing is implemented (view foreground
  and background colors work, haven't done anything for symbol colors yet).

  Revision 1.103.4.7  2003/06/26 16:53:00  wenger
  Index file names for per-session data sources now include the session
  name (to reduce collisions); fixed a few memory problems relating to
  the data source catalogs.

  Revision 1.103.4.6  2003/04/18 17:07:42  wenger
  Merged gcc3_br_0 thru gcc3_br_1 to V1_7b0_br.

  Revision 1.103.4.5.2.1  2003/04/18 15:26:03  wenger
  Committing *some* of the fixes to get things to compile with gcc
  3.2.2; these fixes should be safe for earlier versions of the
  comiler.

  Revision 1.103.4.5  2003/02/04 19:41:10  wenger
  Added union capability for multiple GData attribute links (will help
  with restraint visualizations for BMRB).

  Revision 1.103.4.4  2003/01/09 22:21:51  wenger
  Added "link multiplication factor" feature; changed version to 1.7.14.

  Revision 1.103.4.3  2002/12/03 23:58:17  wenger
  *** empty log message ***

  Revision 1.103.4.2  2002/11/19 19:39:32  wenger
  Better debug info if command buffer is too short.

  Revision 1.103.4.1  2002/06/11 17:27:31  wenger
  Added an option for a view to not "contribute" to home on its visual
  links; this allows a simplification of the NRG sessions, which fixes
  bug 753.

  Revision 1.103  2002/02/08 21:12:23  wenger
  Fixed bug 754 (problem saving sessions).

  Revision 1.102  2002/01/15 21:49:40  wenger
  Added session postscript capability needed for the latest peptide-cgi
  improvements.

  Revision 1.101  2001/12/12 21:05:05  wenger
  Fixed bug 740 (DEVise now inserts appropriate environment variables when
  saving per-session data source definitions).

  Revision 1.100  2001/10/04 19:03:36  wenger
  JavaScreen support allows session files without .ds extension; various
  improvements to session file processing.

  Revision 1.99  2001/10/03 19:09:50  wenger
  Various improvements to error logging; fixed problem with return value
  from JavaScreenCmd::Run().

  Revision 1.98  2001/09/24 15:28:57  wenger
  Added warning if you close or quit with unsaved session changes (note
  that visual filter changes are not considered "changes").

  Revision 1.97  2001/08/28 18:30:11  wenger
  Added 'robustOpen' option (default is true) -- this allows a session
  open to succeed even if there are unrecognized commands (useful for
  opening a newer session file with an older version of DEVise); if a
  session open fails, we now clean things up.

  Revision 1.96  2001/06/12 15:29:30  wenger
  Implemented a choice of modulus (default) or truncate color modes.

  Revision 1.95  2001/05/03 19:39:02  wenger
  Changed negative axis flag to multiplicative factor to be more flexible;
  pass multiplicative factor to JS to correct mouse location display (mods
  to JAVAC_ViewDataArea command); corrected mouse location display in DEVise
  Tcl GUI.

  Revision 1.94  2001/04/23 18:58:25  wenger
  Added negative axis label option (no GUI yet) to allow us to display
  chemical shifts the way the BMRB people want.

  Revision 1.93  2001/04/02 16:09:48  wenger
  Devised now saves configuration for 3D JavaScreen views to sessions,
  and passes it to the JavaScreen when necessary (note: JS protocol
  version is now 6.0).

  Revision 1.92  2001/03/23 18:06:31  wenger
  Color palettes are now associated with sessions; added borders to
  color chooser buttons so they're visible even if they're the same
  color as the background; fixed various color-related bugs.

  Revision 1.91  2001/02/20 20:02:43  wenger
  Merged changes from no_collab_br_0 thru no_collab_br_2 from the branch
  to the trunk.

  Revision 1.90.2.1  2001/02/16 21:37:46  wenger
  Updated DEVise version to 1.7.2; implemented 'forward' and 'back' (like
  a web browser) on 'sets' of visual filters.

  Revision 1.90  2001/01/08 20:32:42  wenger
  Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
  back onto the trunk.

  Revision 1.88.2.1  2000/10/18 20:31:53  wenger
  Merged changes from fixed_bug_616 through link_gui_improvements onto
  the branch.

  Revision 1.89  2000/10/16 16:11:39  wenger
  Link creation GUI now gives a choice of positive or negative record
  links; fixed bug 622 (record link type not saved in session files);
  fixed bug 623 (record link update problem); other link-related cleanups.

  Revision 1.88  2000/08/30 20:08:56  wenger
  Added the option of forcing a cursor to be entirely within its destination
  view; added control for whether a cursor must be at least partially within
  its destination view; generally improved implementation of cursor
  constraints.

  Revision 1.87  2000/08/07 16:23:14  wenger
  Added comment about why a command is not written to session files if
  the string length of the corresponding info is zero.

  Revision 1.86  2000/06/20 22:16:54  wenger
  Added floating-point format for axes and mouse location display.

  Revision 1.85  2000/06/20 16:57:18  wenger
  Added commands and GUI to enable/disable the display of mouse location
  in various views, and globally.

  Revision 1.84  2000/04/19 16:16:28  wenger
  Found and fixed bug 579 (crash if opening session fails); found bug
  580; better handling of session opening errors on the Tcl side;
  improved WindowVisible and WindowExists procedures.

  Revision 1.83  2000/04/07 17:36:00  wenger
  String file path in session file is specified with $DEVISE_SESSION.

  Revision 1.82  2000/03/14 17:05:09  wenger
  Fixed bug 569 (group/ungroup causes crash); added more memory checking,
  including new FreeString() function.

  Revision 1.81  2000/02/23 21:30:57  wenger
  Re-implemented session description capability.

  Revision 1.80  2000/02/17 17:50:41  wenger
  Fixed bug that caused DEVise to crash when saving a session if session
  file could not be opened.

  Revision 1.79  2000/02/16 18:51:21  wenger
  Massive "const-ifying" of strings in ClassDir and its subclasses.

  Revision 1.78  2000/02/08 22:11:47  wenger
  Added JAVAC_GetViewHelp and JAVAC_ShowViewHelp commands, added color
  edge grid, and type to JAVAC_DrawCursor command, JavaScreen protocol
  version now 4.0; added GUI to edit view help, and commands to save it
  to session files.

  Revision 1.77  2000/01/14 18:23:07  wenger
  Added resetAllFilters and JAVAC_ResetFilters commands to reset all visual
  filters back to the values defined in the session file, without actually
  re-opening the session.

  Revision 1.76  2000/01/13 23:06:51  wenger
  Got DEVise to compile with new (much fussier) compiler (g++ 2.95.2).

  Revision 1.75  1999/12/06 20:03:20  wenger
  Windows are forced to be on-screen when opening or saving a session.

  Revision 1.74  1999/12/06 18:40:48  wenger
  Simplified and improved command logging (includes fixing bug 537, command
  logs are now human-readable); added standard header to debug logs.

  Revision 1.73  1999/12/02 15:06:49  wenger
  Fixed bug 538 (slow session saving).

  Revision 1.72  1999/11/24 15:43:55  wenger
  Removed (unnecessary) CommandObj class; commands are now logged for the
  monolithic form, not just the client/server form; other command-related
  cleanups; added GUI for playing back command logs.

  Revision 1.71  1999/11/22 18:11:58  wenger
  Fixed 'command buffer conflict' errors, other command-related cleanup.

  Revision 1.70  1999/11/19 17:17:26  wenger
  Added View::SetVisualFilterCommand() method to clean up command-related
  code for filter setting.

  Revision 1.69  1999/11/16 17:01:44  wenger
  Removed all DTE-related conditional compiles; changed version number to
  1.7.0 because of removing DTE; removed DTE-related schema editing and
  data source creation GUI.

  Revision 1.68  1999/11/01 17:55:13  wenger
  Fixed compile warning.

  Revision 1.67  1999/10/26 16:29:33  wenger
  Fixed bug 519 (problems with opening various sequences of soil science
  sessions, caused by stupid composite parsers not getting reset when a
  session is closed).

  Revision 1.66  1999/10/18 15:36:30  wenger
  Window destroy events are handled better (DEVise doesn't crash); messages
  such as window destroy notifications are now passed to the client in
  client/server form.  (Parsing a string into arguments was moved from the
  Session class to the ArgList class.)

  Revision 1.65  1999/10/04 22:36:07  wenger
  Fixed bug 508 (windows move slightly when repeatedly opening and saving
  a session) -- replaced kludgey (incorrect) way of dealing with window
  manager borders with correct way; user is warned if any windows extend
  off-screen when opening or saving a session.

  Revision 1.64  1999/10/04 19:36:56  wenger
  Mouse location is displayed in "regular" DEVise.

  Revision 1.63  1999/09/24 22:02:19  wenger
  C++ code no longer allows a session to be opened while one is already
  open.

  Revision 1.62  1999/09/23 15:46:23  wenger
  Added per-session data source capability:  data sources defined in a
  session file are added to a separate catalog which is delete when the
  session is closed; the "regular" and the per-session catalog are treated
  as a single catalog while the session is open.

  Revision 1.61  1999/09/20 21:33:38  wenger
  Trailing semicolons are now removed from session file lines.

  Revision 1.60  1999/09/08 20:56:21  wenger
  Removed all Tcl dependencies from the devised (main changes are in the
  Session class); changed version to 1.6.5.

  Revision 1.59  1999/09/07 19:00:31  wenger
  dteInsertCatalogEntry command changed to tolerate an attempt to insert
  duplicate entries without causing a problem (to allow us to get rid of
  Tcl in session files); changed Condor session scripts to take out Tcl
  control statements in data source definitions; added viewGetImplicitHome
  and related code in Session class so this gets saved in session files
  (still no GUI for setting this, though); removed SEQ-related code.

  Revision 1.58  1999/09/01 19:27:01  wenger
  Debug logging improved -- directory of log file can now be specified
  with the DEVISE_LOG_DIR environment variable (changed most startup scripts
  to put it in the DEVise tmp directory); added logging of a bunch of elapsed
  times to help figure out JavaScreen performance bottlenecks.

  Revision 1.57  1999/08/13 17:22:31  wenger
  Custom view layouts are now saved to session files; removed now unused
  TileLayout code.

  Revision 1.56  1999/07/21 18:51:00  wenger
  Moved alignment and data font information from view into mapping.

  Revision 1.55  1999/07/14 18:42:38  wenger
  Added the capability to have axes without ticks and tick labels.

  Revision 1.54  1999/06/11 14:46:52  wenger
  Added the capability (mostly for the JavaScreen) to disable rubberband
  lines, cursor movement, drill down, and key actions in views (the code
  to send this info to the JS is still conditionaled out until the JS is
  ready for it).

  Revision 1.53  1999/05/17 18:37:35  wenger
  Views now have GData sending configuration that is only employed when
  connecting to the JavaScreen (eliminates the need for the current kludgey
  setup to send GData to the JS).

  Revision 1.52  1999/05/14 16:46:33  wenger
  View vertical scroll can now be configured by the user.

  Revision 1.51  1999/05/14 13:59:52  wenger
  User can now control data font family, weight, and slant, on a per-view
  basis.

  Revision 1.50  1999/04/29 17:36:31  wenger
  Implemented 'fixed cursor size' option (for the sake of the JavaScreen).

  Revision 1.49  1999/04/26 20:25:02  wenger
  Fixed bug 486.

  Revision 1.48  1999/04/22 19:29:09  wenger
  Separated the configuration of explicit (user-requested) and implicit
  home actions (no GUI for configuring the implicit home); changed the
  Condor user script accordingly; modified JavaScreen support so that this
  all works for the JS.

  Revision 1.47  1999/03/24 17:26:04  wenger
  Non-DTE data source code prevents adding duplicate data source names;
  added "nice axis" feature (sets axis limits to multiples of powers of
  10 if enabled); improved the propagation of DEVise errors back to the
  GUI; fixed bug 474 (problem with view home).

  Revision 1.46  1999/03/12 18:45:39  wenger
  Implemented duplicate symbol elimination.

  Revision 1.45  1999/03/04 15:10:47  wenger
  Implemented 'automatic filter update' features: views can be designated
  to have their visual filters automatically updated with the 'Update
  Filters' menu selection; alternatively, a session can be opened with
  the 'Open, Update, and Save' selection, which updates the designated
  filters and saves the updated session.

  Revision 1.44  1999/03/01 17:47:32  wenger
  Implemented grouping/ungrouping of views to allow custom view geometries.

  Revision 1.43  1999/02/11 19:54:34  wenger
  Merged newpile_br through newpile_br_1 (new PileStack class controls
  pile and stacks, allows non-linked piles; various other improvements
  to pile-related code).

  Revision 1.42.2.1  1999/02/11 18:24:02  wenger
  PileStack objects are now fully working (allowing non-linked piles) except
  for a couple of minor bugs; new PileStack state is saved to session files;
  piles and stacks in old session files are dealt with reasonably well;
  incremented version number; added some debug code.

  Revision 1.42  1998/12/22 19:39:08  wenger
  User can now change date format for axis labels; fixed bug 041 (axis
  type not being changed between float and date when attribute is changed);
  got dates to work semi-decently as Y axis labels; view highlight is now
  always drawn by outlining the view; fixed some bugs in drawing the highight.

  Revision 1.41  1998/12/18 19:46:59  wenger
  Oops!  Fixed bug in saving sessions resulting from the elimination of
  the getAxis and setAxis commands.

  Revision 1.40  1998/12/11 18:07:13  wenger
  Tempararily disabled saving of color palette because of bug 441.

  Revision 1.39  1998/12/08 20:01:47  wenger
  Color palette is now saved in session files.

  Revision 1.38  1998/12/01 20:04:01  wenger
  More reductions of memory usage in DEVise -- basically eliminated the
  histogram capability (this really saves a lot, since there are big
  structures in every ViewGraph for this); made creation of TDatas more
  efficient by bypassing command code.

  Revision 1.37  1998/11/19 21:13:26  wenger
  Implemented non-DTE version of DEVise (new code handles data source catalog
  functions; Tables, SQLViews, etc., are not implemented); changed version to
  1.6.0.

  Revision 1.36  1998/11/16 18:58:59  wenger
  Added options to compile without DTE code (NO_DTE), and to warn whenever
  the DTE is called (DTE_WARN).

  Revision 1.35  1998/11/11 14:30:42  wenger
  Implemented "highlight views" for record links and set links; improved
  ClassDir::DestroyAllInstances() by having it destroy all links before
  it destroys anything else -- this cuts down on propagation problems as
  views are destroyed; added test code for timing a view's query and draw.

  Revision 1.34  1998/11/06 17:59:35  wenger
  Multiple string tables fully working -- allows separate tables for the
  axes in a given view.

  Revision 1.33  1998/10/28 19:22:15  wenger
  Added code to check all data sources (runs through the catalog and tries
  to open all of them); this includes better error handling in a number of
  data source-related areas of the code; also fixed errors in the propagation
  of command results.

  Revision 1.32  1998/10/20 19:46:00  wenger
  Mapping dialog now displays the view's TData name; "Next in Pile" button
  in mapping dialog allows user to edit the mappings of all views in a pile
  without actually flipping them; user has the option to show all view names;
  new GUI to display info about all links and cursors; added API and GUI for
  count mappings.

  Revision 1.31  1998/09/30 17:44:32  wenger
  Fixed bug 399 (problems with parsing of UNIXFILE data sources); fixed
  bug 401 (improper saving of window positions).

  Revision 1.30  1998/09/22 17:23:42  wenger
  Devised now returns no image data if there are any problems (as per
  request from Hongyu); added a bunch of debug and test code to try to
  diagnose bug 396 (haven't figured it out yet); made some improvements
  to the Dispatcher to make the main loop more reentrant; added some error
  reporting to the xv window grabbing code; improved command-result
  checking code.

  Revision 1.29  1998/09/08 20:25:58  wenger
  Added option to save which view is selected when saving a session -- for
  JavaScreen client switching support.

  Revision 1.28  1998/08/10 19:08:22  wenger
  Moved command result buffer from DeviseCommand class to ControlPanel
  class -- saves 7 MB of memory!

  Revision 1.27  1998/06/10 18:04:03  wenger
  Improved new cursor drawing (bug in Mesa implementation sometimes makes
  it look ugly); cursor color now saved in sessions.

  Revision 1.26  1998/06/04 22:07:17  wenger
  View symbol alignment is now saved in session files.

  Revision 1.25  1998/05/14 18:21:08  wenger
  New protocol for JavaScreen opening sessions works (sending "real" GIF)
  except for the problem of spaces in view and window names.

  Revision 1.24  1998/05/05 15:14:47  zhenhai
  Implemented 3D Cursor as a rectangular block in the destination view
  showing left, right, top, bottom, front and back cutting planes of the
  source view.

  Revision 1.23  1998/05/02 09:02:29  taodb
  Added support for command logging
  Added support for registering events with delay

  Revision 1.22  1998/04/19 22:30:12  wenger
  Modified CreateTData() so that it works on "regular" and "internal"
  data sources.

  Revision 1.21  1998/04/16 20:07:09  wenger
  Changed Session::CreateTData() back so UNIXFILEs work.

  Revision 1.20  1998/04/16 16:53:18  wenger
  Temporarily bypassed catalog checking stuff so we can create mappings
  with TAttrLink slave TDatas.

  Revision 1.19  1998/04/10 18:29:11  wenger
  TData attribute links (aka set links) mostly implemented through table
  insertion; a crude GUI for creating them is implemented; fixed some
  bugs in link GUI; changed order in session file for TData attribute links.

  Revision 1.18  1998/03/12 20:44:57  wenger
  Partial fix for bug 320.

  Revision 1.17  1998/03/02 22:04:06  taodb
  Added control parameter to Run invocations

  Revision 1.16  1998/02/26 20:40:53  taodb
  Replaced ParseAPI calls with Command Container calls

  Revision 1.15  1998/02/20 06:16:46  beyer
  resurected histograms

  Revision 1.14  1998/02/02 18:25:59  wenger
  Strings file can now be loaded manually; name of strings file is now
  stored in session file; added 'serverExit' command and kill_devised
  script to cleanly kill devised; fixed bug 249; more info is now
  printed for unrecognized commands.

  Revision 1.13  1998/01/07 19:28:44  wenger
  Merged cleanup_1_4_7_br_4 thru cleanup_1_4_7_br_5 (integration of client/
  server library into Devise); updated solaris, sun, linux, and hp
  dependencies.

  Revision 1.12  1997/12/19 21:44:51  wenger
  Removed (now obsolete) view override color reference so saving
  sessions works.

  Revision 1.11  1997/11/24 16:22:20  wenger
  Added GUI for saving GData; turning on GData to socket now forces
  redraw of view; GData to socket params now saved in session files;
  improvement to waitForQueries command.

  Revision 1.10.2.1  1998/01/07 15:59:31  wenger
  Removed replica cababilities (since this will be replaced by collaboration
  library); integrated cslib into DEVise server; commented out references to
  Layout Manager in Tcl/Tk code; changed Dispatcher to allow the same object
  to be registered and unregistered for different file descriptors (needed
  for multiple clients); added command line argument to specify port that
  server listens on.

  Revision 1.10  1997/10/28 15:46:19  wenger
  Fixed bug 236.

  Revision 1.9  1997/10/16 16:12:00  donjerko
  Fixed the problem of not recognizing DTE sources correctly.

  Revision 1.8  1997/10/03 16:01:28  wenger
  Enabled session opening and saving from back end; incremented version; a
  few more minor fixes to session-related code.

  Revision 1.7  1997/10/03 14:36:57  wenger
  Various fixes to get session opening/saving to work with client/server
  version; reading old-style (Tcl) session files now works in back end;
  got back-end session file stuff working for multi.

  Revision 1.6  1997/10/02 18:46:31  wenger
  Opening and saving batch-style sessions in back end now fully working;
  added tk2ds.tcl script for conversion.

  Revision 1.5  1997/09/23 19:57:25  wenger
  Opening and saving of sessions now working with new scheme of mapping
  automatically creating the appropriate TData.

  Revision 1.4  1997/09/19 21:29:54  wenger
  Did various cleanups that didn't affect functionality.

  Revision 1.3  1997/09/19 20:04:10  wenger
  Now saving complete session info; works for tables as well as unixfiles;
  derived data not yet tested.

  Revision 1.2  1997/09/18 15:15:17  wenger
  Now writes a useable session file (at least in some cases).

  Revision 1.1  1997/09/17 18:43:59  wenger
  Opening sessions works except for Tcl interpreter handling result; saving
  is most of the way there.

 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>

#include <string>

#include "Session.h"
#include "DevError.h"
#include "Control.h"
#include "ParseAPI.h"
#include "DevFileHeader.h"
#include "Util.h"
#include "ParseCat.h"
#include "StringStorage.h"
#include "CmdContainer.h"
#include "DeviseCommand.h"
#include "DeviseServer.h"
#include "View.h"
#include "DataCatalog.h"
#include "DataSeg.h"
#include "Color.h"
#include "ViewGeom.h"
#include "ViewGraph.h"
#include "Layout.h"
#include "ElapsedTime.h"
#include "WinClassInfo.h"
#include "ArgList.h"
#include "CompositeParser.h"
#include "ControlPanelSimple.h"
#include "VisualLinkClassInfo.h"
#include "DeviseHistory.h"

//#define DEBUG
#define SESSION_TIMER

static char *classNameList;
static unsigned int classNameListLen;

#if !defined(lint) && defined(RCSID)
static char		rcsid[] = "$RCSfile$ $Revision$ $State$";
#endif

Boolean Session::_isJsSession = false;
Boolean Session::_openingSession = false;

DataCatalog *Session::_dataCat = NULL;
char *Session::_catFile = NULL;
char *Session::_sessionFile = NULL;
char *Session::_description = NULL;
PaletteID Session::_defaultPalette = nullPaletteID;
PaletteID Session::_sessionPalette = nullPaletteID;
Boolean Session::_dirty = false;
SessionPostscript *Session::_postscript = NULL;

static const char *_sessionPaletteName = "session";
static const char *_defaultPaletteName = "def";

/*------------------------------------------------------------------------------
 * function: Session::Open
 * Open specified session file.
 */
DevStatus
Session::Open(const char *filename)
{
#if defined(DEBUG)
  printf("Session::Open(%s)\n", filename);
#endif

  DevStatus status = StatusOk;

  //
  // Make sure we don't already have a session open.
  //
  ClassDir *classDir = ControlPanel::Instance()->GetClassDir();
  if (classDir->InstanceCount() != 0) {
	reportErrNosys("Can't open a session with a session already open");
    status += StatusFailed;
  }

  if (status.IsComplete()) {
    if (_sessionFile) {
      FreeString(_sessionFile);
    }
    _sessionFile = CopyString(filename);

    if (_description) {
      FreeString(_description);
    }
    _description = NULL;

	if (_postscript != NULL) {
	  delete _postscript;
	}
	_postscript = new SessionPostscript;

    _openingSession = true;

    ControlPanelSimple control;

    status += ReadSession(&control, filename, RunCommand);
    DeviseHistory::GetDefaultHistory()->RequestCheckpoint();

    _openingSession = false;
  }

  status += CheckWindowLocations();

  ClearDirty();

#if defined(DEBUG)
  printf("  finished Session::Open(%s)\n    ", filename);
  status.Print();
#endif

  // Don't leave things with a half-open session.
  if (!status.IsComplete()) {
    (void)Close();
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::Close
 * Close the current session.
 */
DevStatus
Session::Close()
{
#if defined(DEBUG)
  printf("Session::Close()\n");
#endif

  DevStatus status = StatusOk;

  if (_sessionFile) {
    FreeString(_sessionFile);
  }
  _sessionFile = NULL;

  if (_sessionPalette != nullPaletteID) {
    //
    // Get rid of the session-specific color palette, if any.
    //
    if (!PM_SetCurrentPalette(_defaultPalette)) {
      reportErrNosys("Error resetting color palette to default");
      status += StatusFailed;
    }

    // Note: it seems like maybe you should delete the palette colors
    // here, but that just seems to produce errors.  RKW 2001-03-23.

    if (!PM_DeletePalette(_sessionPalette)) {
      reportErrNosys("Error deleting session-specific color palette");
      status += StatusFailed;
    }
    _sessionPalette = nullPaletteID;

	//
	// Get rid of references to the session-specific color palette in
	// the GUI.
	//
    ControlPanel *control = ControlPanel::Instance();

	char cmdBuf[1024];
    control->NotifyFrontEnd("global curpalette palettes pids");

	int formatted;
	formatted = snprintf(cmdBuf, sizeof(cmdBuf), "set curpalette %s",
	    _defaultPaletteName);
	if (checkAndTermBuf2(cmdBuf, formatted).IsComplete()) {
      control->NotifyFrontEnd(cmdBuf);
	}

	formatted = snprintf(cmdBuf, sizeof(cmdBuf), "unset pids(%s)",
	    _sessionPaletteName);
	if (checkAndTermBuf2(cmdBuf, formatted).IsComplete()) {
      control->NotifyFrontEnd(cmdBuf);
	}

	formatted = snprintf(cmdBuf, sizeof(cmdBuf), "unset palettes(%s)",
	    _sessionPaletteName);
	if (checkAndTermBuf2(cmdBuf, formatted).IsComplete()) {
      control->NotifyFrontEnd(cmdBuf);
	}
  }

  // Reset the color mode to the default.
  SetColorMode(ColorModeModulus);

  // Reset the display mode to the default.
  DisplayMode::SetMode(DisplayMode::ModeNormal);

  if (_description) {
    FreeString(_description);
  }
  _description = NULL;

  delete _postscript;
  _postscript = NULL;

  DeviseHistory::GetDefaultHistory()->ClearAll();

  ViewGeom *vg = ViewGeom::GetViewGeom();
  if (!vg->IsGrouped()) {
    status += vg->Group();
  }
  ControlPanel::Instance()->DestroySessionData();
  DeleteDataSources();
  CompositeParser::ResetAll();
  _isJsSession = false;

  ClearDirty();

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::Save
 * Save session to specified file.
 */
DevStatus
Session::Save(const char *filename, Boolean asTemplate, Boolean asExport,
    Boolean withData, Boolean selectedView, Boolean savePostscript)
{
#if defined(DEBUG)
  printf("Session::Save(%s, %d, %d, %d, %d)\n", filename, asTemplate, asExport,
      withData, selectedView);
#endif

  DevStatus status = StatusOk;

  status += CheckWindowLocations();

  if (asTemplate) {
    reportErrNosys("Save as template not currently implemented");
    status = StatusFailed;
  }

  if (asExport) {
    reportErrNosys("Save as exported template not currently implemented");
    status = StatusFailed;
  }

  if (withData) {
    reportErrNosys("Save with data not currently implemented");
    status = StatusFailed;
  }

  ControlPanelSimple control;
  SaveData saveData;
  saveData.control = &control;
  saveData.fp = NULL;

  if (status.IsComplete()) {
    saveData.fp = fopen(filename, "w");
    if (!saveData.fp) {
	  char errBuf[MAXPATHLEN + 100];
	  int formatted = snprintf(errBuf, sizeof(errBuf),
	    "Can't open session file (%s) for save", filename);
	  checkAndTermBuf2(errBuf, formatted);
      reportErrSys(errBuf);
      status += StatusFailed;
    }
  }

  if (status.IsComplete()) {
    char *header = DevFileHeader::Get(FILE_TYPE_SESSION);
    fprintf(saveData.fp, "%s", header);

    fprintf(saveData.fp, "\n# Session description\n");
    fprintf(saveData.fp, "DEVise setSessionDesc {%s}\n", GetDescription());

    const char *stringFile = StringStorage::GetFile();
    if (stringFile != NULL) {
      fprintf(saveData.fp, "\n# Load strings table\n");
      char *stringWithEnv = AddEnvToPath("DEVISE_SESSION", stringFile);
      fprintf(saveData.fp, "DEVise loadStringSpace %s\n", stringWithEnv);
      FreeString(stringWithEnv);
    }

    fprintf(saveData.fp, "\n# Load color palette\n");
    PaletteID pid = PM_GetCurrentPalette();
    if (pid != nullPaletteID) {
      Palette *palette = PM_GetPalette(pid);
      if (palette == NULL) {
	reportErrNosys("Can't get palette");
        status += StatusFailed;
      } else {
        string colors = palette->ToString();
	fprintf(saveData.fp, "DEVise color SessionPalette {%s}\n",
	  colors.c_str());
      }
    }

    fprintf(saveData.fp, "\n# Set color mode (modulus or truncation)\n");
    status += SaveParams(&saveData, "getColorMode", "setColorMode", NULL);

    status += SaveDataSources(saveData.fp);

    fprintf(saveData.fp, "\n# Create views\n");
    status += ForEachInstance("view", SaveView, &saveData);

    fprintf(saveData.fp, "\n# Create interpreted mapping classes\n");
    char nameBuf[1024];
    nameBuf[0] = '\0';
    classNameList = nameBuf;
    classNameListLen = sizeof(nameBuf);
    status += ForEachInstance("mapping", SaveInterpMapping, &saveData);
    classNameList = NULL;
    classNameListLen = 0;

    fprintf(saveData.fp, "\n# Create mapping instances (GData)\n");
    status += ForEachInstance("mapping", SaveGData, &saveData);

    fprintf(saveData.fp, "\n# Create windows\n");
    // Note: we should really get this info from WinClassInfo.
    fprintf(saveData.fp, "# Params: <category> <class> <name> <x> <y> "
        "<width> <height>\n#   <exclude from print> <print pixmap>\n");
    SaveCategory(&saveData, "window");

    fprintf(saveData.fp, "\n# Set up window layouts\n");
    status += ForEachInstance("window", SaveWindowLayout, &saveData);

    fprintf(saveData.fp, "\n# Create links\n");
    status += SaveCategory(&saveData, "link");
    status += SaveRecLinkTypes(&saveData);

    fprintf(saveData.fp, "\n# Create cursors\n");
    status += SaveCategory(&saveData, "cursor");

    fprintf(saveData.fp, "\n# Create axislabel\n");
    status += SaveCategory(&saveData, "axisLabel");

    fprintf(saveData.fp, "\n# Create actions\n");
    status += SaveCategory(&saveData, "action");

    fprintf(saveData.fp, "\n# Put labels into views\n");
    status += ForEachInstance("view", SaveViewAxisLabels, &saveData);

    fprintf(saveData.fp, "\n# Put action into view\n");
    status += ForEachInstance("view", SaveViewActions, &saveData);

    fprintf(saveData.fp,
        "\n# Put cursors into views and set cursor properties\n");
    status += ForEachInstance("cursor", SaveCursor, &saveData);

    fprintf(saveData.fp, "\n# Put axis label into views\n");
    // Note: the Tcl code didn't do anything here.

    fprintf(saveData.fp, "\n# Insert mappings into views\n");
    status += ForEachInstance("view", SaveViewMappings, &saveData);

    fprintf(saveData.fp, "\n# Link views\n");
    status += ForEachInstance("link", SaveViewLinks, &saveData);

    fprintf(saveData.fp, "\n# Insert views into windows\n");
    status += ForEachInstance("window", SaveWindowViews, &saveData);

    fprintf(saveData.fp, "\n# Set window pile/stack state\n");
    status += ForEachInstance("window", SavePileStack, &saveData);

    fprintf(saveData.fp, "\n# Init history of view\n");
    status += ForEachInstance("view", SaveViewHistory, &saveData);

    fprintf(saveData.fp, "\n# Set camera location for each view\n");
    status += ForEachInstance("view", SaveCamera, &saveData);

    // This is done here because it must be done *after* mappings are
    // inserted into views.
    fprintf(saveData.fp, "\n# Set string tables for each view\n");
    status += ForEachInstance("view", SaveStringTables, &saveData);

    if (selectedView) {
      fprintf(saveData.fp, "\n# Select view\n");
      View *view = View::FindSelectedView();
      if (view != NULL) {
	    fprintf(saveData.fp, "DEVise selectView {%s}\n", view->GetName());
      }
    }

	if (savePostscript) {
      fprintf(saveData.fp, "\n# Session postscript\n");
	  if (_postscript != NULL) {
	    _postscript->Print(saveData.fp);
	  }
	}
  }

  if (saveData.fp != NULL) {
    if (fclose(saveData.fp) != 0) {
      reportErrSys("Error closing session file");
      status = StatusWarn;
    }
  }

  if (status.IsComplete()) {
    if (_sessionFile) {
      FreeString(_sessionFile);
    }
    _sessionFile = CopyString(filename);
  }

  if (status.IsComplete()) {
    ClearDirty();
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::Update
 * Update specified session file (open it, do 'home' on specified views,
 * save it).
 */
DevStatus
Session::Update(const char *filename)
{
#if defined(DEBUG)
  printf("Session::Update(%s)\n", filename);
#endif

  DevStatus status = StatusOk;

  status += Session::Open(filename);
  if (status.IsComplete()) {
    status += Session::UpdateFilters();
  }
  if (status.IsComplete()) {
    status += Session::Save(filename, false, false, false, false);
  }

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::ResetFilters
 * Reset all visual filters to the values specified in the session file.
 */
DevStatus
Session::ResetFilters()
{
#if defined(DEBUG)
  printf("Session::ResetFilters()\n");
#endif

  DevStatus status = StatusOk;

  if (_sessionFile) {
    ControlPanelSimple control;
    status += ReadSession(&control, _sessionFile, FilterCommand);
  } else {
    reportErrNosys("No session file available");
    status = StatusCancel;
  }

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::UpdateFilters
 * Do 'home' on specified views.
 */
DevStatus
Session::UpdateFilters()
{
#if defined(DEBUG)
  printf("Session::UpdateFilters()\n");
#endif

  DevStatus status = StatusOk;

  Dispatcher::Current()->WaitForQueries();

  int index = View::InitViewIterator();
  while (View::MoreView(index)) {
    View *view = View::NextView(index);
    
    if (view->AutoUpdateFilter()) {
#if defined(DEBUG)
      printf("  Updating filter for view <%s>\n", view->GetName());
#endif
      ((ViewGraph *)view)->GoHome(false);
    }
  }
  View::DoneViewIterator(index);

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::CreateTData
 * Create the given TData.  The purpose of this function is to create the
 * TData given only its name, so extra (redundant) information doesn't have
 * to be stored in session files.
 */
DevStatus
Session::CreateTData(const char *name)
{
#if defined(DEBUG)
  printf("Session::CreateTData(%s)\n", name);
#endif

#if defined(SESSION_TIMER)
  ElapsedTime et;
  et.Start();
#endif

  DevStatus status = StatusOk;

  // check for derived sources
  if( strncmp(name, "Hist: ", 6) == 0 ) {
    const char* schemaName = "HISTOGRAM";
    const char* schemaText = 
      "type HISTOGRAM ascii\n"
      "separator ' '\n"
      "sorted attr Bucket double\n"
      "attr Value int\n";
    ParseSchema(schemaName, schemaText, NULL);

    DataSeg::Set(name, "", 0, 0);

    const char *argvIn[3];
    argvIn[0] = name;
    argvIn[1] = schemaName;
    argvIn[2] = "";
    ClassDir *classDir = ControlPanel::Instance()->GetClassDir();
    const char * name = classDir->CreateWithParams("tdata", schemaName,
	    3, (char **)argvIn);
    if (name == NULL) {
	  reportErrArgs("Unable to create TData", 3, argvIn, 0);
	  status += StatusFailed;
	} else {
#if defined(DEBUG)
	  printf("  Created data source <%s>\n", name);
#endif
	}

    if (status.IsError()) reportErrNosys(
	    "Error or warning while opening session");
    return status;
  }

  char *catEntry;
  int dum1, dum2;
  char namebuf[1024];
  if (sscanf(name, "%d.%d", &dum1, &dum2) == 2) {
    // Data source is (hopefully) an internal DTE table, probably generated
    // for a TAttrLink.
    catEntry = CopyString("");
  } else {
    if (name[0] != '.') {
      // DTE goes nuts if first char of TData name isn't '.'.
      int formatted = snprintf(namebuf, sizeof(namebuf), ".%s", name);
	  checkAndTermBuf2(namebuf, formatted);
      name = namebuf;
    }
    // Get the DTE catalog entry for this data source.
	// TEMP -- memory may be leaked in here
    catEntry = ShowDataSource(name);
    if ((catEntry == NULL) || (strlen(catEntry) == 0)) {
      char buf[1024];
      int formatted = snprintf(buf, sizeof(buf),
          "Data catalog entry for %s not found!", name);
      checkAndTermBuf2(buf, formatted);
      reportErrNosys(buf);
      status = StatusFailed;
    }
  }
#if defined(DEBUG)
  printf("  catEntry = <%s>\n", catEntry != NULL ? catEntry : "NULL");
#endif

  // Get rid of braces surrounding the whole catalog entry and semicolon at
  // the end so it can get parsed.
  if (status.IsComplete()) {
    if (catEntry[0] == '{') catEntry[0] = ' ';
    int length = strlen(catEntry);
    if (catEntry[length - 1] == '}') { // { so braces match
      catEntry[length - 1] = '\0';
    } else if (catEntry[length - 1] == ' ' && catEntry[length - 2] == '}') {
      catEntry[length - 2] = '\0';
    }
    char *semicolon = strrchr(catEntry, ';');
    if (semicolon != NULL) *semicolon = ' ';
  }

  // Parse the catalog entry and assemble the proper arguments for creating
  // the TData object.
  char schema[MAXPATHLEN];
  char schemaFile[MAXPATHLEN];
  char sourceType[MAXPATHLEN];
  char param[MAXPATHLEN];
  Boolean isDteSource;
  if (status.IsComplete()) {

    // This is a kludgey way of trying to figure out whether we have a
    // DTE data source or a UNIXFILE -- it will fail if someone has a
    // table with an attribute called UNIXFILE.  However, because of changes
    // Donko has made to SQLViews, Tcl_SplitList() will barf on many
    // SQLView data sources, so we have to decide whether it belongs to
    // the DTE before with do Tcl_SplitList() on it.  RKW Mar. 12, 1998.
	//
	// Tcl_SplitList() has been replaced by ParseString().  RKW 1999-09-08.
    if (strstr(catEntry, "UNIXFILE") != NULL) {
      isDteSource = false;
    } else {
      isDteSource = true;
    }

    if (!isDteSource) {
	  ArgList args;

	  DevStatus tmpStatus = args.ParseString(catEntry);
	  if (tmpStatus != StatusOk) {
		char buf[1024];
		int formatted = snprintf(buf, sizeof(buf),
		    "Unable to parse catalog entry <%s>", catEntry);
		checkAndTermBuf2(buf, formatted);
	    reportErrNosys(buf);
	  }

	  status += tmpStatus;

	  if (tmpStatus.IsComplete()) {
        status += nice_strncpy(schema, args.GetArgs()[3], sizeof(schema));
        status += nice_strncpy(schemaFile, args.GetArgs()[4],
		    sizeof(schemaFile));
        status += nice_strncpy(sourceType, args.GetArgs()[1],
		    sizeof(sourceType));
        int formatted = snprintf(param, sizeof(param), "%s/%s",
		    args.GetArgs()[8], args.GetArgs()[2]);
		status += checkAndTermBuf2(param, formatted);
      }
    }
  }

  // Parse the schema file for the given data source, and re-set the
  // schema type if the type in the file is different from the type
  // given in the catalog.
  if (status.IsComplete()) {
    const char *result ;
    if (isDteSource) {
	  // TEMP -- memory may be leaked in here
      result = NULL;
      if (result == NULL) {
	    char buf[2048];
	    int formatted = snprintf(buf, sizeof(buf),
		    "Error parsing schema <%s>", name);
	    checkAndTermBuf2(buf, formatted);
	    reportErrNosys(buf);
	    status = StatusFailed;
      }
    } else {
      result = ParseCat(schemaFile);
      if (result == NULL) {
		char buf[1024];
		int formatted = snprintf(buf, sizeof(buf),
		    "Unable to parse schema file %s", schemaFile);
		checkAndTermBuf2(buf, formatted);
		reportErrNosys(buf);
	    status = StatusFailed;
      } else {
        if (strcmp(schema, result)) {
		  char buf[1024];
          int formatted = snprintf(buf, sizeof(buf),
		      "Warning: file %s appears to contain schema %s, not %s\n",
			  schemaFile, result, schema);
		  checkAndTermBuf2(buf, formatted);
		  reportErrNosys(buf);
		  status += StatusWarn;

          status += nice_strncpy(schema, result, sizeof(schema));
        }
      }
    }
  }

  // Execute dataSegment command.
  if (status.IsComplete()) {
	const char *filename;
    if (isDteSource) {
      filename = "";
    } else {
      filename = param;
    }
    DataSeg::Set(name, filename, 0, 0);
  }

  // Create the TData object.
  if (status.IsComplete()) {
	const char *arg2;
    const char *argvIn[3];
    if (isDteSource) {
      arg2 = name;
      argvIn[0] = name;
      argvIn[1] = "";
      argvIn[2] = "";
    } else {
      arg2 = schema;
      argvIn[0] = name;
      argvIn[1] = sourceType;
      argvIn[2] = param;
    }
    ClassDir *classDir = ControlPanel::Instance()->GetClassDir();
    const char *name = classDir->CreateWithParams("tdata",
	    (char *)arg2, 3, (char **)argvIn);
    if (name == NULL) {
	  reportErrArgs("Unable to create TData", 3, argvIn, 0);
	  status += StatusFailed;
	} else {
#if defined(DEBUG)
	  printf("  Created data source <%s>\n", name);
#endif
	}
  }

  if (catEntry != NULL) FreeString(catEntry);

#if defined(SESSION_TIMER)
  char timeBuf[256];
  int formatted = snprintf(timeBuf, sizeof(timeBuf), "Creating TData <%s>",
      name);
  checkAndTermBuf2(timeBuf, formatted);
  et.ReportTime(timeBuf);
#endif

  if (status.IsError()) reportErrNosys(
      "Error or warning while opening session");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::AddDataSource
 * Add a per-session data source.
 */
DevStatus
Session::AddDataSource(const char *catName, const char *entry)
{
#if defined(DEBUG)
  printf("Session::AddDataSource(%s, %s)\n", catName, entry);
#endif

  DevStatus status = StatusOk;

  if (strcmp(catName, ".")) {
	reportErrNosys("Catalog name for per-session data sources must be '.'\n");
    status += StatusFailed;
  } else {
    if (GetDataCatalog()->AddEntry(catName, entry) != 0) {
      status += StatusFailed;
    }
  }

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::ShowDataSource
 * Show the data source catalog entry (if any) for the given source.
 */
char *
Session::ShowDataSource(const char *sourceName)
{
#if defined(DEBUG)
  printf("Session::ShowDataSource(%s)\n", sourceName);
#endif

  char *catEntry;

  catEntry = DataCatalog::Instance()->ShowEntry(sourceName);
  if (catEntry == NULL || strlen(catEntry) == 0) {
    catEntry = GetDataCatalog()->ShowEntry(sourceName);
  }

#if defined(DEBUG)
  printf("  catEntry = <%s>\n", catEntry ? catEntry : "NULL");
#endif

  return catEntry;
}

/*------------------------------------------------------------------------------
 * function: Session::ListDataCatalog
 * Lists the data catalog, including per-session data sources.
 */
char *
Session::ListDataCatalog(const char *catName)
{
#if defined(DEBUG)
  printf("Session::ListDataCatalog(%s)\n", catName);
#endif

  char *catListMain;
  catListMain = DataCatalog::Instance()->ListCatalog(catName);

#if defined(DEBUG)
  printf("  catListMain = <%s>\n", catListMain);
#endif

  char *catListSess = NULL;
  if (!strcmp(catName, ".")) {
    catListSess = GetDataCatalog()->ListCatalog(".");
#if defined(DEBUG)
  printf("  catListSess = <%s>\n", catListSess);
#endif
  }

  char *catListTotal;
  if (catListSess && strlen(catListSess) > 0) {
	// +2 is for space and terminator.
	int bufLen = strlen(catListMain) + strlen(catListSess) + 2;
    catListTotal = new char[bufLen];
	int formatted = snprintf(catListTotal, bufLen, "%s %s", catListMain,
	    catListSess);
	checkAndTermBuf(catListTotal, bufLen, formatted);
	FreeString(catListMain);
	FreeString(catListSess);
  } else {
    catListTotal = catListMain;
  }

#if defined(DEBUG)
  printf("  catListTotal = <%s>\n", catListTotal);
#endif

  return catListTotal;
}


/*------------------------------------------------------------------------------
 * function: Session::IsSessionDataSource
 * Returns true iff the given data source is defined in the session data
 * catalog as opposed to the system one.
 */
Boolean
Session::IsSessionDataSource(const char *sourceName)
{
#if defined(DEBUG)
  printf("Session::IsSessionDataSource(%s)\n", sourceName);
#endif

  Boolean result = false;

  char *catEntry = GetDataCatalog()->ShowEntry(sourceName);
  if (catEntry && (strlen(catEntry) > 0)) result = true;
  FreeString(catEntry);

#if defined(DEBUG)
  printf("  Session::IsSessionDataSource() returns %d\n", result);
#endif

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::SetDescription
 * Set session description.
 */
void
Session::SetDescription(const char *description)
{
#if defined(DEBUG)
  printf("Session::SetDescription(%s)\n", description);
#endif

  if (_description) FreeString(_description);
  _description = CopyString(description);
}

/*------------------------------------------------------------------------------
 * function: Session::GetDescription
 * Get current session description.
 */
const char *
Session::GetDescription()
{
#if defined(DEBUG)
  printf("Session::GetDescription()\n");
#endif

  return _description ? _description : "";
}

/*------------------------------------------------------------------------------
 * function: Session::GetDescription
 * Get the session description of the named session file (returns StatusFailed
 * if the file is not a session file; description is "" if the file is a
 * session file but has no description).  Description should be freed with
 * FreeString().
 */
DevStatus
Session::GetDescription(const char *filename, char * &description)
{
#if defined(DEBUG)
  printf("Session::GetDescription(%s)\n", filename);
#endif

  DevStatus result(StatusOk);
  ControlPanelSimple control;

  result += ReadSession(&control, filename, DescriptionCommand);

  description = CopyString(control.GetResult());

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::SetDefaultPalette
 * Record the PaletteID of the default color palette.
 */
void
Session::SetDefaultPalette()
{
#if defined(DEBUG)
  printf("Session::SetDefaultPalette()\n");
#endif

  _defaultPalette = PM_GetCurrentPalette();

#if defined(DEBUG)
  printf("  default palette ID is: %ld\n", _defaultPalette);
#endif
}

/*------------------------------------------------------------------------------
 * function: Session::CreateSessionPalette
 */
DevStatus
Session::CreateSessionPalette(const char *colors)
{
#if defined(DEBUG)
  printf("Session::CreateSessionPalette(%s)\n", colors);
#endif

  DevStatus result(StatusOk);

  string colStr(colors);
  _sessionPalette = PM_NewPalette(colStr);

  if (_sessionPalette == nullPaletteID) {
    reportErrNosys("Couldn't create session-specific color palette");
    result += StatusFailed;
  } else {
    if (!PM_SetCurrentPalette(_sessionPalette)) {
      if (!PM_DeletePalette(_sessionPalette)) {
        reportErrNosys("Error deleting session-specific color palette");
      }
      _sessionPalette = nullPaletteID;
      reportErrNosys("Couldn't set session-specific color palette");
      result += StatusFailed;
    }
  }

  //
  // Set up the Tcl/Tk GUI to reflect the new palette.
  //
  if (result.IsComplete()) {
	const int bufSize = 1024 * 4;
    char cmdBuf[bufSize];
	cmdBuf[bufSize - 1] = '\0';
    ControlPanel *control = ControlPanel::Instance();

    control->NotifyFrontEnd("global curpalette palettes pids");
    int formatted = snprintf(cmdBuf, sizeof(cmdBuf), "set curpalette %s",
	  _sessionPaletteName);
	if (checkAndTermBuf2(cmdBuf, formatted).IsComplete()) {
      control->NotifyFrontEnd(cmdBuf);
	}

    PaletteID pid = PM_GetCurrentPalette();
    formatted = snprintf(cmdBuf, sizeof(cmdBuf), "set pids(%s) %d",
	    _sessionPaletteName, (int)pid);
	if (checkAndTermBuf2(cmdBuf, formatted).IsComplete()) {
      control->NotifyFrontEnd(cmdBuf);
	}

    Palette* palette = PM_GetPalette(pid);
	if (palette == nullPaletteID) {
	  reportErrNosys("Error getting current palette");
	  result += StatusFailed;
	} else {
      // Note: pColors *should* be the same as colors, but get it from
      // the palette to be safe.  RKW 2001-03-22.
      string pColors = palette->ToString();
      formatted = snprintf(cmdBuf, sizeof(cmdBuf), "set palettes(%s) {%s}",
	    _sessionPaletteName, pColors.c_str());
	  if (checkAndTermBuf2(cmdBuf, formatted).IsComplete()) {
        control->NotifyFrontEnd(cmdBuf);
	  }
    }

	DOASSERT(cmdBuf[bufSize - 1] == '\0', "Command buffer overflow");
  }

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::GetDataCatalog
 * Get the per-session data source catalog.
 */
DataCatalog *
Session::GetDataCatalog()
{
#if defined(DEBUG)
  printf("Session::GetDataCatalog()\n");
#endif

  if (!_dataCat) {
    _catFile = tempnam("/tmp", "dscat");

    // Create the file.
    FILE *fp = fopen(_catFile, "w");
    if (!fp) {
      reportErrSys("Can't create catalog file");
    } else {
      fclose(fp);
    }

    _dataCat = new DataCatalog(_catFile);
  }

  return _dataCat;
}

/*------------------------------------------------------------------------------
 * function: Session::ReadSession
 * Read and execute a DEVise session file.
 */
DevStatus
Session::ReadSession(ControlPanelSimple *control, const char *filename,
    CommandProc cp)
{
#if defined(DEBUG)
  printf("Session::ReadSession(%s)\n", filename);
#endif

  DevStatus result = StatusOk;

  FILE *fp = fopen(filename, "r");
  if (!fp) {
	char errBuf[MAXPATHLEN * 2];
	int formatted = snprintf(errBuf, sizeof(errBuf),
	    "Unable to open session file <%s>", filename);
	checkAndTermBuf2(errBuf, formatted);
    reportErrSys(errBuf);
	result += StatusFailed;
  } else {
    result += ReadSession(control, fp, cp);

    if (fclose(fp) != 0) {
	  char errBuf[MAXPATHLEN * 2];
	  int formatted = snprintf(errBuf, sizeof(errBuf),
	      "Error closing session file <%s>", filename);
	  checkAndTermBuf2(errBuf, formatted);
      reportErrSys(errBuf);
	}
  }

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::ReadSession
 * Read and execute a DEVise session file.
 */
DevStatus
Session::ReadSession(ControlPanelSimple *control, FILE *fp, CommandProc cp)
{
#if defined(DEBUG)
  printf("Session::ReadSession()\n");
#endif

  DevStatus result = StatusOk;

  result += CheckHeader(fp);

  if (result.IsComplete()) {
    int cmdCount = 0;
    const int bufSize = 1024 * 4;
    char lineBuf[bufSize];

    while (ReadCommand(fp, lineBuf, bufSize, result) && result.IsComplete()) {
#if defined(DEBUG)
      printf("  read line: <%s>\n", lineBuf);
#endif

      RemoveTrailingSemicolons(lineBuf);

#if defined(DEBUG)
      printf("  semicolons removed: %s\n", lineBuf);
#endif

      if (!IsBlankOrComment(lineBuf)) {
	    ArgList args;
		DevStatus tmpResult = args.ParseString(lineBuf);
		result += tmpResult;
	    if (tmpResult.IsComplete()) {
#if defined(DEBUG)
	      printf("Arguments: ");
          PrintArgs(stdout, args.GetCount(), args.GetArgs(), true);
#endif
		  cmdCount++;
	      result += cp(control, args.GetCount(), (char **)args.GetArgs());
	    }
	  }
    }

    if (cmdCount == 0) {
	  reportErrNosys("No DEVise commands in file -- not a session file");
      result += StatusFailed;
    }
  }

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::CheckHeader
 * Check the header of the given file to see whether it's a session file.
 */
DevStatus
Session::CheckHeader(FILE *fp)
{
#if defined(DEBUG)
  printf("Session::CheckHeader()\n");
#endif

  DevStatus result(StatusOk);

  DevFileHeader::Info info;
  DevStatus tmpResult = DevFileHeader::Read(fp, info);
  if (tmpResult.IsComplete()) {
    if (strcmp(info.fileType, FILE_TYPE_SESSION)) {
	  char buf[256];
	  int formatted = snprintf(buf, sizeof(buf), "File is type %s, not %s",
	      info.fileType, FILE_TYPE_SESSION);
	  checkAndTermBuf2(buf, formatted);
	  reportErrNosys(buf);
	  result += StatusFailed;
	}
	result += tmpResult; // in case of warning
  } else {
	//TEMP -- we may eventually want to change this to a hard failure,
	// once we've made sure all session files have the right header.
	reportErrNosys("No header information in file; may not be a "
	    "DEVise session file");
    result += StatusWarn;
  }

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::ReadCommand
 * Read a single command from the session file.  (Note that a command may
 * extend over several lines, or several commands may be on one line,
 * separated by semicolons.)
 * Returns true if a command was successfully read.
 */
Boolean
Session::ReadCommand(FILE *fp, char buf[], int bufSize, DevStatus &status)
{
  Boolean result = true;

  if (bufSize > 0) buf[0] = '\0';
  Boolean done = false;
  char *ptr = buf;
  char *last = buf + bufSize - 1;
  int leftBraces = 0;
  int rightBraces = 0;

  while (!done) {
    int tmpC = getc(fp);

	if (tmpC == EOF) {
      *ptr = '\0';
	  if (leftBraces != rightBraces) {
		const int errBufLen = 1024 * 4;
		char errBuf[errBufLen];
		int formatted = snprintf(errBuf, sizeof(errBuf),
		    "Incomplete command: <%s>", buf);
		checkAndTermBuf2(errBuf, formatted);
	    reportErrNosys(errBuf);
		status += StatusFailed;
	  }
	  done = true;
	  result = false;
	} else if (tmpC == ';' || tmpC == '\n') {
	  if (leftBraces == rightBraces) {
		// Normal end of command.
	    done = true;
		result = true;
	  }
	}

	if (!done) {
	  *ptr++ = tmpC;

	  if (tmpC == '{') {
	    leftBraces++;
	  } else if (tmpC == '}') {
	    rightBraces++;
	  }

	  if (ptr >= last) {
	    done = true;
		reportErrNosys("Command buffer too short");
		*last = '\0';
		fprintf(stderr, "Command so far is: <%s>\n", buf);
		status += StatusFailed;
		result = false;
	  }
	}
  }

  *ptr = '\0';

  dos2unix(buf);

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::IsBlankOrComment
 * Determine whether is string is a blank or comment string, or not.
 * Comments have '#' as the first non-whitespace character.
 */
Boolean
Session::IsBlankOrComment(const char *str)
{
#if defined(DEBUG)
  printf("Session::IsBlankOrComment(%s)\n", str);
#endif

  Boolean result = true;

  while (*str) {
	if (*str == '#') {
	  break;
	} else if (!isspace(*str)) {
	  result = false;
	  break;
	}
    str++;
  }

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::RemoveTrailingSemicolons
 * Removes trailing semicolons from the given string.
 */
void
Session::RemoveTrailingSemicolons(char *str)
{
#if defined(DEBUG)
  printf("Session::RemoveTrailingSemicolons(%s)\n", str);
#endif

  // Note: Tcl uses semicolons as command separators; we're not currently
  // implementing this.  However, we need to get rid of any trailing
  // semicolons so they're not parsed as arguments.  RKW 1999-09-20.
  char *tmpC = &str[strlen(str) - 1];
  while (tmpC >= str) {
    if (*tmpC == ';') {
      *tmpC = ' ';
    } else if (!isspace(*tmpC)) {
      break;
    }
    tmpC--;
  }
}

/*------------------------------------------------------------------------------
 * function: Session::RunCommand
 * Run the appropriate command.
 * Note: this function needs a ControlPanelSimple object because it uses
 * the GetResult() method not found in ControlPanel.
 */
DevStatus
Session::RunCommand(ControlPanelSimple *control, int argc, char *argv[])
{
#if defined(DEBUG)
  printf("Session::RunCommand(");
  PrintArgs(stdout, argc, argv, false);
  printf(")\n");
#endif

  DevStatus result = StatusOk;
  char errBuf[1024];

  // Note: OpenDataSource, scanDerivedSources, and SetDescription are
  // here for backwards compatibility with old session files.
  if (!strcmp(argv[0], "DEVise")) {
    result += DEViseCmd(control, argc, argv);
  } else if (!strcmp(argv[0], "OpenDataSource")) {
	result += OpenDataSourceCmd(control, argc, argv);
  } else if (!strcmp(argv[0], "scanDerivedSources")) {
	result += ScanDerivedSourcesCmd(control, argc, argv);
  } else if (!strcmp(argv[0], "SetDescription")) {
	result += SetDescriptionCmd(control, argc, argv);
  } else {
    int formatted = snprintf(errBuf, sizeof(errBuf),
	    "Unrecognized command: <%s>", argv[0]);
	checkAndTermBuf2(errBuf, formatted);
	reportErrNosys(errBuf);
    result = StatusFailed;
  }

#if defined(DEBUG)
  printf("  finished command %s; result = ", argv[1]);
  result.Print();
  printf("    result = {%s}\n", control->GetResult());
#endif

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::FilterCommand
 * Run any command that set's a view's visual filter (this is used to reset
 * all visual filters to their original values as defined in the session file).
 * Note: this function needs a ControlPanelSimple object because it uses
 * the GetResult() method not found in ControlPanel.
 */
DevStatus
Session::FilterCommand(ControlPanelSimple *control, int argc, char *argv[])
{
#if defined(DEBUG)
  printf("Session::FilterCommand(");
  PrintArgs(stdout, argc, argv, false);
  printf(")\n");
#endif

  DevStatus result = StatusOk;

  if (!strcmp(argv[0], "DEVise") && !strcmp(argv[1], "create") &&
      !strcmp(argv[2], "view")) {
#if defined(DEBUG)
    PrintArgs(stdout, argc, argv, true);
#endif
    ArgList args(7);
    args.AddArg(argv[0]);
    args.AddArg("setFilter");
    args.AddArg(argv[4]); // view name
    args.AddArg(argv[5]); // x low
    args.AddArg(argv[7]); // y low
    args.AddArg(argv[6]); // x high
    args.AddArg(argv[8]); // y high

    // Don't check result here, otherwise we stop if a view is missing, for
    // example.
    DEViseCmd(control, args.GetCount(), args.GetArgs());

  } else if (!strcmp(argv[0], "DEVise") && !strcmp(argv[1], "sessionPost")) {
    // Without the WaitForQueries() call here, links don't get updated
    // properly, because this is all happening within the resetFilters
    // command.  wenger 2013-02-19
    Dispatcher::Current()->WaitForQueries();
    DEViseCmd(control, argc, argv);
  }

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::DescriptionCommand
 * Save the session description.
 */
DevStatus
Session::DescriptionCommand(ControlPanelSimple *control, int argc, char *argv[])
{
#if defined(DEBUG)
  printf("Session::DescriptionCommand(");
  PrintArgs(stdout, argc, argv, false);
  printf(")\n");
#endif

  DevStatus result = StatusOk;
  
  //TEMP -- can we avoid reading the rest of the session file once we
  // fine the description?

  if (!strcmp(argv[0], "DEVise")) {
    if (argc >= 3 && !strcmp(argv[1], "setSessionDesc")) {
	  control->ReturnVal(API_ACK, argv[2]);
    }

    // Note: OpenDataSource, scanDerivedSources, and SetDescription are
    // here for backwards compatibility with old session files.
  } else if (strcmp(argv[0], "OpenDataSource") &&
      strcmp(argv[0], "scanDerivedSources") &&
	  strcmp(argv[0], "SetDescription")) {
	reportErrArgs("Illegal command", argc, argv, devNoSyserr);
    result += StatusFailed;
  }

  return result;
}

/*------------------------------------------------------------------------------
 * function: Session::DEViseCmd
 * DEVise command procedure for session file interpreter.
 */
DevStatus
Session::DEViseCmd(ControlPanel *control, int argc, const char * const *argv)
{
#if defined(DEBUG)
  printf("Session::DEViseCmd() ");
  PrintArgs(stdout, argc, argv);
#endif

  DevStatus status = StatusOk;

  // Don't do anything for "DEVise create tdata...", "DEVise importFileType",
  // "DEVise dteImportFileType", and "DEVise dataSegment" commands.
  if (!strcmp(argv[1], "create") && !strcmp(argv[2], "tdata")) {
    // No op.
	control->ReturnVal(0, "");
  } else if (!strcmp(argv[1], "importFileType")) {
    // No op.
	control->ReturnVal(0, "");
  } else if (!strcmp(argv[1], "dteImportFileType")) {
    // No op.
	control->ReturnVal(0, "");
  } else if (!strcmp(argv[1], "dataSegment")) {
    // No op.
	control->ReturnVal(0, "");
  } else if (!strcmp(argv[1], "sessionPost")) {
	_postscript->AddCommand(argc, argv);

    // don't pass DEVise command verb (argv[0]) or "sessionPost" (argv[1]).
    if (CmdContainer::GetCmdContainer()->RunOneCommand(argc-2, &argv[2],
	    control) <= 0) {
      status = StatusFailed;
    }
  } else {
    // don't pass DEVise command verb (argv[0])
    if (CmdContainer::GetCmdContainer()->RunOneCommand(argc-1, &argv[1],
	    control) <= 0) {
      status = StatusFailed;
    }
  }

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::OpenDataSourceCmd
 * OpenDataSource command procedure for session file interpreter.
 */
DevStatus
Session::OpenDataSourceCmd(ControlPanel *control, int argc, char *argv[])
{
#if defined(DEBUG)
  printf("Session::OpenDataSourceCmd() ");
  PrintArgs(stdout, argc, argv);
#endif

  DevStatus status = StatusOk;

  // Turn old-style (pre-DTE) name into new-style (DTE) name.
  const char *result;
  char newName[1024];
  if (argv[1][0] != '.') {
    int formatted = snprintf(newName, sizeof(newName), ".%s", argv[1]);
	if (checkAndTermBuf2(newName, formatted).IsComplete()) {
      char *current = &newName[1];
      while (*current != '\0') {
        if (*current == '.' || *current == ' ' || *current == ',') {
	      *current = '_';
        }
        current++;
      }
      result = newName;
	} else {
	  status = StatusFailed;
	  result = "";
	}
  } else {
    result = argv[1];
  }

  control->ReturnVal(0, result);

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::ScanDerivedSourcesCmd
 * ScanDerivedSources command procedure for session file interpreter.
 */
DevStatus
Session::ScanDerivedSourcesCmd(ControlPanel *control, int argc, char *argv[])
{
#if defined(DEBUG)
  printf("Session::ScanDerivedSourcesCmd() ");
  PrintArgs(stdout, argc, argv);
#endif

  DevStatus status = StatusOk;

  // This command is a no-op -- we just need to have the command exist
  // because it's in session files -- derived sources are goofed up
  // right now anyhow.

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SetDescriptionCmd
 * SetDescription command procedure for session file interpreter.
 */
DevStatus
Session::SetDescriptionCmd(ControlPanel *control, int argc, char *argv[])
{
#if defined(DEBUG)
  printf("Session::SetDescriptionCmd() ");
  PrintArgs(stdout, argc, argv);
#endif

  DevStatus status = StatusOk;

  // This command is a no-op -- we just need to have the command exist
  // because it's in session files.

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveView
 * Save information about the given view.
 */
DevStatus
Session::SaveView(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveView({%s} {%s} {%s})\n", category, devClass, instance);
#endif

  DevStatus status = StatusOk;

  fprintf(saveData->fp, "\n");

  ViewGraph *view = (ViewGraph *)View::FindViewByName(instance);
  if (view) {
    TDataMap *map = view->GetFirstMap();
    if (map) {
      const char *mapName = map->GetName();
      fprintf(saveData->fp, "# View {%s} uses mapping {%s}\n",
          instance, mapName);
    }
  }

  // Note: we should really get this info from ViewClassInfo.
  fprintf(saveData->fp, "# Params: <category> <class> <name> <xlow> "
      "<xhigh> <ylow> <yhigh>\n#   <fgcolor (normal)> <bgcolor (normal)> "
      "<fgcolor (color print)>\n#   <bgcolor (color print)> "
      "<fgcolor (b/w print)> <bgcolor (b/w print)>\n");

  status += SaveParams(saveData, "getCreateParam", "create", "view",
      devClass, instance);

  status += SaveParams(saveData, "getLabel", "setLabel", instance);

  status += SaveParams(saveData, "getViewStatistics", "setViewStatistics",
      instance);

  status += SaveParams(saveData, "getViewDimensions", "setViewDimensions",
      instance);

  status += SaveParams(saveData, "getViewSolid3D", "setViewSolid3D",
      instance);

  status += SaveParams(saveData, "getViewXYZoom", "setViewXYZoom", instance);

  status += SaveParams(saveData, "getViewDisplayDataValues",
      "setViewDisplayDataValues", instance);

  status += SaveParams(saveData, "getFont", "setFont", instance, "title");
  status += SaveParams(saveData, "getFont", "setFont", instance, "x axis");
  status += SaveParams(saveData, "getFont", "setFont", instance, "y axis");

  fprintf(saveData->fp, "# Params: <viewName> [<doHomeX> <doHomeY>] <mode> "
      "[<autoYMinZero>]<autoXMargin> <autoYMargin> <manXLo> <manYLo> "
      "<manXHi> <manYHi>\n");
  status += SaveParams(saveData, "viewGetHome", "viewSetHome", instance);

  fprintf(saveData->fp, "# Params: <viewName> <doHomeX> <doHomeY> <mode> "
      "<autoYMinZero> <autoXMargin> <autoYMargin> <manXLo> <manYLo> "
      "<manXHi> <manYHi>\n");
  status += SaveParams(saveData, "viewGetImplicitHome",
      "viewSetImplicitHome", instance);

  status += SaveParams(saveData, "viewGetHorPan", "viewSetHorPan", instance);
  status += SaveParams(saveData, "viewGetVerPan", "viewSetVerPan", instance);

  status += SaveParams(saveData, "getViewGDS", "setViewGDS", instance);
  status += SaveParams(saveData, "viewGetJSSendP", "viewSetJSSendP",
      instance, NULL, NULL, false);

  status += SaveParams(saveData, "getHistogram", "setHistogram", instance);

  status += SaveParams(saveData, "getCountMapping", "setCountMapping",
      instance);

  status += SaveParams(saveData, "viewGetIsHighlight", "viewSetIsHighlight",
      instance);

  status += SaveParams(saveData, "getXAxisDateFormat", "setXAxisDateFormat",
      instance, NULL, NULL, true);
  status += SaveParams(saveData, "getYAxisDateFormat", "setYAxisDateFormat",
      instance, NULL, NULL, true);

  status += SaveParams(saveData, "getXAxisFloatFormat", "setXAxisFloatFormat",
      instance, NULL, NULL, true);
  status += SaveParams(saveData, "getYAxisFloatFormat", "setYAxisFloatFormat",
      instance, NULL, NULL, true);

  status += SaveParams(saveData, "getViewAutoFilter", "setViewAutoFilter",
      instance, NULL, NULL, true);

  status += SaveParams(saveData, "getDupElim", "setDupElim",
      instance, NULL, NULL, true);

  status += SaveParams(saveData, "getNiceAxes", "setNiceAxes",
      instance, NULL, NULL, false);

  fprintf(saveData->fp, "# Params: <viewName> <rubberband disabled> "
      "<cursor move disabled> <drill down disabled> <keys disabled>\n");
  status += SaveParams(saveData, "viewGetDisabledActions",
      "viewSetDisabledActions", instance, NULL, NULL, false);

  status += SaveParams(saveData, "getViewHelp", "setViewHelp", instance,
      NULL, NULL, true);

  status += SaveParams(saveData, "getShowMouseLocation",
      "setShowMouseLocation", instance, NULL, NULL, true);

  status += SaveParams(saveData, "getLinkMultFact", "setLinkMultFact",
      instance, "X");
  status += SaveParams(saveData, "getLinkMultFact", "setLinkMultFact",
      instance, "Y");

  status += SaveParams(saveData, "getGAttrLinkMode", "setGAttrLinkMode",
      instance);

  if (view != NULL && view->JS3dConfigValid()) {
    status += SaveParams(saveData, "getJS3dConfig",
        "setJS3dConfig", instance, NULL, NULL, false);
  }

  status += SaveParams(saveData, "getDoHomeOnVisLink",
      "setDoHomeOnVisLink", instance, NULL, NULL, true);
  status += SaveParams(saveData, "getDoHomeOnVisLinkIfInvisible",
      "setDoHomeOnVisLinkIfInvisible", instance, NULL, NULL, true);

  status += SaveParams(saveData, "viewGetUseJmol",
      "viewSetUseJmol", instance, NULL, NULL, true);

  status += SaveParams(saveData, "getExcludeFromDrillDown",
      "setExcludeFromDrillDown", instance, NULL, NULL, true);

  status += SaveParams(saveData, "getFilterChangeCmds",
      "setFilterChangeCmds", instance, NULL, NULL, true);

  status += SaveParams(saveData, "getViewSaveFilter",
      "setViewSaveFilter", instance);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveInterpMapping
 * Save information about the given mapping class (if it is interpreted).
 */
DevStatus
Session::SaveInterpMapping(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveInterpMapping({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  // Save only _unique_ mapping classes (we may have multiple mapping
  // instances of the same class, so this function may get called multiple
  // times with identical class names).
  char buf[256];
  int formatted = snprintf(buf, sizeof(buf), "{%s}", devClass);
  if (checkAndTermBuf2(buf, formatted).IsComplete()) {
    if (strstr(classNameList, buf) == NULL) {
      if (strlen(classNameList) + strlen(buf) < classNameListLen) {
        nice_strncat(classNameList, buf, classNameListLen);
      } else {
        reportErrNosys("Ran out of room in class name list; saved session file"
	  " may have errors");
      }

      const char *result;
	  ArgList args;
      status += CallParseAPI(saveData->control, result, false, args,
	      "isInterpretedGData", instance);
      if (status.IsComplete()) {
        int isInterpreted = atoi(result);
        if (isInterpreted) {
          fprintf(saveData->fp, "DEVise createMappingClass {%s}\n", devClass);
        }
      }
    }
  } else {
    status = StatusFailed;
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveGData
 * Save information about the given GData.
 */
DevStatus
Session::SaveGData(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveGData({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  fprintf(saveData->fp, "\n");

  // Note: we should really get this info from MapInterpClassInfo.
  fprintf(saveData->fp, "# Params: <category> <class> <TData> <name> "
      "<?> <x> <y> <z> <color> <size>\n#   <pattern> <orientation> <shape> "
      "<shape attr 0> ... <shape attr 14>\n");

  status += SaveParams(saveData, "getCreateParam", "create", "mapping",
      devClass, instance);
  status += SaveParams(saveData, "getPixelWidth", "setPixelWidth", instance);
  // Note: the "create mapping" command will save the color command for
  // whatever display mode we're currently in; that will be overridden
  // by the colors in the setMappingColors command.
  status += SaveParams(saveData, "getMappingColors", "setMappingColors",
      instance);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveWindowLayout
 * Save layout information about the given window.
 */
DevStatus
Session::SaveWindowLayout(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveWindowLayout({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  fprintf(saveData->fp, "\n");

  DevStatus status = SaveParams(saveData, "getWindowLayout",
      "setWindowLayout", instance);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveViewAxisLabels
 * Save axis label information for the given view.
 */
DevStatus
Session::SaveViewAxisLabels(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveViewAxisLabels({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  fprintf(saveData->fp, "\n");

  status += SaveParams(saveData, "getAxisDisplay", "setAxisDisplay",
      instance, "X");
  status += SaveParams(saveData, "getAxisDisplay", "setAxisDisplay",
      instance, "Y");

  status += SaveParams(saveData, "getAxisTicks", "setAxisTicks",
      instance, "X");
  status += SaveParams(saveData, "getAxisTicks", "setAxisTicks",
      instance, "Y");

  status += SaveParams(saveData, "getAxisMultFact", "setAxisMultFact",
      instance, "X");
  status += SaveParams(saveData, "getAxisMultFact", "setAxisMultFact",
      instance, "Y");

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveViewActions
 * Save actions for the given view.
 */
DevStatus
Session::SaveViewActions(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveViewActions({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = SaveParams(saveData, "getAction", "setAction", instance);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveViewLinks
 * Save connections between views and links.
 */
DevStatus
Session::SaveViewLinks(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveViewLinks({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  fprintf(saveData->fp, "\n");

  const char *result;
  ArgList args;
  status += CallParseAPI(saveData->control, result, true, args,
      "getLinkViews", instance);
  if (status.IsComplete()) {
    int index;
    for (index = 0; index < args.GetCount(); index++) {
      fprintf(saveData->fp, "DEVise insertLink {%s} {%s}\n", instance,
	      args.GetArgs()[index]);
    }
  }

  status += SaveParams(saveData, "getLinkMaster", "setLinkMaster", instance,
      NULL, NULL, true);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveCursor
 * Save the given cursor.
 */
DevStatus
Session::SaveCursor(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveCursor({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  const char *result;
  ArgList args;
  status += CallParseAPI(saveData->control, result, true, args,
      "getCursorViews", instance);
  if (status.IsComplete()) {
    const char *source = args.GetArgs()[0];
    const char *dest = args.GetArgs()[1];
    if (strlen(source) > 0) {
      fprintf(saveData->fp, "DEVise setCursorSrc {%s} {%s}\n", instance,
          source);
    }
    if (strlen(dest) > 0) {
      fprintf(saveData->fp, "DEVise setCursorDst {%s} {%s}\n", instance,
          dest);
    }
  }

  args.Cleanup();
  status += CallParseAPI(saveData->control, result, true, args,
      "color", "GetCursorColor", instance);
  if (status.IsComplete()) {
    fprintf(saveData->fp, "DEVise color SetCursorColor {%s} %s\n", instance,
	    args.GetArgs()[0]);
  }

  status += SaveParams(saveData, "getCursorConstraints",
      "setCursorConstraints", instance);

  status += SaveParams(saveData, "getCursorSaveSrcFilter",
      "setCursorSaveSrcFilter", instance);

  status += SaveParams(saveData, "getCursorKeepProp",
      "setCursorKeepProp", instance);

  fprintf(saveData->fp, "\n");

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveViewMappings
 * Save mappings for the given view.
 */
DevStatus
Session::SaveViewMappings(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveViewMappings({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  const char *result;
  ArgList args;
  status += CallParseAPI(saveData->control, result, true, args,
      "getViewMappings", instance);
  if (status.IsComplete()) {
    int index;
    for (index = 0; index < args.GetCount(); index++) {
      fprintf(saveData->fp, "DEVise insertMapping {%s} {%s}\n", instance,
          args.GetArgs()[index]);
      status += SaveParams(saveData, "getMappingLegend", "setMappingLegend",
          instance, args.GetArgs()[index]);
    }
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveWindowViews
 * Save views for the given window.
 */
DevStatus
Session::SaveWindowViews(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveWindowViews({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  const char *result;
  ArgList args;
  status += CallParseAPI(saveData->control, result, true, args,
      "getWinViews", instance);
  if (status.IsComplete()) {
    //
    // Insert views into windows.
    //
    int index;
    for (index = 0; index < args.GetCount(); index++) {
      fprintf(saveData->fp, "DEVise insertWindow {%s} {%s}\n",
	      args.GetArgs()[index], instance);
    }

    //
    // Save view geometries if window layout is custom.
    //
    ClassDir *classDir = ControlPanel::Instance()->GetClassDir();
    Layout *window = (Layout *)classDir->FindInstance(instance);
    LayoutMode mode;
    window->GetLayoutMode(mode);
    if (mode == CUSTOM) {
      for (index = 0; index < args.GetCount(); index++) {
        status += SaveParams(saveData, "getViewGeometry", "setViewGeometry",
            args.GetArgs()[index], NULL, NULL, false);
      }
    }
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SavePileStack
 * Save views for the given window.
 */
DevStatus
Session::SavePileStack(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SavePileStack({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = SaveParams(saveData, "getPileStackState",
      "setPileStackState", instance);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveViewHistory
 * Save the history for the given view.
 */
DevStatus
Session::SaveViewHistory(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveViewHistory({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  fprintf(saveData->fp, "\n");

  fprintf(saveData->fp, "DEVise clearViewHistory {%s}\n", instance);

  const char *result;
  ArgList args;
  status += CallParseAPI(saveData->control, result, true, args,
      "getVisualFilters", instance);
  if (status.IsComplete()) {
    int index;
    for (index = 0; index < args.GetCount(); index++) {
      fprintf(saveData->fp, "DEVise insertViewHistory {%s} %s\n", instance,
          args.GetArgs()[index]);
    }
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveCamera
 * Save the camera location for the given view.
 */
DevStatus
Session::SaveCamera(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveCamera({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  const char *result;
  ArgList args;
  status += CallParseAPI(saveData->control, result, false, args,
      "get3DLocation", instance);
  if (status.IsComplete()) {
    fprintf(saveData->fp, "DEVise set3DLocation {%s} %s\n", instance, result);
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveStringTables
 * Save the camera location for the given view.
 */
DevStatus
Session::SaveStringTables(const char *category, const char *devClass,
    const char *instance, SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveStringTables({%s} {%s} {%s})\n", category, devClass,
      instance);
#endif

  DevStatus status = StatusOk;

  status += SaveParams(saveData, "viewGetStringTable", "viewSetStringTable",
      instance, "x");
  status += SaveParams(saveData, "viewGetStringTable", "viewSetStringTable",
      instance, "y");
  status += SaveParams(saveData, "viewGetStringTable", "viewSetStringTable",
      instance, "z");
  status += SaveParams(saveData, "viewGetStringTable", "viewSetStringTable",
      instance, "gen");

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveRecLinkTypes
 * Save the types (positive or negative) of all record links.
 */
DevStatus
Session::SaveRecLinkTypes(SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::SaveRecLinkTypes()\n");
#endif

  DevStatus status = StatusOk;

  int index = DevLink::InitIterator();
  while (DevLink::More(index)) {
    VisualLinkClassInfo *info = DevLink::Next(index);
    if (info != NULL) {
      DeviseLink *link = (DeviseLink *)info->GetInstance();
      if (link != NULL) {
        if (link->GetFlag() & VISUAL_RECORD) {
	  status += SaveParams(saveData, "getLinkType", "setLinkType",
	    link->GetName());
	}
      }
    }
  }
  DevLink::DoneIterator(index);


  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveParams
 * Get parameters from the given 'get' function, write out the given 'set'
 * function with those parameters.
 */
DevStatus
Session::SaveParams(SaveData *saveData, const char *getCommand,
    const char *setCommand,
    const char *arg0, const char *arg1, const char *arg2, Boolean addBraces)
{
#if defined(DEBUG)
  printf("Session::SaveParams(%s, %s, %s, %s, %s)\n", getCommand, setCommand,
      arg0 ? arg0 : "null", arg1 ? arg1 : "null", arg2 ? arg2 : "null");
#endif

  DevStatus status = StatusOk;

  const char *leftBrace;
  const char *rightBrace;
  if (addBraces) {
    leftBrace = "{";
    rightBrace = "}";
  } else {
    leftBrace = "";
    rightBrace = "";
  }

  const char *result;
  ArgList args;
  status += CallParseAPI(saveData->control, result, false, args,
      getCommand, arg0, arg1, arg2);
  if (status.IsComplete()) {
    if (strlen(result) > 0) { // Note: session files won't work without this
      fprintf(saveData->fp, "DEVise %s ", setCommand);
      if (arg0 != NULL) {
        fprintf(saveData->fp, "{%s} ", arg0);
      }
      if (arg1 != NULL) {
        // Note: arg2 is not passed to 'set' command.
	fprintf(saveData->fp, "{%s} ", arg1);
      }
      fprintf(saveData->fp, "%s%s%s\n", leftBrace, result, rightBrace);
    }
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::CallParseAPI
 * Run the given command; parse the result into individual arguments if
 * requested.
 * Note: this function needs a ControlPanelSimple object because it uses
 * the GetResult() method not found in ControlPanel.
 */
DevStatus
Session::CallParseAPI(ControlPanelSimple *control, const char *&result,
    Boolean splitResult, ArgList &args, const char *arg0,
	const char *arg1, const char *arg2, const char *arg3)
{
#if defined(DEBUG)
  printf("Session::CallParseAPI(%s)\n", arg0);
#endif

  DevStatus status = StatusOk;

  int argcIn;
  if (arg1 != NULL) {
    if (arg2 != NULL) {
      if (arg3 != NULL) {
        argcIn = 4;
      } else {
        argcIn = 3;
      }
    } else {
      argcIn = 2;
    }
  } else {
    argcIn = 1;
  }
  const char *argvIn[4];
  argvIn[0] = arg0;
  argvIn[1] = arg1;
  argvIn[2] = arg2;
  argvIn[3] = arg3;
  if (CmdContainer::GetCmdContainer()->RunOneCommand(argcIn, (char **)argvIn,
      control) <= 0) {
    reportErrNosys(control->GetResult());
    status = StatusFailed;
  } else {
    result = control->GetResult();
#if defined(DEBUG)
    printf("  result = <%s>\n", result);
#endif
    if (splitResult) {
      DevStatus tmpStatus = args.ParseString(result);
	  if (!tmpStatus.IsComplete()) {
        reportErrNosys(result);
	  }
      status += tmpStatus;
    } else {
	  args.Cleanup();
    }
  }

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveCategory
 * Save all instances of the given category.
 */
DevStatus
Session::SaveCategory(SaveData *saveData, const char *category)
{
#if defined(DEBUG)
  printf("Session::SaveCategory()\n");
#endif

  DevStatus status = StatusOk;
  ClassDir *classDir = ControlPanel::Instance()->GetClassDir();

  int classArgc;
  const char **tmpArgv;
  classDir->ClassNames(category, classArgc, tmpArgv);
  char **classArgv;
  CopyArgs(classArgc, tmpArgv, classArgv);

  int index;
  for (index = 0; index < classArgc; index++) {
    SaveClass(saveData, category, classArgv[index]);
  }

  FreeArgs(classArgc, classArgv);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveClass
 * Save all instances of the given class.
 */
DevStatus
Session::SaveClass(SaveData *saveData, const char *category,
     const char *devClass)
{
#if defined(DEBUG)
  printf("Session::SaveClass()\n");
#endif

  DevStatus status = StatusOk;
  ClassDir *classDir = ControlPanel::Instance()->GetClassDir();

  int instArgc;
  const char **tmpArgv;
  classDir->InstanceNames(category, devClass, instArgc, tmpArgv);
  char **instArgv;
  CopyArgs(instArgc, tmpArgv, instArgv);

  int index;
  for (index = 0; index < instArgc; index++) {
    SaveInstance(saveData, category, devClass, instArgv[index]);
  }

  FreeArgs(instArgc, instArgv);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveInstance
 * Save the given instance.
 */
DevStatus
Session::SaveInstance(SaveData *saveData, const char *category,
    const char *devClass, const char *instance)
{
#if defined(DEBUG)
  printf("Session::SaveInstance(%s, %s, %s)\n", category, devClass, instance);
#endif

  DevStatus status = SaveParams(saveData, "getCreateParam", "create", category,
      devClass, instance);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::ForEachInstance
 * Call the given function for each instance in the given category.
 */
DevStatus
Session::ForEachInstance(const char *category, InstanceFuncP function,
    SaveData *saveData)
{
#if defined(DEBUG)
  printf("Session::ForEachInstance(%s)\n", category);
#endif

  DevStatus status = StatusOk;

  ClassDir *classDir = ControlPanel::Instance()->GetClassDir();

  const char **tmpArgv;

  // Get class names
  int classArgc;
  classDir->ClassNames(category, classArgc, tmpArgv);
  char **classArgv;
  CopyArgs(classArgc, tmpArgv, classArgv);

  // For each class, get each instance name.
  int classIndex;
  for (classIndex = 0; classIndex < classArgc; classIndex++) {
    int instArgc;
    classDir->InstanceNames(category, classArgv[classIndex], instArgc, tmpArgv);
    char **instArgv;
    CopyArgs(instArgc, tmpArgv, instArgv);

    int instIndex;
    for (instIndex = 0; instIndex < instArgc; instIndex++) {
#if defined(DEBUG)
      printf("  Instance: {%s} {%s} {%s}\n", category, classArgv[classIndex],
	  instArgv[instIndex]);
#endif
      status += (*function)(category, classArgv[classIndex],
	  instArgv[instIndex], saveData);
    }

    FreeArgs(instArgc, instArgv);
  }

  FreeArgs(classArgc, classArgv);

  if (status.IsError()) reportErrNosys("Error or warning");
  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::SaveDataSources
 * Save all per-session data sources.
 */
DevStatus
Session::SaveDataSources(FILE *fp)
{
#if defined(DEBUG)
  printf("Session::SaveDataSources()\n");
#endif

  DevStatus status = StatusOk;

  char *sourceList = GetDataCatalog()->ListCatalog(".");
#if defined(DEBUG)
  printf("  sourceList = <%s>\n", sourceList);
#endif

  if (sourceList) {
	ArgList args;
    status += args.ParseString(sourceList);

	if (status.IsComplete()) {
	  if (args.GetCount() > 0) {
	    fprintf(fp, "\n# Per-session data source definitions\n");
	  }

	  for (int sourceNum = 0; sourceNum < args.GetCount(); sourceNum++) {
#if defined(DEBUG)
        printf("  source[%d] = <%s>\n", sourceNum, args.GetArgs()[sourceNum]);
#endif
		ArgList args2;
        DevStatus tmpStatus = args2.ParseString(args.GetArgs()[sourceNum]);
		status += tmpStatus;
		if (tmpStatus.IsComplete()) {
		  if (args2.GetCount() != 2) {
			reportErrNosys("Incorrect catalog listing format");
			status += StatusFailed;
		  } else {
#if defined(DEBUG)
            printf("  sourceName = <%s>\n", args2.GetArgs()[0]);
#endif
		    char *catEntry = GetDataCatalog()->ShowEntry(args2.GetArgs()[0]);
			if (!catEntry || strlen(catEntry) == 0) {
			  reportErrNosys("Can't find catalog entry");
			  status += StatusFailed;
			} else {
#if defined(DEBUG)
              printf("  catEntry = <%s>\n", catEntry);
#endif

              // Get rid of trailing semicolon and spaces so we don't gain
			  // another semicolon each time we save.
	          char *tmpC = &catEntry[strlen(catEntry) - 1];
	          while (tmpC >= catEntry) {
	            if (*tmpC == ';' || isspace(*tmpC)) {
	              *tmpC = '\0';
	            } else {
	              break;
	            }
	            tmpC--;
	          }

			  // Substitute environment variables into the data source
			  // definition.
			  char *tmpEntry = AddEnvToPath("DEVISE_DAT", catEntry);
			  char *realEntry = AddEnvToPath("DEVISE_SCHEMA", tmpEntry);

			  fprintf(fp, "DEVise dteInsertCatalogEntry . {%s}\n", realEntry);

			  FreeString(tmpEntry);
			  FreeString(realEntry);
			  FreeString(catEntry);
			}
		  }
		}
	  }
	}

    FreeString(sourceList);
  }

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::DeleteDataSources
 * Delete all per-session data sources.
 */
DevStatus
Session::DeleteDataSources()
{
#if defined(DEBUG)
  printf("Session::DeleteDataSources()\n");
#endif

  DevStatus status = StatusOk;

  if (_dataCat) {
    delete _dataCat;
    _dataCat = NULL;
  }

  if (_catFile) {
    if (unlink(_catFile) != 0) {
      reportErrSys("Can't delete session data catalog file");
    }
    FreeString(_catFile);
    _catFile = NULL;
  }

  return status;
}

/*------------------------------------------------------------------------------
 * function: Session::CheckWindowLocations
 * Warn the user if any windows extent off the screen.
 */
DevStatus
Session::CheckWindowLocations()
{
#if defined(DEBUG)
  printf("Session::CheckWindowLocations()\n");
#endif

  DevStatus status = StatusOk;

  int winIndex = DevWindow::InitIterator();
  while (DevWindow::More(winIndex)) {
    ClassInfo *info = DevWindow::Next(winIndex);
    ViewWin *window = (ViewWin *)info->GetInstance();
    if (window) {
      int argc;
      const char **argv;
      info->CreateParams(argc, argv);
      Coord relX = atof(argv[1]);
      Coord relY = atof(argv[2]);
      Coord relWidth = atof(argv[3]);
      Coord relHeight = atof(argv[4]);
#if defined(DEBUG)
      printf("Relative window geometry: %g, %g, %g, %g\n", relX, relY,
          relWidth, relHeight);
#endif
      if (relX < 0.0 || relX + relWidth > 1.0 || relY < 0.0 ||
          relY + relHeight > 1.0) {
	    char errBuf[256];
	    int formatted = snprintf(errBuf, sizeof(errBuf),
		    "Warning: window <%s> extends outside of screen",
	        window->GetName());
		checkAndTermBuf2(errBuf, formatted);
        reportErrNosys(errBuf);
		status += StatusWarn;
      }
    }
  }
  DevWindow::DoneIterator(winIndex);

  return status;
}

/*============================================================================*/
