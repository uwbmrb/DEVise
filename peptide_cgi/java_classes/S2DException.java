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

// Exception for Star2Devise.

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.1  2000/08/03 19:11:52  wenger
// Added S2DException class; better tolerance for certain missing data.
//

// ========================================================================

public abstract class S2DException extends Exception
{
    private static final int DEBUG = 0;

    public S2DException(String msg)
    {
        super(msg);

	if (DEBUG >= 1) {
	    printStackTrace();
	}
    }
}

// ========================================================================

