#include "EqualityCheck.hpp"

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

void check_equality(const string &a,const string &b)
{
    CPPUNIT_ASSERT(a == b);
}

void check_equality(const Bool &a,const Bool &b)
{
    CPPUNIT_ASSERT(a == b);
}
