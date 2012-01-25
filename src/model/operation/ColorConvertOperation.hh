#ifndef _COLOR_CONVERT_OPERATION_HH_
#define _COLOR_CONVERT_OPERATION_HH_

#include "Operation.hh"
#include "Matrix.hh"
#include "PixelMod.hh"

class Tracing;


class ColorConvertOperation {

public:

  /** Constructeurs et destructeur */
  ColorConvertOperation(Picture*, Operation* = 0);
  ~ColorConvertOperation();

  /** Mutateurs */
  void setKernel(Matrix<double>*);
  void setSeuilMin(PixelMod::RGB, int);
  void setSeuilMax(PixelMod::RGB, int);

  /** Methodes */
  Matrix<unsigned int>* updatePreview();
  Picture* applyOperation();

  /** Methodes de classes */
  static Matrix<double>* createIdentityKernel();
  static Matrix<double>* createGreyScaleKernel();
  static Matrix<double>* createSepiaKernel();

private:

  /** Attributs */
  Operation* m_operation;
  Picture* m_picture;
  Matrix<double>* m_kernel;
  int *m_seuilMin, *m_seuilMax;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;
  
};

#endif
