#include "RescaleOperationChooser.hh"



/** Constructeurs et destructeur */
RescaleOperationChooser::RescaleOperationChooser() :
  m_tabName("Rescale")
{
  setText(m_tabName);
}

RescaleOperationChooser::~RescaleOperationChooser() {}


/** Accesseurs */
const QString& RescaleOperationChooser::getTabName() const { return m_tabName; }
