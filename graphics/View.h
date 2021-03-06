/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2010
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
  Revision 1.128.6.5  2010/08/31 17:28:22  wenger
  Changed the names of some of the new commands and methods to better
  reflect their functions; documented the new methods.  (Note: cursor
  mods still don't always work right for ambiguity code and Pistachio
  visualizations.)

  Revision 1.128.6.4  2010/08/24 20:38:26  wenger
  Added the getViewSaveState, setViewSaveState, getCursorSaveState,
  setCursorSaveState, getCursorKeepProp, and setCursorKeepProp commands
  to control the new view and cursor properties.

  Revision 1.128.6.3  2010/08/19 18:28:31  wenger
  Added class variables to control the new cursor and view symbol
  behaviors (but not the commands to set them yet) -- Y stuff for the
  cursors are temporarily turned on.

  Revision 1.128.6.2  2010/08/19 16:50:07  wenger
  Did some cleanup of the 3D cursor fixes -- no real functional changes,
  mainly changing some method and variable names to better match the
  current functionality.

  Revision 1.128.6.1  2010/08/18 21:10:18  wenger
  Working on 3D cursor fixes -- I have a (preliminary?) implementation
  here that saves the cursor proportions relative to the destination
  view when you change TData and/or parent value for the destination
  view.  (This commit also includes loads of debug code, and turning
  off the earlier feature of trying to save view filters by TData/
  parent value.)

  Revision 1.128  2009/09/23 21:39:29  wenger
  Added clearGlobalFilterHistory command to clean up session files
  (especially for things like Peptide-CGI templates).

  Revision 1.127  2009/09/23 20:39:02  wenger
  Added the selectParent, selectFirstChild, and selectNextChild
  commands to help in editing complex sessions.

  Revision 1.126  2009/09/23 17:05:37  wenger
  Partial implementation of the 'filter change command' idea -- view
  has command it's saved in sessions, parsed, but not actually
  executed.  GUI for creating the command is partly done (but
  commented out).

  Revision 1.125  2009/05/15 20:29:39  wenger
  Implemented to-do 04.001 (be able to exclude views from drill-down;
  this is needed to fix Peptide-CGI bug 071); also fixed some dangerous
  code (strcpy, strcat) in Session.c; added GUI for setting drill-down
  exclusion and copying it when copying a view.

  Revision 1.124  2008/09/23 22:55:34  wenger
  More const-ifying, especially drill-down-related stuff.

  Revision 1.123  2008/09/23 19:32:39  wenger
  Changed DispatchedName() to const char *.

  Revision 1.122  2006/05/26 16:22:57  wenger
  Merged devise_jmol_br_0 thru devise_jmol_br_1 to the trunk.

  Revision 1.121.4.1  2006/02/23 22:08:58  wenger
  Added flag for whether or not 3D views should use Jmol.

  Revision 1.121  2005/12/06 20:03:11  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.120  2003/01/13 19:25:12  wenger
  Merged V1_7b0_br_3 thru V1_7b0_br_4 to trunk.

  Revision 1.119.4.6  2005/09/06 21:20:10  wenger
  Got DEVise to compile with gcc 4.0.1.

  Revision 1.119.4.5  2004/04/23 21:57:08  wenger
  Added new 'select next view in pile' feature.

  Revision 1.119.4.4  2003/11/05 17:01:44  wenger
  First part of display modes for printing is implemented (view foreground
  and background colors work, haven't done anything for symbol colors yet).

  Revision 1.119.4.3  2003/01/09 22:21:52  wenger
  Added "link multiplication factor" feature; changed version to 1.7.14.

  Revision 1.119.4.2  2003/01/04 21:38:27  wenger
  Fixed bugs 852, 855, and 856 (all related to view geometry and transforms
  and axis drawing).

  Revision 1.119.4.1  2002/08/23 17:45:08  wenger
  Fixed bug 812 (problem with drawing piles when a piled view has
  auto filter update turned on).

  Revision 1.119  2001/12/13 21:35:48  wenger
  Added flexibility to enable/disable mouse location display individually
  for X and Y axes (needed for peptide-cgi session improvements requested
  by John Markley).

  Revision 1.118  2001/09/26 16:31:30  wenger
  Fixed bug 693 (DEVise rubberband line now reflects X-only zoom).

  Revision 1.117  2001/05/03 19:39:02  wenger
  Changed negative axis flag to multiplicative factor to be more flexible;
  pass multiplicative factor to JS to correct mouse location display (mods
  to JAVAC_ViewDataArea command); corrected mouse location display in DEVise
  Tcl GUI.

  Revision 1.116  2001/04/23 18:58:32  wenger
  Added negative axis label option (no GUI yet) to allow us to display
  chemical shifts the way the BMRB people want.

  Revision 1.115  2001/04/02 16:09:49  wenger
  Devised now saves configuration for 3D JavaScreen views to sessions,
  and passes it to the JavaScreen when necessary (note: JS protocol
  version is now 6.0).

  Revision 1.114  2001/02/20 20:02:44  wenger
  Merged changes from no_collab_br_0 thru no_collab_br_2 from the branch
  to the trunk.

  Revision 1.113.2.1  2001/02/16 21:37:50  wenger
  Updated DEVise version to 1.7.2; implemented 'forward' and 'back' (like
  a web browser) on 'sets' of visual filters.

  Revision 1.113  2001/01/08 20:32:43  wenger
  Merged all changes thru mgd_thru_dup_gds_fix on the js_cgi_br branch
  back onto the trunk.

  Revision 1.111.2.1  2000/12/27 19:38:57  wenger
  Merged changes from js_restart_improvements thru zero_js_cache_check from
  the trunk onto the js_cgi_br branch.

  Revision 1.112  2000/11/17 22:59:00  wenger
  Fixed problems with command logging of cursor movements and pile/stack
  flips.

  Revision 1.111  2000/07/17 16:07:46  wenger
  Added visual filter info to metavisualization session description.

  Revision 1.110  2000/07/12 20:49:15  wenger
  Added first version of metavisualization session description; changed
  DEVise version to 1.7.1.

  Revision 1.109  2000/06/20 22:16:56  wenger
  Added floating-point format for axes and mouse location display.

  Revision 1.108  2000/06/20 16:57:34  wenger
  Added commands and GUI to enable/disable the display of mouse location
  in various views, and globally.

  Revision 1.107  2000/03/21 17:12:26  wenger
  Removed various unused methods from the View class.

  Revision 1.106  2000/03/21 16:24:47  wenger
  'f' or 'F' key in a view now flips the appropriate pile or stack, if
  there is one.

  Revision 1.105  2000/03/14 21:51:38  wenger
  Added more invalid object checking; had to take some memory checking
  out of client-side stuff for linking reasons.

  Revision 1.104  2000/03/14 17:05:14  wenger
  Fixed bug 569 (group/ungroup causes crash); added more memory checking,
  including new FreeString() function.

  Revision 1.103  2000/02/15 16:16:16  wenger
  Cursors in child views "remember" their size and location when
  switching TDatas or parent attributes.

  Revision 1.102  2000/02/08 22:11:50  wenger
  Added JAVAC_GetViewHelp and JAVAC_ShowViewHelp commands, added color
  edge grid, and type to JAVAC_DrawCursor command, JavaScreen protocol
  version now 4.0; added GUI to edit view help, and commands to save it
  to session files.

  Revision 1.101  1999/12/15 16:25:44  wenger
  Fixed bugs 543 and 544 (problems with cursor movement).

  Revision 1.100  1999/12/14 17:57:19  wenger
  Added enableDrawing command (totally enables or disables drawing) to
  allow Omer to avoid "flashing" when he inserts views into windows.

  Revision 1.99  1999/11/19 17:17:31  wenger
  Added View::SetVisualFilterCommand() method to clean up command-related
  code for filter setting.

  Revision 1.98  1999/11/10 18:48:36  wenger
  Changing view dimenion now changes all views in a pile; PileStack makes
  sure all views in pile have the same number of dimensions; fixed 'bad
  query' problem with highlight views.

  Revision 1.97  1999/10/22 20:54:03  wenger
  Major changes to how view refreshes are handled (prevents "extra" queries
  from being run in piled views, fixes bug 520); also fixed bug 517.

  Revision 1.96  1999/10/08 19:57:46  wenger
  Fixed bugs 470 and 513 (crashes when closing a session while a query
  is running), 510 (disabling actions in piles), and 511 (problem in
  saving sessions); also fixed various problems related to cursors on
  piled views.

  Revision 1.95  1999/10/04 19:36:58  wenger
  Mouse location is displayed in "regular" DEVise.

  Revision 1.94  1999/08/31 21:46:18  wenger
  Found and fixed bug 506 (problem with cursor drawing when source and
  destination views are in the same window).

  Revision 1.93  1999/08/18 20:46:06  wenger
  First step for axis drawing improvement: moved code to new DevAxis
  class with unchanged functionality.

  Revision 1.92  1999/08/05 21:42:37  wenger
  Cursor improvements: cursors can now be dragged in "regular" DEVise;
  cursors are now drawn with a contrasting border for better visibility;
  fixed bug 468 (cursor color not working).

  Revision 1.91  1999/07/30 21:27:05  wenger
  Partway to cursor dragging: code to change mouse cursor when on a DEVise
  cursor is in place (but disabled).

  Revision 1.90  1999/07/21 18:51:02  wenger
  Moved alignment and data font information from view into mapping.

  Revision 1.89  1999/07/14 18:42:41  wenger
  Added the capability to have axes without ticks and tick labels.

  Revision 1.88  1999/06/11 14:46:55  wenger
  Added the capability (mostly for the JavaScreen) to disable rubberband
  lines, cursor movement, drill down, and key actions in views (the code
  to send this info to the JS is still conditionaled out until the JS is
  ready for it).

  Revision 1.87  1999/06/04 16:32:01  wenger
  Fixed bug 495 (problem with cursors in piled views) and bug 496 (problem
  with key presses in piled views in the JavaScreen); made other pile-
  related improvements (basically, I removed a bunch of pile-related code
  from the XWindowRep class, and implemented that functionality in the
  PileStack class).

  Revision 1.86  1999/05/14 13:59:54  wenger
  User can now control data font family, weight, and slant, on a per-view
  basis.

  Revision 1.85  1999/05/13 18:58:55  wenger
  Removed _queryFilter member from View class to avoid confusion with
  _queryFilter in ViewGraph.

  Revision 1.84  1999/05/12 21:01:02  wenger
  Views containing view symbols can now be piled.

  Revision 1.83  1999/05/07 14:13:45  wenger
  Piled view symbols now working: pile name is specified in parent view's
  mapping, views are piled by Z specified in parent's mapping; changes
  include improvements to the Dispatcher because of problems exposed by
  piled viewsyms; for now, view symbol piles are always linked (no GUI or
  API to change this).

  Revision 1.82  1999/05/04 17:17:01  wenger
  Merged js_viewsyms_br thru js_viewsyms_br_1 (code for new JavaScreen
  protocol that deals better with view symbols).

  Revision 1.81  1999/04/21 20:35:20  wenger
  Improved interface for changing fonts, titles, etc.:
  * Fonts can now be set on a window-wide basis.
  * Setting fonts, title, or axis date format in a piled view automatically
  changes all views in the pile accordingly.

  Revision 1.80  1999/04/16 20:59:14  wenger
  Fixed various bugs related to view symbols, including memory problem
  with MappingInterp dimensionInfo; updated create_condor_session script
  to take advantage of view symbol TData switching capability.

  Revision 1.79  1999/04/05 16:15:50  wenger
  Record- and set-link follower views with auto filter update enabled have
  'home' done on them after they are updated by a record link or set link.

  Revision 1.78  1999/03/04 15:11:01  wenger
  Implemented 'automatic filter update' features: views can be designated
  to have their visual filters automatically updated with the 'Update
  Filters' menu selection; alternatively, a session can be opened with
  the 'Open, Update, and Save' selection, which updates the designated
  filters and saves the updated session.

  Revision 1.77  1999/03/01 23:09:01  wenger
  Fixed a number of memory leaks and removed unused code.

  Revision 1.76.2.1  1999/03/17 15:16:23  wenger
  Added view Z coordinate to JAVAC_CreateView command, so the JavaScreen
  knows which views are on top of piles, etc.

  Revision 1.76  1999/02/23 15:35:01  wenger
  Fixed bugs 446 and 465 (problems with cursors in piles); fixed some
  other pile-related problems.

  Revision 1.75  1999/02/22 19:07:37  wenger
  Piling of views with view symbols is not allowed; fixed bug 461 (redrawing
  of piles); fixed bug 464 (toggling axes in a pile); fixed dynamic memory
  problems in PileStack and ViewClassInfo classes.

  Revision 1.74  1999/02/17 15:10:18  wenger
  Added "Next in Pile" button to query dialog; more pile fixes; fixed bug
  in mapping dialog updating when a view is selected.

  Revision 1.73  1999/02/11 19:54:38  wenger
  Merged newpile_br through newpile_br_1 (new PileStack class controls
  pile and stacks, allows non-linked piles; various other improvements
  to pile-related code).

  Revision 1.72  1999/02/01 23:13:35  wenger
  Backspace key in a view goes back one in the visual filter history.

  Revision 1.71.2.2  1999/02/11 18:24:07  wenger
  PileStack objects are now fully working (allowing non-linked piles) except
  for a couple of minor bugs; new PileStack state is saved to session files;
  piles and stacks in old session files are dealt with reasonably well;
  incremented version number; added some debug code.

  Revision 1.71.2.1  1998/12/29 17:24:47  wenger
  First version of new PileStack objects implemented -- allows piles without
  pile links.  Can't be saved or restored in session files yet.

  Revision 1.71  1998/12/22 19:39:14  wenger
  User can now change date format for axis labels; fixed bug 041 (axis
  type not being changed between float and date when attribute is changed);
  got dates to work semi-decently as Y axis labels; view highlight is now
  always drawn by outlining the view; fixed some bugs in drawing the highight.

  Revision 1.70  1998/12/18 22:20:52  wenger
  Removed axis label code, which doesn't seem to have been fully implemented,
  and is not used; added sanity check on visual filter at view creation.

  Revision 1.69  1998/11/11 14:30:46  wenger
  Implemented "highlight views" for record links and set links; improved
  ClassDir::DestroyAllInstances() by having it destroy all links before
  it destroys anything else -- this cuts down on propagation problems as
  views are destroyed; added test code for timing a view's query and draw.

  Revision 1.68  1998/10/20 19:46:05  wenger
  Mapping dialog now displays the view's TData name; "Next in Pile" button
  in mapping dialog allows user to edit the mappings of all views in a pile
  without actually flipping them; user has the option to show all view names;
  new GUI to display info about all links and cursors; added API and GUI for
  count mappings.

  Revision 1.67  1998/09/08 20:26:02  wenger
  Added option to save which view is selected when saving a session -- for
  JavaScreen client switching support.

  Revision 1.66  1998/08/25 20:56:25  wenger
  Implemented support for JavaScreen cursors (not yet fully tested).

  Revision 1.65  1998/05/29 15:19:06  wenger
  Rubberband lines now work in JavaScreen, at least for single-window
  sessions.

  Revision 1.64  1998/05/06 22:04:45  wenger
  Single-attribute set links are now working except where the slave of
  one is the master of another.

  Revision 1.63  1998/05/05 15:14:51  zhenhai
  Implemented 3D Cursor as a rectangular block in the destination view
  showing left, right, top, bottom, front and back cutting planes of the
  source view.

  Revision 1.62  1998/03/18 08:19:44  zhenhai
  Added visual links between 3D graphics.

  Revision 1.61  1998/03/05 08:10:28  zhenhai
  Added ability to view 3D graphs from six directions. Use -gl option to run,
  and click key x,y,z and X,Y,Z to select the direction you are viewing.
  Use arrow keys to pan left right up and down.

  Revision 1.60  1998/02/26 00:19:05  zhenhai
  Implementation for spheres and line segments in OpenGL 3D graphics.

  Revision 1.59  1998/02/05 23:45:55  wenger
  Added view-level specification of symbol alignment, API commands, simple
  GUI for Sanjay.

  Revision 1.58  1998/01/27 23:04:37  wenger
  Broke the server's view selection dependency on the client (except when
  running in collaboration mode).

  Revision 1.57  1997/12/16 17:53:52  zhenhai
  Added OpenGL features to graphics.

  Revision 1.56  1997/12/12 05:50:22  weaver
  *** empty log message ***

  Revision 1.55  1997/11/24 23:14:35  weaver
  Changes for the new ColorManager.

  Revision 1.54  1997/09/05 22:36:06  wenger
  Dispatcher callback requests only generate one callback; added Scheduler;
  added DepMgr (dependency manager); various minor code cleanups.

  Revision 1.53  1997/08/20 22:10:41  wenger
  Merged improve_stop_branch_1 through improve_stop_branch_5 into trunk
  (all mods for interrupted draw and user-friendly stop).

  Revision 1.52.2.1  1997/08/14 16:15:52  wenger
  Statistics, etc., now work correctly for timed-out draw in ViewScatter-
  type views; bumped up version because of improved stop capability.

  Revision 1.52  1997/07/17 19:50:31  wenger
  Added menu selections to report number of strings and save string space.

  Revision 1.51  1997/05/28 15:38:58  wenger
  Merged Shilpa's layout manager code through the layout_mgr_branch_2 tag.

  Revision 1.50.4.1  1997/05/20 16:10:52  ssl
  Added layout manager to DEVise

  Revision 1.50.6.1  1997/05/21 20:40:03  weaver
  Changes for new ColorManager

  Revision 1.50  1997/02/03 19:40:01  ssl
  1) Added a new Layout interface which handles user defined layouts
  2) Added functions to set geometry and remap views as changes in the
     layout editor
  3) Added a function to notify the front end of some change so that it
     can execute a Tcl command
  4) The old TileLayout.[Ch] files still exist but are commented out
     conditionally using #ifdef NEW_LAYOUT

  Revision 1.49  1997/01/23 17:38:28  jussi
  Removed references to GetXMin().

  Revision 1.48  1997/01/08 19:01:43  wenger
  Fixed bug 064 and various other problems with drawing piled views;
  added related debug code.

  Revision 1.47  1996/12/20 16:50:14  wenger
  Fonts for view label, x axis, and y axis can now be changed.

  Revision 1.46  1996/11/26 16:47:46  ssl
  Added support for Stacked Opaque and Transparent views

  Revision 1.45  1996/11/20 16:49:57  jussi
  Added AbortQuery() and removed AbortAndReexecute().

  Revision 1.44  1996/11/13 16:56:14  wenger
  Color working in direct PostScript output (which is now enabled);
  improved ColorMgr so that it doesn't allocate duplicates of colors
  it already has, also keeps RGB values of the colors it has allocated;
  changed Color to GlobalColor, LocalColor to make the distinction
  explicit between local and global colors (_not_ interchangeable);
  fixed global vs. local color conflict in View class; changed 'dali'
  references in command-line arguments to 'tasvir' (internally, the
  code still mostly refers to Dali).

  Revision 1.43  1996/11/07 22:40:16  wenger
  More functions now working for PostScript output (FillPoly, for example);
  PostScript output also working for piled views; PSWindowRep member
  functions no longer do so much unnecessary rounding to integers (left
  over from XWindowRep); kept in place (but disabled) a bunch of debug
  code I added while figuring out piled views; added PostScript.doc file
  for some high-level documentation on the PostScript output code.

  Revision 1.42  1996/10/28 15:55:46  wenger
  Scaling and clip masks now work for printing multiple views in a window
  to PostScript; (direct PostScript printing still disabled pending correct
  text positioning and colors); updated all dependencies except Linux.

  Revision 1.41  1996/09/19 20:11:54  wenger
  More PostScript output code (still disabled); some code for drawing
  view borders (disabled).

  Revision 1.40  1996/09/10 20:07:11  wenger
  High-level parts of new PostScript output code are in place (conditionaled
  out for now so that the old code is used until the new code is fully
  working); changed (c) (tm) in windows so images are not copyrighted
  by DEVise; minor bug fixes; added more debug code in the course of working
  on the PostScript stuff.

  Revision 1.39  1996/08/04 22:18:37  jussi
  Changed return type of ToggleViewLocks from bool to void.

  Revision 1.38  1996/08/04 21:03:36  beyer
  Added view-locks and changed key handling.

  Revision 1.37  1996/08/03 15:35:09  jussi
  Solid3D flag now has three values: wireframe, solid with frame,
  and solid without frame.

  Revision 1.36  1996/07/25 14:22:59  jussi
  Added aborted parameter to ReportQueryDone().

  Revision 1.35  1996/07/23 19:34:06  beyer
  Changed dispatcher so that pipes are not longer used for callback
  requests from other parts of the code.

  Revision 1.34  1996/07/23 17:16:30  jussi
  Added support for piled views.

  Revision 1.33  1996/07/21 02:22:05  jussi
  Added _xyZoom variable and associated methods.

  Revision 1.32  1996/07/20 18:47:20  jussi
  Added solid3D flag.

  Revision 1.31  1996/07/13 17:26:55  jussi
  Added ViewRecomputed() callback interface.

  Revision 1.30  1996/07/12 23:42:08  jussi
  Integrated Init() method with the constructor.

  Revision 1.29  1996/07/08 20:31:01  jussi
  Added PixmapEnabled() method.

  Revision 1.28  1996/07/02 22:44:16  jussi
  Removed unnecessary code.

  Revision 1.27  1996/06/27 19:04:50  jussi
  The user can now switch between 2D and 3D display, the
  data is refreshed and displayed accordingly.

  Revision 1.26  1996/06/27 15:43:58  jussi
  Added method AbortAndReexecuteQuery which allows the QueryProc
  to ask the view to re-issue queries when TData has changed.

  Revision 1.25  1996/06/21 19:32:07  jussi
  Moved all 3D-related code to Map3D.C and Map3D.h.

  Revision 1.24  1996/06/15 14:09:46  jussi
  Added yuc\'s 3D methods.

  Revision 1.23  1996/06/15 13:46:49  jussi
  X and Y axes now use the view foreground color as their color.
  The axis.color field was removed.

  Revision 1.22  1996/06/13 00:14:33  jussi
  Added support for XY cursors. All types of cursors can now
  be moved by clicking on their new location in the data area.
  Previously only the X label area was sensitive for cursor
  movement.

  Revision 1.21  1996/05/31 15:30:29  jussi
  Added support for tick marks in axes. The spacing and location
  of tick marks is set automatically to something reasonable,
  even if the axis range is not.

  Revision 1.20  1996/05/07 16:32:14  jussi
  Moved Action member variable to ViewGraph. Move implementation of
  HandleKey, HandlePress and HandlePopup to ViewGraph as well.

  Revision 1.19  1996/04/20 19:52:21  kmurli
  Changed Viex.c to use a pipe mechanism to call itself if it needs to be
  done again. The view now is not called contiously by the Dispatcher,instead
  only of there is some data in the pipe.
  The pipe mechanism is implemented transparently through static functions
  in the Dispatcher.c (InsertMarker,CreateMarker,CloseMarker,FlushMarker)

  Revision 1.18  1996/04/10 02:43:54  jussi
  Added small check to SetXMin() to accommodate multiple mappings
  per view.

  Revision 1.17  1996/04/09 22:51:58  jussi
  Added SetOverrideColor() and GetOverrideColor().

  Revision 1.16  1996/03/06 19:35:26  jussi
  Added GetNumDimensions() and SetNumDimensions().

  Revision 1.15  1996/02/06 19:32:28  jussi
  Moved logo drawing to ViewWin.c.

  Revision 1.14  1996/02/05 23:57:00  jussi
  Added DEVise logo display.

  Revision 1.13  1996/01/30 00:02:41  jussi
  Made code refer to ForegroundColor and BackgroundColor instead
  of black and white.

  Revision 1.12  1996/01/16 17:06:47  jussi
  Minor updates.

  Revision 1.11  1995/12/29 22:42:12  jussi
  Added support for line connectors.

  Revision 1.10  1995/12/29 18:28:26  jussi
  Added new cursor mechanism; cursors are drawn as inverted rectangles
  which are easier to see than the old cursor lines.

  Revision 1.9  1995/12/05 17:02:13  jussi
  Moved _stats to ViewGraph (superclass) so that statistics can be
  turned on and displayed without having to redisplay the data itself.

  Revision 1.8  1995/12/04 18:06:36  jussi
  Added GetLabelParams and replaced ToggleStatDisplay with SetStatDisplay.

  Revision 1.7  1995/12/02 21:24:45  jussi
  Changed "boundary" default to false. Views no longer have a
  boundary because Tk or other type of margin controls will
  surround each view.

  Revision 1.6  1995/11/28 05:10:23  ravim
  Support for statistics.

  Revision 1.5  1995/11/24 21:32:04  jussi
  Added copyright notice and cleaned up the code. Made GetDataArea
  a protected method so that TDataViewX and ViewScatter can access
  the size of the data area.

  Revision 1.4  1995/09/14 20:49:06  jussi
  Added missing semicolon.

  Revision 1.3  1995/09/14 20:32:35  jussi
  Added missing return statement to SetFormat.

  Revision 1.2  1995/09/05 21:13:17  jussi
  Added/update CVS header.
