

#include "../src/Types.hpp"
#include "../src/Array.hpp"
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkFloatArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkImageViewer2.h>
#include <vtkDataArrayTemplate.h>

#ifndef __VTKPLOT_HPP__
#define __VTKPLOT_HPP__

using namespace pni::utils;


template<typename T,template<typename> class BT> void plot_image(const Array<T,BT> &array)
{
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *window = vtkRenderWindow::New();
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
    vtkImageViewer2 *viewer = vtkImageViewer2::New();

    vtkDataArrayTemplate<T> *ia = vtkDataArrayTemplate<T>::New();
    ia->SetArray((T *)array.ptr(),array.size(),1);
    vtkImageData *idata = vtkImageData::New();
    idata->GetPointData()->SetScalars(ia);
    idata->SetDimensions(array.shape()[0],array.shape()[1],1);
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


#endif
