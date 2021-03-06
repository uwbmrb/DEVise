// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2004-2007
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// Class to get date, version, etc., from chem shift reference data files.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.2  2006/02/01 20:23:10  wenger
// Merged V2_1b4_br_0 thru peptide_cgi_10_8_0_base to the
// trunk.
//
// Revision 1.1.2.2  2004/11/24 16:15:10  wenger
// Final cleanup of major chem shift reference changes, version
// is now 10.5.0.
//
// Revision 1.1.2.1  2004/11/18 19:10:31  wenger
// Peptide-CGI now checks the version of the ChemShift software, since
// the current version of Peptide-CGI needs at least ChemShift 1.4.0.
//

// ========================================================================

package star2devise;

import java.io.File;
import java.text.*;
import java.util.*;

public class S2DCSRFileData extends S2DFileData
{
    //===================================================================
    // VARIABLES

    private static int DEBUG = 0;

    public String fileVersion;

    private static String CSR_VERSION_LABEL = "ChemShift version";

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    /**
     * Get the file data from a chem shift ref file.
     * @param The data set name.
     * @param The frame index of this data set.
     * @param The file number (1-5) of the relevant chem shift reference
     *   data file.
     * @return True iff the data was gotten successfully.
     */
    public boolean getCSRData(String name, int frameIndex, int fileNum,
                              String dataDir)
    {
        if (doDebugOutput(11)) {
            System.out.println("S2DCSRFileData.getCSRData(" +
                               name + ", " + frameIndex + ", " + fileNum + ", " + dataDir);
        }

        fileVersion = null;

        String filename = dataDir + File.separator + name +
                          S2DNames.CSR_SUFFIX + frameIndex + "_" + fileNum +
                          S2DNames.DAT_SUFFIX;

        boolean result = getData(filename);

        if (doDebugOutput(12)) {
            System.out.println("fileVersion: " + fileVersion);
        }

        return result;
    }

    //===================================================================
    // PROTECTED METHODS

    //-------------------------------------------------------------------
    /**
     * Get whatever data is available in the given line of the file.
     * @param The line of the file to process.
     */
    protected void GetDataFromLine(String line) throws ParseException
    {
        // Get the version of ChemShift that created the
        // coordinate chem shift reference file.
        String tmpValue = getLabeledValue(line, CSR_VERSION_LABEL);
        if (tmpValue != null) {
            fileVersion = tmpValue;
            if (doDebugOutput(13)) {
                System.out.println("File version: " + fileVersion);
            }
        }
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
