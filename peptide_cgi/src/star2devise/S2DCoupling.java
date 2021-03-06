// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 2001-2015
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class implements the output of coupling constants.  For each set of
// coupling constants, it creates a data file, a session file, an
// individual html file, and a link in the summary html file.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.16.26.2  2015/03/04 20:46:24  wenger
// To-do 211:  Hopefully final cleanup before merge.
//
// Revision 1.16.26.1  2015/02/20 22:40:53  wenger
// To-do 211:  Re-ordered more of the data; tested it manually in DEVise,
// but test scripts haven't been updated yet.
//
// Revision 1.16  2011/10/10 23:43:38  wenger
// Reduced edited movie time from .1 to .02, and set the resolution to
// 400x400 to speed up generation time (just took 2:44 in a test).
//
// Revision 1.15.8.1  2011/09/21 20:46:09  wenger
// The s2predicted session movie buttons are now updated for the correct
// PDB ID -- I should probably have configuration for the URL, though,
// and also only show the button if the movie is available.
//
// Revision 1.15  2010/12/07 17:41:15  wenger
// Did another version history purge.
//
// Revision 1.14  2010/11/01 00:51:12  wenger
// Merged sample_cond2_br_0 thru sample_cond2_br_1 to trunk.
//
// Revision 1.13.2.3  2010/10/19 00:23:19  wenger
// Split the actual sample info out from the sample conditions info,
// including modifying ambiguity code and Pistachio metadata accordingly.
//
// Revision 1.13.2.2  2010/10/16 01:32:25  wenger
// Getting sample conditions save frame names now works for 2.1 files.
//
// Revision 1.13.2.1  2010/10/15 15:29:02  wenger
// Merged sample_cond_br_0 thru sample_cond_br_1/sample_cond_br_end to
// sample_cond2_br (to get the latest code refactoring from the trunk
// into the sample conditions code).
//
// Revision 1.13  2010/10/13 20:44:02  wenger
// Finished restructuring Peptide-CGI code so that we get values from
// the STAR files in the relevant object constructors, instead of in the
// S2DMain class.
//
// Revision 1.12.6.2  2010/10/11 14:38:31  wenger
// Started on method to get sample conditions for data save frames; I'm
// just committing a preliminary version until I make a change on the trunk
// to move all of the code for actually getting the relevant frame values
// down into the data-specific classes like I've already done with the
// delta shifts.
//
// Revision 1.12.6.1  2010/10/08 21:17:41  wenger
// We now put save frame details into the drill-down data for the data
// selection view in 3D visualizations; also fixed a bug in getting save
// frame details for 3.0/3.1 files.
//
// Revision 1.12  2010/03/10 22:36:16  wenger
// Added NMR-STAR file version to summary html page and detailed
// visualization version info (to-do 072).  (Doing this before I
// add multiple NMR-STAR paths so we can see which NMR-STAR file
// was used.)
//
// Revision 1.11  2010/02/17 18:48:41  wenger
// Fixed bug 093 (incorrect entity assembly IDs in 3D data sets).
//
// Revision 1.10  2009/03/12 17:30:19  wenger
// Changed entity assembly names to things like "EA 1 (polypeptide(L))"
// as requested by Eldon; changed tests accordingly.
//
// ...

// ========================================================================

package star2devise;

import java.io.*;
import java.util.*;
import EDU.bmrb.starlibj.SaveFrameNode;

public class S2DCoupling {
    //===================================================================
    // VARIABLES

    private static final int DEBUG = 0;

    private String _name;
    private String _longName;
    private String _dataDir;
    private String _sessionDir;
    private S2DSummaryHtml _summary;
    private int _entityAssemblyID;
    private String _frameDetails;
    private String _sample;
    private String _sampleConditions;

    private String[] _couplingConstCodes;
    private String[] _atom1ResSeqs;
    private String[] _atom1ResLabels;
    private String[] _atom1Names;
    private String[] _atom2ResSeqs;
    private String[] _atom2ResLabels;
    private String[] _atom2Names;
    private String[] _couplingConstValues;
    private String[] _couplingConstErrors;

