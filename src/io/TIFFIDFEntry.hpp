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

#include "TIFFIDFAbstractEntry.hpp"
#include "TIFFRational.hpp"

namespace pni{
namespace utils{


//define here traits to handle entry type codes
template<typename T> class IDFEntryTypeTrait{
public:
	static const IDFEntryTypeCode TypeCode;
};

template<> class IDFEntryTypeTrait<UInt8>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_BYTE;
};

template<> class IDFEntryTypeTrait<Int8>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SBYTE;
};

template<> class IDFEntryTypeTrait<UInt16>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SHORT;
};

template<> class IDFEntryTypeTrait<Int16>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SSHORT;
};

template<> class IDFEntryTypeTrait<UInt32>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_LONG;
};

template<> class IDFEntryTypeTrait<Int32>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SLONG;
};

template<> class IDFEntryTypeTrait<Float32>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_FLOAT;
};

template<> class IDFEntryTypeTrait<Float64>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_DOUBLE;
};

template<> class IDFEntryTypeTrait<URational>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_RATIONAL;
};

template<> class IDFEntryTypeTrait<SRational>{
public:
	static const IDFEntryTypeCode TypeCode = IDFE_SRATIONAL;
};

template<typename T> class IDFEntry;
template<typename T> std::ifstream &operator>>(std::ifstream &,IDFEntry<T> &);
template<typename T> std::ostream &operator<<(std::ostream &,const IDFEntry<T> &);

template<typename T>
class IDFEntry:public IDFAbstractEntry{
protected:
	typedef typename std::vector<T>::iterator _iterator;
	typedef typename std::vector<T>::const_iterator _const_iterator;
	std::vector<T> _values;
public:
	//! default constructor
	IDFEntry();
	//! copy constructor
	IDFEntry(const IDFEntry<T> &o);
	//! standard constructor
	IDFEntry(const String &n, const UInt32 &cnt,const T *values);
	IDFEntry(const String &n, const UInt32 &cnt);
	virtual ~IDFEntry();

	IDFEntry<T> &operator=(const IDFEntry &);

	T &operator[](const UInt64 &i);
	T operator[](const UInt64 &i) const;

	virtual IDFEntryTypeCode getEntryTypeCode() const{
		return IDFEntryTypeTrait<T>::TypeCode;
	}

	friend std::ifstream &operator>><> (std::ifstream &in,IDFEntry<T> &e);
	friend std::ostream &operator<<<> (std::ostream &o,const IDFEntry<T> &e);
};

//implement default constructor
template<typename T> IDFEntry<T>::IDFEntry():IDFAbstractEntry(){
	_values.clear();
}

template<typename T> IDFEntry<T>::IDFEntry(const IDFEntry<T> &o):IDFAbstractEntry(o){
	_cnt = o._cnt;
	_name = o._name;

	for(_iterator iter=o._values.begin();iter != o._values.end();iter++){
		_values.push_back(*iter);
	}
}

template<typename T> IDFEntry<T>::IDFEntry(const String &n,const UInt32 &cnt,const T *values)
		:IDFAbstractEntry(n,cnt)
{
	for(UInt32 i=0;i<cnt;i++){
		_values.push_back(values[i]);
	}
}

template<typename T> IDFEntry<T>::IDFEntry(const String &n,const UInt32 &cnt)
		:IDFAbstractEntry(n,cnt)
{
}

template<typename T> IDFEntry<T>::~IDFEntry(){

}

template<typename T> IDFEntry<T> &IDFEntry<T>::operator=(const IDFEntry<T> &o){
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

template<typename T> T &IDFEntry<T>::operator[](const UInt64 &i){
	return _values[i];
}

template<typename T> T IDFEntry<T>::operator[](const UInt64 &i) const {
	return _values[i];
}

template<> std::ifstream &operator>>(std::ifstream &in,IDFEntry<URational> &e){
	UInt32 buffer1;
	UInt32 buffer2;
	Int32 vo;
	Int32 old_offset;

	//In the case of the 32Bit long values the last 4Byte entry of a
	//entry stream is always a stream offset.

	//data does not fit - interpret the 4 bytes as an offset
	in.read((char *) (&vo), 4);
	//safe the offset in the stream
	old_offset = in.tellg();

	in.seekg(vo, std::ios::beg);
	//read the data
	for (UInt64 i = 0; i < e._cnt; i++) {
		in.read((char *) (&buffer1), sizeof(UInt32));  //read the numerator
		in.read((char *) (&buffer2), sizeof(UInt32));  //read the denominator
		e._values.push_back(URational(buffer1,buffer2));
	}

	//reset the stream position
	in.seekg(old_offset, std::ios::beg);

	return in;
}

template<> std::ifstream &operator>>(std::ifstream &in,IDFEntry<SRational> &e){
	Int32 buffer1;
	Int32 buffer2;
	Int32 vo;
	Int32 old_offset;

	//In the case of the 32Bit long values the last 4Byte entry of a
	//entry stream is always a stream offset.

	//data does not fit - interpret the 4 bytes as an offset
	in.read((char *) (&vo), 4);
	//safe the offset in the stream
	old_offset = in.tellg();

	in.seekg(vo, std::ios::beg);
	//read the data
	for (UInt64 i = 0; i < e._cnt; i++) {
		in.read((char *) (&buffer1), sizeof(Int32));  //read the numerator
		in.read((char *) (&buffer2), sizeof(Int32));  //read the denominator
		e._values.push_back(SRational(buffer1,buffer2));
	}

	//reset the stream position
	in.seekg(old_offset, std::ios::beg);

	return in;
}

template<typename T> std::ifstream &operator>>(std::ifstream &in,IDFEntry<T> &e){
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



template<typename T> std::ostream &operator<<(std::ostream &o,const IDFEntry<T> &e){
	o<<"Entry "<<e._name<<"["<<e._cnt<<"] ";
	for(typename IDFEntry<T>::_const_iterator iter = e._values.begin();iter != e._values.end();iter++){
		o<<*iter<<" ";
	}

	return o;
}


//define some default entry types
typedef IDFEntry<UInt8> ByteEntry;
typedef IDFEntry<Int8> SByteEntry;
typedef IDFEntry<UInt16> ShortEntry;
typedef IDFEntry<Int16> SShortEntry;
typedef IDFEntry<UInt32> LongEntry;
typedef IDFEntry<Int32> SLongEntry;
typedef IDFEntry<Float32> FloatEntry;
typedef IDFEntry<Float64> DoubleEntry;

typedef IDFEntry<URational> RationalEntry;
typedef IDFEntry<SRational> SRationalEntry;


//end of namespace
}
}

#endif /* TIFFIDFENTRY_HPP_ */
