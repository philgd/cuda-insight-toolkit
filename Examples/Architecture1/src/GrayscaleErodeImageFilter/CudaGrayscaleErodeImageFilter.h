/*=========================================================================

  Program:   Cuda Insight Toolkit
  Module:    $RCSfile: itkCudaGrayscaleErodeImageFilter.h,v $
  Language:  C++ & CUDA
  Date:      $Date: 2009-02-24 14:18:00 $
  Version:   $Revision: 1.0 $

  Copyright (c) 2010, Victorian Partnership for Advanced Computing
All rights reserved.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/


#ifndef __itkCudaGrayscaleErodeImageFilter_h
#define __itkCudaGrayscaleErodeImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkNeighborhood.h"

namespace itk {

/** \class CudaGrayscaleErodeImageFilter
 * \brief gray scale erosion of an image
 *
 * Erode an image using grayscale morphology. Erosion takes the
 * minimum of all the pixels identified by the structuring element.
 *
 * The structuring element is assumed to be composed of binary
 * values (zero or one). Only elements of the structuring element
 * having values > 0 are candidates for affecting the center pixel.
 * 
 * For the each input image pixel,
 *   - NeighborhoodIterator gives neighbors of the pixel.
 *   - Evaluate() member function returns the minimum value among
 *     the image neighbors where the kernel has elements > 0
 *   - Replace the original value with the min value
 *
 * \author Phillip Ward, Victorian Partnership for Advanced Computing (VPAC)
 *
 * \sa ImageToImageFilter
 * \ingroup ImageEnhancement  MathematicalMorphologyImageFilters  CudaEnabled
 */


template<class TInputImage, class TOutputImage, class TKernel>
class ITK_EXPORT CudaGrayscaleErodeImageFilter: public ImageToImageFilter<TInputImage,
		TOutputImage> {
public:

	/** Standard class typedefs. */
	typedef CudaGrayscaleErodeImageFilter Self;
	typedef ImageToImageFilter<TInputImage, TOutputImage> Superclass;
	typedef SmartPointer<Self> Pointer;
	typedef SmartPointer<const Self> ConstPointer;

	/** Method for creation through the object factory. */
	itkNewMacro(Self)	;

	/** Runtime information support. */
	itkTypeMacro(CudaGrayscaleErodeImageFilter,
			ImageToImageFilter)	;

	  typedef TInputImage                                   InputImageType;
	  typedef TOutputImage                                  OutputImageType;
	  typedef typename TInputImage::RegionType              RegionType;
	  typedef typename TInputImage::SizeType                SizeType;
	  typedef typename TInputImage::IndexType               IndexType;
	  typedef typename TInputImage::PixelType               PixelType;
	  typedef typename Superclass::OutputImageRegionType    OutputImageRegionType;

	  /** Image related typedefs. */
	   itkStaticConstMacro(ImageDimension, unsigned int, TInputImage::ImageDimension);

	   /** Kernel typedef. */
	     typedef TKernel KernelType;
	     typedef typename TKernel::PixelType            KernelPixelType;

	     /** n-dimensional Kernel radius. */
	     typedef typename KernelType::SizeType RadiusType;

	     /** Set kernel (structuring element). */
	     itkSetMacro(Kernel, KernelType);

	     /** Get the kernel (structuring element). */
	     itkGetConstReferenceMacro(Kernel, KernelType);

	     /** ImageDimension constants */
	     itkStaticConstMacro(InputImageDimension, unsigned int,
	                         TInputImage::ImageDimension);
	     itkStaticConstMacro(OutputImageDimension, unsigned int,
	                         TOutputImage::ImageDimension);
	     itkStaticConstMacro(KernelDimension, unsigned int,
	                         TKernel::NeighborhoodDimension);


#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro(InputConvertibleToOutputCheck,
    (Concept::Convertible<PixelType, typename TOutputImage::PixelType>));
  itkConceptMacro(SameDimensionCheck1,
     (Concept::SameDimension<InputImageDimension, OutputImageDimension>));
  itkConceptMacro(SameDimensionCheck2,
    (Concept::SameDimension<InputImageDimension, KernelDimension>));
  itkConceptMacro(InputLessThanComparableCheck,
    (Concept::LessThanComparable<PixelType>));
  itkConceptMacro(KernelGreaterThanComparableCheck,
    (Concept::GreaterThanComparable<KernelPixelType>));
  /** End concept checking */
#endif


protected:
	CudaGrayscaleErodeImageFilter();
	~CudaGrayscaleErodeImageFilter() {
	}
	void PrintSelf(std::ostream& os, Indent indent) const;
	void GenerateData();

private:
	CudaGrayscaleErodeImageFilter(const Self&); //purposely not implemented
	void operator=(const Self&); //purposely not implemented

	/** kernel or structuring element to use. */
	KernelType m_Kernel;
};

} // end namespace itk
#ifndef ITK_MANUAL_INSTANTIATION
#include "CudaGrayscaleErodeImageFilter.txx"
#endif

#endif
