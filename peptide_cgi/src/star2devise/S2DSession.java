// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2001-2005
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
// Revision 1.2  2006/02/01 20:23:12  wenger
// Merged V2_1b4_br_0 thru peptide_cgi_10_8_0_base to the
// trunk.
//
// Revision 1.1.2.14.6.3  2005/11/04 17:56:27  wenger
// Added command-line arguments, config, properties, etc., to
// specify LACS processing level, LACS filename template, and
// LACS URL -- so now we have the option to have the software
// automatically try to process the appropriate LACS file;
// updated some tests accordingly.  Test_all now names failed
// tests at the end.
//
// Revision 1.1.2.14.6.2  2005/11/02 20:33:18  wenger
// LACS visualization now has correct axis labels.
//
// Revision 1.1.2.14.6.1  2005/10/14 21:19:31  wenger
// Most LACS processing now in place -- still needs lots of cleanup,
// though.
//
// Revision 1.1.2.14  2005/03/22 20:34:38  wenger
// Merged ambiguity_vis2_br_0 thru ambiguity_vis2_br_3 to V2_1b4_br.
//
// Revision 1.1.2.13.4.1  2005/03/11 23:33:20  wenger
// Ambiguity visualization is mostly working (incorporating some feedback
// from Eldon); still needs some cleanup to the calculations, though.
//
// Revision 1.1.2.13  2005/01/31 23:02:54  wenger
// Merged pistachio_vis_br_0 thru pistachio_vis_br_1a to V2_1b4_br.
//
// Revision 1.1.2.12  2004/12/03 21:04:14  wenger
// Info view now has date without time, and no Peptide-CGI version
// number (as requested by Eldon); they are now in the view help.
//
// Revision 1.1.2.11  2004/12/03 17:18:34  wenger
// Added BMRB accession number, PDB ID (if relevant), timestamp and
// Peptide-CGI version number to Peptide-CGI visualizations.
//
// Revision 1.1.2.10.2.1  2005/01/12 20:46:42  wenger
// Pistachio processing is now integrated into the normal Peptide-CGI
// processing -- the Pistachio visualization is generated autmatically
// if the Pistachio data exists.  (Still needs some cleanup, though.)
// (We generate the Pistachio visualization by generating a temporary
// mmCIF file with coordinates -- that is then run through the normal
// coordinate processing to generate the DEVise file with Pistachio
// coordinates.)
//
// Revision 1.1.2.10  2004/09/14 16:47:15  wenger
// Deltashift and CSI sessions now only show CB shifts when there
// are "real" (not GLY HA3->CB) CB shifts to show.
//
// Revision 1.1.2.9  2004/06/23 17:39:26  wenger
// Preliminary version of chem shift reference visualization 3 in
// place; cleaned up 4317 chem shift ref test data; changed fonts
// in chem shift ref visualization 1.
//
// Revision 1.1.2.8  2004/06/16 19:23:31  wenger
// Added headers to data files generated by Peptide-CGI.
//
// Revision 1.1.2.7  2004/01/26 18:55:37  wenger
// Incorporated "Eldon's" chemical shift reference session; added help
// pages for both chem shift ref visualizations (with no help info
// for now).
//
// Revision 1.1.2.6  2004/01/22 16:43:49  wenger
// Finished to-do item 020 (replace "/" with File.separator), other
// minor cleanups.
//
// Revision 1.1.2.5  2003/10/23 18:08:57  wenger
// Basic chem shift ref stuff is in place -- session and specific html
// files are generated, summary html file has link, etc.  The main thing
// left is the mechanics of calling Dan's chem shift ref software --
// right now I am just using a script that creates dummy chem shift
// ref data files.
//
// Revision 1.1.2.4  2003/05/14 23:35:34  wenger
// Data and session files can now be in non-standard directories.
//
// Revision 1.1.2.3  2003/05/14 21:45:52  wenger
// Changed "/"s in file names to File.separator (hope I got them all!).
//
// Revision 1.1.2.2  2003/05/14 20:10:47  wenger
// Split generated html and data files into separate directories (for
// better security); moved html and session templates out of main
// html and session directories.
//
// Revision 1.1.2.1  2003/04/22 21:58:15  wenger
// Added package name to peptide-cgi java code and put everything into
// a single jar file; version is now 6.0.
//
// Revision 1.7.18.3  2003/04/09 18:02:13  wenger
// First version of visualization-server capability now in place; still
// needs some fixes.
//
// Revision 1.7.18.2  2003/03/19 17:43:02  wenger
// Fixed bug 019 (problem with residue lists in the atomic coordinate
// sessions).
//
// Revision 1.7.18.1  2003/01/14 16:51:49  wenger
// Merged V2_1b3_br_0 thru V2_1b3_br_end to V2_1b4_br.
//
// Revision 1.7.16.7  2002/11/07 20:54:58  wenger
// Peptide-CGI now re-uses cached atomic coordinate data as appropriate
// (to-do 018).
//
// Revision 1.7.16.6  2002/11/02 00:08:34  wenger
// Added generation date to session files (prep. for re-using cached
// PDB data).
//
// Revision 1.7.16.5  2002/11/01 23:43:00  wenger
// Fixed bug 015 (data values not displayed correctly in 3D visualization
// because of data source definition problems).
//
// Revision 1.7.16.4  2002/11/01 17:40:14  wenger
// Fixed bug 013 (s2d fails if no write permission on output files).
//
// Revision 1.7.16.3  2002/10/31 22:17:35  wenger
// Changed Exception output to use toString() instead of getMessage()
// because that (at least sometimes) produces more complete information.
//
// Revision 1.7.16.2  2002/08/21 20:40:50  wenger
// Selection of data set to view now works, but there is not yet selection
// on the data linked to the 3D view.
//
// Revision 1.7.16.1  2002/08/21 14:21:30  wenger
// Working on 4096-type 3D visualization -- added data and view to show
// list of available data sets.
//
// Revision 1.7  2001/10/10 22:37:33  wenger
// First version of atomic coordinate extraction and visualization (atoms,
// not bonds, only tested on 4096 -- coordinates must be in same NMR-STAR
// file as other data); fixed various minor problems with peptide-cgi code.
//
// Revision 1.6  2001/05/08 18:24:18  wenger
// Fixed problem getting residue count if a star file contains info for
// more than one protein; added residue counts to 'all shifts' and 'H
// vs. N' visualizations.
//
// Revision 1.5  2001/04/17 17:09:10  wenger
// Added display of H vs. N chem shifts.
//
// Revision 1.4  2001/04/16 19:49:11  wenger
// Added display of all chem shifts by amino acid.
//
// Revision 1.3  2001/03/08 20:33:24  wenger
// Merged changes from no_collab_br_0 thru no_collab_br_2 from the branch
// to the trunk.
//
// Revision 1.2.2.1  2001/02/09 16:57:13  wenger
// Added heteronuclear NOE; made T1 and T2 relaxation errors optional
// (conversion doesn't fail if they are not found); added an X margin of
// 0.5 in all sessions; updated star file list; misc. minor cleanups.
//
// Revision 1.2  2001/01/19 15:39:06  wenger
// Added T1 and T2 relaxation; removed some unnecessary variables from
// coupling constants; added schema files to installation, unified T1
// and T2 relaxation schema.
//
// Revision 1.1  2001/01/17 20:00:07  wenger
// Restructured the peptide-cgi code to make it much more maintainable.
//

