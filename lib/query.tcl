#  ========================================================================
#  DEVise Data Visualization Software
#  (c) Copyright 1992-1999
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
#  Revision 1.16.14.1  2004/04/23 21:57:28  wenger
#  Added new 'select next view in pile' feature.
#
#  Revision 1.16  1999/06/16 18:28:41  wenger
#  Fixed bug 499 (problem with 'Next in Pile' not working for piled view
#  symbols).
#
#  Revision 1.15  1999/02/17 15:10:06  wenger
#  Added "Next in Pile" button to query dialog; more pile fixes; fixed bug
#  in mapping dialog updating when a view is selected.
#
#  Revision 1.14  1998/10/21 17:17:02  wenger
#  Fixed bug 101 (problems with the '5' (home) key); added "Set X, Y to
#  Show All" (go home) button to Query dialog; fixed bug 421 (crash when
#  closing set link sessions); fixed bug 423 (saving session file over
#  directory).
#
#  Revision 1.13  1997/11/24 23:15:44  weaver
#  Changes for the new ColorManager.
#
#  Revision 1.12  1997/02/26 16:32:05  wenger
#  Merged rel_1_3_1 through rel_1_3_3c changes; compiled on Intel/Solaris.
#
#  Revision 1.11.4.1  1997/02/14 20:26:17  wenger
#  Fixed bug 159.
#
#  Revision 1.11  1997/01/23 17:03:03  wenger
#  Added full info to 'About DEVise' window.
#
#  Revision 1.10  1997/01/23 00:07:35  jussi
#  Replaced references to queryWinOpened with calls to WindowExists.
#
#  Revision 1.9  1997/01/22 20:13:58  wenger
#  Removed other non-functional user interface components (includes workaround
#  for bug 127); fixed a number of OK/Cancel button positions.
#
#  Revision 1.8  1996/11/25 22:31:35  beyer
#  1. extended .devise.rc search
#  2. added DestroyView command
#  3. query window updated properly, history window update changed
#  4. filter properly set to (0,100) instead of (100,0) when high,low values
#     are not known.
#
#  Revision 1.7  1996/08/07 15:43:40  guangshu
#  Added global statistics into the query box.
#
#  Revision 1.6  1996/07/10 19:02:01  jussi
#  3D query window now displays fix_focus and perspective flags.
#
#  Revision 1.5  1996/06/27 00:00:35  jussi
#  Coordinates of 3D focal point are now saved and displayed.
#
#  Revision 1.4  1996/06/20 21:38:57  jussi
#  Added radial coordinates of the camera and rectangular coordinates
#  of the focal point to the 3D query dialog.
#
#  Revision 1.3  1996/06/20 17:22:11  guangshu
#  Added statistics button but commented it out.
#
#  Revision 1.2  1996/06/15 14:43:16  jussi
#  Added yuc's 3D procedures.
#
#  Revision 1.1  1996/04/11 18:13:34  jussi
#  Initial revision.
#

############################################################

# Global holding name of view currently being edited.
set curQueryView ""

