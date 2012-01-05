#ifndef _OPERATION_HH_
#define _OPERATION_HH_

class Picture;


class Operation {

public:

  /** Constructeurs et destructeur */
  Operation();
  ~Operation();

  /** Methodes */
  Picture* applyOn(Picture*);

private:

};

#endif
