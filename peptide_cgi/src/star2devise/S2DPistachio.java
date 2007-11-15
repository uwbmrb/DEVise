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

// This class calculates and writes out the per-residue Pistachio
// values.  It also creates the session file and visualization-specific
// html file for the Pistachio visualization.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.6  2007/10/02 18:54:24  wenger
// More improvements to error and warning messages, including printing
// fewer at the default verbosity setting.
//
// Revision 1.5  2007/10/01 21:32:29  wenger
// Changes to how we get chemical shift entity ID values: added check for
// _Atom_chem_shift.Entity_assembly_ID if _Atom_chem_shift.Entity_ID is
// not found; change "?" to "1" in values.  This makes the new test50 work
// at least somewhat, but that still needs more checking.  Also added
// some more error checking for problems I found while working on this.
//
// Revision 1.4  2007/08/20 20:26:08  wenger
// Added -verb command-line flag and property so we can turn on debug
// output without recompiling; added debug_level property corresponding
// to the existing -debug command-line flag.
//
// Revision 1.3  2006/02/01 21:34:32  wenger
// Merged peptide_cgi_10_8_0_br_0 thru peptide_cgi_10_8_0_br_2
// to the trunk.
//
// ...

// ========================================================================

package star2devise;

import java.io.*;
import java.util.*;

public class S2DPistachio {
    //===================================================================
    // VARIABLES

    private static final int DEBUG = 0;

    private String _name;
    private String _dataDir;
    private String _sessionDir;
    private S2DSummaryHtml _summary;

    private int[] _resSeqCodes;
    private String[] _residueLabels;
    private String[] _atomNames;
    private double[] _meritVals;

    private boolean[] _residueHasData;
    private float[] _backboneGE95;
    private float[] _backboneLT95;
    private float[] _sideChainGE95;
    private float[] _sideChainLT95;
    private float[] _hGE95;
    private float[] _hLT95;

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    // Constructor.
    public S2DPistachio(String name, String dataDir, String sessionDir,
      S2DSummaryHtml summary, int[] resSeqCodes, String[] residueLabels,
      String[] atomNames, double[] meritVals)
      throws S2DException
    {
        if (doDebugOutput(11)) {
	    System.out.println("S2DPistachio.S2DPistachio(" + name +
	      ")");
	}

	_name = name;
	_dataDir = dataDir;
	_sessionDir = sessionDir;
	_summary = summary;

	_resSeqCodes = resSeqCodes;
	_residueLabels = residueLabels;
	_atomNames = atomNames;
	_meritVals = meritVals;

	calculatePistachioValues();
    }

    //-------------------------------------------------------------------
    // Write the Pistachio values for this data.
    public void writePistachio(int frameIndex) throws S2DException
    {
        if (doDebugOutput(11)) {
	    System.out.println("S2DChemShift.writePistachio()");
	}

	//
	// Write the Pistachio values to the appropriate data file.
	//
        FileWriter pistachioWriter = null;
	try {
            pistachioWriter = S2DFileWriter.create(_dataDir + File.separator +
	      _name + S2DNames.PISTACHIO_SUFFIX + frameIndex +
	      S2DNames.DAT_SUFFIX);
	    pistachioWriter.write("# Data: Assignment figure of merit " +
	      "values for " + _name + "\n");
	    pistachioWriter.write("# Schema: bmrb-Pistachio\n");
	    pistachioWriter.write("# Attributes: Residue_seq_code; " +
	      "backbone >= 95%; backbone < 95%; side chain >= 95%; " +
	      "side chain < 95%; H >= 95%; H < 95%\n");
            pistachioWriter.write("# Peptide-CGI version: " +
	      S2DMain.PEP_CGI_VERSION + "\n");
            pistachioWriter.write("# Generation date: " +
	      S2DUtils.getCurrentDateStr() + "\n");
	    pistachioWriter.write("#\n");

        } catch(IOException ex) {
	    System.err.println("IOException writing Pistachio values: " +
	      ex.toString());
	    throw new S2DError("Can't write Pistachio values");
	}

	try {
            for (int index = 0; index < _residueHasData.length; ++index) {
		if (_residueHasData[index]) {
	            pistachioWriter.write(index + " " +
		      _backboneGE95[index] + " " +
		      _backboneLT95[index] + " " +
		      _sideChainGE95[index] + " " +
		      _sideChainLT95[index] + " " +
		      _hGE95[index] + " " +
		      _hLT95[index] + "\n");
	        }
	    }

	    //
	    // Write the session file
	    //
	    String info = "Visualization of " + _name +
	      " assignment figure of merit data";
	    S2DSession.write(_sessionDir, S2DUtils.TYPE_PISTACHIO,
	      _name, frameIndex, info);

	    //
	    // Write the session-specific html file.
	    //
	    S2DSpecificHtml.write(_summary.getHtmlDir(),
	      S2DUtils.TYPE_PISTACHIO, _name, frameIndex,
	      "Assignment figure of merit data");

	    //
	    // Write the link in the summary html file.
	    //
	    _summary.writePistachio(frameIndex);

	} catch (IOException ex) {
	    System.err.println("IOException writing Pistachio values: " +
	      ex.toString());
	    throw new S2DError("Unable to write Pistachio values for " +
	      frameIndex);
	} finally {
	    try {
	        pistachioWriter.close();
	    } catch (IOException ex) {
	        System.err.println("IOException: " + ex.toString());
	    }
	}
    }

    //===================================================================
    // PRIVATE METHODS