*/

//******************************************************************************
//
//******************************************************************************

#ifndef __VIEW_H
#define __VIEW_H

//******************************************************************************
// Libraries
//******************************************************************************

#include "Dispatcher.h"
#include "DList.h"
#include "VisualArg.h"
#include "ViewWin.h"
#include "Control.h"
#include "ViewCallback.h"
#include "AttrList.h"
#include "Cursor.h"
#include "DevFont.h"

#include "Color.h"
#include "Coloring.h"
#include "ViewDir.h"
#include "DevAxis.h"
#include "PileStack.h"
#include "ObjectValid.h"

//******************************************************************************

//#define VIEWTABLE 
class DataSourceBuf;
class DataSourceFixedBuf;
class View;
DefinePtrDList(ViewList, View *)

/* rectangle to store screen coordinates */
struct ViewRect {
  int xLow, yLow, xHigh, yHigh;
};

// AxisLabels aren't actually used or fully implemented -- using the
// typedef here to simplify cleaning up.
typedef void * AxisLabel;

struct LabelInfo {
  char *name;	          /* name used to draw label */
  Boolean occupyTop;      /* TRUE if label occupies top of view.
			     false if label occupies left of view */
  int extent;	          /* height if label occupies top of view.
			     width if label occupies left of view */
};

