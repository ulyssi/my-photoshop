#include "UserInterface.hh"


/** Methodes internes */
void UserInterface::createToolBar() {
  createFileToolBar();
  createEditToolBar();
  createViewToolBar();
  createHelpToolBar();
  createOperationToolBar();
}

QToolBar* UserInterface::createFileToolBar() {
  m_fileToolBar = new QToolBar(tr("&File"), this);
  m_fileToolBar->addAction(actionMaker->getOpenAction());
  m_fileToolBar->addAction(actionMaker->getSaveAction());
  m_fileToolBar->addSeparator();
  m_fileToolBar->addAction(actionMaker->getExitAction());
  return m_fileToolBar;
}

QToolBar* UserInterface::createEditToolBar() {
  m_editToolBar = new QToolBar(tr("&Edit"), this);
  m_editToolBar->addAction(actionMaker->getUndoAction());
  m_editToolBar->addAction(actionMaker->getRedoAction());
  return m_editToolBar;
}

QToolBar* UserInterface::createViewToolBar() {
  m_viewToolBar = new QToolBar(tr("&View"), this);
  m_viewToolBar->addAction(actionMaker->getZoomInAction());
  m_viewToolBar->addAction(actionMaker->getZoomOutAction());
  m_viewToolBar->addAction(actionMaker->getNormalSizeAction());
  m_viewToolBar->addAction(actionMaker->getFitToWindowAction());
  return m_viewToolBar;
}

QToolBar* UserInterface::createHelpToolBar() {
  m_helpToolBar = new QToolBar(tr("&Help"), this);
  m_helpToolBar->addAction(actionMaker->getAboutAction());
  m_helpToolBar->addAction(actionMaker->getAboutQtAction());
  return m_helpToolBar;
}

QToolBar* UserInterface::createOperationToolBar() {
  m_operationToolBar = new QToolBar(tr("&Operation"), this);
  m_operationToolBar->addAction(actionMaker->getBlackAndWhiteAction());
  m_operationToolBar->addAction(actionMaker->getRescaleAction());
  return m_operationToolBar;
}


