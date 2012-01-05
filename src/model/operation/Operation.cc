#include "Operation.hh"

#include "../Picture.hh"


/** Constructeurs et destructeur */
Operation::Operation() {}

Operation::~Operation() {}


/** Methodes */
Picture* Operation::applyOn(Picture* picture) { return picture; }