class FilterQueue;

//******************************************************************************
// class View
//******************************************************************************

class View_ControlPanelCallback;
class View_DispatcherCallback;

class View : public ViewWin
{
		friend class View_ControlPanelCallback;
		friend class View_DispatcherCallback;
		friend class JavaScreenCmd;
		friend class PileStack;
		friend class DevAxis;
		friend class MetaVisDesc;

		// This is here to allow direct access to dispatcherCallback
		friend class ActionDefault;

	public:

		enum VIEW_LOCK
		{
			LOWER_LEFT	= 0x0001,
			UPPER_LEFT	= 0x0002,
			LOWER_RIGHT	= 0x0004,
			UPPER_RIGHT	= 0x0008,
			XWIDTH		= 0x0010,
			YWIDTH		= 0x0020,

			LEFT_SIDE	= LOWER_LEFT  | UPPER_LEFT,
			RIGHT_SIDE	= LOWER_RIGHT | UPPER_RIGHT,
			TOP_SIDE	= UPPER_LEFT  | UPPER_RIGHT,
			BOTTOM_SIDE	= LOWER_LEFT  | LOWER_RIGHT,
			ALL_LOCKS	= 0xffff
		};

	private:

		// Callback Adapters
		View_ControlPanelCallback*		controlPanelCallback;
		View_DispatcherCallback*		dispatcherCallback;

