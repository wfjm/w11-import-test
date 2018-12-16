// $Id: Rw11UnitRL11.cpp 1081 2018-12-14 22:29:42Z mueller $
//
// Copyright 2014-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
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
// 2018-12-09  1080   1.0.3  use HasVirt(); Virt() returns ref
// 2017-04-07   868   1.0.2  Dump(): add detail arg
// 2015-03-21   659   1.0.1  BUGFIX: SetType(): set fType;
// 2014-06-08   561   1.0    Initial version
// ---------------------------------------------------------------------------

/*!
  \file
  \brief   Implemenation of Rw11UnitRL11.
*/

#include "librtools/Rexception.hpp"
#include "librtools/RosFill.hpp"
#include "Rw11CntlRL11.hpp"

#include "Rw11UnitRL11.hpp"

using namespace std;

/*!
  \class Retro::Rw11UnitRL11
  \brief FIXME_docs
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! Constructor

Rw11UnitRL11::Rw11UnitRL11(Rw11CntlRL11* pcntl, size_t index)
  : Rw11UnitDiskBase<Rw11CntlRL11>(pcntl, index),
    fRlsta(0),
    fRlpos(0)
{
  // setup disk geometry: rl01 and rl02 supported, default rl02
  fType    = "rl02";
  fEnabled = true;
  fNCyl    = 512;
  fNHead   =   2;
  fNSect   =  40;
  fBlksize = 256;
  fNBlock  = fNCyl*fNHead*fNSect;
}

//------------------------------------------+-----------------------------------
//! Destructor

Rw11UnitRL11::~Rw11UnitRL11()
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

void Rw11UnitRL11::SetType(const std::string& type)
{
  if (HasVirt()) {
    throw Rexception("Rw11UnitRL11::SetType", 
                     string("Bad state: file attached"));
  }
  
  if (type == "rl01") {
    fNCyl    = 256;
  } else if (type == "rl02") {
    fNCyl    = 512;
  } else {
    throw Rexception("Rw11UnitRL11::SetType", 
                     string("Bad args: only types 'rl01' and 'rl02' supported"));
  }

  fType    = type;
  fNBlock  = fNCyl*fNHead*fNSect;
  return;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

void Rw11UnitRL11::Dump(std::ostream& os, int ind, const char* text,
                        int detail) const
{
  RosFill bl(ind);
  os << bl << (text?text:"--") << "Rw11UnitRL11 @ " << this << endl;
  os << bl << "  fRlsta:          " << RosPrintf(fRlsta,"o",6)   << endl;
  os << bl << "  fRlpos:          " << RosPrintf(fRlpos,"o",6)   << endl;

  Rw11UnitDiskBase<Rw11CntlRL11>::Dump(os, ind, " ^", detail);
  return;
}
  
} // end namespace Retro
