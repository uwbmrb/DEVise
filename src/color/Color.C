/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1997-2004
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  Implementation of various high-level color functions.
 */

/*
  $Id$

  $Log$
  Revision 1.8  2002/06/17 19:41:59  wenger
  Merged V1_7b0_br_1 thru V1_7b0_br_2 to trunk.

  Revision 1.7.10.3  2004/08/23 22:53:39  wenger
  Fixed bug 890 (problems with drill-down dialog caused by
  some color palettes not having a pure white color).

  Revision 1.7.10.2  2003/12/19 18:12:49  wenger
  Merged redhat9_br_0 thru redhat9_br_1 to V1_7b0_br.

  Revision 1.7.10.1.6.1  2003/12/17 00:18:40  wenger
  Merged gcc3_br_1 thru gcc3_br_2 to redhat9_br (just fixed conflicts,
  didn't actually get it to work).

  Revision 1.7.10.1.4.1  2003/04/18 16:11:00  wenger
  Got things to compile and link with gcc 3.2.2 (with lots of warnings),
  but some code is commented out; also may need fixes to be backwards-
  compatible with older gcc versions.

  Revision 1.7.10.1  2002/05/16 17:16:11  wenger
  Changed default foreground color to black.

  Revision 1.7  2001/06/12 15:29:52  wenger
  Implemented a choice of modulus (default) or truncate color modes.

  Revision 1.6  1998/05/05 15:16:13  zhenhai
  Corrected make files for sgi uses.

  Revision 1.5  1998/02/19 23:26:02  wenger
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
// 970409 [weaver]: Original file.
// 970513 [weaver]: Updated to standard C++ class String.
// 970513 [weaver]: Added trace points.
// 970925 [weaver]: Updated to C++ standard libraries.
// 971016 [weaver]: Added CM_GetRGBList(), CM_GetColorID().
// 971017 [weaver]: Added lensBackColor.
// 971106 [weaver]: Added basic palette-handling methods.
// 971107 [weaver]: Improved palette initialization, alloc/free and swapping.
// 971203 [weaver]: Added PM_GetRGBList().
// 971204 [weaver]: Added AP_GetRawXColorID().
//
//******************************************************************************

#include "Color.h"
#include "XColor.h"
#include "ColorUtil.h"

//******************************************************************************
// Libraries
//******************************************************************************

#include <iostream>

#include "ColorManager.h"
#include "XColorManager.h"
#include "PaletteManager.h"
#include "ActivePalette.h"
#include "Coloring.h"

//#define INLINE_TRACE
#include "debug.h"

//******************************************************************************
// Types and Constants
//******************************************************************************

static const ColorID	gNumCoreColors	= 6;
static const ColorID	gNumDefColors	= 38;

// WARNING!!  Do not change these colors without making corresponding
// changes to SetupColors().
static const string		gCoreColors[gNumCoreColors] =
{
	"#000000000000 black",
	"#00000000ff00 blue",
	"#000064000000 DarkGreen",
	"#0000ff000000 green",
	"#ff0000000000 red",
	"#ffffffffffff white",
};

static const string		gDefColors[gNumDefColors] =
{
	"#000000000000 black",
	"#000000008b00 DarkBlue",
	"#00000000cd00 MediumBlue",
	"#00000000ff00 blue",
	"#000064000000 DarkGreen",
	"#00008b000000 green4",
	"#0000bf00ff00 DeepSkyBlue1",
	"#0000ff000000 green",
	"#0000ff00ff00 cyan",
	"#190019007000 MidnightBlue",
	"#1e009000ff00 DodgerBlue",
	"#1f001f001f00 gray12",
	"#22008b002200 ForestGreen",
	"#400040004000 gray25",
	"#610061006100 gray38",
	"#7f007f007f00 gray50",
	"#8b0000000000 DarkRed",
	"#8b0045001300 SaddleBrown",
	"#99003200cc00 DarkOrchid",
	"#a100a100a100 gray63",
	"#b20022002200 firebrick",
	"#b4005200cd00 MediumOrchid3",
	"#bf00bf00bf00 gray75",
	"#c000ff003e00 OliveDrab",
	"#e000e000e000 gray88",
	"#ee00ad000e00 Goldenrod2",
	"#ee00e800aa00 PaleGoldenrod",
	"#f000e6008c00 khaki",
	"#f500de00b300 wheat",
	"#fa00fa00d200 LightGoldenrodYellow",
	"#fd00f500e600 OldLace",
	"#ff0000000000 red",
	"#ff000000ff00 magenta",
	"#ff007f000000 DarkOrange1",
	"#ff00a5000000 orange",
	"#ff00d7000000 gold",
	"#ff00ff000000 yellow",
	"#ffffffffffff white",
};

//******************************************************************************
// Globals
//******************************************************************************

static ColorManager*	gColorManager	= NULL;		// Unique ColorManager
static PaletteManager*	gPaletteManager	= NULL;		// Unique PaletteManager

static PaletteID		gCorePaletteID;				// Core PaletteID
static Palette*			gCorePalette;				// Core Palette

static PaletteID		gDefaultPaletteID;			// Default PaletteID
static Palette*			gDefaultPalette	= NULL;		// Default Palette

static PaletteID		gCurrentPaletteID;			// Current PaletteID
static Palette*			gCurrentPalette	= NULL;		// Current Palette

static ActivePalette*	gActivePalette	= NULL;		// ActivePalette

static ColorMode		gMode = ColorModeModulus;

// These are more devise-specific than the others
static ColorID			globalColors[maxGlobalColor];
static Coloring			kgraphDefColoring;

//******************************************************************************
// Function Prototypes
//******************************************************************************

static void		SetupColors(void);
static void		InitKGraphDefaultColoring(void);

// Allocates the colors in the palette. All or nothing.
static bool		AllocPalette(PaletteID pid);

// Frees the colors in the palette.
static bool		FreePalette(PaletteID pid);

//******************************************************************************
// Initialization Functions
//******************************************************************************

bool	InitColor(Display * d, int depth, int nmap, Colormap *map)
{
	Trace("InitColor()");

	Palette*	palette;
	PaletteID	pid;

	// Initialize managers, active palette
	gColorManager		= new XColorManager(d, depth, nmap, map);
								// Color manager
	gPaletteManager		= new PaletteManager();			// Palette manager
	gActivePalette		= new ActivePalette();			// Active palette

	// Initialize core palette
	pid					= gPaletteManager->NewPalette();
	palette				= (*gPaletteManager)[pid];

	for (ColorID i=0; i<gNumCoreColors; i++)
	{
		PaletteColor	pc;

		pc.FromString(gCoreColors[i]);
		palette->NewColor(pc);
	}

	if (palette->EnsureBlackWhite()) {
		cerr << "Core palette MUST contain black and white\n";
		return false;
	}

	if (!AllocPalette(pid)) {
		cerr << "AllocPalette() failed at " << __FILE__ << ": " <<
		  __LINE__ << "\n";
		return false;
	}

	gCorePaletteID		= pid;
	gCorePalette		= palette;

	// Initialize default palette
	pid					= gPaletteManager->NewPalette();
	palette				= (*gPaletteManager)[pid];

	for (ColorID i=0; i<gNumDefColors; i++)
	{
		PaletteColor	pc;

		pc.FromString(gDefColors[i]);
		palette->NewColor(pc);
	}

	if (palette->EnsureBlackWhite()) {
		cerr << "Default palette MUST contain black and white\n";
		return false;
	}

	if (!AllocPalette(pid)) {
		cerr << "AllocPalette() failed at " << __FILE__ << ": " <<
		  __LINE__ << "\n";
		return false;
	}

	gDefaultPaletteID	= pid;
	gDefaultPalette		= palette;

	// Allocate and install active palette (using default palette)
	gCurrentPaletteID	= gDefaultPaletteID;
	gCurrentPalette		= gDefaultPalette;

	gActivePalette->SetColors(*gCurrentPalette, *gColorManager);

	// Initialize "hard-coded" color scheme
	SetupColors();
	InitKGraphDefaultColoring();

	return true;
}

void	TermColor(void)
{
	Trace("TermColor()");

	delete gActivePalette;
	delete gDefaultPalette;
	delete gPaletteManager;
	delete gColorManager;
}

// Allocates the default palette then assigns global colors.
void	SetupColors(void)
{
	Trace("SetupColors()");

	RGB			rgb;
	ColorID		cid;

	// WARNING!!  Indices passed to gCorePalette->GetColor() rely on
	// corresponding values in gCoreColors.

	// Alloc black
	rgb = gCorePalette->GetColor(0)->GetColor();
	gColorManager->GetColorID(rgb, cid);

	SetColorID(blackColor, cid);
	SetColorID(defForeColor, cid);
	SetColorID(gifBlackColor, cid);
	SetColorID(map3DframeColor, cid);
	SetColorID(xWinForeColor, cid);
	SetColorID(psDaliBlackColor, cid);
	SetColorID(lensBackColor, cid);

	// Alloc blue
	rgb = gCorePalette->GetColor(1)->GetColor();
	gColorManager->GetColorID(rgb, cid);

	SetColorID(kgraphCircleColor, cid);
	SetColorID(kgraphLabelColor, cid);

	// Alloc dark green
	rgb = gCorePalette->GetColor(2)->GetColor();
	gColorManager->GetColorID(rgb, cid);

	SetColorID(kgraphForeColor, cid);
	SetColorID(gdatasnapColor, cid);
	SetColorID(viewBorderColor, cid);
	SetColorID(viewGraphLegendColor, cid);

	// Alloc green
	rgb = gCorePalette->GetColor(3)->GetColor();
	gColorManager->GetColorID(rgb, cid);

	SetColorID(kgraphPointColor, cid);

	// Alloc red
	rgb = gCorePalette->GetColor(4)->GetColor();
	gColorManager->GetColorID(rgb, cid);

	SetColorID(kgraphTextColor, cid);

	// Alloc white
	rgb = gCorePalette->GetColor(5)->GetColor();
	gColorManager->GetColorID(rgb, cid);

	SetColorID(defBackColor, cid);
	SetColorID(whiteColor, cid);
	SetColorID(gifWhiteColor, cid);
	SetColorID(kgraphBackColor, cid);
	SetColorID(xWinBackColor, cid);
	SetColorID(psDaliWhiteColor, cid);
}

// This is a workaround for now. There should be a single default global
// Coloring object for KGraphs.
void	InitKGraphDefaultColoring(void)
{
	Trace("InitKGraphDefaultColoring()");

	kgraphDefColoring.SetForeground(GetColorID(kgraphForeColor));
	kgraphDefColoring.SetBackground(GetColorID(kgraphBackColor));

	kgraphDefColoring.AddDataColor(GetColorID(kgraphCircleColor));
	kgraphDefColoring.AddDataColor(GetColorID(kgraphPointColor));
	kgraphDefColoring.AddDataColor(GetColorID(kgraphTextColor));
	kgraphDefColoring.AddDataColor(GetColorID(kgraphLabelColor));
}

//******************************************************************************
// Utility Functions (Global Colors, Colorings)
//******************************************************************************

ColorID		GetColorID(GlobalColor color)
{
	if ((minGlobalColor <= color) && (color < maxGlobalColor))
		return globalColors[color];
	else
		return globalColors[defForeColor];
}

void		SetColorID(GlobalColor color, ColorID cid)
{
	if ((minGlobalColor <= color) && (color < maxGlobalColor))
		globalColors[color] = cid;
}

PColorID	GetPColorID(GlobalColor color)
{
	ColorID		cid = GetColorID(color);
	RGB			rgb;
	PColorID	pcid;

	if (gColorManager == NULL) {
		return nullPColorID;
	}

	gColorManager->GetRGB(cid, rgb);

	if (PM_GetPColorID(rgb, pcid)) {
		return pcid;
	} else {
		return nullPColorID;
    }
}

void		SetPColorID(GlobalColor color, PColorID pcid)
{
	ColorID		cid = GetColorID(color);
	RGB			rgb;

	gColorManager->GetRGB(cid, rgb);

	PColorID	fake = pcid;
}

const Coloring&		GetKGraphDefColoring(void)
{
	return kgraphDefColoring;
}

void				SetColorMode(ColorMode mode)
{
	if (mode != ColorModeModulus && mode != ColorModeTruncate) {
		cerr << "Illegal color mode: " << (int)mode << endl;
    	gMode = ColorModeModulus;
	} else {
    	gMode = mode;
	}
}

ColorMode			GetColorMode()
{
    return gMode;
}

//******************************************************************************
// Utility Functions (Color Manager)
//******************************************************************************

// Watch out for the nullXColorID case.
XColorID	CM_GetXColorID(ColorID cid)
{
	XColorID	xcid;
	
	if (gColorManager->GetXColorID(cid, xcid))
		return xcid;

	return nullXColorID;
}

bool		CM_GetRGB(ColorID cid, RGB& rgb)
{
	return gColorManager->GetRGB(cid, rgb);
}

bool		CM_GetColorID(const RGB& rgb, ColorID& cid)
{
	return gColorManager->GetColorID(rgb, cid);
}

RGBList		CM_GetRGBList()
{
	RGBList		rgbList;

	gColorManager->GetRGBList(rgbList);

	return rgbList;
}

//******************************************************************************
// Utility Functions (Palette Manager)
//******************************************************************************

bool		PM_GetRGB(PColorID pcid, RGB& rgb)
{
	Trace("PM_GetRGB()");

	const PaletteColor*		pc = (*gCurrentPalette)[pcid];

	if (pc == NULL)
		return false;					// Couldn't find id in palette

	rgb = pc->GetColor();

	return true;
}

RGBList		PM_GetRGBList(void)
{
	RGBList		rgbList;

	for (int i=0; i<gCurrentPalette->GetSize(); i++)
		rgbList.push_back(gCurrentPalette->GetColor(i)->GetColor());

	return rgbList;
}

bool		PM_GetPColorID(const RGB& rgb, PColorID& pcid)
{
	Trace("PM_GetPColorID()");
	return gCurrentPalette->GetPColorID(rgb, pcid);
}

ColorID		PM_GetColorID(PColorID pcid)
{
	Trace("PM_GetColorID()");

	const PaletteColor*		pc = (*gCurrentPalette)[pcid];

	if (pc == NULL)
		return nullColorID;				// Couldn't find id in palette

	const RGB&	rgb = pc->GetColor();
	ColorID		cid;
	
	if (!gColorManager->GetColorID(rgb, cid))
		return nullColorID;				// Couldn't find RGB in CM

	return cid;
}

Palette*	PM_GetPalette(PaletteID pid)
{
	Trace("PM_GetPalette()");

	if (pid == gCorePaletteID)
		return NULL;

	return gPaletteManager->GetPalette(pid);
}

PaletteID	PM_GetCurrentPalette(void)
{
	Trace("PM_GetCurrentPalette()");

	return gCurrentPaletteID;
}

bool		PM_SetCurrentPalette(PaletteID pid)
{
	Trace("PM_SetCurrentPalette()");

	if (pid == gCorePaletteID)
		return false;

	if (pid == gCurrentPaletteID)
		return true;

	Palette*	palette = gPaletteManager->GetPalette(pid);

	if (palette == NULL)
		return false;

	if (!FreePalette(gCurrentPaletteID))
		return false;

	if (!AllocPalette(pid))
	{
		AllocPalette(gCurrentPaletteID);
		return false;
	}

	gCurrentPaletteID	= pid;
	gCurrentPalette		= palette;

	gActivePalette->SetColors(*gCurrentPalette, *gColorManager);

	return true;
}

PaletteID	PM_NewPalette(const string& s)
{
	Trace("PM_NewPalette()");

	PaletteID	pid = gPaletteManager->NewPalette();
	Palette*	palette = gPaletteManager->GetPalette(pid);

	if (pid == nullPaletteID)
		return nullPaletteID;

	if (!palette->FromString(s))
	{
		gPaletteManager->DeletePalette(pid);
		return nullPaletteID;
	}
	palette->EnsureBlackWhite();

	return pid;
}

bool		PM_DeletePalette(PaletteID pid)
{
	Trace("PM_DeletePalette()");

	if ((pid == gCorePaletteID) || (pid == gDefaultPaletteID) ||
		(pid == gCurrentPaletteID))
		return false;

	Palette*	palette = gPaletteManager->GetPalette(pid);

	if (palette == NULL)
		return false;

	return gPaletteManager->DeletePalette(pid);
}

bool		AllocPalette(PaletteID pid)
{
	Trace("PM_AllocPalette()");

	Palette*	palette = gPaletteManager->GetPalette(pid);

	if (palette == NULL) {
		cerr << "Can't get palette\n";
		return false;
	}

	for (int i=0; i<palette->GetSize(); i++)
	{
		RGB		rgb = palette->GetColor(i)->GetColor();

		if (!gColorManager->AllocColor(rgb))
		{
			// Note: I don't quite understand the connection between the
			// color allocation and the palette here; but if you don't
			// successfully allocate a color for a given palette entry,
			// you seem to end up with the first core color.  Anyhow,
			// if some color allocations fail we want to go ahead and
			// put _something_ on the screen, as opposed to just exiting.
			// RKW Jan. 25, 1998.
			cerr << "Cannot allocate color " << rgb.ToString() <<
			  " -- mapping to " << gCoreColors[0] << "\n";
		}
	}

	return true;
}

bool		FreePalette(PaletteID pid)
{
	Trace("PM_FreePalette()");

	Palette*	palette = gPaletteManager->GetPalette(pid);
	bool		result = true;

	if (palette == NULL)
		return false;

	for (int i=0; i<palette->GetSize(); i++)
	{
		RGB		rgb = palette->GetColor(i)->GetColor();
		
		if (!gColorManager->FreeColor(rgb))
			result = false;
	}

	return result;
}

//******************************************************************************
// Utility Functions (Active Palette)
//******************************************************************************

XColorID	AP_GetXColorID(PColorID pcid)
{
	Trace("AP_GetXColorID()");

    int index = PColorID2Index(pcid, gActivePalette->GetSize());
	
	return (*gActivePalette)[index];
}

XColorID	AP_GetRawXColorID(PColorID pcid)
{
	Trace("AP_GetRawXColorID()");

	return (*gActivePalette)[pcid];
}

//******************************************************************************
