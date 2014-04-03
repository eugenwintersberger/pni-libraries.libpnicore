//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
// Created on: Apr 2, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>

using namespace pni::core;

typedef std::vector<value>       record_type;
typedef std::vector<record_type> table_type;

//-----------------------------------------------------------------------------
// read a single record from the stream
//-----------------------------------------------------------------------------
record_type read_record(std::istream &&stream)
{
    record_type record;
    int32 int_data;
    float64 float_data;
    complex32 cmplx_data;

    stream>>int_data>>float_data>>cmplx_data;
    record.push_back(value(int_data));
    record.push_back(value(float_data));
    record.push_back(value(cmplx_data));

    return record;
}

//-----------------------------------------------------------------------------
// read an entire table from a stream
//-----------------------------------------------------------------------------
table_type read_table(std::istream &stream)
{
    table_type table;
    string line;

    while(!stream.eof())
    {
        std::getline(stream,line);
        if(!line.empty())
            table.push_back(read_record(std::stringstream(line)));
    }

    return table;
}

//-----------------------------------------------------------------------------
// write a single record to the output stream
//-----------------------------------------------------------------------------
void write_record(std::ostream &stream,const record_type &r)
{
    for(auto v: r) stream<<v<<"\t";
    stream<<std::endl; //terminate the output with a newline
}

//-----------------------------------------------------------------------------
// write the entire table to the output stream
//-----------------------------------------------------------------------------
void write_table(std::ostream &stream,const table_type &table)
{
    for(auto r: table) write_record(stream,r);
}


//-----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    std::ifstream stream("record.dat");

    table_type table = read_table(stream);

    //check the different data types
    auto record = table.front();
    for(auto entry: record) std::cout<<type_id(entry)<<std::endl;

    write_table(std::cout,table);

    return 0;
}
