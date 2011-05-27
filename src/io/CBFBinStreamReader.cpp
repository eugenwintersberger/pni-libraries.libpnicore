/*
 * cbfbinreader.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Implementation of class CBFBinReader

#include "CBFBinStreamReader.hpp"

namespace pni{
namespace utils{


CBFBinStreamReader::CBFBinStreamReader(){
	nelements_ = 0;
	elemsize_ = 0;
	_stream = NULL;
}

CBFBinStreamReader::CBFBinStreamReader(const CBFBinStreamReader &r){
	nelements_ = r.nelements_;
	elemsize_ = r.elemsize_;
	_stream = r._stream;
}

CBFBinStreamReader::CBFBinStreamReader(unsigned long n){
	nelements_ = n;
	elemsize_ = 0;
	_stream = NULL;
}

CBFBinStreamReader::~CBFBinStreamReader(){
	nelements_ = 0;
	elemsize_ = 0;
	_stream = NULL;
}

//end of namespaces
}
}
