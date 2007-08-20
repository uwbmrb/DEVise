// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2001-2007
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class implements the output of heteronuclear NOE data.  For each set
// of heteronuclear NOE data, it creates a data file, a session file, an
// individual html file, and a link in the summary html file.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.2  2006/02/01 20:23:11  wenger
// Merged V2_1b4_br_0 thru peptide_cgi_10_8_0_base to the
// trunk.
//
// Revision 1.1.2.8  2004/12/08 23:07:17  wenger
// Oops -- re-fixed deltashift session template; added titles to
// specific html pages; enlarges the JavaScreen.
//
// Revision 1.1.2.7  2004/12/03 17:18:34  wenger
// Added BMRB accession number, PDB ID (if relevant), timestamp and
// Peptide-CGI version number to Peptide-CGI visualizations.
//
// Revision 1.1.2.6  2004/06/16 19:23:30  wenger
// Added headers to data files generated by Peptide-CGI.
//
// Revision 1.1.2.5  2003/09/19 17:54:53  wenger
// Changed cursor for simulated 2D spectrum so that only one amino acid
// is seleted by default; got rid of colon in schema file names (becuase
// of Windows).
//
// Revision 1.1.2.4  2003/05/14 21:45:52  wenger
// Changed "/"s in file names to File.separator (hope I got them all!).
//
// Revision 1.1.2.3  2003/05/14 20:10:47  wenger
// Split generated html and data files into separate directories (for
// better security); moved html and session templates out of main
// html and session directories.
//
// Revision 1.1.2.2  2003/05/09 16:21:06  wenger
// Removed case-sensitivity in residue labels.
//
// Revision 1.1.2.1  2003/04/22 21:58:14  wenger
// Added package name to peptide-cgi java code and put everything into
// a single jar file; version is now 6.0.
//
// Revision 1.3.12.2  2003/04/09 18:02:12  wenger
// First version of visualization-server capability now in place; still
// needs some fixes.
//
// Revision 1.3.12.1  2003/01/14 16:51:48  wenger
// Merged V2_1b3_br_0 thru V2_1b3_br_end to V2_1b4_br.
//
// Revision 1.3.10.4  2002/11/01 17:40:14  wenger
// Fixed bug 013 (s2d fails if no write permission on output files).
//
// Revision 1.3.10.3  2002/10/31 22:17:34  wenger
// Changed Exception output to use toString() instead of getMessage()
// because that (at least sometimes) produces more complete information.
//
// Revision 1.3.10.2  2002/08/21 20:40:49  wenger
// Selection of data set to view now works, but there is not yet selection
// on the data linked to the 3D view.
//
// Revision 1.3.10.1  2002/08/21 14:21:29  wenger
// Working on 4096-type 3D visualization -- added data and view to show
// list of available data sets.
//
// Revision 1.3  2001/12/11 20:23:34  wenger
// First version of bond-visualization generation; added RCS Id string to
// schema files; manually added environment variables to data source
// definitions.
//
// Revision 1.2  2001/03/08 20:33:24  wenger
// Merged changes from no_collab_br_0 thru no_collab_br_2 from the branch
// to the trunk.
//
// Revision 1.1.2.1  2001/02/09 16:57:12  wenger
// Added heteronuclear NOE; made T1 and T2 relaxation errors optional
// (conversion doesn't fail if they are not found); added an X margin of
// 0.5 in all sessions; updated star file list; misc. minor cleanups.
//

// ========================================================================

package star2devise;

import java.io.*;
import java.util.*;

public class S2DHetNOE {
    //===================================================================
    // VARIABLES

    private static final int DEBUG = 0;

    private String _name;
    private String _longName;
    private String _dataDir;
    private String _sessionDir;
    private S2DSummaryHtml _summary;

    private String _title;
    private String _shortName;

