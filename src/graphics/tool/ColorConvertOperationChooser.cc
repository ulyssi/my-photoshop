#include "ColorConvertOperationChooser.hh"



/** Constructeurs et destructeur */
ColorConvertOperationChooser::ColorConvertOperationChooser() :
  m_tabName("ColorConvertOperation")
{
  setText(m_tabName);
}

ColorConvertOperationChooser::~ColorConvertOperationChooser() {}


/** Accesseurs */
const QString& ColorConvertOperationChooser::getTabName() const { return m_tabName; }

