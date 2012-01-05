#include "ConvolveOperationChooser.hh"



/** Constructeurs et destructeur */
ConvolveOperationChooser::ConvolveOperationChooser() :
  m_tabName("Convolve")
{
  setText(m_tabName);
}

ConvolveOperationChooser::~ConvolveOperationChooser() {}


/** Accesseurs */
const QString& ConvolveOperationChooser::getTabName() const { return m_tabName; }
