// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2000
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// Subclass of Error for our errors.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.7.4.1  2000/11/16 17:13:13  wenger
// Made static variables into static final variables.
//
// Revision 1.7  2000/04/07 22:44:10  wenger
// Improved shading of atoms (it now works on white atoms); added comments
// based on meeting with Hongyu on 2000-04-06.
//
// Revision 1.6  2000/03/23 16:26:16  wenger
// Cleaned up headers and added requests for comments.
//
// Revision 1.5  1999/12/10 15:37:01  wenger
// Added standard headers to source files.
//
// ========================================================================


public class YError extends Error
{
    private static final String defaultMsg = "YError has been thrown!";

    public YError()
    {
        this(null, null);
    }

    public YError(String s)
    {
        this(s, null);
    }

    public YError(String s, String w)
    {
        super( ((s == null)?defaultMsg:s) + ((w == null)?"":(" in " + w)) );
    }
}

