
#ifndef _RESCALE_OPERATION_HH_
#define _RESCALE_OPERATION_HH_

#include "Operation.hh"
#include "Matrix.hh"

class Tracing;


class RescaleOperation : public Operation {

public:

  /** Constructeurs et destructeur */
  RescaleOperation(int,int);
  ~RescaleOperation();

  /** Methodes */
  Tracing* doOperation(Tracing*);
  Operation* clone();

private:

  /** Attributs */
  
  int m_nX;
  int m_nY;
};

#endif
