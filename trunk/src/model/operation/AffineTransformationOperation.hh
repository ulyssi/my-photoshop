#ifndef _AFFINE_TRANSFORMATION_OPERATION_HH_
#define _AFFINE_TRANSFORMATION_OPERATION_HH_

#include "Operation.hh"
#include "PixelMod.hh"
#include "Matrix.hh"

class Picture;

class AffineTransformationOperation : public Operation {

public:

  /** Constructeurs et destructeur */
  AffineTransformationOperation(Picture*, Operation* = 0);
  ~AffineTransformationOperation();

  /** Accesseurs */
  Picture* getPicture();
  PixelMod::Type getInputType();
  PixelMod::Type getOutputType();

  /** Methodes */
  Matrix<unsigned int>* preview(double, double);
  Picture* apply(double, double);
  
private:

  /** Attributs */
  Operation* m_operation;
  Picture* m_picture;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;

};

#endif
