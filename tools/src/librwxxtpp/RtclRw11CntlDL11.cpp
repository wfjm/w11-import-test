// $Id: RtclRw11CntlDL11.cpp 1082 2018-12-15 13:56:20Z mueller $
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
// 2018-12-15  1082   1.1.1  use lambda instead of bind
// 2017-04-16   878   1.1    add class in ctor; derive from RtclRw11CntlTermBase
// 2013-05-04   516   1.0.1  add RxRlim support (receive interrupt rate limit)
// 2013-03-06   495   1.0    Initial version
// 2013-02-02   480   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \file
  \brief   Implemenation of RtclRw11CntlDL11.
*/

#include "librtcltools/RtclNameSet.hpp"

#include "RtclRw11CntlDL11.hpp"
#include "RtclRw11UnitDL11.hpp"

using namespace std;

/*!
  \class Retro::RtclRw11CntlDL11
  \brief FIXME_docs
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! Constructor

RtclRw11CntlDL11::RtclRw11CntlDL11()
  : RtclRw11CntlTermBase<Rw11CntlDL11>("Rw11CntlDL11","term")
{
  Rw11CntlDL11* pobj = &Obj();
  fGets.Add<uint16_t> ("rxrlim", [pobj](){ return pobj->RxRlim(); });
  fSets.Add<uint16_t> ("rxrlim", [pobj](uint16_t v){ pobj->SetRxRlim(v); });
}

//------------------------------------------+-----------------------------------
//! Destructor

RtclRw11CntlDL11::~RtclRw11CntlDL11()
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

int RtclRw11CntlDL11::FactoryCmdConfig(RtclArgs& args, RtclRw11Cpu& cpu)
{
  static RtclNameSet optset("-base|-lam");

  string cntlname(cpu.Obj().NextCntlName("tt"));
  string cntlcmd = cpu.CommandName() + cntlname;

  uint16_t base = Rw11CntlDL11::kIbaddr;
  int      lam  = Rw11CntlDL11::kLam;
  
  string opt;
  while (args.NextOpt(opt, optset)) {
    if        (opt == "-base") {
      if (!args.GetArg("base", base, 0177776, 0160000)) return kERR;
    } else if (opt == "-lam") {
      if (!args.GetArg("lam",  lam,  0, 15)) return kERR;
    }
  }
  if (!args.AllDone()) return kERR;

  // configure controller
  Obj().Config(cntlname, base, lam);

  // install in CPU
  cpu.Obj().AddCntl(dynamic_pointer_cast<Rw11Cntl>(ObjSPtr()));

  // finally create tcl command
  CreateObjectCmd(args.Interp(), cntlcmd.c_str()); 

  // and create unit commands
  for (size_t i=0; i<Obj().NUnit(); i++) {
    string unitcmd = cpu.CommandName() + Obj().UnitName(i);
    new RtclRw11UnitDL11(args.Interp(), unitcmd, Obj().UnitSPtr(i));
  }

  return kOK;
}

} // end namespace Retro
