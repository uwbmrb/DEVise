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
  $Id$

  $Log$
  Revision 1.255  2010/09/01 18:44:10  wenger
  Merged fix_3d_cursor_br_0 thru fix_3d_cursor_br_1 to trunk.

  Revision 1.254.6.6  2010/08/31 19:14:42  wenger
  Fixed the cursor behavior problems in the ambiguity code and Pistachio
  visualizations by calling RestoreCursorState() at a different point.

  Revision 1.254.6.5  2010/08/19 18:28:31  wenger
  Added class variables to control the new cursor and view symbol
  behaviors (but not the commands to set them yet) -- Y stuff for the
  cursors are temporarily turned on.

  Revision 1.254.6.4  2010/08/19 17:12:43  wenger
  Got rid of a bunch of debug output, etc.

  Revision 1.254.6.3  2010/08/19 16:50:06  wenger
  Did some cleanup of the 3D cursor fixes -- no real functional changes,
  mainly changing some method and variable names to better match the
  current functionality.

  Revision 1.254.6.2  2010/08/19 15:39:59  wenger
  More work on 3D cursor fixes -- we now remember the cursor location for
  a given TData/parentVal combination; if you go to a new combination for
  the first time, the cursor stays the same proportion of the destination
  view that it was.  (Still needs options to turn this on and off for
  X and Y independently.)

  Revision 1.254.6.1  2010/08/18 21:10:18  wenger
  Working on 3D cursor fixes -- I have a (preliminary?) implementation
  here that saves the cursor proportions relative to the destination
  view when you change TData and/or parent value for the destination
  view.  (This commit also includes loads of debug code, and turning
  off the earlier feature of trying to save view filters by TData/
  parent value.)

  Revision 1.254  2009/09/23 21:39:29  wenger
  Added clearGlobalFilterHistory command to clean up session files
  (especially for things like Peptide-CGI templates).

  Revision 1.253  2009/09/23 21:15:38  wenger
  Added parent view names to view names (optionally) displayed in views
  (to help in editing complex sessions).

  Revision 1.252  2009/09/23 20:39:02  wenger
  Added the selectParent, selectFirstChild, and selectNextChild
  commands to help in editing complex sessions.

  Revision 1.251  2009/09/23 17:05:37  wenger
  Partial implementation of the 'filter change command' idea -- view
  has command it's saved in sessions, parsed, but not actually
  executed.  GUI for creating the command is partly done (but
  commented out).

  Revision 1.250  2009/05/15 20:29:39  wenger
  Implemented to-do 04.001 (be able to exclude views from drill-down;
  this is needed to fix Peptide-CGI bug 071); also fixed some dangerous
  code (strcpy, strcat) in Session.c; added GUI for setting drill-down
  exclusion and copying it when copying a view.

  Revision 1.249  2008/10/13 19:45:16  wenger
  More const-ifying, especially Control- and csgroup-related.

  Revision 1.248  2008/09/23 22:55:33  wenger
  More const-ifying, especially drill-down-related stuff.

  Revision 1.247  2008/09/23 19:32:39  wenger
  Changed DispatchedName() to const char *.

  Revision 1.246  2006/05/26 16:22:57  wenger
  Merged devise_jmol_br_0 thru devise_jmol_br_1 to the trunk.

  Revision 1.245.4.1  2006/02/23 22:08:58  wenger
  Added flag for whether or not 3D views should use Jmol.

  Revision 1.245  2005/12/06 20:03:10  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.244  2003/01/13 19:25:11  wenger
  Merged V1_7b0_br_3 thru V1_7b0_br_4 to trunk.

  Revision 1.243  2002/06/17 19:41:00  wenger
  Merged V1_7b0_br_1 thru V1_7b0_br_2 to trunk.

  Revision 1.242  2002/05/01 21:30:03  wenger
  Merged V1_7b0_br thru V1_7b0_br_1 to trunk.

  Revision 1.241.4.18  2005/04/12 18:25:39  wenger
  Fixed bug 914 ('Select Next in Pile' doesn't work on 3D views).

  Revision 1.241.4.17  2005/03/17 17:25:04  wenger
  Added a bunch of debug code while working on bug 915.

  Revision 1.241.4.16  2004/04/23 21:57:07  wenger
  Added new 'select next view in pile' feature.

  Revision 1.241.4.15  2004/01/05 16:25:19  wenger
  "Current filter does not match last history filter" warning is now
  only shown if DEBUG is turned on in View.c.

  Revision 1.241.4.14  2003/11/05 17:01:44  wenger
  First part of display modes for printing is implemented (view foreground
  and background colors work, haven't done anything for symbol colors yet).

  Revision 1.241.4.13  2003/08/01 18:31:03  wenger
  Fixed bug 886 (home problem); found bug 887 (another home problem).

  Revision 1.241.4.12  2003/04/18 17:07:42  wenger
  Merged gcc3_br_0 thru gcc3_br_1 to V1_7b0_br.

  Revision 1.241.4.11.2.1  2003/04/18 15:26:04  wenger
  Committing *some* of the fixes to get things to compile with gcc
  3.2.2; these fixes should be safe for earlier versions of the
  comiler.

  Revision 1.241.4.11  2003/01/28 21:37:38  wenger
  Fixed bug 862 (missing data in antares session) -- the problem was
  that XDrawRectangle() with width and height of 0 doesn't draw anything
  when drawing to an Xvfb pixmap; when drawing to a window, it makes a
  one-pixel point.  Argh!

  Revision 1.241.4.10  2003/01/09 22:21:52  wenger
  Added "link multiplication factor" feature; changed version to 1.7.14.

  Revision 1.241.4.9  2003/01/06 22:31:27  wenger
  Fixed off-by-one-pixel area in coloring X axis area; added notes on
  differing width and height definitions in View and XWindowRep.

  Revision 1.241.4.8  2003/01/06 20:41:16  wenger
  Added note about visual filter/WindowRep transform setup.

  Revision 1.241.4.7  2003/01/04 21:38:26  wenger
  Fixed bugs 852, 855, and 856 (all related to view geometry and transforms
  and axis drawing).

  Revision 1.241.4.6  2002/08/27 21:14:23  wenger
  Fixed bug 817 (view not draw because of single-view pile); improved
  debug code in View and Dispatcher classes.

  Revision 1.241.4.5  2002/08/27 16:02:18  wenger
  Added 3D view warning because of bug 815; fixed bug 680 ('histograms
  not implemented' warning).

  Revision 1.241.4.4  2002/08/23 19:19:25  wenger
  Fixed bug 818 (problem with visual link/cursor grid interaction).

  Revision 1.241.4.3  2002/08/23 17:45:06  wenger
  Fixed bug 812 (problem with drawing piles when a piled view has
  auto filter update turned on).

  Revision 1.241.4.2  2002/05/27 15:13:58  wenger
  Improved fix to bug 775 (view previous filter/JS client switch
  problem) -- improved precision of view history values.

  Revision 1.241.4.1  2002/04/19 16:13:27  wenger
  Fixed bug 775 (backspace in JS doesn't work after client switch)
  (really a problem in the view history in the DEVised).

  Revision 1.241  2002/02/05 19:32:33  wenger
  Fixed bug 750 (problem with child view/pile combinations with an X
  server with no backing store); added TEST_NO_BACKING_STORE code to
  test this case even if we really do have backing store on the server.

  Revision 1.240  2001/12/13 21:35:46  wenger
  Added flexibility to enable/disable mouse location display individually
  for X and Y axes (needed for peptide-cgi session improvements requested
  by John Markley).

  Revision 1.239  2001/09/26 16:31:29  wenger
  Fixed bug 693 (DEVise rubberband line now reflects X-only zoom).

  Revision 1.238  2001/08/03 18:13:04  wenger
  Removed all OpenGL-related code.

  Revision 1.237  2001/07/27 18:32:11  wenger
  Found and fixed bug 684 (problem with home on linked views).

  Revision 1.236  2001/05/03 19:39:02  wenger
  Changed negative axis flag to multiplicative factor to be more flexible;
  pass multiplicative factor to JS to correct mouse location display (mods
  to JAVAC_ViewDataArea command); corrected mouse location display in DEVise
  Tcl GUI.

  Revision 1.235  2001/04/23 18:58:25  wenger
  Added negative axis label option (no GUI yet) to allow us to display
  chemical shifts the way the BMRB people want.

  Revision 1.234  2001/04/02 16:09:49  wenger
  Devised now saves configuration for 3D JavaScreen views to sessions,
  and passes it to the JavaScreen when necessary (note: JS protocol
  version is now 6.0).

  Revision 1.233  2001/02/20 20:02:43  wenger
  Merged changes from no_collab_br_0 thru no_collab_br_2 from the branch
  to the trunk.

  Revision 1.232.2.1  2001/02/16 21:37:47  wenger
  Updated DEVise version to 1.7.2; implemented 'forward' and 'back' (like
  a web browser) on 'sets' of visual filters.

  Revision 1.232  2001/01/08 20:32:43  wenger
  Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
  back onto the trunk.

  Revision 1.229.2.2  2000/12/27 19:38:56  wenger
  Merged changes from js_restart_improvements thru zero_js_cache_check from
  the trunk onto the js_cgi_br branch.

  Revision 1.231  2000/11/17 22:59:00  wenger
  Fixed problems with command logging of cursor movements and pile/stack
  flips.

  Revision 1.229.2.1  2000/10/18 20:31:54  wenger
  Merged changes from fixed_bug_616 through link_gui_improvements onto
  the branch.

  Revision 1.230  2000/09/11 19:24:46  wenger
  Fixed bug 617 and some other problems with the cursor constraints code.

  Revision 1.229  2000/08/10 16:10:40  wenger
  Phase 1 of getting rid of shared-memory-related code.

  Revision 1.228  2000/07/20 18:52:53  wenger
  Added support for blank floating-point format for axes and mouse location.

  Revision 1.227  2000/07/12 20:49:15  wenger
  Added first version of metavisualization session description; changed
  DEVise version to 1.7.1.

  Revision 1.226  2000/06/20 22:16:55  wenger
  Added floating-point format for axes and mouse location display.

  Revision 1.225  2000/06/20 16:57:29  wenger
  Added commands and GUI to enable/disable the display of mouse location
  in various views, and globally.

  Revision 1.224  2000/06/16 18:28:32  wenger
  Fixed bug 598 (JavaScreen crashing on bmrb/4096_side3f.ds session).

  Revision 1.223  2000/05/16 14:35:53  wenger
  Fixed minor typo.

  Revision 1.222  2000/05/10 16:19:42  wenger
  Cursors now drawn as frames rather than filled rectangles.

  Revision 1.221  2000/03/21 17:12:23  wenger
  Removed various unused methods from the View class.

  Revision 1.220  2000/03/21 16:24:35  wenger
  'f' or 'F' key in a view now flips the appropriate pile or stack, if
  there is one.

  Revision 1.219  2000/03/15 22:53:57  wenger
  Found and fixed bug 574 (invalid object access).

  Revision 1.218  2000/03/14 21:51:36  wenger
  Added more invalid object checking; had to take some memory checking
  out of client-side stuff for linking reasons.

  Revision 1.217  2000/03/14 17:05:11  wenger
  Fixed bug 569 (group/ungroup causes crash); added more memory checking,
  including new FreeString() function.

  Revision 1.216  2000/02/16 18:51:22  wenger
  Massive "const-ifying" of strings in ClassDir and its subclasses.

  Revision 1.215  2000/02/15 16:16:15  wenger
  Cursors in child views "remember" their size and location when
  switching TDatas or parent attributes.

  Revision 1.214  2000/02/09 21:28:50  wenger
  Fixed bug 562 (one problem with pop clip underflow, related to highlight
  views).

  Revision 1.213  2000/02/08 22:11:49  wenger
  Added JAVAC_GetViewHelp and JAVAC_ShowViewHelp commands, added color
  edge grid, and type to JAVAC_DrawCursor command, JavaScreen protocol
  version now 4.0; added GUI to edit view help, and commands to save it
  to session files.

  Revision 1.212  1999/12/15 16:25:42  wenger
  Fixed bugs 543 and 544 (problems with cursor movement).

  Revision 1.211  1999/12/14 20:33:52  wenger
  Rubberband lines aren't allowed to go outside of data area; rubberband
  lines are not drawn in views in which zooming is disabled.

  Revision 1.210  1999/12/14 17:57:09  wenger
  Added enableDrawing command (totally enables or disables drawing) to
  allow Omer to avoid "flashing" when he inserts views into windows.

  Revision 1.209  1999/12/01 00:09:35  wenger
  Disabled extra debug logging for tracking down Omer's crash.

  Revision 1.208  1999/11/30 22:28:05  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.207  1999/11/24 15:43:56  wenger
  Removed (unnecessary) CommandObj class; commands are now logged for the
  monolithic form, not just the client/server form; other command-related
  cleanups; added GUI for playing back command logs.

  Revision 1.206  1999/11/22 18:11:59  wenger
  Fixed 'command buffer conflict' errors, other command-related cleanup.

  Revision 1.205  1999/11/19 17:17:28  wenger
  Added View::SetVisualFilterCommand() method to clean up command-related
  code for filter setting.

  Revision 1.204  1999/11/15 22:54:52  wenger
  Fixed bug 534 ("disappearing" data in SoilSci/TwoStation5Var.ds session
  caused by highlight view/pile problems).

  Revision 1.203  1999/11/10 22:46:56  wenger
  More fixes to dimension-changing.

  Revision 1.202  1999/11/10 18:48:32  wenger
  Changing view dimenion now changes all views in a pile; PileStack makes
  sure all views in pile have the same number of dimensions; fixed 'bad
  query' problem with highlight views.

  Revision 1.201  1999/10/30 19:08:24  wenger
  Kludgey fix for bug 527 (problems with Condor/UserWeek.ds session).

  Revision 1.200  1999/10/22 20:54:02  wenger
  Major changes to how view refreshes are handled (prevents "extra" queries
  from being run in piled views, fixes bug 520); also fixed bug 517.

  Revision 1.199  1999/10/14 16:47:35  wenger
  Fixed problem with missing view titles in the JS in the
  SoilSci/TwoStation5Var.ds session (actually the background of the title
  area being the wrong color).

  Revision 1.198  1999/10/08 22:04:31  wenger
  Fixed bugs 512 and 514 (problems related to cursor moving).

  Revision 1.197  1999/10/08 19:57:44  wenger
  Fixed bugs 470 and 513 (crashes when closing a session while a query
  is running), 510 (disabling actions in piles), and 511 (problem in
  saving sessions); also fixed various problems related to cursors on
  piled views.

  Revision 1.196  1999/10/05 17:55:38  wenger
  Added debug log level.

  Revision 1.195  1999/10/04 19:36:57  wenger
  Mouse location is displayed in "regular" DEVise.

  Revision 1.194  1999/09/24 21:02:16  wenger
  Devised changes to correspond with the latest JavaScreen code:
  JAVAC_CreateView command sends more info; JS protocol version is now
  3.0; devised doesn't draw titles in JS views (JS draws the titles).

  Revision 1.193  1999/09/20 18:59:54  wenger
  Fixed problem with titles not being displayed in the JavaScreen (premature
  commit of code to avoid drawing titles in JS sessions).

  Revision 1.192  1999/08/31 21:46:16  wenger
  Found and fixed bug 506 (problem with cursor drawing when source and
  destination views are in the same window).

  Revision 1.191  1999/08/30 19:34:24  wenger
  Unified X and Y axis drawing code; found and fixed bug 505 (changing axis
  date format didn't force redraw).

  Revision 1.190  1999/08/18 20:46:04  wenger
  First step for axis drawing improvement: moved code to new DevAxis
  class with unchanged functionality.

  Revision 1.189  1999/08/17 19:46:54  wenger
  Converted Condor UserMonth session from high/low symbols to piles for
  better representation of data; fixed some cursor/pile drawing bugs and
  TData switching bugs that I found in the process.

  Revision 1.188  1999/08/13 19:43:13  wenger
  DoIsOnCursor now makes sure the mouse is within the data area.

  Revision 1.187  1999/08/09 21:52:40  wenger
  Now does a better job of avoiding having overlaps of Y axis tick labels.

  Revision 1.186  1999/08/05 21:42:35  wenger
  Cursor improvements: cursors can now be dragged in "regular" DEVise;
  cursors are now drawn with a contrasting border for better visibility;
  fixed bug 468 (cursor color not working).

  Revision 1.185  1999/07/30 21:27:02  wenger
  Partway to cursor dragging: code to change mouse cursor when on a DEVise
  cursor is in place (but disabled).

  Revision 1.184  1999/07/21 18:51:00  wenger
  Moved alignment and data font information from view into mapping.

  Revision 1.183  1999/07/16 21:35:52  wenger
  Changes to try to reduce the chance of devised hanging, and help diagnose
  the problem if it does: select() in Server::ReadCmd() now has a timeout;
  DEVise stops trying to connect to Tasvir after a certain number of failures,
  and Tasvir commands are logged; errors are now logged to debug log file;
  other debug log improvements.  Changed a number of 'char *' declarations
  to 'const char *'.

  Revision 1.182  1999/07/15 19:26:19  wenger
  More Y axis drawing improvements -- spaced ticks out a little more.

  Revision 1.181  1999/07/15 15:21:30  wenger
  Improved axis drawing when labels don't fit; Y labels spaced closer
  together.

  Revision 1.180  1999/07/14 20:45:36  wenger
  Added more debug logging.

  Revision 1.179  1999/07/14 18:42:39  wenger
  Added the capability to have axes without ticks and tick labels.

  Revision 1.178  1999/06/25 15:58:13  wenger
  Improved debug logging, especially for JavaScreen support: JavaScreenCmd.C
  now uses DebugLog facility instead of printf; dispatcher logging is turned
  on by default, and commands and queries are logged; added -debugLog command
  line flag to turn logging on and off.

  Revision 1.177  1999/06/16 19:26:45  wenger
  Fixed bug 497 (doing 'remove view' on a piled parent view with a piled
  view symbol caused crash).

  Revision 1.176  1999/06/11 20:46:47  wenger
  Fixed bug that caused DEVise to crash when closing the
  SoilSci/TwoStations.ds demo session.

  Revision 1.175  1999/06/11 14:46:53  wenger
  Added the capability (mostly for the JavaScreen) to disable rubberband
  lines, cursor movement, drill down, and key actions in views (the code
  to send this info to the JS is still conditionaled out until the JS is
  ready for it).

  Revision 1.174  1999/06/04 16:31:59  wenger
  Fixed bug 495 (problem with cursors in piled views) and bug 496 (problem
  with key presses in piled views in the JavaScreen); made other pile-
  related improvements (basically, I removed a bunch of pile-related code
  from the XWindowRep class, and implemented that functionality in the
  PileStack class).

  Revision 1.173  1999/06/01 17:37:26  wenger
  Fixed various compiler warnings.

  Revision 1.172  1999/05/17 20:55:12  wenger
  Partially-kludged fix for bug 488 (problems with cursors in piled views
  in the JavaScreen).

  Revision 1.171  1999/05/14 13:59:53  wenger
  User can now control data font family, weight, and slant, on a per-view
  basis.

  Revision 1.170  1999/05/13 18:58:54  wenger
  Removed _queryFilter member from View class to avoid confusion with
  _queryFilter in ViewGraph.

  Revision 1.169  1999/05/12 21:01:00  wenger
  Views containing view symbols can now be piled.

  Revision 1.168  1999/05/07 14:13:43  wenger
  Piled view symbols now working: pile name is specified in parent view's
  mapping, views are piled by Z specified in parent's mapping; changes
  include improvements to the Dispatcher because of problems exposed by
  piled viewsyms; for now, view symbol piles are always linked (no GUI or
  API to change this).

  Revision 1.167  1999/05/04 17:16:59  wenger
  Merged js_viewsyms_br thru js_viewsyms_br_1 (code for new JavaScreen
  protocol that deals better with view symbols).

  Revision 1.166  1999/04/23 21:08:07  wenger
  Fixed the problem with piles/date formats that caused some of Tim Wilson's
  sessions to crash.

  Revision 1.165  1999/04/21 20:35:17  wenger
  Improved interface for changing fonts, titles, etc.:
  * Fonts can now be set on a window-wide basis.
  * Setting fonts, title, or axis date format in a piled view automatically
  changes all views in the pile accordingly.

  Revision 1.164  1999/04/20 19:44:46  wenger
  Improved axis drawing:
  * Tick mark spacing is better.
  * Axes always have tick marks drawn.
  * Rounding errors fixed.
  * Off-by-one-pixel errors fixed.
  * Labels positioned better.

  Revision 1.163  1999/04/20 14:13:31  wenger
  Improved debug output.

  Revision 1.162  1999/04/16 20:59:12  wenger
  Fixed various bugs related to view symbols, including memory problem
  with MappingInterp dimensionInfo; updated create_condor_session script
  to take advantage of view symbol TData switching capability.

  Revision 1.161  1999/04/05 16:15:38  wenger
  Record- and set-link follower views with auto filter update enabled have
  'home' done on them after they are updated by a record link or set link.

  Revision 1.160  1999/03/04 15:10:58  wenger
  Implemented 'automatic filter update' features: views can be designated
  to have their visual filters automatically updated with the 'Update
  Filters' menu selection; alternatively, a session can be opened with
  the 'Open, Update, and Save' selection, which updates the designated
  filters and saves the updated session.

  Revision 1.159  1999/03/01 23:08:59  wenger
  Fixed a number of memory leaks and removed unused code.

  Revision 1.158.2.2  1999/03/17 15:16:10  wenger
  Added view Z coordinate to JAVAC_CreateView command, so the JavaScreen
  knows which views are on top of piles, etc.

  Revision 1.158.2.1  1999/03/15 22:13:20  wenger
  Fixed problems with view origin and data area origin for JavaScreen
  sessions.

  Revision 1.158  1999/02/23 15:34:59  wenger
  Fixed bugs 446 and 465 (problems with cursors in piles); fixed some
  other pile-related problems.

  Revision 1.157  1999/02/22 19:07:34  wenger
  Piling of views with view symbols is not allowed; fixed bug 461 (redrawing
  of piles); fixed bug 464 (toggling axes in a pile); fixed dynamic memory
  problems in PileStack and ViewClassInfo classes.

  Revision 1.156  1999/02/17 15:10:17  wenger
  Added "Next in Pile" button to query dialog; more pile fixes; fixed bug
  in mapping dialog updating when a view is selected.

  Revision 1.155  1999/02/11 19:54:37  wenger
  Merged newpile_br through newpile_br_1 (new PileStack class controls
  pile and stacks, allows non-linked piles; various other improvements
  to pile-related code).

  Revision 1.154  1999/02/02 17:14:40  wenger
  Fixed bug 422 (setting cursor dest w/o source causes crash).

  Revision 1.153  1999/02/01 23:13:33  wenger
  Backspace key in a view goes back one in the visual filter history.

  Revision 1.152  1999/01/06 21:25:00  wenger
  Fixed Condor2.ds redraw problem (a problem with the VisualLink class);
  also added some debug code and code to make sure view filter histories
  are consistent.

  Revision 1.151  1999/01/04 15:33:17  wenger
  Improved View symbol code; removed NEW_LAYOUT and VIEW_SHAPE conditional
  compiles; added code (GUI is currently disabled) to manually set view
  geometry (not yet saved to sessions).

  Revision 1.150.2.2  1999/02/11 18:24:05  wenger
  PileStack objects are now fully working (allowing non-linked piles) except
  for a couple of minor bugs; new PileStack state is saved to session files;
  piles and stacks in old session files are dealt with reasonably well;
  incremented version number; added some debug code.

  Revision 1.150.2.1  1998/12/29 17:24:44  wenger
  First version of new PileStack objects implemented -- allows piles without
  pile links.  Can't be saved or restored in session files yet.

  Revision 1.150  1998/12/22 19:39:12  wenger
  User can now change date format for axis labels; fixed bug 041 (axis
  type not being changed between float and date when attribute is changed);
  got dates to work semi-decently as Y axis labels; view highlight is now
  always drawn by outlining the view; fixed some bugs in drawing the highight.

  Revision 1.149  1998/12/18 22:20:51  wenger
  Removed axis label code, which doesn't seem to have been fully implemented,
  and is not used; added sanity check on visual filter at view creation.

  Revision 1.148  1998/11/11 14:30:45  wenger
  Implemented "highlight views" for record links and set links; improved
  ClassDir::DestroyAllInstances() by having it destroy all links before
  it destroys anything else -- this cuts down on propagation problems as
  views are destroyed; added test code for timing a view's query and draw.

  Revision 1.147  1998/10/20 19:46:03  wenger
  Mapping dialog now displays the view's TData name; "Next in Pile" button
  in mapping dialog allows user to edit the mappings of all views in a pile
  without actually flipping them; user has the option to show all view names;
  new GUI to display info about all links and cursors; added API and GUI for
  count mappings.

  Revision 1.146  1998/09/28 20:06:04  wenger
  Fixed bug 383 (unnecessary creation of QueryProc); moved all
  DestroySessionData() code from subclasses of ControlPanel into base class,
  because it was all the same; found and fixed bug 398 (caused by a change
  in the propagation of view selections).

  Revision 1.145  1998/09/25 20:52:55  wenger
  Fixed bug 390 (cursor drawn in slightly wrong location) (partly caused
  by problems in JavaScreenCmd code and partly by problems in XWindowRep).

  Revision 1.144  1998/09/10 23:24:27  wenger
  Fixed JavaScreen client switch GIF geometry problem.

  Revision 1.143  1998/09/08 20:26:01  wenger
  Added option to save which view is selected when saving a session -- for
  JavaScreen client switching support.

  Revision 1.142  1998/08/25 20:56:23  wenger
  Implemented support for JavaScreen cursors (not yet fully tested).

  Revision 1.141  1998/07/06 21:06:35  wenger
  More memory leak hunting -- partly tracked down some in the DTE.

  Revision 1.140  1998/07/03 23:42:09  wenger
  Fixed some memory leaks; added provision to print data segment size
  at certain places in the code.

  Revision 1.139  1998/06/24 14:49:53  beyer
  changed #ifdef 0 to #if 0

  Revision 1.138  1998/06/12 19:55:18  wenger
  Attribute of TAttr/set links can now be changed; GUI has menu of available
  attributes; attribute is set when master view is set instead of at link
  creation; misc. debug code added.

  Revision 1.137  1998/06/10 18:04:05  wenger
  Improved new cursor drawing (bug in Mesa implementation sometimes makes
  it look ugly); cursor color now saved in sessions.

  Revision 1.136  1998/05/21 18:18:30  wenger
  Most code for keeping track of 'dirty' GIFs in place; added 'test'
  command to be used for generic test code that needs to be controlled
  by GUI; added debug code in NetworkSend().

  Revision 1.135  1998/05/06 22:04:43  wenger
  Single-attribute set links are now working except where the slave of
  one is the master of another.

  Revision 1.134  1998/05/05 15:14:49  zhenhai
  Implemented 3D Cursor as a rectangular block in the destination view
  showing left, right, top, bottom, front and back cutting planes of the
  source view.

  Revision 1.133  1998/04/13 22:24:57  zhenhai
  Optimized 2D cursors to read and draw individual patches instead
  of patches for the whole region. Added 3D cursors to show directions.
  After adding a 3D cursor (same as adding 2D cursors by first
  creating the cursor, then selecting the source and destination),
  the direction of the cone (where its top is pointing to) in one graph shows the
  location and direction of the camera in another graph.

  Revision 1.132  1998/03/26 15:21:39  zhenhai
  The cursor drawings now use CursorStore as backup instead of using
  XOR mode for drawing and erasing.

  Revision 1.131  1998/03/18 08:19:42  zhenhai
  Added visual links between 3D graphics.

  Revision 1.130  1998/03/13 18:10:37  wenger
  Fixed bug 327 (gaps in view background colors).

  Revision 1.129  1998/03/08 00:00:52  wenger
  Fixed bugs 115 (I think -- can't test), 128, and 311 (multiple-link
  update problems) -- major changes to visual links.

  Revision 1.128  1998/03/05 08:10:27  zhenhai
  Added ability to view 3D graphs from six directions. Use -gl option to run,
  and click key x,y,z and X,Y,Z to select the direction you are viewing.
  Use arrow keys to pan left right up and down.

  Revision 1.127  1998/03/04 19:11:13  wenger
  Fixed some more dynamic memory errors.

  Revision 1.126  1998/02/26 00:19:04  zhenhai
  Implementation for spheres and line segments in OpenGL 3D graphics.

  Revision 1.125  1998/02/16 15:41:24  wenger
  Fixed (I believe) bug 287.

  Revision 1.124  1998/02/09 18:10:22  wenger
  Removed ViewScatter class (totally replaced by ViewData, which is a
  renamed version of TDataViewX); removed ViewRanges class (not used);
  re-made Solaris dependencies.

  Revision 1.123  1998/02/05 23:45:53  wenger
  Added view-level specification of symbol alignment, API commands, simple
  GUI for Sanjay.

  Revision 1.122  1998/02/04 20:22:02  zhenhai
  Fixed bugs of displaying date and customized text at axis.

  Revision 1.121  1998/02/03 18:31:26  zhenhai
  Fully implemented functionalities of XWindowRep with GLWindowRep. Fixed bugs in
  postscript printing.

  Revision 1.120  1998/01/23 20:37:53  zhenhai
  Fixed a bug on transformation which was caused by inconsistency between origins
  or XWindows (Upper left) and OpenGL (Lower left). Also fixed a bug for
  incorrect labelling of axis.

  Revision 1.119  1997/12/16 17:53:51  zhenhai
  Added OpenGL features to graphics.

  Revision 1.118  1997/12/12 05:50:21  weaver
  *** empty log message ***

  Revision 1.117  1997/11/24 23:14:33  weaver
  Changes for the new ColorManager.

  Revision 1.116  1997/09/05 22:36:04  wenger
  Dispatcher callback requests only generate one callback; added Scheduler;
  added DepMgr (dependency manager); various minor code cleanups.

  Revision 1.115  1997/08/20 22:10:40  wenger
  Merged improve_stop_branch_1 through improve_stop_branch_5 into trunk
  (all mods for interrupted draw and user-friendly stop).

  Revision 1.114.2.3  1997/08/20 19:32:44  wenger
  Removed/disabled debug output for interruptible drawing.

  Revision 1.114.2.2  1997/08/14 15:46:20  wenger
  Fixed bug 215; cleaned up duplicate code in BasicStats.C.

  Revision 1.114.2.1  1997/08/07 16:56:12  wenger
  Partially-complete code for improved stop capability (includes some
  debug code).

  Revision 1.114  1997/07/17 19:50:29  wenger
  Added menu selections to report number of strings and save string space.

  Revision 1.113  1997/06/25 17:05:27  wenger
  Fixed bug 192 (fixed problem in the PSWindowRep::FillPixelRect() member
  function, disabled updating of record links during print, print dialog
  grabs input.

  Revision 1.112  1997/06/04 15:50:29  wenger
  Printing windows to PostScript as pixmaps is now implemented, including
  doing so when printing the entire display.

  Revision 1.111  1997/05/28 15:38:57  wenger
  Merged Shilpa's layout manager code through the layout_mgr_branch_2 tag.

  Revision 1.110  1997/05/21 22:09:59  andyt
  Added EmbeddedTk and Tasvir functionality to client-server library.
  Changed protocol between devise and ETk server: 1) devise can specify
  that a window be "anchored" at an x-y location, with the anchor being
  either the center of the window, or the upper-left corner. 2) devise can
  let Tk determine the appropriate size for the new window, by sending
  width and height values of 0 to ETk. 3) devise can send Tcl commands to
  the Tcl interpreters running inside the ETk process.

  Revision 1.109.4.1  1997/05/20 16:10:50  ssl
  Added layout manager to DEVise

  Revision 1.109.6.1  1997/05/21 20:40:01  weaver
  Changes for new ColorManager

  Revision 1.109  1997/04/03 16:37:24  wenger
  Reduced memory and CPU usage in statistics; fixed a memory leak in the
  statistics code; switched devised back to listening on port 6100
  (changed accidentally?); turned off a bunch of debug output.

  Revision 1.108  1997/03/25 17:58:57  wenger
  Merged rel_1_3_3c through rel_1_3_4b changes into the main trunk.

  Revision 1.107  1997/03/19 19:41:07  andyt
  Embedded Tcl/Tk windows are now sized in data units, not screen pixel
  units. The old list of ETk window handles (WindowRep class) has been
  replaced by a list of ETkInfo structs, each with fields for the window
  handle, x-y coordinates, name of the Tcl script, and an "in_use"
  flag. Added an ETk_Cleanup() procedure that gets called inside
  View::ReportQueryDone and destroys all ETk windows that are not marked
  as in_use.

  Revision 1.106  1997/02/08 00:29:51  ssl
  Fixed compilation bug

  Revision 1.105  1997/02/03 19:39:59  ssl
  1) Added a new Layout interface which handles user defined layouts
  2) Added functions to set geometry and remap views as changes in the
     layout editor
  3) Added a function to notify the front end of some change so that it
     can execute a Tcl command
  4) The old TileLayout.[Ch] files still exist but are commented out
     conditionally using #ifdef NEW_LAYOUT

  Revision 1.104.4.1  1997/03/15 00:31:06  wenger
  PostScript printing of entire DEVise display now works; PostScript output
  is now centered on page; other cleanups of the PostScript printing along
  the way.

  Revision 1.104  1997/01/28 19:46:33  wenger
  Fixed bug 139; better testing of ScaledText() in client/server example;
  fixes to Exit class for client/server library.

  Revision 1.103  1997/01/28 16:50:40  wenger
  Fixed bugs 122 and 124 (reduced data and X axis area so selection rectangle
  doesn't draw over them); Devise now returns a status of 0 when exiting
  normally; cleaned up some of the exit code.

  Revision 1.102  1997/01/23 21:43:03  wenger
  Conditionaled out redrawing of entire background, and bug 123 workaround
  in View class.

  Revision 1.101  1997/01/23 17:38:27  jussi
  Removed references to GetXMin().

  Revision 1.100  1997/01/17 20:31:47  wenger
  Fixed bugs 088, 121, 122; put workaround in place for bug 123; added
  simulation of XOR drawing in PSWindowRep; removed diagnostic output
  from Tcl/Tk code; removed (at least for now) the ETk interface from
  the cslib versions of WindowRep classes so that the cslib will link
  okay; cslib server now tests XOR drawing.

  Revision 1.99  1997/01/14 20:05:31  wenger
  Fixed some compile warnings; fixed relative positions of OK/Cancel
  buttons in link GUI; removed some debug code I accidentally left
  in place.

  Revision 1.98  1997/01/14 15:48:08  wenger
  Fixed bug 105; changed '-noshm' flag to '-sharedMem 0|1' for more
  flexibility in overriding startup script default; fixed bug 116
  (off-by-one error in BufMgrFull caused buffer overflow in XWindowRep).

  Revision 1.97  1997/01/11 23:04:00  jussi
  Fixed bugs #071 and 098: clipping in piled views.

  Revision 1.96  1997/01/09 18:41:17  wenger
  Added workarounds for some Tasvir image bugs, added debug code.

  Revision 1.95  1997/01/08 19:01:42  wenger
  Fixed bug 064 and various other problems with drawing piled views;
  added related debug code.

  Revision 1.94  1996/12/30 23:51:11  andyt
  First version with support for Embedded Tcl/Tk windows. WindowRep classes
  now have member functions for creating and destroying Tk windows.
  Interface to the EmbeddedTk server is in ETkIfc.h

  Revision 1.93  1996/12/20 16:50:13  wenger
  Fonts for view label, x axis, and y axis can now be changed.

  Revision 1.92  1996/12/04 22:38:53  wenger
  Fixed bug 087 (view removal crash); noted several other fixed bugs
  in the bug list.

  Revision 1.91  1996/12/03 17:01:10  jussi
  Adjusted location of axis labels.

  Revision 1.90  1996/12/03 16:02:25  jussi
  Disabled a debugging message.

  Revision 1.89  1996/12/02 16:54:22  wenger
  Fixed compile warning; added standard headers to some files;
  conditionaled out debug code.

  Revision 1.88  1996/11/26 16:47:45  ssl
  Added support for Stacked Opaque and Transparent views

  Revision 1.87  1996/11/26 15:44:09  wenger
  Added features and fixed bugs in PostScript-related parts of the
  client/server library and the PSWindowRep class; page size can now be
  set in PSDisplay; did some cleanup of the DeviseDisplay and WindowRep
  methods (allowed elimination of many typecasts).

  Revision 1.86  1996/11/20 20:34:55  wenger
  Fixed bugs 062, 073, 074, and 075; added workaround for bug 063; make
  some Makefile improvements so compile works first time; fixed up files
  to correspond to new query catalog name.

  Revision 1.85  1996/11/20 16:49:56  jussi
  Added AbortQuery() and removed AbortAndReexecute().

  Revision 1.84  1996/11/18 23:11:19  wenger
  Added procedures to generated PostScript to reduce the size of the
  output and speed up PostScript processing; added 'small font' capability
  and trademark notice to PostScript output; improved text positioning in
  PostScript output (but still a ways to go); added a little debug code;
  fixed data/axis area bugs (left gaps); fixed misc. bugs in color handling.

  Revision 1.83  1996/11/18 18:12:53  donjerko
  Added DTE make stuff

  Revision 1.82  1996/11/13 16:56:13  wenger
  Color working in direct PostScript output (which is now enabled);
  improved ColorMgr so that it doesn't allocate duplicates of colors
  it already has, also keeps RGB values of the colors it has allocated;
  changed Color to GlobalColor, LocalColor to make the distinction
  explicit between local and global colors (_not_ interchangeable);
  fixed global vs. local color conflict in View class; changed 'dali'
  references in command-line arguments to 'tasvir' (internally, the
  code still mostly refers to Dali).

  Revision 1.81  1996/11/07 22:40:14  wenger
  More functions now working for PostScript output (FillPoly, for example);
  PostScript output also working for piled views; PSWindowRep member
  functions no longer do so much unnecessary rounding to integers (left
  over from XWindowRep); kept in place (but disabled) a bunch of debug
  code I added while figuring out piled views; added PostScript.doc file
  for some high-level documentation on the PostScript output code.

  Revision 1.80  1996/10/28 15:55:45  wenger
  Scaling and clip masks now work for printing multiple views in a window
  to PostScript; (direct PostScript printing still disabled pending correct
  text positioning and colors); updated all dependencies except Linux.

  Revision 1.79  1996/10/18 20:34:09  wenger
  Transforms and clip masks now work for PostScript output; changed
  WindowRep::Text() member functions to ScaledText() to make things
  more clear; added WindowRep::SetDaliServer() member functions to make
  Dali stuff more compatible with client/server library.

  Revision 1.78  1996/10/02 15:23:38  wenger
  Improved error handling (modified a number of places in the code to use
  the DevError class).

  Revision 1.77  1996/09/27 15:52:34  wenger
  Fixed a number of memory leaks.

  Revision 1.76  1996/09/19 20:11:53  wenger
  More PostScript output code (still disabled); some code for drawing
  view borders (disabled).

  Revision 1.75  1996/09/10 20:07:10  wenger
  High-level parts of new PostScript output code are in place (conditionaled
  out for now so that the old code is used until the new code is fully
  working); changed (c) (tm) in windows so images are not copyrighted
  by DEVise; minor bug fixes; added more debug code in the course of working
  on the PostScript stuff.

  Revision 1.74  1996/09/06 06:59:43  beyer
  - Improved support for patterns, modified the pattern bitmaps.
  - possitive pattern numbers are used for opaque fills, while
    negative patterns are used for transparent fills.
  - Added a border around filled shapes.
  - ShapeAttr3 is (temporarily) interpreted as the width of the border line.

  Revision 1.73  1996/09/05 22:18:12  jussi
  Fixed problem with system hanging in batch mode.

  Revision 1.72  1996/08/30 18:41:04  wenger
  Fixed bug 036 (problem with piled views with client/server software).

  Revision 1.71  1996/08/30 15:56:02  wenger
  Modified View and QueryProcessor code to work correctly with current
  dispatcher semantics (call back forever unless cancelled).

  Revision 1.70  1996/08/28 00:19:37  wenger
  Improved use of Dali to correctly free images (use of Dali is now fully
  functional with filenames in data).

  Revision 1.69  1996/08/23 16:55:50  wenger
  First version that allows the use of Dali to display images (more work
  needs to be done on this); changed DevStatus to a class to make it work
  better; various minor bug fixes.

  Revision 1.68  1996/08/09 22:39:00  wenger
  Fixed bug 027 (error in dispatcher code sometimes put callback into
  list twice); fixed error in View.c that caused compile failure.

  Revision 1.67  1996/08/08 20:59:11  beyer
  changed some #ifdefs #if defined

  Revision 1.66  1996/08/05 17:28:59  beyer
  Added is_safe() which checks to see if a double is safe value (ie, not
  NaN or Infinity).  Made SetVisualFilter check the new filter for safety.

  Revision 1.65  1996/08/05 16:35:16  beyer
  Made the _viewList statically allocated.  Sometimes the _viewList can
  be queried before any views (and, as was the case, the _viewList) are
  created.

  Revision 1.64  1996/08/04 21:03:35  beyer
  Added view-locks and changed key handling.

  Revision 1.63  1996/08/03 15:48:37  jussi
  Pixmaps are restored only for 2D views.

  Revision 1.62  1996/08/03 15:37:05  jussi
  Flag _solid3D now has three values.

  Revision 1.61  1996/07/25 14:22:58  jussi
  Added aborted parameter to ReportQueryDone().

  Revision 1.60  1996/07/23 21:18:02  jussi
  Added a couple of debugging statements, removed extra callback
  request to the dispatcher.

  Revision 1.59  1996/07/23 19:34:01  beyer
  Changed dispatcher so that pipes are not longer used for callback
  requests from other parts of the code.

  Revision 1.58  1996/07/23 17:16:28  jussi
  Added support for piled views.

  Revision 1.57  1996/07/21 02:21:22  jussi
  Added _xyZoom flag. Fixed problem when small exposures caused
  the whole view to be erased but not redrawn.

  Revision 1.56  1996/07/20 18:47:17  jussi
  Added solid3D flag.

  Revision 1.55  1996/07/15 21:33:47  jussi
  Added SetPattern(Pattern0) just before label is drawn.

  Revision 1.54  1996/07/14 16:51:36  jussi
  Added handling of special case where view is unmapped but is
  requested to unhighlight as if the highlighting was still on.

  Revision 1.53  1996/07/13 17:25:38  jussi
  When view is iconified, statistics are collected but data
  is not drawn. Added ViewRecomputed() callback interface.

  Revision 1.52  1996/07/12 23:41:30  jussi
  When View is destroyed, it is removed from the _viewList.
  Got rid of Init() method, integrated it with the constructor.

  Revision 1.51  1996/07/10 19:29:03  jussi
  Fixed problem with 3D focus points.

  Revision 1.50  1996/07/08 20:31:51  jussi
  Pixmaps are restored now only if view is not a master of a record
  link nor a slave of one.

  Revision 1.49  1996/07/05 17:10:33  jussi
  Added missing call to CompRhoPhiTheta().

  Revision 1.48  1996/06/27 19:04:48  jussi
  The user can now switch between 2D and 3D display, the
  data is refreshed and displayed accordingly.

  Revision 1.47  1996/06/27 15:43:55  jussi
  Added method AbortAndReexecuteQuery which allows the QueryProc
  to ask the view to re-issue queries when TData has changed.

  Revision 1.46  1996/06/24 19:35:39  jussi
  Added a win->Flush() call to strategic points so that view
  updates get propagated to the X server.

  Revision 1.45  1996/06/21 19:56:10  jussi
  Default 3D navigation is now radial instead of rectangular.

  Revision 1.44  1996/06/21 19:31:54  jussi
  Replaced MinMax calls with calls to MIN() and MAX().

  Revision 1.43  1996/06/20 21:40:14  jussi
  Added call to SetVisualFilter() to SetCamera() which causes the
  (non-existent) filter change to be reported to clients, including
  the 3D query dialog.

  Revision 1.42  1996/06/16 02:06:56  jussi
  Various improvements in debugging.

  Revision 1.41  1996/06/15 13:46:39  jussi
  X and Y axes now use the view foreground color as their color.
  The axis.color field was removed.

  Revision 1.40  1996/06/15 07:05:08  yuc
  Change CompRhoPhiTheta so it will display x vs y and z-axis into the
  screen, add spherical coordinate system to CompRhoPhiTheta also.

  Revision 1.39  1996/06/13 00:14:31  jussi
  Added support for XY cursors. All types of cursors can now
  be moved by clicking on their new location in the data area.
  Previously only the X label area was sensitive for cursor
  movement.

  Revision 1.38  1996/05/31 15:30:28  jussi
  Added support for tick marks in axes. The spacing and location
  of tick marks is set automatically to something reasonable,
  even if the axis range is not.

  Revision 1.37  1996/05/14 18:05:16  jussi
  Added initialization of view callback list. Added debugging
  statements.

  Revision 1.36  1996/05/09 18:12:19  kmurli
  No change to this makefile.

  Revision 1.35  1996/05/07 16:32:40  jussi
  Moved Action member variable to ViewGraph. Move implementation of
  HandleKey, HandlePress and HandlePopup to ViewGraph as well.

  Revision 1.34  1996/04/22 20:25:46  jussi
  Added calls to Dispatcher::InsertMarker() to a few additional places
  where a View redisplay must be initiated.

  Revision 1.33  1996/04/20 19:52:16  kmurli
  Changed Viex.c to use a pipe mechanism to call itself if it needs to be
  done again. The view now is not called contiously by the Dispatcher,instead
  only of there is some data in the pipe.
  The pipe mechanism is implemented transparently through static functions
  in the Dispatcher.c (InsertMarker,CreateMarker,CloseMarker,FlushMarker)

  Revision 1.32  1996/04/19 19:07:02  wenger
  Changed exit(1) to Exit::DoExit(1).

  Revision 1.31  1996/04/16 20:07:01  jussi
  Replaced assert() calls with DOASSERT macro.

  Revision 1.30  1996/04/09 22:51:44  jussi
  Added SetOverrideColor() and GetOverrideColor().

  Revision 1.29  1996/04/09 20:35:11  jussi
  Minor fixes.

  Revision 1.28  1996/04/09 18:05:28  jussi
  Minor improvements.

  Revision 1.27  1996/04/05 20:12:34  wenger
  Fixed error causing pure virtual function to be called
  if a session was closed during a query; fixed an error
  in one of the Linux Makefiles; updated other Makefiles
  to allow testWindowRep to be built on all architectures.

  Revision 1.26  1996/03/29 18:13:57  wenger
  Got testWindowRep to compile and run, added drawing in
  windows; fixed a few more compile warnings, etc.

  Revision 1.25  1996/03/06 19:35:40  jussi
  Added GetNumDimensions() and SetNumDimensions().

  Revision 1.24  1996/02/06 19:32:41  jussi
  Moved logo drawing to ViewWin.c.

  Revision 1.23  1996/02/05 23:56:57  jussi
  Added DEVise logo display.

  Revision 1.22  1996/02/02 21:53:45  jussi
  Removed SetFgColor() right after SetXorMode() which changed the
  effect of the xor function.

  Revision 1.21  1996/02/01 20:28:52  jussi
  Axis areas were cleared even if axes were not displayed. Fixed
  this.

  Revision 1.20  1996/01/30 21:11:21  jussi
  Replaced references to specific colors with references to
  BackgrounColor and ForegroundColor.

  Revision 1.19  1996/01/16 17:07:29  jussi
  Redefined computation of cursor area.

  Revision 1.18  1995/12/29 22:41:01  jussi
  Symbols are turned on and connectors off before a pixel map
  is saved.

  Revision 1.17  1995/12/29 18:33:13  jussi
  Forgot to comment out the #define DEBUG statement in last check-in.

  Revision 1.16  1995/12/29 18:27:52  jussi
  Added new cursor mechanism; cursors are drawn as inverted rectangles
  which are easier to see than the old cursor lines.

  Revision 1.15  1995/12/14 21:11:05  jussi
  Replaced 0x%x with %p.

  Revision 1.14  1995/12/14 17:18:24  jussi
  More small fixes to get rid of g++ -Wall warnings.

  Revision 1.13  1995/12/14 17:14:56  jussi
  Small fixes.

  Revision 1.12  1995/12/06 21:18:12  jussi
  Minor improvements: X high label no longer gets overdrawn by the highlight
  rectangle when label is at top; erasing data area erases top pixel line
  as well; PushClip() and AbsoluteText() interface changed slightly, so
  now the caller has to decrement width and height by one if passing pixel
  coordinates.

  Revision 1.11  1995/12/05 22:05:00  jussi
  A constant integer value is saved at the head of a pixmap file
  to make sure that a machine which tries to load the pixmap has
  the same endianness.

  Revision 1.10  1995/12/05 17:02:00  jussi
  Moved _stats to ViewGraph (superclass) so that statistics can be
  turned on and displayed without having to redisplay the data itself.

  Revision 1.9  1995/12/04 18:06:05  jussi
  Added GetLabelParams and replaced ToggleStatDisplay with SetStatDisplay.

  Revision 1.8  1995/12/02 21:23:26  jussi
  Corrected code which was based on the assumption that a view
  always has origin 0,0 which is no longer true with margins
  surrounding the view. Fixed numerous other bugs.

  Revision 1.7  1995/11/28  05:08:24  ravim
  Support for statistics.

  Revision 1.6  1995/11/25 19:55:37  jussi
  Added debugging statement.

  Revision 1.5  1995/11/24 21:30:39  jussi
  Added copyright notice and cleaned up code. Added debugging
  statements.

  Revision 1.4  1995/09/26 23:05:12  jussi
  Made X low label left-justified.

  Revision 1.3  1995/09/14 19:19:51  jussi
  Corrected a couple of perror messages.

  Revision 1.2  1995/09/05 21:13:15  jussi
  Added/updated CVS header.
*/

//******************************************************************************

#include <time.h>
#if defined(DEBUG_MEM)
#  include <unistd.h>
#endif

//#define DEBUG
#define DEBUG_LOG

#include <unistd.h>

#include "Geom.h"
#include "WindowRep.h"
#include "FilterQueue.h"
#include "Control.h"
#include "TimeStamp.h"
#include "Parse.h"
#include "Map3D.h"
#ifdef JPEG
#include "Jpeg.h"
#endif
#include "Display.h"
#include "PSDisplay.h"
#include "Init.h"
#include "DaliIfc.h"
#include "DevError.h"
#include "Util.h"
#include "View.h"
#include "RecordLink.h"
#include "Scheduler.h"
#include "DepMgr.h"
#include "JavaScreenCmd.h"
#include "PileStack.h"
#include "DebugLog.h"
#include "Session.h"
#include "CmdContainer.h"
#include "ArgList.h"

//******************************************************************************

// Whether to draw view borders -- must eventually be controlled by GUI.
static const Boolean viewBorder = false;

// Whether to fill the background of the entire view, rather than filling
// the various parts separately.  About the only time you wouldn't want to
// use this is on a machine that doesn't have backing store for the windows.
#define FILL_WHOLE_BACKGROUND 0

// Set COLOR_AREAS to 1 to color the label, axis, and data areas
// differentially (for debugging).  (This works best on views with a white
// background.)
#define COLOR_AREAS 0

// Whether to use the workaround for bug 123.
#define USE_BUG123_WORKAROUND 0

/* width/height of sensitive area for cursor */
static const int VIEW_CURSOR_SENSE = 10;

/*
   pixel image must be at least 64K bytes before it is saved with the
   session file
*/
static const int VIEW_BYTES_BEFORE_SAVE = 64 * 1024;

static const Coord DELTA_X = .000000000001;
static const Coord DELTA_Y = .000000000001;

static const int highlightWidth = 3;
static const int halfHighlightWidth = (int)((highlightWidth + 1.0) / 2.0);

/* id for the next view created. view == NULL return id = 0. */

int View::_nextId = 0;
static ViewList theViewList;
ViewList *View::_viewList = &theViewList;   /* list of all views */

int View::_nextPos = 0;
ViewCallbackList *View::_viewCallbackList = 0;

#if 0
DataSourceFixedBuf *View::_viewTableBuffer = NULL;
#endif

Boolean View::_drawCursors = true;
Boolean View::_jsCursors = false;
Boolean View::_showNames = false;
Boolean View::_drawingEnabled = true;
int View::_globalShowMouseLocation = 1;

//******************************************************************************
// Constructors and Destructors
//******************************************************************************

View::View(char* name, VisualFilter& initFilter, PColorID fgid, PColorID bgid,
		   AxisLabel*, AxisLabel*,
		   AxisLabel *, int weight, Boolean boundary)
	: ViewWin(name, fgid, bgid, weight, boundary),
	  _xAxis(this, DevAxis::AxisX, false, _defaultXAxisWidth,
	      _noTicksXAxisWidth, 4, 60),
      _yAxis(this, DevAxis::AxisY, false, _defaultYAxisWidth,
	      _noTicksYAxisWidth, 4, 20),
      _zAxis(this, DevAxis::AxisZ, false, _defaultZAxisWidth,
	      _noTicksZAxisWidth, 4, 40)
{
#if defined(DEBUG)
	printf("View::View(%s, this = %p)\n", name, this);
#endif

    _objectValid.Set();

	_inDestructor = false;

	controlPanelCallback = new View_ControlPanelCallback(this);
	dispatcherCallback = new View_DispatcherCallback(this);

	_jump = _zoomIn = _zoomOut = _scrollLeft = _scrollRight = _unknown = 0;
	_modeRefresh = false;

	// Init default filter
	_filter = initFilter;
	if (_filter.xLow > _filter.xHigh) {
	  Coord tmp = _filter.xLow;
	  _filter.xLow = _filter.xHigh;
	  _filter.xHigh = tmp;
	}
	if (_filter.yLow > _filter.yHigh) {
	  Coord tmp = _filter.yLow;
	  _filter.yLow = _filter.yHigh;
	  _filter.yHigh = tmp;
	}

	_filterChanged = true;
	_hasTimestamp = true;
	_timeStamp = TimeStamp::NextTimeStamp();

	_hasExposure = false;	// No exposure rectangle yet
	_querySent = false;		// TRUE if query has been sent

	_label.occupyTop = false;
	_label.extent = 12;
	_label.name = 0;

	_cursors = new DeviseCursorList;
	DOASSERT(_cursors, "Out of memory");

	_filterQueue = new FilterQueue();
	ReportViewCreated();

	int		flushed = _filterQueue->Enqueue(initFilter);

	_filterChangeCmds = NULL;
	ReportFilterChanged(initFilter, flushed);
	_selected = false; 

	_view_locks = 0;

	_hasLastFilter = false;
	_updateTransform = true;
	_updateNumDim = false;
	_refresh = true;

	_pixmap = NULL;

	_cursorsOn = false;
	_numDimensions = 2;
	_solid3D = 2;
	_useJmol = false;

	_xyZoom = true;
	_dispDataValues = false;
	_pileMode = false;
	_pileViewHold = true;
	_printing = false;
	_isHighlightView = false;

	_displaySymbol = true;

	_showMouseLocation = 1;

#if 0
	_filter.camera.x_ = 4.6;
	_filter.camera.y_ = 4.0;
	_filter.camera.z_ = -4.0;
	_filter.camera.fx = 0.0;
	_filter.camera.fy = 0.0;
	_filter.camera.fz = 0.0;
	_filter.camera._rho = 7.0;
	_filter.camera._phi = 1.0;
	_filter.camera._theta = 0.9;
	_filter.camera._dvs = 250;
	_filter.camera._twist_angle = deg_rad(0.0);
	_filter.camera._perspective = 1;
	_filter.camera.flag = 0;
	_filter.camera.fix_focus = 1;
	_filter.camera.spherical_coord = 1;
	_filter.camera.H = 0;
	_filter.camera.V = 0;
#endif
	_filter.camera.view_dir = NegZ;
	_filter.camera.pan_right = 0.0;
	_filter.camera.pan_up = 0.0;

	_autoUpdate = false;

    _viewHelp = NULL;

	_viewZ = -1.0; // invalid -- needs to be set later

	SetDisabledActions(false, false, false, false);
	_excludeFromDrillDown = false;

	_refreshPending = false;

	_isChildView = false;

	_viewList->Insert(this);
	ControlPanel::Instance()->InsertCallback(controlPanelCallback);
	_dispatcherID = Dispatcher::Current()->Register(dispatcherCallback, 10,
													GoState);
	DepMgr::Current()->RegisterEvent(dispatcherCallback,
									 DepMgr::EventViewCreated);
	_refreshPending = true;
	Scheduler::Current()->RequestCallback(_dispatcherID);

	DeviseHistory::GetDefaultHistory()->ClearAll();
	_3dValid = false;

	_queryCount = 0;

	_xAxisLinkMultFact = 1.0;
	_yAxisLinkMultFact = 1.0;

	_viewSymSaveX = false;
	_viewSymSaveY = false;
}

View::~View(void)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
	printf("View::~View(%s, this = %p)\n", GetName(), this);
#endif

	_inDestructor = true;

	_viewList->Delete(this);
	Dispatcher::Current()->Unregister(dispatcherCallback);

	DOASSERT(!_querySent, "Query still active");

	FreeString(_label.name);
	delete _cursors;
	delete _filterQueue;
	FreeString((char *)_viewHelp);

	Unmap();
	DeleteFromParent();

	// This effectively duplicates code in the ViewWin destructor, but
	// we need to do it here to fix bug 574.  (Probably the parent PileStack
	// stuff should be moved from ViewWin to View, since a window can't
	// have a parent at this point.  RKW 2000-03-15.
	if (GetParentPileStack()) {
	  GetParentPileStack()->DeleteView(this);
	}

	ControlPanel::Instance()->DeleteCallback(controlPanelCallback);

	ReportViewDestroyed();

	DeviseHistory::GetDefaultHistory()->ClearAll();

	delete controlPanelCallback;
	delete dispatcherCallback;

	FreeString(_filterChangeCmds);
	_filterChangeCmds = NULL;
}

