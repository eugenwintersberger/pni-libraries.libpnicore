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

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkFloatArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkImageViewer2.h>

#include <pni/utils/io/CBFReader.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Shape.hpp>

using namespace pni::utils;
using namespace pni::io;


void plot_image(const Float32Array &array)
{
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *window = vtkRenderWindow::New();
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
    vtkImageViewer2 *viewer = vtkImageViewer2::New();

    vtkFloatArray *ia = vtkFloatArray::New();
    ia->SetArray((float *)array.ptr(),array.size(),1);
    vtkImageData *idata = vtkImageData::New();
    idata->GetPointData()->SetScalars(ia);
    idata->SetDimensions(array.shape()[1],array.shape()[0],1);
    idata->SetScalarType(VTK_FLOAT);
    idata->SetSpacing(1.0,1.0,1.0);
    idata->SetOrigin(0,0,0);

    viewer->SetInput(idata);
    viewer->SetZSlice(0);
    viewer->SetupInteractor(interactor);
    viewer->Render();
    interactor->Start();

    //cleanup everything
    renderer->Delete();
    window->Delete();
    interactor->Delete();

}

int main(int argc,char **argv){

    if(argc<2){
        std::cerr<<"Usage: cbf_reader_test <filename>"<<std::endl;
        return -1;
    }

    //get the name of the file to copen
    String file_name(argv[1]);


    CBFReader reader(file_name);
    ImageInfo info = reader.info(0);
    std::cout<<info<<std::endl;

    Float32Array array = reader.image<Float32Array>(0);
    plot_image(array);

    reader.close();

    return 0;
}
