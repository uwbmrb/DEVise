#include <assert.h>
#include <stdio.h>

#include "PhonyRAM.h"

RBMObjectInfo *findObjectInfo(RBMObject objectId);

PhonyRAM::PhonyRAM(RBMObject obj, const DteTupleAdt& rec,
		   vector<char*>& inPages)
: _page(rec), _inPages(inPages)
{
    _obj = obj;
    _scanOutstanding = false;
}

PhonyRAM::~PhonyRAM()
{
    /* don't have to do anything */
}

int PhonyRAM::openScan(BoundingBox *in, BoundingBoxList *notIn)
{
    _in = in->clone();
    _notIn = notIn->clone();

    _scanOutstanding = true;
    _curPage = 0;
    _curSlot = 0;

    return 0;
}

int PhonyRAM::nextRec(void *&record)
{
    Tuple *tuple;
    float8 value;

    assert(_scanOutstanding);

    /* iterate through the page to find the next qualified record */
    while( _curPage < _inPages.size() ) {
        _page.setPage( _inPages[_curPage] );
        while (_curSlot < _page.getNumSlots() )
        {
    	    tuple = _page.getTuple(_curSlot);
    	    _curSlot++;

 	    /* find the value for the bounding box attribute */

	    RBMObjectInfo *roi = findObjectInfo(_obj);
    	    value = DteFloat8Adt::cast(tuple[roi->boundingBoxAttrNumber]);

	    if (_in->contain(value) && (_notIn->contain(value) == false))
	    {
	        record = tuple;
	        return 0;
  	    }
        }
        _curPage++;
	_curSlot = 0;
    }

    return NO_MORE_RECORD;
}

void PhonyRAM::closeScan()
{
    if (_in)
    {
	delete _in;
	_in = NULL;
    }

    if (_notIn)
    {
	delete _notIn;
	_notIn = NULL;
    }

    _scanOutstanding = false;
}

void PhonyRAM::output(int verbose)
{
    /* don't have to do anything */
}