	public:

		// Constructors and Destructors
		View(char* name, VisualFilter& initFilter,
			 PColorID fgid = GetPColorID(defForeColor),
			 PColorID bgid = GetPColorID(defBackColor),
			 AxisLabel* xAxis = NULL, AxisLabel* yAxis = NULL,
			 AxisLabel* zAxis = NULL,
			 int weight = 1, Boolean boundary = false);
		virtual ~View(void);

		// Getters and Setters
		virtual void    SetForeground(PColorID fgid);
		virtual void    SetForeground(PColorID fgid,
		                  DisplayMode::Mode mode);
		virtual void    SetBackground(PColorID bgid);
		virtual void    SetBackground(PColorID bgid,
		                  DisplayMode::Mode mode);

		virtual void    SetColors(PColorID fgid, PColorID bgid);

		// Utility Functions
		static void		RefreshAll(void);


		/* Highlight a view of depending on flag.*/
	void DoSelect(Boolean flag);

	/* setting/getting visual filter */
	// Set visual filter, generating a command.
	void SetVisualFilterCommand(const VisualFilter &filter,
	                            Boolean registerEvent = true);
	// Set visual filter, *not* generating a command.
	void SetVisualFilter(const VisualFilter &filter,
			     Boolean registerEvent = true);
	void GetVisualFilter(VisualFilter &filter);
	VisualFilter *GetVisualFilter(); // Note: treat return value as const