    //-------------------------------------------------------------------
    // Calculate the Pistachio values we want to visualize for this
    // data set.
    private void calculatePistachioValues() throws S2DException
    {
        if (doDebugOutput(11)) {
	    System.out.println("S2DChemShift.calculatePistachioValues()");
	}

        // We calculate lastResidue this way to allow for the data not
        // being strictly ordered by residue.
        int lastResidue = 0;
        for (int index = 0; index < _resSeqCodes.length; index++) {
            lastResidue = Math.max(lastResidue, _resSeqCodes[index]);
        }

	// Residues normally start with 1 -- skip the first element of
	// these arrays to make things simpler.
        _residueHasData = new boolean[lastResidue + 1];
        _backboneGE95 = new float[lastResidue + 1];
        _backboneLT95 = new float[lastResidue + 1];
        _sideChainGE95 = new float[lastResidue + 1];
        _sideChainLT95 = new float[lastResidue + 1];
        _hGE95 = new float[lastResidue + 1];
        _hLT95 = new float[lastResidue + 1];

	for (int index = 0; index < _residueHasData.length; ++index) {
	    _residueHasData[index] = false;
	}

	if (_resSeqCodes.length < 1) {
	    if (doDebugOutput(1)) {
	        System.out.println("No Pistachio values calculated because " +
	          "we have no residue sequence codes");
	    }
	    return;
	}

	TempData td = new TempData();

	int currResSeqCode = -1; // invalid value
	int prevResSeqCode = -1; // invalid value
	String residueLabel = null;
	for (int index = 0; index < _resSeqCodes.length; ++index) {

	    currResSeqCode = _resSeqCodes[index];

	    if (currResSeqCode != prevResSeqCode) {
		if (currResSeqCode < prevResSeqCode) {
		    throw new S2DError("Residue numbers must be " +
		      "monotonically increasing for Pistachio data " +
		      "(" + currResSeqCode + " after " + prevResSeqCode +
		      ")");
		}

		if (prevResSeqCode != -1) {
		    td.save(prevResSeqCode, residueLabel);
		}

		td.reset();
		residueLabel = _residueLabels[index];

		prevResSeqCode = currResSeqCode;
	    }

	    td.addAnAtom(_atomNames[index], _meritVals[index]);
	}

	td.save(currResSeqCode, residueLabel);
    }

    // ========================================================================

    // This class holds the data for one residue as we work our way
    // through the data for that residue.
    class TempData {
	public int _backboneTotalCount = 0;
	public int _backboneGE95Count = 0;
	public int _sideChainTotalCount = 0;
	public int _sideChainGE95Count = 0;
	public int _hTotalCount = 0;
	public int _hGE95Count = 0;

	public void reset()
	{
	    _backboneTotalCount = 0;
	    _backboneGE95Count = 0;
	    _sideChainTotalCount = 0;
	    _sideChainGE95Count = 0;
	    _hTotalCount = 0;
	    _hGE95Count = 0;
	}

	public void addAnAtom(String atomName, double meritVal)
	{
	    if (S2DNames.ATOM_H.equals(atomName)) {
		++_hTotalCount;
		++_backboneTotalCount;
	        if (meritVal >= 0.95) {
		    ++_hGE95Count;
		    ++_backboneGE95Count;
		}

	    } else if (S2DNames.ATOM_C.equals(atomName) ||
	      S2DNames.ATOM_CA.equals(atomName) ||
	      S2DNames.ATOM_N.equals(atomName)) {
		++_backboneTotalCount;
	        if (meritVal >= 0.95) {
		    ++_backboneGE95Count;
		}

	    } else {
		++_sideChainTotalCount;
	        if (meritVal >= 0.95) {
		    ++_sideChainGE95Count;
		}
	    }
	}

	public void save(int resSeqCode, String residueLabel)
	{
	    if (doDebugOutput(13)) {
	        System.out.println("S2DPistachio.TempData.save(" +
	          resSeqCode + ", " + residueLabel + ")");
	    }

            _residueHasData[resSeqCode] = true;

	    try {
	        S2DAtomCounts counts = S2DAtomCounts.getInstance();

		int idealBackboneCount = counts.getPistBackCount(residueLabel);
	        if (idealBackboneCount > 0 && _backboneTotalCount > 0) {
	            _backboneGE95[resSeqCode] = (float)_backboneGE95Count /
		        (float)idealBackboneCount;
	            _backboneLT95[resSeqCode] = (float)(_backboneTotalCount -
		      _backboneGE95Count) / (float)idealBackboneCount;
	        } else {
	            _backboneGE95[resSeqCode] = 0.0f;
	            _backboneLT95[resSeqCode] = 0.0f;
	        }

		int idealSideChainCount = counts.getPistSideCount(residueLabel);
	        if (idealSideChainCount > 0 && _sideChainTotalCount > 0) {
	            _sideChainGE95[resSeqCode] = (float)_sideChainGE95Count /
		      (float)idealSideChainCount;
	            _sideChainLT95[resSeqCode] = (float)(_sideChainTotalCount -
		      _sideChainGE95Count) / (float)idealSideChainCount;
	        } else {
	            _sideChainGE95[resSeqCode] = 0.0f;
	            _sideChainLT95[resSeqCode] = 0.0f;
	        }

		int idealHCount = counts.getPistHCount(residueLabel);
	        if (idealHCount > 0 && _hTotalCount > 0) {
	            _hGE95[resSeqCode] = (float)_hGE95Count /
		      (float)idealHCount;
	            _hLT95[resSeqCode] = (float)(_hTotalCount - _hGE95Count) /
		      (float)idealHCount;
	        } else {
	            _hGE95[resSeqCode] = 0.0f;
	            _hLT95[resSeqCode] = 0.0f;
	        }
	    } catch (S2DException ex) {
		S2DWarning warning = new S2DWarning(
		  "Exception saving Pistachio values " + ex);
		if (doDebugOutput(1)) {
	            System.err.println(warning);
		}
	    }
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
