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
 *  Created on: Oct 25, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include "BenchmarkResult.hpp"
#include <list>
#include <functional>

namespace pni{
namespace core{

    class BenchmarkRunner
    {
        private:
            //! list with benchmark results
            std::list<BenchmarkResult> _results;
            std::function<void()> _pre_run;
            std::function<void()> _post_run;

            void do_nothing() {}

        public:
            //======================public types===================================
            typedef std::list<BenchmarkResult>::iterator iterator;
            typedef std::list<BenchmarkResult>::const_iterator const_iterator;
            typedef std::function<void()> function_t;

            //====================constructors and destructor=======================
            //! default constructor
            BenchmarkRunner():_results(0)
            {
                _pre_run =
                    function_t(std::bind(&BenchmarkRunner::do_nothing,*this));
                _post_run = 
                    function_t(std::bind(&BenchmarkRunner::do_nothing,*this));
            }

            //! destructor
            virtual ~BenchmarkRunner(){}

            //! perform all runs
            template<typename TIMERT> void run(size_t n,function_t &func);

            //! get iterator to first element
            iterator begin() { return _results.begin(); }

            //! get iterator to last+1 element
            iterator end() { return _results.end(); }

            //! get const iterator to first element
            const_iterator begin() const { return _results.begin(); }

            //! get const iterator to last+1 element
            const_iterator end() const { return _results.end(); }

            //! get size
            size_t size() const { return _results.size(); }

            void prerun(const function_t f) { _pre_run = f; }

            void postrun(const function_t f) { _post_run = f; }
    };

    //-----------------------------------------------------------------------------
    template<typename TIMERT> void BenchmarkRunner::run(size_t n,function_t &func)
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
            BenchmarkResult result(timer.duration(),timer.unit());
            _results.push_back(result);
        }

    }

    //-----------------------------------------------------------------------------
    BenchmarkResult average(const BenchmarkRunner &bm)
    {
        Float64 time = 0.;

#ifdef NOFOREACH
        for(auto iter = bm.begin();iter!=bm.end();++iter)
        {
            auto &result = *iter;
#else
        for(auto result: bm)
        {
#endif
            time += result.time();
        }

        time /= Float64(bm.size());

        return BenchmarkResult(time,bm.begin()->unit());

    }

//end of namespace
}
}