proc SetQuery {} { 
    global curQueryView

    if {[WindowVisible .query]} {
	return
    }

    set expand 1
    set fill both

    toplevel    .query
    wm title    .query "Query Tool"
    wm geometry .query +200+200

    # build view name widget

    frame .query.title
    pack .query.title -side top -pady 1m -expand $expand -fill $fill

    # this is used just to (roughly) center the title
    frame .query.title.spacer -width 26m -height 5m
    pack .query.title.spacer -side left

    button .query.next -text "Next in Pile" -state disabled \
        -command { DEVise selectNextInPile }
    pack .query.next -in .query.title -side right

    label .query.title.text -text "No View Selected"
    pack .query.title.text -side top -pady 1m

    # build xyRange widgets

    frame .query.xyRange
    pack .query.xyRange -side top -pady 1m -expand $expand -fill $fill

    frame .query.xyRange.top
    frame .query.xyRange.bottom 

    frame .query.xyRange.top.yEntry
    frame .query.xyRange.top.yDummy -width 280 -relief groove -bd 3
    frame .query.xyRange.top.yDummy.high
    frame .query.xyRange.top.yDummy.high.left
    frame .query.xyRange.top.yDummy.high.right
    frame .query.xyRange.top.yDummy.low
    frame .query.xyRange.top.yDummy.low.left
    frame .query.xyRange.top.yDummy.low.right
    frame .query.xyRange.top.yEntry.yhigh
    frame .query.xyRange.top.yEntry.ylow

    frame .query.xyRange.bottom.xDummy
    frame .query.xyRange.bottom.xEntry
    frame .query.xyRange.bottom.xEntry.xlow
    frame .query.xyRange.bottom.xEntry.xhigh

    #set up max mean min count labels and entries

    label .query.xyRange.top.yDummy.high.left.max -text "Max" \
	   -width 4 -font 8x13
    entry .query.max -text "" -relief sunken -width 5 -font 8x13
    pack .query.xyRange.top.yDummy.high.left.max .query.max \
	    -in .query.xyRange.top.yDummy.high.left \
	    -side left -expand $expand -fill $fill

    label .query.xyRange.top.yDummy.high.right.min -text "Min" \
           -width 4 -font 8x13
    entry .query.min -text "" -relief sunken -width 5 -font 8x13
    pack .query.xyRange.top.yDummy.high.right.min .query.min \
            -in .query.xyRange.top.yDummy.high.right \
            -side left -expand $expand -fill $fill

    label .query.xyRange.top.yDummy.low.left.mean -text "Mean" \
           -width 4 -font 8x13
    entry .query.mean -text "" -relief sunken -width 5 -font 8x13
    pack .query.xyRange.top.yDummy.low.left.mean .query.mean \
            -in .query.xyRange.top.yDummy.low.left \
            -side left -expand $expand -fill $fill

    label .query.xyRange.top.yDummy.low.right.count -text "Count" \
           -width 4 -font 8x13
    entry .query.count -text "" -relief sunken -width 5 -font 8x13
    pack .query.xyRange.top.yDummy.low.right.count .query.count \
            -in .query.xyRange.top.yDummy.low.right \
            -side left -expand $expand -fill $fill

    pack .query.xyRange.top.yDummy.high.left \
           .query.xyRange.top.yDummy.high.right \
           -side left -expand $expand -fill $fill

    pack .query.xyRange.top.yDummy.low.left \
           .query.xyRange.top.yDummy.low.right \
           -side left -expand $expand -fill $fill

    pack .query.xyRange.top.yDummy.high .query.xyRange.top.yDummy.low \
            -side top -expand $expand -fill $fill
         
    # set up Y labels and entries

    label .query.xyRange.top.yEntry.yhigh.yHighHeading -text "Y high" \
	    -width 6 -font 8x13
    entry .query.yhigh -text "" -relief sunken -width 10 -font 8x13

    pack .query.xyRange.top.yEntry.yhigh.yHighHeading .query.yhigh \
	    -in .query.xyRange.top.yEntry.yhigh \
	    -side left -expand $expand -fill $fill

    label .query.xyRange.top.yEntry.ylow.yLowHeading -text "Y low" \
	    -width 6 -font 8x13
    entry .query.ylow -text "" -relief sunken -width 10 -font 8x13

    pack .query.xyRange.top.yEntry.ylow.yLowHeading .query.ylow \
	    -in .query.xyRange.top.yEntry.ylow \
	    -side left -expand $expand -fill $fill

    pack .query.xyRange.top.yEntry.yhigh \
	    .query.xyRange.top.yEntry.ylow \
	    -side top -expand $expand -fill $fill

    pack .query.xyRange.top.yEntry \
	    .query.xyRange.top.yDummy \
	    -side left -expand $expand -fill $fill

    # set up X labels and entries

    entry .query.xlow -text "" -relief sunken -width 20 -font 8x13
    label .query.xyRange.bottom.xEntry.xlow.xLowHeading -text "X low"

    pack .query.xlow .query.xyRange.bottom.xEntry.xlow.xLowHeading \
	    -in .query.xyRange.bottom.xEntry.xlow \
	    -side top -expand $expand -fill $fill

    entry .query.xhigh -text "" -relief sunken -width 20 -font 8x13
    label .query.xyRange.bottom.xEntry.xhigh.xHighHeading -text "X high"

    pack .query.xhigh .query.xyRange.bottom.xEntry.xhigh.xHighHeading \
	    -in .query.xyRange.bottom.xEntry.xhigh \
	    -side top -expand $expand -fill $fill

    pack .query.xyRange.bottom.xEntry.xlow \
	    .query.xyRange.bottom.xEntry.xhigh \
	    -side left -expand $expand -fill $fill

    pack .query.xyRange.bottom.xDummy \
	    .query.xyRange.bottom.xEntry \
	    -side left -expand $expand -fill $fill

    pack .query.xyRange.top .query.xyRange.bottom -side top \
	    -expand $expand -fill $fill

#    button .query.xyRange.top.yDummy.stat -text "Toggle Statistics" \
#	    -command DoStat
#    pack .query.xyRange.top.yDummy.stat -side left -expand $expand

    # set up selection area

    frame .query.sel
    pack .query.sel -in .query.xyRange.bottom.xDummy \
	    -side bottom -expand $expand -fill $fill

    button .query.goHome -text "Set X, Y to Show All" -command {
      global curQueryView; DEVise viewGoHome $curQueryView }
    pack .query.goHome -in .query.sel -side bottom -padx 12m

#    button .query.sel.attr -text "Attributes..." \
#	    -command DoAttributeSelect

#    pack .query.sel.attr -side left -padx 3m

    # This frame takes up the space held by the removed buttons.
#    frame .query.sel.placeholder -relief flat -width 65m -height 8m \
#        -borderwidth 4
#    pack .query.sel.placeholder -side left -padx 3m

    if {0} {
	frame .query.sel.sample -relief groove -bd 2
	pack .query.sel.sample -side left -padx 3m \
		-expand $expand -fill $fill
    }

    # set up buttons

    frame .query.bot
    frame .query.bot.but

    button .query.bot.but.exec -text "Execute" -width 10 \
	    -command { ExecuteQuery }
    button .query.bot.but.undo -text "Undo Edit" -width 10 \
	    -command { DoUndoEdit }
    button .query.bot.but.back -text "Back One" -width 10 \
	    -command { DoGoBackOne; ExecuteQuery }
    button .query.bot.but.history -text "History" -width 10 \
	    -command { DoHistoryToggle }
    button .query.bot.but.close -text Close -width 10 \
	    -command { destroy .query }

    pack .query.bot.but.exec .query.bot.but.undo .query.bot.but.back \
	    .query.bot.but.history .query.bot.but.close \
	    -side left -expand 1 -fill x -padx 3m

    pack .query.bot.but -side top
    pack .query.bot -side top -pady 5m

    Query_ViewSelected

    if {$curQueryView != ""} {
	.query.title.text configure -text "View: $curQueryView"
	DoUndoEdit
    }
}

