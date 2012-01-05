/** Slots */
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QListIterator>
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
  t_fileDialog->setFileMode(QFileDialog::ExistingFiles);
  QStringList fileNames;
  if (t_fileDialog->exec())
    fileNames = t_fileDialog->selectedFiles();
  t_fileDialog->setNameFilterDetailsVisible(true);
  QListIterator <QString> t_listIterator (fileNames);
  QString t_path ; 
  while (t_listIterator.hasNext()){
    t_path =t_listIterator.next();
    PictureModifier* modifier = new PictureModifier(new Picture(t_path), this);
    m_pictureManager->addPictureModifier(modifier);	
    QString f_name =t_path.right(t_path.lastIndexOf("/"));
    m_viewTabWidget->addTab((QWidget*)(modifier->getPictureArea()),f_name);
  }
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
