#include <vtkSmartPointer.h>
#include <vtkRandomGraphSource.h>
#include <vtkGraphWriter.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>

int main ( int argc, char *argv[] )
{
  vtkSmartPointer<vtkRandomGraphSource> randomGraphSource = 
      vtkSmartPointer<vtkRandomGraphSource>::New();
  randomGraphSource->SetNumberOfVertices(5);
  randomGraphSource->SetNumberOfEdges(4);
  randomGraphSource->SetSeed(0); // This ensures repeatable results for testing. Turn this off for real use.
  randomGraphSource->Update();
  
  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView = 
      vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(randomGraphSource->GetOutput());
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();
  graphLayoutView->GetInteractor()->Start();
     
  return EXIT_SUCCESS;
}
