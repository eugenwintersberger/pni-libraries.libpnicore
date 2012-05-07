/*
 * BinaryArithmetics.hpp
 *
 *  Created on: Aug 31, 2011
 *      Author: eugen
 */

#ifndef BINARYARITHMETICS_HPP_
#define BINARYARITHMETICS_HPP_

//! \cond no_doc
class BinaryArithmetics{
public:
	template<typename RType,typename AType,typename BType,
			 template <typename RType> class RObject,
			 template <typename AType> class AObject>
	RObject<RType> add(const AObject<AType> &a,const BType &b);

	template<typename RType,typename AType,typename BType,
			 template <typename RType> class RObject,
			 template <typename AType> class AObject,
			 template <typename BType> class BObject>
	RObject<RType> add(const AObject<AType> &a,const BObject<BType> &b);


};
template<typename RType,typename AType,typename BType,
	     template <typename RType> class RObject,
		 template <typename AType> class AObject>
RObject<RType> BinaryArithmetics::add(const AObject<AType> &a,const BType &b){{
	RObject<RType> o(a);


	return o;
}

template<typename RType,typename AType,typename BType,
		 template <typename RType> class RObject,
		 template <typename AType> class AObject,
		 template <typename BType> class BObject>
RObject<RType> BinaryArithemtics::add(const AObject<AType> &a,const BObject<BType> &b){
	RObject<RType> o(a);


	return o;
}

//! \endcond

#endif /* BINARYARITHMETICS_HPP_ */
