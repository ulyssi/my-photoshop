#include <QMessageBox>
#include <QMenuBar>

#include "UserInterface.hh"

/** Constructeurs et Destructeurs */
UserInterface::UserInterface() :
  m_imageViewer(new ImageViewer())
{
  createActions();
  createMenus();

  setCentralWidget(m_imageViewer);
  setWindowTitle(tr("MyPhotoShop"));
  resize(500, 400);
}

UserInterface::~UserInterface() {
  delete m_imageViewer;
}

/** Slots */
void UserInterface::open() {}

void UserInterface::save() {}

void UserInterface::undo() {}

void UserInterface::redo() {}

void UserInterface::zoomIn() {}

void UserInterface::zoomOut() {}

void UserInterface::normalSize() {}

void UserInterface::fitToWindow() {}

void UserInterface::blackAndWhite() {}

void UserInterface::rescale() {}

void UserInterface::about() {
  QMessageBox::about(this, tr("About MyPhotoShop"),
                     tr("Blablabla..."));
}

void UserInterface::exit() {}

/** Methodes internes */
void UserInterface::createActions() {
  m_openAct = new QAction(tr("&Open..."), this);
  m_openAct->setShortcut(tr("Ctrl+O"));
  connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));

  m_saveAct = new QAction(tr("&Save..."), this);
  m_saveAct->setShortcut(tr("Ctrl+S"));
  connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));

  m_undoAct = new QAction(tr("&Undo"), this);
  m_undoAct->setShortcut(tr("Ctrl+Z"));
  connect(m_undoAct, SIGNAL(triggered()), this, SLOT(undo()));
  
  m_redoAct = new QAction(tr("&Redo"), this);
  m_redoAct->setShortcut(tr("Ctrl+E"));
  connect(m_redoAct, SIGNAL(triggered()), this, SLOT(redo()));

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

  m_blackAndWhiteAct = new QAction(tr("&Black and White"), this);
  m_blackAndWhiteAct->setEnabled(false);
  m_blackAndWhiteAct->setCheckable(true);
  connect(m_blackAndWhiteAct, SIGNAL(triggered()), this, SLOT(blackAndWhite()));

  m_rescaleAct = new QAction(tr("&Rescale"), this);
  m_rescaleAct->setEnabled(false);
  m_rescaleAct->setCheckable(true);
  connect(m_rescaleAct, SIGNAL(triggered()), this, SLOT(rescale()));

  m_aboutAct = new QAction(tr("&About"), this);
  connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));
  
  m_aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(m_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  m_exitAct = new QAction(tr("E&xit"), this);
  m_exitAct->setShortcut(tr("Ctrl+Q"));
  connect(m_exitAct, SIGNAL(triggered()), this, SLOT(exit()));
}

void UserInterface::createMenus() {
  m_fileMenu = new QMenu(tr("&File"), this);
  m_fileMenu->addAction(m_openAct);
  m_fileMenu->addAction(m_saveAct);
  m_fileMenu->addSeparator();
  m_fileMenu->addAction(m_exitAct);

  m_editMenu = new QMenu(tr("&Edit"), this);
  m_editMenu->addAction(m_undoAct);
  m_editMenu->addAction(m_redoAct);

  m_operationMenu = new QMenu(tr("&Operation"), this);
  m_operationMenu->addAction(m_blackAndWhiteAct);
  m_operationMenu->addAction(m_rescaleAct);
  
  m_helpMenu = new QMenu(tr("&Help"), this);
  m_helpMenu->addAction(m_aboutAct);
  m_helpMenu->addAction(m_aboutQtAct);
  
  menuBar()->addMenu(m_fileMenu);
  menuBar()->addMenu(m_editMenu);
  menuBar()->addMenu(m_operationMenu);
  menuBar()->addMenu(m_helpMenu);
}

void UserInterface::updateActions() {
  m_openAct->setEnabled(false);
  m_saveAct->setEnabled(false);
  m_undoAct->setEnabled(false);
  m_redoAct->setEnabled(false);
  m_zoomInAct->setEnabled(false);
  m_zoomOutAct->setEnabled(false);
  m_normalSizeAct->setEnabled(false);
  m_exitAct->setEnabled(false);
}
