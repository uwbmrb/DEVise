/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-1995
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  $Id$

  $Log$
  Revision 1.10  1996/01/13 23:10:13  jussi
  Added support for Z attribute and shape attribute 2.

  Revision 1.9  1996/01/09 22:08:33  jussi
  Added GetZ() function.

  Revision 1.8  1995/12/28 19:30:37  jussi
  Small fix to remove compiler warning.

  Revision 1.7  1995/12/22 18:06:25  jussi
  Symbol width and height are taken as an absolute value.

  Revision 1.6  1995/11/28 00:23:36  jussi
  Elevated a couple of #include statements from MapInterpShape.h
  to this file.

  Revision 1.5  1995/11/28 00:07:25  jussi
  Moved some common code from MapInterpShape.h to this file.
  BoundingBoxGData is by default computed based on the width
  and height of a symbol. Small symbols are drawn as single
  pixels, and for this purpose derived classes can use the
  DrawPixelArray method.

  Revision 1.4  1995/11/25  01:20:15  jussi
  This code now uses Transform matrix operations to convert user/world
  coordinates to screen pixel coordinates. This is to avoid any future
  inconsistencies in how the different code locations compute the
  conversion. xPerPixel and yPerPixel are now obsolete coefficients.

  Revision 1.3  1995/11/21 23:23:38  jussi
  Added copyright notice and cleaned up the code.

  Revision 1.2  1995/09/05 22:15:35  jussi
  Added CVS header.
*/

#ifndef Shape_h
#define Shape_h

#include <stdio.h>
#include "TDataMap.h"
#include "WindowRep.h"
#include "Temp.h"

#define GetAttr(ptr, attrName, attrType, offset) \
	*((attrType *)(ptr+offset->attrName))

inline Coord GetX(char *ptr, TDataMap *map, GDataAttrOffset *offset)
{
  if (offset->xOffset < 0)
    return map->GetDefaultX();
  return GetAttr(ptr, xOffset, Coord, offset);
}

inline Coord GetY(char *ptr, TDataMap *map, GDataAttrOffset *offset)
{
  if (offset->yOffset < 0)
    return map->GetDefaultY();
  return GetAttr(ptr, yOffset, Coord, offset);
}

inline Coord GetZ(char *ptr, TDataMap *map, GDataAttrOffset *offset)
{
  if (offset->zOffset < 0)
    return map->GetDefaultZ();
  return GetAttr(ptr, zOffset, Coord, offset);
}

inline Color GetColor(View *view, char *ptr, TDataMap *map,
		      GDataAttrOffset *offset)
{
  Boolean active;
  Color color = view->GetOverrideColor(active);
  if (active)
    return color;
  if (offset->colorOffset < 0)
    return map->GetDefaultColor();
  return GetAttr(ptr, colorOffset, Color , offset);
}

inline Pattern GetPattern(char *ptr, TDataMap *map, GDataAttrOffset *offset)
{
  if (offset->patternOffset < 0)
    return map->GetDefaultPattern();
  return GetAttr(ptr, patternOffset, Pattern, offset);
}

inline Coord GetShapeAttr0(char *ptr, TDataMap *map, GDataAttrOffset *offset)
{
  if (offset->shapeAttrOffset[0] < 0) {
    ShapeAttr *attrs = map->GetDefaultShapeAttrs();
    return attrs[0];
  }
  return GetAttr(ptr, shapeAttrOffset[0], Coord, offset);
}

inline Coord GetShapeAttr1(char *ptr, TDataMap *map, GDataAttrOffset *offset)
{
  if (offset->shapeAttrOffset[1] < 0){
    ShapeAttr *attrs = map->GetDefaultShapeAttrs();
    return attrs[1];
  }
  return GetAttr(ptr, shapeAttrOffset[1], Coord, offset);
}

inline Coord GetShapeAttr2(char *ptr, TDataMap *map, GDataAttrOffset *offset)
{
  if (offset->shapeAttrOffset[2] < 0){
    ShapeAttr *attrs = map->GetDefaultShapeAttrs();
    return attrs[2];
  }
  return GetAttr(ptr, shapeAttrOffset[2], Coord, offset);
}

class WindowRep;
class TDataMap;

class Shape {
 public:
  /* Return # of shape attributes needed for this shape */
  virtual int NumShapeAttrs() {
    return 0;
  }

  /* Find bounding box for GData. By default, use 0th and 1st shape
     attribute as the width and height, respectively.  */
  virtual void BoundingBoxGData(TDataMap *map, void **gdataArray, int numSyms,
				Coord &width, Coord &height) {
    width = 0.0;
    height = 0.0;

    GDataAttrOffset *offset = map->GetGDataOffset();
    for(int i = 0; i < numSyms; i++) {
      char *gdata = (char *)gdataArray[i];
      Coord temp = fabs(GetShapeAttr0(gdata, map, offset));
      if (temp > width) width = temp;
      temp = fabs(GetShapeAttr1(gdata, map,  offset));
      if (temp > height) height = temp;
    }
  }

  /* Draw GData symbols. */
  virtual void DrawGDataArray(WindowRep *win, void **gdataArray, int numSyms,
			      TDataMap *map, View *view, int pixelSize) {}

 protected:
  /* Draw each GData symbol as a single pixel. Used by derived classes
     as a common method in cases where symbols are smaller than one
     pixel. */
  virtual void DrawPixelArray(WindowRep *win, void **gdataArray, int numSyms,
			      TDataMap *map, View *view, int pixelSize) {
    GDataAttrOffset *offset = map->GetGDataOffset();
    int i = 0;
    while (i < numSyms) {
      char *gdata = (char *)gdataArray[i];
      int count = 1;
      _x[0] = GetX(gdata, map, offset);
      _y[0] = GetY(gdata, map, offset);
      Color lastColor = GetColor(view, gdata, map, offset);
      
      int colorIndex;
      for(colorIndex = i + 1; colorIndex < numSyms; colorIndex++) {
	char *colorGData = (char *)gdataArray[colorIndex];
	if (GetColor(view, colorGData, map, offset) != lastColor)
	  break;
	_x[count] = GetX(colorGData, map, offset);
	_y[count++] = GetY(colorGData, map, offset);
      }
      
      win->SetFgColor(lastColor);
      win->DrawPixelArray(_x, _y, count, pixelSize);
      
      lastColor = GetColor(view, (char *)gdataArray[colorIndex], map, offset);
      i = colorIndex;
    }
  }
};

#endif
