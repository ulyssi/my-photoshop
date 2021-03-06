#ifndef _AFFINE_TRANSFORMATION_OPERATION_HH_
#define _AFFINE_TRANSFORMATION_OPERATION_HH_

#include "Operation.hh"
#include "../PixelMod.hh"
#include "../Matrix.hh"

class Picture;

class AffineTransformationOperation:public Operation {

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

  /** Mutateurs */
  void setRotationDegree(double);
  void setRotation(double);
  void setRescale(double, double);
  void setRescaleX(double);
  void setRescaleY(double);
  void setCenter(double, double);
  void setCenterX(double);
  void setCenterY(double);
  void setSymetrie(bool);
  void setSymetrieX(bool);
  void setSymetrieY(bool);
  void setInterpolation(Interpolation);
  void setData(Matrix<unsigned int>*);

  /** Methodes */
  Matrix<unsigned int>* updateInternalPreview();
  Picture* applyInternalOperation();

private:

  /** Methodes internes */
  void createPreview();
  unsigned int bilinearInterpolation(double, double);

  /** Attributs */


  double m_scaleX, m_scaleY, m_alpha;
  double m_x0, m_y0;
  double m_cosAlpha, m_sinAlpha;
  int m_symetrieX, m_symetrieY;
  Interpolation m_interpolation;


  Matrix<double>* m_mapping;
  Matrix<double>* m_mappingInv;
  unsigned int m_defaultColor;

};

#endif
