//Author: Chung Kai Lun Peter
#include <vtkSmartPointer.h>
#include <vtkAppendFilter.h>
#include <vtkCellArray.h>
#include <vtkConeSource.h>
#include <vtkContourFilter.h>
#include <vtkCubeSource.h>
#include <vtkDataSetMapper.h>
#include <vtkImplicitModeller.h>
#include <vtkLODActor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRotationalExtrusionFilter.h>
#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkWarpTo.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkArrowSource.h>

int main(int, char*[])
{
  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> ren1 = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  vtkSmartPointer<vtkRenderWindowInteractor> iren = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);


  // Draw the arrows
  vtkSmartPointer<vtkPolyData> pd = 
    vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkCellArray> ca = 
    vtkSmartPointer<vtkCellArray>::New();
  vtkSmartPointer<vtkPoints> fp = 
    vtkSmartPointer<vtkPoints>::New();
  fp->InsertNextPoint(0, 1, 0);
  fp->InsertNextPoint(8, 1, 0);
  fp->InsertNextPoint(8, 2, 0);
  fp->InsertNextPoint(10, 0.01, 0);
  fp->InsertNextPoint(8, -2, 0);
  fp->InsertNextPoint(8, -1, 0);
  fp->InsertNextPoint(0, -1, 0);
  ca->InsertNextCell(7);
  ca->InsertCellPoint(0);
  ca->InsertCellPoint(1);
  ca->InsertCellPoint(2);
  ca->InsertCellPoint(3);
  ca->InsertCellPoint(4);
  ca->InsertCellPoint(5);
  ca->InsertCellPoint(6);
  pd->SetPoints(fp);
  pd->SetPolys(ca);


  vtkSmartPointer<vtkImplicitModeller> arrowIM = 
    vtkSmartPointer<vtkImplicitModeller>::New();
  arrowIM->SetInput(pd);
  arrowIM->SetSampleDimensions(50, 20, 8);

  vtkSmartPointer<vtkContourFilter> arrowCF = 
    vtkSmartPointer<vtkContourFilter>::New();
  arrowCF->SetInput((vtkDataObject*)arrowIM->GetOutput());
  arrowCF->SetValue(0, 0.2);
  
  vtkSmartPointer<vtkWarpTo> oldArrowWT = 
    vtkSmartPointer<vtkWarpTo>::New();
  oldArrowWT->SetInputConnection(arrowCF->GetOutputPort());
  oldArrowWT->SetPosition(5, 0, 5);
  
  oldArrowWT->SetScaleFactor(0.85);
  oldArrowWT->AbsoluteOn();

  vtkSmartPointer<vtkDataSetMapper> oldArrowMapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  oldArrowMapper->SetInput(oldArrowWT->GetOutput());
  oldArrowMapper->ScalarVisibilityOff();

  
  vtkSmartPointer<vtkLODActor> oldArrowActor = 
    vtkSmartPointer<vtkLODActor>::New();
  oldArrowActor->SetMapper(oldArrowMapper);

  ////////////// NEW ////////////////
  //Create an arrow.
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();
  arrowSource->Update();
  
  vtkSmartPointer<vtkWarpTo> arrowWT = 
    vtkSmartPointer<vtkWarpTo>::New();
  arrowWT->SetInputConnection(arrowSource->GetOutputPort());
  //arrowWT->SetPosition(5, 0, 5);
  arrowWT->SetPosition(5, 5, 0);
  arrowWT->SetScaleFactor(0.85);
  arrowWT->AbsoluteOn();

  vtkSmartPointer<vtkDataSetMapper> arrowMapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  arrowMapper->SetInput(arrowWT->GetOutput());
  arrowMapper->ScalarVisibilityOff();

  
  vtkSmartPointer<vtkLODActor> arrowActor = 
    vtkSmartPointer<vtkLODActor>::New();
  arrowActor->SetMapper(arrowMapper);
  
  ren1->AddActor(arrowActor);
  ren1->AddActor(oldArrowActor);

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}