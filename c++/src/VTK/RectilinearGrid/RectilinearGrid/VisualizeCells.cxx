#include <vtkSmartPointer.h>
#include <vtkRectilinearGrid.h>
#include <vtkMath.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkShrinkFilter.h>
#include <vtkDoubleArray.h>

int main(int argc, char *argv[])
{
   //create a grid
  vtkSmartPointer<vtkRectilinearGrid> grid = 
      vtkSmartPointer<vtkRectilinearGrid>::New();
  
  grid->SetDimensions(2,3,2);
  
  vtkSmartPointer<vtkDoubleArray> xArray = 
      vtkSmartPointer<vtkDoubleArray>::New();
  xArray->InsertNextValue(0.0);
  xArray->InsertNextValue(2.0);
  
  vtkSmartPointer<vtkDoubleArray> yArray = 
      vtkSmartPointer<vtkDoubleArray>::New();
  yArray->InsertNextValue(0.0);
  yArray->InsertNextValue(1.0);
  yArray->InsertNextValue(2.0);
  
  vtkSmartPointer<vtkDoubleArray> zArray = 
      vtkSmartPointer<vtkDoubleArray>::New();
  zArray->InsertNextValue(0.0);
  zArray->InsertNextValue(5.0);
  
  grid->SetXCoordinates(xArray);
  grid->SetYCoordinates(yArray);
  grid->SetZCoordinates(zArray);
  
  vtkSmartPointer<vtkShrinkFilter> shrinkFilter = 
      vtkSmartPointer<vtkShrinkFilter>::New();
  shrinkFilter->SetInputConnection(grid->GetProducerPort());
  shrinkFilter->SetShrinkFactor(.99);
  shrinkFilter->Update();
  
  //Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper = 
      vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(shrinkFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  //Add the actor to the scene
  renderer->AddActor(actor);
  //renderer->SetBackground(1,1,1); // Background color white
 
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}