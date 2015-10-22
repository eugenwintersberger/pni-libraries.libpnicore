//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Nov 27, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing math operations on arrays
#include <boost/test/unit_test.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/current_function.hpp>
#include <pni/core/algorithms/math/inplace_arithmetics.hpp>

#include "array_types.hpp"
#include <cmath>
#include "../data_generator.hpp"
#include "number_ranges.hpp"


namespace boost{
namespace math{

    //utility funtion template to check for the finiteness of a 
    //comples value. This is only the case if real and imaginary part 
    //are finite.
    template<typename T> bool isfinite(std::complex<T> v)
    {

        return isfinite(v.real()) && isfinite(v.imag());
    }
}
}


template<typename AT> struct fixture
{
    typedef AT array_type;
    typedef typename AT::value_type value_type;
    typedef random_generator<value_type> generator_type; 
        
    generator_type gen_rhs;
    generator_type gen_lhs;
    shape_t shape;
    array_type lhs_orig;
    array_type lhs;
    value_type rhs_scalar;
    array_type rhs;
    pni::core::type_id_t tid;
    pni::core::string type_name;

    template<typename RT> fixture(const RT &r):
        gen_rhs(r.rhs_min(),r.rhs_max()),
        gen_lhs(r.lhs_min(),r.lhs_max()),
        shape(shape_t{2,3,4}),
        lhs_orig(array_type::create(shape)),
        lhs(array_type::create(shape)),
        rhs_scalar(gen_rhs()),
        rhs(array_type::create(shape)),
        tid(pni::core::type_id_map<value_type>::type_id),
        type_name(str_from_type_id(tid))
    {
        std::generate(lhs.begin(),lhs.end(),gen_lhs); 
        std::generate(rhs.begin(),rhs.end(),gen_rhs);
        std::copy(lhs.begin(),lhs.end(),lhs_orig.begin());
    }
};

typedef inplace_arithmetics ipa_type; 

BOOST_AUTO_TEST_SUITE(inplace_arithmetics_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(add_scalar_test,AT,all_array_types)
    {
        fixture<AT> f((add_ranges<typename AT::value_type>()));
    
        ipa_type::add(f.lhs,f.rhs_scalar);

        for(size_t i=0;i<f.lhs.size();++i) 
        {
            if(!boost::math::isfinite(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"+"<<f.rhs_scalar
                                    <<" at index "<<i<< "with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],f.lhs_orig[i]+f.rhs_scalar);
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(add_array_test,AT,all_array_types)
    {
        fixture<AT> f((add_ranges<typename AT::value_type>()));
    
        ipa_type::add(f.lhs,f.rhs);

        for(size_t i=0;i<f.lhs.size();++i) 
        {
            if(!boost::math::isfinite(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"+"<<f.rhs[i]
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],f.lhs_orig[i]+f.rhs[i]);
            }
        }

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(sub_scalar_test,AT,all_array_types)
    {
        fixture<AT> f((add_ranges<typename AT::value_type>()));
    
        ipa_type::sub(f.lhs,f.rhs_scalar);

        for(size_t i=0;i<f.lhs.size();++i) 
        {
            if(!boost::math::isfinite(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"-"<<f.rhs_scalar
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],f.lhs_orig[i]-f.rhs_scalar);
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(sub_array_test,AT,all_array_types)
    {
        fixture<AT> f((add_ranges<typename AT::value_type>()));
    
        ipa_type::sub(f.lhs,f.rhs);

        for(size_t i=0;i<f.lhs.size();++i) 
        {
            if(!boost::math::isfinite(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"-"<<f.rhs[i]
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],f.lhs_orig[i]-f.rhs[i]);
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_div_scalar,AT,all_array_types)
    {
        fixture<AT> f((div_ranges<typename AT::value_type>()));

        ipa_type::div(f.lhs,f.rhs_scalar);
    
        for(size_t i=0;i<f.lhs.size();++i)
        {
            if(!boost::math::isfinite(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"/"<<f.rhs_scalar
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],f.lhs_orig[i]/f.rhs_scalar);
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_div_array,AT,all_array_types)
    {
        typedef typename AT::value_type value_type;
        fixture<AT> f((div_ranges<value_type>()));

        ipa_type::div(f.lhs,f.rhs);

        for(size_t i=0;i<f.lhs.size();++i)
        {
            if(!boost::math::isfinite(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"/"<<f.rhs[i]
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],f.lhs_orig[i]/f.rhs[i]);
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_scalar,AT,all_array_types)
    {
        fixture<AT> f((mult_ranges<typename AT::value_type>()));

        ipa_type::mult(f.lhs,f.rhs_scalar);
        
        for(size_t i=0;i<f.lhs.size();++i)
        {
            if(!boost::math::isfinite(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"*"<<f.rhs_scalar
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],(f.lhs_orig[i]*f.rhs_scalar));
            }
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_array,AT,all_array_types)
    {
        fixture<AT> f((mult_ranges<typename AT::value_type>()));

        ipa_type::mult(f.lhs,f.rhs);

        for(size_t i=0;i<f.lhs.size();++i)
        {
            if(!boost::math::isfinite(f.lhs[i]))
            {
                BOOST_TEST_MESSAGE( "Infinite result "<<f.lhs[i]<<" from "<<
                                    f.lhs_orig[i]<<"*"<<f.rhs[i]
                                    <<" at index "<<i<<" with type: "<<
                                    f.type_name);
            }
            else
            {
                BOOST_CHECK_EQUAL(f.lhs[i],(f.lhs_orig[i]*f.rhs[i]));
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()

