#include <vtkSmartPointer.h>
#include <vtkRuledSurfaceFilter.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellArray.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkLine.h>

int main(int, char *[])
{

  // Create first line.
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertPoint(0, 0, 0, 0);
  points->InsertPoint(1, 1, 0, 0);
  points->InsertPoint(2, 0, 1, 0);
  points->InsertPoint(3, 1, 1, 0);
  
  vtkSmartPointer<vtkLine> line1 = 
    vtkSmartPointer<vtkLine>::New();
  line1->GetPointIds()->SetId(0,0);
  line1->GetPointIds()->SetId(1,1);
  
  vtkSmartPointer<vtkLine> line2 = 
    vtkSmartPointer<vtkLine>::New();
  line2->GetPointIds()->SetId(0,2);
  line2->GetPointIds()->SetId(1,3);
  
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line1);
  lines->InsertNextCell(line2);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(lines);

  vtkSmartPointer<vtkRuledSurfaceFilter> ruledSurfaceFilter =
    vtkSmartPointer<vtkRuledSurfaceFilter>::New();
  ruledSurfaceFilter->SetInputConnection(polydata->GetProducerPort());
  ruledSurfaceFilter->SetResolution(51, 51);
  ruledSurfaceFilter->SetRuledModeToResample();

  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
    
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(ruledSurfaceFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(0.3800, 0.7000, 0.1600);

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(actor);
  renderer->SetBackground(1, 1, 1);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
