#include "MenuMaker.hh"

#include <QObject>

#include "UserInterface.hh"
#include "ActionMaker.hh"





/** Constructeurs et destructeur */
MenuMaker::MenuMaker(ActionMaker* actionMaker, UserInterface* userInterface) :
  m_fileMenu(createFileMenu(actionMaker, userInterface)),
  m_editMenu(createEditMenu(actionMaker, userInterface)),
  m_viewMenu(createViewMenu(actionMaker, userInterface)),
  m_helpMenu(createHelpMenu(actionMaker, userInterface)),
  m_operationMenu(createOperationMenu(actionMaker, userInterface))
{}

MenuMaker::~MenuMaker() {}


/** Accesseurs */
QMenu* MenuMaker::getFileMenu() const { return m_fileMenu; }
QMenu* MenuMaker::getEditMenu() const { return m_editMenu; }
QMenu* MenuMaker::getViewMenu() const { return m_viewMenu; }
QMenu* MenuMaker::getHelpMenu() const { return m_helpMenu; }
QMenu* MenuMaker::getOperationMenu() const { return m_operationMenu; }


/** Methodes internes */
QMenu* MenuMaker::createFileMenu(ActionMaker* actionMaker, UserInterface* userInterface) {
  QMenu* menu = new QMenu(QObject::tr("&File"), userInterface);
  menu->addAction(actionMaker->getOpenAction());
  menu->addAction(actionMaker->getSaveAction());
  menu->addSeparator();
  menu->addAction(actionMaker->getExitAction());
  return menu;
}

QMenu* MenuMaker::createEditMenu(ActionMaker* actionMaker, UserInterface* userInterface) {
  QMenu* menu = new QMenu(QObject::tr("&Edit"), userInterface);
  menu->addAction(actionMaker->getUndoAction());
  menu->addAction(actionMaker->getRedoAction());
  return menu;
}

QMenu* MenuMaker::createViewMenu(ActionMaker* actionMaker, UserInterface* userInterface) {
  QMenu* menu = new QMenu(QObject::tr("&View"), userInterface);
  menu->addAction(actionMaker->getZoomInAction());
  menu->addAction(actionMaker->getZoomOutAction());
  menu->addAction(actionMaker->getNormalSizeAction());
  menu->addAction(actionMaker->getFitToWindowAction());
  return menu;
}

QMenu* MenuMaker::createHelpMenu(ActionMaker* actionMaker, UserInterface* userInterface) {
  QMenu* menu = new QMenu(QObject::tr("&Help"), userInterface);
  menu->addAction(actionMaker->getAboutAction());
  menu->addAction(actionMaker->getAboutQtAction());
  return menu;
}

QMenu* MenuMaker::createOperationMenu(ActionMaker* actionMaker, UserInterface* userInterface) {
  QMenu* menu = new QMenu(QObject::tr("&Operation"), userInterface);
  menu->addAction(actionMaker->getBlackAndWhiteAction());
  menu->addAction(actionMaker->getRescaleAction());
  return menu;
}

