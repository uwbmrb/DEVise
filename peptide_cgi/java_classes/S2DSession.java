// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2001
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class is used to convert a "base" session file to a session file
// specific to a particular data set.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.1  2001/01/17 20:00:07  wenger
// Restructured the peptide-cgi code to make it much more maintainable.
//

// ========================================================================

import java.io.*;

public class S2DSession {
    //===================================================================
    // VARIABLES

    private static final int DEBUG = 0;

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    static void write(String sessionDir, int dataType, int accessionNum,
      int frameIndex) throws S2DException
    {
        write(sessionDir, dataType, accessionNum, frameIndex, null);
    }

    //-------------------------------------------------------------------
    static void write(String sessionDir, int dataType, int accessionNum,
      int frameIndex, String title) throws S2DException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DSession.write(" + sessionDir + ", " +
	      dataType + ", " + accessionNum + ", " + frameIndex + ")");
	}

	String baseName;
	String dataSuffix;
	String searchString;

	switch (dataType) {
	case S2DUtils.TYPE_DELTASHIFT:
	    baseName = "deltashift.base";
	    dataSuffix = S2DNames.DELTASHIFT_SUFFIX;
	    searchString = "4081d1";
	    break;

	case S2DUtils.TYPE_CSI:
	    baseName = "csi.base";
	    dataSuffix = S2DNames.CSI_SUFFIX;
	    searchString = "4081c1";
	    break;

	case S2DUtils.TYPE_PCT_ASSIGN:
	    baseName = "percent.base";
	    dataSuffix = S2DNames.PERCENT_ASSIGN_SUFFIX;
	    searchString = "4081p1";
	    break;

        case S2DUtils.TYPE_COUPLING:
	    baseName = "coupling.base";
	    dataSuffix = S2DNames.COUPLING_SUFFIX;
	    searchString = "4096g1";
	    break;

/*TEMP
        case S2DUtils.TYPE_HXRATES:
	    baseName = "hxrates.base";
	    dataSuffix = S2DNames.HX_RATE_SUFFIX;
	    searchString = "4096r";
	    break;

        case S2DUtils.TYPE_ORDER:
	    baseName = "order.base";
	    dataSuffix = S2DNames.
	    searchString = "";
	    break;
TEMP*/

        case S2DUtils.TYPE_T1_RELAX:
	    baseName = "relax.base";
	    dataSuffix = S2DNames.T1_SUFFIX;
	    searchString = "4267t11";
	    break;

        case S2DUtils.TYPE_T2_RELAX:
	    baseName = "relax.base";
	    dataSuffix = S2DNames.T2_SUFFIX;
	    searchString = "4267t11";
	    break;

	default:
	    throw new S2DError("Illegal data type: " + dataType);
	}

        String outFileName = sessionDir + "/" + accessionNum + dataSuffix +
	  frameIndex + ".ds";

	try {
            FileWriter writer = new FileWriter(outFileName);
	    BufferedReader reader = new BufferedReader(new FileReader(
	      sessionDir + "/" + baseName));

	    writer.write("# DEVise session file generated by S2DSession\n\n");

            String replaceString = accessionNum + dataSuffix + frameIndex;

            String line;
	    while ((line = reader.readLine()) != null) {
	        String line2 = S2DUtils.replace(line, searchString,
		  replaceString);
		if (title != null) {
		    line2 = S2DUtils.replace(line2, "dummy title", title);
		}
	        writer.write(line2 + "\n");
	    }

	    reader.close();
	    writer.close();
        } catch(IOException ex) {
	    System.err.println("IOException writing session file: " +
	      ex.getMessage());
	    throw new S2DError("Can't write session file" + outFileName);
	}
    }
}

// ========================================================================