	/* history queue */
	FilterQueue *GetHistory();

	// Go back one in history queue.
	void BackOne();

	/* For history initialization only */
	void ClearHistory();
	void InsertHistory(VisualFilter &filter);

	/* Mark/unmark nth visualfilter in history */
	void Mark(int index, Boolean true_false);

	static View *FindViewByName(const char *name);

	/* iterate through all views */
	static int InitViewIterator() { return _viewList->InitIterator(); }
	static Boolean MoreView(int index) { return _viewList->More(index); }
	static View *NextView(int index){ return _viewList->Next(index); }
	static void DoneViewIterator(int index) { _viewList->DoneIterator(index); }

	static View *FindSelectedView();
	void SelectView(Boolean calledFromPile = false);
	static void SelectNextInPile();
	static void SelectParent();
	static void SelectFirstChild();
	static void SelectNextChild();

	static void ClearGlobalFilterHistory();

	/* Set axes callback */
	void SetXAxisAttrType(AttrType type);
	AttrType GetXAxisAttrType() { return _xAxis.GetAttrType(); }
	void SetYAxisAttrType(AttrType type);
	AttrType GetYAxisAttrType() { return _yAxis.GetAttrType(); }
	void SetZAxisAttrType(AttrType type);
	AttrType GetZAxisAttrType() { return _zAxis.GetAttrType(); }

	void XAxisDisplayOnOff(Boolean axisOn, Boolean notifyPile = true);
	void YAxisDisplayOnOff(Boolean axisOn, Boolean notifyPile = true);
	void AxisDisplay(Boolean &xOnOff, Boolean &yOnOff) {
	  xOnOff = _xAxis.IsInUse();
	  yOnOff = _yAxis.IsInUse();
	}
	void AxisDisplay(Boolean &xOnOff, Boolean &yOnOff, Boolean &zOnOff) {
	  xOnOff = _xAxis.IsInUse();
	  yOnOff = _yAxis.IsInUse();
	  zOnOff = _zAxis.IsInUse();
        }
	void XAxisTicksOnOff(Boolean ticksOn, Boolean notifyPile = true);
	void YAxisTicksOnOff(Boolean ticksOn, Boolean notifyPile = true);

        static const int _defaultXAxisWidth = 15;
        static const int _defaultYAxisWidth = 50;
        static const int _defaultZAxisWidth = 50;
	static const int _noTicksXAxisWidth = 2;
	static const int _noTicksYAxisWidth = 2;
	static const int _noTicksZAxisWidth = 2;

	void SetXAxisMultFact(double factor, Boolean notifyPile = true);
	void SetYAxisMultFact(double factor, Boolean notifyPile = true);
	double GetXAxisMultFact() { return _xAxis.GetMultFactor(); }
	double GetYAxisMultFact() { return _yAxis.GetMultFactor(); }

    void SetXLinkMultFact(double factor) { _xAxisLinkMultFact = factor; }
    void SetYLinkMultFact(double factor) { _yAxisLinkMultFact = factor; }
	double GetXLinkMultFact() { return _xAxisLinkMultFact; }
	double GetYLinkMultFact() { return _yAxisLinkMultFact; }

	void TicksEnabled(Boolean &xTicks, Boolean &yTicks) {
	  xTicks = _xAxis.Width() > _noTicksXAxisWidth;
	  yTicks = _yAxis.Width() > _noTicksYAxisWidth;
	}

	/* view locks - lock corners or widths */
	void SetViewLocks(int locks) { _view_locks |= locks; }
	void ClearViewLocks(int locks) { _view_locks &= ~locks; }
	void ToggleViewLocks(int locks) { _view_locks ^= locks; }
	int ViewLocks() { return _view_locks; }
	bool IsViewLocked(int locks) { return (_view_locks & locks) != 0; }

