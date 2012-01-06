#ifndef _OPERATION_HH_
#define _OPERATION_HH_

class Picture;
class Tracing;


class Operation {

public:

  /** Constructeurs et destructeur */
  Operation();
  Operation(Operation*);
  ~Operation();

  /** Methodes */
  Picture* applyOn(Picture*);
  Tracing* applyOn(Tracing*);

  Picture* doOperation(Picture*);
  virtual Tracing* doOperation(Tracing*) = 0;
  virtual Operation* clone() = 0;

private:

  Operation* m_operation;

};

#endif