############################################################

proc Update2DQueryWindow {} {
    global curQueryView

    if {![WindowExists .query]} {
	return
    }
    foreach i {xlow ylow xhigh yhigh max mean min count} {
        .query.$i delete 0 end
    }
    if {$curQueryView == ""} {
        .query.title.text configure -text "No View Selected"
        return
    }

    .query.title.text configure -text "View: $curQueryView"

    DoUndoEdit
}

############################################################

proc ExecuteQuery {} {
    global curQueryView

    if {$curQueryView == ""} {
	return
    }

    set xlow [DEVise parseDateFloat [.query.xlow get]]
    set ylow [DEVise parseDateFloat [.query.ylow get]]
    set xhigh [DEVise parseDateFloat [.query.xhigh get]]
    set yhigh [DEVise parseDateFloat [.query.yhigh get]]

    if {$xlow >= $xhigh} {
	dialog .useError "Invalid Visual Filter" \
		"X low $xlow >= X high $xhigh." \
		"" 0 Cancel
	return
    }

    if {$ylow >= $yhigh} {
	dialog .useError "Invalid Visual Filter" \
		"Y low $ylow >= Y high $yhigh." \
		"" 0 Cancel
	return
    }

    DEVise setFilter $curQueryView $xlow $ylow $xhigh $yhigh
}

############################################################

proc DoUndoEdit {} {
    global curQueryView
    
    if { $curQueryView == "" } {
	return
    }
    
    set filters [DEVise getVisualFilters $curQueryView] 
    set filter [lindex $filters [expr [llength $filters]-1]]
    
    foreach i { xlow ylow xhigh yhigh} {
	.query.$i delete 0 end
    }
    .query.xlow insert 0 [lindex $filter 0]
    .query.ylow insert 0 [lindex $filter 1]
    .query.xhigh insert 0 [lindex $filter 2]
    .query.yhigh insert 0 [lindex $filter 3]

    set stat [DEVise getAllStats $curQueryView]
    
    foreach i { max mean min count} {
         .query.$i delete 0 end
    }
    .query.max insert 0 [lindex $stat 0]
    .query.mean insert 0 [lindex $stat 1]
    .query.min insert 0 [lindex $stat 2]
    .query.count insert 0 [lindex $stat 3]
}

