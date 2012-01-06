#include "ConvolveOperation.hh"

#include "Tracing.hh"
#include "Kernel.hh"


/** Constructeurs et destructeur */
ConvolveOperation::ConvolveOperation(Kernel *kernel) :
  m_kernel(kernel)
{}

ConvolveOperation::~ConvolveOperation() {}


/** Methodes */
Tracing* ConvolveOperation::doOperation(Tracing* tracing) {
  // unsigned int dataSource = Tracing->getData();

  // int kOff = m_kernel.getSize()/2;
  // for (int i = 0; i < Tracing->getWidth(); i++)
  //   for (int j = 0; j < Tracing->getHeight(); j++)
  //     for (int i2 = -kOff; i2 <= kOff; i2++)
  // 	for (int j2 = -kOff; j2 <= kOff; j2++)
  // 	  m_kernel
  return tracing;
}

Operation* ConvolveOperation::clone() {}
