#include<iostream>
#include<limits>

#include "Types.hpp"
#include "TypeInfo.hpp"

using namespace pni::utils;

template<typename A> void print_type(){
	std::cout<<"Size:  "<<TypeInfo<A>::size<<" Bytes ";
	std::cout<<"Range: ("<<TypeInfo<A>::getMin()<<" , "<<TypeInfo<A>::getMax()<<")"<<std::endl;
}

int main(int argc,char **argv){
	std::cout<<"UInt8: ";
	print_type<UInt8>();
	std::cout<<"Int8: ";
	print_type<Int8>();

	std::cout<<"UInt16: ";
	print_type<UInt16>();
	std::cout<<"Int16: ";
	print_type<Int16>();

	std::cout<<"UInt32: ";
	print_type<UInt32>();
	std::cout<<"Int32: ";
	print_type<Int32>();

	std::cout<<"UInt64: ";
	print_type<UInt64>();
	std::cout<<"Int64: ";
	print_type<Int64>();

	std::cout<<"Float32: ";
	print_type<Float32>();
	std::cout<<"Float64: ";
	print_type<Float64>();
	std::cout<<"Float128: ";
	print_type<Float128>();

	std::cout<<"Complex32: ";
	print_type<Complex32>();
	std::cout<<"Complex64: ";
	print_type<Complex64>();
	std::cout<<"Complex128: ";
	print_type<Complex128>();

    return 0;
}
