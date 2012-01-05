#include "OperationChooser.hh"

#include "ToolMaker.hh"
#include "AffineOperationChooser.hh"
#include "RescaleOperationChooser.hh"
#include "ConvolveOperationChooser.hh"
#include "AlgebricOperationChooser.hh"
#include "ColorConvertOperationChooser.hh"



/** Constructeurs et destructeur */
OperationChooser::OperationChooser() :
  m_tabName("OperationChooser"),
  m_affineOperationChooser(ToolMaker::createAffineOperationChooser()),
  m_rescaleOperationChooser(ToolMaker::createRescaleOperationChooser()),
  m_convolveOperationChooser(ToolMaker::createConvolveOperationChooser()),
  m_algebricOperationChooser(ToolMaker::createAlgebricOperationChooser()),
  m_colorConvertOperationChooser(ToolMaker::createColorConvertOperationChooser())
{
  addTab(m_affineOperationChooser, m_affineOperationChooser->getTabName());
  addTab(m_rescaleOperationChooser, m_rescaleOperationChooser->getTabName());
  addTab(m_convolveOperationChooser, m_convolveOperationChooser->getTabName());
  addTab(m_algebricOperationChooser, m_algebricOperationChooser->getTabName());
  addTab(m_colorConvertOperationChooser, m_colorConvertOperationChooser->getTabName());
}

OperationChooser::~OperationChooser() {}


/** Accesseurs */
const QString& OperationChooser::getTabName() const { return m_tabName; }

AffineOperationChooser* OperationChooser::getAffineOperationChooser() const {
  return m_affineOperationChooser; 
}

RescaleOperationChooser* OperationChooser::getRescaleOperationChooser() const {
  return m_rescaleOperationChooser; 
}

ConvolveOperationChooser* OperationChooser::getConvolveOperationChooser() const {
  return m_convolveOperationChooser; 
}

AlgebricOperationChooser* OperationChooser::getAlgebricOperationChooser() const {
  return m_algebricOperationChooser; 
}

ColorConvertOperationChooser* OperationChooser::getColorConvertOperationChooser() const { 
  return m_colorConvertOperationChooser;
}