// ========================================================================

package star2devise;

import java.io.*;
import java.util.*;

public class S2DSession {
    //===================================================================
    // VARIABLES

    private static final int DEBUG = 0;

    private static String _jsDataDir = null;
    // Note: keeping "/" instead of File.separator here because session
    // files are only used on UNIX...
    private static final String _defaultJSDataDir = "bmrb/dynamic_data";

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    static void setJSDataDir(String dir)
    {
        _jsDataDir = dir;
    }

    //-------------------------------------------------------------------
    static void write(String sessionDir, int dataType, String name,
      int frameIndex, String info) throws S2DException
    {
        write(sessionDir, dataType, name, frameIndex, info, null);
    }

    //-------------------------------------------------------------------
    static void write(String sessionDir, int dataType, String name,
      int frameIndex, String info, String title) throws S2DException
    {
        write(sessionDir, dataType, name, frameIndex, info, title, true);
    }

    //-------------------------------------------------------------------
    static void write(String sessionDir, int dataType, String name,
      int frameIndex, String info, String title, boolean hasRealCBShifts)
      throws S2DException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DSession.write(" + sessionDir + ", " +
	      dataType + ", " + name + ", " + frameIndex + ")");
	}

	String baseName;
	String dataSuffix;
	String sessionSuffix;

	// The "main" data source in the base file.
	String searchString1 = null;

	// The "main" data source in the file we're writing.
        String replaceString1 = null;

	// The residue count data source in the base file.
	String searchString2 = null;

	// The residue count data source for the file we're writing.
        String replaceString2 = null;

	// The summary data source in the base file.
	String searchString3 = null;

	// The summary data for the 3D atomic coordinates visualization.
	String replaceString3 = null;

	// The dummy visualization info string in the base file.
	String visInfoSearchString = "Visualization info";

	// The full visualization info string.
	String visInfo = info + " generated by Peptide-CGI " +
	  S2DMain.PEP_CGI_VERSION + " at " + S2DMain.getTimestamp();

	// The dummy visualization short info string in the base file.
	String visShortInfoSearchString = "Visualization short info";

	// The full visualization short info string.
	String visShortInfo = info + " generated on " +
	  S2DMain.getShortTimestamp();

	switch (dataType) {
	case S2DUtils.TYPE_DELTASHIFT:
	    baseName = "deltashift.base";
	    dataSuffix = S2DNames.DELTASHIFT_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4081d1";
	    break;

	case S2DUtils.TYPE_CSI:
	    baseName = "csi.base";
	    dataSuffix = S2DNames.CSI_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4081c1";
	    break;

	case S2DUtils.TYPE_PCT_ASSIGN:
	    baseName = "percent.base";
	    dataSuffix = S2DNames.PERCENT_ASSIGN_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4081p1";
	    break;

	case S2DUtils.TYPE_ALL_CHEM_SHIFTS:
	    baseName = "allshift.base";
	    dataSuffix = S2DNames.ALL_CHEM_SHIFT_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4267as1";
	    searchString2 = "4267rc1";
	    replaceString2 = name + S2DNames.RES_COUNT_SUFFIX + frameIndex;
	    break;

	case S2DUtils.TYPE_HVSN_CHEM_SHIFTS:
	    baseName = "h_vs_n.base";
	    dataSuffix = S2DNames.HVSN_CHEM_SHIFT_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4267hn1";
	    searchString2 = "4267rc1";
	    replaceString2 = name + S2DNames.RES_COUNT_SUFFIX + frameIndex;
	    break;

        case S2DUtils.TYPE_COUPLING:
	    baseName = "coupling.base";
	    dataSuffix = S2DNames.COUPLING_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4096g1";
	    break;

/*TEMP
        case S2DUtils.TYPE_HXRATES:
	    baseName = "hxrates.base";
	    dataSuffix = S2DNames.HX_RATE_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4096r";
	    break;

        case S2DUtils.TYPE_ORDER:
	    baseName = "order.base";
	    dataSuffix = S2DNames.
	    sessionSuffix = dataSuffix;
	    searchString1 = "";
	    break;
TEMP*/

        case S2DUtils.TYPE_T1_RELAX:
	    baseName = "relax.base";
	    dataSuffix = S2DNames.T1_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4267t11";
	    break;

        case S2DUtils.TYPE_T2_RELAX:
	    baseName = "relax.base";
	    dataSuffix = S2DNames.T2_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4267t11";
	    break;

        case S2DUtils.TYPE_HETNOE:
	    baseName = "het_noe.base";
	    dataSuffix = S2DNames.HETERONUCLEAR_NOE_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4267n1";
	    break;

        case S2DUtils.TYPE_ATOMIC_COORDS:
	    baseName = "atom_coord.base";
	    dataSuffix = S2DNames.ATOMIC_COORD_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4096ac1";
	    searchString3 = "4096md";
	    replaceString3 = name + S2DNames.SUMMARY_DATA_SUFFIX;
	    break;

        case S2DUtils.TYPE_CHEM_SHIFT_REF1:
	    baseName = "chem_shift_ref.base";
	    dataSuffix = S2DNames.CSR_SUFFIX;
	    sessionSuffix = S2DNames.CSR1_SUFFIX;
	    searchString1 = "4974csr1";
	    break;

        case S2DUtils.TYPE_CHEM_SHIFT_REF2:
	    baseName = "chem_shift_ref2.base";
	    dataSuffix = S2DNames.CSR_SUFFIX;
	    sessionSuffix = S2DNames.CSR2_SUFFIX;
	    searchString1 = "4974csr1";
	    break;

        case S2DUtils.TYPE_CHEM_SHIFT_REF3:
	    baseName = "chem_shift_ref3.base";
	    dataSuffix = S2DNames.CSR_SUFFIX;
	    sessionSuffix = S2DNames.CSR3_SUFFIX;
	    searchString1 = "4974csr1";
	    break;

	case S2DUtils.TYPE_PISTACHIO:
	    baseName = "pistachio.base";
	    dataSuffix = S2DNames.PISTACHIO_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "6318ps1";
	    searchString2 = "6318psac1";
	    replaceString2 = name + S2DNames.PISTACHIO_ATOMIC_COORD_SUFFIX +
	      frameIndex;
	    searchString3 = "6318rl1";
	    replaceString3 = name + S2DNames.RES_LIST_SUFFIX + frameIndex;
	    break;

	case S2DUtils.TYPE_AMBIGUITY:
	    baseName = "ambiguity.base";
	    dataSuffix = S2DNames.AMBIGUITY_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4081am1";
	    searchString2 = "4081amac1";
	    replaceString2 = name + S2DNames.AMBIGUITY_ATOMIC_COORD_SUFFIX +
	      frameIndex;
	    searchString3 = "4081rl1";
	    replaceString3 = name + S2DNames.RES_LIST_SUFFIX + frameIndex;
	    break;

	case S2DUtils.TYPE_LACS:
	    baseName = "lacs.base";
	    dataSuffix = S2DNames.LACS_SUFFIX;
	    sessionSuffix = dataSuffix;
	    searchString1 = "4081lacsl1";
	    replaceString1 = name + S2DNames.LACS_LINE_SUFFIX + frameIndex;
	    searchString2 = "4081lacsp1";
	    replaceString2 = name + S2DNames.LACS_POINT_SUFFIX + frameIndex;
	    searchString3 = "4081lacsc1";
	    replaceString3 = name + S2DNames.LACS_COORD_SUFFIX + frameIndex;
	    break;

	default:
	    throw new S2DError("Illegal data type: " + dataType);
	}

        String outFileName = sessionDir + File.separator + name +
	  sessionSuffix + frameIndex + ".ds";

	try {
            FileWriter writer = S2DFileWriter.create(outFileName);
	    BufferedReader reader = new BufferedReader(new FileReader(
	      "session_templates" + File.separator + baseName));

	    writer.write("# DEVise session file generated by S2DSession\n");
            writer.write("# " + S2DSummaryHtml.VERSION_LABEL + ": {" +
	      S2DMain.PEP_CGI_VERSION + "}\n");
	    writer.write("# " + S2DSummaryHtml.GEN_DATE_LABEL + ": {" +
	      S2DMain.getTimestamp() + "}\n\n");

	    // The "main" data source for the file we're writing.
	    if (replaceString1 == null) {
                replaceString1 = name + dataSuffix + frameIndex;
	    }

	    boolean printSummaryData = false;
	    boolean printedSummaryData = false;
            String line;
	    while ((line = reader.readLine()) != null) {

		if (DEBUG >= 3) {
		    System.out.println("Input line: " + line);
		}

		if (dataType == S2DUtils.TYPE_ATOMIC_COORDS) {
		    if (line.indexOf("dteInsertCatalogEntry") >= 0) {
		        if (line.indexOf(searchString1) >= 0) {
			    // 4096ac1 should get replaced below...
		        } else if (line.indexOf("4096rl1") >= 0) {
			    // 4096rl1 should get replaced below...
		        } else if (line.indexOf(searchString3) >= 0) {
			    // 4096md should get replaced below...
		            printSummaryData = true;
			} else {
			    // Note: I would like to substitute the string
			    // below, but we need to keep the 4096 data
			    // source definitions in place so that the
			    // initial session open works (before the parent
			    // view changes the child view's data source
			    // to an appropriate one).  RKW 2002-11-01.
			    // line = "# data source from template omitted";
			}
		    }

		    line = S2DUtils.replace(line, "4096rl1",
		      name + S2DNames.RES_LIST_SUFFIX + "1");
		}

	        line = S2DUtils.replace(line, searchString1,
		  replaceString1);

                if (searchString2 != null) {
	            line = S2DUtils.replace(line, searchString2,
		      replaceString2);
		}

                if (searchString3 != null) {
	            line = S2DUtils.replace(line, searchString3,
		      replaceString3);
		}

		line = S2DUtils.replace(line, visInfoSearchString, visInfo);
		line = S2DUtils.replace(line, visShortInfoSearchString,
		  visShortInfo);

		if (_jsDataDir != null) {

		    // Don't change label.dat definitions.
		    if (line.indexOf("label.dat") == -1) {

		        // Don't do data directory substitution on
			// unchanged 4096 data sources in 3D sessions.
		        if (dataType != S2DUtils.TYPE_ATOMIC_COORDS ||
		          line.indexOf("4096") == -1) {
		            line = S2DUtils.replace(line, _defaultJSDataDir,
			  _jsDataDir);
		        }
		    }
		}

		if (title != null) {
		    line = S2DUtils.replace(line, "dummy title", title);
		}

	        writer.write(line + "\n");

		if (DEBUG >= 3) {
		    System.out.println("  Output line: " + line);
		}

		if (printSummaryData && !printedSummaryData) {
                    copy3DDataSources(name, sessionDir, writer);
		    printedSummaryData = true;
		}
	    }

	    // For the deltashift and CSI sessions, we have a special
	    // "No CB chem shifts" view to show if we don't have any
	    // "real" CB chem shifts (that is, not counting the special
	    // case for GLY where we stick the HA3 chem shift value in
	    // for CB).
	    if (dataType == S2DUtils.TYPE_DELTASHIFT && !hasRealCBShifts) {
	        writer.write("\n# Show special \"no CB chem shifts\" view\n");
		writer.write("DEVise removeView {View 4}\n");
		writer.write("DEVise insertWindow {View 5} {DEViseWn0}\n");
		writer.write("DEVise setAxisTicks {View 3} {X} 1\n");
	    }

	    if (dataType == S2DUtils.TYPE_CSI && !hasRealCBShifts) {
	        writer.write("\n# Show special \"no CB chem shifts\" view\n");
		writer.write("DEVise removeView {View 4} \n");
		writer.write("DEVise insertWindow {View 7} {DEViseWn0}\n");
		writer.write("DEVise swapView {DEViseWn0} {View 5} {View 7}\n");
	    }

	    reader.close();
	    writer.close();
        } catch(IOException ex) {
	    System.err.println("IOException writing session file: " +
	      ex.toString());
	    throw new S2DError("Can't write session file " + outFileName);
	}
    }

    //-------------------------------------------------------------------
    // Write out the data source definitions we need for the 3D coordinate
    // visualization.  (These are the data sources for all of the available
    // chem shift, etc., data, not the actual coordinate data source.)
    public static void write3DDataSources(Writer writer, Vector dataSets)
      throws IOException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DSession.write3DDataSources()");
	}
	for (int index = 0; index < dataSets.size(); index++) {
	    S2DDatasetInfo info = (S2DDatasetInfo)dataSets.elementAt(index);
	    // Note: keeping "/" instead of File.separator here because
	    // session files can only get used on UNIX...
	    String dataSource = "DEVise dteInsertCatalogEntry . {\"" +
	      info.getDataSourceName() + "\" UNIXFILE " +
	      info.getDataSourceName() + ".dat " + info.getSchemaType() +
	      " $DEVISE_SCHEMA/physical/" + info.getSchemaFile() +
	      " \"\" 100 50 \"$DEVISE_DAT/bmrb/dynamic_data\" \"\"}\n";

	    if (_jsDataDir != null) {
	        dataSource = S2DUtils.replace(dataSource, _defaultJSDataDir,
	          _jsDataDir);
	    }

	    writer.write(dataSource);
        }
    }

    //===================================================================
    // PRIVATE METHODS

    //-------------------------------------------------------------------
    // Copy the data source definitions we need for the 3D coordinate
    // visualization from the file that was generated when we did
    // the processing of the BMRB file.
    public static void copy3DDataSources(String name,
      String sessionDir, Writer writer) throws IOException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DSession.copy3DDataSources()");
	}

	BufferedReader reader = new BufferedReader(new FileReader(
	  sessionDir + File.separator + name +
	  S2DNames.ATOMIC_COORD_DATA_DEF));

	 String line;
	 while ((line = reader.readLine()) != null) {
	    writer.write(line + "\n");
	 }
    }
}

// ========================================================================
