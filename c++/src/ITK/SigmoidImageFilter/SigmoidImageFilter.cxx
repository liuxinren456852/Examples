#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkSigmoidImageFilter.h"

#include <itkImageToVTKImageFilter.h>

#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkImageActor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderer.h"

int main(int argc, char *argv[])
{
  if(argc < 2)
    {
    std::cerr << "Required: filename" << std::endl;
    return EXIT_FAILURE;
    }
  typedef itk::Image<unsigned char, 2> ImageType;
  typedef itk::ImageFileReader<ImageType> ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);

  typedef itk::SigmoidImageFilter <ImageType, ImageType>
          SigmoidImageFilterType;

  SigmoidImageFilterType::Pointer sigmoidFilter
          = SigmoidImageFilterType::New();
  sigmoidFilter->SetInput(reader->GetOutput());
  sigmoidFilter->SetOutputMinimum(50);
  sigmoidFilter->SetOutputMaximum(200);
  sigmoidFilter->SetAlpha(5);
  sigmoidFilter->SetBeta(10);
  sigmoidFilter->Update();

  // Visualize first image
  typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
  ConnectorType::Pointer originalConnector = ConnectorType::New();
  originalConnector->SetInput(reader->GetOutput());

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->SetInput(originalConnector->GetOutput());

  // Visualize padded image
  ConnectorType::Pointer sigmoidConnector = ConnectorType::New();
  sigmoidConnector->SetInput(sigmoidFilter->GetOutput());

  vtkSmartPointer<vtkImageActor> sigmoidActor =
    vtkSmartPointer<vtkImageActor>::New();
  sigmoidActor->SetInput(sigmoidConnector->GetOutput());

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  // Add the sphere to the left and the cube to the right
  leftRenderer->AddActor(originalActor);
  rightRenderer->AddActor(sigmoidActor);

  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(style);

  interactor->Start();

  return EXIT_SUCCESS;
}
