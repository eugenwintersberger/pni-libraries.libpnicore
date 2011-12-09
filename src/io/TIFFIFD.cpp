/*
 * Implementation of class TIFFIFD
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
 * Implementation of class TIFFIFD.
 *
 * Created on: Jun 16, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "TIFFIFD.hpp"
#include "TIFFIFDEntry.hpp"
#include "TIFFStandard.hpp"
#include "TIFFIFDAbstractEntry.hpp"

namespace pni{
namespace utils{

//------------------------------------------------------------------------------
TIFFIFD::TIFFIFD() {
	_idf_offset = 0;
	_idf_next_offset = 0;
	_number_of_idf_entries = 0;
	_entry_list.clear();
}

//------------------------------------------------------------------------------
TIFFIFD::TIFFIFD(const TIFFIFD &idf){
	_idf_offset = idf._idf_offset;
	_idf_next_offset = idf._idf_next_offset;
	_number_of_idf_entries = idf._number_of_idf_entries;
	_entry_list = idf._entry_list;
}

//------------------------------------------------------------------------------
TIFFIFD::~TIFFIFD() {
	_entry_list.clear();
}

//------------------------------------------------------------------------------
TIFFIFD &TIFFIFD::operator=(const TIFFIFD &o){
	if(this != &o){
		_idf_offset = o._idf_offset;
		_idf_next_offset = o._idf_next_offset;
		_number_of_idf_entries = o._number_of_idf_entries;
		_entry_list.clear();
		_entry_list = o._entry_list;
	}

	return *this;
}

//------------------------------------------------------------------------------
UInt16 TIFFIFD::getNumberOfEntries() const{
	return _number_of_idf_entries;
}
//------------------------------------------------------------------------------
bool TIFFIFD::isLastIDF() const {
	if(_idf_next_offset==0) return true;

	return false;
}

//------------------------------------------------------------------------------
Int32 TIFFIFD::getNextOffset() const{
	return _idf_next_offset;
}

//------------------------------------------------------------------------------
Int32 TIFFIFD::getOffset() const {
	return _idf_offset;
}

//------------------------------------------------------------------------------
void TIFFIFD::setOffset(const Int32 &o){
	_idf_offset = o;
}

//------------------------------------------------------------------------------
IFDAbstractEntry::sptr TIFFIFD::operator[](const UInt16 i){
	EXCEPTION_SETUP("IFDAbstractEntry::sptr TIFFIFD::operator[](const UInt16 i)");
	if(i>=getNumberOfEntries()){
		EXCEPTION_INIT(IndexError,"Index exceeds number of IFD entries!");
		EXCEPTION_THROW();
	}
	return _entry_list[i];
}

//------------------------------------------------------------------------------
IFDAbstractEntry::sptr TIFFIFD::operator[](const String &n){
	EXCEPTION_SETUP("IFDAbstractEntry::sptr TIFFIFD::operator[](const String &n)");
	IFDAbstractEntry::const_iterator iter;
	IFDAbstractEntry::sptr entry;

	for(iter = _entry_list.begin(); iter != _entry_list.end();iter++ ){
		entry = *iter;
		if(entry->getName()==n){
			return entry;
		}
	}
	KeyError error(__ExIssuer,"IFD entry key ["+n+"] not found in IFD!");
	throw error;
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const TIFFIFD &idf){
	o<<"IDF at offset "<<idf._idf_offset<<" with "<<idf._number_of_idf_entries<<" entries"<<std::endl;
	o<<idf._entry_list.size()<<std::endl;
	IFDAbstractEntry::sptr e;
	IFDAbstractEntry::const_iterator iter;

	for(iter = idf._entry_list.begin();iter!=idf._entry_list.end();iter++){
		e = *iter;

		switch(e->getEntryTypeCode()){
		case IDFE_BYTE:
			o<<*boost::dynamic_pointer_cast<ByteEntry>(e)<<std::endl; break;
		case IDFE_ASCII:
			o<<*boost::dynamic_pointer_cast<ASCIIEntry>(e)<<std::endl; break;
		case IDFE_SHORT:
			o<<*boost::dynamic_pointer_cast<ShortEntry>(e)<<std::endl; break;
		case IDFE_LONG:
			o<<*boost::dynamic_pointer_cast<LongEntry>(e)<<std::endl; break;
		case IDFE_RATIONAL:
			o<<*boost::dynamic_pointer_cast<RationalEntry>(e)<<std::endl; break;
		case IDFE_UNDEFINED:
			o<<*boost::dynamic_pointer_cast<ASCIIEntry>(e)<<std::endl; break;
		case IDFE_SBYTE:
			o<<*boost::dynamic_pointer_cast<SByteEntry>(e)<<std::endl; break;
		case IDFE_SSHORT:
			o<<*boost::dynamic_pointer_cast<SShortEntry>(e)<<std::endl; break;
		case IDFE_SLONG:
			o<<*boost::dynamic_pointer_cast<SLongEntry>(e)<<std::endl; break;
		case IDFE_SRATIONAL:
			o<<*boost::dynamic_pointer_cast<SRationalEntry>(e)<<std::endl; break;
		case IDFE_FLOAT:
			o<<*boost::dynamic_pointer_cast<FloatEntry>(e)<<std::endl; break;
		case IDFE_DOUBLE:
			o<<*boost::dynamic_pointer_cast<DoubleEntry>(e)<<std::endl; break;
		default:
			o<<*e<<std::endl;

		};
	}

	return o;
}

//------------------------------------------------------------------------------
std::ifstream &operator>>(std::ifstream &in,TIFFIFD &idf){
	UInt64 i;
	UInt16 tag,ttype;
	UInt32 cnt;
	IFDAbstractEntry::sptr e;
	String ename;
	TIFFStandard standard;

	idf._idf_offset = in.tellg();
	//first we have to read the number of entries in the IDF
	in.read((char *)(&idf._number_of_idf_entries),2);

	//loop over all IDF entries
	for(i=0;i<idf._number_of_idf_entries;i++){
		//read some basic information required to decide which reader to use
		in.read((char*)(&tag),2);
		in.read((char*)(&ttype),2);
		in.read((char*)(&cnt),4);
		//in.read((char*)(&vo),4);
		ename = standard.getTagName(tag);

		//now we have to do something with the data

		//switch for the proper data type
		switch(ttype){
		case ENTRY_TYPE_BYTE:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(ByteEntry::sptr(new ByteEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<ByteEntry>(e);
			break;
		case ENTRY_TYPE_ASCII:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(
					ASCIIEntry::sptr(new ASCIIEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<ASCIIEntry>(e);
			//actually no Idea how to handle this - most probably as string
			break;
		case ENTRY_TYPE_SHORT:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(ShortEntry::sptr(new ShortEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<ShortEntry>(e);
			break;
		case ENTRY_TYPE_LONG:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(LongEntry::sptr(new LongEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<LongEntry>(e);
			break;
		case ENTRY_TYPE_RATIONAL:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(RationalEntry::sptr(new RationalEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<RationalEntry>(e);
			//here one could define a kind of Pair type
			break;
		case ENTRY_TYPE_SBYTE:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(SByteEntry::sptr(new SByteEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<SByteEntry>(e);
			break;
		case ENTRY_TYPE_UNDEFINED:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(ASCIIEntry::sptr(new ASCIIEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<ASCIIEntry>(e);
			//need something like void - differs in interpretation
			break;
		case ENTRY_TYPE_SSHORT:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(SShortEntry::sptr(new SShortEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<SShortEntry>(e);
			break;
		case ENTRY_TYPE_SLONG:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(SLongEntry::sptr(new SLongEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<SLongEntry>(e);
			break;
		case ENTRY_TYPE_SRATIONAL:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(SRationalEntry::sptr(new SRationalEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<SRationalEntry>(e);
			//like above - something like a Pair type can do the job
			break;
		case ENTRY_TYPE_FLOAT:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(FloatEntry::sptr(new FloatEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<FloatEntry>(e);
			break;
		case ENTRY_TYPE_DOUBLE:
			e = boost::dynamic_pointer_cast<IFDAbstractEntry>(DoubleEntry::sptr(new DoubleEntry(ename,cnt)));
			in>>*boost::dynamic_pointer_cast<DoubleEntry>(e);
			break;
		default:
			std::cerr<<"IDF entry has unknow type code - do not know what to do with it!";
		}

		idf._entry_list.push_back(e);

	}

	//the last entry should be the offset to the next IDF entry
	in.read((char*)(&idf._idf_next_offset),4);

	return in;
}



//end of namespace
}
}
