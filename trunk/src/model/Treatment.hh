#ifndef _TREATMENT_HH_
#define _TREATMENT_HH_

class Operation;
class Picture;
class Tracing;


class Treatment {

public:

  /** Constructeurs et destructeurs */
  Treatment(Operation*);
  ~Treatment();

  /** Methodes */
  void execute(Picture*);
  void execute(Tracing*);

private:

  /** Attributs */
  Operation* m_operation;

};

#endif
