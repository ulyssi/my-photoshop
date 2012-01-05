#include "ToolBarMaker.hh"

#include <QObject>

#include "UserInterface.hh"
#include "ActionMaker.hh"





/** Constructeurs et destructeur */
ToolBarMaker::ToolBarMaker(ActionMaker* actionMaker, UserInterface* userInterface) :
  m_fileToolBar(createFileToolBar(actionMaker, userInterface)),
  m_editToolBar(createEditToolBar(actionMaker, userInterface)),
  m_viewToolBar(createViewToolBar(actionMaker, userInterface)),
  m_helpToolBar(createHelpToolBar(actionMaker, userInterface)),
  m_operationToolBar(createOperationToolBar(actionMaker, userInterface))
{}

ToolBarMaker::~ToolBarMaker() {}


/** Accesseurs */
QToolBar* ToolBarMaker::getFileToolBar() const { return m_fileToolBar; }
QToolBar* ToolBarMaker::getEditToolBar() const { return m_editToolBar; }
QToolBar* ToolBarMaker::getViewToolBar() const { return m_viewToolBar; }
QToolBar* ToolBarMaker::getHelpToolBar() const { return m_helpToolBar; }
QToolBar* ToolBarMaker::getOperationToolBar() const { return m_operationToolBar; }


/** Methodes internes */
QToolBar* ToolBarMaker::createFileToolBar(ActionMaker* actionMaker, UserInterface* userInterface) {
  QToolBar* toolBar = new QToolBar(QObject::tr("&File"), userInterface);
  toolBar->addAction(actionMaker->getOpenAction());
  toolBar->addAction(actionMaker->getSaveAction());
  toolBar->addSeparator();
  toolBar->addAction(actionMaker->getExitAction());
  return toolBar;
}

QToolBar* ToolBarMaker::createEditToolBar(ActionMaker* actionMaker, UserInterface* userInterface) {
  QToolBar* toolBar = new QToolBar(QObject::tr("&Edit"), userInterface);
  toolBar->addAction(actionMaker->getUndoAction());
  toolBar->addAction(actionMaker->getRedoAction());
  return toolBar;
}

QToolBar* ToolBarMaker::createViewToolBar(ActionMaker* actionMaker, UserInterface* userInterface) {
  QToolBar* toolBar = new QToolBar(QObject::tr("&View"), userInterface);
  toolBar->addAction(actionMaker->getZoomInAction());
  toolBar->addAction(actionMaker->getZoomOutAction());
  toolBar->addAction(actionMaker->getNormalSizeAction());
  toolBar->addAction(actionMaker->getFitToWindowAction());
  return toolBar;
}

QToolBar* ToolBarMaker::createHelpToolBar(ActionMaker* actionMaker, UserInterface* userInterface) {
  QToolBar* toolBar = new QToolBar(QObject::tr("&Help"), userInterface);
  toolBar->addAction(actionMaker->getAboutAction());
  toolBar->addAction(actionMaker->getAboutQtAction());
  return toolBar;
}

QToolBar* ToolBarMaker::createOperationToolBar(ActionMaker* actionMaker, UserInterface* userInterface) {
  QToolBar* toolBar = new QToolBar(QObject::tr("&Operation"), userInterface);
  toolBar->addAction(actionMaker->getBlackAndWhiteAction());
  toolBar->addAction(actionMaker->getRescaleAction());
  return toolBar;
}

