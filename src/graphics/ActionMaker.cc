#include "ActionMaker.hh"

#include <QObject>
#include <QMessageBox>
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


/** Slots */
void ActionMaker::open() {}

void ActionMaker::save() {}

void ActionMaker::exit() {}


void ActionMaker::undo() {}

void ActionMaker::redo() {}


void ActionMaker::zoomIn() {}

void ActionMaker::zoomOut() {}

void ActionMaker::normalSize() {}

void ActionMaker::fitToWindow() {}


void ActionMaker::blackAndWhite() {}

void ActionMaker::rescale() {}


void ActionMaker::about() {
  QMessageBox::about((QWidget*)this, tr("About MyPhotoShop"), tr("Blablabla..."));
}


/** Methodes internes */
void ActionMaker::createFileAction() {
  m_openAct = new QAction(tr("&Open..."), this);
  m_openAct->setShortcut(tr("Ctrl+O"));
  connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));

  m_saveAct = new QAction(tr("&Save..."), this);
  m_saveAct->setShortcut(tr("Ctrl+S"));
  connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));

  m_exitAct = new QAction(tr("E&xit"), this);
  m_exitAct->setShortcut(tr("Ctrl+Q"));
  connect(m_exitAct, SIGNAL(triggered()), this, SLOT(exit()));
}

void ActionMaker::createEditAction() {
  m_undoAct = new QAction(tr("&Undo"), this);
  m_undoAct->setShortcut(tr("Ctrl+Z"));
  connect(m_undoAct, SIGNAL(triggered()), this, SLOT(undo()));
  
  m_redoAct = new QAction(tr("&Redo"), this);
  m_redoAct->setShortcut(tr("Ctrl+E"));
  connect(m_redoAct, SIGNAL(triggered()), this, SLOT(redo()));
}

void ActionMaker::createViewAction() {
  m_zoomInAct = new QAction(tr("Zoom &In"), this);
  m_zoomInAct->setShortcut(tr("Ctrl++"));
  m_zoomInAct->setEnabled(false);
  connect(m_zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
  
  m_zoomOutAct = new QAction(tr("Zoom &Out"), this);
  m_zoomOutAct->setShortcut(tr("Ctrl+-"));
  m_zoomOutAct->setEnabled(false);
  connect(m_zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
  
  m_normalSizeAct = new QAction(tr("&Normal Size"), this);
  m_normalSizeAct->setEnabled(false);
  connect(m_normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
  
  m_fitToWindowAct = new QAction(tr("&Fit to Window"), this);
  m_fitToWindowAct->setEnabled(false);
  m_fitToWindowAct->setCheckable(true);
  connect(m_fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
}

void ActionMaker::createOperationAction() {
  m_blackAndWhiteAct = new QAction(tr("&Black and White"), this);
  m_blackAndWhiteAct->setEnabled(false);
  m_blackAndWhiteAct->setCheckable(true);
  connect(m_blackAndWhiteAct, SIGNAL(triggered()), this, SLOT(blackAndWhite()));

  m_rescaleAct = new QAction(tr("&Rescale"), this);
  m_rescaleAct->setEnabled(false);
  m_rescaleAct->setCheckable(true);
  connect(m_rescaleAct, SIGNAL(triggered()), this, SLOT(rescale()));
}

void ActionMaker::createHelpAction() {
  m_aboutAct = new QAction(tr("&About"), this);
  connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));
  
  m_aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(m_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(QApplication::aboutQt()));
}
