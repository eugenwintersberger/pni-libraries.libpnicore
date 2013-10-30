#include "EqualityCheck.hpp"

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

void check_equality(string a, string b)
{
    CPPUNIT_ASSERT(a == b);
}

void check_equality(Bool a,Bool b)
{
    CPPUNIT_ASSERT(a == b);
}
