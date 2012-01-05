/** Slots */
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include "UserInterface.hh"
#include "ActionMaker.hh"
#include "MenuMaker.hh"
#include "ToolMaker.hh"
#include "PictureManager.hh"
#include "PictureModifier.hh"
#include "Picture.hh"


void UserInterface::open() {
  
  // ouverture QFileDialog
  QFileDialog *t_fileDialog = new QFileDialog(this, windowFlags());
  t_fileDialog->setViewMode(QFileDialog::List);
  t_fileDialog->setNameFilter(tr("Images Files(*.jpg *.png *.pnn);; All Files (*)"));
  t_fileDialog->setNameFilterDetailsVisible(true);
  QString t_fileName = t_fileDialog->getOpenFileName(this, tr("Open Image"));



  PictureModifier* modifier = new PictureModifier(new Picture(t_fileName), this);
  m_pictureManager->addPictureModifier(modifier);	
  m_viewTabWidget->addTab((QWidget*)(modifier->getPictureArea()), t_fileName);	       
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
