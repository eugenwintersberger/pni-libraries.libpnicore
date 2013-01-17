#include "EqualityCheck.hpp"

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

void check_equality(const String &a,const String &b)
{
    CPPUNIT_ASSERT(a == b);
}
