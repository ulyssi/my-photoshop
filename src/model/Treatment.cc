#include "Treatment.hh"

#include "operation/Operation.hh"
#include "Picture.hh"
#include "Tracing.hh"


/** Constructeurs et destructeur */
Treatment::Treatment(Operation* operation) :
  m_operation(operation)
{}

Treatment::~Treatment() {}


/** Methodes */
void Treatment::execute(Picture* picture) {}

void Treatment::execute(Tracing* tracing) {}
