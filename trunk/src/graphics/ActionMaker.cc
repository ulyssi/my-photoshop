#include "ActionMaker.hh"

#include <QObject>
#include <QApplication>

#include "UserInterface.hh"

/** Constructeurs et destructeur */
ActionMaker::ActionMaker(UserInterface* userInterface) :
  m_userInterface(userInterface)
{
  createFileAction();
  createEditAction();
  createViewAction();
  createOperationAction();
  createHelpAction();
}

ActionMaker::~ActionMaker() {}

/** Accesseurs */
QAction* ActionMaker::getOpenAction() const { return m_openAct; }
QAction* ActionMaker::getSaveAction() const { return m_saveAct; }
QAction* ActionMaker::getExitAction() const { return m_exitAct; }

QAction* ActionMaker::getUndoAction() const { return m_undoAct; }
QAction* ActionMaker::getRedoAction() const { return m_redoAct; }

QAction* ActionMaker::getZoomInAction() const { return m_zoomInAct; }
QAction* ActionMaker::getZoomOutAction() const { return m_zoomOutAct; }
QAction* ActionMaker::getNormalSizeAction() const { return m_normalSizeAct; }
QAction* ActionMaker::getFitToWindowAction() const { return m_fitToWindowAct; }

QAction* ActionMaker::getBlackAndWhiteAction() const { return m_blackAndWhiteAct; }
QAction* ActionMaker::getRescaleAction() const { return m_rescaleAct; }

QAction* ActionMaker::getAboutAction() const { return m_aboutAct; }
QAction* ActionMaker::getAboutQtAction() const { return m_aboutQtAct; }

/** Methodes */
void ActionMaker::updateActions() {
  m_openAct->setEnabled(false);
  m_saveAct->setEnabled(false);
  m_exitAct->setEnabled(false);
  
  m_undoAct->setEnabled(false);
  m_redoAct->setEnabled(false);
  
  m_zoomInAct->setEnabled(false);
  m_zoomOutAct->setEnabled(false);
  m_normalSizeAct->setEnabled(false);
  m_fitToWindowAct->setEnabled(false);

  m_blackAndWhiteAct->setEnabled(false);
  m_rescaleAct->setEnabled(false);

  m_aboutAct->setEnabled(false);
  m_aboutQtAct->setEnabled(true);
}




/** Methodes internes */
void ActionMaker::createFileAction() {
  m_openAct = new QAction(tr("&Open..."), m_userInterface);
  m_openAct->setShortcut(tr("Ctrl+O"));
  connect(m_openAct, SIGNAL(triggered()),m_userInterface, SLOT(open()));

  m_saveAct = new QAction(tr("&Save..."), m_userInterface);
  m_saveAct->setShortcut(tr("Ctrl+S"));
  connect(m_saveAct, SIGNAL(triggered()), m_userInterface, SLOT(save()));

  m_exitAct = new QAction(tr("E&xit"), m_userInterface);
  m_exitAct->setShortcut(tr("Ctrl+Q"));
  connect(m_exitAct, SIGNAL(triggered()), m_userInterface, SLOT(exit()));
}

void ActionMaker::createEditAction() {
  m_undoAct = new QAction(tr("&Undo"), m_userInterface);
  m_undoAct->setShortcut(tr("Ctrl+Z"));
  connect(m_undoAct, SIGNAL(triggered()), m_userInterface, SLOT(undo()));
  
  m_redoAct = new QAction(tr("&Redo"), m_userInterface);
  m_redoAct->setShortcut(tr("Ctrl+E"));
  connect(m_redoAct, SIGNAL(triggered()), m_userInterface, SLOT(redo()));
}

void ActionMaker::createViewAction() {
  m_zoomInAct = new QAction(tr("Zoom &In"), m_userInterface);
  m_zoomInAct->setShortcut(tr("Ctrl++"));
  m_zoomInAct->setEnabled(false);
  connect(m_zoomInAct, SIGNAL(triggered()), m_userInterface, SLOT(zoomIn()));
  
  m_zoomOutAct = new QAction(tr("Zoom &Out"), m_userInterface);
  m_zoomOutAct->setShortcut(tr("Ctrl+-"));
  m_zoomOutAct->setEnabled(false);
  connect(m_zoomOutAct, SIGNAL(triggered()), m_userInterface, SLOT(zoomOut()));
  
  m_normalSizeAct = new QAction(tr("&Normal Size"), m_userInterface);
  m_normalSizeAct->setEnabled(false);
  connect(m_normalSizeAct, SIGNAL(triggered()), m_userInterface, SLOT(normalSize()));
  
  m_fitToWindowAct = new QAction(tr("&Fit to Window"), m_userInterface);
  m_fitToWindowAct->setEnabled(false);
  m_fitToWindowAct->setCheckable(true);
  connect(m_fitToWindowAct, SIGNAL(triggered()), m_userInterface, SLOT(fitToWindow()));
}

void ActionMaker::createOperationAction() {
  m_blackAndWhiteAct = new QAction(tr("&Black and White"), m_userInterface);
  m_blackAndWhiteAct->setEnabled(false);
  m_blackAndWhiteAct->setCheckable(true);
  connect(m_blackAndWhiteAct, SIGNAL(triggered()), m_userInterface, SLOT(blackAndWhite()));

  m_rescaleAct = new QAction(tr("&Rescale"), m_userInterface);
  m_rescaleAct->setEnabled(false);
  m_rescaleAct->setCheckable(true);
  connect(m_rescaleAct, SIGNAL(triggered()), m_userInterface, SLOT(rescale()));
}

void ActionMaker::createHelpAction() {
  m_aboutAct = new QAction(tr("&About"), m_userInterface);
  connect(m_aboutAct, SIGNAL(triggered()), m_userInterface, SLOT(about()));
  
  m_aboutQtAct = new QAction(tr("About &Qt"), m_userInterface);
  connect(m_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
