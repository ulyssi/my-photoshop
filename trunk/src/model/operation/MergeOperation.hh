#ifndef _MERGE_OPERATION_HH_
#define _MERGE_OPERATION_HH_

#include "Operation.hh"

class Picture;
class Tracing;

class MergeOperation : public Operation {

public:

  /** Constructeurs et destructeurs */
  MergeOperation();
  ~MergeOperation();

  /** Methodes */
  Picture* doOperation(Picture*);
  Picture* doOperation(Picture**, int);

  Tracing* doOperation(Tracing*);
  Tracing* doOperation(Tracing**, int);
  Operation* clone();

};

#endif
