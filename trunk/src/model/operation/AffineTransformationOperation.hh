#ifndef _AFFINE_TRANSFORMATION_OPERATION_HH_
#define _AFFINE_TRANSFORMATION_OPERATION_HH_

#include "Operation.hh"
#include "PixelMod.hh"
#include "Matrix.hh"

class Picture;

class AffineTransformationOperation {

public:

  /** Constructeurs et destructeur */
  AffineTransformationOperation(Picture*, Operation* = 0);
  ~AffineTransformationOperation();

  /** Accesseurs */
  Picture* getPicture();
  PixelMod::Type getInputType();
  PixelMod::Type getOutputType();

  /** Methodes */
  Matrix<unsigned int>* preview(double, double, double, int, int);
  Picture* apply(double, double);
  
private:

  /** Methodes internes */
  void createPreview();
  unsigned int bilinearInterpolation(double, double);

  /** Attributs */
  Operation* m_operation;
  Picture* m_picture;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;
  Matrix<double>* m_mapping;
  Matrix<double>* m_mappingInv;
  int m_centerX, m_centerY;

  unsigned int m_defaultColor;

};

#endif
