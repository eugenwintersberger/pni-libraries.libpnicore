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
#include <complex>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

using namespace pni::core;
using namespace boost::spirit;

typedef std::complex<float64>    complex_type;
typedef std::vector<value>       record_type;
typedef std::vector<record_type> table_type;

//----------------------------------------------------------------------------
// complex number praser
//----------------------------------------------------------------------------
template<typename ITERT>
struct complex_parser : public qi::grammar<ITERT,complex_type()>
{
    qi::rule<ITERT,complex_type()> complex_rule;

    complex_parser() : complex_parser::base_type(complex_rule)
    {
        using namespace boost::fusion;
        using namespace boost::phoenix;
        using qi::_1;
        using qi::_2;
        using qi::double_;
        
        complex_rule = ('('>>double_>>','>>double_>>')')
                        [_val = construct<complex_type>(_1,_2)];
    }
};

//----------------------------------------------------------------------------
// parse a single value
//----------------------------------------------------------------------------
template<typename ITERT>
struct value_parser : public qi::grammar<ITERT,pni::core::value()>
{
    qi::rule<ITERT,pni::core::value()> value_rule;

    complex_parser<ITERT> complex_;

    value_parser() : value_parser::base_type(value_rule)
    {
        using qi::_1;
        using qi::char_;
        using qi::int_;
        using qi::double_;
        using qi::_val;

        value_rule = (
                     (int_ >> !(char_('.')|char_('e')))[_val = _1]
                     || 
                     double_[_val = _1]
                     ||
                     complex_[_val = _1]
                     );
    }
};

//----------------------------------------------------------------------------
// parse an entire record
//----------------------------------------------------------------------------
template<typename ITERT>
struct record_parser : public qi::grammar<ITERT,record_type()>
{
    qi::rule<ITERT,record_type()> record_rule;

    value_parser<ITERT> value_;

    record_parser() : record_parser::base_type(record_rule)
    {
        using qi::blank;

        record_rule = value_ % (*blank);
    }
};

//-----------------------------------------------------------------------------
// read a single record from the stream
//-----------------------------------------------------------------------------
record_type parse_record(const string &line)
{
    typedef string::const_iterator iterator_type;
    typedef record_parser<iterator_type> parser_type;

    parser_type parser;
    record_type record;

    qi::parse(line.begin(),line.end(),parser,record);

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
            table.push_back(parse_record(line));
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