	/* get label (title) parameters */
	void GetLabelParam(Boolean &occupyTop, int &extent, const char *&name);
	
	/* set label (title) parameters */
	void SetLabelParam(Boolean occupyTop, int extent, const char *name = 0,
	    Boolean notifyPile = true);

        /* abort query */
        void AbortQuery();

        /* refresh view (re-execute query) */
	void Refresh(Boolean refreshPile = true);

	// Cancel a refresh of this view.
	void CancelRefresh();

	// True means that a refresh has been requested or a query is
	// running for this view.
	Boolean RefreshPending() { return _refreshPending; }

	/* Insert callback */
	static void InsertViewCallback(ViewCallback *callBack);
	static void DeleteViewCallback(ViewCallback *callBack);

	/* Iconify view */
	void Iconify(Boolean iconified);

	/* Cursor manipulations */
	void AppendCursor(DeviseCursor *cursor);
	void DeleteCursor(DeviseCursor *cursor);
	Boolean DrawCursors();
	Boolean HideCursors();

	/* Get/set dimensionality */
	int GetNumDimensions() { return _numDimensions; }
	void SetNumDimensions(int d, Boolean notifyPile = true);

	/* Get/set wireframe/solid/solid+frame 3D objects */
	int GetSolid3D() { return _solid3D; }
	void SetSolid3D(int solid);

	/* Whether to use Jmol for this view in the JavaScreen (applies
	 * only if view is 3D; must be the same for all views in a pile). */
	Boolean GetUseJmol() { return _useJmol; }
	void SetUseJmol(Boolean newValue) { _useJmol = newValue; }

	/* Get/set XY zoom or X/Y zoom */
	Boolean IsXYZoom() { return _xyZoom; }
	void SetXYZoom(Boolean xyZoom) { _xyZoom = xyZoom; }

	/* Get/set data value display flag */
	Boolean GetDisplayDataValues() { return _dispDataValues; }
	void SetDisplayDataValues(Boolean disp);

	/* Get/set pile mode */
	Boolean IsInPileMode() { return _pileMode; }
	void SetPileMode(Boolean mode);

	// Flip the appropriate PileStack object, if any.
	void Flip(Boolean doCommand = false);

	Boolean IsHighlightView() { return _isHighlightView; }
	void SetHighlightView(Boolean highlightView) {
	  _isHighlightView = highlightView;
	}

	Boolean DoneRefresh() { return _doneRefresh;}

	virtual void SetGeometry(int x, int y, unsigned wd, unsigned ht); 

	/******** Pixmap manipulations *********/
    /* Look into pixmap buffer for pixmap that we can use for drawing
	filter.  Restore the pixmap, and return a new visual filter. */
	enum PixmapStat { PixmapTotal , PixmapPartial, PixmapNone };
	PixmapStat RestorePixmap(VisualFilter filter, VisualFilter &newFilter);
    virtual Boolean PixmapEnabled() { return true; }

	/* Append pixmaps in pixmap buffer into file.*/
	void SavePixmaps(FILE *file);

	/* Restore pixmaps from an open file into pixmap buffer*/
	void LoadPixmaps(FILE *file);

	/* Invalidate pixmaps because of changes in mapping.
	This needs to be developed into a more complicated interface
	in order to detect whether mapping has been changed back */
	void InvalidatePixmaps();

	/* Print view statistics */
	virtual void PrintStat();

	/* Toggle symbol display */
	virtual Boolean DisplaySymbols() { return false; }
	virtual Boolean DisplaySymbols(Boolean state) { return state; }

	/* Toggle connector display */
	virtual Boolean DisplayConnectors() { return false; }
	virtual Boolean DisplayConnectors(Boolean state) { return state; }

	/* Report size of data display area. */
	void GetDataArea(int &x, int &y, int &width,int &height);

	/* 3D functions */
        void Draw3DAxis();
	Camera GetCamera() { return _filter.camera; }
	void SetCamera(Camera new_camera);
	void SetViewDir(ViewDir dir);

	Boolean JS3dConfigValid() { return _3dValid; }
	Boolean GetJS3dConfig(float data[3][3], float origin[3], float &shiftedX,
	    float &shiftedY); // returns true iff successful
	void SetJS3dConfig(const float data[3][3], const float origin[3],
	    float shiftedX, float shiftedY);

	// Print this view (and any child views) to PostScript.
	virtual DevStatus PrintPS();

	virtual void SetFont(const char *which, int family, float pointSize,
	  Boolean bold, Boolean italic, Boolean notifyPile = true);
	virtual void GetFont(const char *which, int &family, float &pointSize,
	  Boolean &bold, Boolean &italic);

#if  0 
	/* Update Viewtable */
	static void UpdateViewTable(char *name, double X, double Y, 
				    GlobalColor bgColor);
	static void UpdateViewTable();
	static DataSourceBuf* GetViewTable();
#endif

	static Boolean InVisualFilter(const VisualFilter &filter, Coord xLoc,
				      Coord yLoc, Coord width = 0.0,
				      Coord height = 0.0)
	{
	  if ((xLoc + (width / 2.0) < filter.xLow) ||
	      (xLoc - (width / 2.0) > filter.xHigh) ||
	      (yLoc + (height / 2.0) < filter.yLow) ||
	      (yLoc - (height / 2.0) > filter.yHigh)) {
	    return false;
	  } else {
	    return true;
	  }
	}

    Boolean IsSelected() { return _selected; }

	const char *GetXAxisDateFormat() { return _xAxis.GetDateFormat(); }
	void SetXAxisDateFormat(const char *format, Boolean notifyPile = true);
	const char *GetYAxisDateFormat() { return _yAxis.GetDateFormat(); }
	void SetYAxisDateFormat(const char *format, Boolean notifyPile = true);

	const char *GetXAxisFloatFormat() { return _xAxis.GetFloatFormat(); }
	void SetXAxisFloatFormat(const char *format,
	    Boolean notifyPile = true);
	const char *GetYAxisFloatFormat() { return _yAxis.GetFloatFormat(); }
	void SetYAxisFloatFormat(const char *format,
	    Boolean notifyPile = true);

	// Z coordinate of views.  Initially, at least, this is used only for
	// drawing the views in the JavaScreen.  RKW 1999-03-17.
	float GetZ() { return _viewZ; }
	void SetZ(float viewZ) { _viewZ = viewZ; }

	static void SetDrawCursors(Boolean draw) { _drawCursors = draw; }
	static void SetJSCursors(Boolean js) { _jsCursors = js; }
	static Boolean GetShowNames() { return _showNames; }
	static void SetShowNames(Boolean showNames);

