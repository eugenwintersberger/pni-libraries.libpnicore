//implementation of the exception classes

#include<iostream>
#include<string>

#include "Exceptions.hpp"

namespace pni{
namespace utils{


Exception::Exception(const String &n){
    _name = n;
}
     
Exception::Exception(const String &n,const String &i){
    _name = n;
    _issuer = i;
}

Exception::Exception(const String &n,const String &i,const String &d)
{
    _name = n;
    _issuer = i;
    _description = d;
}

std::ostream &Exception::print(std::ostream &o) const {
	o<<_name<<" by:  "<<_issuer<<std::endl;
	o<<_description<<std::endl;

	return o;
}

std::ostream &operator<<(std::ostream &ostr,const Exception &ex){
    return ex.print(ostr);
}

std::ostream &operator<<(std::ostream &o,const MemoryAllocationError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const ShapeMissmatchError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const SizeMissmatchError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const IndexError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const FileError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const TypeError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const RangeError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const NotImplementedError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const MemoryAccessError &e){
	return e.print(o);
}

//end of namespace
}
}
