#include <vtkPoints.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkHull.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkXMLPolyDataReader> reader = 
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();
  
  vtkSmartPointer<vtkHull> hullFilter = 
      vtkSmartPointer<vtkHull>::New();
  hullFilter->SetInputConnection(reader->GetOutputPort());
  hullFilter->AddCubeFacePlanes ();
  hullFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(hullFilter->GetOutputPort());
  writer->SetFileName("hull.vtp");
  writer->Write();
  
  return 0;
}
