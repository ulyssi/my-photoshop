#include "ToolMaker.hh"

#include "ColorChooser.hh"
// #include "BrushChooser.hh"
// #include "HistogramModifier.hh"
#include "OperationChooser.hh"
#include "AffineOperationChooser.hh"
#include "RescaleOperationChooser.hh"
#include "ConvolveOperationChooser.hh"
#include "AlgebricOperationChooser.hh"
#include "ColorConvertOperationChooser.hh"



/** Constructeurs et destructeur */
ToolMaker::ToolMaker() :
  m_colorChooser(createColorChooser()),
//  m_histogramModifier(createHistogramModifier()),
  m_affineOperationChooser(createAffineOperationChooser()),
  m_rescaleOperationChooser(createRescaleOperationChooser()),
  m_convolveOperationChooser(createConvolveOperationChooser()),
  m_algebricOperationChooser(createAlgebricOperationChooser()),
  m_colorConvertOperationChooser(createColorConvertOperationChooser()),
  m_operationChooser(createOperationChooser())
{}

ToolMaker::~ToolMaker() {}


/** Accesseurs */
ColorChooser* ToolMaker::getDefaultColorChooser() const {
  return m_colorChooser; 
}

// BrushChooser* getDefaultBrushChooser() const;

// HistogramModifier* ToolMaker::getDefaultHistogramModifier() const {
//   return m_histogramModifier;
// }

AffineOperationChooser* ToolMaker::getDefaultAffineOperationChooser() const {
  return m_affineOperationChooser; 
}

RescaleOperationChooser* ToolMaker::getDefaultRescaleOperationChooser() const {
  return m_rescaleOperationChooser; 
}

ConvolveOperationChooser* ToolMaker::getDefaultConvolveOperationChooser() const {
  return m_convolveOperationChooser; 
}

AlgebricOperationChooser* ToolMaker::getDefaultAlgebricOperationChooser() const {
  return m_algebricOperationChooser; 
}

ColorConvertOperationChooser* ToolMaker::getDefaultColorConvertOperationChooser() const { 
  return m_colorConvertOperationChooser;
}

OperationChooser* ToolMaker::getDefaultOperationChooser() const { 
  return m_operationChooser; 
}


/** Methodes */
ColorChooser* ToolMaker::createColorChooser() { return new ColorChooser(); }
// BrushChooser* createBrushChooser();
/*HistogramModifier* ToolMaker::createHistogramModifier() { return new HistogramModifier(); }*/
AffineOperationChooser* ToolMaker::createAffineOperationChooser() { return new AffineOperationChooser(); }
RescaleOperationChooser* ToolMaker::createRescaleOperationChooser() { return new RescaleOperationChooser(); }
ConvolveOperationChooser* ToolMaker::createConvolveOperationChooser() { return new ConvolveOperationChooser(); }
AlgebricOperationChooser* ToolMaker::createAlgebricOperationChooser() { return new AlgebricOperationChooser(); }
ColorConvertOperationChooser* ToolMaker::createColorConvertOperationChooser() { return new ColorConvertOperationChooser(); }
OperationChooser* ToolMaker::createOperationChooser() { return new OperationChooser(this); }


