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

// Constant strings for names used in NMR-STAR files, etc.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.13  2002/01/10 22:14:07  wenger
// Added structure type selection to atomic coordinate sessions.
//
// Revision 1.12  2001/10/10 22:37:33  wenger
// First version of atomic coordinate extraction and visualization (atoms,
// not bonds, only tested on 4096 -- coordinates must be in same NMR-STAR
// file as other data); fixed various minor problems with peptide-cgi code.
//
// Revision 1.11  2001/07/25 19:56:23  wenger
// Started adding configuration setup stuff; s2d gets URLs from properties
// file.
//
// Revision 1.10  2001/05/14 18:08:26  wenger
// Parameterized all star file tag names, etc.
//
// Revision 1.9  2001/05/08 18:24:18  wenger
// Fixed problem getting residue count if a star file contains info for
// more than one protein; added residue counts to 'all shifts' and 'H
// vs. N' visualizations.
//
// Revision 1.8  2001/04/17 17:09:10  wenger
// Added display of H vs. N chem shifts.
//
// Revision 1.7  2001/04/16 19:49:11  wenger
// Added display of all chem shifts by amino acid.
//
// Revision 1.6  2001/01/19 15:39:06  wenger
// Added T1 and T2 relaxation; removed some unnecessary variables from
// coupling constants; added schema files to installation, unified T1
// and T2 relaxation schema.
//
// Revision 1.5  2001/01/17 19:55:46  wenger
// Restructured the peptide-cgi code to make it much more maintainable.
//
// Revision 1.4  2000/10/11 23:04:25  wenger
// Added coupling constants (for arbitrary entries, not just 4096) to the
// peptide-cgi code.
//
// Revision 1.3  2000/10/06 16:52:48  wenger
// Peptide-cgi code now handles multiple chemical shift save frames.  This
// required a fairly major reorganization of the code (all html files are
// now generated by the Java code, not the cgi script).  Changed the chem-
// shift-related base session files to 'new style'.
//
// Revision 1.2  2000/09/22 21:06:39  wenger
// Star2Devise checks chemical shift save frames individually to make sure
// they refer to a protein; for now it only saves chemical shift info for
// the first protein-related chemical shift save frame in the NMR-STAR file.
//
// Revision 1.1  2000/08/29 14:55:52  wenger
// Star2Devise can now extract relaxation parameters, H exchange rates, etc.
// from all appropriate NMR-STAR files, not just bmr4096.str (the sessions
// are not yet fully set up to handle this); fixed an error in the CSI
// calculations; improved test_summarize script.
//

// ========================================================================