//******************************************************************************
// Getters and Setters
//******************************************************************************

void
View::SetForeground(PColorID fgid)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  ViewWin::SetForeground(fgid);
  Refresh();
}

void
View::SetForeground(PColorID fgid, DisplayMode::Mode mode)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  ViewWin::SetForeground(fgid, mode);
  Refresh();
}

void
View::SetBackground(PColorID bgid)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  ViewWin::SetBackground(bgid);
  Refresh();
}

void
View::SetBackground(PColorID bgid, DisplayMode::Mode mode)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  ViewWin::SetBackground(bgid, mode);
  Refresh();
}

// Exists to avoid refreshing a view twice when both foreground and
// background are changed.
void    View::SetColors(PColorID fgid, PColorID bgid)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
	ViewWin::SetForeground(fgid);
	ViewWin::SetBackground(bgid);
	Refresh();
}

//******************************************************************************

/***************************************************************
Find view by name. Return NULL if not found.
****************************************************************/

View *View::FindViewByName(const char *name)
{
  DOASSERT(_viewList, "Invalid view list");
  
  int index;
  for(index = _viewList->InitIterator(); _viewList->More(index); ) {
    View *view = _viewList->Next(index);
    if (strcmp(view->GetName(), name)== 0) {
      _viewList->DoneIterator(index);
      return view;
    }
  }
  _viewList->DoneIterator(index);
  
  fprintf(stderr, "View %s not found\n", name);
  return NULL;
}

