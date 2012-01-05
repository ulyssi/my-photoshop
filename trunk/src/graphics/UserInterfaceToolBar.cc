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
  m_fileToolBar->addAction(m_openAct);
  m_fileToolBar->addAction(m_saveAct);
  m_fileToolBar->addSeparator();
  m_fileToolBar->addAction(m_exitAct);
  return m_fileToolBar;
}

QToolBar* UserInterface::createEditToolBar() {
  m_editToolBar = new QToolBar(tr("&Edit"), this);
  m_editToolBar->addAction(m_undoAct);
  m_editToolBar->addAction(m_redoAct);
  return m_editToolBar;
}

QToolBar* UserInterface::createViewToolBar() {
  m_viewToolBar = new QToolBar(tr("&View"), this);
  m_viewToolBar->addAction(m_zoomInAct);
  m_viewToolBar->addAction(m_zoomOutAct);
  m_viewToolBar->addAction(m_normalSizeAct);
  m_viewToolBar->addAction(m_fitToWindowAct);
  return m_viewToolBar;
}

QToolBar* UserInterface::createHelpToolBar() {
  m_helpToolBar = new QToolBar(tr("&Help"), this);
  m_helpToolBar->addAction(m_aboutAct);
  m_helpToolBar->addAction(m_aboutQtAct);
  return m_helpToolBar;
}

QToolBar* UserInterface::createOperationToolBar() {
  m_operationToolBar = new QToolBar(tr("&Operation"), this);
  m_operationToolBar->addAction(m_blackAndWhiteAct);
  m_operationToolBar->addAction(m_rescaleAct);
  return m_operationToolBar;
}


