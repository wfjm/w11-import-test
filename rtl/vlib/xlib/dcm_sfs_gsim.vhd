-- $Id: dcm_sfs_gsim.vhd 1065 2018-11-04 11:32:06Z mueller $
--
-- Copyright 2010-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
--
-- This program is free software; you may redistribute and/or modify it under
-- the terms of the GNU General Public License as published by the Free
-- Software Foundation, either version 3, or (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful, but
-- WITHOUT ANY WARRANTY, without even the implied warranty of MERCHANTABILITY
-- or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
-- for complete details.
--
------------------------------------------------------------------------------
-- Module Name:    dcm_sfs - sim
-- Description:    DCM for simple frequency synthesis
--                 simple vhdl model, without Xilinx UNISIM primitives
--
-- Dependencies:   -
-- Test bench:     -
-- Target Devices: generic Spartan-3A,-3E
-- Tool versions:  xst 12.1-14.7; ghdl 0.29-0.34
--
-- Revision History: 
-- Date         Rev Version  Comment
-- 2018-11-03  1065   1.1    use sfs_gsim_core
-- 2011-11-17   426   1.0.1  rename dcm_sp_sfs -> dcm_sfs
-- 2010-11-12   338   1.0    Initial version 
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

use work.slvtypes.all;
use work.xlib.all;

entity dcm_sfs is                       -- DCM for simple frequency synthesis
  generic (
    CLKFX_DIVIDE   : positive := 1;     -- FX clock divide   (1-32)
    CLKFX_MULTIPLY : positive := 1;     -- FX clock multiply (2-32) (1->no DCM)
    CLKIN_PERIOD   : real := 20.0);     -- CLKIN period (def is 20.0 ns)
  port (
    CLKIN  : in slbit;                  -- clock input
    CLKFX  : out slbit;                 -- clock output (synthesized freq.) 
    LOCKED : out slbit                  -- dcm locked
  );
end dcm_sfs;


architecture sim of dcm_sfs is
begin

  -- generate clock
  SFS: sfs_gsim_core
    generic map (
      VCO_DIVIDE   => 1,
      VCO_MULTIPLY => CLKFX_MULTIPLY,
      OUT_DIVIDE   => CLKFX_DIVIDE)
    port map (
      CLKIN   => CLKIN,
      CLKFX   => CLKFX,
      LOCKED  => LOCKED
    );
  
end sim;