void View::SubClassMapped()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::SubClassMapped()\n", GetName());
#endif

  _updateTransform = true;

  // cause pending Expose events to be retrieved from the X server
  DeviseDisplay::DefaultDisplay()->Run();

  // in batch mode, force Run() method to be called so that
  // (first) query gets properly started up
  DepMgr::Current()->RegisterEvent(dispatcherCallback,
								   DepMgr::EventViewSubclassMapped);
  Refresh(true);

#if 0
  UpdateViewTable();
#endif
}
	
void View::SubClassUnmapped()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::SubClassUnmapped()\n", GetName());
#endif

  AbortQuery();
  CleanUpViewSyms();
}

void View::SetVisualFilterCommand(const VisualFilter &filter,
    Boolean registerEvent)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::SetVisualFilterCommand()\n", GetName());
#endif

  if (DeviseCommand::GetCmdDepth() > 1) {
    // We don't want this to be sent to collaborating deviseds, etc.
    SetVisualFilter(filter, registerEvent);

  } else {
    // Propagate to other deviseds if we're in group mode.

    ArgList args(6);
    args.AddArg("setFilter");
    args.AddArg(GetName());

    char tmpBuf[128];
    int formatted = snprintf(tmpBuf, sizeof(tmpBuf), "%.20g", filter.xLow);
    checkAndTermBuf2(tmpBuf, formatted);
    args.AddArg(tmpBuf);
    formatted = snprintf(tmpBuf, sizeof(tmpBuf), "%.20g", filter.yLow);
    checkAndTermBuf2(tmpBuf, formatted);
    args.AddArg(tmpBuf);
    formatted = snprintf(tmpBuf, sizeof(tmpBuf), "%.20g", filter.xHigh);
    checkAndTermBuf2(tmpBuf, formatted);
    args.AddArg(tmpBuf);
    formatted = snprintf(tmpBuf, sizeof(tmpBuf), "%.20g", filter.yHigh);
    checkAndTermBuf2(tmpBuf, formatted);
    args.AddArg(tmpBuf);

    CmdContainer::GenerateCommand(args.GetCount(), args.GetArgs());
  }
}

void View::SetVisualFilter(const VisualFilter &filter, Boolean registerEvent)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");

  VisualFilter newFilter = filter;

#if defined(DEBUG)
  printf("View(%s)::SetVisualFilter()\n", GetName());
  printf("  Old filter: (%g, %g), (%g, %g) %d\n", _filter.xLow, _filter.yLow,
      _filter.xHigh, _filter.yHigh, _filter.flag);
  printf("  New filter: (%g, %g), (%g, %g) %d\n", newFilter.xLow,
      newFilter.yLow, newFilter.xHigh, newFilter.yHigh, newFilter.flag);
#endif
#if defined(DEBUG_LOG)
  {
    char logBuf[1024];
    int formatted = snprintf(logBuf, sizeof(logBuf),
        "View(%s)::SetVisualFilter()\n"
        "  Old filter: (%g, %g), (%g, %g) %d\n"
        "  New filter: (%g, %g), (%g, %g) %d\n",
        GetName(), _filter.xLow, _filter.yLow, _filter.xHigh, _filter.yHigh,
	_filter.flag, newFilter.xLow, newFilter.yLow, newFilter.xHigh,
	newFilter.yHigh, newFilter.flag);
    checkAndTermBuf2(logBuf, formatted);
    DebugLog::DefaultLog()->Message(DebugLog::LevelInfo2, logBuf);
  }
#endif

  /* Just in case record links didn't get re-enabled after printing. */
  RecordLink::EnableUpdates();

  // check the new filter for safety & sanity
  if (is_safe(newFilter.xLow) && is_safe(newFilter.xHigh) &&
      is_safe(newFilter.yLow) && is_safe(newFilter.yHigh)) {

    if (newFilter.xLow >= newFilter.xHigh) {
#if defined(DEBUG)
      printf("Using old filter X values because new ones are bad\n");
#endif
	  newFilter.xLow = _filter.xLow;
	  newFilter.xHigh = _filter.xHigh;
	}

    if (newFilter.yLow >= newFilter.yHigh) {
#if defined(DEBUG)
      printf("Using old filter Y values because new ones are bad\n");
#endif
	  newFilter.yLow = _filter.yLow;
	  newFilter.yHigh = _filter.yHigh;
	}

    /* ignore new filter if same as current one */
    if (!(_filter == newFilter)) {

#if defined(DEBUG)
      printf("View %s filter changed\n", GetName());
#endif

      //TEMP -- what is this stuff for? wenger 2003-08-01.
      if (newFilter.xLow > _filter.xHigh || newFilter.xHigh < _filter.xLow) {
	_jump++;
      } else if (newFilter.xLow < _filter.xLow &&
	      newFilter.xHigh > _filter.xHigh) {
	_zoomOut++;
      } else if (newFilter.xLow > _filter.xLow &&
	      newFilter.xHigh < _filter.xHigh) {
	_zoomIn++;
      } else if (newFilter.xLow < _filter.xLow &&
	      newFilter.xHigh < _filter.xHigh) {
	_scrollLeft++;
      } else if (newFilter.xLow > _filter.xLow &&
	      newFilter.xHigh > _filter.xHigh) {
	_scrollRight++;
      } else {
	_unknown++;
      }
      
      if (registerEvent) DepMgr::Current()->RegisterEvent(dispatcherCallback,
													DepMgr::EventViewFilterCh);
      ReportFilterAboutToChange();

      _filterChanged = true;
      if (!_hasTimestamp) {
	_timeStamp = TimeStamp::NextTimeStamp();
	_hasTimestamp = true;
      }
      _updateTransform = true;
      _filter = newFilter;

      int flushed = _filterQueue->Enqueue(newFilter);
	  // Note: it is VERY important that we call ReportFilterChanged with
	  // _filter, not newFilter (this fixes bug 818).  The reason is that
	  // ReportFilterChanged calls DeviseCursor()::SatisfyConstraints(),
	  // which may call SetVisualFilter with a new filter.  If we call
	  // ReportFilterChanged with newFilter, the pre-cursor-constraints filter
	  // gets reported *after* the post-cursor-constraints filter, and
	  // therefore becomes the value for any links on this view.
	  // RKW 2002-08-23.
      ReportFilterChanged(_filter, flushed);
      
	  Refresh();
    }
  } else {
#if defined(DEBUG)
    printf("  Bad filter: (%g, %g), (%g, %g) %d ignored\n", newFilter.xLow,
        newFilter.yLow, newFilter.xHigh, newFilter.yHigh, newFilter.flag);
#endif
  }

#if defined(DEBUG)
  printf("View(%s)::SetVisualFilter() ", GetName());
  printf(" final filter: (%g, %g), (%g, %g) %d\n", _filter.xLow, _filter.yLow,
      _filter.xHigh, _filter.yHigh, _filter.flag);
#endif
#if defined(DEBUG)
  _filterQueue->Print(stdout);
#endif
}

void View::GetVisualFilter(VisualFilter &filter)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  filter = _filter;
}