public class S2DNames
{
    //
    // NMR-STAR tags and values.
    //
    public static final String ASSIGNED_CHEM_SHIFTS =
      "assigned_chemical_shifts";
    public static final String ATOM_1_ATOM_NAME = "_Atom_one_atom_name";
    public static final String ATOM_1_NAME = "_Atom_one_name";
    public static final String ATOM_1_RES_LABEL = "_Atom_one_residue_label";
    public static final String ATOM_1_RES_SEQ_CODE =
      "_Atom_one_residue_seq_code";
    public static final String ATOM_2_ATOM_NAME = "_Atom_two_atom_name";
    public static final String ATOM_2_NAME = "_Atom_two_name";
    public static final String ATOM_2_RES_LABEL = "_Atom_two_residue_label";
    public static final String ATOM_2_RES_SEQ_CODE =
      "_Atom_two_residue_seq_code";
    public static final String ATOM_COORD_SAVE_FRAME =
      "representative_structure";//TEMP?
    public static final String ATOM_COORD_X = "_Atom_coord_x";
    public static final String ATOM_COORD_Y = "_Atom_coord_y";
    public static final String ATOM_COORD_Z = "_Atom_coord_z";
    public static final String ATOM_NAME = "_Atom_name";
    public static final String ATOM_TYPE = "_Atom_type";
    public static final String CHEM_SHIFT_VALUE = "_Chem_shift_value";
    public static final String CONF_SUB_TOTAL =
      "_Conformer_submitted_total_number";
    public static final String COUPLING_CONSTANT_CODE =
      "_Coupling_constant_code";
    public static final String COUPLING_CONSTANT_VALUE =
      "_Coupling_constant_value";
    public static final String COUPLING_CONSTANT_VALUE_ERR =
      "_Coupling_constant_value_error";
    public static final String COUPLING_CONSTANTS = "coupling_constants";
    public static final String DB_ACC_CODE = "_Database_accession_code";
    public static final String DB_NAME = "_Database_name";
    public static final String DETAILS = "_Details";
    public static final String ENTRY_TITLE = "_Entry_title";
    public static final String H_EXCHANGE_PROT_FACT =
      "H_exchange_protection_factors";
    public static final String H_EXCHANGE_PROT_FACT_VALUE =
      "_H_exchange_protection_factor_value";
    public static final String H_EXCHANGE_RATE_VALUE =
      "_H_exchange_rate_value";
    public static final String H_EXCHANGE_RATE = "H_exchange_rate";
    public static final String H_EXCHANGE_RATES = "H_exchange_rates";
    public static final String HEME = "HEME";
    public static final String HETERONUCLEAR_NOE = "heteronuclear_NOE";
    public static final String HET_NOE_VALUE = "_Heteronuclear_NOE_value";
    public static final String HET_NOE_VALUE_ERR =
      "_Heteronuclear_NOE_value_error";
    public static final String MOL_POLYMER_CLASS = "_Mol_polymer_class";
    public static final String MOL_SYSTEM = "molecular_system";
    public static final String MOL_SYSTEM_NAME = "_Mol_system_name";
    public static final String MOL_SYS_COMP_NAME =
      "_Mol_system_component_name";
    public static final String RESIDUE_COUNT = "_Residue_count";
    public static final String RESIDUE_LABEL = "_Residue_label";
    public static final String RESIDUE_SEQ_CODE = "_Residue_seq_code";
    public static final String S2_PARAMS = "S2_parameters";
    public static final String SAVE_CONF_STAT =
      "save_conformer_statistical_characteristics";
    public static final String SAVE_DIST_CONSTRAINTS =
      "save_distance_constraints";
    public static final String SAVE_ENTRY_INFO = "save_entry_information";
    public static final String SAVE_FRAME_PREFIX = "save_";
    public static final String SAVE_GMG4 = "save_GMG4";
    public static final String SAVEFRAME_CATEGORY = "_Saveframe_category";
    public static final String SAVEFRAME_CAT_TYPE = "_Saveframe_category_type";
    public static final String SAVEFRAME_PREFIX = "_save";
    public static final String SPEC_FREQ_1H = "_Spectrometer_frequency_1H";
    public static final String T1_RELAX = "T1_relaxation";
    public static final String T1_VALUE = "_T1_value";
    public static final String T1_VALUE_ERR = "_T1_value_error";
    public static final String T2_RELAX = "T2_relaxation";
    public static final String T2_VALUE = "_T2_value";
    public static final String T2_VALUE_ERR = "_T2_value_error";

    //
    // Atom names.
    //
    public static final String ATOM_C = "C";
    public static final String ATOM_CA = "CA";
    public static final String ATOM_CB = "CB";
    public static final String ATOM_H = "H";
    public static final String ATOM_HA = "HA";
    public static final String ATOM_HA2 = "HA2";
    public static final String ATOM_HA3 = "HA3";
    public static final String ATOM_N = "N";
    public static final String ATOM_O = "O";

    //
    // Residue labels (amino acids).
    //
    public static final String ACID_GLY = "GLY";

    //
    // Misc. values.
    //
    public static final String PROTEIN = "protein";

    //
    // URL for getting NMR-STAR files from BMRB.  Note: this will be
    // set according to the s2d.props file value.
    //
    public static String BMRB_STAR_URL = null;

    //
    // URL for 3D example.  Note: this will be set according to the
    // s2d.props file value.
    //
    public static String BMRB_3D_URL = null;

    //
    // NMR-Star file name components.
    //
    public static final String NMR_STAR_PREFIX = "bmr";
    public static final String NMR_STAR_SUFFIX = ".str";

    //
    // Data type suffixes.
    //
    public static final String ATOMIC_COORD_SUFFIX = "ac";
    public static final String ALL_CHEM_SHIFT_SUFFIX = "as";
    public static final String CSI_SUFFIX = "c";
    public static final String DELTASHIFT_SUFFIX = "d";
    public static final String COUPLING_SUFFIX = "g";
    public static final String HETERONUCLEAR_NOE_SUFFIX = "n";
    public static final String HVSN_CHEM_SHIFT_SUFFIX = "hn";
    public static final String HX_PROT_FACTOR_SUFFIX = "f";
    public static final String HX_RATE_SUFFIX = "r";
    public static final String PERCENT_ASSIGN_SUFFIX = "p";
    public static final String RES_COUNT_SUFFIX = "rc";
    public static final String S2_SUFFIX = "s";
    public static final String T1_SUFFIX = "t1";
    public static final String T2_SUFFIX = "t2";

    //
    // Data file suffixes.
    //
    public static final String DAT_SUFFIX = ".dat";

    //
    // Html file suffixes.
    //
    public static final String HTML_SUFFIX = ".html";
    public static final String SUMMARY_HTML_SUFFIX = "y.html";

    //
    // Helper files.
    //
    public static final String CHEMASSG_FILE = "assignments.txt";

}

// ========================================================================

