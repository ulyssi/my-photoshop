#include "TabPanel.hh"

#include "UserInterface.hh"
#include "TracingManager.hh"
#include "Histogram.hh"
#include "Previewer.hh"
#include "ToolBoxChooser.hh"
#include "AffineOperationChooser.hh"
#include "ConvolveOperationChooser.hh"
#include "ColorConvertOperationChooser.hh"


/** Constructeurs et destructeur */
TabPanel::TabPanel(UserInterface* userInterface) :
  m_userInterface(userInterface)
{}

TabPanel::~TabPanel() {}


/** Accesseurs */
QString TabPanel::getTabName() { return m_tabName; }

UserInterface* TabPanel::getUserInterface() { return m_userInterface; }


/** Mutateurs */
void TabPanel::notifyCurrent() {
  m_userInterface->getPreviewer()->setPictureModifier(NULL);
  m_userInterface->getToolBoxChooser()->setPictureModifier(NULL);
  m_userInterface->getAffineOperationChooser()->setPictureModifier(NULL);
  m_userInterface->getConvolveOperationChooser()->setPictureModifier(NULL); 
  m_userInterface->getColorConvertOperationChooser()->setPictureModifier(NULL);
  m_userInterface->getTracingManager()->setPictureModifier(NULL);
  m_userInterface->getHistogram()->setPictureModifier(NULL);
  m_userInterface->update();
}

void TabPanel::setTabName(QString tabName) { m_tabName = tabName; }

void TabPanel:: zoomIn() {}
void TabPanel:: zoomOut(){}
void TabPanel:: normalSize(){}
void TabPanel:: fitToWindow(){}

void TabPanel:: copy(){}		
void TabPanel:: paste(){}
void TabPanel:: cut(){}

bool TabPanel:: enableSelection(){return false;}
void TabPanel:: disableSelection(){}

bool TabPanel:: enableMove(){return false;}
void TabPanel:: disableMove(){}
