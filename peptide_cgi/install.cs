#! /bin/csh -f

#  ========================================================================
#  DEVise Data Visualization Software
#  (c) Copyright 2000
#  By the DEVise Development Group
#  Madison, Wisconsin
#  All Rights Reserved.
#  ========================================================================
#
#  Under no circumstances is this software to be copied, distributed,
#  or altered in any way without prior permission from the DEVise
#  Development Group.

############################################################

#  Install the peptide-cgi setup.  Note: some of the installation is
#  specific to a certain machine; this script is configured to do
#  the installation on pumori -- slight changes may be needed to
#  do the installation on other machines.

#  To use the installed software, go to:
#  http://pumori.cs.wisc.edu/bmrb/bmrb_select.html.

############################################################

#  $Id$

############################################################

set demohome = /p/devise/demo
set wwwhome = /var/home/www


echo You are about to install the peptide-cgi setup.  This
echo will install files in $demohome
echo and $wwwhome.
echo ""
echo -n "Are you absolutely sure you want to do this? [N] "

set answer = $<
if ($answer != y && $answer != Y) then
  echo Aborted.
  exit 1
endif


# Compile the Java code.
cd java_classes
make
cd ..

# Create and set up the directory containing the "front-end" html file.
set targetdir = $wwwhome/public/bmrb
if (! -e $targetdir) then
  mkdir $targetdir
  chmod a+rx $targetdir
endif
cp -p bmrb_select.html $targetdir
chmod a+r $targetdir/bmrb_select.html

# Create and set up the dynamic sessions directory.
set targetdir = $demohome/session.js/bmrb/dynamic_sessions
if (! -e $targetdir) then
  mkdir $targetdir

  # Needed so www-user can write here.
  fs setacl $targetdir system:anyuser write
endif
cp -p dynamic_sessions/*.base $targetdir
chmod a+r $targetdir/*.base

# Create and set up the data/html directory.
set targetdir = $demohome/dat/bmrb/dynamic_data
if (! -e $targetdir) then
  mkdir $targetdir

  # Needed so www-user can write here.
  fs setacl $targetdir system:anyuser write
endif
cp -p html/* $targetdir
chmod a+r $targetdir/*
chmod a+rx $targetdir/summarize

# Create and set up the java classes directory.
set targetdir = $demohome/dat/bmrb/dynamic_data/java_classes
if (! -e $targetdir) then
  mkdir $targetdir
  chmod a+rx $targetdir
endif
cp java_classes/*.class $targetdir
cp java_classes/*.jar $targetdir
chmod a+r $targetdir/*.*

# Create the link that we use to have the browser find the summary page.
set targetdir = $wwwhome/public/bmrb/html
if (! -e $targetdir) then
  ln -s $demohome/dat/bmrb/dynamic_data $targetdir
endif

# Create and set up the CGI directory.
set targetdir = $wwwhome/cgi-bin/bmrb
if (! -e $targetdir) then
  mkdir $targetdir
  chmod a+rx $targetdir
endif
cp -p cgi-bin/make_view $targetdir
chmod a+rx $targetdir/make_view

# Link data directory to CGI directory.
set targetdir = $wwwhome/cgi-bin/bmrb/data_dir
if (! -e $targetdir) then
  ln -s $demohome/dat/bmrb/dynamic_data $targetdir
endif

# Link session directory to CGI directory.
set targetdir = $wwwhome/cgi-bin/bmrb/session_dir
if (! -e $targetdir) then
  ln -s $demohome/session.js/bmrb/dynamic_sessions $targetdir
endif