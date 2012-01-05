#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include "UserInterface.hh"
#include "ActionMaker.hh"
#include "MenuMaker.hh"
#include "ToolMaker.hh"
#include "PictureManager.hh"
#include "PictureModifier.hh"
#include "../model/Picture.hh"


/** Constructeurs et Destructeurs */
UserInterface::UserInterface() :
  m_actionMaker(new ActionMaker(this)),
  m_menuMaker(new MenuMaker(m_actionMaker, this)),
  m_toolMaker(new ToolMaker()),
  m_pictureManager(new PictureManager(this)),
  m_viewTabWidget(createTabWidget())
{
  menuBar()->addMenu(m_menuMaker->getFileMenu());
  menuBar()->addMenu(m_menuMaker->getEditMenu());
  menuBar()->addMenu(m_menuMaker->getViewMenu());
  menuBar()->addMenu(m_menuMaker->getOperationMenu());
  menuBar()->addMenu(m_menuMaker->getHelpMenu());

  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultColorChooser())));
  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultOperationChooser())));
  setCentralWidget(m_viewTabWidget);
  setWindowTitle(tr("MyPhotoShop"));
  resize(500, 400);
  
  m_actionMaker->updateActions();
}

UserInterface::~UserInterface() {
  delete m_pictureManager;
  delete m_menuMaker;
  delete m_actionMaker;
}


/** Slots */
void UserInterface::open() {
  QString t_fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.jpg)"));
  PictureModifier* modifier = new PictureModifier(new Picture(t_fileName), this);
  // m_pictureManager->addPictureModifier(modifier);	
  m_viewTabWidget->addTab((QWidget*)(modifier->getImageViewer()), t_fileName);	       
}

void UserInterface::save() {}
void UserInterface::exit() {}

void UserInterface::undo() {}
void UserInterface::redo() {}

void UserInterface::zoomIn() {}
void UserInterface::zoomOut() {}
void UserInterface::normalSize() {}
void UserInterface::fitToWindow() {}

void UserInterface::blackAndWhite() {}
void UserInterface::rescale() {}

void UserInterface::about(){
  QMessageBox::about(this, tr("About MyPhotoShop"), tr("Blablabla..."));
}


/** Methodes internes */
QTabWidget* UserInterface::createTabWidget() {
  QTabWidget* tabWidget = new QTabWidget(this);
  tabWidget->addTab(m_pictureManager, m_pictureManager->getTabName());
  return tabWidget;
}

QDockWidget* UserInterface::createDockWidget(QWidget* widget) {
  QDockWidget* dockWidget = new QDockWidget();
  dockWidget->setWidget(widget);
  return dockWidget;
}
