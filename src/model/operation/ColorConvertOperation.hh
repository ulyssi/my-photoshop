#ifndef _COLOR_CONVERT_OPERATION_HH_
#define _COLOR_CONVERT_OPERATION_HH_

#include "Operation.hh"
#include "Matrix.hh"

class Tracing;


class ColorConvertOperation : public Operation {

public:

  /** Constructeurs et destructeur */
  ColorConvertOperation(Matrix<double>* application);
  ~ColorConvertOperation();

  /** Methodes */
  Tracing* doOperation(Tracing*);
  Operation* clone();

private:

  /** Attributs */
  Matrix<double>* m_application;

};

#endif