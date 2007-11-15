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

// This class is used to convert a "base" session file to a session file
// specific to a particular data set.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.6  2007/08/21 18:56:30  wenger
// Improved debug output -- better verbosity levels, etc.
//
// Revision 1.5  2007/08/20 20:26:09  wenger
// Added -verb command-line flag and property so we can turn on debug
// output without recompiling; added debug_level property corresponding
// to the existing -debug command-line flag.
//
// Revision 1.4  2006/05/26 16:50:55  wenger
// Merged peptide_cgi_jmol_proto_br_0 thru peptide_cgi_jmol_proto_br_1
// to the trunk.
//
// Revision 1.3.2.1  2006/02/20 21:57:40  wenger
// Peptide-CGI now generates data, sessions, etc., that use
// Jmol for 3D molecule visualization.
//
// ...

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
        if (doDebugOutput(11)) {
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
	    baseName = "atom_coord_jmol.base";
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

		if (doDebugOutput(15)) {
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

		if (doDebugOutput(15)) {
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
        if (doDebugOutput(11)) {
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
        if (doDebugOutput(11)) {
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
