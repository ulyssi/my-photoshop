#ifndef _AFFINE_TRANSFORMATION_OPERATION_HH_
#define _AFFINE_TRANSFORMATION_OPERATION_HH_

#include "Operation.hh"
#include "PixelMod.hh"
#include "Matrix.hh"

class Picture;

class AffineTransformationOperation {

public:

  /** Type internes */
  enum Interpolation { BILINEAR_INTERPOLATION };

  /** Constructeurs et destructeur */
  AffineTransformationOperation(Picture*, Operation* = 0);
  ~AffineTransformationOperation();

  /** Accesseurs */
  Picture* getPicture();
  PixelMod::Type getInputType();
  PixelMod::Type getOutputType();

  /** Methodes */
  Matrix<unsigned int>* preview(double, double, double, int, int);
  Picture* apply(double, double, double , int, int, Interpolation = BILINEAR_INTERPOLATION);
  
private:

  /** Methodes internes */
  void createPreview();
  unsigned int bilinearInterpolation(double, double);

  /** Attributs */
  Operation* m_operation;
  Picture* m_picture;
  double m_scaleX, m_scaleY, m_alpha;
  double m_x0, m_y0;
  double m_cosAlpha, m_sinAlpha;
  
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;
  Matrix<double>* m_mapping;
  Matrix<double>* m_mappingInv;
  unsigned int m_defaultColor;

};

#endif