VisualFilter *View::GetVisualFilter()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  return &_filter;
}

void View::Mark(int index, Boolean marked)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  _filterQueue->Mark(index, marked);
}

Boolean View::CheckCursorOp(int x, int y)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::CheckCursorOp()\n", GetName());
#endif

  // view has no cursors, so we can't move them either
  if (!_cursors->Size()) {
#if defined(DEBUG)
    printf("  view has no cursors\n");
#endif
    return false;
  }

  // can only move cursors in 2D views
  if (_numDimensions != 2) {
#if defined(DEBUG)
    printf("  view is not 2D\n");
#endif
    return false;
  }

  // if view is not selected, no cursor movement is induced;
  // mouse click is intended for selecting the view as current;
  // the next mouse click in this view will move the cursor
  if (IsInPileMode()) {
    if (!GetParentPileStack()->ViewIsSelected()) {
#if defined(DEBUG)
      printf("  pile is not selected\n");
#endif
      return false;
    }
  } else {
    if (!_selected) {
#if defined(DEBUG)
      printf("  view is not selected\n");
#endif
      return false;
    }
  }

  if (GetCursorMoveDisabled()) {
    printf("Cursor moving disabled in view <%s>\n", GetName());
    return false;
  }

#if defined(DEBUG)
  printf("  moving cursor\n");
#endif

  /* change the X and Y coordinates of the cursor */
  // Why the heck do we do this?  Why not just move the center of the
  // cursor to where the mouse click happened?  RKW 1998-09-25.
  Coord worldXLow, worldYLow, worldXHigh, worldYHigh;
  FindWorld(x, y, x + 1, y - 1, worldXLow, worldYLow, worldXHigh, worldYHigh);

  int index = _cursors->InitIterator();
  while (_cursors->More(index)) {
    DeviseCursor *cursor = _cursors->Next(index);
    DOASSERT(cursor, "Invalid cursor");
    cursor->MoveSource((worldXHigh + worldXLow) / 2.0,
		       (worldYHigh + worldYLow) / 2.0);
  }
  _cursors->DoneIterator(index);

  return true;
}

/* set dimensionality */

void View::SetNumDimensions(int d, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (d != 2 && d != 3) {
    fprintf(stderr, "View::SetNumDimensions %d invalid\n", d);
    return;
  }

  if (_pileMode && notifyPile) {
    GetParentPileStack()->SetNumDimensions(d);
  } else {
	if (d != _numDimensions) {
       if (d == 3) {
           printf("Note: view %s is a 3D view\n", GetName());
       }
      _numDimensions = d;
      _updateNumDim = true;

      DepMgr::Current()->RegisterEvent(dispatcherCallback,
	      DepMgr::EventViewDimensionsCh);
      Refresh();
	}
  }
}

/* set solid or wideframe 3D objects */

void View::SetSolid3D(int solid)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (solid == _solid3D)
    return;

  _solid3D = solid;

  DepMgr::Current()->RegisterEvent(dispatcherCallback, DepMgr::EventViewSolidCh);
  Refresh();
}

/* set flag for data value display */

void View::SetDisplayDataValues(Boolean disp)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (disp == _dispDataValues)
    return;

  _dispDataValues = disp;

  DepMgr::Current()->RegisterEvent(dispatcherCallback, DepMgr::EventViewDataDisplayCh);
  Refresh();
}

/* set pile mode flag */

void View::SetPileMode(Boolean mode)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::SetPileMode(%d)\n", GetName(), mode);
#endif

  //
  // This is kind of a kludgey fix for the following problem: when a view
  // gets destroyed, it deletes itself from its parent window, which deletes
  // it from the PileStack object, which may call SetPileMode()...
  // RKW 1999-02-10.
  //
  if (_inDestructor) {
    return;
  }

  if (mode == _pileMode) {
    return;
  }

  _pileMode = mode;
  _pileViewHold = true;

  if (mode) {
	if (GetParentPileStack()->GetFirstView() && GetWindowRep()) {
      GetWindowRep()->SetOutput(
	      GetParentPileStack()->GetFirstView()->GetWindowRep());
	}
  } else {
    if (GetWindowRep()) {
	  GetWindowRep()->ResetOutput();
    }
  }

  /* Just in case record links didn't get re-enabled after printing. */
  RecordLink::EnableUpdates();

  DepMgr::Current()->RegisterEvent(dispatcherCallback, DepMgr::EventViewPileCh);
  Refresh();
}

void View::Flip(Boolean doCommand)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::Flip(%d)\n", GetName(), doCommand);
#endif

  // Find the right PileStack to flip:
  // - If this is a "regular" piled view, flip its parent PileStack.
  // - If this is a piled child of piled parents, flip the parent view's
  //   parent PileStack.
  // - If this is a piled child of unpiled parents or a single parent,
  //   flip this view's parent PileStack.
  // - If this is an unpiled child of piled parents, do nothing.
  PileStack *ps = NULL; // PileStack to flip
  ViewWin *tmpView = this;
  Boolean done = false;
  while (tmpView && !done) {
    PileStack *tmpPs = tmpView->GetParentPileStack();
    if (tmpPs && tmpPs->GetState() != PileStack::PSNormal) {
	  ps = tmpPs;
	  tmpView = tmpView->GetParent();
	} else {
	  done = true;
	}
  }

  if (ps) {
    if (doCommand) {
      ps->FlipCommand();
    } else {
      ps->Flip();
    }
  }
}

/* set view geometry */
// Note: I'm not sure what this really does that MoveResize() doesn't do.
void View::SetGeometry(int x, int y, unsigned wd, unsigned ht) 
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
    printf("View(%s)::SetGeometry(%d, %d, %d, %d)\n", GetName(), x, y, wd, ht);
#endif
#if defined(DEBUG_LOG)
    char logBuf[1024];
    int formatted = snprintf(logBuf, sizeof(logBuf),
      "View(%s)::SetGeometry(%d, %d, %d, %d)\n", GetName(),
      x, y, wd, ht);
    checkAndTermBuf2(logBuf, formatted);
    DebugLog::DefaultLog()->Message(DebugLog::LevelInfo2, logBuf);
#endif

  /*ViewWin::SetGeometry(x,y,wd,ht); */
  ViewWin::MoveResize(x,y,wd,ht);
  _updateTransform = true;
#if defined(DEBUG)
  printf("view: setting geometry done....%d %d %u %u\n", x , y, wd, ht);
#endif

  /* Just in case record links didn't get re-enabled after printing. */
  RecordLink::EnableUpdates();

  DepMgr::Current()->RegisterEvent(dispatcherCallback, DepMgr::EventViewGeomCh);
  Refresh();

#if defined(DEBUG_LOG)
    formatted = snprintf(logBuf, sizeof(logBuf),
      "  Done with View::SetGeometry()\n");
    checkAndTermBuf2(logBuf, formatted);
    DebugLog::DefaultLog()->Message(DebugLog::LevelInfo2, logBuf);
#endif
}

/********************************************************************
Get the area for displaying the label (title).  Note that Y is measured up
from the bottom.

              width
          +-----------+
          |           | height
     (x,y)+--+--------+
          |  |        |
          |  |        |
          |  |        |
          +--+--------+
          |           | 
          |           |
          +-----------+
********************************************************************/

void View::GetLabelArea(int &areaX, int &areaY, int &areaW, int &areaH)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");

  int winX, winY;
  unsigned int winW, winH;
  GeometryWithHighlight(winX, winY, winW, winH);

  areaX = winX;
  areaW = winW;

  areaH = GetLabelHeight();
  areaY = winY + winH - areaH;

#if defined(DEBUG)
  printf("View::GetLabelArea %s %d %d %d %d\n", GetName(), areaX, areaY,
      areaW, areaH);
#endif
}

/********************************************************************
Get area for displaying X axis. Note that Y is measured up
from the bottom.  The axis area includes the row of pixels used to
draw the actual axis line.

          +--+--------+
          |  |        |
          |  |        |
          |  |        |
     (x,y)+--+--------+
          |  ^        | <- height
          |  startX   |
          +-----------+
                ^
                |
	    	 width
************************************************************************/

void View::GetXAxisArea(int &areaX, int &areaY, int &areaW, int &areaH,
			int &startX)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  DOASSERT(_numDimensions == 2, "Invalid number of dimensions");

  int winX, winY;
  unsigned int winW, winH;
  GeometryWithHighlight(winX, winY, winW, winH);

  areaX = winX;
  areaW = winW;

  areaH = GetXAxisHeight();
  areaY = winY + areaH - 1;

  startX = winX + GetYAxisWidth();

#if defined(DEBUG)
  printf("View::GetXAxisArea(%s): %d %d %d %d %d\n", GetName(), areaX, areaY,
      areaW, areaH, startX);
#endif
}

/********************************************************************
Get area for displaying Y axis. Note that Y is measured up
from the bottom.  The axis area includes the row of pixels used to
draw the actual axis line.

          width
          +--+--------+
          |  |        |
    height|  |        |
          |  |        |
     (x,y)+--+--------+
          |           | 
          |           |
          +-----------+
********************************************************************/

void View::GetYAxisArea(int &areaX, int &areaY, int &areaW, int &areaH)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  DOASSERT(_numDimensions == 2, "Invalid number of dimensions");

  int winX, winY;
  unsigned int winW, winH;
  GeometryWithHighlight(winX, winY, winW, winH);

  areaX = winX;
  areaW = GetYAxisWidth();

  areaY = winY + GetXAxisHeight();
  areaH = winH - GetLabelHeight() - GetXAxisHeight();

#if defined(DEBUG)
  printf("View::GetYAxisArea(%s): %d %d %d %d\n", GetName(), areaX, areaY,
      areaW, areaH);
#endif
}

/********************************************************************
Get the area for displaying the data.  Note that Y is measured up
from the bottom.

                width
          +--+--------+
          |  |        |
    height|  |        |
          |  |        |
          +--+--------+
          | (x,y)     | 
          |           |
          +-----------+
********************************************************************/

// Note: Y here is up from the bottom, not down from the top!!  RKW 1999-03-15.
void View::GetDataArea(int &areaX, int &areaY, int &areaW,int &areaH)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");

  int winX, winY;
  unsigned int winW, winH;
  GeometryWithHighlight(winX, winY, winW, winH);

  areaX = winX + GetYAxisWidth();
  areaW = winW - GetYAxisWidth();

  areaY = winY + GetXAxisHeight();
  areaH = winH - GetLabelHeight() - GetXAxisHeight();

#if defined(DEBUG)
  printf("  View %s data area is %d %d; %d %d\n", GetName(), areaX, areaY,
      areaW, areaH);
#endif
}

void View::DrawAxesLabel(WindowRep *win, int x, int y, int w, int h)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View::DrawAxesLabel %s %d %d %d %d\n", GetName(), x, y, w, h);
#endif

  int winX, winY; 
  unsigned int winW, winH;
  Geometry(winX, winY, winW, winH);
  
  /* Make it possible to update the label areas */
  win->PushClip(winX, winY, winW - 1, winH - 1);

  /* Fill the whole background so we don't have the missing "stripes"
   * in PostScript.  Note that we _must_ have an identity matrix for
   * the window transform for this to work. */
  if (FILL_WHOLE_BACKGROUND || _winReps.IsFileOutput()) {
    win->SetForeground(GetBackground());
    win->ClearBackground((Coord) winX, (Coord) winY, (Coord) winW, (Coord) winH);
  }

  DrawLabel();

#if !FILL_WHOLE_BACKGROUND
  /* Clear highlight area */
  win->SetForeground(GetBackground());
  DrawHighlight();
#endif

  if (_numDimensions == 2) {
    int axisX, axisY, axisWidth, axisHeight, startX;
    if (_xAxis.IsInUse()) {
#if !FILL_WHOLE_BACKGROUND || COLOR_AREAS
      GetXAxisArea(axisX, axisY, axisWidth, axisHeight, startX);
      win->SetForeground(GetBackground());
      win->SetPattern(Pattern0);
#  if COLOR_AREAS
      win->SetForeground((PColorID)20);
      win->SetPattern((Pattern)-2);
#  endif
      win->SetLineWidth(0);
      // Note: -1s are here because WindowRep (at least, XWindowRep), defines
      // width and height differently than View does.  RKW 2003-01-06.
      win->ClearBackground(axisX, axisY - axisHeight + 1, axisWidth - 1,
          axisHeight - 1);
#  if COLOR_AREAS
      win->SetForeground(GetBackground());
      win->SetPattern(Pattern0);
#  endif
#endif
      _xAxis.DrawAxis(win, x, y, w, h);
    }
    if (_yAxis.IsInUse()) {
#if !FILL_WHOLE_BACKGROUND || COLOR_AREAS
      GetYAxisArea(axisX, axisY, axisWidth, axisHeight);
      win->SetForeground(GetBackground());
      win->SetPattern(Pattern0);
#  if COLOR_AREAS
      win->SetForeground((PColorID)33);
      win->SetPattern((Pattern)-21);
#  endif
      win->SetLineWidth(0);
      // Note: -1s are here because WindowRep (at least, XWindowRep), defines
      // width and height differently than View does.  RKW 2003-01-06.
      win->ClearBackground(axisX, axisY, axisWidth - 1, axisHeight - 1);
#  if COLOR_AREAS
      win->SetForeground(GetBackground());
      win->SetPattern(Pattern0);
#  endif
#endif
      _yAxis.DrawAxis(win, x, y, w, h);
    }
  }

  win->PopClip();
}

void View::DrawLabel()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  WindowRep*	win = GetWindowRep();
  win->SetGifDirty(true);
	
  win->PushTop();
  win->MakeIdentity();
  
  win->SetNormalFont();
  _titleFont.SetWinFont(win);

  if (_label.occupyTop) {
    /* draw label */
    int labelX, labelY, labelWidth, labelHeight;
    GetLabelArea(labelX, labelY, labelWidth, labelHeight);
    win->SetPattern(Pattern0);
    win->SetLineWidth(0);

    win->SetForeground(GetBackground());
#if COLOR_AREAS
    win->SetForeground((PColorID)10);
    win->SetPattern((Pattern)-4);
#endif
    // Note: -1s are here because WindowRep (at least, XWindowRep), defines
    // width and height differently than View does.  RKW 2003-01-06.
    win->ClearBackground(labelX, labelY, labelWidth - 1, labelHeight - 1);
#if COLOR_AREAS
    win->SetForeground(GetBackground());
    win->SetPattern(Pattern0);
#endif

    if (!Session::GetIsJsSession()) {
      win->SetForeground(GetForeground());

      win->AbsoluteText(_label.name, labelX, labelY, labelWidth - 1,
		        labelHeight - 1, WindowRep::AlignCenter, true);
    }
  }

  win->PopTransform();
}

/* Find world coord given screen coord */

void View::FindWorld(int sx1,int sy1, int sx2, int sy2,
		     Coord &xLow, Coord &yLow, Coord &xHigh, Coord &yHigh)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View::FindWorld(%d, %d, %d, %d)\n", sx1, sy1, sx2, sy2);
#endif

  Coord x1, x2, y1, y2;
  WindowRep *winRep = GetWindowRep();
  winRep->InverseTransform(sx1, sy1, x1, y1);
  winRep->InverseTransform(sx2, sy2, x2, y2);
  xLow = MIN(x1, x2);
  xHigh = MAX(x1, x2);
  yLow = MIN(y1, y2);
  yHigh = MAX(y1, y2);
}

/* Calculate the transformation matrix used to translate from
   world to screen coordinates */

void View::CalcTransform2(WindowRep *winRep)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  winRep->MakeIdentity();

  int dataX, dataY, dataWidth, dataHeight;
  GetDataArea(dataX, dataY, dataWidth, dataHeight);

#if defined(DEBUG)
  printf("transform data: %d,%d,%d,%d\n", dataX, dataY,
	 dataWidth, dataHeight);
#endif
  /* Notice everything is reversed for OpenGL convention of
   Current matrix=old matrix * transformation matrix */

  /* Translate to beginning of data area. */
  winRep->Translate(dataX, dataY);

  /* scale to size of the screen */

  // IMPORTANT NOTE!!!!!!!!  The setting for the WindowRep transform here
  // assumes that the lowest X and Y filter values correspond to the *center*
  // of the lower left pixel of the data area, and the highest X and Y filter
  // values correspond to the *center* of the upper right pixel of the
  // data area.

  // Note: we need dataWidth-1 and dataHeight-1 here because, for example,
  // if the data area were 2 pixels wide, there is only *one* pixel
  // *difference* between the two pixels.  (Putting in the -1s fixes
  // bug 855.)
  winRep->Scale((Coord)(dataWidth-1) / (_filter.xHigh - _filter.xLow),
		  (Coord)(dataHeight-1) / (_filter.yHigh - _filter.yLow));

  /* translate to 0, 0 */
  winRep->Translate(-_filter.xLow, -_filter.yLow);

}

void View::CalcTransform3(WindowRep *winRep)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  winRep->MakeIdentity();

  int dataX, dataY, dataWidth, dataHeight;
  GetDataArea(dataX, dataY, dataWidth, dataHeight);

#if defined(DEBUG)
  printf("transform data: %d,%d,%d,%d\n", dataX, dataY,
	 dataWidth, dataHeight);
#endif
  // need to figure out the correct positioning of camera later...

  winRep->SetViewCamera(_filter.camera);
}

/* For query processing */

void View::ReportQueryDone(int bytes, Boolean aborted)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::ReportQueryDone(%d, %d)\n", _name, bytes, aborted);
#endif
#if defined(DEBUG_MEM)
  printf("%s: %d; end of data seg = %p\n", __FILE__, __LINE__, sbrk(0));
#endif

   if (!aborted) {
       _queryCount++;
#if defined(DEBUG)
       printf("  %d non-aborted queries have been run by view %s\n",
	     _queryCount, GetName());
#endif
   }

  if (!aborted) {
   	RestoreCursorState();
  }

  _refreshPending = false;

  _bytes = bytes;
  _querySent = false;
  _hasLastFilter = false;

  WindowRep *win = GetWindowRep();
  win->SetGifDirty(true);

  // Show the view name, if necessary.  Note that the view name is drawn
  // *inside* the data area, because it's considered a temporary measure
  // and not part of a "finished" presentation (titles should be used for
  // that, since the view names are often pretty ugly).
  if (_showNames) {
    win->PushTop();
    win->MakeIdentity();
  
    win->SetNormalFont();
    _titleFont.SetWinFont(win);
    win->SetForeground(GetForeground());

	ViewWin *parent = GetParent();
	if (parent->GetParent() == NULL) {
	  // This is a window, not a view.
	  parent = NULL;
	}
    int xloc, yloc, width, height;
    GetDataArea(xloc, yloc, width, height);
    char buf[1024];
    int formatted = snprintf(buf, sizeof(buf), "<%s%s%s>",
	    parent ? parent->GetName() : "", parent ? ":" : "", GetName());
	checkAndTermBuf2(buf, formatted);

    // Show the names of all views in piled mode, but keep them from
    // overlapping.
    if (_pileMode) {
      PileStack *ps = GetParentPileStack();
      int index = ps->InitIterator();
      while (ps->More(index)) {
	ViewWin *sibling = ps->Next(index);
	if (this == sibling) {
	  break;
	} else {
	  yloc -= 15; // Warning: constant depends on font size.
	}
      }
      ps->DoneIterator(index);
    }

    win->AbsoluteText(buf, xloc, yloc, width, height,
	  WindowRep::AlignNorth, true);

    win->PopTransform();
  }

  /* if view is on top of a pile, it has to wake the other views
     up and ask them to refresh; the bottom views might not have
     received an Exposure or ConfigurationNotify event requesting
     them to redraw; also, first view erases window and draws
     axes and other decorations, so it has to go first */

  /* Rather than the top view waking up all other views, now the top
   * view only wakes up the next view, and then when that view finishes
   * it wakes up the one after it, etc.  This is done to be sure that the
   * various views are drawn in the correct order.  RKW 1/7/97. */

  /* Note: when we're printing, we shouldn't really have to refresh the
   * next piled view here, but if we don't, things don't work right.
   * RKW June 25, 1997. */

  //TEMP -- move this to PileStack class?
  Boolean lastInPile = true;
  if (_pileMode) {
    if (!aborted) {
      ViewWin *parent = GetParent();
      DOASSERT(parent, "View has no parent");

      int index = GetParentPileStack()->InitIterator();

      /* Skip over all views in order up to and including this view. */
      while (GetParentPileStack()->More(index) &&
	      (GetParentPileStack()->Next(index) != this)) {}

      /* Now refresh the next view. */
      if (GetParentPileStack()->More(index)) {
        ViewWin *vw = GetParentPileStack()->Next(index);

        /* FindViewByName is a type-safe way to convert from a ViewWin to
         * a View, which is necessary to call Refresh(). */
        View *view = FindViewByName(vw->GetName());
        DOASSERT(view, "Cannot find view");
        DOASSERT(vw == view, "ViewWin != View");
#if defined(DEBUG)
        printf("View %s refreshes view %s\n", GetName(), view->GetName());
#endif
        view->_pileViewHold = false;
        view->Refresh(false);
        lastInPile = false;
      }

      GetParentPileStack()->DoneIterator(index);
    }
  }

  if (win->ETk_WindowCount() > 0)
  {
      if (!aborted)
      {
	  win->ETk_Cleanup();  
      }
  }
  
  if (_numDimensions == 3)
    Draw3DAxis();

  //
  // If we're in a pile, postpone drawing cursors until all views of the pile
  // have been drawn; then draw all cursors in the pile.  (This fixes bug
  // 446.)  RKW 1999-02-22.
  if (IsInPileMode()) {
    if (lastInPile) {
	  int index = GetParentPileStack()->InitIterator();
	  while (GetParentPileStack()->More(index)) {
	    View *tmpView = (View *)GetParentPileStack()->Next(index);
		tmpView->DrawCursors();
	  }
	  GetParentPileStack()->DoneIterator(index);
	}
  } else {
    DrawCursors();
  }

  win->PopClip();
  win->Flush();

  if (_printing)
  {
    (void) PrintPSDone();
  }
  
  ControlPanel::Instance()->SetIdle();

#if defined(DEBUG)
  printf("View %s completed\n", GetName());
#endif

  /* Report to interested parties that view has been recomputed */
  ReportViewRecomputed();
}

