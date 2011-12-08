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
#include "../src/DataObject.hpp"
#include "../src/Array.hpp"
#include "../src/ArrayShape.hpp"
#include "../src/Index.hpp"

using namespace pni::utils;

template<typename T> class PlPlotArrayDecorator:public Contourable_Data{
private:
	Array<T> *_array;
	Index _index;
public:
	PlPlotArrayDecorator(){}
	PlPlotArrayDecorator(Array<T> *a);
	virtual ~PlPlotArrayDecorator(){
		_array = NULL;
	}

	virtual PLFLT operator()(int i,int j) const{
		Index index(2);
		index[0] = i;
		index[1] = j;
		return (PLFLT)(*_array)(index);
	}
};

template<typename T> PlPlotArrayDecorator<T>::PlPlotArrayDecorator(Array<T> *a)
	:Contourable_Data(a->shape().dim(0),
			          a->shape().dim(1)){
	_array = a;
	_index.rank(a->shape().rank());
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

	template<typename T> void image_plot(const ArrayObject *data);
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


template<typename T> void PlotArray::image_plot(const ArrayObject *data){
	pni::utils::Array<T> &a = *(Array<T> *)data;
	PlPlotArrayDecorator<T> adec((Array<T> *)data);
	Index index(2);

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
	for(index[0]=0;index[0]<_nx;index.inc(0)){
		for(index[1]=0;index[1]<_ny;index.inc(1)){
			_image_buffer[index[0]][index[1]] = std::log10(a(index));
		}
	}

	p.image(_image_buffer, nx, ny, 0, nx, 0, ny,zmin,zmax, 0, nx, 0,
			ny);

}




int main(int argc,char **argv){
    CBFReader reader;     //the reader object
    ArrayObject::sptr v ;  //shared pointer to a data object (most general object to represent data)
    PlotArray *plotter;
    ArrayShape shape; //shared pointer to an ArrayShape object

    //reader.setFileName("LAOS3_05461.cbf"); //set the name of the file to read
    reader.setFileName("org_00009.cbf");
    reader.open();                         //open the file
    v = boost::dynamic_pointer_cast<ArrayObject>(reader.read());                     //read data
    reader.close();                        //close the file

    std::cout<<"finished with reading data"<<std::endl;

    //DataObject is an extremely general object - however, in reality the data we have
    //obtained is at least of type ArrayObject. Now we need to find out what type of
    //array the data is. Since DataObject provides actually no facility to obtain
    //the type code of the data stored we have to do a little pointer casting
    //to ArrayObject.
    PNITypeID dtid = v->type_id();

    //ArrayObject is the base class for all numeric arrays which are implemented as
    //templates Array<T>. Each of these templates consists of a shared pointer to a
    //Buffer<T> object representing the data in memory and an ArrayShape object
    //describing the geometry of the array. While Buffer<T> depends on the
    //concrete data type is appears only in the Array<T> template. The ArrayShape
    //object is independent of the data type and is held by the base class ArrayObject.
    //So in cases where we need some geometry information we have to obtain the
    //shape object with

    shape = v->shape();
    //the number of dimensions can be obtained with
    std::cout<<shape.rank()<<std::endl;
    //The number of elements along each dimension with the getDimension(...) method
    //described below
    for(size_t i = 0; i<shape.rank();i++){
    	std::cout<<shape.dim(i)<<std::endl;
    }

    //finally we need to access the data

    if(dtid == PNITypeID::INT32){
    	//For Int32 data convert the ArrayObject ot an Int32 Array type
    	Int32Array::sptr a = boost::dynamic_pointer_cast<Int32Array>(v);

    	//call some array methods just to see if they work
    	std::cout<<a->Min()<<" "<<a->Max()<<std::endl;
    	std::cout<<a->Sum()<<std::endl;

    	//to access the raw pointer from an array use
    	//void *ptr = a->getBuffer()->getVoidPtr();

    	std::cout<<(a->shape())<<std::endl;
    	plotter = new PlotArray(a->shape());
    	plotter->image_plot<int>(a.get());
    	std::cout<<"finished with plotting!"<<std::endl;


    }else if(dtid == PNITypeID::INT16){
    	std::cout<<"data is an Int16Array()"<<std::endl;
    	Int16Array::sptr a = boost::dynamic_pointer_cast<Int16Array>(v);

    	std::cout<<a->Min()<<" "<<a->Max()<<std::endl;
    	std::cout<<a->Sum()<<std::endl;
    }






    return 0;
}
