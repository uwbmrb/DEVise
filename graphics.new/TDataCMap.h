/*
  $Id$

  $Log$*/

/* implements default mapping for connectors.
   Default:
     color:	white.
     Pattern:	0.
*/

#ifndef TDataCMap_h
#define TDataCMap_h
#include "Color.h"
#include "Pattern.h"
#include "ConnectorShape.h"
#include "Connector.h"
#include "GDataBin.h"
#include "Exit.h"

class Stream;
class Connector;
class TDataCMap{
public:
	TDataCMap(){
		defaultColor = WhiteColor;
		defaultPattern = Pattern0;
		_shapeId = ContLineConnectorID;
		_numShapeAttrs = 0;
	};

	/* called by to map 2 gdata to one connection */
	virtual Boolean MapToConnection(void *grec1,void *grec2, Connector *c){
		GDataBinRec *s1 = (GDataBinRec *)grec1;
		GDataBinRec *s2 = (GDataBinRec *)grec2;
		c->x1 = s1->x;
		c->y1 = s1->y;
		c->x2 = s2->x;
		c->y2 = s2->y;
		c->pattern = defaultPattern;
		c->color = defaultColor;
		c->cShapeID = _shapeId;
		c->numShapeAttrs = _numShapeAttrs;
		for (int i=0; i < _numShapeAttrs; i++){
			c->shapeAttrs[i] = _shapeAttrs[i];
		}

		return Map(grec1,grec2,c);
	};

protected:

	/* this is specified by the user */
	virtual Boolean Map(void *, void *, Connector *){ return false;};

	void SetDefaultColor(Color c) { defaultColor = c; };
	void SetDefaultPattern(Pattern p){ defaultPattern = p; };
	void SetDefaultConnectorShape(ConnectorShapeID shapeId,
		int numAttrs=0,ShapeAttr *shapeAttr= NULL){
		if (numAttrs > MAX_CONNECTOR_SHAPE_ATTRS){
			fprintf(stderr,"ConnectorMapping::SetDefaultShape:too many attrs %d\n", numAttrs);
			Exit::DoExit(1);
		}
		_shapeId = shapeId;
		_numShapeAttrs = numAttrs;
		_shapeAttrs= shapeAttr;
	}
	Color GetDefaultColor(){ return defaultColor;};
	Pattern GetDefaultPattern() { return defaultPattern; };


private:
	Color defaultColor;
	Pattern defaultPattern;
	ConnectorShapeID _shapeId;
	int _numShapeAttrs;
	ShapeAttr *_shapeAttrs;
};

#endif
