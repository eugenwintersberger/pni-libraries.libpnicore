/*
 * ScalarObject.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef SCALAROBJECT_HPP_
#define SCALAROBJECT_HPP_

#include "PNITypes.hpp"
#include "DataObject.hpp"

namespace pni{
namespace utils{


class ScalarObject:public DataObject {
public:
	ScalarObject();
	virtual ~ScalarObject();
};


//end of namespace
}
}


#endif /* SCALAROBJECT_HPP_ */
