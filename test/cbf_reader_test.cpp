/*
 * cbf_reader_test.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Testing program for the CBF reader

#include<iostream>
#include<typeinfo>

#include "../src/io/cbfreader.hpp"
#include "../src/array.hpp"


int main(int argc,char **argv){
    CBFReader reader;
    DataValue *v = NULL;

    reader.setFileName("org_00009.cbf");
    v = reader.read();


    if(typeid(*v).name()==typeid((Int32Array())).name()){
    	std::cout<<"this is an Int32Array()"<<std::endl;
    	Int32Array &a = *(Int32Array *)v;


    }else if(typeid(*v).name()==typeid((Int16Array())).name()){
    	Int16Array &a = *(Int16Array *)v;
    }



    return 0;
}
