/*
 * cbf_reader_test.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Testing program for the CBF reader

#include<iostream>

#include "../src/io/cbf.hpp"


int main(int argc,char **argv){
    CBFReader reader;

    reader.setFileName("org_00009.cbf");
    reader.read();


    return 0;
}
