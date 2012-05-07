/*
 * SimpleArithmetics.hpp
 *
 *  Created on: Aug 31, 2011
 *      Author: eugen
 */

#ifndef INPLACEARITHMETICS_HPP_
#define INPLACEARITHMETICS_HPP_

#include <limits>

#include "../Exceptions.hpp"
#include "TypeInfo.hpp"

namespace pni{
namespace utils{

//! \cond no_doc
//Inplace arithmetics of typed objects - the object can only be a left-value
class InplaceArithmetics{
public:
	//object with a scalar
	template<typename A,template <typename A> class ObjectA,typename ObjectB >
	void add_inplace(ObjectA<A> &a,const ObjectB &b);

	template<typename A,typename B,
			 template <typename A> class ObjectA,
	         template <typename B> class ObjectB >
	void add_inplace(ObjectA<A> &a,const ObjectB<B> &b);

	template<typename A,template <typename A> class ObjectA,typename ObjectB>
	void mult_inplace(ObjectA<A> &a,const ObjectB &b);

	template<typename A,typename B,
			 template <typename A> class ObjectA,
		     template <typename B> class ObjectB>
	void mult_inplace(ObjectA<A> &a,const ObjectB<B> &b);

	template<typename A,template <typename A> class ObjectA,typename ObjectB>
	void sub_inplace(ObjectA<A> &a,const ObjectB &b);

	template<typename A,typename B,
			 template <typename A> class ObjectA,
			 template <typename B> class ObjectB>
	void sub_inplace(ObjectA<A> &a,const ObjectB<B> &b);

	template<typename A,template <typename A> class ObjectA,typename ObjectB>
	void div_inplace(ObjectA<A> &a,const ObjectB &b);

	template<typename A,typename B,
			 template <typename A> class ObjectA,
	         template <typename B> class ObjectB>
	void div_inplace(ObjectA<A> &a,const ObjectB<B> &b);
};

// \endcond


template<typename A,template <typename A> class ObjectA,typename ObjectB >
void InplaceArithmetics::add_inplace(ObjectA<A> &a,const ObjectB &b){
	EXCEPTION_SETUP("template<typename A,template <typename A> class ObjectA,typename ObjectB >"
			        "void InplaceArithmetics::add_inplace(ObjectA<A> &a,const ObjectB &b)");

	if(TypeInfo<A>::isSigned() != TypeInfo<ObjectB>::isSigned()){
		EXCEPTION_INIT(RangeError,"You try to add a signed with an unsigned value!");
		EXCEPTION_THROW();
	}

	for(UInt64 i=0;i<a.size();i++){
		a[i] += b;
	}
}

template<typename A,typename B,
		 template <typename A> class ObjectA,
		 template <typename B> class ObjectB >
void InplaceArithmetics::add_inplace(ObjectA<A> &a,const ObjectB<B> &b){
	EXCEPTION_SETUP("template<typename A,typename B,template <typename A> class ObjectA,"
					"template <typename B> class ObjectB >"
					 "void InplaceArithmetics::add_inplace(Object<A> &a,const ObjectB<B> &b)");
	if(a.size()!=b.size()){
		EXCEPTION_INIT(SizeMissmatchError,"Object sizes do not match!");
		EXCEPTION_THROW();
	}

	for(UInt64 i=0;i<a.size();i++){
		a[i] += b[i];
	}
}

template<typename A,template <typename A> class ObjectA,typename ObjectB>
void InplaceArithmetics::mult_inplace(ObjectA<A> &a,const ObjectB &b){
	EXCEPTION_SETUP("template<typename A,template <typename A> class ObjectA,typename ObjectB>"
				    "void InplaceArithmetics::mult_inplace(ObjectA<A> &a,const ObjectB &b)");
	for(UInt64 i=0;i<a.size();i++){
		a[i] *= b;
	}
}

template<typename A,typename B,
		 template <typename A> class ObjectA,
	     template <typename B> class ObjectB>
void InplaceArithmetics::mult_inplace(ObjectA<A> &a,const ObjectB<B> &b){
	EXCEPTION_SETUP("template<template <typename A> class ObjectA,"
					"template <typename B> class ObjectB>"
					"void InplaceArithmetics::mult_inplace(ObjectA<A> &a,const ObjectB<B> &b)");
	if(a.size()!=b.size()){
		EXCEPTION_INIT(SizeMissmatchError,"Object sizes do not match!");
		EXCEPTION_THROW();
	}

	for(UInt64 i=0;i<a.size();i++){
		a[i] *= b[i];
	}
}

template<typename A,template <typename A> class ObjectA,typename ObjectB>
void InplaceArithmetics::sub_inplace(ObjectA<A> &a,const ObjectB &b){
	EXCEPTION_SETUP("template<template <typename A> class ObjectA,typename ObjectB>"
				    "void InplaceArithmetics::sub_inplace(ObjectA<A> &a,const ObjectB &b)");

	for(UInt64 i=0;i<a.size();i++){
		a[i] -= b;
	}
}

template<typename A,typename B,
		 template <typename A> class ObjectA,
		 template <typename B> class ObjectB>
void InplaceArithmetics::sub_inplace(ObjectA<A> &a,const ObjectB<B> &b){
	EXCEPTION_SETUP("template<template <typename A> class ObjectA,"
				     "template <typename B> class ObjectB>"
					 "void InplaceArithmetics::sub_inplace(ObjectA<A> &a,const ObjectB<B> &b)");

	if(a.size() != b.size()){
		EXCEPTION_INIT(SizeMissmatchError,"Object sizes do not match!");
		EXCEPTION_THROW();
	}

	for(UInt64 i=0;i<a.size();i++) a[i] -= b[i];
}

template<typename A,template <typename A> class ObjectA,typename ObjectB>
void InplaceArithmetics::div_inplace(ObjectA<A> &a,const ObjectB &b){
	EXCEPTION_SETUP("template<template <typename A> class ObjectA,typename ObjectB>"
				    "void InplaceArithmetics::div_inplace(ObjectA<A> &a,const ObjectB &b)");

	for(UInt64 i=0;i<a.size();i++) a[i] /= b;

}

template<typename A,typename B,
		 template <typename A> class ObjectA,
         template <typename B> class ObjectB>
void InplaceArithmetics::div_inplace(ObjectA<A> &a,const ObjectB<B> &b){
	EXCEPTION_SETUP("template<template <typename A> class ObjectA,"
				    "template <typename B> class ObjectB>"
					"void InplaceArithmetics::div_inplace(ObjectA<A> &a,const ObjectB<B> &b)");

	if(a.size() != b.size()){
		EXCEPTION_INIT(SizeMissmatchError,"Object sizes do not match!");
		EXCEPTION_THROW();
	}

	for(UInt64 i=0;i<a.size();i++) a[i] /= b[i];

}

//end namespace
}
}

#endif /* INPLACEARITHMETICS_HPP_ */
