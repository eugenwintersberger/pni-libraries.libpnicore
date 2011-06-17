/*
 * TIFFIDF.cpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */


#include "TIFFIDF.hpp"
#include "TIFFIDFEntry.hpp"
#include "TIFFStandard.hpp"
#include "TIFFIDFAbstractEntry.hpp"

namespace pni{
namespace utils{


TIFFIDF::TIFFIDF() {
	_idf_offset = 0;
	_idf_next_offset = 0;
	_number_of_idf_entries = 0;
	_entry_list.clear();
}

TIFFIDF::TIFFIDF(const TIFFIDF &idf){
	_idf_offset = idf._idf_offset;
	_idf_next_offset = idf._idf_next_offset;
	_number_of_idf_entries = idf._number_of_idf_entries;
}

TIFFIDF::~TIFFIDF() {
	//free all memory that has been allocated by the entry list
	for (_iterator iter=_entry_list.begin();iter!=_entry_list.end();iter++){
		delete *iter;
	}
}

bool TIFFIDF::isLastIDF() const {
	if(_idf_next_offset==0) return true;

	return false;
}

Int32 TIFFIDF::getNextOffset() const{
	return _idf_next_offset;
}

Int32 TIFFIDF::getOffset() const {
	return _idf_offset;
}

void TIFFIDF::setOffset(const Int32 &o){
	_idf_offset = o;
}

IDFAbstractEntry *TIFFIDF::operator[](const UInt16 i){
	return _entry_list[i];
}

IDFAbstractEntry *TIFFIDF::operator[](const String &n){
	for(_const_iterator iter = _entry_list.begin(); iter != _entry_list.end();iter++ ){
		IDFAbstractEntry *e = *iter;
		if(e->getName()==n){
			return e;
		}
	}
	return NULL;
}

std::ostream &operator<<(std::ostream &o,const TIFFIDF &idf){
	o<<"IDF at offset "<<idf._idf_offset<<" with "<<idf._number_of_idf_entries<<" entries"<<std::endl;

	for(TIFFIDF::_const_iterator iter = idf._entry_list.begin();iter!=idf._entry_list.end();iter++){
		IDFAbstractEntry *e = *iter;

		switch(e->getEntryTypeCode()){
		case IDFE_BYTE:
			o<<*(ByteEntry *)(e)<<std::endl; break;
		case IDFE_SHORT:
			o<<*(ShortEntry *)(e)<<std::endl; break;
		case IDFE_LONG:
			o<<*(LongEntry *)(e)<<std::endl; break;
		case IDFE_SBYTE:
			o<<*(SByteEntry *)(e)<<std::endl; break;
		case IDFE_SSHORT:
			o<<*(SShortEntry *)(e)<<std::endl; break;
		case IDFE_SLONG:
			o<<*(SLongEntry *)(e)<<std::endl; break;
		case IDFE_FLOAT:
			o<<*(FloatEntry *)(e)<<std::endl; break;
		case IDFE_DOUBLE:
			o<<*(DoubleEntry *)(e)<<std::endl; break;
		default:
			o<<*e<<std::endl;

		};
	}

	return o;
}

std::ifstream &operator>>(std::ifstream &in,TIFFIDF &idf){
	UInt64 i;
	UInt16 tag,ttype;
	UInt32 cnt,vo;
	IDFAbstractEntry *e;
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
			e = new ByteEntry(ename,cnt);
			in>>*(ByteEntry *)e;
			break;
		case ENTRY_TYPE_ASCII:
			in.read((char*)(&vo),4);
			//actually no Idea how to handle this - most probably as string
			break;
		case ENTRY_TYPE_SHORT:
			e = new ShortEntry(ename,cnt);
			in>>*(ShortEntry *)e;
			break;
		case ENTRY_TYPE_LONG:
			e = new LongEntry(ename,cnt);
			in>>*(LongEntry *)e;
			break;
		case ENTRY_TYPE_RATIONAL:
			e = new RationalEntry(ename,cnt);
			in>>*(RationalEntry *)e;
			//here one could define a kind of Pair type
			break;
		case ENTRY_TYPE_SBYTE:
			e = new SByteEntry(ename,cnt);
			in>>*(SByteEntry *)e;
			break;
		case ENTRY_TYPE_UNDEFINED:
			in.read((char*)(&vo),4);
			//need something like void - differs in interpretation
			break;
		case ENTRY_TYPE_SSHORT:
			e = new SShortEntry(ename,cnt);
			in>>*(SShortEntry *)e;
			break;
		case ENTRY_TYPE_SLONG:
			e = new SLongEntry(ename,cnt);
			in>>*(SLongEntry *)e;
			break;
		case ENTRY_TYPE_SRATIONAL:
			e = new SRationalEntry(ename,cnt);
			in>>*(SRationalEntry *)e;
			//like above - something like a Pair type can do the job
			break;
		case ENTRY_TYPE_FLOAT:
			e = new FloatEntry(ename,cnt);
			in>>*(FloatEntry *)e;
			break;
		case ENTRY_TYPE_DOUBLE:
			e = new DoubleEntry(ename,cnt);
			in>>*(DoubleEntry *)e;
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
