/*
 * TIFFIDFEntry.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */

#ifndef TIFFIDFENTRY_HPP_
#define TIFFIDFENTRY_HPP_

#include <vector>
#include <fstream>

#include "../PNITypes.hpp"

#include "TIFFIFDAbstractEntry.hpp"
#include "TIFFRational.hpp"

namespace pni{
namespace utils{


//define here traits to handle entry type codes
template<typename T> class IFDEntryTypeTrait{
public:
	static const IDFEntryTypeCode TypeCode;
};

template<> class IFDEntryTypeTrait<UInt8>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_BYTE;
};

template<> class IFDEntryTypeTrait<Int8>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SBYTE;
};

template<> class IFDEntryTypeTrait<UInt16>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SHORT;
};

template<> class IFDEntryTypeTrait<Int16>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SSHORT;
};

template<> class IFDEntryTypeTrait<UInt32>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_LONG;
};

template<> class IFDEntryTypeTrait<Int32>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SLONG;
};

template<> class IFDEntryTypeTrait<Float32>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_FLOAT;
};

template<> class IFDEntryTypeTrait<Float64>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_DOUBLE;
};

template<> class IFDEntryTypeTrait<URational>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_RATIONAL;
};

template<> class IFDEntryTypeTrait<SRational>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SRATIONAL;
};

template<> class IFDEntryTypeTrait<String>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_ASCII;
};

template<typename T> class IFDEntry;
template<typename T> std::ifstream &operator>>(std::ifstream &,IFDEntry<T> &);
template<typename T> std::ostream &operator<<(std::ostream &,const IFDEntry<T> &);


template<typename T>
class IFDEntry:public IFDAbstractEntry{
protected:
	typedef typename std::vector<T>::iterator _iterator;
	typedef typename std::vector<T>::const_iterator _const_iterator;
	std::vector<T> _values;
public:
	typedef boost::shared_ptr<IFDEntry<T> > sptr;
	typedef std::vector<sptr> list;
	typedef typename list::iterator iterator;
	typedef typename list::const_iterator const_iterator;
	//! default constructor
	IFDEntry();
	//! copy constructor
	IFDEntry(const IFDEntry<T> &o);
	//! standard constructor
	IFDEntry(const String &n, const UInt32 &cnt,const T *values);
	IFDEntry(const String &n, const UInt32 &cnt);
	virtual ~IFDEntry();

	IFDEntry<T> &operator=(const IFDEntry &);

	T &operator[](const UInt64 &i);
	T operator[](const UInt64 &i) const;

	virtual IDFEntryTypeCode getEntryTypeCode() const{
		return IFDEntryTypeTrait<T>::TypeCode;
	}

	friend std::ifstream &operator>><> (std::ifstream &in,IFDEntry<T> &e);
	friend std::ostream &operator<<<> (std::ostream &,const IFDEntry<T> &e);
};

//implement default constructor
template<typename T> IFDEntry<T>::IFDEntry():IFDAbstractEntry(){
	_values.clear();
}

template<typename T> IFDEntry<T>::IFDEntry(const IFDEntry<T> &o):IFDAbstractEntry(o){
	_cnt = o._cnt;
	_name = o._name;

	for(_iterator iter=o._values.begin();iter != o._values.end();iter++){
		_values.push_back(*iter);
	}
}

template<typename T> IFDEntry<T>::IFDEntry(const String &n,const UInt32 &cnt,const T *values)
		:IFDAbstractEntry(n,cnt)
{
	for(UInt32 i=0;i<cnt;i++){
		_values.push_back(values[i]);
	}
}

template<typename T> IFDEntry<T>::IFDEntry(const String &n,const UInt32 &cnt)
		:IFDAbstractEntry(n,cnt)
{
}

template<typename T> IFDEntry<T>::~IFDEntry(){
	//std::cout<<"Entry constructor called"<<std::endl;
}

template<typename T> IFDEntry<T> &IFDEntry<T>::operator=(const IFDEntry<T> &o){
	if (this != &o) {
		_name = o._name;
		_cnt = o._cnt;

		_values.clear();
		for (_iterator iter = o._values.begin(); iter != o._values.end(); iter++) {
			_values.push_back(*iter);
		}
	}

	return *this;
}

template<typename T> T &IFDEntry<T>::operator[](const UInt64 &i){
	return _values[i];
}

template<typename T> T IFDEntry<T>::operator[](const UInt64 &i) const {
	return _values[i];
}


template<typename T> std::ifstream &operator>>(std::ifstream &in,IFDEntry<T> &e){
	T buffer;
	Int32 vo;
	Int32 old_offset;
	//the frist thing we have to do is to check whether or not the Tag data fits into
	//the next 4 byte in the stream
	if(sizeof(T)*e._cnt>4){
		//data does not fit - interpret the 4 bytes as an offset
		in.read((char *)(&vo),4);
		//safe the offset in the stream
		old_offset = in.tellg();

		in.seekg(vo,std::ios::beg);
		//read the data
		for(UInt64 i=0;i<e._cnt;i++){
			in.read((char *)(&buffer),sizeof(T));
			e._values.push_back(buffer);
		}

		//reset the stream position
		in.seekg(old_offset,std::ios::beg);

	}else{
		//data fits
		for(UInt64 i=0;i<e._cnt;i++){
			in.read((char *)(&buffer),sizeof(T));
			e._values.push_back(buffer);
		}
		//need to modify the stream position in cases where the
		//amount of data read from the stream is smaller than 4 Byte
		in.seekg((4-(sizeof(T)*e._cnt)),std::ios::cur);

	}

	return in;
}



template<typename T> std::ostream &operator<<(std::ostream &o,const IFDEntry<T> &e){
	o<<"Entry "<<e._name<<"["<<e._cnt<<"] ";
	for(typename IFDEntry<T>::_const_iterator iter = e._values.begin();iter != e._values.end();iter++){
		o<<*iter<<" ";
	}

	return o;
}


//define some default entry types
typedef IFDEntry<UInt8> ByteEntry;
typedef IFDEntry<Int8> SByteEntry;
typedef IFDEntry<UInt16> ShortEntry;
typedef IFDEntry<Int16> SShortEntry;
typedef IFDEntry<UInt32> LongEntry;
typedef IFDEntry<Int32> SLongEntry;
typedef IFDEntry<Float32> FloatEntry;
typedef IFDEntry<Float64> DoubleEntry;

typedef IFDEntry<URational> RationalEntry;
typedef IFDEntry<SRational> SRationalEntry;
typedef IFDEntry<String> ASCIIEntry;


//end of namespace
}
}

#endif /* TIFFIDFENTRY_HPP_ */
