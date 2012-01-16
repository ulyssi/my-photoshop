#ifndef _OPERATION_HH_
#define _OPERATION_HH_

#include "Matrix.hh"

class Picture;
class Tracing;


class Operation {

public:

  /** Constructeurs et destructeur */
  Operation();
  Operation(Operation*);
  ~Operation();

  /** Accesseurs */
  // Operation* getPreviousOperation();
  // Matrix<unsigned int>* getPictureData();
  // Matrix<unsigned int>* getPreviewData();

  /** Methodes */
  // Matrix<unsigned int>* updatePreview();
  // Picture* applyOperation();

  Picture* applyOn(Picture*);
  Tracing* applyOn(Tracing*);

  Picture* doOperation(Picture*);
  virtual Tracing* doOperation(Tracing*) = 0;
  virtual Operation* clone() = 0;

private:

  /** Attributs */
  Operation* m_operation;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;

};

#endif
