/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    CudaMultiplyImageFilter.txx
  Language:  

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __CudaMultiplyImageFilter_txx
#define __CudaMultiplyImageFilter_txx

#include "CudaMultiplyImageFilter.h"

#include "CudaMultiplyImageFilterKernel.h"

namespace itk {

/*
 *
 */
template<class TInputImage, class TOutputImage>
CudaMultiplyImageFilter<TInputImage, TOutputImage>::CudaMultiplyImageFilter() {
  this->SetNumberOfRequiredInputs(2);
}

/*
 *
 */
template<class TInputImage, class TOutputImage>
void CudaMultiplyImageFilter<TInputImage, TOutputImage>::PrintSelf(
  std::ostream& os, Indent indent) const {
  Superclass::PrintSelf(os, indent);

  os << indent << "Cuda Multiply Image Filter" << std::endl;
}

/*
 *
 */
template<class TInputImage, class TOutputImage>
void CudaMultiplyImageFilter<TInputImage, TOutputImage>::GenerateData() {
  this->AllocateOutputs();
  // Set input and output type names.
  typename OutputImageType::Pointer output = this->GetOutput();
  typename InputImageType::ConstPointer input1 = this->GetInput(0);
  typename InputImageType::ConstPointer input2 = this->GetInput(1);

  // Calculate number of Dimensions
  const unsigned long D =
    input1->GetLargestPossibleRegion().GetImageDimension();
  const unsigned long D2 =
    input2->GetLargestPossibleRegion().GetImageDimension();

  // Calculate size of array using number of dimensions.
  const unsigned long N = input1->GetPixelContainer()->Size();
  const unsigned long N2 = input2->GetPixelContainer()->Size();

  if (D != D2 || N != N2) {
  std::cerr << "Input Dimensions Dont Match" << std::endl;
  return;
  }


  // Call Cu Function to execute kernel
  MultiplyImageKernelFunction<InputPixelType, OutputPixelType>(input1->GetDevicePointer(), input2->GetDevicePointer(), output->GetDevicePointer(), N);
}
}

#endif

