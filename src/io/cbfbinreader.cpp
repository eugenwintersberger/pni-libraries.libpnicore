/*
 * cbfbinreader.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Implementation of class CBFBinReader

#include "cbf.hpp"


CBFBinReader::CBFBinReader(){
	nelements_ = 0;
	elemsize_ = 0;
}

CBFBinReader::CBFBinReader(const CBFBinReader &r){
	nelements_ = r.nelements_;
	elemsize_ = r.elemsize_;
}

CBFBinReader::CBFBinReader(unsigned long n){
	nelements_ = n;
	elemsize_ = 0;
}

CBFBinReader::~CBFBinReader(){
	nelements_ = 0;
	elemsize_ = 0;
}