void View::UpdateTransform(WindowRep *winRep)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View::UpdateTransform %s\n", GetName());
#endif

  winRep->ClearTransformStack();

  if (_numDimensions == 2) {
     CalcTransform2(winRep);
  } else {
     CalcTransform3(winRep);
     //winRep->MakeIdentity();
  }
}

/* Get label parameters */

void View::GetLabelParam(Boolean &occupyTop, int &extent, const char *&name)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  occupyTop = _label.occupyTop;
  extent = _label.extent;
  name = _label.name;
}

/* Set label parameters */

void View::SetLabelParam(Boolean occupyTop, int extent, const char *name,
    Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (_pileMode && notifyPile) {
    GetParentPileStack()->SetLabelParam(occupyTop, extent, name);
	return;
  }

  FreeString(_label.name);

  /* CopyString() now handles NULL okay. */
  _label.name = CopyString(name);

  if (!_label.name) {
    occupyTop = false;
  }

  Boolean oldOccupyTop = _label.occupyTop;
  _label.occupyTop = occupyTop;
  _label.extent = extent;

  /* If we're just changing the label string, not whether or not we
   * have a label, we can just re-draw the label.  Otherwise, we have
   * to re-draw the whole view. */
  if (occupyTop == oldOccupyTop) {
    if (_winReps.GetWindowRep()) {
	  if (_selected) {
        // Undraw highlight.
        WindowRep *winRep = GetWindowRep();
        winRep->SetXorMode();
        DrawHighlight();
        winRep->SetCopyMode();
      }
      DrawLabel();
      _winReps.GetWindowRep()->Flush();
      _winReps.GetWindowRep()->SetGifDirty(true);
	  if (_selected) {
        // Redraw highlight.
        WindowRep *winRep = GetWindowRep();
        winRep->SetXorMode();
        DrawHighlight();
        winRep->SetCopyMode();
      }
    }
  } else {
    _updateTransform = true;

    DepMgr::Current()->RegisterEvent(dispatcherCallback, DepMgr::EventViewTitleCh);
    Refresh();
  }
}

void View::XAxisDisplayOnOff(Boolean axisOn, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::XAxisDisplayOnOff(%d)\n", GetName(), axisOn);
#endif

  if (axisOn != _xAxis.IsInUse()) {
    if (_pileMode && notifyPile) {
	  GetParentPileStack()->EnableXAxis(axisOn);
	} else {
      _xAxis.SetInUse(axisOn);
      _updateTransform = true;

      DepMgr::Current()->RegisterEvent(dispatcherCallback,
	      DepMgr::EventViewAxesCh);
      Refresh();
	}
  }
}

void View::YAxisDisplayOnOff(Boolean axisOn, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::YAxisDisplayOnOff(%d)\n", GetName(), axisOn);
#endif

  if (axisOn != _yAxis.IsInUse()) {
    if (_pileMode && notifyPile) {
	  GetParentPileStack()->EnableYAxis(axisOn);
	} else {
      _yAxis.SetInUse(axisOn);
      _updateTransform  = true;

      DepMgr::Current()->RegisterEvent(dispatcherCallback,
	      DepMgr::EventViewAxesCh);
      Refresh();
	}

  }
}

void View::XAxisTicksOnOff(Boolean ticksOn, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::XAxisTicksOnOff(%d)\n", GetName(), ticksOn);
#endif

  Boolean currentTicksOn = _xAxis.TicksEnabled();

  if (ticksOn != currentTicksOn) {
    if (_pileMode && notifyPile) {
	  GetParentPileStack()->EnableXTicks(ticksOn);
	} else {
	  _xAxis.EnableTicks(ticksOn);
      _updateTransform  = true;

      DepMgr::Current()->RegisterEvent(dispatcherCallback,
	      DepMgr::EventViewAxesCh);
      Refresh();
	}
  }
}

void View::YAxisTicksOnOff(Boolean ticksOn, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::YAxisTicksOnOff(%d)\n", GetName(), ticksOn);
#endif

  Boolean currentTicksOn = _yAxis.TicksEnabled();

  if (ticksOn != currentTicksOn) {
    if (_pileMode && notifyPile) {
	  GetParentPileStack()->EnableYTicks(ticksOn);
	} else {
	  _yAxis.EnableTicks(ticksOn);
      _updateTransform  = true;

      DepMgr::Current()->RegisterEvent(dispatcherCallback,
	      DepMgr::EventViewAxesCh);
      Refresh();
	}
  }
}

void View::SetXAxisMultFact(double factor, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::SetXAxisMultFact(%g, %d)\n", GetName(), factor,
      notifyPile);
#endif

  if (factor != _xAxis.GetMultFactor()) {
    if (_pileMode && notifyPile) {
	  GetParentPileStack()->SetXAxisMultFact(factor);
	} else {
	  _xAxis.SetMultFactor(factor);

      DepMgr::Current()->RegisterEvent(dispatcherCallback,
	      DepMgr::EventViewAxesCh);
      Refresh();
	}
  }
}

void View::SetYAxisMultFact(double factor, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::SetYAxisMultFact(%g, %d)\n", GetName(), factor,
      notifyPile);
#endif

  if (factor != _yAxis.GetMultFactor()) {
    if (_pileMode && notifyPile) {
	  GetParentPileStack()->SetYAxisMultFact(factor);
	} else {
	  _yAxis.SetMultFactor(factor);

      DepMgr::Current()->RegisterEvent(dispatcherCallback,
	      DepMgr::EventViewAxesCh);
      Refresh();
	}
  }
}

/* Find real window coords */

inline void FindRealCoord(WindowRep *winRep, Coord xlow, Coord ylow, 
			  Coord xhigh, Coord yhigh, int &txlow, int &tylow,
			  int &txhigh, int &tyhigh)
{
  Coord xl,yl, xh, yh;
  winRep->Transform(xlow, ylow, xl, yl);
  winRep->Transform(xhigh, yhigh, xh, yh);
  txlow = (int)MIN(xl, xh);
  txhigh = (int)MAX(xl, xh);
  tylow = (int)MIN(yl, yh);
  tyhigh = (int)MAX(yl,yh);
}

/* Update filter by scrolling.
Algorithm:
	If no exposure and can scroll, scroll the window. 
	Change _filterChanged into _hasExposure
Return:
	0: can not scroll.
	1: scroll was performed, and update the _exposureRect.
	2: can scroll, and no exposure left.
	true if filter was scrolled.
	false if not.
*/

View::UpdateFilterStat View::UpdateFilterWithScroll()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("UpdateFilterWithScroll: _refresh %d, _filterChanged %d, _hasExposure %d\n",
	 _refresh, _filterChanged, _hasExposure);
#endif
  
  WindowRep *winRep = GetWindowRep();
  Coord xlow, ylow, xhigh, yhigh;
  xlow = _filter.xLow;
  ylow = _filter.yLow;
  xhigh = _filter.xHigh;
  yhigh = _filter.yHigh;

  if ( /* make sure we can scroll */
      winRep->Scrollable() 
      /* and have current and last filter available */
      && _hasLastFilter && _filterChanged
      /* and we are not refreshing the window by redraw */
      && !_refresh
      /* And did not zoom */
      &&fabs((_filter.xHigh - _filter.xLow)-
	     (_lastFilter.xHigh-_lastFilter.xLow)) <= DELTA_X
      &&fabs((_filter.yHigh - _filter.yLow)-
	     (_lastFilter.yHigh-_lastFilter.yLow)) <= DELTA_Y
      /* and the two filters overlap */
      && Geom::RectRectClip(xlow, ylow, xhigh, yhigh,_lastFilter.xLow,
			    _lastFilter.yLow, _lastFilter.xHigh, _lastFilter.yHigh)
      
      /* and scrollling to the right or scroll left */
      &&(	(_lastFilter.yLow == _filter.yLow &&
		 _lastFilter.yHigh == _filter.yHigh )
	 ||	(_lastFilter.xLow == _filter.xLow &&
		 _lastFilter.xHigh == _filter.xHigh ))) {
    
    /* Find the real window coord of the overlap region */
    int fxl, fyl, fxh, fyh; /* transformed filter coord */
    int lxl, lyl, lxh, lyh; /* xformed last filter */
    int oxl, oyl, oxh, oyh; /* xformed overlap */
    FindRealCoord(winRep, _filter.xLow, _filter.yLow, 
		  _filter.xHigh, _filter.yHigh, fxl, fyl, fxh, fyh);
    FindRealCoord(winRep, _lastFilter.xLow, _lastFilter.yLow, 
		  _lastFilter.xHigh, _lastFilter.yHigh, lxl, lyl, lxh, lyh);
    FindRealCoord(winRep, xlow, ylow, xhigh, yhigh, oxl, oyl, oxh, oyh);
    int overlapWidth = oxh-oxl+1;
    int overlapHeight = oyh-oyl+1;
    
    int dataX, dataY, dataW, dataH;
    GetDataArea(dataX, dataY, dataW, dataH);

#if defined(DEBUG)
    printf("data: x:%d, y:%d, w:%d, h:%d\n", dataX, dataY, dataW, dataH);
#endif

	winRep->SetGifDirty(true);
    winRep->ScrollAbsolute(oxl, oyl, overlapWidth, overlapHeight,
			oxl-fxl+lxl, oyl-fyl+lyl);
    
    /* Find exposed region for redraw */
    if (_filter.xLow > _lastFilter.xLow) {
      /* scrolling data left */
      _exposureRect.xLow = lxh-overlapWidth;
      _exposureRect.yLow = lyl;
      _exposureRect.xHigh = lxh;
      _exposureRect.yHigh = lyh;
    }
    else if (_filter.xLow < _lastFilter.xLow) {
      /* scrolling data right */
      _exposureRect.xLow = lxl;
      _exposureRect.yLow = lyl;
      _exposureRect.xHigh = lxl+overlapWidth;
      _exposureRect.yHigh = lyh;
    }
    else if (_filter.yLow > _lastFilter.yLow) {
      /* scroll data down */
      _exposureRect.xLow = lxl;
      _exposureRect.yLow = lyl;
      _exposureRect.xHigh = lxh;
      _exposureRect.yHigh = lyl+overlapHeight;
    }
    else if (_filter.yLow < _lastFilter.yLow) {
      /* scroll up */
      _exposureRect.xLow = lxl;
      _exposureRect.yLow = lyl+overlapHeight-1;
      _exposureRect.xHigh = lxh;
      _exposureRect.yHigh = lyh;
    }
    else {
      /* new filter same as old filter. */
      return SameFilter;
    }

#if defined(DEBUG)
    printf("after scroll exposure (%d,%d),(%d,%d)\n",
	   _exposureRect.xLow, _exposureRect.yLow,
	   _exposureRect.xHigh, _exposureRect.yHigh);
#endif
    
    return Scrolled;
  }
  return NotScrolled;
}

void View::AbortQuery()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::AbortQuery()\n", _name);
#endif

  // If the View object is really anything other than a
  // ViewData or maybe ViewLens, and _querySent is true,
  // this will call a pure virtual function.

  if (_querySent) {
#if defined(DEBUG)
    printf("View %s aborting...\n", GetName());
#endif
    DerivedAbortQuery();
    ReportQueryDone(0, true);
  }
}

void View::Refresh(Boolean refreshPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::Refresh(%d)\n", GetName(), refreshPile);
  printf("  _pileMode = %d, GetParentPileStack() = %p\n", _pileMode,
      GetParentPileStack());
#endif

  if (_inDestructor) {
    return;
  }

  // Part of kludgey fix for bug 527.  RKW 1999-10-30.
  AbortQuery();//TEMP

  if (refreshPile && _pileMode && GetParentPileStack()) {
    GetParentPileStack()->Refresh(this);
  } else {
    _doneRefresh = false;
    _refresh = true;
	_refreshPending = true;
    Scheduler::Current()->RequestCallback(_dispatcherID);
  }
}

void
View::CancelRefresh()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::CancelRefresh()\n", GetName());
#endif
  _refreshPending = false;
  Scheduler::Current()->CancelCallback(_dispatcherID);
}

void View::ReportViewCreated()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (!_viewCallbackList)
    return;
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling ViewCreated callback %p for view %p\n",
	   callBack, this);
#endif
    callBack->ViewCreated(this);
  }
  _viewCallbackList->DoneIterator(index);

}

void View::ReportViewRecomputed()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View::ReportViewRecomputed()\n");
#endif
  if (!_viewCallbackList)
    return;
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
#if defined(DEBUG)
    printf("View = %p, ViewCallbacklist = %p\n", this, _viewCallbackList);
#endif
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling ViewRecomputed callback %p for view %p (%s)\n",
	   callBack, this, GetName());
#endif
    callBack->ViewRecomputed(this);
  }
  _viewCallbackList->DoneIterator(index);
}

void View::ReportViewDestroyed()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (!_viewCallbackList)
    return;
  
  int index;
  _doneRefresh = false;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling ViewDestroyed callback %p for view %p\n",
	   callBack, this);
#endif
    callBack->ViewDestroyed(this);
  }
  _viewCallbackList->DoneIterator(index);
  
}

void View::ReportFilterAboutToChange()
{
#if defined(DEBUG)
  printf("View(%s)::ReportFilterAboutToChange()\n", GetName());
#endif

  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (!_viewCallbackList)
    return;
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling FilterAboutToChange callback %p for view %p\n",
	   callBack, this);
#endif
    callBack->FilterAboutToChange(this);
  }
  _viewCallbackList->DoneIterator(index);
}

void View::ReportFilterChanged(const VisualFilter &filter, int flushed)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::ReportFilterChanged()\n", GetName());
#endif

  if (_filterChangeCmds) {
    RunFilterChangeCmds();
  }

  if (!_viewCallbackList) {
    return;
  }
  
  int index;
  for(index = _viewCallbackList->InitIterator(); 
      _viewCallbackList->More(index);) {
    ViewCallback *callBack = _viewCallbackList->Next(index);
#if defined(DEBUG)
    printf("Calling FilterChanged callback %p for view %p\n",
	   callBack, this);
#endif
    callBack->FilterChanged(this, filter, flushed);
  }
  _viewCallbackList->DoneIterator(index);
}

void
View::RunFilterChangeCmds()
{
#if defined(DEBUG)
  printf("View(%s)::RunFilterChangeCmds()\n", GetName());
  printf("  Cmds: <%s>\n", _filterChangeCmds ? _filterChangeCmds : "");
#endif

  if (!_filterChangeCmds) {
    return;
  }

  // Parse the overall command string into individual commands, and
  // execute each one.
  // Note: do we need a capability to escape '{' and '}'?
  char *tmpCmd = CopyString(_filterChangeCmds);
  int braceCount = 0;
  char *cmdStart = NULL;
  char *current = tmpCmd;
  while(*current != '\0') {
	if (*current == '{') {
	  if (braceCount == 0) {
	    cmdStart = current + 1;
	  }
	  braceCount++;
	} else if (*current == '}') {
	  braceCount--;
	  if (braceCount == 0) {
	    if (!cmdStart) {
		  reportErrNosys("Error: } w/o {"/*TEMP*/);
	      break;
	    } else {
	  	  *current = '\0';
		  printf("Running command <%s>\n", cmdStart);//TEMP
		  //TEMP -- actually parse and run the command here
		  cmdStart = NULL;
	    }
	  }
	}
    current++;
  }

  if (braceCount != 0) {
    reportErrNosys("Error: unterminated command"/*TEMP*/);
  }

  FreeString(tmpCmd);
}

void View::InsertViewCallback(ViewCallback *callBack)
{
  if (!_viewCallbackList) {
    _viewCallbackList = new ViewCallbackList;
  }
    
  DOASSERT(_viewCallbackList, "Invalid view callback list");

#if defined(DEBUG)
  printf("Inserting %p to view callback list\n", callBack);
#endif

  _viewCallbackList->Append(callBack);
}

void View::DeleteViewCallback(ViewCallback *callBack)
{
  DOASSERT(_viewCallbackList, "Invalid view callback list");
#if defined(DEBUG)
  printf("Removing %p from view callback list\n", callBack);
#endif

  _viewCallbackList->Delete(callBack);
}

void View::Iconify(Boolean iconified)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (iconified) {
    AbortQuery();
  }

  DepMgr::Current()->RegisterEvent(dispatcherCallback, DepMgr::EventViewIconify);
  Refresh();
}

void View::DoSelect(Boolean flag)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::DoSelect(%d)\n", GetName(), flag);
#endif

  // I'm not sure why this code was here, but I don't think we need it
  // anymore -- removing it fixes bug 914.  wenger 2005-02-16.
#if 0
  if (_numDimensions == 3)
    return;
#endif
  if (_selected == flag)
    return;

#if defined(DEBUG)
  if (flag) {
    printf("Drawing highlight for view <%s>\n", GetName());
  } else {
    printf("Erasing highlight for view <%s>\n", GetName());
  }
#endif

  _selected = flag;

  WindowRep *winRep = GetWindowRep();
  if (!winRep) {
//TEMP -- do we want to set the GifDirty flag here???
    /* View is unmapped but is still selected, and we're told by the
       client to unhighlight the view. This may occur when a window
       is destroyed by the window manager and all views are unmapped,
       but if a view among those is selected, it will stay selected. */
    return;
  }

  winRep->SetXorMode();
  DrawHighlight();
  winRep->SetCopyMode();
}

void View::DrawHighlight()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::DrawHighlight()\n", GetName());
#endif

  if (!Mapped())
    return;

  WindowRep *winRep = GetWindowRep();
//TEMP -- do we want to set the GifDirty flag here???

  int x,y;
  unsigned int w,h;

  Geometry(x, y, w, h);

  /* Make sure we can draw the whole highlight. */
  winRep->PushTop();
  winRep->MakeIdentity();
  winRep->PushClip((Coord) x, (Coord) y, (Coord) w - 1, (Coord) h - 1);
  
  winRep->AbsoluteLine(x, y, w - 1, x, highlightWidth);
  winRep->AbsoluteLine(x + w - 1, y, x + w - 1, y + h - 1, highlightWidth);
  winRep->AbsoluteLine(x + w - 1, y + h - 1, x, y + h - 1, highlightWidth);
  winRep->AbsoluteLine(x, y + h - 1, x, y, highlightWidth);

  winRep->PopClip();
  winRep->PopTransform();

  winRep->Flush();
}

void View::SetXAxisAttrType(AttrType type)
{ 
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  _xAxis.SetAttrType(type);
}

void View::SetYAxisAttrType(AttrType type)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  _yAxis.SetAttrType(type);
}

void View::SetZAxisAttrType(AttrType type)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  _zAxis.SetAttrType(type);
}

void View::AppendCursor(DeviseCursor *cursor)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::AppendCursor(%s)\n", GetName(), cursor->GetName());
#endif

  _cursors->Append(cursor);
}

void View::DeleteCursor(DeviseCursor *cursor)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::DeleteCursor(%s)\n", GetName(), cursor->GetName());
#endif

  _cursors->Delete(cursor);
}

// This seems to return true if it changes anything, false otherwise.
Boolean
View::DrawCursors()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::DrawCursors()\n", GetName());
#endif

  if (!_drawingEnabled) {
#if defined(DEBUG)
    printf("View drawing is disabled\n");
#endif
    return false;
  }

  if (!Mapped()) {
#if defined(DEBUG)
    printf("View %s not mapped\n", GetName());
#endif
    return false;
  }

  if (!_cursorsOn) {
    WindowRep *winRep = GetWindowRep();

    int index;
    for(index = _cursors->InitIterator(); _cursors->More(index);) {
      DeviseCursor *cursor = _cursors->Next(index);
	  if (_drawCursors) {
	  }
    }
    _cursors->DoneIterator(index);

    for(index = _cursors->InitIterator(); _cursors->More(index);) {
      DeviseCursor *cursor = _cursors->Next(index);
	  if (_drawCursors) {
        DoDrawCursor(winRep, cursor);
	  }
	  if (_jsCursors) {
	    JavaScreenCmd::DrawCursor(this, cursor);
	  }
    }
    _cursors->DoneIterator(index);

    _cursorsOn = true;
    return true;
  }

  return false;
}

// This seems to return true if it changes anything, false otherwise.
Boolean
View::HideCursors()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::HideCursors()\n", GetName());
#endif

  if (!Mapped()) {
#if defined(DEBUG)
    printf("not mapped\n");
#endif
    return false;
  }

  if (_cursorsOn) {
    WindowRep *winRep = GetWindowRep();

    int index;
    for(index = _cursors->InitIterator(); _cursors->More(index);) {
      DeviseCursor *cursor = _cursors->Next(index);
	  if (_drawCursors) {
        DoDrawCursor(winRep, cursor);
	  }
	  if (_jsCursors) {
		// JavaScreen automatically erases a cursor when it gets a
		// cursor draw request.
	    // JavaScreenCmd::EraseCursor(this, cursor);
	  }
    }
    _cursors->DoneIterator(index);
    _cursorsOn = false;
    return true;
  }

  return false;
}

