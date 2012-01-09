#include "UserInterface.hh"

#include <QMessageBox>
#include <QFileDialog>
#include <QListIterator>
#include <QApplication>

#include "Picture.hh"
#include "PictureManager.hh"
#include "PictureModifier.hh"
//#include "MTabWidget.hh"


/** Slots */
void UserInterface::open() {
  
  // ouverture QFileDialog
  QFileDialog *t_fileDialog = new QFileDialog(this, windowFlags());
  t_fileDialog->setViewMode(QFileDialog::List);
  t_fileDialog->setNameFilter(tr("Images Files(*.jpg *.png *.pnn);; All Files (*)"));
  t_fileDialog->setFileMode(QFileDialog::ExistingFiles);
  QStringList fileNames;
  if (t_fileDialog->exec()) fileNames = t_fileDialog->selectedFiles();
  t_fileDialog->setNameFilterDetailsVisible(true);
  QListIterator <QString> t_listIterator (fileNames);
  while (t_listIterator.hasNext()){
    PictureModifier* modifier = new PictureModifier(new Picture(t_listIterator.next()), this);
    m_pictureManager->addPictureModifier(modifier);
    m_viewTabWidget->addTab((QWidget*)(modifier), modifier->getTabName());
  }
}


void UserInterface::save() {}
void UserInterface::close(int i){
  // penser a detruire les objets
  

}
void UserInterface::exit() {}

void UserInterface::undo() {}
void UserInterface::redo() {}

void UserInterface::zoomIn() {}
void UserInterface::zoomOut() {}
void UserInterface::normalSize() {}
void UserInterface::fitToWindow() {}

void UserInterface::binary() {}

void UserInterface::greyScale() {
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++) {
    application->setValue(i, 0, 0.30);
    application->setValue(i, 1, 0.59);
    application->setValue(i, 2, 0.11);
  }
  colorConvertOperation(application);
}

void UserInterface::rescale() {}

void UserInterface::colorConvertOperation(Matrix<double>* application) {
  
  // if (getCurrentTab()->isPicture()) {
  //   Picture* picture = getCurrentTab()->getPicture();

  //   Matrix* greyScale = new Matrix(3, 3);
  //   for (int i = 0; i < 3; i++) {
  //     greyScale->setValue(i, 0) = 0.30;
  //     greyScale->setValue(i, 1) = 0.59;
  //     greyScale->setValue(i, 2) = 0.11;
  //   }
  
  //   ColorConvertOperation* op = new ColorConvertOperation(greyScale);
  //   op->applyOn(picture);
    
  //   getCurrentTab()->refresh();
  // }
}

void UserInterface::convolveOperation(Matrix<double>* filter) {
}

void UserInterface::about(){
  QMessageBox::about(this, tr("About MyPhotoShop"), tr("Blablabla..."));
}


/** Methodes internes */
void UserInterface::updateActions() {
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

void UserInterface::createActions() {
  createFileAction();
  createEditAction();
  createViewAction();
  createOperationAction();
  createHelpAction();
}

void UserInterface::createFileAction() {
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

void UserInterface::createEditAction() {
  m_undoAct = new QAction(tr("&Undo"), this);
  m_undoAct->setShortcut(tr("Ctrl+Z"));
  connect(m_undoAct, SIGNAL(triggered()), this, SLOT(undo()));
  
  m_redoAct = new QAction(tr("&Redo"), this);
  m_redoAct->setShortcut(tr("Ctrl+E"));
  connect(m_redoAct, SIGNAL(triggered()), this, SLOT(redo()));
}

void UserInterface::createViewAction() {
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
  connect(m_fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
}

void UserInterface::createOperationAction() {
  m_blackAndWhiteAct = new QAction(tr("&Black and White"), this);
  m_blackAndWhiteAct->setEnabled(false);
  //  connect(m_blackAndWhiteAct, SIGNAL(triggered()), this, SLOT(blackAndWhite()));

  m_rescaleAct = new QAction(tr("&Rescale"), this);
  m_rescaleAct->setEnabled(false);
  connect(m_rescaleAct, SIGNAL(triggered()), this, SLOT(rescale()));
}

void UserInterface::createHelpAction() {
  m_aboutAct = new QAction(tr("&About"), this);
  connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));
  
  m_aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(m_aboutQtAct, SIGNAL(triggered()),m_QApplication, SLOT(aboutQt()));
}

