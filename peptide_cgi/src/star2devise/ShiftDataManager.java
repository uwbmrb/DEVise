// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2000-2009
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// Manages chemical shift info.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.6.6.1  2009/07/01 18:06:00  wenger
// A lot of the SPARTA deltashift processing is in place -- the actual
// data isn't yet coming out right, though.
//
// Revision 1.6  2009/01/28 19:48:01  wenger
// Updated the ShiftDataManager class to work with DNA and RNA chemical
// shift lists.
//
// Revision 1.5  2007/11/15 17:15:37  wenger
// Cleaned out cvs history in source files.
//
// Revision 1.4  2007/08/21 18:56:30  wenger
// Improved debug output -- better verbosity levels, etc.
//
// Revision 1.3  2007/08/20 20:26:10  wenger
// Added -verb command-line flag and property so we can turn on debug
// output without recompiling; added debug_level property corresponding
// to the existing -debug command-line flag.
//
// Revision 1.2  2006/02/01 20:23:14  wenger
// Merged V2_1b4_br_0 thru peptide_cgi_10_8_0_base to the
// trunk.
//
// Revision 1.1.2.4  2005/01/31 21:35:44  wenger
// Slight mods to atomic coordinates template for better highlight
// selection; s2d chem shift ref timeout increased to 120 sec., added
// try-again message if timed out; cleaned up warning/error messages
// somewhat.
//
// ...

// ========================================================================

package star2devise;

import java.io.*;

//The following class maintains data contained in the shift.txt table
// Converted from dsilva's C++ code to Java by Richard Chang, 06/25/1999
public class ShiftDataManager
{
    private static final int DEBUG = 0;

    private static final int MAX_DATA_ENTRIES = 500;

    private boolean _dummy = false;

    private String filename;

    // Residue label name
    private String [] aminoAcidType = new String[MAX_DATA_ENTRIES];

    // Atom name
    private String [] atomName = new String[MAX_DATA_ENTRIES];

    // Standard value of chemical shift
    private double [] chemicalShiftCorr = new double[MAX_DATA_ENTRIES];

    // The range column vals
    private double [] range = new double[MAX_DATA_ENTRIES];

    // Total number of entries in the table
    private int totalNumEntries;


    public class Pair
    {
        public double chemshift;
        public double offset;
    }


    // Constructor which initializes the object by reading the data file
    ShiftDataManager( String filename )
    throws S2DException
    {
        if (doDebugOutput(11, true)) {
            System.out.println("ShiftDataManager(" + filename + ")");
        }

        try
        {
            StreamTokenizer inFile =
                new StreamTokenizer(new FileReader(filename));
            inFile.wordChars('\'', '\'');
            totalNumEntries = 0;
            this.filename = filename;

            // This assumes that each entry corresponds to one line
            while (inFile.nextToken() != inFile.TT_EOF)
            {
                aminoAcidType[totalNumEntries] = inFile.sval;
                inFile.nextToken();
                atomName[totalNumEntries] = inFile.sval;
                inFile.nextToken();
                chemicalShiftCorr[totalNumEntries] = inFile.nval;
                inFile.nextToken();
                range[totalNumEntries] = inFile.nval;

                if (doDebugOutput(31, false)) {
                    System.out.println("  " +
                                       aminoAcidType[totalNumEntries] + " " +
                                       atomName[totalNumEntries] + " " +
                                       chemicalShiftCorr[totalNumEntries] + " " +
                                       range[totalNumEntries]);
                }
                totalNumEntries++;
            }

        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + e.toString() );
            throw new S2DError("Unable to open or read shift data file " +
                               filename);
        } catch (IOException e) {
            System.err.println("IO Exception: " + e.toString() );
            throw new S2DError("Unable to open or read shift data file " +
                               filename);
        }
    } // end constructor

    // Constructor for dummy version that always returns zeroes.
    ShiftDataManager()
    {
        if (doDebugOutput(11, true)) {
            System.out.println("ShiftDataManager()");
        }

        _dummy = true;
    }


    // A function that takes as input arguments a residue name and an
    // atom name and returns a pair of values -- standard value of
    // chemical shift and the range. Also the reference parameter.
    public Pair returnValues(String in_aminoAcidType, String in_atomName)
    throws S2DException
    {
        if (doDebugOutput(21, true)) {
            System.out.println("ShiftDataManager.returnValues(" +
                               in_aminoAcidType + ", " + in_atomName + ")");
        }

        Pair retValues = new Pair();

        if (_dummy) {
            retValues.chemshift = 0.0;
            retValues.offset    = 0.0;
            return retValues;
        }

        // Initialize with default error values
        retValues.chemshift = -1.0;
        retValues.offset    = -1.0;

        int position = 0;

        boolean foundAminoAcidType = false;
        while ((!foundAminoAcidType) && position < totalNumEntries) {
            if (in_aminoAcidType.equals(aminoAcidType[position])) {
                foundAminoAcidType = true;
            } else {
                position++;
            }
        }

        if (foundAminoAcidType) {
            boolean foundAtomName = false;
            while ((position < totalNumEntries) && (!foundAtomName) &&
                    in_aminoAcidType.equals(aminoAcidType[position])) {
                if (in_atomName.equals(atomName[position])) {
                    foundAtomName = true;
                } else {
                    position++;
                }
            }

            if (!foundAtomName) {
                if (doDebugOutput(21, false)) {
                    throw new S2DWarning("Warning: atom " +
                                         in_atomName + " corresponding to amino acid " +
                                         in_aminoAcidType + " not found in chemical " +
                                         "shift reference table file " + filename);
                }
            }

        } else {
            throw new S2DWarning("Amino acid type " + in_aminoAcidType +
                                 "  not found..... \n");
        }

        retValues.chemshift = chemicalShiftCorr[position];
        retValues.offset  = range[position];
        return retValues;
    } // end function returnValues

    //-------------------------------------------------------------------
    // Determine whether to do debug output based on the current debug
    // level settings and the debug level of the output.
    private static boolean doDebugOutput(int level, boolean doPrint)
    {
        if (DEBUG >= level || S2DMain._verbosity >= level) {
            if (level > 0 && doPrint)
                System.out.print("DEBUG " + level + ": ");
            return true;
        }

        return false;
    }
}
