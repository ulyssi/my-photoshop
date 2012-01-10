#include "Operation.hh"

#include "Picture.hh"
#include "Tracing.hh"


/** Constructeurs et destructeur */
Operation::Operation() {}

Operation::Operation(Operation* operation) :
  m_operation(operation)
{}

Operation::~Operation() {}


/** Methodes */
Picture* Operation::applyOn(Picture* picture) {
  if (m_operation != NULL) picture = m_operation->applyOn(picture);
  return doOperation(picture);
}

Tracing* Operation::applyOn(Tracing* tracing) {
  if (m_operation != NULL) tracing = m_operation->applyOn(tracing);
  return doOperation(tracing);
}

Picture* Operation::doOperation(Picture* picture) {
  std::vector<Tracing*> tracingPtrList = picture->getListTracing();
  std::vector<Tracing*>::iterator tracingPtr = tracingPtrList.begin();
  while (tracingPtr != tracingPtrList.end()) {
    doOperation(*tracingPtr);
    tracingPtr++;
  }
  return picture;
}

// rgb2 = { r2, g2, b2, a2 } t2
// rgb1 = { r1, g1, b1, a1 } t1 

// rgb2 = { r2, g2, b2, (a2 / 255) * t2 = a2. }
// rgb1 = { r1, g1, b1, (a1 / 255) * t1 = a1. }

// rgb3 = { r1 * (1 - a2.) + r2 * a2., , , (a1. + a2. - a1. * a2.) * 255 } 

// rgbResult(rgb1, rgb2) = { r1 * (1 - a2.) + r2 * a2., , , (a1. + a2. - a1. * a2.) * 255 } 
