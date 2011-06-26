#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkImagePlaneWidget.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  
  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);
  
  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  
  //vtkSmartPointer<vtkInteractorStyleTrackballActor> style = 
    //  vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  
  renderWindowInteractor->SetInteractorStyle( style );
  
  vtkSmartPointer<vtkImagePlaneWidget> planeWidget = vtkSmartPointer<vtkImagePlaneWidget>::New();
  planeWidget->SetInteractor(renderWindowInteractor);
  
  double origin[3] = {0, 1,0};
  planeWidget->SetOrigin(origin);
  planeWidget->UpdatePlacement();
    
  // render an image (lights and cameras are created automatically)
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  planeWidget->On();
  
  // begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;;
}
