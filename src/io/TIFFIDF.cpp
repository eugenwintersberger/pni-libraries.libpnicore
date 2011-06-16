/*
 * TIFFIDF.cpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */


#include "TIFFIDF.hpp"
#include "TIFFIDFEntry.hpp"

namespace pni{
namespace utils{


TIFFIDF::TIFFIDF() {
	_idf_offset = 0;
	_idf_next_offset = 0;
	_number_of_idf_entries = 0;
}

TIFFIDF::TIFFIDF(const TIFFIDF &idf){
	_idf_offset = idf._idf_offset;
	_idf_next_offset = idf._idf_next_offset;
	_number_of_idf_entries = idf._number_of_idf_entries;
}

TIFFIDF::~TIFFIDF() {

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

std::ostream &operator<<(std::ostream &o,const TIFFIDF &idf){
	o<<"IDF at offset "<<idf._idf_offset<<" with "<<idf._number_of_idf_entries<<" entries"<<std::endl;

	return o;
}

std::ifstream &operator>>(std::ifstream &in,TIFFIDF &idf){
	UInt64 i;

	idf._idf_offset = in.tellg();
	//first we have to read the number of entries in the IDF
	in.read((char *)(&idf._number_of_idf_entries),2);

	//loop over all IDF entries
	for(i=0;i<idf._number_of_idf_entries;i++){
		UInt16 tag,ttype;
		UInt32 cnt,vo;
		IDFAbstractEntry *e;

		in.read((char*)(&tag),2);
		in.read((char*)(&ttype),2);
		in.read((char*)(&cnt),4);
		in.read((char*)(&vo),4);

		//now we have to do something with the data

		//switch for the proper data type
		switch(ttype){
		case ENTRY_TYPE_BYTE:
			e = (IDFAbstractEntry *)(new IDFEntry<UInt8>(ename,cnt));
			in>>*(IDFEntry<UInt8> *)e;
			break;
		case ENTRY_TYPE_ASCII:
			//actually no Idea how to handle this - most probably as string
			break;
		case ENTRY_TYPE_SHORT:
			e = (IDFAbstractEntry *)(new IDFEntry<UInt16>(ename,cnt));
			in>>*(IDFEntry<UInt16>)e;
			break;
		case ENTRY_TYPE_LONG:
			IDFEntry<UInt32> *e = new IDFEntry<UInt32>(ename,cnt);
			in>>*e;
			break;
		case ENTRY_TYPE_RATIONAL:
			//here one could define a kind of Pair type
			break;
		case ENTRY_TYPE_SBYTE:
			IDFEntry<Int8> *e = new IDFEntry<Int8>(ename,cnt);
			in>>*e;
			break;
		case ENTRY_TYPE_UNDEFINED:
			//need something like void - differs in interpretation
			break;
		case ENTRY_TYPE_SSHORT:
			IDFEntry<Int16> *e = new IDFEntry<Int16>(ename,cnt);
			in>>*e;
			break;
		case ENTRY_TYPE_SLONG:
			IDFEntry<Int32> *e = new IDFEntry<Int32>(ename,cnt);
			in>>*e;
			break;
		case ENTRY_TYPE_SRATIONAL:
			//like above - something like a Pair type can do the job
			break;
		case ENTRY_TYPE_FLOAT:
			IDFEntry<Float32> *e = new IDFEntry<Float32>(ename,cnt);
			in>>*e;
			break;
		case ENTRY_TYPE_DOUBLE:
			IDFEntr<Float64> *e = new IDFEntry<Float64>(ename,cnt);
			in>>*e;
			break
		default:
			std::cerr<<"IDF entry has unknow type code - do not know what to do with it!"
		}

	}


	//the last entry should be the offset to the next IDF entry
	in.read((char*)(&idf._idf_next_offset),4);

	return in;
}

//end of namespace
}
}
