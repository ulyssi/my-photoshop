#ifndef _USERINTERFACE_HH_
#define _USERINTERFACE_HH_

#include <QMessageBox>
#include <QMenuBar>

#include "UserInterface.hh"

/** Constructeurs et Destructeurs */
UserInterface::UserInterface() :
  m_actionMaker(new ActionMaker(this)),
  m_menuMaker(new MenuMaker(this)),
  m_imageViewer(new ImageViewer())
{
  menuBar()->addMenu(m_menuMaker.getFileMenu());
  menuBar()->addMenu(m_menuMaker.getEditMenu());
  menuBar()->addMenu(m_menuMaker.getViewMenu());
  menuBar()->addMenu(m_menuMaker.getOperationMenu());
  menuBar()->addMenu(m_menuMaker.getHelpMenu());

  setCentralWidget(m_imageViewer);
  setWindowTitle(tr("MyPhotoShop"));
  resize(500, 400);
  
  m_actionMaker.updateActions();
}

UserInterface::~UserInterface() {
  delete m_imageViewer;
  delete m_menuMaker;
  delete m_imageViewer;
}


/** Accesseurs */
ActionMaker* getActionMaker() const { return m_actionMaker; }

#endif
