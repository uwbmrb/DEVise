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

// This class is used to convert a "base" specific html files to an html file
// specific to a particular data set.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.1.2.9  2005/03/22 20:34:38  wenger
// Merged ambiguity_vis2_br_0 thru ambiguity_vis2_br_3 to V2_1b4_br.
//
// Revision 1.1.2.8.4.1  2005/03/10 19:27:36  wenger
// Merged ambiguity_vis_br_0 thru ambiguity_vis_br_end to
// ambiguity_vis2_br.
//
// Revision 1.1.2.8.2.1  2005/03/10 18:34:07  wenger
// I need to commit the ambiguity stuff I've done so far so I can make
// a new ambiguity branch that has the latest Pistachio changes.
//
// Revision 1.1.2.8  2005/01/31 23:02:55  wenger
// Merged pistachio_vis_br_0 thru pistachio_vis_br_1a to V2_1b4_br.
//
// Revision 1.1.2.7  2004/12/08 23:07:18  wenger
// Oops -- re-fixed deltashift session template; added titles to
// specific html pages; enlarges the JavaScreen.
//
// Revision 1.1.2.6.2.1  2005/01/12 20:46:42  wenger
// Pistachio processing is now integrated into the normal Peptide-CGI
// processing -- the Pistachio visualization is generated autmatically
// if the Pistachio data exists.  (Still needs some cleanup, though.)
// (We generate the Pistachio visualization by generating a temporary
// mmCIF file with coordinates -- that is then run through the normal
// coordinate processing to generate the DEVise file with Pistachio
// coordinates.)
//
// Revision 1.1.2.6  2004/06/23 17:39:26  wenger
// Preliminary version of chem shift reference visualization 3 in
// place; cleaned up 4317 chem shift ref test data; changed fonts
// in chem shift ref visualization 1.
//
// Revision 1.1.2.5  2004/01/26 18:55:37  wenger
// Incorporated "Eldon's" chemical shift reference session; added help
// pages for both chem shift ref visualizations (with no help info
// for now).
//
// Revision 1.1.2.4  2003/10/23 18:08:57  wenger
// Basic chem shift ref stuff is in place -- session and specific html
// files are generated, summary html file has link, etc.  The main thing
// left is the mechanics of calling Dan's chem shift ref software --
// right now I am just using a script that creates dummy chem shift
// ref data files.
//
// Revision 1.1.2.3  2003/05/14 21:45:52  wenger
// Changed "/"s in file names to File.separator (hope I got them all!).
//
// Revision 1.1.2.2  2003/05/14 20:10:48  wenger
// Split generated html and data files into separate directories (for
// better security); moved html and session templates out of main
// html and session directories.
//
// Revision 1.1.2.1  2003/04/22 21:58:16  wenger
// Added package name to peptide-cgi java code and put everything into
// a single jar file; version is now 6.0.
//
// Revision 1.7.18.3  2003/04/09 18:02:13  wenger
// First version of visualization-server capability now in place; still
// needs some fixes.
//
// Revision 1.7.18.2  2003/03/06 19:18:26  wenger
// Restored visible borders between views in the 3D visualizations, as
// per Eldon's request.
//
// Revision 1.7.18.1  2003/01/14 16:51:49  wenger
// Merged V2_1b3_br_0 thru V2_1b3_br_end to V2_1b4_br.
//
// Revision 1.7.16.2  2002/11/01 17:40:14  wenger
// Fixed bug 013 (s2d fails if no write permission on output files).
//
// Revision 1.7.16.1  2002/10/31 22:17:35  wenger
// Changed Exception output to use toString() instead of getMessage()
// because that (at least sometimes) produces more complete information.
//
// Revision 1.7  2001/10/10 22:37:33  wenger
// First version of atomic coordinate extraction and visualization (atoms,
// not bonds, only tested on 4096 -- coordinates must be in same NMR-STAR
// file as other data); fixed various minor problems with peptide-cgi code.
//
// Revision 1.6  2001/07/25 17:46:49  wenger
// Added -usage and -version args to S2DMain, changed version to 2.12;
// slightly improved s2d error messages; install script now uses find
// to change the mode of html/data files to avoid argument overflow;
// distribution now generates tar file name with version number.
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

public class S2DSpecificHtml {
    //===================================================================
    // VARIABLES

    private static final int DEBUG = 0;

