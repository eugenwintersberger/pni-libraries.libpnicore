/*
 * cbf_reader_test.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Testing program for the CBF reader

#include<iostream>
#include<typeinfo>
#include<cmath>

#include<plplot/plplot.h>
#include<plplot/plstream.h>

#include "../src/io/CBFReader.hpp"
#include "../src/Array.hpp"
#include "../src/Shape.hpp"

using namespace pni::utils;


int main(int argc,char **argv){

    if(argc<2){
        std::cerr<<"Usage: cbf_reader_test <filename>"<<std::endl;
        return -1;
    }

    //get the name of the file to copen
    String file_name(argv[1]);


    CBFReader reader(file_name);
    ImageInfo info = reader.info()[0];
    std::cout<<info<<std::endl;

    Float32Array array = reader.image<Float32Array>(0);

    return 0;
}
