#include "itkWin32Header.h"
#include <iostream>
#include <fstream>
#include "itkNumericTraits.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkExtractImageFilter.h"
#include "itkDifferenceImageFilter.h"

using namespace std;

#define ITK_TEST_DIMENSION_MAX 6

int RegressionTestImage (const char *, const char *, int, bool);

int main(int argc, char **argv)
{
  if(argc < 3)
    {
    cerr << "Usage:" << endl;
    cerr << "testImage, baselineImage1, [baselineImage2, baselineImage3, ...]" << endl;
    cerr << "Note that if you supply more than one baselineImage, this test will pass if any" << endl;
    cerr << "of them match the testImage" << endl;
    return -1;
    }
  int bestBaselineStatus = 2001;
  int bestBaseline = 2;
  try
    {
    if(argc == 3)
      {
      bestBaselineStatus = RegressionTestImage(argv[1], argv[2], 0, false);
      }
    else
      {
      int currentStatus = 2001;
      for(int i=2;i<argc;i++)
        {
        currentStatus = RegressionTestImage(argv[1], argv[i], 0, false);
        if(currentStatus < bestBaselineStatus)
          {
          bestBaselineStatus = currentStatus;
          bestBaseline = i;
          }
        if(bestBaselineStatus == 0)
          {
          break;
          }
        }
      }
    // generate images of our closest match
    if(bestBaselineStatus == 0)
      {
      RegressionTestImage(argv[1], argv[bestBaseline], 1, false);
      }
    else
      {
      RegressionTestImage(argv[1], argv[bestBaseline], 1, true);
      }
    
    }
  catch(const itk::ExceptionObject& e)
    {
    std::cerr << "ITK test driver caught an ITK exception:\n";
    std::cerr << e.GetFile() << ":" << e.GetLine() << ":\n"
              << e.GetDescription() << "\n";
    bestBaselineStatus = -1;
    }
  catch(const std::exception& e)
    {
    std::cerr << "ITK test driver caught an exception:\n";
    std::cerr << e.what() << "\n";
    bestBaselineStatus = -1;
    }
  catch(...)
    {
    std::cerr << "ITK test driver caught an unknown exception!!!\n";
    bestBaselineStatus = -1;
    }
  cout << bestBaselineStatus << endl;
  return bestBaselineStatus;
}

