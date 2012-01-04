#include <QMenuBar>
#include <QMessageBox>

#include "UserInterface.hh"
#include "ActionMaker.hh"
#include "MenuMaker.hh"
#include "PictureManager.hh"

/** Constructeurs et Destructeurs */
UserInterface::UserInterface() :
  m_actionMaker(new ActionMaker(this)),
  m_menuMaker(new MenuMaker(this)),
  m_pictureManager(new PictureManager(this))
{
  menuBar()->addMenu(m_menuMaker->getFileMenu());
  menuBar()->addMenu(m_menuMaker->getEditMenu());
  menuBar()->addMenu(m_menuMaker->getViewMenu());
  menuBar()->addMenu(m_menuMaker->getOperationMenu());
  menuBar()->addMenu(m_menuMaker->getHelpMenu());

  setCentralWidget(m_pictureManager);
  setWindowTitle(tr("MyPhotoShop"));
  resize(500, 400);
  
  m_actionMaker->updateActions();
}

UserInterface::~UserInterface() {
  delete m_pictureManager;
  delete m_menuMaker;
  delete m_actionMaker;
}


/** Accesseurs */
ActionMaker* UserInterface::getActionMaker() const { return m_actionMaker; }

/** Slots */
void UserInterface::open() {}

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
