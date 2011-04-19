//implementation of the exception classes

#include<iostream>
#include<string>

#include "exceptions.hpp"

Exception::Exception(const std::string &n){
    _name = n;
}

Exception::Exception(const char *n){
	_name = std::string(n);
}
     
Exception::Exception(const std::string &n,const std::string &w){
    _name = n;
    _who = w;
}

Exception::Exception(const char *n,const char *w){
	_name = std::string(n);
	_who = std::string(w);
}


Exception::Exception(const std::string &n,const std::string &w,
                     const std::string &d)
{
    _name = n;
    _who = w;
    _desc = d;
}

Exception::Exception(const char *n,const char *w,const char *d){
	_name = std::string(n);
	_who  = std::string(w);
	_desc = std::string(d);
}

std::ostream &operator<<(std::ostream &ostr,const Exception &ex){
    ostr<<ex._name<<"raised by "<<ex._who<<std::endl;
    ostr<<ex._desc<<std::endl;
    
    return ostr;
}
