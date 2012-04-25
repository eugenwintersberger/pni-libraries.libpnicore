/*
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
 * DectrisCBFReader class definition
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __DECTRISCBFREADER_HPP__
#define __DECTRISCBFREADER_HPP__

#include<iostream>
#include<fstream>
#include<vector>

#include "../../Array.hpp"
#include "../ImageInfo.hpp"
#include "CBFTypes.hpp"

using namespace pni::utils;

namespace pni{
namespace io{

    class DectrisCBFReader
    {
        public:
            static std::streampos read_header(std::ifstream &is,
                    std::vector<ImageInfo> &info,CBFCompressionType &ct);

            template<typename CBFT,typename T,template<typename> class BT>
                static void read_data_byte_offset(
                        std::ifstream &is,
                        const ImageInfo &info,
                        Array<T,BT> &array);


    };

    template<typename CBFT,typename T,template<typename> class BT>
        void DectrisCBFReader::read_data_byte_offset( std::ifstream &is,
                const ImageInfo &info, Array<T,BT> &array)
    {

        //unsigned long i;
        size_t ecnt = 0; // element counter
        CBFT buffer = 0;

        array = 0;

        //std::cout << "start with reading binary data ..." << std::endl;
        while ((!is.eof()) && (ecnt != info.npixels())) {

            is.read((char *) (&buffer), 1);
            if (((unsigned char) buffer) != 0x80){
                //this byte is a valid offset
                array[ecnt] += (char) buffer;
                //now we have to increment the element counter
                ecnt++;
                if (ecnt >= info.npixels()) break;
                array[ecnt] = array[ecnt - 1];
                //reset the buffer so that all bits are set to 0
                buffer = 0;
                continue;
            }

            is.read((char *) (&buffer), 2);
            if (((unsigned short) buffer) != 0x8000) {
                array[ecnt] += (short) buffer;
                //increase the element counter
                ecnt++;
                if (ecnt >= info.npixels()) break;
                array[ecnt] = array[ecnt - 1];
                //reset the buffer so that all bits are set to 0
                buffer = 0;
                continue;
            }

            is.read((char*) (&buffer), 4);
            if (((unsigned int) buffer) != 0x800000) {
                array[ecnt] += (int) buffer;
                //increase the element counter
                ecnt++;
                if (ecnt >= info.npixels()) break;
                array[ecnt] = array[ecnt - 1];
                buffer = 0;
                continue;
            }

        }

    }

//end of namespace
}
}

#endif
