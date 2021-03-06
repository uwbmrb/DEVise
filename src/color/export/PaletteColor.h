/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1997-2003
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
// A PaletteColor is simply an RGB value and a name (string). Palettes contain
// this special class (instead of the RGB values alone) for future addition
// of palette statistics, special PaletteColor values, etc.
//
// DEVise currently eschews color naming.
 */

/*
  $Id$

  $Log$
  Revision 1.4  2005/12/06 20:11:29  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.3.22.1  2003/12/19 18:12:56  wenger
  Merged redhat9_br_0 thru redhat9_br_1 to V1_7b0_br.

  Revision 1.3.40.1  2003/12/17 00:18:46  wenger
  Merged gcc3_br_1 thru gcc3_br_2 to redhat9_br (just fixed conflicts,
  didn't actually get it to work).

  Revision 1.3.38.1  2003/04/18 16:11:08  wenger
  Got things to compile and link with gcc 3.2.2 (with lots of warnings),
  but some code is commented out; also may need fixes to be backwards-
  compatible with older gcc versions.

  Revision 1.3  1998/06/24 14:45:41  beyer
  fixed booboo in destructor

  Revision 1.2  1998/06/24 14:44:47  beyer
  added destructor

  Revision 1.1  1998/02/20 20:44:07  wenger
  Changed color and utils libraries to new export directory scheme for
  dealing with include files (email with complete explanation forthcoming).

  Revision 1.3  1998/02/19 23:26:07  wenger
  Improved color library and got client/server test code to work
  (except for setting colors by RGB): reduced compile interdependencies,
  especially in color library; color and utils libraries install headers
  as per code reorg plans; added standard DEVise headers to all color
  manager files; moved color initialization into Display constructors;
  fixed some compile warnings throughout the code.

 */

//******************************************************************************
// Modification History:
//
// 970320 [weaver]: Original file.
// 970331 [weaver]: Added iostream operators and FromString().
// 970401 [weaver]: Changed FromString() to use new class String tokenization.
// 970513 [weaver]: Updated to standard C++ class String.
// 970925 [weaver]: Updated to C++ standard libraries.
//
//******************************************************************************

#ifndef __CLASS_PALETTECOLOR
#define __CLASS_PALETTECOLOR

//******************************************************************************
// Libraries
//******************************************************************************

using namespace std;

#include <iostream>
#include <string>

#include "RGB.h"

//******************************************************************************
// Types and Constants
//******************************************************************************

//******************************************************************************
// class PaletteColor
//******************************************************************************

class PaletteColor
{
	private:

		RGB		color;		// Logical color value
		string	name;		// Color name

	public:

		// Constructors and Destructors
		PaletteColor(const RGB& rgb = RGB(), const string& s = string());

                virtual ~PaletteColor() {}

		// Getters and Setters
		const RGB&		GetColor(void) const			{ return color;	}
		const string&	GetName(void) const				{ return name;	}

		void	SetColor(const RGB& rgb = RGB())		{ color = rgb;	}
		void	SetName(const string& s = string())		{ name = s;		}
		
		// Utility Functions
		void	GenerateName(void);

		// Conversions and Operators
		bool	operator==(const PaletteColor& t) const;
		bool	operator<(const PaletteColor& t) const;

		// Iostream Operators
		friend ostream&		operator<<(ostream& s, const PaletteColor& t);
		friend istream&		operator>>(istream& s, PaletteColor& t);

		// Output Functions
		virtual string	ToString(void) const;
		virtual bool	FromString(const string& s);
};

typedef PaletteColor*	PaletteColorPtr;

//******************************************************************************
// Constructors and Destructors (Inline)
//******************************************************************************

inline	PaletteColor::PaletteColor(const RGB& rgb, const string& s)
	: color(rgb), name(s)
{
}

//******************************************************************************
// Conversions and Operators (Inline)
//******************************************************************************

inline bool		PaletteColor::operator==(const PaletteColor& t) const
{
	return (color == t.color);
}

inline bool		PaletteColor::operator<(const PaletteColor& t) const
{
	return (color < t.color);
}

//******************************************************************************
#endif



