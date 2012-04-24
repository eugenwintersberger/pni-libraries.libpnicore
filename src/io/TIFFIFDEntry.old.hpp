/*
 * Declaration of class TIFFIFDEntry
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of class TIFFIFDEntry.
 *
 * Created on: Jun 16, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#ifndef TIFFIDFENTRY_HPP_
#define TIFFIDFENTRY_HPP_

#include <vector>
#include <fstream>

#include "../Types.hpp"
#include "../Exceptions.hpp"

#include "TIFFIFDAbstractEntry.hpp"
#include "TIFFRational.hpp"

namespace pni{
namespace utils{

//! \ingroup io_classes
//! \brief type trait for TIFF IFD entries

//! This trait is used to set the type code in the getEntryTypeCode method of
//! the IDFEntry template. The trait is specialized for all available data
//! types for TIFF IFD entries.
template<typename T> class IFDEntryTypeTrait{
public:
	static const IFDEntryTypeCode TypeCode;  //!< typecode of the IDF entry
};

//! \cond NO_API_DOC

//! \ingroup io_classes
//! \brief trait specialication for 8Bit unsigned integer entries
template<> class IFDEntryTypeTrait<UInt8>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_BYTE; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 8Bit signed integer entries
template<> class IFDEntryTypeTrait<Int8>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_SBYTE; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 16Bit unsigned integer entries
template<> class IFDEntryTypeTrait<UInt16>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_SHORT; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 16Bit signed integer entries
template<> class IFDEntryTypeTrait<Int16>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_SSHORT; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 32Bit unsigned integer entries
template<> class IFDEntryTypeTrait<UInt32>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_LONG; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 32Bit signed integer entries
template<> class IFDEntryTypeTrait<Int32>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_SLONG; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 32Bit IEEE float entries
template<> class IFDEntryTypeTrait<Float32>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_FLOAT; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 64Bit IEEE float entries
template<> class IFDEntryTypeTrait<Float64>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_DOUBLE; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 32Bit unsigned integer Rational entries
template<> class IFDEntryTypeTrait<URational>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_RATIONAL; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for 32Bit signed integer Rational entries
template<> class IFDEntryTypeTrait<SRational>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_SRATIONAL; //!< IDFEntryTypeCode value
};

//! \ingroup io_classes
//! \brief trait specialization for String entries
template<> class IFDEntryTypeTrait<String>{
public:
	static const IFDEntryTypeCode TypeCode = IDFE_ASCII; //!< IDFEntryTypeCode value
};
//! \endcond

template<typename T> class IFDEntry;
template<typename T> std::ifstream &operator>>(std::ifstream &,IFDEntry<T> &);
template<typename T> std::ostream &operator<<(std::ostream &,const IFDEntry<T> &);

//! \ingroup io_classes
//! \brief typed IFDEntry

//! The IFDEntry template represents an IFD entry. Read/write access to the
//! elements stored is given by the [] operator along with the integer index of
//! the element that should be addressed.
template<typename T>
class IFDEntry:public IFDAbstractEntry{
protected:
	typedef typename std::vector<T>::iterator _iterator;  //!< iterator over the element entries
	typedef typename std::vector<T>::const_iterator _const_iterator; //!< const iterator over the element entries
	std::vector<T> _values; //!< vector holding the entry elements
public:
	typedef std::shared_ptr<IFDEntry<T> > sptr;          //!< smart pointer to an entry
	typedef std::vector<sptr> list;                        //!< vector type of IFD smart pointers
	typedef typename list::iterator iterator;              //!< iterator over an entry list
	typedef typename list::const_iterator const_iterator;  //!< const iterator over an entry list
	//! default constructor
	IFDEntry();
	//! copy constructor
	IFDEntry(const IFDEntry<T> &o);
	//! standard constructor with initialization

	//! \param n name of the entry
	//! \param cnt number of elements
	//! \param values pointer to a cnt values which belong to the element
	IFDEntry(const String &n, const UInt32 &cnt,const T *values);
	//! standard constructor without initialization

	//! \param n name of the entry
	//! \param cnt number of elements in the entry
	IFDEntry(const String &n, const UInt32 &cnt);
	//! destructor
	virtual ~IFDEntry();

	//! assignment operator
	IFDEntry<T> &operator=(const IFDEntry &);

	//! [] operator for read/write access

	//! if i exceeds the number of elements in the entry an IndexError
	//! exception will be thrown.
	//! \param i index of the element
	T &operator[](const UInt64 &i);

	//! [] operator for read access

	//! if i exceeds the number of elements in the entry an IndexError
	//! exception will be thrown.
	//! \param i index of the element
	T operator[](const UInt64 &i) const;

	//! return the entries type code

	//! This method can be used to obtain the type code of a particular
	//! entry at runtime.
	virtual IFDEntryTypeCode getEntryTypeCode() const{
		return IFDEntryTypeTrait<T>::TypeCode;
	}

	//! ifstream operator to read the entry from a binary stream
	friend std::ifstream &operator>><> (std::ifstream &in,IFDEntry<T> &e);
	//! ostream operator to write the content of an entry to standard out
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
	EXCEPTION_SETUP("template<typename T> T &IFDEntry<T>::operator[](const UInt64 &i)");
	if(i>=_cnt){
		EXCEPTION_INIT(IndexError,"IFD entry element out of bound!");
		EXCEPTION_THROW();
	}
	return _values[i];
}

template<typename T> T IFDEntry<T>::operator[](const UInt64 &i) const {
	EXCEPTION_SETUP("template<typename T> T IFDEntry<T>::operator[](const UInt64 &i) const");
	if (i >= _cnt) {
		EXCEPTION_INIT(IndexError,"IFD entry element out of bound!");
		EXCEPTION_THROW();
	}
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
