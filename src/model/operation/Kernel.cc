#include "Kernel.hh"



/** Constructeurs et destructeur */
Kernel::Kernel(int size) :
  Matrix<double>(size, size)
{}

Kernel::Kernel(int size, double **data) :
  Matrix<double>(size, size, data)
{}

Kernel::~Kernel() {}


/** Accesseurs */
int Kernel::getSize() { return getWidth(); }
