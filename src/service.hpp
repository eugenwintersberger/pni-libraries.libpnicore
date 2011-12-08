/*
 * service.hpp
 *
 *  Created on: Dec 8, 2011
 *      Author: eugen
 */

#ifndef SERVICE_HPP_
#define SERVICE_HPP_

namespace pni{
namespace utils{

#define DEPRECATION_WARNING(old_method,new_method) \
	std::cerr<<"Method "+String(old_method)+"is deprecated and will be removed!"<<std::endl;\
	std::cerr<<"use "+String(new_method)+" instead!"<<std::endl;

}
}




#endif /* SERVICE_HPP_ */
