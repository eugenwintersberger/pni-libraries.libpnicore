/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Oct 24, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include "../../src/Types.hpp"

#include<iostream>
#include<ctime>

using namespace pni::utils;

class ClockTimer
{
    private:
        clock_t _start;
        clock_t _stop;

    public:
        //======================static members=================================
        static const String name; 
        //=======================constructors==================================
        ClockTimer():_start(0),_stop(0) {}

        //========================public member functions======================
        void start() { _start = clock(); }

        void stop() { _stop = clock(); }

        Float64 duration() const
        {
            return ((double)(_stop-_start))/CLOCKS_PER_SEC;
        }


        String unit() const
        {
            return String("s");
        }
};

const String ClockTimer::name = String("ClockTimer");
