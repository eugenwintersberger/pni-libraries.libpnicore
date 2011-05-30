/*
 * cbf_reader_test.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Testing program for the CBF reader

#include<iostream>
#include<typeinfo>

#include<plplot/plplot.h>
#include<plplot/plstream.h>

#include "../src/io/CBFReader.hpp"
#include "../src/DataObject.hpp"
#include "../src/Array.hpp"
#include "../src/ArrayShape.hpp"

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
		return (PLFLT)_array(i,j);
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
	void __alloc_image_buffer();
	void __free_image_buffer();
public:
	PlotArray(){}
	PlotArray(int nx,int ny);
	PlotArray(const pni::utils::ArrayShape *s);
	PlotArray(const pni::utils::ArrayShape::sptr &s);
	virtual ~PlotArray(){}

	template<typename T> void image_plot(const pni::utils::ArrayObject *data);
};

PlotArray::PlotArray(){
	_nx = 0;
	_ny = 0;
	_ntot = 0;
	_image_buffer = NULL;
}


template<typename T> void PlotArray::image_plot(const pni::utils::ArrayObject *data){
	pni::utils::Array<T> &a = *(pni::utils::Array<T> *)data;
	PlPlotArrayDecorator<T> adec((pni::utils::Array<T> *)data);

	int nx = a.getShape()->getDimension(0);
	int ny = a.getShape()->getDimension(1);

	plstream p(1,1,"xwin",NULL);
	p.init();
	p.env(0,nx,0,ny,0,0);
	p.lab("channels","channels","test plot");
	p.scmap1n(100);

	PLFLT zmin = a.Min();
	PLFLT zmax = a.Max();

	p.image(_image_buffer, nx, ny, 0, nx, 0, ny,zmin,zmax, 0, nx, 0,
			ny);

}


int main(int argc,char **argv){
    pni::utils::CBFReader reader;
    pni::utils::DataObject *v = NULL;
    PlotArray *plotter;

    reader.setFileName("org_00009.cbf");
    reader.open();
    v = reader.read();
    reader.close();

    std::cout<<"finished with reading data"<<std::endl;
    std::cout<<typeid(*v).name()<<std::endl;

    if(typeid(*v).name()==typeid((pni::utils::Int32Array())).name()){
    	std::cout<<"this is an Int32Array()"<<std::endl;
    	pni::utils::Int32Array *a = (pni::utils::Int32Array *)v;

    	std::cout<<a->Min()<<" "<<a->Max()<<std::endl;
    	std::cout<<a->Sum()<<std::endl;

    	plotter = new PlotArray();
    	plotter->plot<int>(a);


    }else if(typeid(*v).name()==typeid((pni::utils::Int16Array())).name()){
    	std::cout<<"data is an Int16Array()"<<std::endl;
    	pni::utils::Int16Array &a = *(pni::utils::Int16Array *)v;

    	std::cout<<a.Min()<<" "<<a.Max()<<std::endl;
    	std::cout<<a.Sum()<<std::endl;
    }






    return 0;
}
