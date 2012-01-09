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

// Tracing* MergeOperation::doOperation(std::vector<Tracing*> tracingList) {
//   return NULL;;
// }

Operation* MergeOperation::clone() { return NULL; }


/** Methodes internes */
Tracing* MergeOperation::doOperation(Tracing* t1, Tracing* t2) {
  return t1;
}
