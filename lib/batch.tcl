#  ========================================================================
#  DEVise Data Visualization Software
#  (c) Copyright 1992-1996
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
#  Revision 1.4  1996/08/29 22:26:49  guangshu
#  Changed puts to proc Puts in case the client want to be quiet.
#
#  Revision 1.3  1996/07/11 18:17:04  jussi
#  Removed all non-essential code. The Tcl batch client no longer
#  uses any Tk (X11) features.
#
#  Revision 1.2  1996/05/14 15:09:21  jussi
#  Added a few global variables.
#
#  Revision 1.1  1996/04/18 18:18:02  jussi
#  Initial revision.

############################################################

set restoring 0
set template 0
set sessionName ""
set curView ""
set mode 0
set libdir $env(DEVISE_LIB)
source $libdir/tool.tcl

set libdir "."
if { [info exists env(DEVISE_LIB)] } {
    set libdir $env(DEVISE_LIB)
}
set datadir "."
if { [info exists env(DEVISE_DAT)] } {
    set datadir $env(DEVISE_DAT)
}
set schemadir "."
if { [info exists env(DEVISE_SCHEMA)] } {
    set schemadir $env(DEVISE_SCHEMA)
}
set tmpdir "tmp"
if { [info exists env(DEVISE_TMP)] } {
    set tmpdir $env(DEVISE_TMP)
}

set hostCfg $libdir/config.tcl
if {![file exists $hostCfg]} {
    Puts "Cannot read configuration file $hostCfg"
} else {
    Puts "Reading configuration file $hostCfg"
    source $hostCfg
}

if {![catch {set hostCfg $libdir/config.$env(HOSTNAME)}]} {
    if {[file exists $hostCfg]} {
	Puts "Reading configuration file $hostCfg"
	source $hostCfg
    }
}

source $libdir/macrodef.tk
source $libdir/util.tcl
source $libdir/sources.tcl

set progName [ file tail $argv0 ]
set envName [ format "%s_RC" [string toupper $progName] ]
set rcFile1 [ format ".%s_rc" $progName ]
set rcFile2 [ format "%s.rc" $progName ]
set rcFile3 "devise.rc"

if { [ info exists env($envName)] && [file exists $env($envName) ] } {
    set rcFile $env($envName)
} elseif { [ file exists $rcFile1 ] } {
    set rcFile $rcFile1
} elseif { [ file exists $rcFile2 ] } {
    set rcFile $rcFile2
} elseif { [ file exists $rcFile3 ] } {
    set rcFile $rcFile3
} else {
    set rcFile ""
}

if {$rcFile != ""} {
    Puts "Reading initialization file $rcFile"
    source $rcFile
}