############################################################

proc DoGoBackOne {} {
    global curQueryView
    
    if { $curQueryView == "" } {
	return
    }
    
    set filters [DEVise getVisualFilters $curQueryView] 
    set len [llength $filters]
    if { $len <= 1 } {
	return
    }
    set filter [lindex $filters [expr $len-2]]
    
    foreach i {xlow ylow xhigh yhigh} {
	.query.$i delete 0 end
    }
    .query.xlow insert 0 [lindex $filter 0]
    .query.ylow insert 0 [lindex $filter 1]
    .query.xhigh insert 0 [lindex $filter 2]
    .query.yhigh insert 0 [lindex $filter 3]
}

############################################################

proc DoAttributeSelect {} {
}

############################################################

proc Do3DQuery {} { 
    global curView

    if {[WindowVisible .query3d]} {
	return
    }

    toplevel    .query3d
    wm title    .query3d "3D Query Tool"
    wm geometry .query3d +100+100

    # build view name widget

    frame .query3d.title
    pack .query3d.title -side top -pady 1m -expand 1 -fill both

    label .query3d.title.text -text "No View Selected"
    label .query3d.title.sub -text ""
    pack .query3d.title.text .query3d.title.sub -side top -pady 1m

    # build xyzLoc widgets (rectangular and radial coordinates of
    # camera, plus rectangular coordinates of focal point)

    frame .query3d.info
    pack .query3d.info -side top -pady 1m -expand 1 -fill both

    frame .query3d.recLoc -relief groove -bd 2
    frame .query3d.radLoc -relief groove -bd 2
    frame .query3d.focLoc -relief groove -bd 2
    pack .query3d.recLoc .query3d.radLoc .query3d.focLoc \
	    -in .query3d.info -side left -padx 2m -expand 1 -fill both

    label .query3d.recLoc.heading -text "Camera (Rectangular)"
    frame .query3d.recLoc.x
    frame .query3d.recLoc.y
    frame .query3d.recLoc.z
    pack .query3d.recLoc.heading .query3d.recLoc.x \
	    .query3d.recLoc.y .query3d.recLoc.z \
	    -side top -pady 1m -padx 2m

    # set up X label and entry

    label .query3d.recLoc.x.heading -text "X"
    entry .query3d.recLoc.x.e -text "" -relief sunken -width 20
    pack .query3d.recLoc.x.heading .query3d.recLoc.x.e \
	    -side left -expand 1 -fill both

    # set up Y label and entry

    label .query3d.recLoc.y.heading -text "Y"
    entry .query3d.recLoc.y.e -text "" -relief sunken -width 20
    pack .query3d.recLoc.y.heading .query3d.recLoc.y.e \
	    -side left -expand 1 -fill both

    # set up Z label and entry

    label .query3d.recLoc.z.heading -text "Z"
    entry .query3d.recLoc.z.e -text "" -relief sunken -width 20
    pack .query3d.recLoc.z.heading .query3d.recLoc.z.e \
	    -side left -expand 1 -fill both

    label .query3d.radLoc.heading -text "Camera (Radial)"
    frame .query3d.radLoc.theta
    frame .query3d.radLoc.phi
    frame .query3d.radLoc.rho
    pack .query3d.radLoc.heading .query3d.radLoc.theta \
	    .query3d.radLoc.phi .query3d.radLoc.rho \
	    -side top -pady 1m -padx 2m

    # set up theta label and entry

    label .query3d.radLoc.theta.heading -text "Theta" -width 5 -anchor e
    label .query3d.radLoc.theta.e -text "" -relief sunken -width 15 -anchor w
    pack .query3d.radLoc.theta.heading .query3d.radLoc.theta.e \
	    -side left -expand 1 -fill both

    # set up phi label and entry

    label .query3d.radLoc.phi.heading -text "Phi" -width 5 -anchor e
    label .query3d.radLoc.phi.e -text "" -relief sunken -width 15 -anchor w
    pack .query3d.radLoc.phi.heading .query3d.radLoc.phi.e \
	    -side left -expand 1 -fill both

    # set up rho label and entry

    label .query3d.radLoc.rho.heading -text "Rho" -width 5 -anchor e
    label .query3d.radLoc.rho.e -text "" -relief sunken -width 15 -anchor w
    pack .query3d.radLoc.rho.heading .query3d.radLoc.rho.e \
	    -side left -expand 1 -fill both

    label .query3d.focLoc.heading -text "Focal Point"
    frame .query3d.focLoc.x
    frame .query3d.focLoc.y
    frame .query3d.focLoc.z
    pack .query3d.focLoc.heading .query3d.focLoc.x \
	    .query3d.focLoc.y .query3d.focLoc.z \
	    -side top -pady 1m -padx 2m

    # set up X label and entry

    label .query3d.focLoc.x.heading -text "X"
    label .query3d.focLoc.x.e -text "" -relief sunken -width 15 -anchor w
    pack .query3d.focLoc.x.heading .query3d.focLoc.x.e \
	    -side left -expand 1 -fill both

    # set up Y label and entry

    label .query3d.focLoc.y.heading -text "Y"
    label .query3d.focLoc.y.e -text "" -relief sunken -width 15 -anchor w
    pack .query3d.focLoc.y.heading .query3d.focLoc.y.e \
	    -side left -expand 1 -fill both

    # set up Z label and entry

    label .query3d.focLoc.z.heading -text "Z"
    label .query3d.focLoc.z.e -text "" -relief sunken -width 15 -anchor w
    pack .query3d.focLoc.z.heading .query3d.focLoc.z.e \
	    -side left -expand 1 -fill both

    # set up buttons

    frame .query3d.bot
    frame .query3d.bot.but

    button .query3d.bot.but.exec -text "Execute" -width 10 \
	    -command {
	if {$curView == ""} {
	    return
	}
	set x [.query3d.recLoc.x.e get]
	set y [.query3d.recLoc.y.e get]
	set z [.query3d.recLoc.z.e get]
	set loc [DEVise get3DLocation $curView]
	set fx [lindex $loc 4]
	set fy [lindex $loc 5]
	set fz [lindex $loc 6]
	DEVise set3DLocation $curView $x $y $z $fx $fy $fz
	Update3DLocation
    }
    button .query3d.bot.but.close -text Close -width 10 \
	    -command { destroy .query3d }

    pack .query3d.bot.but.exec .query3d.bot.but.close \
	    -side left -expand 1 -fill x -padx 3m

    pack .query3d.bot.but -side top
    pack .query3d.bot -side top -pady 5m

    if {$curView != ""} {
	Update3DLocation
    }
}