	Boolean AutoUpdateFilter() { return _autoUpdate; }
	void SetAutoUpdate(Boolean autoUpdate);

	// Disable certain actions in a view (mainly for JavaScreen).
	void GetDisabledActions(Boolean &rubberbandDisabled,
	    Boolean &cursorMoveDisabled, Boolean &drillDownDisabled,
		Boolean &keysDisabled) {
	  rubberbandDisabled = GetRubberbandDisabled();
	  cursorMoveDisabled = GetCursorMoveDisabled();
	  drillDownDisabled = GetDrillDownDisabled();
	  keysDisabled = GetKeysDisabled();
    }
	Boolean GetRubberbandDisabled() { return (IsInPileMode() ?
	    GetParentPileStack()->GetRubberbandDisabled() : _rubberbandDisabled); }
	Boolean GetCursorMoveDisabled() { return (IsInPileMode() ?
	    GetParentPileStack()->GetCursorMoveDisabled() : _cursorMoveDisabled); }
	Boolean GetDrillDownDisabled() { return (IsInPileMode() ?
	    GetParentPileStack()->GetDrillDownDisabled() : _drillDownDisabled); }
	Boolean GetKeysDisabled() { return (IsInPileMode() ?
	    GetParentPileStack()->GetKeysDisabled() : _keysDisabled); }
	void SetDisabledActions(Boolean disableRubberband,
	    Boolean disableCursorMove, Boolean disableDrillDown,
		Boolean disableKeys) {
	  _rubberbandDisabled = disableRubberband;
	  _cursorMoveDisabled = disableCursorMove;
	  _drillDownDisabled = disableDrillDown;
	  _keysDisabled = disableKeys;
	  if (IsInPileMode()) {
	    GetParentPileStack()->SetDisabledActions(disableRubberband,
		    disableCursorMove, disableDrillDown, disableKeys);
	  }
    }

	Boolean GetExcludeFromDrillDown() { return _excludeFromDrillDown; }
	void SetExcludeFromDrillDown(Boolean value) {
	    _excludeFromDrillDown = value; }

	static void EnableDrawing(Boolean enable);

	const char *GetViewHelp() { return _viewHelp; }
	void SetViewHelp(const char *helpStr);

	// Show value meanings: 0 = none; 1 = xy; 2 = x; 3 = y;
	// values are this way for backwards compatibility.
	int GetShowMouseLocation() { return _showMouseLocation; }
	void SetShowMouseLocation(int show) { _showMouseLocation = show; }
	static Boolean GetGlobalShowMouseLocation() {
	    return _globalShowMouseLocation; }
	static void SetGlobalShowMouseLocation(Boolean show) {
	    _globalShowMouseLocation = show; }

    Boolean IsChildView() { return _isChildView; }
	void SetChildView(Boolean isChild) { _isChildView = isChild; }

	void SetFilterChangeCmds(const char *cmds);
	const char *GetFilterChangeCmds(void) const {
	  return _filterChangeCmds ? _filterChangeCmds : ""; }

	/* Get whether to save this view's visual filter (indexed by
	   TData name and parent attribute value) when either the TData
	   or parent value is changed, if this view is a view symbol. */
	void GetViewSymSaveFilter(Boolean &saveX, Boolean &saveY) {
	  saveX = _viewSymSaveX; saveY = _viewSymSaveY; }

	/* Set whether to save this view's visual filter (indexed by
	   TData name and parent attribute value) when either the TData
	   or parent value is changed, if this view is a view symbol. */
	void SetViewSymSaveFilter(Boolean saveX, Boolean saveY) {
	  _viewSymSaveX = saveX; _viewSymSaveY = saveY; }

	/* Save the state of all cursors for which this view is the
	   destination view (state is source view visual filter and
	   proportions relative to destination view). */
	void SaveCursorState();

	/* Restore the state of all cursors for which this view is the
	   destination view (state is source view visual filter and
	   proportions relative to destination view). */
	void RestoreCursorState();

protected:
	/* called by base class when it has been mapped/unmapped */
	virtual void SubClassMapped();   /* called just after mapping */
	virtual void SubClassUnmapped(); /* called just before unmapping */

	/* Base class decides when to start/abort a query. Derived
	   class must implement the following methods. */
	virtual void DerivedStartQuery(VisualFilter &filter,
				       int timestamp) = 0;
	virtual void DerivedAbortQuery() = 0;

	/* When a query is done, derived class must inform the base class */
	void ReportQueryDone(int bytes, Boolean aborted = false);

	/* Find World coord given screen coord */
	void FindWorld(int sx1, int sy1, int sx2, int sy2,
		       Coord &xLow, Coord &yLow, Coord &xHigh, Coord &yHigh);


	/* check Cursor Op. Return cursor operated on */
	Boolean CheckCursorOp(int x, int y);

	/* Get area for displaying label */
	void GetLabelArea(int &x, int &y, int &w, int &h);
	void GetXAxisArea(int &x, int &y, int &width, int &height,
			  int &startX);
	void GetYAxisArea(int &x, int &y, int &width, int &height);

	// Force the given point to be within the view's data area.  Returns
	// true iff original point was outside data area.
	Boolean ForceIntoDataArea(int &x, int &y);

private:
    void CleanUpViewSyms();
	void InvalidateCursors();
	void RunFilterChangeCmds();

	// Get the geometry of the view, with the space for the highlight outline
	// removed.
	void GeometryWithHighlight(int &x, int &y, unsigned &w, unsigned &h);

	// Get the height of the label (title) area.
	unsigned int GetLabelHeight();

	// Get the height of the X axis area.
	unsigned int GetXAxisHeight();

	// Get the width of the Y axis area.
	unsigned int GetYAxisWidth();

protected:
	void DrawHighlight();

	void ReportViewCreated();
	void ReportFilterAboutToChange();
	void ReportFilterChanged(const VisualFilter &filter, int flushed);
	void ReportViewRecomputed();
	void ReportViewDestroyed();

	virtual void UpdatePhysTData() {}

	/* Update the visual filter with scrolling. Return
	the stat as followed:
		NotScrolled: can't scroll new filter with respect to old.
		Scrolled: was able to scroll, and _exposureRect was updated.
		SameFilter: new and old filter are the same. _exposureRect
			was not changed.*/
	enum UpdateFilterStat { NotScrolled, Scrolled, SameFilter };
	UpdateFilterStat UpdateFilterWithScroll();

	/* Drawing axes and label*/
	void DrawAxesLabel(WindowRep *win, int x, int y, int w, int h);
	void DrawLabel();
	void DoDrawCursor(WindowRep *winRep, DeviseCursor *cursor);

