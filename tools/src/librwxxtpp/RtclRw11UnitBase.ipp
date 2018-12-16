// $Id: RtclRw11UnitBase.ipp 1082 2018-12-15 13:56:20Z mueller $
//
// Copyright 2013-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
//
// This program is free software; you may redistribute and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY, without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for complete details.
// 
// Revision History: 
// Date         Rev Version  Comment
// 2018-12-15  1082   1.3.5  use lambda instead of bind
// 2018-12-09  1080   1.3.4  use HasVirt(); Virt() returns ref
// 2018-12-07  1078   1.3.3  use std::shared_ptr instead of boost
// 2018-12-01  1076   1.3.2  use unique_ptr
// 2017-04-15   875   1.3.1  add attached,attachutl getters
// 2017-04-08   870   1.3    add TUV,TB; add TUV* ObjUV(); inherit from TB
// 2017-04-02   863   1.2    add AttachDone()
// 2015-05-14   680   1.1    fGets: add enabled (moved from RtclRw11UnitDisk)
// 2013-03-06   495   1.0    Initial version
// 2013-02-16   488   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \file
  \brief   Implemenation (all inline) of RtclRw11UnitBase.
*/

#include "librtcltools/RtclStats.hpp"
#include "RtclRw11VirtFactory.hpp"

/*!
  \class Retro::RtclRw11UnitBase
  \brief FIXME_docs
*/

// all method definitions in namespace Retro
namespace Retro {

// Note on coding style:
//   all base class members must be qualified with "this->" to ensure proper
//   name lookup. Otherwise one gets errors like "no declarations were found
//   by argument-dependent lookup at the point of instantiation"
//
//   Reason is the according to C++ standart in a first pass all names which
//   are not template parameter dependent are resolved. If a name is not found
//   one gets above mentioned error. All other names are looked up in a second
//   pass.  Adding "this->" makes the name template parameter dependent.
//
//   Prefixing a "TC::" can also be used, e.g. for constants like TB::kOK.
  
//------------------------------------------+-----------------------------------
//! Constructor

template <class TU, class TUV, class TB>
inline RtclRw11UnitBase<TU,TUV,TB>::RtclRw11UnitBase(const std::string& type,
                                     const std::shared_ptr<TU>& spunit)
  : TB(type),
    fspObj(spunit)
{
  this->AddMeth("stats",    [this](RtclArgs& args){ return M_stats(args); });
  
  TU* pobj = fspObj.get();

  // the following construction is neccessary because the base class is a
  // template argument. Access to "this->fGets" is done via a local variable
  // 'gets' to a local variable. Otherwise processing of the template functions
  // Add<...> will cause obscure "expected primary-expression before ‘>’ "
  // error messages. Simply too much nested templating...
  
  RtclGetList& gets = this->fGets;
  gets.Add<size_t>          ("index",    [pobj](){ return pobj->Index(); });
  gets.Add<std::string>     ("name",     [pobj](){ return pobj->Name(); });
  gets.Add<bool>            ("enabled",  [pobj](){ return pobj->Enabled(); });
  gets.Add<bool>            ("attached",
                             [pobj](){ return pobj->IsAttached(); });
  gets.Add<const std::string&> ("attachurl",
                                [pobj](){ return pobj->AttachUrl(); });
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TU, class TUV, class TB>
inline RtclRw11UnitBase<TU,TUV,TB>::~RtclRw11UnitBase()
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TU, class TUV, class TB>
inline TU& RtclRw11UnitBase<TU,TUV,TB>::Obj()
{
  return *fspObj;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TU, class TUV, class TB>
inline TUV& RtclRw11UnitBase<TU,TUV,TB>::ObjUV()
{
  return *fspObj;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TU, class TUV, class TB>
inline Rw11Cpu& RtclRw11UnitBase<TU,TUV,TB>::Cpu() const
{
  return fspObj->Cpu();
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TU, class TUV, class TB>
inline const std::shared_ptr<TU>& RtclRw11UnitBase<TU,TUV,TB>::ObjSPtr()
{
  return fspObj;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TU, class TUV, class TB>
void RtclRw11UnitBase<TU,TUV,TB>::AttachDone()
{
  if (!Obj().HasVirt()) return;
  std::unique_ptr<RtclRw11Virt> pvirt(RtclRw11VirtFactory(&Obj().Virt()));
  if (!pvirt) return;
  this->fupVirt = move(pvirt);
  this->AddMeth("virt", [this](RtclArgs& args){ return this->M_virt(args); });
  return;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TU, class TUV, class TB>
int RtclRw11UnitBase<TU,TUV,TB>::M_stats(RtclArgs& args)
{
  RtclStats::Context cntx;
  if (!RtclStats::GetArgs(args, cntx)) return TB::kERR;
  if (!RtclStats::Collect(args, cntx, Obj().Stats())) return TB::kERR;
  if (Obj().HasVirt()) {
    if (!RtclStats::Collect(args, cntx, Obj().Virt().Stats())) return TB::kERR;
  }
  return TB::kOK;
}

} // end namespace Retro
