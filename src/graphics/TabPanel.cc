#include "TabPanel.hh"

#include "UserInterface.hh"
#include "Histogram.hh"

#include <iostream>
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
  m_userInterface->getHistogram()->setPictureModifier(NULL);
  m_userInterface->update();
  std::cout << "OK TabPanel" << std::endl;
}

void TabPanel::setTabName(QString tabName) { m_tabName = tabName; }
