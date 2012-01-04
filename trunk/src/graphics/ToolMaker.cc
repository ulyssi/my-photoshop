#include "ToolMaker.hh"

#include "ColorChooser.hh"



/** Constructeurs et destructeur */
ToolMaker::ToolMaker() :
  m_colorChooser(createColorChooser())
{}

ToolMaker::~ToolMaker() {}


/** Accesseurs */
ColorChooser* ToolMaker::getDefaultColorChooser() const { return m_colorChooser; }


/** Methodes */
ColorChooser* ToolMaker::createColorChooser() {
  return new ColorChooser(); 
}