// Regression Testing Code
int RegressionTestImage (const char *testImageFilename, const char *baselineImageFilename,
                         int reportErrors, bool differences)
{
  // Use the factory mechanism to read the test and baseline files and convert them to double
  typedef itk::Image<double,ITK_TEST_DIMENSION_MAX> ImageType;
  typedef itk::Image<unsigned char,ITK_TEST_DIMENSION_MAX> OutputType;
  typedef itk::Image<unsigned char,2> DiffOutputType;
  typedef itk::ImageFileReader<ImageType> ReaderType;

  // Read the baseline file
  ReaderType::Pointer baselineReader = ReaderType::New();
    baselineReader->SetFileName(baselineImageFilename);
  try
    {
    baselineReader->UpdateLargestPossibleRegion();
    }
  catch (itk::ExceptionObject& e)
    {
    std::cerr << "Exception detected while reading " << baselineImageFilename << " : "  << e.GetDescription();
    return 1000;
    }

  // Read the file generated by the test
  ReaderType::Pointer testReader = ReaderType::New();
    testReader->SetFileName(testImageFilename);
  try
    {
    testReader->UpdateLargestPossibleRegion();
    }
  catch (itk::ExceptionObject& e)
    {
    std::cerr << "Exception detected while reading " << testImageFilename << " : "  << e.GetDescription() << std::endl;
    return 1000;
    }

  // The sizes of the baseline and test image must match
  ImageType::SizeType baselineSize;
    baselineSize = baselineReader->GetOutput()->GetLargestPossibleRegion().GetSize();
  ImageType::SizeType testSize;
    testSize = testReader->GetOutput()->GetLargestPossibleRegion().GetSize();
  
  if (baselineSize != testSize)
    {
    std::cerr << "The size of the Baseline image and Test image do not match!" << std::endl;
    std::cerr << "Baseline image: " << baselineImageFilename
              << " has size " << baselineSize << std::endl;
    std::cerr << "Test image:     " << testImageFilename
              << " has size " << testSize << std::endl;
    return 1;
    }

  // Now compare the two images
  typedef itk::DifferenceImageFilter<ImageType,ImageType> DiffType;
  DiffType::Pointer diff = DiffType::New();
    diff->SetValidInput(baselineReader->GetOutput());
    diff->SetTestInput(testReader->GetOutput());
    diff->SetDifferenceThreshold(2.0);
    diff->UpdateLargestPossibleRegion();

  double status = diff->GetTotalDifference();

  
  if (reportErrors)
    {
    typedef itk::RescaleIntensityImageFilter<ImageType,OutputType> RescaleType;
    typedef itk::ExtractImageFilter<OutputType,DiffOutputType> ExtractType;
    typedef itk::ImageFileWriter<DiffOutputType> WriterType;
    typedef itk::ImageRegion<ITK_TEST_DIMENSION_MAX> RegionType;
    OutputType::IndexType index; index.Fill(0);
    OutputType::SizeType size; size.Fill(0);

    RescaleType::Pointer rescale = RescaleType::New();
      rescale->SetOutputMinimum(itk::NumericTraits<unsigned char>::NonpositiveMin());
      rescale->SetOutputMaximum(itk::NumericTraits<unsigned char>::max());
      rescale->SetInput(diff->GetOutput());
      rescale->UpdateLargestPossibleRegion();

    RegionType region;
    region.SetIndex(index);
    
    size = rescale->GetOutput()->GetLargestPossibleRegion().GetSize();
    for (unsigned int i = 2; i < ITK_TEST_DIMENSION_MAX; i++)
      {
      size[i] = 0;
      }
    region.SetSize(size);

    ExtractType::Pointer extract = ExtractType::New();
      extract->SetInput(rescale->GetOutput());
      extract->SetExtractionRegion(region);

    WriterType::Pointer writer = WriterType::New();
      writer->SetInput(extract->GetOutput());
    if(differences)
      {
      // if there are discrepencies, report an error
      std::cout << "<DartMeasurement name=\"ImageError\" type=\"numeric/double\">";
      std::cout << status;
      std::cout <<  "</DartMeasurement>" << std::endl;
      }
    ::itk::OStringStream diffName;
      diffName << testImageFilename << ".diff.png";
    try
      {
      rescale->SetInput(diff->GetOutput());
      rescale->Update();
      }
    catch (...)
      {
      std::cerr << "Error during rescale of " << diffName.str() << std::endl;
      }
    writer->SetFileName(diffName.str().c_str());
    try
      {
      writer->Update();
      }
    catch (...)
      {
      std::cerr << "Error during write of " << diffName.str() << std::endl;
      }

    std::cout << "<DartMeasurementFile name=\"DifferenceImage\" type=\"image/png\">";
    std::cout << diffName.str();
    std::cout << "</DartMeasurementFile>" << std::endl;
    ::itk::OStringStream baseName;
    baseName << testImageFilename << ".base.png";
    try
      {
      rescale->SetInput(baselineReader->GetOutput());
      rescale->Update();
      }
    catch (...)
      {
      std::cerr << "Error during rescale of " << baseName.str() << std::endl;
      }
    try
      {
      writer->SetFileName(baseName.str().c_str());
      writer->Update();
      }
    catch (...)
      {
      std::cerr << "Error during write of " << baseName.str() << std::endl;
      }

    std::cout << "<DartMeasurementFile name=\"BaselineImage\" type=\"image/png\">";
    std::cout << baseName.str();
    std::cout << "</DartMeasurementFile>" << std::endl;

    ::itk::OStringStream testName;
    testName << testImageFilename << ".test.png";
    try
      {
      rescale->SetInput(testReader->GetOutput());
      rescale->Update();
      }
    catch (...)
      {
      std::cerr << "Error during rescale of " << testName.str()
                << std::endl;
      }
    try
      {
      writer->SetFileName(testName.str().c_str());
      writer->Update();
      }
    catch (...)
      {
      std::cerr << "Error during write of " << testName.str() << std::endl;
      }

    std::cout << "<DartMeasurementFile name=\"TestImage\" type=\"image/png\">";
    std::cout << testName.str();
    std::cout << "</DartMeasurementFile>" << std::endl;


    }
  return (status != 0) ? 1 : 0;
}
