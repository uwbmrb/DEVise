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
  Revision 1.3  1995/11/24 21:29:58  jussi
  Added copyright notice and cleaned up code. Added Print method
  to help in debugging.

  Revision 1.2  1995/09/05 21:13:11  jussi
  Added/updated CVS header.
*/

/* transformation matrix */

#ifndef Transform_h
#define Transform_h

#include <stdio.h>
#include <math.h>

#include "DeviseTypes.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif

inline Coord ToRadian(Coord degree)
{
  return degree*2*PI/360.0;
}

inline Coord ToDegree(Coord radian)
{
  return radian*360.0/(2*PI);
};

/* 2D transformation matrix, ala Foley et al, 1990 */

class Transform2D {
public:
  /* identity matrix */
  Transform2D() {
    MakeIdentity();
  }

  /* Copy from another matrix */
  Transform2D(Transform2D *t) {
    t->GetCoords(_a00,_a01,_a02,_a10,_a11,_a12);
    _cartesian = t->_cartesian;
  }

  /* Copy from another mattrix */
  void Copy(Transform2D &t) {
    t.GetCoords(_a00,_a01,_a02,_a10,_a11,_a12);
    _cartesian = t._cartesian;
  }

  /* Clear the matrix into an identity matrix */
  void MakeIdentity() {
    _a00 = 1.0; _a01 = 0.0, _a02 = 0.0, _a10 = 0.0; _a11 = 1.0; _a12 = 0.0;
    _cartesian = true;
  }

  /* Translate by dx,dy */
  void Translate(Coord dx, Coord dy) { _a02 += dx; _a12 += dy; }

  /* Scale by sx, sy */
  void Scale(Coord sx, Coord sy) { _a00 *= sx; _a01 *= sx; _a02 *= sx;
				   _a10 *= sy; _a11 *= sy; _a12 *= sy; }

  /* Rotate by theta. counter-clockwise = positive theta. */
  void Rotate(Coord theta) {
    Coord cos_theta = cos(theta);
    Coord sin_theta = sin(theta);

    Coord temp = _a00;
    _a00 = cos_theta*temp-sin_theta*_a10;
    _a10 = sin_theta*temp+cos_theta*_a10;
    
    temp = _a01;
    _a01 = cos_theta*temp-sin_theta*_a11;
    _a11 = sin_theta*temp+cos_theta*_a11;
    
    temp = _a02;
    _a02 = cos_theta*temp-sin_theta*_a12;
    _a12 = sin_theta*temp+cos_theta*_a12;

    if (_a01 == 0.0 && _a10 == 0.0)
      _cartesian = true;
    else
      _cartesian = false;
  }

  /* Return the transformed X,Y coordinates */
  void Transform(Coord x, Coord y, Coord &newX, Coord &newY) {
    TransformX(x, y, newX);
    TransformY(y, y, newY);
  }

  /* Return the transformed X coordinate, optimized for speed */
  void TransformX(Coord x, Coord y, Coord &newX) {
    if (_cartesian)
      newX = _a00 * x + _a02;
    else
      newX = _a00 * x + _a01 * y + _a02;
  }

  /* Return the transformed Y coordinate, optimized for speed */
  void TransformY(Coord x, Coord y, Coord &newY) {
    if (_cartesian)
      newY = _a11 * y + _a12;
    else
      newY = _a10 * x + _a11 * y + _a12;
  }

  /* Find the original coord given transformed coordinate x,y.
     Inverse of matrix
     | a00 a01 a02|                        | a11  -a01 a01*a12-a02*a11 |
     | a10 a11 a12| = 1/(a00*a11-a01*a10)* | -a10 a00  a10*a02-a12*a00 |
     | 0    0   1 |                        | 0     0   a00*a11-a01*a10 |
  */
  void InverseTransform(Coord x, Coord y, Coord &oldX, Coord &oldY) {
    Coord temp = 1.0/(_a00*_a11-_a01*_a10);
    oldX = (x*_a11- y*_a01 + _a01*_a12-_a02*_a11)*temp;
    oldY = (-x*_a10+y*_a00+_a10*_a02-_a12*_a00)*temp;
  }

  /* Multiply other matrix after this one matrix. Store the
     result in this */
  void PostMultiply(Transform2D *other) {
    Coord o00,o01,o02,o10,o11,o12;
    other->GetCoords(o00,o01,o02,o10,o11,o12);
    
    _a02 = _a00*o02+ _a01*o12 + _a02;
    Coord temp = _a01;
    _a01 = _a00*o01+ _a01*o11;
    _a00 = _a00*o00+ temp*o10;
    
    _a12 = _a10*o02+ _a11*o12 + _a12;
    temp = _a11;
    _a11 = _a10*o01+ _a11*o11;
    _a10 = _a10*o00+ temp*o10;

    if (_a01 == 0.0 && _a10 == 0.0)
      _cartesian = true;
    else
      _cartesian = false;
  }

  /* Multiply other matrix before this. Store the result in this. */
  void PreMultiply(Transform2D *other) {
    Coord o00,o01,o02,o10,o11,o12;
    other->GetCoords(o00,o01,o02,o10,o11,o12);
    
    Coord temp = _a00;
    _a00 = o00*_a00+ o01*_a10;
    _a10 = o10*temp+ o11*_a10;
    
    temp = _a01;
    _a01 = o00*_a01+ o01*_a11;
    _a11 = o10*temp+ o11*_a11;
    
    temp = _a02;
    _a02 = o00*_a02+ o01*_a12 + o02;
    _a12 = o10*temp+ o11*_a12 + o12;

    if (_a01 == 0.0 && _a10 == 0.0)
      _cartesian = true;
    else
      _cartesian = false;
  }
  
  void GetCoords(Coord &a00, Coord &a01, Coord &a02, Coord &a10, Coord &a11,
		 Coord &a12) {
    a00 = _a00; a01 = _a01; a02 = _a02; a10 = _a10; a11 = _a11; a12 = _a12;
  }
  
  void Print() {
    printf("(%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f),%d", _a00, _a01, _a02,
	   _a10, _a11, _a12, (_cartesian ? 1 : 0));
  }

private:
  Coord _a00,_a01,_a02,_a10,_a11,_a12;  // transformation matrix
  Boolean _cartesian;                   // TRUE if cartesian transformation
                                        // (a01 == a10 == 0.0)
};
#endif
