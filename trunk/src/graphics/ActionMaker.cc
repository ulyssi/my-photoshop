#include "ActionMaker.hh"

#include <QObject>
#include <QApplication>

#include "UserInterface.hh"


/** Constructeurs et destructeur */
ActionMaker::ActionMaker(UserInterface* userInterface) {
  createFileAction(userInterface);
  createEditAction(userInterface);
  createViewAction(userInterface);
  createOperationAction(userInterface);
  createHelpAction(userInterface);
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
  m_openAct->setEnabled(true);
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
void ActionMaker::createFileAction(UserInterface* userInterface) {
  m_openAct = new QAction(QObject::tr("&Open..."), userInterface);
  m_openAct->setShortcut(QObject::tr("Ctrl+O"));
  QObject::connect(m_openAct, SIGNAL(triggered()), userInterface, SLOT(open()));

  m_saveAct = new QAction(QObject::tr("&Save..."), userInterface);
  m_saveAct->setShortcut(QObject::tr("Ctrl+S"));
  QObject::connect(m_saveAct, SIGNAL(triggered()), userInterface, SLOT(save()));

  m_exitAct = new QAction(QObject::tr("E&xit"), userInterface);
  m_exitAct->setShortcut(QObject::tr("Ctrl+Q"));
  QObject::connect(m_exitAct, SIGNAL(triggered()), userInterface, SLOT(exit()));
}

void ActionMaker::createEditAction(UserInterface* userInterface) {
  m_undoAct = new QAction(QObject::tr("&Undo"), userInterface);
  m_undoAct->setShortcut(QObject::tr("Ctrl+Z"));
  QObject::connect(m_undoAct, SIGNAL(triggered()), userInterface, SLOT(undo()));
  
  m_redoAct = new QAction(QObject::tr("&Redo"), userInterface);
  m_redoAct->setShortcut(QObject::tr("Ctrl+E"));
  QObject::connect(m_redoAct, SIGNAL(triggered()), userInterface, SLOT(redo()));
}

void ActionMaker::createViewAction(UserInterface* userInterface) {
  m_zoomInAct = new QAction(QObject::tr("Zoom &In"), userInterface);
  m_zoomInAct->setShortcut(QObject::tr("Ctrl++"));
  m_zoomInAct->setEnabled(false);
  QObject::connect(m_zoomInAct, SIGNAL(triggered()), userInterface, SLOT(zoomIn()));
  
  m_zoomOutAct = new QAction(QObject::tr("Zoom &Out"), userInterface);
  m_zoomOutAct->setShortcut(QObject::tr("Ctrl+-"));
  m_zoomOutAct->setEnabled(false);
  QObject::connect(m_zoomOutAct, SIGNAL(triggered()), userInterface, SLOT(zoomOut()));
  
  m_normalSizeAct = new QAction(QObject::tr("&Normal Size"), userInterface);
  m_normalSizeAct->setEnabled(false);
  QObject::connect(m_normalSizeAct, SIGNAL(triggered()), userInterface, SLOT(normalSize()));
  
  m_fitToWindowAct = new QAction(QObject::tr("&Fit to Window"), userInterface);
  m_fitToWindowAct->setEnabled(false);
  QObject::connect(m_fitToWindowAct, SIGNAL(triggered()), userInterface, SLOT(fitToWindow()));
}

void ActionMaker::createOperationAction(UserInterface* userInterface) {
  m_blackAndWhiteAct = new QAction(QObject::tr("&Black and White"), userInterface);
  m_blackAndWhiteAct->setEnabled(false);
  QObject::connect(m_blackAndWhiteAct, SIGNAL(triggered()), userInterface, SLOT(blackAndWhite()));

  m_rescaleAct = new QAction(QObject::tr("&Rescale"), userInterface);
  m_rescaleAct->setEnabled(false);
  QObject::connect(m_rescaleAct, SIGNAL(triggered()), userInterface, SLOT(rescale()));
}

void ActionMaker::createHelpAction(UserInterface* userInterface) {
  m_aboutAct = new QAction(QObject::tr("&About"), userInterface);
  QObject::connect(m_aboutAct, SIGNAL(triggered()), userInterface, SLOT(about()));
  
  m_aboutQtAct = new QAction(QObject::tr("About &Qt"), userInterface);
  QObject::connect(m_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
