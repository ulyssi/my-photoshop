#ifndef _CONVOLVE_OPERATION_HH_
#define _CONVOLVE_OPERATION_HH_

#include "Operation.hh"
#include "PixelMod.hh"
#include "Matrix.hh"

class Picture;
class Tracing;


class ConvolveOperation {

public:

  /** Constructeurs et destructeur */
  ConvolveOperation(Picture*, Operation* = 0);
  ~ConvolveOperation();

  /** Accesseurs */
  Picture* getPicture();
  PixelMod::Type getInputType();
  PixelMod::Type getOutputType();

  /** Mutateurs */
  void setKernel(Matrix<double>*);
  void setRGBA(bool, bool, bool, bool);
  void setRed(bool);
  void setGreen(bool);
  void setBlue(bool);
  void setAlpha(bool);

  /** Methodes */
  Matrix<unsigned int>* updatePreview();
  Picture* applyOperation();

private:

  /** Attributs */
  Operation* m_operation;
  Picture* m_picture;
  Matrix<double>* m_kernel;
  bool m_red, m_green, m_blue, m_alpha;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;

};

#endif