    //===================================================================
    // PUBLIC METHODS
    static void write(String htmlDir, int dataType, String name,
      int frameIndex, String title) throws S2DException
    {
        if (DEBUG >= 1) {
	    System.out.println("S2DSpecificHtml.write(" + htmlDir + ", " +
	      dataType + ", " + name + ", " + frameIndex + ")");
	}

	String baseName = "html_templates" + File.separator +
	  "specific_html.base";
	String dataSuffix;
	String searchString1 = "4264d1";
	String searchString2 = "4264";
	String searchString3 = "help_d.html";
	String searchString4 = "Dummy title";

	//TEMP -- should this be made into a method in S2DUtils?
	switch (dataType) {
	case S2DUtils.TYPE_DELTASHIFT:
	    dataSuffix = S2DNames.DELTASHIFT_SUFFIX;
	    break;

	case S2DUtils.TYPE_CSI:
	    dataSuffix = S2DNames.CSI_SUFFIX;
	    break;

	case S2DUtils.TYPE_PCT_ASSIGN:
	    dataSuffix = S2DNames.PERCENT_ASSIGN_SUFFIX;
	    break;

	case S2DUtils.TYPE_ALL_CHEM_SHIFTS:
	    dataSuffix = S2DNames.ALL_CHEM_SHIFT_SUFFIX;
	    break;

	case S2DUtils.TYPE_HVSN_CHEM_SHIFTS:
	    dataSuffix = S2DNames.HVSN_CHEM_SHIFT_SUFFIX;
	    break;

        case S2DUtils.TYPE_COUPLING:
	    dataSuffix = S2DNames.COUPLING_SUFFIX;
	    break;

/*TEMP
        case S2DUtils.TYPE_HXRATES:
	    dataSuffix = S2DNames.HX_RATE_SUFFIX;
	    break;

        case S2DUtils.TYPE_ORDER:
	    dataSuffix = S2DNames.
	    break;
TEMP*/

        case S2DUtils.TYPE_T1_RELAX:
	    dataSuffix = S2DNames.T1_SUFFIX;
	    break;

        case S2DUtils.TYPE_T2_RELAX:
	    dataSuffix = S2DNames.T2_SUFFIX;
	    break;

        case S2DUtils.TYPE_HETNOE:
	    dataSuffix = S2DNames.HETERONUCLEAR_NOE_SUFFIX;
	    break;

	case S2DUtils.TYPE_ATOMIC_COORDS:
	    dataSuffix = S2DNames.ATOMIC_COORD_SUFFIX;
	    break;

	case S2DUtils.TYPE_CHEM_SHIFT_REF1:
	    dataSuffix = S2DNames.CSR1_SUFFIX;
	    break;

	case S2DUtils.TYPE_CHEM_SHIFT_REF2:
	    dataSuffix = S2DNames.CSR2_SUFFIX;
	    break;

	case S2DUtils.TYPE_CHEM_SHIFT_REF3:
	    dataSuffix = S2DNames.CSR3_SUFFIX;
	    break;

	case S2DUtils.TYPE_PISTACHIO:
	    dataSuffix = S2DNames.PISTACHIO_SUFFIX;
	    break;

	case S2DUtils.TYPE_AMBIGUITY:
	    dataSuffix = S2DNames.AMBIGUITY_SUFFIX;
	    break;

	default:
	    throw new S2DError("Illegal data type: " + dataType);
	}

        String outFileName = htmlDir + File.separator + name + dataSuffix +
	  frameIndex + ".html";

	try {
            FileWriter writer = S2DFileWriter.create(outFileName);
	    BufferedReader reader = new BufferedReader(
	      new FileReader(baseName));

            String replaceString1 = name + dataSuffix + frameIndex;
            String replaceString2 = name;
            String replaceString3 = "help_" + dataSuffix + ".html";
            String replaceString4 = title;

            String line0;
	    while ((line0 = reader.readLine()) != null) {
		String line2 = S2DUtils.replace(line0, searchString1,
		  replaceString1);
		String line3 = S2DUtils.replace(line2, searchString2,
		  replaceString2);
		String line4 = S2DUtils.replace(line3, searchString3,
		  replaceString3);
		line4 = S2DUtils.replace(line4, searchString4,
		  replaceString4);
		if (dataType == S2DUtils.TYPE_ATOMIC_COORDS) {
		    // Change JS background color so gaps between views
		    // show up.
		    line4 = S2DUtils.replace(line4, "0+0+0", "64+96+0");
		}
	        writer.write(line4 + "\n");
	    }

	    reader.close();
	    writer.close();
        } catch(IOException ex) {
	    System.err.println("IOException: " +
	      ex.toString() + " writing specific html file");
	    throw new S2DError("Can't write specific html file: " +
	      outFileName);
	}
    }
}

// ========================================================================