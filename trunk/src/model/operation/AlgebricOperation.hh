#ifndef _ALGEBRIC_OPERATION_HH_
#define _ALGEBRIC_OPERATION_HH_

#include "Operation.hh"
#include "Matrix.hh"
#include "PixelMod.hh"

class Picture;


class AlgebricOperation {

public:

  /** Type internes */
  enum Operator { ERODE_OPERATOR, EXPAND_OPERATOR };
  enum EdgeControl { EXTEND_EDGE, CROP_EDGE, WRAP_EDGE };

  /** Constructeurs et destructeur */
  AlgebricOperation(Picture*, Operation* = 0);
  ~AlgebricOperation();

  /** Mutateurs */
  void setKernel(Matrix<double>*);

  /** Methodes */
  Matrix<unsigned int>* updatePreview();
  Picture* applyOperation();

private:

  /** Methodes internes */
  Matrix<unsigned int>* binarization(Matrix<unsigned int>*);

  /** Attributs */
  Operation* m_operation;
  Picture* m_picture;
  Matrix<double>* m_kernel;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;
  
};

#endif
