/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Sep 02, 2011
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/utils/Scalar.hpp>

#define DOUBLE_PREC 1.e-3

using namespace pni::utils;

class ScalarTest : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(ScalarTest);
        CPPUNIT_TEST(testConstructors);

        CPPUNIT_TEST(testConversion);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testSetGetValue);
        CPPUNIT_TEST(testBinaryAddOperation);
        CPPUNIT_TEST(testBinarySubtractionOperation);
        CPPUNIT_TEST(testBinaryDivisionOperation);
        CPPUNIT_TEST(testBinaryMultiplicationOperation);
        CPPUNIT_TEST(testUnaryAddOperation);
        CPPUNIT_TEST(testUnaryDivOperation);
        CPPUNIT_TEST(testUnarySubOperation);
        CPPUNIT_TEST(testUnaryMultOperation);
        CPPUNIT_TEST(testComparison);
        CPPUNIT_TEST_SUITE_END();
    private:
    public:
        void tearDown();
        void setUp();
        
        void testConstructors();
        void testAssignment();
        void testSetGetValue();
        void testComparison();

        //some remarks about testing binary operations:
        //In all cases the temporary type of the result
        //is ok - so exceptions are raised only in cases
        //where the assignment operation and the type of the
        //l-value object do not satisfy the requirements for
        //assignment.
        void testBinaryAddOperation();
        void testBinarySubtractionOperation();
        void testBinaryDivisionOperation();
        void testBinaryMultiplicationOperation();


        void testUnaryAddOperation();
        void testUnaryMultOperation();
        void testUnaryDivOperation();
        void testUnarySubOperation();
        void testConversion();
};