	/* Calculate the transformation for this view */
	void CalcTransform2(WindowRep* winrep);
	void CalcTransform3(WindowRep* winrep);

	/* Find World coord given screen coord */
	/* void FindWorld(int sx1, int sy1, int sx2, int sy2,
		Coord &xLow, Coord &yLow, Coord &xHigh, Coord &yHigh); */

	Boolean  _displaySymbol; /* true if to be displayed */
	DevAxis _xAxis, _yAxis, _zAxis;

	DispatcherID _dispatcherID;

	/* TRUE if _filter has changed since last time query was sent */
	Boolean _filterChanged; 
	VisualFilter _filter;      /* new state of visual filter */
	
	Boolean _hasExposure;      /* TRUE if _exporsureRect has valid data */
	ViewRect _exposureRect;    /* Rect that has been exposed
				      and needs to be redrawn */
	
	Boolean _querySent;	    /* TRUE if query has been sent */

	int _id;                    /* id of this view */
	static int _nextId;         /* id of next view */
	static ViewList *_viewList; /* list of all views */

#if 0 
	static DataSourceFixedBuf *_viewTableBuffer; /* for view table */
#endif
	

	LabelInfo _label;	  /* info about label */
	Boolean _updateTransform; /* TRUE if we need to update transform
				     for the window */
	Boolean _updateNumDim;    /* TRUE if we need to update number of
                                     dimensions for the window */

	void UpdateTransform(WindowRep *winRep); /* update transformation */

	Boolean _hasLastFilter; /* TRUE if last filter was used for query */
	VisualFilter _lastFilter;

	Boolean _refresh;	/* TRUE if we are refreshing */
	
	FilterQueue *_filterQueue; /* stores history of filter changes */
	
	static ViewCallbackList *_viewCallbackList;
	
	Boolean _hasTimestamp;
	int _timeStamp;
	
	/* true if events occurs in layout mode that requires refresh when
	   in display mode. This variable is sent when anything happens during
	   LayoutMode that requires a refresh. It is resent only when a query
	   is sent. */
	Boolean _modeRefresh;
	Boolean _selected;

	int _view_locks;	// bits from VIEW_LOCK

	// This is a list of cursors for which this view is the *destination*
	// view (in other words, cursors that are drawn in this view).
	DeviseCursorList *_cursors;
	DevisePixmap *_pixmap;
	int _bytes;          /* # data bytes used to draw the current view */
	static int _nextPos; /* next position in file to read from
				input file */
	
	Boolean _cursorsOn;             /* true if cursors displayed */

	int _numDimensions;             /* number of dimensions */
        Boolean _solid3D;               /* true if solid 3D objects */

	    // Whether to use Jmol for this view in the JavaScreen --
	    // applies only if view is 3D.
	Boolean _useJmol;

        Boolean _xyZoom;                /* true if XY zooms */
        Boolean _dispDataValues;        /* true if data values display
                                           in graph */
        Boolean _pileMode;              /* true if view is in pile mode */
        Boolean _pileViewHold;          /* true if bottom view must hold */

	Boolean _printing;		/* true if we're printing right now */

	/* count # of times something happens */
	int _jump, _zoomIn, _zoomOut, _scrollLeft, _scrollRight, _unknown;

        Boolean _XORflag;    /* draw view on XOR layer */
	/* 3D data structures */
	
	Boolean _doneRefresh;   /* for any dependent views to determine the 
				 * state of the view 
                                 */
	virtual DevStatus PrintPSDone();

	DevFont _titleFont;

	Boolean _isHighlightView;

	// Whether to save and restore the X and Y parts of the visual filter
	// for a view symbol when we switch TData and/or parent value.
	Boolean _viewSymSaveX;
	Boolean _viewSymSaveY;

	protected:

		// Callback methods (ControlPanelCallback)
		void	ModeChange(ControlPanel::Mode mode);

		// Callback methods (DispatcherCallback)
		virtual const char*	DispatchedName(void);
		virtual void	Run(void);
		virtual void	Cleanup(void)
		{ DOASSERT(false, "Call in derived class only"); }

		// Callback methods (WindowRepCallback)
		virtual void	HandleExpose(WindowRep* w, int x, int y,
									 unsigned width, unsigned height);
		virtual void	HandleResize(WindowRep* w, int xlow, int ylow,
									 unsigned width, unsigned height);

        virtual void IsOnCursor(int pixX, int pixY, CursorHit &cursorHit);
        virtual void DoIsOnCursor(int pixX, int pixY, CursorHit &cursorHit);

        virtual void MouseDrag(int x1, int y1, int x2, int y2, int button);

		virtual void ShowMouseLocation(int *mouseX, int *mouseY);

		Boolean _autoUpdate;

		static Boolean _drawCursors;
		static Boolean _jsCursors;
		static Boolean _showNames;

    private:
		Boolean _inDestructor;

		float _viewZ;

		// Never access these members directly!
	    Boolean _rubberbandDisabled;
	    Boolean _cursorMoveDisabled;
	    Boolean _drillDownDisabled;
		Boolean _keysDisabled;

		Boolean _excludeFromDrillDown;

		Boolean _refreshPending;

		static Boolean _drawingEnabled;
		
		const char *_viewHelp;
		int _showMouseLocation;
		static int _globalShowMouseLocation;

		Boolean _isChildView;

		// 3D configuration for JavaScreen.
		Boolean _3dValid;
		float _3dData[3][3];
		float _3dOrigin[3];
		float _3dShiftedX, _3dShiftedY;

		// Number of non-aborted queries run by this view.
		int _queryCount;

		double _xAxisLinkMultFact;
		double _yAxisLinkMultFact;

		char *_filterChangeCmds;

    private:
        ObjectValid _objectValid;
};

//******************************************************************************
// class View_ControlPanelCallback
//******************************************************************************

class View_ControlPanelCallback : public ControlPanelCallback
{
	private:

		View*	_parent;
		
	public:

		View_ControlPanelCallback(View* parent)
			: _parent(parent) {}

		virtual void	ModeChange(ControlPanel::Mode mode)
		{
			_parent->ModeChange(mode);
		}
};

//******************************************************************************
// class View_DispatcherCallback
//******************************************************************************

class View_DispatcherCallback : public DispatcherCallback
{
	private:

		View*	_parent;
		
	public:

		View_DispatcherCallback(View* parent)
			: _parent(parent) {}

		virtual const char*	DispatchedName(void)
		{
			return _parent->DispatchedName();
		}

		virtual void	Run(void)
		{
			_parent->Run();
		}

		virtual void	Cleanup(void)
		{
			_parent->Cleanup();
		}
};

//******************************************************************************
#endif
