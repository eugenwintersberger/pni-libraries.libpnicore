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

#include "../src/io/TIFFReader.hpp"

using namespace pni::utils;
using namespace pni::io;


int main(int argc,char **argv){

    if(argc<2){
        std::cerr<<"usage: tif_reader_test <filename>"<<std::endl;
    	return -1;
    }

    //open file for reading
    String filename(argv[1]);
    TIFFReader reader(filename);

    std::cout<<"number of images: "<<reader.nimages()<<std::endl;
    std::cout<<reader<<std::endl;
    std::cout<<reader.info(0)<<std::endl;
    
    

    //close the reader object when we are done

    return 0;
}