proc Update3DLocation {} {
    global curView

    if {![WindowExists .query3d]} {
	return
    }

    .query3d.recLoc.x.e delete 0 end
    .query3d.recLoc.y.e delete 0 end
    .query3d.recLoc.z.e delete 0 end
    .query3d.radLoc.theta.e configure -text ""
    .query3d.radLoc.phi.e configure -text ""
    .query3d.radLoc.rho.e configure -text ""
    .query3d.focLoc.x.e configure -text ""
    .query3d.focLoc.y.e configure -text ""
    .query3d.focLoc.z.e configure -text ""
    .query3d.title.text configure -text "No View Selected"
    .query3d.title.sub configure -text ""

    if {$curView == ""} {
	return
    }

    set loc [DEVise get3DLocation $curView]
    .query3d.recLoc.x.e insert 0 [lindex $loc 1]
    .query3d.recLoc.y.e insert 0 [lindex $loc 2]
    .query3d.recLoc.z.e insert 0 [lindex $loc 3]
    .query3d.radLoc.theta.e configure -text [lindex $loc 7]
    .query3d.radLoc.phi.e configure -text [lindex $loc 8]
    .query3d.radLoc.rho.e configure -text [lindex $loc 9]
    .query3d.focLoc.x.e configure -text [lindex $loc 4]
    .query3d.focLoc.y.e configure -text [lindex $loc 5]
    .query3d.focLoc.z.e configure -text [lindex $loc 6]

    .query3d.title.text configure -text "View: $curView"

    set coordsys "Rectangular"
    if {[lindex $loc 0]} {
        set coordsys "Radial"
    }
    set fixfocus "MoveFocus"
    if {[lindex $loc 10]} {
        set fixfocus ""
    }
    set persp "Non-Perspective"
    if {[lindex $loc 11]} {
        set persp ""
    }
    .query3d.title.sub configure -text "$coordsys $fixfocus $persp"
}

proc Query_ViewSelected {} {
    global curView
    global curQueryView

    if {![WindowExists .query]} {
    	return
    }

    if {$curView != "" && [DEVise getViewPileMode $curView]} {
        .query.next configure -state normal
    } else {
        .query.next configure -state disabled
    }
    
    set curQueryView $curView
}
