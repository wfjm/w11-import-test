// $Id: RtclSetList.ipp 1083 2018-12-15 19:19:16Z mueller $
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
// 2018-12-15  1083   1.1.2  Add(): use rval ref and move semantics
// 2018-12-14  1081   1.1.1  use std::function instead of boost
// 2018-12-01  1076   1.1    use unique_ptr
// 2013-02-12   487   1.0    Initial version
// ---------------------------------------------------------------------------

/*!
  \file
  \brief   Implemenation (inline) of class RtclSetList.
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! FIXME_docs

template <class TP>
inline void RtclSetList::Add(const std::string& name,
                             std::function<void(TP)>&& set)
{
  Add(name, set_uptr_t(new RtclSet<TP>(move(set))));
  return;
}

} // end namespace Retro