void
View::DoDrawCursor(WindowRep *winRep, DeviseCursor *cursor)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::DoDrawCursor(%s)\n", GetName(), cursor->GetName());
#endif

  winRep->SetGifDirty(true);

  Boolean pixelsValid;
  int pixX1, pixY1, pixX2, pixY2;
  const char *action;

  if (_cursorsOn) {
    pixelsValid = cursor->GetOldDestPixels(pixX1, pixY1, pixX2, pixY2);
	action = "Erasing";
  } else {
    pixelsValid = cursor->GetDestPixels(pixX1, pixY1, pixX2, pixY2);
	action = "Drawing";
  }

  if (pixelsValid) {
    Coord pixXLow = MIN(pixX1, pixX2);
    Coord pixXHigh = MAX(pixX1, pixX2);
    Coord pixYLow = MIN(pixY1, pixY2);
    Coord pixYHigh = MAX(pixY1, pixY2);

    // Set things up to draw the cursor.
    winRep->SetPattern(Pattern0);
    winRep->SetLineWidth(0);
    winRep->SetXorMode();
    winRep->SetForeground(cursor->GetCursorColor());

#if defined(DEBUG)
    printf("%s cursor <%s> in view <%s> at (%g, %g), (%g, %g)\n", action,
	    cursor->GetName(), GetName(), pixXLow, pixYLow, pixXHigh, pixYHigh);
#endif

    // Fill in the cursor area, leaving space for the border.
    winRep->FillPixelRect(pixXLow, pixYLow,
        pixXHigh - pixXLow - 1.0,
        pixYHigh - pixYLow - 1.0, 1.0, 1.0, WindowRep::AlignNorthWest);

    // Clear out the middle.
	{ // for variable scope
	    const int thickness = 4;
	    int width = (int)(pixXHigh - pixXLow - thickness * 2);
	    int height = (int)(pixYHigh - pixYLow - thickness * 2);
		if (width > 0 && height > 0) {
            winRep->FillPixelRect(pixXLow + thickness, pixYLow + thickness,
			  width, height, 1.0, 1.0, WindowRep::AlignNorthWest);
		}
	}

    // Draw the border.
    winRep->SetForeground(whiteColor);
    winRep->SetPattern((Pattern)-1);
    winRep->FillPixelRect(pixXLow, pixYLow, pixXHigh - pixXLow,
        pixYHigh - pixYLow, 1.0, 1.0, WindowRep::AlignNorthWest);

    // Reset the window rep.
    winRep->SetCopyMode();

    if (_cursorsOn) {
      cursor->InvalidateOldDestPixels();
    } else {
      cursor->SetOldDestPixels(pixX1, pixY1, pixX2, pixY2);
    }
  }
}

FilterQueue *View::GetHistory()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  // Make sure we've at least got the current filter in the history!
  if (_filterQueue->Size() == 0) {
    _filterQueue->Enqueue(_filter, _filter.marked);
  }
  return _filterQueue;
}

void
View::BackOne()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::BackOne()\n", GetName());
#endif

  // Don't do anything if there's no previous filter to go back to.
  if (_filterQueue->Size() > 1) {
    VisualFilter filter;
    _filterQueue->Get(_filterQueue->Size() - 2, filter);
	filter.flag = _filter.flag;
    SetVisualFilter(filter);
    //TEMP -- should this do collaboration, etc.???
  }
}

void View::ClearHistory()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  _filterQueue->Clear();
}

void View::InsertHistory(VisualFilter &filter)
{
#if defined(DEBUG)
  printf("View::InsertHistory((%g, %g), (%g, %g), %d)\n", filter.xLow,
      filter.yLow, filter.xHigh, filter.yHigh, filter.flag);
#endif

  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  (void)_filterQueue->Enqueue(filter, filter.marked);
}

/* Look into pixmap buffer for pixmap that we can use for drawing
   filter. Restore the pixmap, and return a new visual filter. */

View::PixmapStat View::RestorePixmap(VisualFilter filter,
				     VisualFilter &newFilter)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  int x, y;
  unsigned int width, height;
  Geometry(x, y, width, height);

#if defined(DEBUG)
  if (_pixmap) {
    printf("RestorePixmap %s\n", GetName());
    printf("cur filter: %f,%f,%f,%f\n", filter.xLow, filter.xHigh,
	   filter.yLow, filter.yHigh);
    printf("pix filter: %f,%f,%f,%f\n",
	   _pixmap->filter.xLow, _pixmap->filter.xHigh,
	   _pixmap->filter.yLow, _pixmap->filter.yHigh);
    printf("cur width %d, height %d, pix %d, %d\n", width, height,
	   _pixmap->width, _pixmap->height);
  }
#endif

  if (!PixmapEnabled())
    return PixmapNone;

  if (Mapped() && _pixmap && 
      filter.xLow ==  _pixmap->filter.xLow &&
      filter.yLow == _pixmap->filter.yLow &&
      filter.xHigh == _pixmap->filter.xHigh &&
      filter.yHigh == _pixmap->filter.yHigh &&
      _pixmap->width == (int)width && _pixmap->height == (int)height) {
    GetWindowRep()->DisplayPixmap(_pixmap);
    return PixmapTotal;
  }

  return PixmapNone;
}

void View::InvalidatePixmaps()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (!_pixmap)
    return;

  free(_pixmap->data);
  delete _pixmap;
  _pixmap = NULL;
}

// Used by the color manager when the palette changes. Forces all views
// to update their pixmaps to use the new colors.
void	View::RefreshAll(void)
{
	int		index;

	for(index = View::InitViewIterator(); View::MoreView(index);)
	{
		View*	view = View::NextView(index);

		view->Refresh(false);
	}

	View::DoneViewIterator(index);
}

void View::SavePixmaps(FILE *file)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("SavePixmap at bytes %ld\n", ftell(file));
  printf("View SavePixmaps bytes %d\n", _bytes);
#endif

  // Store a known 4-byte integer at head of file to distinguish
  // the byte order (little/big endian) used on this machine; at
  // load time, check the value of the integer.

  unsigned long int magic = 0xdeadbeef;
  if (fwrite(&magic, sizeof magic, 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }
  
  /* Disable cursors if currently displayed */
  Boolean cursorState = HideCursors();
  Boolean dispSymbol = DisplaySymbols(true);
  Boolean dispConnector = DisplayConnectors(false);

#ifndef JPEG

  //
  // Save pixmap in run-length-encoded format
  //

  int saved = 0;
  DevisePixmap *pixmap = 0;
  if (Iconified() || !Mapped() ||_refresh || _bytes < VIEW_BYTES_BEFORE_SAVE) {
    if (_pixmap) {
      /* save old pixmap */
      saved = 1;
      pixmap = _pixmap;
    } else
      saved = 0;
  } else {
    /* save current pixmap */
    saved = 1;
    WindowRep *winRep = GetWindowRep();
	winRep->SetGifDirty(true);
    pixmap = winRep->GetPixmap();
    if (!pixmap) {
      saved = 0;
    }
  }
  
  if (fwrite(&saved, sizeof(saved), 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }

  if (!saved) {
    /* Return cursors to original state */
    if (cursorState)
      (void) DrawCursors();
    DisplaySymbols(dispSymbol);
    DisplayConnectors(dispConnector);
    return;
  }
  
  DOASSERT(pixmap, "No pixmap");

#if defined(DEBUG)
  printf("Saving Pixmap for %s, data %d bytes\n", GetName(), _bytes);
#endif

  pixmap->dataBytes = _bytes; /* # of data bytes used to create pixmap*/
  pixmap->filter = _filter;
  if (GetXAxisAttrType() == DateAttr) {
    /* Convert to date and back to be consistent with control panel's
       date format. Otherwise, we might get round-off errors */
    (void)ParseFloatDate(DateString(pixmap->filter.xLow),
			 pixmap->filter.xLow);
    (void)ParseFloatDate(DateString(pixmap->filter.xHigh),
			 pixmap->filter.xHigh);
  }
  if (GetYAxisAttrType() == DateAttr) {
    (void)ParseFloatDate(DateString(pixmap->filter.yLow),
			 pixmap->filter.yLow);
    (void)ParseFloatDate(DateString(pixmap->filter.yHigh),
			 pixmap->filter.yHigh);
  }
  
#if defined(DEBUG)
  printf("SavePixmap filter %f,%f,%f,%f\n",
	 pixmap->filter.xLow, pixmap->filter.xHigh,
	 pixmap->filter.yLow, pixmap->filter.yHigh);
#endif
		
  if (fwrite(pixmap, sizeof(*pixmap), 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }
  if (fwrite(pixmap->data, pixmap->compressedBytes, 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }

#else

  //
  // Save pixmap in JPEG format
  //

  int num[2] = {0, 0};
  int pos = ftell(file);
  if (!Mapped() || _bytes < 0 * VIEW_BYTES_BEFORE_SAVE || _refresh) {
    num[1] = pos + 2 * sizeof(int);
    if (fwrite(num, sizeof(num), 1, file) != 1) {
      reportErrSys("fwrite");
      DOASSERT(0, "Cannot write pixmap file");
    }
    /* Return cursors to original state */
    if (cursorState)
      DrawCursors();
    DisplaySymbols(dispSymbol);
    DisplayConnectors(dispConnector);
    return;
  }
  
  /* Save window pixmap */
  num[0] = 1;

#if 0
  if (fwrite(&num, sizeof(num), 1, file) != 1) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }
#endif

  WindowRep *winRep = GetWindowRep();
  DevisePixmap *pixmap = winRep->GetPixmap();
  pixmap->dataBytes = _bytes;
  pixmap->filter = _filter;
  
#if defined(DEBUG)
  printf("pixMap dataBytes %d, imageBytes %d, width %d, height %d, bpl %d, pad %d\n",
	 pixmap->dataBytes, pixmap->imageBytes, pixmap->width,
	 pixmap->height, pixmap->bytes_per_line, pixmap->padding);
#endif
  
#if 0
  if (fwrite(pixmap, sizeof(*pixmap), 1, file) != 1 ) {
    reportErrSys("fwrite");
    DOASSERT(0, "Cannot write pixmap file");
  }
#endif
  
#if defined(DEBUG)
  printf("before compress, at %d\n", ftell(file));
#endif

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  JSAMPROW row_pointer[1];
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo,file);
  cinfo.image_width = pixmap->width;
  cinfo.image_height = pixmap->height;
  cinfo.input_components = pixmap->bytes_per_line/pixmap->width;
  cinfo.in_color_space = JCS_GRAYSCALE;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 100, TRUE);
  jpeg_start_compress(&cinfo, TRUE);
  
  unsigned char *data = (unsigned char *)pixmap->data;
  for(int i = 0; i < pixmap->height; i++) {
    row_pointer[0] = &data[i * pixmap->bytes_per_line];
    (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
  
  int posNow = ftell(file);
  fseek(file, pos + sizeof(int), 0);
  fwrite(&posNow, sizeof(int), 1, file);
  fseek(file, posNow, 0);
  
#if defined(DEBUG)
  printf("after compress, at %d\n", ftell(file));
#endif
#endif

  /* Return cursors to original state */
  if (cursorState)
    DrawCursors();
  DisplaySymbols(dispSymbol);
  DisplayConnectors(dispConnector);
}

/* Restore pixmaps from an open file into pixmap buffer */

void View::LoadPixmaps(FILE *file)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  // The first 4-byte integer contains a known value. Check the value
  // to make sure we're reading data stored in the same endian order
  // as this machine is using.

  unsigned long int check;
  if (fread(&check, sizeof check, 1, file) != 1) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }

  if (check != 0xdeadbeef) {
    printf("Note: Pixel image for %s not in compatible format.\n",
	   GetName());
    _pixmap = NULL;
    return;
  }
  
#ifndef JPEG

  //
  // Load image stored in run-length-encoded format
  //

  int saved;
  if (fread(&saved, sizeof(saved), 1, file) != 1 ) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }
  if (!saved) {
#if defined(DEBUG)
    printf("View::LoadPixmaps: %s not saved\n", GetName());
#endif
    _pixmap = NULL;
    return;
  }

#if defined(DEBUG)
  printf("Loading pixmap for %s\n", GetName());
#endif

  DevisePixmap *pixmap = new DevisePixmap;
  DOASSERT(pixmap, "Out of memory");

  if (fread(pixmap, sizeof(*pixmap), 1, file) != 1 ) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }

#if defined(DEBUG)
  printf("LoadPixmap filter %f,%f,%f,%f\n",
	 pixmap->filter.xLow, pixmap->filter.xHigh,
	 pixmap->filter.yLow, pixmap->filter.yHigh);
#endif
		
  if (!(pixmap->data = (unsigned char *)malloc(pixmap->compressedBytes))) {
    fprintf(stderr,"View::LoadPixmaps out of memory\n");
    DOASSERT(0, "Cannot read pixmap file");
  }
  
  if (fread(pixmap->data, pixmap->compressedBytes, 1, file) != 1) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }
  _pixmap = pixmap;
  
#else

  //
  // Load image stored in JPEG format
  //

  fseek(file, _nextPos, 0);
  printf("Load pixmap at bytes %d\n", ftell(file));

  int num[2];
  if (fread(num, sizeof(num), 1, file) != 1) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }
  _nextPos = num[1];
  
  if (num[0] <= 0 )
    return;
  
  DOASSERT(num[0] <= 1, "Too many pixmaps");
  
  _pixmap = new DevisePixmap;
  DOASSERT(_pixmap, "Out of memory");

  if (fread(_pixmap, sizeof(*_pixmap), 1, file) != 1) {
    reportErrSys("fread");
    DOASSERT(0, "Cannot read pixmap file");
  }

#if defined(DEBUG)
  printf("pixMap dataBytes %d, imageBytes %d, width %d, height %d, bpl %d pad %d\n",
	 _pixmap->dataBytes, _pixmap->imageBytes, _pixmap->width,
	 _pixmap->height, _pixmap->bytes_per_line, _pixmap->padding);
#endif
  
#if defined(DEBUG)
  printf("before decompress, at %d\n", ftell(file));
#endif

  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  
  jpeg_stdio_src(&cinfo,file);
  (void)jpeg_read_header(&cinfo,TRUE);
  jpeg_start_decompress(&cinfo);

#if defined(DEBUG)
  printf("allocating %d bytes\n", _pixmap->imageBytes);
#endif

  unsigned char *data = (unsigned char *)malloc(_pixmap->imageBytes);
  DOASSERT(data, "Out of memory");

  _pixmap->data = data;
  unsigned char *buffer[1];
  for(int i = 0; i < _pixmap->height; i++) {
    buffer[0] = &data[i * _pixmap->bytes_per_line];
#if defined(DEBUG)
    printf("reading line %d\n", i);
#endif
    jpeg_read_scanlines(&cinfo,buffer,1);
  }

  (void)jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

#if defined(DEBUG)
  printf("after decompress, at %d\n", ftell(file));
#endif
#endif
}

/* Print view statistics */

void View::PrintStat()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  int total = _jump + _zoomIn + _zoomOut + _scrollLeft + _scrollRight
              + _unknown;
  printf("View %s: total operationss %d\n", GetName(), total);

  if (total <= 0)
    return;

  printf("  Jump %d, %.2f%%\n", _jump, 100.0 * _jump / total);
  printf("  ZoomIn %d, %.2f%%\n", _zoomIn, 100.0 * _zoomIn / total);
  printf("  ZoomOut %d, %.2f%%\n", _zoomOut, 100.0 * _zoomOut / total);
  printf("  ScrollLeft %d, %.2f%%\n", _scrollLeft,
	 100.0 * _scrollLeft / total);
  printf("  ScrollRight %d, %.2f%%\n", _scrollRight,
	 100.0 * _scrollRight / total);
  printf("  Unknown %d, %.2f%%\n", _unknown, 100.0 * _unknown / total);
}

#if 0
void View::CompRhoPhiTheta()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("<<<< x = %f y = %f z = %f\n",
         _filter.camera.x_, _filter.camera.y_, _filter.camera.z_);
  printf("<<<< fx = %f fy = %f fz = %f\n",
         _filter.camera.fx, _filter.camera.fy, _filter.camera.fz);
  printf("<<<< rho = %f phi = %f theta = %f\n\n",
         _filter.camera._rho, _filter.camera._phi, _filter.camera._theta);
#endif

  if (!_filter.camera.spherical_coord) {
    double X = _filter.camera.x_ - _filter.camera.fx;
    double Y = _filter.camera.y_ - _filter.camera.fy;
    double Z = -(_filter.camera.z_ - _filter.camera.fz);

    _filter.camera._rho = sqrt(SQUARE(X) + SQUARE(Y) + SQUARE(Z));

    if (_filter.camera._rho > 0)
      _filter.camera._phi = acos(Y / _filter.camera._rho);
    else {
      _filter.camera._phi = 0.0;
#if defined(DEBUG)
      printf("*********** WARNING *****************\n");
#endif
    }

    if (_filter.camera._rho == 0)
      _filter.camera._theta = 0.0;

    // ------------- on yz-axis
    else if (X == 0 && Z >= 0)  // on +z axis
      _filter.camera._theta = 0.0;
    else if (X == 0 && Z < 0)   // on -z axis
      _filter.camera._theta = M_PI;
    
    // ------------- on xy-axis
    else if (Z == 0 && X > 0) // on +x axis
      _filter.camera._theta = M_PI_2;
    else if (Z == 0 && X < 0) // on -x axis
      _filter.camera._theta = M_PI_2 + M_PI;    // pi * 2 / 3
    
    // ------------- four quadrants
    else if (X > 0 && Z > 0)
      _filter.camera._theta = atan(X / Z);
    else if (X > 0 && Z < 0)
      _filter.camera._theta = M_PI + atan(X / Z);
    else if (X < 0 && Z < 0)
      _filter.camera._theta = M_PI + atan(X / Z);
    else if (X < 0 && Z > 0)
      _filter.camera._theta = (M_PI_2 + M_PI) + fabs(atan(Z / X));

    else {
      printf("cx = %f cy = %f cz = %f\n", X, Y, Z);
      DOASSERT(0, "Invalid coordinates");
    }
  } else {
    _filter.camera.x_ = _filter.camera._rho * sin(_filter.camera._phi) * sin(_filter.camera._theta);
    _filter.camera.x_ += _filter.camera.fx;
    _filter.camera.y_ = _filter.camera._rho * cos(_filter.camera._phi);
    _filter.camera.y_ += _filter.camera.fy;
    _filter.camera.z_ = -_filter.camera._rho * sin(_filter.camera._phi) * cos(_filter.camera._theta);
    _filter.camera.z_ += _filter.camera.fz;
  }
  _filter.camera=_filter.camera;

#if defined(DEBUG)
  printf(">>>> x = %f y = %f z = %f\n",
         _filter.camera.x_, _filter.camera.y_, _filter.camera.z_);
  printf(">>>> fx = %f fy = %f fz = %f\n",
         _filter.camera.fx, _filter.camera.fy, _filter.camera.fz);
  printf(">>>> rho = %f phi = %f theta = %f\n\n",
         _filter.camera._rho, _filter.camera._phi, _filter.camera._theta);
#endif
}
#endif

void View::SetCamera(Camera camera)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  /* see if 3D mapping needs to be updated */
#if 0
  if (camera.x_ != _filter.camera.x_ ||
      camera.y_ != _filter.camera.y_ || 
      camera.z_ != _filter.camera.z_ ||
      camera._dvs != _filter.camera._dvs ||
      camera._rho != _filter.camera._rho || 
      camera._phi != _filter.camera._phi || 
      camera._theta != _filter.camera._theta || 
      camera.fx != _filter.camera.fx ||
      camera.fy != _filter.camera.fy ||
      camera.fz != _filter.camera.fz || 
      camera._perspective != _filter.camera._perspective || 
      camera._twist_angle != _filter.camera._twist_angle || 
      camera.H != _filter.camera.H ||
      camera.V != _filter.camera.V ||
      camera.view_dir != _filter.camera.view_dir ||
      camera.pan_right != _filter.camera.pan_right ||
      camera.pan_up != _filter.camera.pan_up)
#endif
  if (!(camera == _filter.camera)) {
    _filter.camera = camera;
//    CompRhoPhiTheta();
    _updateTransform = true;
    DepMgr::Current()->RegisterEvent(dispatcherCallback,
									 DepMgr::EventViewCameraCh);
    Refresh();
  }

  /* these calls cause the user interface to update the 3D query dialog */
  ReportFilterAboutToChange();
  ReportFilterChanged(_filter, false);
}

void View::Draw3DAxis()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("Drawing 3D axis\n");
#endif

  WindowRep*	win = GetWindowRep();
  win->SetGifDirty(true);

  win->SetForeground(GetForeground());
  Map3D::DrawRefAxis(win, _filter.camera);
}

DevStatus
View::PrintPS()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%p)::PrintPS(%s)\n", this, _name);
#endif
  DevStatus result(StatusOk);

  _printing = true;

  DeviseDisplay *psDispP = DeviseDisplay::GetPSDisplay();

  // Switch this view over to PostScript drawing mode.
  Rectangle viewGeom;
  int xVal, yVal;
  AbsoluteOrigin(xVal, yVal);
  viewGeom.x = xVal;
  viewGeom.y = yVal;
  viewGeom.width = _width;
  viewGeom.height = _height;

  Rectangle parentGeom;
  psDispP->GetScreenPrintRegion(parentGeom);

  /* If we're in piled mode, the drawing will actually be done using
   * the WindowRep of the *bottom* view in the pile, so that's the one
   * that has to be set for file output. */
  SetFileOutput(viewGeom, parentGeom);

  // Force a refresh to print the PostScript.
  FILE *printFile = psDispP->GetPrintFile();
  DOASSERT(printFile != NULL, "No PostScript file open");
  fprintf(printFile, "\n%% Start of view '%s'\n", _name);
  Refresh(false);

  return result;
}

DevStatus
View::PrintPSDone()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View::PrintPSDone(%s)\n", _name);
#endif
  DevStatus result(StatusOk);

  DeviseDisplay *psDispP = DeviseDisplay::GetPSDisplay();

  FILE *printFile = psDispP->GetPrintFile();
  DOASSERT(printFile != NULL, "No PostScript file open");
  fprintf(printFile, "%% End of view '%s'\n", _name);

  // Switch this view back to screen drawing mode.
  SetScreenOutput();

  // Continue printing any more views that need to be printed.
  result += ViewWin::PrintPS();

  _printing = false;

  return result;
}

void
View::SetFont(const char *which, int family, float pointSize,
	      Boolean bold, Boolean italic, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View::SetFont(%s, %d, %f, %d, %d)\n", which, family, pointSize,
    bold, italic);
#endif

  if (_pileMode && notifyPile) {
	GetParentPileStack()->SetFont(which, family, pointSize, bold, italic);
  } else {
    if (!strcmp(which, "title")) {
      _titleFont.Set(family, pointSize, bold, italic);
    } else if (!strcmp(which, "x axis")) {
      _xAxis.SetFont(family, pointSize, bold, italic);
    } else if (!strcmp(which, "y axis")) {
      _yAxis.SetFont(family, pointSize, bold, italic);
    } else if (!strcmp(which, "z axis")) {
      _zAxis.SetFont(family, pointSize, bold, italic);
    } else if (!strcmp(which, "data")) {
      // Moved data font stuff into mapping -- RKW 1999-07-20.
      fprintf(stderr,
          "Warning: using deprecated command: setFont <view> %s\n", which);

      int defFamily;
      float defSize;
      Boolean defBold, defItalic;
      DevFont defFont;
      defFont.Get(defFamily, defSize, defBold, defItalic);

      if (family != defFamily || pointSize != defSize || bold != defBold ||
          italic != defItalic) {
        fprintf(stderr, "Set font parameters in view <%s> mapping\n\n",
            GetName());
      }
    } else {
      reportErrNosys("Illegal font selection");
    }

    DepMgr::Current()->RegisterEvent(dispatcherCallback,
	    DepMgr::EventViewFontCh);
    Refresh();
  }
}

