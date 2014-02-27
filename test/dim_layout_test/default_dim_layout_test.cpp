/*
 * (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jan 8, 2014
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "default_dim_layout_test.hpp"

void default_layout_test::test_default_construction()
{
    default_dim_layout layout; 

    CPPUNIT_ASSERT(layout.stride().size() == 0);
    CPPUNIT_ASSERT(layout.offset().size() == 0);
    CPPUNIT_ASSERT(layout.counts().size() == 0);
}

//-----------------------------------------------------------------------------
void default_layout_test::test_move_construction()
{

}

//-----------------------------------------------------------------------------
void default_layout_test::test_copy_construction()
{

}
//-----------------------------------------------------------------------------
void default_layout_test::test_copy_assignment()
{

}

//-----------------------------------------------------------------------------
void default_layout_test::test_move_assignment()
{

}

//-----------------------------------------------------------------------------
void default_layout_test::test_counts_assignment()
{

}

//-----------------------------------------------------------------------------
void default_layout_test::test_offset_assignment()
{

}

//-----------------------------------------------------------------------------
void default_layout_test::test_stride_assignment()
{

}
