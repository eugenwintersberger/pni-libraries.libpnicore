/*
 * bmark.cpp
 * a small benchmark for numerical operations
 *  Created on: Sep 12, 2011
 *      Author: Eugen Wintersberger
 */


#include <pni/utils/Types.hpp>
#include <pni/utils/Scalar.hpp>
#include <cstdio>
#include <ctime>

using namespace pni::utils;

void BinaryScalarOperations(UInt64 nruns){
	//test binary operations of simple data types
	clock_t start,stop;
	Float64 etime;

	Int32 ai32,bi32,ci32;
	Int32Scalar sai32,sbi32,sci32;
	ai32 = 100; bi32 = 1294021;

	start = clock();
	for(UInt64 i=0;i<nruns;i++) ci32 = ai32 + bi32;
	stop = clock();
	etime = ((double)(stop-start))/CLOCKS_PER_SEC;
	std::cout<<"Int32 = Int32 + Int32: "<<etime<<" (sec.)"<<std::endl;

	sai32 = ai32; sbi32 = bi32;
	start = clock();
	for(UInt64 i=0;i<nruns;i++) sci32 = sai32 + sbi32;
	stop = clock();
	etime = ((double)(stop-start))/CLOCKS_PER_SEC;
	std::cout<<"Int32Scalar = Int32Scalar + Int32Scalar: "<<etime<<" (sec.)"<<std::endl;

	Float64 ai64,bi64,ci64;
	Float64Scalar sai64,sbi64,sci64;

	ai64 = 1324.1909433; bi64 = -12239.2098;
	start = clock();
	for(UInt64 i=0; i<nruns;i++) ci64 = ai64 + bi64;
	stop = clock();
	etime = ((double)(stop-start))/CLOCKS_PER_SEC;
	std::cout<<"Float64 = Float64 + Float64: "<<etime<<" (sec.)"<<std::endl;

	sai64 = ai64; sbi64 = bi64;
	start = clock();
	for(UInt64 i=0; i<nruns;i++) sci64 = sai64 + sbi64;
	stop = clock();
	etime = ((double)(stop-start))/CLOCKS_PER_SEC;
	std::cout<<"Float64Scalar = Float64Scalar + Float64Scalar: "<<etime<<" (sec.)"<<std::endl;
}

int main(int argc,char **argv){
	UInt64 nruns;

	if(argc < 2){
		std::cerr<<"you must pass the number of runs as a command line argument!"<<std::endl;
		std::cerr<<"Using default value"<<std::endl;
		nruns = 100000000;
	}else{
		nruns = (UInt64)std::atoi(argv[1]);
	}



	BinaryScalarOperations(nruns);


	return 0;
}





