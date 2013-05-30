/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Oct 25, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include "benchmark_result.hpp"
#include <list>
#include <functional>
#include <cmath>

namespace pni{
namespace core{

    /*!
    \brief benchmark runner class

    This class runs benchmark functions.
    */
    class benchmark_runner
    {
        private:
            //! list with benchmark results
            std::list<benchmark_result> _results;
            //! function to run before a benchmark run
            std::function<void()> _pre_run;
            //! function to run after a benchmark run
            std::function<void()> _post_run;

            //! default pre- and post-run function
            void do_nothing() {}

        public:
            //======================public types================================
            //! iterator for benchmark results
            typedef std::list<benchmark_result>::iterator iterator;
            //! const iterator for benchnmark results
            typedef std::list<benchmark_result>::const_iterator const_iterator;
            //! function type for pre- and post-run functions
            typedef std::function<void()> function_t;

            //====================constructors and destructor===================
            //! default constructor
            benchmark_runner():_results(0)
            {
                _pre_run =
                    function_t(std::bind(&benchmark_runner::do_nothing,*this));
                _post_run = 
                    function_t(std::bind(&benchmark_runner::do_nothing,*this));
            }

            //-----------------------------------------------------------------
            //! destructor
            virtual ~benchmark_runner(){}

            //-----------------------------------------------------------------
            //! perform all runs
            template<typename TIMERT> void run(size_t n,function_t &func);

            //-----------------------------------------------------------------
            //! get iterator to first element
            iterator begin() { return _results.begin(); }

            //-----------------------------------------------------------------
            //! get iterator to last+1 element
            iterator end() { return _results.end(); }

            //-----------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const { return _results.begin(); }

            //-----------------------------------------------------------------
            //! get const iterator to last+1 element
            const_iterator end() const { return _results.end(); }

            //-----------------------------------------------------------------
            //! get size
            size_t size() const { return _results.size(); }

            //-----------------------------------------------------------------
            //! set pre-run function
            void prerun(const function_t f) { _pre_run = f; }

            //-----------------------------------------------------------------
            //! set post-run function
            void postrun(const function_t f) { _post_run = f; }
    };

    //-----------------------------------------------------------------------------
    template<typename TIMERT> void benchmark_runner::run(size_t n,function_t &func)
    {
        for(size_t i=0;i<n;i++)
        {
            TIMERT timer;

            _pre_run(); //run function before benchmark

            //run the write cycle
            timer.start();
            func();
            timer.stop();

            _post_run(); //run function after benchmark

            //getting the result
            benchmark_result result(timer.duration(),timer.unit());
            _results.push_back(result);
        }

    }

    //--------------------------------------------------------------------------
    /*!
    \brief compute the average result

    Computes the average of the results of each individual run. The result is
    returned as an instance of benchmark_result.
    \param bm benchmark run
    \return average benchmark result
    */
    benchmark_result average(const benchmark_runner &bm);

    //-------------------------------------------------------------------------
    /*!
    \brief compute result standard deviation

    Computes the standard deviation for all individual results in the original
    benchmark run. 
    \param bm benchmark run
    \return standard deviation of the result
    */
    benchmark_result standard_deviation(const benchmark_runner &bm);

//end of namespace
}
}
