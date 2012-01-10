#ifndef _CONVOLVE_OPERATION_HH_
#define _CONVOLVE_OPERATION_HH_

#include "Operation.hh"
#include "Matrix.hh"

class Tracing;

class ConvolveOperation : public Operation {

public:

  /** Constructeurs et destructeur */
  ConvolveOperation(Matrix<double>*);
  ~ConvolveOperation();

  /** Methodes */
  Tracing* doOperation(Tracing*);
  Operation* clone();

private:

  Matrix<double>* m_kernel;

};

#endif