    private String[] _resSeqCodes;
    private String[] _resLabels;
    private String[] _hetNOEValues;
    private String[] _hetNOEErrors;

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    // Constructor.
    public S2DHetNOE(String name, String longName, String dataDir,
      String sessionDir, S2DSummaryHtml summary, String frequency,
      String atom1Name, String atom2Name, String[] resSeqCodes,
      String[] resLabels, String[] hetNOEValues, String[] hetNOEErrors)
      throws S2DException
    {
        if (doDebugOutput(11)) {
	    System.out.println("S2DHetNOE.S2DHetNOE(" + name + ")");
	}
        _name = name;
        _longName = longName;
        _dataDir = dataDir;
        _sessionDir = sessionDir;
        _summary = summary;

	_shortName = "Het NOE (" + frequency + ") " + atom1Name +
	  " " + atom2Name;
	_title = "Heteronuclear NOE (" + frequency + " MHz) " + atom1Name +
	  " " + atom2Name;

        _resSeqCodes = resSeqCodes;
        _resLabels = S2DUtils.arrayToUpper(resLabels);
        _hetNOEValues = hetNOEValues;
        _hetNOEErrors = hetNOEErrors;
    }

    //-------------------------------------------------------------------
    // Write the heteronuclear NOE values for this data.
    public void writeHetNOE(int frameIndex) throws S2DException
    {
        if (doDebugOutput(11)) {
	    System.out.println("S2DHetNOE.writeHetNOE()");
	}

	try {
	    //
	    // Write the heteronuclear NOE values to the data file.
	    //
            FileWriter hetNOEWriter = S2DFileWriter.create(_dataDir +
	      File.separator + _name + S2DNames.HETERONUCLEAR_NOE_SUFFIX +
	      frameIndex + S2DNames.DAT_SUFFIX);

	    hetNOEWriter.write("# Data: heteronuclear NOE for " + _name + "\n");
	    hetNOEWriter.write("# Schema: bmrb-NOE\n");
	    hetNOEWriter.write("# Attributes: Residue_seq_code; " +
	      "Residue_label; NOE_value; NOE_error\n");
            hetNOEWriter.write("# Peptide-CGI version: " +
	      S2DMain.PEP_CGI_VERSION + "\n");
            hetNOEWriter.write("# Generation date: " +
	      S2DMain.getTimestamp() + "\n");
	    hetNOEWriter.write("#\n");

	    for (int index = 0; index < _resSeqCodes.length; index++) {
	        hetNOEWriter.write(_resSeqCodes[index] + " " +
		  _resLabels[index] + " " + _hetNOEValues[index] + " " +
		  _hetNOEErrors[index] + "\n");
	    }

	    hetNOEWriter.close();

	    //
	    // Write the session file.
	    //
	    String info = "Visualization of " + _longName;
	    S2DSession.write(_sessionDir, S2DUtils.TYPE_HETNOE,
	      _name, frameIndex, info, _title);

	    //
	    // Write the session-specific html file.
	    //
	    S2DSpecificHtml.write(_summary.getHtmlDir(), S2DUtils.TYPE_HETNOE,
	      _name, frameIndex, _title);

	    //
	    // Write the link in the summary html file.
	    //
	    _summary.writeHetNOE(_title, frameIndex, _resSeqCodes.length);

        } catch(IOException ex) {
	    System.err.println(
	      "IOException writing heteronuclear NOE values: " +
	      ex.toString());
	    throw new S2DError("Can't write heteronuclear NOE values");
	}
    }

    //-------------------------------------------------------------------
    /**
     * Add heteronuclear NOE sets to the data set list.
     * @param The data set list.
     * @param The frame index.
     */
    public void addHetNOEData(Vector dataSets, int frameIndex)
    {
        // Note: attribute names must match the bmrb-NOE schema.
	String dataSource = _name +
	  S2DNames.HETERONUCLEAR_NOE_SUFFIX + frameIndex;
        dataSets.addElement(new S2DDatasetInfo(_shortName, dataSource,
	  "NOE_value", "bmrb-NOE", "NOE"));
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
