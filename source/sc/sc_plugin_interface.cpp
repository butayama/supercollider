//  interface for supercollider plugins
//  Copyright (C) 2009 Tim Blechmann
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; see the file COPYING.  If not, write to
//  the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
//  Boston, MA 02111-1307, USA.

#include "sc_plugin_interface.hpp"
#include "sc_ugen_factory.hpp"

#include "supercollider/Headers/server/SC_Samp.h"

extern "C"
{

bool define_unit(const char *inUnitClassName, size_t inAllocSize,
                 UnitCtorFunc inCtor, UnitDtorFunc inDtor, uint32 inFlags)
{
    try {
        nova::ugen_factory.register_ugen(inUnitClassName, inAllocSize, inCtor, inDtor, inFlags);
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool define_bufgen(const char * name, BufGenFunc func)
{
    try {
        nova::ugen_factory.register_bufgen(name, func);
        return true;
    }
    catch(...)
    {
        return false;
    }
}

} /* extern "C" */

namespace nova
{

sc_plugin_interface::sc_plugin_interface(void)
{
    sc_interface.fDefineUnit = &define_unit;
    sc_interface.fDefineBufGen = &define_bufgen;

    sc_interface.mSine = gSine;
    sc_interface.mCosecant = gInvSine;
    sc_interface.mSineSize = kSineSize;
    sc_interface.mSineWavetable = gSineWavetable;
}

} /* namespace nova */
