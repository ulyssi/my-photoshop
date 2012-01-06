#ifndef _KERNEL_HH_
#define _KERNEL_HH_

#include "Matrix.hh"


class Kernel : public Matrix<double> {

public:

  /** Constructeurs et destructeur */
  Kernel(int);
  Kernel(int, double**);
  ~Kernel();

  /** Accesseurs */
  int getSize();

};

#endif
