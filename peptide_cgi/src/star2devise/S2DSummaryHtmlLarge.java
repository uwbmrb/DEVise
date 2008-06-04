// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2006-2008
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class is used to generate the summary page for the large-size
// visualizations.

// Note that almost all of the work is done in S2DSummaryGen.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.4  2008/04/09 19:35:42  wenger
// Added frame details to individual visualization pages in preparation
// for summary page changes; spelled out Linear Analysis of Chemical
// Shifts; removed some unneeded parameters from the S2DSummaryHtml*
// constructors.
//
// Revision 1.3  2007/08/20 20:26:10  wenger
// Added -verb command-line flag and property so we can turn on debug
// output without recompiling; added debug_level property corresponding
// to the existing -debug command-line flag.
//
// Revision 1.2  2007/03/07 16:37:58  wenger
// Phase 2 of "upload and visualize data" -- mostly working, I think,
// but still needs chem shift reference capability and hasn't been
// hooked up to Dimitri's upload scripts yet.
//
// Revision 1.1  2006/08/21 21:01:11  wenger
// Added second summary page for direct access to all large-size
// visualizations; updated all tests accordingly.
//

// ========================================================================

package star2devise;

import java.io.*;
import java.util.*;

public class S2DSummaryHtmlLarge extends S2DSummaryHtmlGen {
    //===================================================================
    // VARIABLES

    private static final int DEBUG = 0;

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    public String sizeString()
    {
        return "_large";
    }

    //-------------------------------------------------------------------
    // Constructor.  Opens the html file and writes the header.
    public S2DSummaryHtmlLarge(String name, String longName,
      String accessionNum, Vector localFiles, String htmlDir)
      throws S2DException
    {
	super(name, longName, accessionNum, localFiles, htmlDir);

        if (doDebugOutput(11)) {
	    System.out.println("S2DSummaryHtmlLarge.S2DSummaryHtmlLarge(" +
	      name + ", " + accessionNum + ")");
	}
    }

    //===================================================================
    // PROTECTED METHODS

    //-------------------------------------------------------------------
    // Write the link to the other size of visualizations.
    protected void writeSizeLink() throws IOException
    {
        _writer.write("Large visualizations on this page; " +
	  "<a href=" + _sibling.fileNameShort() +
	  ">normal size</a> visualizations\n");
    }

    //===================================================================
    // PRIVATE METHODS

    //-------------------------------------------------------------------
    // Determine whether to do debug output based on the current debug
    // level settings and the debug level of the output.
    private static boolean doDebugOutput(int level)
    {
    	if (DEBUG >= level || S2DMain._verbosity >= level) {
	    if (level > 0) System.out.print("DEBUG " + level + ": ");
	    return true;
	}

	return false;
    }
}

// ========================================================================
