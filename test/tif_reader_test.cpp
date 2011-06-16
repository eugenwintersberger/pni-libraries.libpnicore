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

#include "../src/io/TIFFReader.hpp"
#include "../src/DataObject.hpp"
#include "../src/Array.hpp"
#include "../src/ArrayShape.hpp"
#include "../src/io/TIFFFile.hpp"

template<typename T> class PlPlotArrayDecorator:public Contourable_Data{
private:
	typename pni::utils::Array<T>::sptr _array;
public:
	PlPlotArrayDecorator(){}
	PlPlotArrayDecorator(pni::utils::Array<T> *a);
	PlPlotArrayDecorator(const typename pni::utils::Array<T>::sptr &a);
	virtual ~PlPlotArrayDecorator(){
		_array.reset();
	}

	virtual PLFLT operator()(int i,int j) const{
		return (PLFLT)(*_array)(i,j);
	}
};

template<typename T> PlPlotArrayDecorator<T>::PlPlotArrayDecorator(pni::utils::Array<T> *a)
	:Contourable_Data(a->getShape()->getDimension(0),
			          a->getShape()->getDimension(1)){
	_array.reset(a);
}
template<typename T> PlPlotArrayDecorator<T>::PlPlotArrayDecorator(const typename pni::utils::Array<T>::sptr &a)
	:Contourable_Data(a->getShape()->getDimension(0),
			          a->getShape()->getDimension(1)){
	_array = a;
}


class PlotArray{
private:
	PLFLT **_image_buffer;
	int _nx;
	int _ny;
	int _ntot;
	PlotArray(const PlotArray &){}
	void _alloc_image_buffer();
	void _free_image_buffer();
public:
	PlotArray();
	PlotArray(int nx,int ny);
	PlotArray(const pni::utils::ArrayShape *s);
	PlotArray(const pni::utils::ArrayShape::sptr &s);
	virtual ~PlotArray();

	template<typename T> void image_plot(const pni::utils::ArrayObject *data);
	template<typename T> void contour_plot(const pni::utils::ArrayObject *data){}
};

void PlotArray::_alloc_image_buffer(){
	int i;

	_image_buffer = new PLFLT*[_nx];
	for(i=0;i<_nx;i++){
		_image_buffer[i] = new PLFLT[_ny];
	}
}

void PlotArray::_free_image_buffer(){
	int i;

	for(i=0;i<_nx;i++) delete [] _image_buffer[i];
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

PlotArray::PlotArray(const pni::utils::ArrayShape *s){
	_nx = s->getDimension(0);
	_ny = s->getDimension(1);
	_ntot = _nx*_ny;

	_alloc_image_buffer();

}

PlotArray::PlotArray(const pni::utils::ArrayShape::sptr &s){
	_nx = s->getDimension(0);
	_ny = s->getDimension(1);
	_ntot = _nx*_ny;

	_alloc_image_buffer();
}

PlotArray::~PlotArray(){
	_free_image_buffer();
	_nx = 0;
	_ny = 0;
	_ntot = 0;
}


template<typename T> void PlotArray::image_plot(const pni::utils::ArrayObject *data){
	pni::utils::Array<T> &a = *(pni::utils::Array<T> *)data;
	PlPlotArrayDecorator<T> adec((pni::utils::Array<T> *)data);
	int i,j;

	int nx = a.getShape()->getDimension(0);
	int ny = a.getShape()->getDimension(1);

	plstream p(1,1,"xwin",NULL);
	p.init();
	p.env(0,nx,0,ny,0,0);
	p.lab("channels","channels","test plot");
	p.scmap1n(100);

	PLFLT zmin = a.Min();
	PLFLT zmax = a.Max();

	//copy data to image buffer
	for(i=0;i<_nx;i++){
		for(j=0;j<_ny;j++){
			_image_buffer[i][j] = (PLFLT)a(i,j);
		}
	}

	p.image(_image_buffer, nx, ny, 0, nx, 0, ny,zmin,zmax, 0, nx, 0,
			ny);

}


int main(int argc,char **argv){
    pni::utils::TIFFReader reader;
    pni::utils::DataObject *v = NULL;
    PlotArray *plotter;

    pni::utils::TIFFFile f;
    f.setFileName("water_00259.tif");
    f.open();
    std::cout<<f;
    f.close();
    return 0;

    //reader.setFileName("test_data/pr531_100k_1_1_0256.cbf");
    reader.setFileName("mscp03_au_sputter2_00057.tif");
    reader.open();
    v = reader.read();
    reader.close();

    std::cout<<"finished with reading data"<<std::endl;
    std::cout<<typeid(*v).name()<<std::endl;

   	pni::utils::UInt32Array *a = (pni::utils::UInt32Array *)v;

	std::cout << a->Min() << " " << a->Max() << std::endl;
	std::cout << a->Sum() << std::endl;

	std::cout << *(a->getShape()) << std::endl;
	plotter = new PlotArray(a->getShape());
	plotter->image_plot<pni::utils::UInt32> (a);
	std::cout<<"finished with plotting!"<<std::endl;



    return 0;
}
