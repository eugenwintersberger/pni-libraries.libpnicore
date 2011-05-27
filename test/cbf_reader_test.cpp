/*
 * cbf_reader_test.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Testing program for the CBF reader

#include<iostream>
#include<typeinfo>

#include "../src/io/CBFReader.hpp"
#include "../src/DataObject.hpp"
#include "../src/Array.hpp"


int main(int argc,char **argv){
    pni::utils::CBFReader reader;
    pni::utils::DataObject *v = NULL;

    reader.setFileName("org_00009.cbf");
    reader.open();
    v = reader.read();
    reader.close();

    std::cout<<"finished with reading data"<<std::endl;
    std::cout<<typeid(*v).name()<<std::endl;

    if(typeid(*v).name()==typeid((pni::utils::Int32Array())).name()){
    	std::cout<<"this is an Int32Array()"<<std::endl;
    	pni::utils::Int32Array &a = *(pni::utils::Int32Array *)v;

    	std::cout<<a.Min()<<" "<<a.Max()<<std::endl;
    	std::cout<<a.Sum()<<std::endl;


    }else if(typeid(*v).name()==typeid((pni::utils::Int16Array())).name()){
    	std::cout<<"data is an Int16Array()"<<std::endl;
    	pni::utils::Int16Array &a = *(pni::utils::Int16Array *)v;

    	std::cout<<a.Min()<<" "<<a.Max()<<std::endl;
    	std::cout<<a.Sum()<<std::endl;
    }




    return 0;
}
