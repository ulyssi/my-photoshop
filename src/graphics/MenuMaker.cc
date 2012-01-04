#include "MenuMaker.hh"

void MenuMaker::createFileMenu() {
  m_fileMenu = new QMenu(tr("&File"), this);
  m_fileMenu->addAction(m_openAct);
  m_fileMenu->addAction(m_saveAct);
  m_fileMenu->addSeparator();
  m_fileMenu->addAction(m_exitAct);
}

void MenuMaker::createEditMenu() {
  m_editMenu = new QMenu(tr("&Edit"), this);
  m_editMenu->addAction(m_undoAct);
  m_editMenu->addAction(m_redoAct);
}

void MenuMaker::createViewMenu() {

}

void MenuMaker::createOperationMenu() {
  m_operationMenu = new QMenu(tr("&Operation"), this);
  m_operationMenu->addAction(m_blackAndWhiteAct);
  m_operationMenu->addAction(m_rescaleAct);
}

void MenuMaker::createHelpMenu() {
  m_helpMenu = new QMenu(tr("&Help"), this);
  m_helpMenu->addAction(m_aboutAct);
  m_helpMenu->addAction(m_aboutQtAct);
}

void MenuMaker::createMenus() {


  
  
}
