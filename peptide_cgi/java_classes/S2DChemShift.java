// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2000-2001
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class implements the calculation and output of chemical shift data.
// For each set of chemical shift data, it creates a data file, a session
// file, an individual html file, and a link in the summary html file.

// ------------------------------------------------------------------------

// $Id$

// $Log$

// ========================================================================

import java.io.*;

import ShiftDataManager.Pair;
import AssgDataManager.AssgEntry;

public class S2DChemShift {
    //===================================================================
    // VARIABLES

    private static final int DEBUG = 0;

    private int _accessionNum;
    private String _dataDir;
    private String _sessionDir;
    private S2DSummaryHtml _summary;

    private int[] _resSeqCodes;
    private String[] _residueLabels;
    private String[] _atomNames;
    private String[] _atomTypes;
    private double[] _chemShiftVals;

    private final String CHEMSHIFT_FILE = "chemshift.txt";
    private ShiftDataManager _refTable;

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    // Constructor.
    public S2DChemShift(int accessionNum, String dataDir, String sessionDir,
      S2DSummaryHtml summary, int[] resSeqCodes, String[] residueLabels,
      String[] atomNames, String[] atomTypes, double[] chemShiftVals)
      throws S2DException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DChemShift.S2DChemShift(" + accessionNum +
	      ")");
	}

	_accessionNum = accessionNum;
	_dataDir = dataDir;
	_sessionDir = sessionDir;
	_summary = summary;

	_resSeqCodes = resSeqCodes;
	_residueLabels = residueLabels;
	_atomNames = atomNames;
	_atomTypes = atomTypes;
	_chemShiftVals = chemShiftVals;

	_refTable = new ShiftDataManager(_dataDir + "/" + CHEMSHIFT_FILE);
    }

    //-------------------------------------------------------------------
    // Write the deltashifts for this data.
    public void writeDeltashifts(int frameIndex) throws S2DException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DChemShift.writeDeltashifts()");
	}

	//
	// Calculate the deltashift values and write them to the data
	// file.
	//
        FileWriter deltashiftWriter = null;
	try {
            deltashiftWriter = new FileWriter(_dataDir + "/" +
	      _accessionNum + S2DNames.DELTASHIFT_SUFFIX + frameIndex +
	      S2DNames.DAT_SUFFIX);
        } catch(IOException ex) {
	    System.err.println("IOException writing deltashifts: " +
	      ex.getMessage());
	    throw new S2DError("Can't write deltashifts");
	}

	int prevResSeqCode = -1; // -1 means invalid
	int currResSeqCode;

	float haDeltashift = 0;
	float cDeltashift = 0;
	float caDeltashift = 0;
	float cbDeltashift = 0;

	int dsCount = 0;

	try {
	    for (int index = 0; index < _resSeqCodes.length; index++) {
	        currResSeqCode = _resSeqCodes[index];

	        if (currResSeqCode != prevResSeqCode) {
		    if (prevResSeqCode != -1) {
	                // We're done with prevSeqCode, so write out its info.
		        deltashiftWriter.write(prevResSeqCode + " " +
			  haDeltashift + " " + cDeltashift + " " +
			  caDeltashift + " " + cbDeltashift + "\n");
	                dsCount++;
		    }

		    prevResSeqCode = currResSeqCode;

		    // Re-initialize the values.
	            haDeltashift = 0;
	            cDeltashift = 0;
	            caDeltashift = 0;
	            cbDeltashift = 0;
	        }

	        String resLabel = _residueLabels[index];
	        String atomName = _atomNames[index];
	        double chemShift = _chemShiftVals[index];

		try {
	            Pair standardValue = _refTable.returnValues(resLabel,
		      atomName);

		    // Note: do the calculation in double and truncate to float
		    // to avoid getting values like 0.05000000000000071.
		    float deltashift = (float)(chemShift -
		      standardValue.chemshift);

		    // Special cases of combining HA2 with HA and HA3 with
		    // CB as per algorithm.
		    //TEMP -- need alg reference here
	            if (atomName.equals("HA") ||
		      (atomName.equals("HA2") && resLabel.equals("GLY"))) {
		        haDeltashift = deltashift;
	            } else if (atomName.equals("C")) {
		        cDeltashift = deltashift;
		    } else if (atomName.equals("CA")) {
		        caDeltashift = deltashift;
		    } else if (atomName.equals("CB") ||
		      (atomName.equals("HA3") && resLabel.equals("GLY"))) {
		        cbDeltashift = deltashift;
		    } else {
		        //TEMP -- should we ever get here????
		    }
	        } catch(S2DWarning ex) {
		    if (DEBUG >= 1) {
		        System.err.println(ex.getMessage());
		    }
	        } catch(S2DException ex) {
		    System.err.println(ex.getMessage());
		}
	    }

	    // Write last residue.
	    //TEMP -- currResSeqCode should equal prevResSeqCode here?
	    deltashiftWriter.write(prevResSeqCode + " " + haDeltashift +
	      " " + cDeltashift + " " + caDeltashift + " " +
	      cbDeltashift + "\n");
	    dsCount++;

	    deltashiftWriter.close();

	    //
	    // Write the session file
	    //
	    S2DSession.write(_sessionDir, S2DUtils.TYPE_DELTASHIFT,
	      _accessionNum, frameIndex);

	    //
	    // Write the session-specific html file.
	    //
	    S2DSpecificHtml.write(_dataDir, S2DUtils.TYPE_DELTASHIFT,
	      _accessionNum, frameIndex);

	    //
	    // Write the link in the summary html file.
	    //
	    _summary.writeDeltashift(frameIndex, dsCount);

	} catch (IOException ex) {
	    System.err.println("IOException writing deltashift data: " +
	      ex.getMessage());
	    throw new S2DError("Unable to write deltashift data for " +
	      frameIndex);
	}
    }

    //-------------------------------------------------------------------
    // Write the CSI info for this data.
    public void writeCSI(int frameIndex) throws S2DException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DChemShift.writeCSI()");
	}

	//
	// Calculate the CSI values and write them to the data file.
	//
        FileWriter csiWriter = null;
	LineTokens dsLine = null;
	try {
            csiWriter = new FileWriter(_dataDir + "/" +
	      _accessionNum + S2DNames.CSI_SUFFIX + frameIndex +
	      S2DNames.DAT_SUFFIX);
	    dsLine = new LineTokens(new StreamTokenizer(
	      new FileReader(_dataDir + "/" + _accessionNum +
	        S2DNames.DELTASHIFT_SUFFIX + frameIndex +
		S2DNames.DAT_SUFFIX)));
        } catch(IOException ex) {
	    System.err.println("IOException writing CSI values: " +
	      ex.getMessage());
	    throw new S2DError("Can't write CSI values");
	}

	int prevCsiSeq = -1; // -1 means invalid
	int currCsiSeq;
	int currDelSeq = -1; // -1 means invalid
	boolean hasCsiInfo = false;

	int haCsi = 0;
	int cCsi = 0;
	int caCsi = 0;
	int cbCsi = 0;
	int consCsi = 0;

	int csiCount = 0;

	try {
	    for (int index = 0; index < _resSeqCodes.length; index++) {
	        currCsiSeq = _resSeqCodes[index];

	        if (currCsiSeq != prevCsiSeq) {
		    if (prevCsiSeq != -1 && hasCsiInfo) {
	                // We're done with prevCsiSeq, so write out its info.
		        csiWriter.write(prevCsiSeq + " " + haCsi + " " +
			  cCsi + " " + caCsi + " " + cbCsi + " " +
			  consCsi + "\n");
		        csiCount++;
		    }

		    while (currDelSeq < currCsiSeq) {
		        dsLine.readAndTokenLine();
			currDelSeq = dsLine.seqNumber;
		    }

		    prevCsiSeq = currCsiSeq;
		    hasCsiInfo = false;

		    // Re-initialize the values.
	            haCsi = 0;
	            cCsi = 0;
	            caCsi = 0;
	            cbCsi = 0;
	            consCsi = dsLine.csi;

                }

		if (currCsiSeq == currDelSeq) {
		    hasCsiInfo = true;

	            String resLabel = _residueLabels[index];
	            String atomName = _atomNames[index];
		    double chemShift = _chemShiftVals[index];

		    try {
	                Pair standardValue = _refTable.returnValues(resLabel,
			  atomName);

			// Note: do the calculation in double and truncate to
			// float to avoid getting values like
			// 0.05000000000000071.
		        float deltashift = (float)(chemShift -
			  standardValue.chemshift);

			int csi;
			if (deltashift > standardValue.offset) {
			    csi = 1;
			} else if (deltashift < -1.0 * standardValue.offset) {
			    csi = -1;
			} else {
			    csi = 0;
			}

		        // Special cases of combining HA2 with HA and HA3 with
		        // CB as per algorithm.
		        //TEMP -- need alg reference here
	                if (atomName.equals("HA") ||
		          (atomName.equals("HA2") && resLabel.equals("GLY"))) {
		            haCsi = csi;
	                } else if (atomName.equals("C")) {
		            cCsi = csi;
		        } else if (atomName.equals("CA")) {
		            caCsi = csi;
		        } else if (atomName.equals("CB") ||
		          (atomName.equals("HA3") && resLabel.equals("GLY"))) {
		            cbCsi = csi;
		        } else {
		            //TEMP -- should we ever get here????
		        }
	            } catch(S2DWarning ex) {
		        if (DEBUG >= 1) {
		            System.err.println(ex.getMessage());
		        }
		    } catch (S2DException ex) {
		        System.err.println(ex.getMessage());
		    }
		}
            }

	    // Write last residue.
	    //TEMP -- currResSeqCode should equal prevResSeqCode here?
	    if (hasCsiInfo) {
	        csiWriter.write(prevCsiSeq + " " + haCsi + " " +
		  cCsi + " " + caCsi + " " + cbCsi + " " +
		  consCsi + "\n");
	        csiCount++;
	    }

	    csiWriter.close();

	    //
	    // Write the session file.
	    //
	    S2DSession.write(_sessionDir, S2DUtils.TYPE_CSI,
	      _accessionNum, frameIndex);

	    //
	    // Write the session-specific html file.
	    //
	    S2DSpecificHtml.write(_dataDir, S2DUtils.TYPE_CSI,
	      _accessionNum, frameIndex);

	    //
	    // Write the link in the summary html file.
	    //
	    _summary.writeCSI(frameIndex, csiCount);

	} catch (IOException ex) {
	    System.err.println("IOException writing CSI data: " +
	      ex.getMessage());
	    throw new S2DError("Unable to write CSI data for " +
	      frameIndex);
	}
    }

    //-------------------------------------------------------------------
    // Write the percent assignments for this data.
    public void writePctAssign(int frameIndex) throws S2DException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DChemShift.writePctAssign()");
	}

	//
	// Calculate the percent assignment values and write them to the
	// data file.
	//
        FileWriter pctWriter = null;
	AssgDataManager assgTable = null;
	try {
            pctWriter = new FileWriter(_dataDir + "/" +
	      _accessionNum + S2DNames.PERCENT_ASSIGN_SUFFIX + frameIndex +
	      S2DNames.DAT_SUFFIX);
	    assgTable = new AssgDataManager(_dataDir + "/" +
	      S2DNames.CHEMASSG_FILE);
        } catch(IOException ex) {
	    System.err.println(
	      "IOException writing percent assignment values: " +
	      ex.getMessage());
	    throw new S2DError("Can't write percent assignment values");
	}

	int paCount = 0;

        try {
	    int index = 0;
	    while (index < _resSeqCodes.length) {
	        int resSeqCode = _resSeqCodes[index];
	        String resLabel = _residueLabels[index];

		try {
		    AssgEntry assignments = assgTable.returnAssg(resLabel);

		    int starNumH = 0;
		    int starNumC = 0;
		    int starNumN = 0;

		    while (index < _resSeqCodes.length &&
		      resLabel.equals(_residueLabels[index]) &&
		      resSeqCode == _resSeqCodes[index]) {
	                String atomType = _atomTypes[index];
			if (atomType.equals("H")) {
			    starNumH++;
			} else if (atomType.equals("C")) {
			    starNumC++;
			} else if (atomType.equals("N")) {
			    starNumN++;
			}

		        index++;
		    }

		    pctWriter.write(resSeqCode + " " + resLabel + " " +
		      (100 * (float)starNumH / assignments.numH) + " " +
		      (100 * (float)starNumC / assignments.numC) + " " +
		      (100 * (float)starNumN / assignments.numN) + " " + "\n");
		    paCount++;
		} catch (S2DException ex) {
		    System.err.println(ex.getMessage());
		}
	    }

	    pctWriter.close();

	    //
	    // Write the session file.
	    //
	    S2DSession.write(_sessionDir, S2DUtils.TYPE_PCT_ASSIGN,
	      _accessionNum, frameIndex);

	    //
	    // Write the session-specific html file.
	    //
	    S2DSpecificHtml.write(_dataDir, S2DUtils.TYPE_PCT_ASSIGN,
	      _accessionNum, frameIndex);

	    //
	    // Write the link in the summary html file.
	    //
	    _summary.writePctAssign(frameIndex, paCount);

	} catch (IOException ex) {
	    System.err.println("IOException writing percent assignment data: " +
	      ex.getMessage());
	    throw new S2DError("Unable to write percent assignment data for " +
	      frameIndex);
	}
    }
}

// ========================================================================
