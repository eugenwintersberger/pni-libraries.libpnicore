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

//#include "../src/io/TIFFReader.hpp"
#include "../src/DataObject.hpp"
#include "../src/Array.hpp"
#include "../src/ArrayShape.hpp"
#include "../src/io/TIFFFile.hpp"
#include "../src/io/TIFFIFD.hpp"
#include "../src/io/TIFFImageData.hpp"

using namespace pni::utils;

template<typename T> class PlPlotArrayDecorator:public Contourable_Data{
private:
	typename Array<T>::sptr _array;
public:
	PlPlotArrayDecorator(){}
	PlPlotArrayDecorator(Array<T> *a);
	PlPlotArrayDecorator(const typename Array<T>::sptr &a);
	virtual ~PlPlotArrayDecorator(){
		_array.reset();
	}

	virtual PLFLT operator()(int i,int j) const{
		return (PLFLT)(*_array)(i,j);
	}
};

template<typename T> PlPlotArrayDecorator<T>::PlPlotArrayDecorator(Array<T> *a)
	:Contourable_Data(a->getShape().getDimension(0),
			          a->getShape().getDimension(1)){
	_array.reset(a);
}
template<typename T> PlPlotArrayDecorator<T>::PlPlotArrayDecorator(const typename Array<T>::sptr &a)
	:Contourable_Data(a->getShape().getDimension(0),
			          a->getShape().getDimension(1)){
	_array = a;
}


class PlotArray{
private:
	PLFLT **_image_buffer;
	size_t _nx;
	size_t _ny;
	int _ntot;
	PlotArray(const PlotArray &){}
	void _alloc_image_buffer();
	void _free_image_buffer();
public:
	PlotArray();
	PlotArray(int nx,int ny);
	PlotArray(const ArrayShape &s);
	virtual ~PlotArray();

	template<typename T> void image_plot(const ArrayObject::sptr data);
	template<typename T> void contour_plot(const ArrayObject *data){}
};

void PlotArray::_alloc_image_buffer(){
	_image_buffer = new PLFLT*[_nx];
	for(size_t i=0;i<_nx;i++){
		_image_buffer[i] = new PLFLT[_ny];
	}
}

void PlotArray::_free_image_buffer(){
	for(size_t i=0;i<_nx;i++) delete [] _image_buffer[i];
	delete [] _image_buffer;
}

PlotArray::PlotArray(){
	_nx = 0;
	_ny = 0;
	_ntot = 0;
	_image_buffer = NULL;
}

PlotArray::PlotArray(int nx,int ny){
	_nx = nx;
	_ny = ny;
	_ntot = _nx*_ny;

	_alloc_image_buffer();
}

PlotArray::PlotArray(const ArrayShape &s){
	_nx = s.dim(0);
	_ny = s.dim(1);
	_ntot = _nx*_ny;

	_alloc_image_buffer();

}

PlotArray::~PlotArray(){
	_free_image_buffer();
	_nx = 0;
	_ny = 0;
	_ntot = 0;
}


template<typename T> void PlotArray::image_plot(const pni::utils::ArrayObject::sptr data){
	pni::utils::Array<T> &a = *boost::dynamic_pointer_cast<pni::utils::Array<T> >(data);
	//PlPlotArrayDecorator<T> adec((pni::utils::Array<T> *)data);
	int i,j;

	int nx = a.shape().dim(0);
	int ny = a.shape().dim(1);

	plstream p(1,1,"xwin",NULL);
	p.init();
	p.env(0,nx,0,ny,0,0);
	p.lab("channels","channels","test plot");
	p.scmap1n(100);

	PLFLT zmin = a.Min();
	PLFLT zmax = a.Max();

	//copy data to image buffer
	Index index(2);

	for(index[0]=0;index[0]<_nx;index.inc(0)){
		for(index[1]=0;index[1]<_ny;index.inc(1)){
			_image_buffer[index[0]][index[1]] = (PLFLT)a(index);
		}
	}

	p.image(_image_buffer, nx, ny, 0, nx, 0, ny,zmin,zmax, 0, nx, 0,
			ny);

}


int main(int argc,char **argv){
    PlotArray *plotter;
    pni::utils::TIFFImageData::sptr idata;

    if(argc<2){
    	return 1;
    }

    pni::utils::TIFFFile f;
    //f.setFileName("water_00259.tif");
    f.setFileName(String(argv[1]));
    //f.setFileName("mscp03_au_sputter2_00057.tif");
    f.open();
    std::cout<<f<<std::endl;
    std::cout<<"read data"<<std::endl;
    idata = f.getData(0);
    std::cout<<"print image data"<<std::endl;
    pni::utils::ArrayObject::sptr a = idata->getChannel(0);
    f.close();


    std::cout<<*idata<<std::endl;
    std::cout<<*a<<std::endl;
    plotter = new PlotArray(a->shape());

    switch(a->type_id()){
    case PNITypeID::INT32:
    	plotter->image_plot<Int32>(a); break;
    case PNITypeID::UINT16:
    	plotter->image_plot<UInt16>(a); break;
    default:
    	std::cerr<<"Unsupported image format!"<<std::endl; break;
    }

    std::cout<<"finished with plotting!"<<std::endl;
	delete plotter;

    return 0;
}
