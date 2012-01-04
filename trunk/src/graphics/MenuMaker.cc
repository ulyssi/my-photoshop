#include "MenuMaker.hh"

#include "UserInterface.hh"
#include "ActionMaker.hh"

/** Constructeurs et destructeur */
MenuMaker::MenuMaker(UserInterface* userInterface) :
  m_userInterface(userInterface)
{
  createFileMenu();
  createEditMenu();
  createViewMenu();
  createOperationMenu();
  createHelpMenu();
}

MenuMaker::~MenuMaker() {}


/** Accesseurs */

QMenu* MenuMaker::getFileMenu() const { return m_fileMenu; }

QMenu* MenuMaker::getEditMenu() const { return m_editMenu; }

QMenu* MenuMaker::getViewMenu() const { return m_viewMenu; }

QMenu* MenuMaker::getOperationMenu() const { return m_operationMenu; }

QMenu* MenuMaker::getHelpMenu() const { return m_helpMenu; }


/** Accesseurs internes */
ActionMaker* MenuMaker::getActionMaker() const { return m_userInterface->getActionMaker(); } 


/** Methodes internes */
void MenuMaker::createFileMenu() {
  m_fileMenu = new QMenu(tr("&File"), m_userInterface);
  m_fileMenu->addAction(getActionMaker()->getOpenAction());
  m_fileMenu->addAction(getActionMaker()->getSaveAction());
  m_fileMenu->addSeparator();
  m_fileMenu->addAction(getActionMaker()->getExitAction());
}

void MenuMaker::createEditMenu() {
  m_editMenu = new QMenu(tr("&Edit"), m_userInterface);
  m_editMenu->addAction(getActionMaker()->getUndoAction());
  m_editMenu->addAction(getActionMaker()->getRedoAction());
}

void MenuMaker::createViewMenu() {
  m_viewMenu = new QMenu(tr("&View"), m_userInterface);
  m_viewMenu->addAction(getActionMaker()->getZoomInAction());
  m_viewMenu->addAction(getActionMaker()->getZoomOutAction());
  m_viewMenu->addAction(getActionMaker()->getNormalSizeAction());
  m_viewMenu->addAction(getActionMaker()->getFitToWindowAction());
}

void MenuMaker::createOperationMenu() {
  m_operationMenu = new QMenu(tr("&Operation"), m_userInterface);
  m_operationMenu->addAction(getActionMaker()->getBlackAndWhiteAction());
  m_operationMenu->addAction(getActionMaker()->getRescaleAction());
}

void MenuMaker::createHelpMenu() {
  m_helpMenu = new QMenu(tr("&Help"), m_userInterface);
  m_helpMenu->addAction(getActionMaker()->getAboutAction());
  m_helpMenu->addAction(getActionMaker()->getAboutQtAction());
}
