/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: May 30, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/core/benchmark/chrono_timer.hpp>


namespace pni{
namespace core{

    DURATIONUNITMAPINIT(std::chrono::nanoseconds,"ns");
    DURATIONUNITMAPINIT(std::chrono::microseconds,"us");
    DURATIONUNITMAPINIT(std::chrono::milliseconds,"ms");
    DURATIONUNITMAPINIT(std::chrono::seconds,"s");
    DURATIONUNITMAPINIT(std::chrono::minutes,"min");
    DURATIONUNITMAPINIT(std::chrono::hours,"h");

//end of namespace
}
}
