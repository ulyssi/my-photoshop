#include "TabPanel.hh"

#include "UserInterface.hh"


/** Constructeurs et destructeur */
TabPanel::TabPanel(UserInterface* userInterface) :
  m_userInterface(userInterface)
{}

TabPanel::~TabPanel() {}
  

/** Accesseurs */
QString TabPanel::getTabName() { return m_tabName; }

UserInterface* TabPanel::getUserInterface() { return m_userInterface; }


/** Mutateurs */
void TabPanel::setTabName(QString tabName) { m_tabName = tabName; }