    private String _starVersion;

    //===================================================================
    // PUBLIC METHODS

    //-------------------------------------------------------------------
    // Constructor.
    public S2DCoupling(String name, String longName, S2DNmrStarIfc star,
                       SaveFrameNode frame, String dataDir, String sessionDir,
                       S2DSummaryHtml summary, String entityAssemblyID) throws S2DException
    {
        if (doDebugOutput(11)) {
            System.out.println("S2DCoupling.S2DCoupling(" + name +
                               ")");
        }

        _name = name;
        _longName = longName;
        _dataDir = dataDir;
        _sessionDir = sessionDir;
        _summary = summary;
        _frameDetails = star.getFrameDetails(frame);
        _sample = star.getFrameSample(frame);
        _sampleConditions = star.getFrameSampleConditions(frame);
        _starVersion = star.version();

        //
        // Get the values we need from the Star file.
        //

        // If a non-blank entityAssemblyID is specified, we need to filter
        // the frame values to only take the ones corresponding to that
        // entityAssemblyID.  To do that, we get the entityAssemblyID
        // values in each row of the loop.  (entityAssemblyID will be blank
        // when processing NMR-STAR 2.1 files -- they don't have data for
        // more than one entity assembly in a single save frame).
        String[] entityAssemblyIDs = null;
        if (!entityAssemblyID.equals("")) {
            entityAssemblyIDs = star.getFrameValues(frame,
                                                    star.COUPLING_ENTITY_ASSEMBLY_ID_1,
                                                    star.COUPLING_ENTITY_ASSEMBLY_ID_1);
        }

        _atom1ResSeqs = star.getAndFilterFrameValues(frame,
                        star.COUPLING_CONSTANT_VALUE, star.COUPLING_RES_SEQ_CODE_1,
                        entityAssemblyID, entityAssemblyIDs);

        _atom2ResSeqs = star.getAndFilterFrameValues(frame,
                        star.COUPLING_CONSTANT_VALUE, star.COUPLING_RES_SEQ_CODE_2,
                        entityAssemblyID, entityAssemblyIDs);

        _couplingConstValues = star.getAndFilterFrameValues(frame,
                               star.COUPLING_CONSTANT_VALUE, star.COUPLING_CONSTANT_VALUE,
                               entityAssemblyID, entityAssemblyIDs);

        _couplingConstCodes = star.getAndFilterOptionalFrameValues(
                                  frame, star.COUPLING_CONSTANT_VALUE, star.COUPLING_CONSTANT_CODE,
                                  entityAssemblyID, entityAssemblyIDs,
                                  _atom1ResSeqs.length, "0");

        _atom1ResLabels = star.getAndFilterOptionalFrameValues(frame,
                          star.COUPLING_CONSTANT_VALUE, star.COUPLING_RES_LABEL_1,
                          entityAssemblyID, entityAssemblyIDs,
                          _atom1ResSeqs.length, "0");

        _atom1Names = star.getAndFilterOptionalFrameValues(frame,
                      star.COUPLING_CONSTANT_VALUE, star.COUPLING_ATOM_NAME_1,
                      entityAssemblyID, entityAssemblyIDs,
                      _atom1ResSeqs.length, "0");

        _atom2ResLabels = star.getAndFilterOptionalFrameValues(frame,
                          star.COUPLING_CONSTANT_VALUE, star.COUPLING_RES_LABEL_2,
                          entityAssemblyID, entityAssemblyIDs,
                          _atom1ResSeqs.length, "0");

        _atom2Names = star.getAndFilterOptionalFrameValues(frame,
                      star.COUPLING_CONSTANT_VALUE, star.COUPLING_ATOM_NAME_2,
                      entityAssemblyID, entityAssemblyIDs,
                      _atom1ResSeqs.length, "0");

        _couplingConstErrors = star.getAndFilterOptionalFrameValues(
                                   frame, star.COUPLING_CONSTANT_VALUE,
                                   star.COUPLING_CONSTANT_VALUE_ERR, entityAssemblyID,
                                   entityAssemblyIDs, _atom1ResSeqs.length, "0");

        _entityAssemblyID = star.getEntityAssemblyID(frame,
                            entityAssemblyID);
    }

