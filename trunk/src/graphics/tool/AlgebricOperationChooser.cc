#include "AlgebricOperationChooser.hh"



/** Constructeurs et destructeur */
AlgebricOperationChooser::AlgebricOperationChooser() :
  m_tabName("AlgebricOperation")
{
  setText(m_tabName);
}

AlgebricOperationChooser::~AlgebricOperationChooser() {}


/** Accesseurs */
const QString& AlgebricOperationChooser::getTabName() const { return m_tabName; }
