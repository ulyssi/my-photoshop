#ifndef _CONVOLVE_OPERATION_HH_
#define _CONVOLVE_OPERATION_HH_

#include "Operation.hh"

class Tracing;
class Kernel;


class ConvolveOperation : public Operation {

public:

  /** Constructeurs et destructeur */
  ConvolveOperation(Kernel*);
  ~ConvolveOperation();

  Tracing* doOperation(Tracing*);
  Operation* clone();

private:

  Kernel* m_kernel;

};

#endif