void
View::GetFont(const char *which, int &family, float &pointSize,
	      Boolean &bold, Boolean &italic)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View::GetFont()\n");
#endif

  if (!strcmp(which, "title")) {
    _titleFont.Get(family, pointSize, bold, italic);
  } else if (!strcmp(which, "x axis")) {
    _xAxis.GetFont(family, pointSize, bold, italic);
  } else if (!strcmp(which, "y axis")) {
    _yAxis.GetFont(family, pointSize, bold, italic);
  } else if (!strcmp(which, "z axis")) {
    _zAxis.GetFont(family, pointSize, bold, italic);
#if 0 // Moved data font stuff into mapping -- RKW 1999-07-20.
  } else if (!strcmp(which, "data")) {
    _dataFont.Get(family, pointSize, bold, italic);
#endif
  } else {
    reportErrNosys("Illegal font selection");
  }
}

#if 0

//void 
// View::UpdateViewTable(char *name, double X, double Y, PColorID bgid) 
void View::UpdateViewTable()
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  DataSourceBuf *vBuf = GetViewTable();
  char line[100];
  int index = _viewList->InitIterator();
  _viewTableBuffer->Clear();
  while (_viewList->More(index)) {
    View *v = _viewList->Next(index);
#if defined(DEBUG)
    printf("View %s \n", v->GetName());
#endif
    int x, y, x0, y0;
    unsigned w, h;
    v->Geometry(x, y, w, h);
    v->AbsoluteOrigin(x0,y0);
    char *name = v->GetName();
    PColorID	bgid = v->GetBackground();
#if defined(DEBUG)
    printf("UpdateViewtable: %g %g %d %s\n", (double)x0, (double)y0, bgid, 
	   name);
#endif
    int formatted = snprintf(line, sizeof(line), "%g %g %d %s\n",
	    (double)x0, (double)y0, bgid, name );
	DevStatus bufCheck = checkAndTermBuf2(line, formatted);
	DOASSERT(bufCheck == StatusOk);
    int len = strlen(line);
    DOASSERT(_viewTableBuffer,"no view table buffer");
    if ( (int) _viewTableBuffer->Write(line, len) != len) {
      fprintf(stderr, "Out of viewtable space\n");
      return;
    }
  }
  _viewList->DoneIterator(index);
}


DataSourceBuf* View::GetViewTable()      
{ 
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (!_viewTableBuffer) {
    _viewTableBuffer = new DataSourceFixedBuf(3072, "viewTableBuffer");
  }
  return _viewTableBuffer; 
}
#endif

//******************************************************************************
// Callback Methods (ControlPanelCallback)
//******************************************************************************

void	View::ModeChange(ControlPanel::Mode mode)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
	printf("Change mode %d,%d,%d,%d\n", _hasExposure, _filterChanged, _refresh,
		   _updateTransform);
#endif

	if ((mode == ControlPanel::LayoutMode) && _querySent)
	{
#if defined(DEBUG)
		printf("abort query from mode change\n");
#endif

		AbortQuery();
		_modeRefresh = true;
	}

	Refresh();
}

//******************************************************************************
// Callback Methods (DispatcherCallback)
//******************************************************************************

const char*	View::DispatchedName(void)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
	return GetName();
}

// Send a query, if there is one. Abort existing query if necessary. 
// XXX: need to crop exposure against _filter before sending query.
void	View::Run(void)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG_LOG)
	{
      char logBuf[256];
	  int formatted = snprintf(logBuf, sizeof(logBuf),
	    "View(%s)::Run()\n", GetName());
	  checkAndTermBuf2(logBuf, formatted);
	  DebugLog::DefaultLog()->Message(DebugLog::LevelInfo2, logBuf);
	}
#endif
#if defined(DEBUG)
	printf("\nView(%s, %p)::Run()\n", GetName(), _dispatcherID);
#endif
#if defined(DEBUG_MEM)
  printf("%s: %d; end of data seg = %p\n", __FILE__, __LINE__, sbrk(0));
#endif

    if (!_drawingEnabled) {
#if defined(DEBUG)
      printf("View drawing is disabled\n");
#endif
      return;
    }

    _refreshPending = false;

#if defined(DEBUG)
  _filterQueue->Print(stdout);
#endif

    VisualFilter histFilter;
	FilterQueue *fq = GetHistory();
	fq->Get(fq->Size() - 1, histFilter);
	const double absTol = 1.0e-3;
	const double relTol = 1.0e-3;
    if (!dequal(histFilter.xLow, _filter.xLow, absTol, relTol) ||
	    !dequal(histFilter.xHigh, _filter.xHigh, absTol, relTol) ||
		!dequal(histFilter.yLow, _filter.yLow, absTol, relTol) ||
		!dequal(histFilter.yHigh, _filter.yHigh, absTol, relTol)) {
      _filterQueue->Enqueue(_filter, _filter.marked);
	  char errBuf[256];
#if defined(DEBUG)
	  int formatted = snprintf(errBuf, sizeof(errBuf),
	      "(warning) view <%s> current filter does not match "
	      "last history filter", GetName());
	  checkAndTermBuf2(errBuf, formatted);
	  reportErrNosys(errBuf);
#endif
	}
#if 0
	printf("  histFilter: %d, (%g, %g), (%g, %g)\n", histFilter.flag,
	  histFilter.xLow, histFilter.yLow, histFilter.xHigh, histFilter.yHigh);
	printf("  _filter: %d, (%g, %g), (%g, %g)\n", _filter.flag,
	  _filter.xLow, _filter.yLow, _filter.xHigh, _filter.yHigh);
	printf("  _lastFilter: %d, (%g, %g), (%g, %g)\n", _lastFilter.flag,
	  _lastFilter.xLow, _lastFilter.yLow, _lastFilter.xHigh,
	  _lastFilter.yHigh);
#endif

	if (_refresh)
		_hasExposure = false;

	// If view is in pile mode but not the top view, it has to wait until the
	// top view has erased the window and drawn axes and other decorations; the
	// top view will send explicit refresh requests to the bottom views.

    if (_pileMode)
	{
		ViewWin*	parent = GetParent();

		// If we are running client/server Devise, we may get here before this
		// view's parent has been created, so do not bomb out.  RKW 8/30/96.
		if (parent == NULL) {
			return;
        }

		ViewWin *vw = GetParentPileStack()->GetFirstView();

		if (this != vw)
		{
			if ((_pileViewHold && !_isHighlightView) ||
			  GetParentPileStack()->QueryRunning())
			{
#if defined(DEBUG)
				printf("View %s cannot continue\n", GetName());
#endif
				AbortQuery();
				return;
			}

#if defined(DEBUG)
			printf("Middle or top pile view %s continues\n", GetName());
#endif

			_pileViewHold = true;
		}
		else
		{
			if (GetParentPileStack()->QueryRunning())
			{
#if defined(DEBUG)
				printf("View %s cannot continue\n", GetName());
#endif
				const int bufLen = 1024;
				char buf[bufLen];
				int formatted = snprintf(buf, bufLen, "Warning: bottom pile "
				  "view %s should run a query, but another view in the pile "
				  "is already running a query -- possible incorrect pile draw",
				  GetName());
				checkAndTermBuf(buf, bufLen, formatted);
				reportErrNosys(buf);

				AbortQuery();
				return;
			}
#if defined(DEBUG)
			printf("Bottom pile view %s continues\n", GetName());
#endif

			// Assure that the bottom view's window rep (the one used to
			// draw the pile) is visible.
			GetWindowRep()->Raise();
		}
	}

	ControlPanel::Mode	mode = ControlPanel::Instance()->GetMode();

#if defined(DEBUG)
	if (mode == ControlPanel::LayoutMode)
		printf("layout mode ");
	else
		printf("disp mode ");

	printf("exp %d flt %d ref %d upd %d upnd %d\n",
	        _hasExposure, _filterChanged,
	        _refresh, _updateTransform, _updateNumDim);
#endif

	//TEMP -- there seems to be almost no difference between what we do
	// for _hasExposure, _filterChanged, _refresh, and _updateTransform.
	// and _updateNumDim.

	if ((mode == ControlPanel::LayoutMode) && 
		(_hasExposure || _filterChanged || _refresh || _updateTransform))
	{ 
		// Keep track that events occurred while in LayoutMode
		_modeRefresh = true;
	}
	else if ((mode == ControlPanel::DisplayMode) && _modeRefresh)
	{
		// Refresh in display mode because events occurred in LayoutMode
		_refresh = true;
	}

	if (_querySent)
	{
		if (_hasExposure || _filterChanged || _refresh
                    || _updateTransform || _updateNumDim || !Mapped())
		{
#if defined(DEBUG)
			printf("View:: aborting\n");
			printf("querySent == true, refresh = %d\n", _refresh);
#endif

			AbortQuery();
			_refresh = true;
		}
		else
		{
#if defined(DEBUG)
			printf("Query already sent, nothing to do\n");
#endif
			return;
		}
	}

	if (!Mapped())
	{
#if defined(DEBUG)
		printf("Window not mapped, nothing to do\n");
#endif

		return;
	}

	if (Iconified())
	{
		// Force "redrawing" of whole view (mainly for statistics and
		// other derived data) when window iconified displayed
		_refresh = true;
		_hasExposure = false;
	}

	if (!_hasExposure && !_filterChanged && !_refresh)
	{
#if defined(DEBUG)
		printf("View not refreshed and filter not changed, nothing to do\n");
#endif

		return;
	}

	WindowRep*		winRep = GetWindowRep();
	int				scrnX, scrnY, scrnWidth, scrnHeight;
	unsigned int	sW, sH;
    VisualFilter	newFilter;

	winRep->SetGifDirty(true);

	Geometry(scrnX, scrnY, sW, sH);

	scrnWidth = sW;
	scrnHeight = sH;
        if (_updateNumDim) {
	  winRep->SetNumDim(_numDimensions);
	  UpdateTransform(GetWindowRep());
	  _updateTransform = false;
	  _updateNumDim = false;
	}
    
	if (!Iconified() && !_pileMode && (_numDimensions == 2) &&
		RestorePixmap(_filter, newFilter) == PixmapTotal)
	{
#if defined(DEBUG)
		printf("View::Run: Restored complete pixmap for\n  %s\n", GetName());
#endif

		if (_updateTransform)
		{
			UpdateTransform(GetWindowRep());
			_updateTransform = false;
		}

		winRep->PushTop();
		winRep->MakeIdentity();			// Set up identity transformation
		DrawAxesLabel(winRep, scrnX, scrnY, sW, sH);	// Draw axes
	
		if (viewBorder)					// Draw view border
		{
			PColorID	savePColorID = winRep->GetForeground();
		
			winRep->SetForeground(GetPColorID(viewBorderColor));
			DrawHighlight();
			winRep->SetForeground(savePColorID);
		}

		Boolean		oldSelected = _selected;

		_selected = false;
		DoSelect(oldSelected);		// Draw highlight border
		winRep->PopTransform();			// Pop the transform

		_cursorsOn = false;

		if (_numDimensions == 3)
			Draw3DAxis();
		DrawCursors();		// Draw cursors

		_hasExposure = false;
		_filterChanged = false;
		_refresh = false;
		_hasLastFilter = false;

		return;
	}

	// Make sure the view's physical TData is up-to-date as per any
	// TAttrLinks the view is a slave of.
	UpdatePhysTData();

	if (!_updateTransform && !_hasExposure && !_refresh && _filterChanged)
	{
		UpdateFilterStat	stat;

		stat = UpdateFilterWithScroll();

		if (stat == Scrolled)			// Do scroll, if possible
		{
			// Did scrolling. Can keep this filter update so that _hasFilter
			// is no longer true, and _hasExposure is true.
			_hasExposure = true;
			_filterChanged = false;
			_hasLastFilter = true;
			_lastFilter = _filter;
		}
		else if (stat == SameFilter)
		{
			// A sequence of scroll/zoom between updates made the latest
			// filter the same as the one being displayed
			_filterChanged = false;
			_hasLastFilter = true;
			_lastFilter = _filter;
			return;
		}
	}

	if (_updateTransform)				// Update WindowRep transform matrix
	{
		UpdateTransform(GetWindowRep());
		_updateTransform = false;
	}

	Boolean		piledDisplay = false;

	if (_pileMode)
	{
		ViewWin*	firstSibling = GetParentPileStack()->GetFirstView();

		if (this != firstSibling)
		{
#if defined(DEBUG)
			printf("View %s follows first sibling %s\n", GetName(),
				   firstSibling->GetName());
#endif

			piledDisplay = true;
		}
		else
		{
#if defined(DEBUG)
			printf("View %s is first child\n", GetName());
#endif
		}
	}

	if (piledDisplay || _filterChanged || _refresh)
	{									// Need to redraw the whole screen
		_hasLastFilter = true;
		_lastFilter = _filter;
		_hasExposure = false;
	}

#if !FILL_WHOLE_BACKGROUND
	if (_hasExposure)					// Limit exposure to size of window
	{
#if defined(DEBUG)
		printf("exposure (%d,%d),(%d,%d) ",
			   _exposureRect.xLow, _exposureRect.yLow,
			   _exposureRect.xHigh, _exposureRect.yHigh);
#endif

		_exposureRect.xLow = MAX(_exposureRect.xLow, 0);
		_exposureRect.xLow = MIN(_exposureRect.xLow, scrnWidth - 1);
		_exposureRect.xHigh = MAX(_exposureRect.xLow, _exposureRect.xHigh);
		_exposureRect.xHigh = MIN(_exposureRect.xHigh, scrnWidth - 1);

		_exposureRect.yLow = MAX(_exposureRect.yLow, 0);
		_exposureRect.yLow = MIN(_exposureRect.yLow, scrnHeight - 1);
		_exposureRect.yHigh = MAX(_exposureRect.yLow, _exposureRect.yHigh);
		_exposureRect.yHigh = MIN(_exposureRect.yHigh, scrnHeight - 1);

#if defined(DEBUG)
		printf("--> (%d,%d),(%d,%d)\n", _exposureRect.xLow, _exposureRect.yLow,
			   _exposureRect.xHigh, _exposureRect.yHigh);
#endif
	}
#endif
    
	// Decorate view with axes etc.
	// Set up identity transformation
	winRep->PushTop();
	winRep->MakeIdentity();

	if (!piledDisplay)
	{
		DrawAxesLabel(winRep, scrnX, scrnY, scrnWidth, scrnHeight);	// Draw axes

		if (viewBorder)					//	Draw view border
		{
			PColorID	savePColorID = winRep->GetBackground();

			winRep->SetForeground(GetPColorID(viewBorderColor));
			DrawHighlight();
			winRep->SetForeground(savePColorID);
		}

		Boolean		oldSelected = _selected;

		_selected = false;
		DoSelect(oldSelected);		// Draw highlight border
	}

	// Push clip region using this transform
	int		dataX, dataY, dataW, dataH;

	GetDataArea(dataX, dataY, dataW, dataH);

#if !FILL_WHOLE_BACKGROUND
	if (_hasExposure)					// Use exposure rectangle if needed
	{
		int		dataX2 = MIN(_exposureRect.xHigh, dataX + dataW - 1);
		int		dataY2 = MIN(_exposureRect.yHigh, dataY + dataH - 1);

		dataX = MAX(_exposureRect.xLow, dataX);
		dataY = MAX(_exposureRect.yLow, dataY);
		dataW = dataX2 - dataX + 1;
		dataH = dataY2 - dataY + 1;
	}
#endif

	winRep->PushClip(dataX, dataY, dataW - 1, dataH - 1);	// Clip draw area

	if (!piledDisplay)					// Blank out area to be drawn
	{
#if defined(DEBUG)
		printf("Clearing data area in window %p\n", winRep);
#endif

		if (winRep->DaliImageCount() > 0)
		{
			(void)winRep->DaliFreeImages();
			sleep(1);
		}

		if (winRep->ETk_WindowCount() > 0) {
			winRep->ETk_MarkAll(false);
        }

		// Always do the cleanup in pile mode in case this view doesn't have
		// children but other views in the pile do.
		if (NumChildren() || IsInPileMode()) {
		  if (IsInPileMode()) {
            // This view is piled -- we must clean up the view symbols (if
			// any) of all views in the pile.
            int parentIdx = GetParentPileStack()->InitIterator();
			while (GetParentPileStack()->More(parentIdx)) {
			  View *parentView = (View *)GetParentPileStack()->Next(parentIdx);
			  parentView->CleanUpViewSyms();
			}
			GetParentPileStack()->DoneIterator(parentIdx);
		  } else {
		    CleanUpViewSyms();
          }
		}

#if !FILL_WHOLE_BACKGROUND || COLOR_AREAS
		winRep->SetForeground(GetBackground());
		winRep->SetPattern(Pattern0);
#  if COLOR_AREAS
		winRep->SetForeground((PColorID)4);
        winRep->SetPattern((Pattern)-32);
#  endif
		winRep->SetLineWidth(0);
		winRep->ClearBackground(dataX, dataY, dataW - 1, dataH - 1);
#  if COLOR_AREAS
		winRep->SetForeground(GetBackground());
        winRep->SetPattern(Pattern0);
#  endif
#endif

		//
		// Since we've just cleared the whole view background, we've erased
		// all cursors in this view and any views piled with this view.
		//
		if (IsInPileMode()) {
		    PileStack *ps = GetParentPileStack();
		    int viewIndex = ps->InitIterator();
			while (ps->More(viewIndex)) {
			    View *tmpView = (View *)ps->Next(viewIndex);
				tmpView->InvalidateCursors();
		    }
			ps->DoneIterator(viewIndex);
		} else {
		    InvalidateCursors();
		}
	}

	winRep->PopTransform();				// Pop the identity transform matrix

	_hasExposure = false;
	_filterChanged = false;
	_refresh = false;

	if (mode == ControlPanel::DisplayMode)
	{
		// Send query for events that occurred while in layout mode
		_querySent = true;
		_modeRefresh = false; 

		ControlPanel::Instance()->SetBusy();

		if (!_hasTimestamp)
			_timeStamp = TimeStamp::NextTimeStamp();

		_hasTimestamp = false;
		_bytes = 0;

#if defined(DEBUG)
		printf("View %s sending query\n", GetName());
        printf("  filter: %d, (%f, %f, %f, %f)\n", _filter.flag,
			   _filter.xLow, _filter.xHigh, _filter.yLow,
			   _filter.yHigh);
#endif

        _refreshPending = true;
		DerivedStartQuery(_filter, _timeStamp);
	}
	else
	{
		winRep->PopClip();
	}

#if defined(DEBUG)
	printf("after Run %d %d %d %d\n", _hasExposure, _filterChanged, _refresh,
		   _updateTransform);
#endif
}

//******************************************************************************
// Callback Methods (WindowRepCallback)
//******************************************************************************

void	View::HandleExpose(WindowRep* w, int x, int y, unsigned width, 
						   unsigned height)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
	printf("View(%s)::HandleExpose(%d,%d,%u,%u)\n", GetName(), x, y,
	    width, height);
#endif

	// Fix for bug 750.  RKW 2002-02-05.
    if (IsChildView() && RefreshPending()) {
	  return;
	}

	// In case record links didn't get re-enabled after printing.
	RecordLink::EnableUpdates();

#if USE_BUG123_WORKAROUND
	// If we have backing store, all Expose events should be for the whole view
	if (GetWindowRep()->HasBackingStore())
	{
		int				viewX, viewY;
		unsigned int	viewWidth, viewHeight;

		Geometry(viewX, viewY, viewWidth, viewHeight);

		if ((viewX != x) || (viewY != y) ||
			(viewWidth != width) || (viewHeight != height))
		{
#if defined(DEBUG)
			printf("View(%s)::HandleExpose() ignoring Expose event\n",
				   GetName());
#endif
			return;
		}
	}
#endif

	if (!_hasExposure)
	{
		_hasExposure = true;
		_exposureRect.xLow = x;
		_exposureRect.yLow = y;
		_exposureRect.xHigh = x + width - 1;
		_exposureRect.yHigh = y + height - 1;
	}
	else								// Merge with existing exposed region
	{
		int		minX1 = _exposureRect.xLow;
		int		minY1 = _exposureRect.yLow;
		int		maxX1 = _exposureRect.xHigh;
		int		maxY1 = _exposureRect.yHigh;
    
		int		minX2 = x;
		int		minY2 = y;
		int		maxX2 = x + width - 1;
		int		maxY2 = y + height - 1;

		_exposureRect.xLow = MIN(minX1, minX2);
		_exposureRect.yLow = MIN(minY1, minY2);
		_exposureRect.xHigh = MAX(maxX1, maxX2);
		_exposureRect.yHigh = MAX(maxY1, maxY2);
	}

	DepMgr::Current()->RegisterEvent(dispatcherCallback,
									 DepMgr::EventViewExpose);
  Refresh(true);
}

void	View::HandleResize(WindowRep* w, int xlow, int ylow,
						   unsigned width, unsigned height)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
	printf("View(%s)::HandleResize(%d,%d,%d,%d)\n", GetName(), xlow, ylow,
		   width, height);
    printf("  Old size: %d, %d, %d, %d\n", _x, _y, _width, _height);
#endif
#if defined(DEBUG_LOG)
    char logBuf[1024];
    int formatted = snprintf(logBuf, sizeof(logBuf),
          "View(%s)::HandleResize(%d,%d,%d,%d)\n", GetName(),
	  xlow, ylow, width, height);
    checkAndTermBuf2(logBuf, formatted);
    DebugLog::DefaultLog()->Message(DebugLog::LevelInfo2, logBuf);
