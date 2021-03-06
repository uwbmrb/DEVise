/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1998-2000
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  Declaration of DeviseLink class (base class for all links).
 */

/*
  $Id$

  $Log$
  Revision 1.6.2.1  2000/10/18 20:32:10  wenger
  Merged changes from fixed_bug_616 through link_gui_improvements onto
  the branch.

  Revision 1.7  2000/10/16 16:11:47  wenger
  Link creation GUI now gives a choice of positive or negative record
  links; fixed bug 622 (record link type not saved in session files);
  fixed bug 623 (record link update problem); other link-related cleanups.

  Revision 1.6  2000/02/16 18:51:39  wenger
  Massive "const-ifying" of strings in ClassDir and its subclasses.

  Revision 1.5  1999/02/11 19:54:58  wenger
  Merged newpile_br through newpile_br_1 (new PileStack class controls
  pile and stacks, allows non-linked piles; various other improvements
  to pile-related code).

  Revision 1.4.4.1  1999/02/11 18:24:22  wenger
  PileStack objects are now fully working (allowing non-linked piles) except
  for a couple of minor bugs; new PileStack state is saved to session files;
  piles and stacks in old session files are dealt with reasonably well;
  incremented version number; added some debug code.

  Revision 1.4  1998/05/06 22:04:53  wenger
  Single-attribute set links are now working except where the slave of
  one is the master of another.

  Revision 1.3  1998/04/29 17:53:51  wenger
  Created new DerivedTable class in preparation for moving the tables
  from the TAttrLinks to the ViewDatas; found bug 337 (potential big
  problems) while working on this.

  Revision 1.2  1998/03/27 15:08:57  wenger
  Added dumping of logical session description, added GUI for dumping
  logical or physical description; cleaned up some of the command code
  a little.

  Revision 1.1  1998/03/08 00:01:09  wenger
  Fixed bugs 115 (I think -- can't test), 128, and 311 (multiple-link
  update problems) -- major changes to visual links.

 */

#ifndef _DeviseLink_h_
#define _DeviseLink_h_

#include "DeviseTypes.h"
#include "DList.h"
#include "ViewCallback.h"
#include "VisualArg.h"
#include "ObjectValid.h"

class ViewGraph;

DefinePtrDList(LinkViewList, ViewGraph *)
enum RecordLinkType { NotRecordLink, Positive, Negative };

class DeviseLink: public ViewCallback {
public:
  DeviseLink(const char *name, VisualFlag linkFlag);
  virtual ~DeviseLink();

  /* Return name of link */
  const char *GetName() { return _name; }

  /* Set/get visual flag */
  virtual void SetFlag(VisualFlag flag) { _linkAttrs = flag; }
  virtual VisualFlag GetFlag() { return _linkAttrs; }

  /* Record link type */
  virtual RecordLinkType GetLinkType() { return NotRecordLink; }
  virtual void SetLinkType(RecordLinkType) {}

  /* Set view as link master, or reset */
  virtual void SetMasterView(ViewGraph *view) {}
  virtual ViewGraph *GetMasterView() { return 0; }

  /* Insert/delete view from link's view list */
  virtual void InsertView(ViewGraph *view);
  virtual bool DeleteView(ViewGraph *view);

  /* Return TRUE if view is part of this link */
  virtual Boolean ViewInLink(ViewGraph *view);	

  virtual void ViewDestroyed(View *view);

  /* Iterator for view list */
  int InitIterator();
  Boolean More(int index);
  ViewGraph *Next(int index);
  void DoneIterator(int index);

  virtual void Print();

  // Find out whether the given name is the name of a pile link.
  static Boolean IsPileLinkName(const char *name);

  void RefreshAll();

protected:
  const char *_name;
  LinkViewList *_viewList;
  VisualFlag _linkAttrs; // Which attribute(s) is link on?

private:
  ObjectValid _objectValid;
};

#endif /* _DeviseLink_h_ */

/*============================================================================*/
