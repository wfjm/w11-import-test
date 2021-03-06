// $Id: RtclProxyOwned.ipp 1186 2019-07-12 17:49:59Z mueller $
//  SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2011-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2018-12-07  1078   1.1.1  use std::shared_ptr instead of boost
// 2013-02-05   482   1.1    use shared_ptr to TO*; add ObjPtr();
// 2011-02-13   361   1.0    Initial version
// 2011-02-11   360   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \brief   Implemenation (all inline) of class RtclProxyOwned.
*/

/*!
  \class Retro::RtclProxyOwned
  \brief FIXME_docs
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! Default constructor

template <class TO>
inline RtclProxyOwned<TO>::RtclProxyOwned()
  : RtclProxyBase(),
    fspObj()
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TO>
inline RtclProxyOwned<TO>::RtclProxyOwned(const std::string& type)
  : RtclProxyBase(type),
    fspObj()
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TO>
inline RtclProxyOwned<TO>::RtclProxyOwned(const std::string& type,
                                          Tcl_Interp* interp, const char* name, 
                                          TO* pobj)
  : RtclProxyBase(type),
    fspObj(pobj)
{
  CreateObjectCmd(interp, name);
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TO>
inline RtclProxyOwned<TO>::~RtclProxyOwned()
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TO>
inline TO& RtclProxyOwned<TO>::Obj()
{
  return *fspObj;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TO>
inline const std::shared_ptr<TO>& RtclProxyOwned<TO>::ObjSPtr()
{
  return fspObj;
}

} // end namespace Retro
