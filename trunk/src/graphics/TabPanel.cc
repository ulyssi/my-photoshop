#include "TabPanel.hh"

#include "UserInterface.hh"
#include "TracingManager.hh"
#include "Histogram.hh"
#include "Previewer.hh"
#include "AffineOperationChooser.hh"


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
  m_userInterface->getAffineOperationChooser()->setPictureModifier(NULL);
  m_userInterface->getTracingManager()->setPictureModifier(NULL);
  m_userInterface->getHistogram()->setPictureModifier(NULL);
  m_userInterface->update();
}

void TabPanel::setTabName(QString tabName) { m_tabName = tabName; }
