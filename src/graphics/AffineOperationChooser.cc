#include "AffineOperationChooser.hh"


/** Constructeurs et destructeur */
AffineOperationChooser::AffineOperationChooser() :
  m_tabName("AffineOperation")
{
  setText(m_tabName);
}

AffineOperationChooser::~AffineOperationChooser() {}


/** Accesseurs */
const QString& AffineOperationChooser::getTabName() const { return m_tabName; }
