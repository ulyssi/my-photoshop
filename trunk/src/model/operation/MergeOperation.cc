#include "MergeOperation.hh"

#include "Picture.hh"
#include "Tracing.hh"


/** Constructeurs et destructeur */
MergeOperation::MergeOperation() {}

MergeOperation::~MergeOperation() {}


/** Methodes */
Picture* MergeOperation::doOperation(Picture* picture) {
  return picture;
}

Picture* MergeOperation::doOperation(Picture** pictureList, int nbPicture) {
  for (int i = 0; i < nbPicture; i++) pictureList[i] = doOperation(pictureList[i]);
  return pictureList[0];
}

Tracing* MergeOperation::doOperation(Tracing* tracing) { return tracing; }

Tracing* MergeOperation::doOperation(Tracing** tracingList, int nbTracing) {
  return tracingList[0];
}

Operation* MergeOperation::clone() { return NULL; }
