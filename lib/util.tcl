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
#  Revision 1.6  1996/01/17 20:53:45  jussi
#  Added support for additional image export formats.
#
#  Revision 1.5  1996/01/17 19:47:53  jussi
#  Minor bug fix.
#
#  Revision 1.4  1995/12/01 19:46:30  jussi
#  Fixed case where a view that is not mapped to the screen caused
#  an error.
#
#  Revision 1.3  1995/11/29 15:55:11  jussi
#  Removed constant window size definitions because they will produce
#  unexpected results on some window managers.
#
#  Revision 1.2  1995/11/28 16:58:25  jussi
#  Added capability to store window images in a user specified file
#  instead of printing it.
#
# Revision 1.1  1995/11/28  00:02:52  jussi
# Initial revision.
#

############################################################

proc PrintView {} {
    global toprinter printcmd filename allviews formatsel

    # see if .printdef window already exists; if so, just return
    set err [catch {wm state .printdef}]
    if {!$err} { wm deiconify .printdef; return }

    toplevel .printdef
    wm title .printdef "Print View"
    wm geometry .printdef +150+150
    selection clear .printdef
    
    set toprinter 1
    set printcmd "lpr "
    set filename "/tmp/devise"
    set allviews 0

    frame .printdef.top -relief groove -borderwidth 2
    frame .printdef.bot
    pack .printdef.top -side top -fill both -expand 1
    pack .printdef.bot -side top -fill x -pady 5m

    frame .printdef.top.row1
    frame .printdef.top.row2
    frame .printdef.top.row3 -relief groove -borderwidth 2
    pack .printdef.top.row1 .printdef.top.row2 .printdef.top.row3 \
	    -side top -pady 3m

    radiobutton .printdef.top.row1.r1 -text "To Printer" -width 12 \
	    -variable toprinter -value 1 -anchor e
    label .printdef.top.row1.l1 -text "Print Command:" -width 14
    entry .printdef.top.row1.e1 -relief sunken -textvariable printcmd \
	    -width 30
    pack .printdef.top.row1.r1 .printdef.top.row1.l1 .printdef.top.row1.e1 \
	    -side left -padx 2m -fill x -expand 1

    radiobutton .printdef.top.row2.r1 -text "To File" -width 12 \
	    -variable toprinter -value 0 -anchor e
    menubutton .printdef.top.row2.m1 -relief raised \
	    -textvariable formatsel -menu .printdef.top.row2.m1.menu \
	    -width 10
    label .printdef.top.row2.l1 -text "File Name:" -width 14
    entry .printdef.top.row2.e1 -relief sunken -textvariable filename \
	    -width 30
    pack .printdef.top.row2.r1 .printdef.top.row2.m1 \
	    .printdef.top.row2.l1 .printdef.top.row2.e1 \
	    -side left -padx 2m -fill x -expand 1

    menu .printdef.top.row2.m1.menu -tearoff 0
    .printdef.top.row2.m1.menu add radiobutton -label Postscript \
	    -variable formatsel -value Postscript
    .printdef.top.row2.m1.menu add radiobutton -label EPS \
	    -variable formatsel -value EPS
    .printdef.top.row2.m1.menu add radiobutton -label GIF \
	    -variable formatsel -value GIF
    set formatsel Postscript

    label .printdef.top.row3.l1 -text "Print Views:"
    radiobutton .printdef.top.row3.r1 -text "All Views" \
	    -variable allviews -value 1
    radiobutton .printdef.top.row3.r2 -text "Selected View" \
	    -variable allviews -value 0
    pack .printdef.top.row3.l1 .printdef.top.row3.r1 .printdef.top.row3.r2 \
	    -side left -padx 2m -fill x -expand 1

    frame .printdef.bot.but
    pack .printdef.bot.but -side top

    button .printdef.bot.but.ok -text OK -width 10 \
	    -command {
	PrintActual $toprinter $printcmd $filename $allviews $formatsel; \
	destroy .printdef
    }
    button .printdef.bot.but.cancel -text Cancel -width 10 \
	    -command { destroy .printdef }
    pack .printdef.bot.but.ok .printdef.bot.but.cancel -side left -padx 7m

    tkwait visibility .printdef
}

proc PrintActual {toprinter printcmd filename allviews format} {
    global curView

    set windowlist ""

    if {!$allviews} {
	if {$curView == ""} {
	    dialog .printView "Print Selected View" \
		    "Please select a view by clicking in it first." "" 0 OK
	    return
	}
	set windowlist [list [DEVise getViewWin $curView]]

    } else {

	set viewClasses [ DEVise get view ]
	foreach viewClass $viewClasses {
	    set views [ DEVise get view $viewClass ]
	    foreach v $views {
		set win [DEVise getViewWin $v]
		if {$win != "" && [lsearch $windowlist $win] < 0} {
		    lappend windowlist $win
		}
	    }
	}
    }

    set format [string tolower $format]

    set suffix ".ps"
    if {$format != "postscript"} {
	set suffix ".$format"
    }

    if {$toprinter} {
	set format postscript
	set template [format "/tmp/devise.%s.%%d$suffix" [pid]]
    } else {
	set template [format "%s.%%d$suffix" $filename]
    }

    set i 0
    foreach win $windowlist {
	set file [format $template $i]
	puts "Save window $win to file $file"
	set err [ DEVise saveWindowImage $format $win $file ]
	if {$err > 0} {
	    dialog .printError "Window Image Save Error" \
		    "An error occurred while saving window images to files." \
		    "" 0 OK
	    return
	}
	if {$toprinter} {
	    puts "File $file not actually printed. To print file, do:"
	    puts "  $printcmd $file"
	    puts "  rm $file"
	}
	incr i
    }
}