    //-------------------------------------------------------------------
    // Write the coupling constansts for this data.
    public void writeCoupling(int frameIndex) throws S2DException
    {
        if (doDebugOutput(11)) {
            System.out.println("S2DCoupling.writeCoupling()");
        }

        try {
            //
            // Write the coupling constant values to the data file.
            //
            FileWriter couplingWriter = S2DFileWriter.create(_dataDir +
                                        File.separator + _name + S2DNames.COUPLING_SUFFIX + frameIndex +
                                        S2DNames.DAT_SUFFIX);
            couplingWriter.write("# Data: coupling constant values for " +
                                 _name + "\n");
            couplingWriter.write("# Schema: bmrb-CouplingConstant\n");
            couplingWriter.write("# Attributes: Coupling_constant_value; " +
                                 "Coupling_constant_value_error; Residue_seq_code; " +
                                 "Atom_one_residue_label; Atom_one_name; " +
                                 "Atom_two_residue_seq_code; " +
                                 "Atom_two_residue_label; Atom_two_name; " +
                                 "Coupling_constant_code; Entity_assembly_ID\n");

            couplingWriter.write("# Peptide-CGI version: " +
                                 S2DMain.PEP_CGI_VERSION + "\n");
            couplingWriter.write("# Generation date: " +
                                 S2DMain.getTimestamp() + "\n");
            couplingWriter.write("#\n");

            for (int index = 0; index < _couplingConstValues.length; index++) {
                couplingWriter.write(_couplingConstValues[index] + " " +
                                     _couplingConstErrors[index] + " " +
                                     _atom1ResSeqs[index] + " " +
                                     _atom1ResLabels[index] + " " +
                                     _atom1Names[index] + " " +
                                     _atom2ResSeqs[index] + " " +
                                     _atom2ResLabels[index] + " " +
                                     _atom2Names[index] + " " +
                                     _couplingConstCodes[index] + " " +
                                     _entityAssemblyID + "\n");
            }

            couplingWriter.close();

            //
            // Write the session file.
            //
            String info = "Visualization of " + _longName;
            S2DSession.write(_sessionDir, S2DUtils.TYPE_COUPLING,
                             _name, frameIndex, info, null, true, _starVersion, "");

            //
            // Write the session-specific html file.
            //
            String title = "Coupling Constants (entity assembly " +
                           _entityAssemblyID + ")";
            S2DSpecificHtml specHtml = new S2DSpecificHtml(
                _summary.getHtmlDir(),
                S2DUtils.TYPE_COUPLING, _name, frameIndex,
                title, _frameDetails);
            specHtml.write();

            //
            // Write the link in the summary html file.
            //
            _summary.writeCoupling(frameIndex, _entityAssemblyID,
                                   _couplingConstValues.length);

        } catch(IOException ex) {
            System.err.println("IOException writing coupling constants: " +
                               ex.toString());
            throw new S2DError("Can't write coupling constants");
        }
    }

    //-------------------------------------------------------------------
    /**
     * Add coupling constant data sets to the data data set list.
     * @param The data set list.
     * @param The frame index.
     */
    public void addCouplingData(Vector dataSets, int frameIndex,
                                int polymerType)
    {
        // Note: attribute names must match the bmrb-CouplingConstant schema.
        String dataSource = _name + S2DNames.COUPLING_SUFFIX +
                            frameIndex;
        String dataName = "3JHNHA coupling const [" + _entityAssemblyID + "]";
        dataSets.addElement(new S2DDatasetInfo(dataName, _frameDetails,
                                               _sample, _sampleConditions, dataSource,
                                               "Coupling_constant_value", "bmrb-CouplingConstant",
                                               "CouplingConstant", _entityAssemblyID, polymerType));
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
