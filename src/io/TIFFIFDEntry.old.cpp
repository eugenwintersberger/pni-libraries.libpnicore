/*
 * Implementation of class TIFFIFDEntry
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
 * Implementation of class TIFFIFDEntry.
 *
 * Created on: Jun 20, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include <iostream>

#include "TIFFIFDEntry.hpp"

namespace pni{
namespace utils{

template<> std::ifstream &operator>>(std::ifstream &in,IFDEntry<URational> &e){
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

template<> std::ifstream &operator>>(std::ifstream &in,IFDEntry<SRational> &e){
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

template<> std::ifstream &operator>>(std::ifstream &in,IFDEntry<String> &e){
	char buffer;
	String s;
	UInt64 s_cnt=0;  //string counter
	Int32 vo;
	Int32 old_offset;
	//the frist thing we have to do is to check whether or not the Tag data fits into
	//the next 4 byte in the stream
	if (sizeof(char) * e._cnt > 4) {
		//data does not fit - interpret the 4 bytes as an offset
		in.read((char *) (&vo), 4);
		//safe the offset in the stream
		old_offset = in.tellg();

		in.seekg(vo, std::ios::beg);
		//read the data
		for (UInt64 i = 0; i < e._cnt; i++) {
			//read a character from the stream
			in.read((char *) (&buffer), sizeof(char));

			if(buffer=='\0'){
				e._values.push_back(s);
				s_cnt++;
				s.clear();
			}else{
				s += buffer;
			}
		}

		//reset the stream position
		in.seekg(old_offset, std::ios::beg);

	} else {
		//data fits
		for (UInt64 i = 0; i < e._cnt; i++) {
			//read a character from the stream
			in.read((char *) (&buffer), sizeof(char));

			if (buffer == '\0') {
				e._values.push_back(s);
				s_cnt++;
				s.clear();
			}else{
				s += buffer;
			}
		}
		//need to modify the stream position in cases where the
		//amount of data read from the stream is smaller than 4 Byte
		in.seekg((4 - (sizeof(char) * e._cnt)), std::ios::cur);

	}

	e._cnt = s_cnt;  //reset the counter - this should reflect now the number
	                 //of strings in the entry

	return in;
}

//end of namespace
}
}