#endif

	// In case record links didn't get re-enabled after printing.
	RecordLink::EnableUpdates();
  
	// Is this a real size change?
	if (_hasGeometry && (_x == xlow) && (_y == ylow) &&
		(_width == width) && (_height == height)) {
#if defined(DEBUG_LOG)
    formatted = snprintf(logBuf, sizeof(logBuf),
        "  Done with View::HandleResize()\n");
    checkAndTermBuf2(logBuf, formatted);
    DebugLog::DefaultLog()->Message(DebugLog::LevelInfo2, logBuf);
#endif
		return;
    }

	ViewWin::HandleResize(w, xlow, ylow, width, height);
	_updateTransform = true;// Update the transformation
	DepMgr::Current()->RegisterEvent(dispatcherCallback, 
									 DepMgr::EventViewResize);
    Refresh(true);

#if defined(DEBUG_LOG)
    formatted = snprintf(logBuf, sizeof(logBuf),
	    "  Done with View::HandleResize()\n");
	checkAndTermBuf2(logBuf, formatted);
    DebugLog::DefaultLog()->Message(DebugLog::LevelInfo2, logBuf);
#endif
}

void
View::IsOnCursor(int pixX, int pixY, CursorHit &cursorHit)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::IsOnCursor(%d, %d)\n", GetName(), pixX, pixY);
#endif

  cursorHit._hitType = CursorHit::CursorNone;
  cursorHit._cursor = NULL;

  if (GetCursorMoveDisabled()) {
    return;
  }

  if (IsInPileMode()) {
    GetParentPileStack()->IsOnCursor(pixX, pixY, cursorHit);
  } else {
    DoIsOnCursor(pixX, pixY, cursorHit);
  }
}

void
View::DoIsOnCursor(int pixX, int pixY, CursorHit &cursorHit)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::DoIsOnCursor(%d, %d)\n", GetName(), pixX, pixY);
#endif

  int daX, daY, daWidth, daHeight;
  GetDataArea(daX, daY, daWidth, daHeight);

  int winX, winY;
  unsigned winWidth, winHeight;
  Geometry(winX, winY, winWidth, winHeight);
  daY = winHeight - daHeight - daY;

  if (pixX < daX || pixX > daX + daWidth - 1 || pixY < daY ||
      pixY > daY + daHeight - 1) {
	// Mouse is outside of data area.
    return;
  }

  //
  // How close you have to be to "catch" an edge.
  //
  const int pixTol = 4;

  //
  // Convert pixel coordinates to data coordinates, and figure out the
  // tolerance for "catching" an edge.
  //
  Coord dataX, dataY, dataX2, dataY2;
  WindowRep *winRep = GetWindowRep();
  winRep->InverseTransform(pixX, pixY, dataX, dataY);
  winRep->InverseTransform(pixX + pixTol, pixY + pixTol, dataX2, dataY2);


  //
  // Go thru all cursors and see if we're on one.
  //
  int index = _cursors->InitIterator();
  while (_cursors->More(index) &&
      cursorHit._hitType == CursorHit::CursorNone) {
    DeviseCursor *tmpCursor = _cursors->Next(index);
    cursorHit._hitType = tmpCursor->IsOnCursor(dataX, dataY, dataX - dataX2,
        dataY - dataY2);
    if (cursorHit._hitType != CursorHit::CursorNone) {
      cursorHit._cursor = tmpCursor;
    }
  }
  _cursors->DoneIterator(index);
}

void
View::MouseDrag(int x1, int y1, int x2, int y2, int button)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  // Note: we can't print here, because that causes the display to lock up.
  const int bufLen = 256;
  char buf[bufLen];
  int formatted = snprintf(buf, bufLen,
      "View(%s)::MouseDrag(%d, %d, %d, %d, %d)\n", GetName(), x1, y1, x2,
      y2, button);
  checkAndTermBuf(buf, bufLen, formatted);
  DebugLog::DefaultLog()->Message(DebugLog::LevelInfo1, buf);
#endif

  WindowRep *winRep = GetWindowRep();

  CursorHit::HitType hitType = WindowRep::GetCursorHit()._hitType;
  if (hitType == CursorHit::CursorNone) {
    if (button == 1) { // X-only zoom
      y1 = 0;
      y2 = MAXINT;
    }

    (void) ForceIntoDataArea(x1, y1);
    (void) ForceIntoDataArea(x2, y2);
    if (x1 != x2 && y1 != y2 && !GetRubberbandDisabled()) {
      winRep->DrawRubberband(x1, y1, x2, y2);
    }
  } else {
    DeviseCursor *cursor = WindowRep::GetCursorHit()._cursor;
    DOASSERT(cursor, "No cursor specified");
    if (cursor->GetDst() != this) {
      cursor->GetDst()->MouseDrag(x1, y1, x2, y2, button);
    } else {
      Coord dataXLow, dataYLow, dataXHigh, dataYHigh;
      cursor->FindNewPosition(x1, y1, x2, y2, hitType, dataXLow, dataYLow,
          dataXHigh, dataYHigh);
      int x3, y3, x4, y4;
	  if (cursor->GetDestPixels(dataXLow, dataYLow, dataXHigh, dataYHigh,
	      x3, y3, x4, y4)) {
        winRep->DrawRubberband(x3, y3, x4, y4);
	  }
    }
  }
}

void View::SetViewDir(ViewDir dir)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  Camera c;
  c.view_dir=dir;
  c.pan_right=0.0;
  c.pan_up=0.0;
  SetCamera(c);
}

Boolean
View::GetJS3dConfig(float data[3][3], float origin[3],
    float &shiftedX, float &shiftedY)
{
#if defined(DEBUG)
  printf("View(%s)::GetJS3dConfig()\n", GetName());
#endif

  Boolean result = false;

  if (_3dValid) {
    for (int i1 = 0; i1 < 3; i1++) {
      for (int i2 = 0; i2 < 3; i2++) {
	    data[i1][i2] = _3dData[i1][i2];
	  }
	   origin[i1] = _3dOrigin[i1];
    }
    shiftedX = _3dShiftedX;
    shiftedY = _3dShiftedY;

    result = true;
  }

  return result;
}

void
View::SetJS3dConfig(const float data[3][3], const float origin[3],
    float shiftedX, float shiftedY)
{
#if defined(DEBUG)
  printf("View(%s)::SetJS3dConfig()\n", GetName());
#endif

  for (int i1 = 0; i1 < 3; i1++) {
    for (int i2 = 0; i2 < 3; i2++) {
	  _3dData[i1][i2] = data[i1][i2];
	}
	_3dOrigin[i1] = origin[i1];
  }
  _3dShiftedX = shiftedX;
  _3dShiftedY = shiftedY;

  _3dValid = true;
}

View *
View::FindSelectedView()
{
  View *selectedView = NULL;
  int index = InitViewIterator();
  while (MoreView(index) && selectedView == NULL) {
    View *tmpView = NextView(index);
    if (tmpView->IsSelected()) selectedView = tmpView;
  }
  DoneViewIterator(index);

  return selectedView;
}

void
View::SelectView(Boolean calledFromPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View(%s)::SelectView(%d)\n", GetName(), calledFromPile);
#endif

  if (IsInPileMode() && !calledFromPile) {
    GetParentPileStack()->SelectView();
    return;
  }

  // Unhighlight previously-selected view, if any, and highlight the
  // newly-selected view (do nothing if they are the same view).
  View *prevSelView = FindSelectedView();
  if (prevSelView != this) {
    if (prevSelView != NULL) prevSelView->DoSelect(false);
    DoSelect(true);
  }
  ControlPanel::Instance()->SelectView(this);
}

// Select the next view in the pile that the currently-selected view
// belongs to (if the currently-selected view is not in a pile, do
// nothing; if there is no currently-selected view, do nothing).
void
View::SelectNextInPile()
{
#if defined(DEBUG)
  printf("View::SelectNextInPile()\n");
#endif

  View *selView = FindSelectedView();

#if defined(DEBUG)
  printf("  Currently-selected view is %s\n",
      selView ? selView->GetName() : "none");
#endif

  if (selView) {
    PileStack *ps = selView->GetParentPileStack();
	if (ps && ps->IsPiled()) {
	  ViewWin *nextView = NULL;

	  int it = ps->InitIterator();
	  while (ps->More(it) && nextView == NULL) {
	    ViewWin *tmpView = ps->Next(it);
	    if (tmpView == selView) {
		  if (ps->More(it)) {
		    nextView = ps->Next(it);
		  } else {
		    nextView = ps->GetFirstView();
		  }
	    }
	  }
	  ps->DoneIterator(it);

#if defined(DEBUG)
  printf("  View to select next is %s\n",
      nextView ? nextView->GetName() : "none");
#endif

	  // Note: must pass in true here to keep from selecting the first
	  // view in the pile.
	  ((View *)nextView)->SelectView(true);
	}
  }
}

// Select the parent view of the currently-selected view (if the
// currently-selected view has no parent, do nothing; if there is no
// currently-selected view, do nothing).
void
View::SelectParent()
{
#if defined(DEBUG)
  printf("View::SelectParent()\n");
#endif

  View *selView = FindSelectedView();

#if defined(DEBUG)
  printf("  Currently-selected view is %s\n",
      selView ? selView->GetName() : "none");
#endif

  if (selView) {
    ViewWin *parent = selView->GetParent();
    if (parent) {
	  // Figure out whether the parent is a view or a window -- if the
	  // parent has no parent, it is a window and we can't select it.
	  if (parent->GetParent() == NULL) {
	    printf("Currently-selected view <%s> has no parent view\n",
		    selView->GetName());
	  } else {
#if defined(DEBUG)
        printf("  View to select next is %s\n",
            parent ? parent->GetName() : "none");
#endif
	    // Note: must pass in true here to keep from selecting the first
	    // view in the pile.
	    ((View *)parent)->SelectView(true);
	  }
    }
  }
}

// Select the first child view (if any) of the currently-selected
// view (if the currently-selected view has no children, do nothing;
// if there is no currently-selected view, do nothing).
void
View::SelectFirstChild()
{
#if defined(DEBUG)
  printf("View::SelectFirstChild()\n");
#endif

  View *selView = FindSelectedView();

#if defined(DEBUG)
  printf("  Currently-selected view is %s\n",
      selView ? selView->GetName() : "none");
#endif

  if (selView) {
    int index = selView->InitIterator();
	if (!selView->More(index)) {
	    printf("Currently-selected view <%s> has no children\n",
		    selView->GetName());
	} else {
	  ViewWin *nextView = selView->Next(index);

#if defined(DEBUG)
      printf("  View to select next is %s\n",
          nextView ? nextView->GetName() : "none");
#endif

	  // Note: must pass in true here to keep from selecting the first
	  // view in the pile.
	  ((View *)nextView)->SelectView(true);
	}
	selView->DoneIterator(index);
  }
}

// Select the next child of the currently-selected view's parent (if
// the currently-selected view is not a child view, or is the last child
// view of its parent, do nothing; if there is no currently-selected view,
// do nothing).
void
View::SelectNextChild()
{
#if defined(DEBUG)
  printf("View::SelectNextChild()\n");
#endif

  View *selView = FindSelectedView();

#if defined(DEBUG)
  printf("  Currently-selected view is %s\n",
      selView ? selView->GetName() : "none");
#endif

  if (selView) {
    ViewWin *parent = selView->GetParent();
    if (parent) {
	  // Figure out whether the parent is a view or a window -- if the
	  // parent has no parent, it is a window and we can't select it.
	  if (parent->GetParent() == NULL) {
	    printf("Currently-selected view <%s> has no parent view\n",
		    selView->GetName());
	  } else {
		// Find the next child of the parent view.
		ViewWin *nextView = NULL;
	    int index = parent->InitIterator();
		while (parent->More(index)) {
		  ViewWin *tmpView = parent->Next(index);
		  if (tmpView == selView) {
		    if (!parent->More(index)) {
			  printf("Currently-selected view <%s> is last child of "
			      "its parent\n", selView->GetName());
			} else {
			  nextView = parent->Next(index);
			}
			break;
		  }
		}
		parent->DoneIterator(index);

		if (nextView) {
#if defined(DEBUG)
          printf("  View to select next is %s\n",
              nextView ? nextView->GetName() : "none");
#endif
	      // Note: must pass in true here to keep from selecting the first
	      // view in the pile.
	      ((View *)nextView)->SelectView(true);
	    }
	  }
    }
  }
}

// Clear the visual filter histories of all views.
void
View::ClearGlobalFilterHistory()
{
  int index = InitViewIterator();
  while (MoreView(index)) {
    View *view = NextView(index);
    view->ClearHistory();
  }
  DoneViewIterator(index);
}

void
View::SetShowNames(Boolean showNames)
{
#if defined(DEBUG)
  printf("View::SetShowNames(%d)\n", showNames);
#endif

  if (showNames != false) showNames = true;
  if (showNames != _showNames) {
	_showNames = showNames;
	RefreshAll();
  }
}

void
View::SetAutoUpdate(Boolean autoUpdate)
{
  _autoUpdate = autoUpdate;
  if (autoUpdate && (_viewSymSaveX || _viewSymSaveY)) {
    printf("Warning (view %s): automatic filter updating and saving "
         "view symbol filters are both enabled -- this may produce "
	 "unpredictable behavior\n", GetName());
  }
}

void
View::SetXAxisDateFormat(const char *format, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (_pileMode && notifyPile) {
    GetParentPileStack()->SetXAxisDateFormat(format);
  } else {
    _xAxis.SetDateFormat(format);
    Refresh();
  }
}

void
View::SetYAxisDateFormat(const char *format, Boolean notifyPile)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (_pileMode && notifyPile) {
    GetParentPileStack()->SetYAxisDateFormat(format);
  } else {
    _yAxis.SetDateFormat(format);
    Refresh();
  }
}

void
View::SetXAxisFloatFormat(const char *format, Boolean notifyPile)
{
#if defined(DEBUG)
  printf("View(%s)::SetXAxisFloatFormat(%s)\n", GetName(), format);
#endif

  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (_pileMode && notifyPile) {
    GetParentPileStack()->SetXAxisFloatFormat(format);
  } else {
    _xAxis.SetFloatFormat(format);
    Refresh();
  }
}

void
View::SetYAxisFloatFormat(const char *format, Boolean notifyPile)
{
#if defined(DEBUG)
  printf("View(%s)::SetYAxisFloatFormat(%s)\n", GetName(), format);
#endif

  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (_pileMode && notifyPile) {
    GetParentPileStack()->SetYAxisFloatFormat(format);
  } else {
    _yAxis.SetFloatFormat(format);
    Refresh();
  }
}

void
View::CleanUpViewSyms()
{
#if defined(DEBUG)
  printf("View(%s)::CleanUpViewSyms()\n", GetName());
#endif

  int index = InitIterator();
  while (More(index)) {
    ViewWin *view = Next(index);
    if (view->GetParentPileStack()) {
      view->GetParentPileStack()->DeleteView(view);
    }
    ((View *)view)->SetChildView(false);
  }
  DoneIterator(index);
  DetachChildren();
}

void
View::InvalidateCursors()
{
#if defined(DEBUG)
  printf("View(%s)::InvalidateCursors()\n", GetName());
#endif

  _cursorsOn = false;

  int cursorIndex = _cursors->InitIterator();
  while (_cursors->More(cursorIndex)) {
    DeviseCursor *cursor = _cursors->Next(cursorIndex);
    cursor->InvalidateOldDestPixels();
  }
  _cursors->DoneIterator(cursorIndex);
}

void
View::ShowMouseLocation(int *mouseX, int *mouseY)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
#if defined(DEBUG)
  printf("View::ShowMouseLocation(");
  if (mouseX) {
    printf("%d, ", *mouseX);
  } else {
    printf("NULL, ");
  }
  if (mouseY) {
    printf("%d", *mouseY);
  } else {
    printf("NULL");
  }
  printf(")\n");
#endif

  if ((_showMouseLocation == 0) || (_globalShowMouseLocation == 0)) return;

  Coord dataX = 0.0;
  Coord dataY = 0.0;
  if (mouseX || mouseY) {
    WindowRep *wr = GetWindowRep();

    Coord tmpX, tmpY;
    if (mouseX) {
      tmpX = *mouseX;
    } else {
      tmpX = 0.0;
    }

    if (mouseY) {
      tmpY = *mouseY;
    } else {
      tmpY = 0.0;
    }

    wr->InverseTransform(tmpX, tmpY, dataX, dataY);
#if defined(DEBUG)
    printf("  data x, y: %g, %g\n", dataX, dataY);
#endif

    VisualFilter filter;
    GetVisualFilter(filter);
    if (!InVisualFilter(filter, dataX, dataY)) {
      mouseX = NULL;
	  mouseY = NULL;
    }
  }

  dataX *= _xAxis.GetMultFactor();
  dataY *= _yAxis.GetMultFactor();

  if ((_showMouseLocation != 1) && (_showMouseLocation != 2)) {
    mouseX = NULL;
  }
  if ((_globalShowMouseLocation != 1) && (_globalShowMouseLocation != 2)) {
    mouseX = NULL;
  }

  if ((_showMouseLocation != 1) && (_showMouseLocation != 3)) {
    mouseY = NULL;
  }
  if ((_globalShowMouseLocation != 1) && (_globalShowMouseLocation != 3)) {
    mouseY = NULL;
  }

  const int mouseFieldWidth = 6;
  const int mouseFieldPrec = 4;
  char xBuf[32], yBuf[32];
  int formatted;
  if (mouseX) {
	if (GetXAxisAttrType() == DateAttr) {
	  formatted = snprintf(xBuf, sizeof(xBuf), "%s",
	      DateString((time_t)dataX, GetXAxisDateFormat()));
	} else {
	  if (!strcmp(GetXAxisFloatFormat(), DevAxis::_blankFloatFormat)) {
        formatted = snprintf(xBuf, sizeof(xBuf), "%*s", mouseFieldWidth, "");
	  } else {
        formatted = snprintf(xBuf, sizeof(xBuf), GetXAxisFloatFormat(), dataX);
	  }
	}
  } else {
    formatted = snprintf(xBuf, sizeof(xBuf), "%*s", mouseFieldWidth, "");
  }
  checkAndTermBuf2(xBuf, formatted);

  if (mouseY) {
	if (GetYAxisAttrType() == DateAttr) {
	  formatted = snprintf(yBuf, sizeof(yBuf), "%s",
	      DateString((time_t)dataY, GetYAxisDateFormat()));
	} else {
	  if (!strcmp(GetYAxisFloatFormat(), DevAxis::_blankFloatFormat)) {
        formatted = snprintf(yBuf, sizeof(yBuf), "%*s", mouseFieldWidth, "");
	  } else {
        formatted = snprintf(yBuf, sizeof(yBuf), GetYAxisFloatFormat(), dataY);
	  }
	}
  } else {
    formatted = snprintf(yBuf, sizeof(yBuf), "%*s", mouseFieldWidth, "");
  }
  checkAndTermBuf2(yBuf, formatted);

  ControlPanel::Instance()->ShowMouseLocation(xBuf, yBuf);
}

void
View::EnableDrawing(Boolean enable)
{
  if (enable != _drawingEnabled) {
    if (enable) {
	  RefreshAll();
    } else {
	  int index = InitViewIterator();
	  while (MoreView(index)) {
	    View *tmpView = NextView(index);
		tmpView->AbortQuery();
	  }
	  DoneViewIterator(index);
	  //TEMP -- we might want to clear all views here
    }
    _drawingEnabled = enable;
  }
}

Boolean
View::ForceIntoDataArea(int &x, int &y)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  Boolean result = false;

  int dataX, dataY, dataWidth, dataHeight;
  GetDataArea(dataX, dataY, dataWidth, dataHeight);

  // Correct for the fact that GetDataArea expresses Y up from the bottom(!!).
  int viewX, viewY;
  unsigned int viewWidth, viewHeight;
  Geometry(viewX, viewY, viewWidth, viewHeight);
  int dataY2 = viewHeight - (dataY + dataHeight);

  if (x < dataX) {
    x = dataX;
    result = true;
  } else if (x > dataX + dataWidth - 1) {
    x = dataX + dataWidth - 1;
    result = true;
  }

  if (y < dataY2 - 1) {
    y = dataY2 - 1;
    result = true;
  } else if (y > dataY2 + dataHeight - 1) {
    y = dataY2 + dataHeight - 1;
    result = true;
  }

  return result;
}

void
View::SetViewHelp(const char *helpStr)
{
  DOASSERT(_objectValid.IsValid(), "operation on invalid object");
  if (_viewHelp) FreeString((char *)_viewHelp);
  _viewHelp = CopyString(helpStr);
}

void
View::SetFilterChangeCmds(const char *cmds)
{
	FreeString(_filterChangeCmds);
	_filterChangeCmds = CopyString(cmds);
}

void
View::SaveCursorState()
{
#if defined(DEBUG)
  printf("View(%s)::SaveCursorState()\n", GetName());
#endif

  int index = _cursors->InitIterator();
  while (_cursors->More(index)) {
    DeviseCursor *cursor = _cursors->Next(index);
    DOASSERT(cursor, "Invalid cursor");
    cursor->SaveState();
  }
  _cursors->DoneIterator(index);
}

void
View::RestoreCursorState()
{
#if defined(DEBUG)
  printf("View(%s)::RestoreCursorState()\n", GetName());
#endif

  int index = _cursors->InitIterator();
  while (_cursors->More(index)) {
    DeviseCursor *cursor = _cursors->Next(index);
    DOASSERT(cursor, "Invalid cursor");
    cursor->RestoreState();
  }
  _cursors->DoneIterator(index);
}

void
View::GeometryWithHighlight(int &x, int &y, unsigned &w, unsigned &h)
{
  Geometry(x, y, w, h);

  // Note: we're assuming here that half of the highlight line is actually
  // "drawn" outside the window.
  x += halfHighlightWidth;
  y += halfHighlightWidth;
  w -= halfHighlightWidth * 2;
  h -= halfHighlightWidth * 2;
}

unsigned int
View::GetLabelHeight()
{
  unsigned int height;

  if (_label.occupyTop) {
    height = _label.extent;
  } else {
    height = 0;
  }

  return height;
}

unsigned int
View::GetXAxisHeight()
{
  unsigned int height;

  if (_xAxis.IsInUse()) {
    height = _xAxis.Width();
  } else {
    height = 0;
  }

  return height;
}

unsigned int
View::GetYAxisWidth()
{
  unsigned int width;

  if (_yAxis.IsInUse()) {
    width = _yAxis.Width();
  } else {
    width = 0;
  }

  return width;
}

//******************************************************************************
