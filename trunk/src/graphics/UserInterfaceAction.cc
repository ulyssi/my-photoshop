#include "UserInterface.hh"

#include <QMessageBox>
#include <QFileDialog>
#include <QListIterator>
#include <QApplication>


#include "Picture.hh"
#include "PictureManager.hh"
#include "PictureModifier.hh"
#include "TabWidget.hh"
#include "Histogram.hh"
#include "Operation.hh"
#include "ColorConvertOperation.hh"
#include "AffineTransformationOperation.hh"
#include "Tracing.hh"
#include "TracingManager.hh"


/** Slots */
void UserInterface::open() {
  QFileDialog *t_fileDialog = new QFileDialog(this, windowFlags());
  t_fileDialog->setViewMode(QFileDialog::List);
  t_fileDialog->setNameFilter(tr("Images Files(*.jpg *.jpeg *.bmp *.png *.ppm *.tiff* .xbm *.xpm);; All Files (*)"));
  t_fileDialog->setFileMode(QFileDialog::ExistingFiles);

  QStringList fileNames;
  if (t_fileDialog->exec()) fileNames = t_fileDialog->selectedFiles();
  t_fileDialog->setNameFilterDetailsVisible(true);

  QListIterator <QString> t_listIterator (fileNames);
  while (t_listIterator.hasNext()){
    PictureModifier* modifier = new PictureModifier(new Picture(t_listIterator.next()), this);
    m_pictureManager->addPictureModifier(modifier);
    m_viewTabWidget->addTab((TabPanel*)modifier);
  }
}

void UserInterface::save() {
  if(m_viewTabWidget->getTabPanel() != NULL){
  Picture* picture = m_viewTabWidget->getTabPanel()->getSelectedPicture();
  std::cout << m_viewTabWidget->getTabPanel()->getTabName().toStdString()<< std::endl;
  if(picture != 0){
    QString path = QFileDialog::getSaveFileName(this, 
						"Enregistrer le fichier", 
						picture->getPath() , 
						"All files *.* ;; Images () ;;Images *.bmp (*.bmp);; Images *.jpg(*.jpg);; Images *.jpeg(*.jpeg);; Images *.png(*.png);; Images *.ppm(*.ppm);; Images *.tiff(*.tiff);; Images *.xbm(*.xbm);; Images *.xpm(*.xpm)" );

    Matrix<unsigned int>* pictureData = picture->getData();
    QImage *m_image = new QImage(pictureData->getWidth(), pictureData->getHeight(), QImage::Format_ARGB32);
    for (int i = 0; i < pictureData->getWidth(); i++)
      for (int j = 0; j < pictureData->getHeight(); j++)
	m_image->setPixel(i, j, (uint)pictureData->getValue(i, j));
    picture->saveQImage(path, *m_image);
  }
  } 
}

void UserInterface::close(QWidget* q) {
  m_pictureManager->removePictureModifier((PictureModifier*) q);
}
void UserInterface::exit() {}

void UserInterface::undo() {}
void UserInterface::redo() {}


#include <iostream>
void UserInterface::copy(){m_viewTabWidget->getTabPanel()->copy();
}
void UserInterface::cut(){
  m_viewTabWidget->getTabPanel()->cut();
}
void UserInterface::paste(){
  m_viewTabWidget->getTabPanel()->paste();
}

void UserInterface::crop(){
  m_viewTabWidget->getTabPanel()->crop();
}

void UserInterface::select(){
  if(!m_selection->isChecked()){
    m_selection->setChecked(false);
    m_viewTabWidget->getTabPanel()->disableSelection();
  }
  else{
    if(m_move->isChecked()){
      m_move->setChecked(false);
      m_viewTabWidget->getTabPanel()->disableMove();
    }
    if(m_viewTabWidget->getTabPanel()->enableSelection())
      m_selection->setChecked(true);
    else
      m_selection->setChecked(false);
  }
  
}

void UserInterface::move(){
  if(!m_move->isChecked()){
    m_move->setChecked(false);
    m_viewTabWidget->getTabPanel()->disableMove();
  }
  else{
    if(m_selection->isChecked()){
      m_selection->setChecked(false);
      m_viewTabWidget->getTabPanel()->disableSelection();
    }
    if(m_viewTabWidget->getTabPanel()->enableMove())
      m_move->setChecked(true);
    else
      m_move->setChecked(false);
  }
}

void UserInterface::resetEditionTool(int index){
  // m_viewTabWidget->getTabPanel()->disableSelection();
  // m_selection->setChecked(false);
  // m_viewTabWidget->getTabPanel()->disableMove();
  // m_move->setChecked(false);

}

void UserInterface::zoomIn() {
  m_viewTabWidget->getTabPanel()->zoomIn();
}
void UserInterface::zoomOut() {
  m_viewTabWidget->getTabPanel()->zoomOut();
}
void UserInterface::normalSize() {
  m_viewTabWidget->getTabPanel()->normalSize();
}
void UserInterface::fitToWindow() {
  m_viewTabWidget->getTabPanel()->fitToWindow();
}

void UserInterface::binary() {}

void UserInterface::greyScale() {
  convolveOperation(ColorConvertOperation::createGreyScaleKernel());
}


void UserInterface::colorConvert() {
  colorConvertOperation(ColorConvertOperation::createSepiaKernel());
}

void UserInterface::changeGIMode(){
  
  if(m_guiMode->isChecked()){
    m_copy->setIcon(QPixmap("Icon/Copy.png"));
    m_cut->setIcon(QPixmap("Icon/Cut.png"));
    m_paste->setIcon(QPixmap("Icon/Paste.png"));
    m_openAct->setIcon(QPixmap("Icon/Open.png"));
    m_saveAct->setIcon(QPixmap("Icon/Save.png"));
    m_undoAct->setIcon(QPixmap("Icon/Undo.png"));
    m_redoAct->setIcon(QPixmap("Icon/Redo.png"));
    m_zoomInAct->setIcon(QPixmap("Icon/ZoomIn.png"));
    m_zoomOutAct->setIcon(QPixmap("Icon/ZoomOut.png"));
    m_normalSizeAct->setIcon(QPixmap("Icon/NormalSize.png"));
    m_fitToWindowAct->setIcon(QPixmap("Icon/FitToWindow.png"));
    m_selection->setIcon(QPixmap("Icon/Selection.png"));
    m_move->setIcon(QPixmap("Icon/Move.png"));
    m_crop->setIcon(QPixmap("Icon/Crop.png"));
  }
  else{
    m_copy->setIcon(QIcon());
    m_cut->setIcon(QIcon());
    m_paste->setIcon(QIcon());
    m_openAct->setIcon(QIcon());
    m_saveAct->setIcon(QIcon());
    m_undoAct->setIcon(QIcon());
    m_redoAct->setIcon(QIcon());
    m_zoomInAct->setIcon(QIcon());
    m_zoomOutAct->setIcon(QIcon());
    m_normalSizeAct->setIcon(QIcon());
    m_fitToWindowAct->setIcon(QIcon());
    m_selection->setIcon(QIcon());
    m_move->setIcon(QIcon());
    m_crop->setIcon(QIcon());
  }
  
}


void UserInterface::rescale() {
  TabPanel* panel = m_viewTabWidget->getTabPanel();
  Picture* picture = panel->getSelectedPicture();
  AffineTransformationOperation* op = new AffineTransformationOperation(picture);
  op->setRescale(0.5, 0.5);
  picture->getBackground()->setData(op->updatePreview());
  picture->refresh();
  panel->refresh();
}

void UserInterface::about() {
  QMessageBox::about(this, tr("About MyPhotoShop"), tr("Blablabla..."));
}


/** Methodes internes */
void UserInterface::colorConvertOperation(Matrix<double>* kernel) {
  TabPanel* panel = m_viewTabWidget->getTabPanel();
  Picture* picture = panel->getSelectedPicture();
  ColorConvertOperation* op = new ColorConvertOperation(picture);
  op->setKernel(kernel);
  picture = op->applyOperation();
  delete op;
  picture->refresh();
  panel->refresh();
}

void UserInterface::updateActions() {
  m_openAct->setEnabled(true);
  m_saveAct->setEnabled(true);
  m_exitAct->setEnabled(false);
  
  m_undoAct->setEnabled(false);
  m_redoAct->setEnabled(false);
  m_copy->setEnabled(true);
  m_cut->setEnabled(true);
  m_paste->setEnabled(true);
 
  m_zoomInAct->setEnabled(true);
  m_zoomOutAct->setEnabled(true);
  m_normalSizeAct->setEnabled(true);
  m_fitToWindowAct->setEnabled(true);

  m_increaseContrastAct->setEnabled(true);
  m_averageBlurAct->setEnabled(true);
  m_gaussianBlurAct->setEnabled(true);
  m_leftEdgeStrengtheningAct->setEnabled(true);
  m_edgeDetectionAct->setEnabled(true);
  m_repulsingAct->setEnabled(true);
  m_greyScaleAct->setEnabled(true);
  m_colorConvertAct->setEnabled(true);
  m_convolveAct->setEnabled(true);

  m_rescaleAct->setEnabled(true);

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

  m_copy=  new QAction(tr("&Copy"), this);
  m_copy->setShortcut(tr("Ctrl+C"));
 
  connect(m_copy, SIGNAL(triggered()), this, SLOT(copy()));

  m_paste=  new QAction(tr("&Paste"), this);
  m_paste->setShortcut(tr("Ctrl+V"));
  connect(m_paste, SIGNAL(triggered()), this, SLOT(paste()));

  m_cut= new QAction(tr("&Cut"), this);
  m_cut->setShortcut(tr("Ctrl+X"));
  connect(m_cut, SIGNAL(triggered()), this, SLOT(cut()));
  
  
  m_selection= new QAction(tr("&Selection"), this);
  m_selection->setShortcut(tr("Alt"));
  m_selection->setCheckable(true);
  connect(m_selection, SIGNAL(triggered()), this, SLOT(select()));
  
  m_move= new QAction(tr("&Move"), this);
  m_move->setShortcut(tr("Atl+S"));
  m_move->setCheckable(true);
  connect(m_move, SIGNAL(triggered()), this, SLOT(move()));
  
  m_crop= new QAction(tr("&Crop"), this);
  m_crop->setShortcut(tr("Ctrl+Q"));
  connect(m_crop, SIGNAL(triggered()), this, SLOT(crop()));
  

  

  
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

  m_previewerAct = new QAction(tr("Previewer"), this);
  m_previewerAct->setCheckable(true);
  m_previewerAct->setChecked(true);
  connect(m_previewerAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));
  
  m_histogramAct = new QAction(tr("Histogram"), this);
  m_histogramAct->setCheckable(true);
  m_histogramAct->setChecked(true);
  connect(m_histogramAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));

  m_colorChooserAct = new QAction(tr("ColorChooser"), this);
  m_colorChooserAct->setCheckable(true);
  m_colorChooserAct->setChecked(true);
  connect(m_colorChooserAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));

  m_toolBoxChooserAct = new QAction(tr("ToolBoxChooser"), this);
  m_toolBoxChooserAct->setCheckable(true);
  m_toolBoxChooserAct->setChecked(true);
  connect(m_toolBoxChooserAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));

  m_tracingManagerAct = new QAction(tr("TracingManager"), this);
  m_tracingManagerAct->setCheckable(true);
  m_tracingManagerAct->setChecked(true);
  connect(m_tracingManagerAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));

  m_affineOperationAct = new QAction(tr("AffineOperation"), this);
  m_affineOperationAct->setCheckable(true);
  m_affineOperationAct->setChecked(true);
  connect(m_affineOperationAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));

  m_convolveOperationAct = new QAction(tr("ConvolveOperation"), this);
  m_convolveOperationAct->setCheckable(true);
  m_convolveOperationAct->setChecked(true);
  connect(m_convolveOperationAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));

  m_algebricOperationAct = new QAction(tr("AlgebricOperation"), this);
  m_algebricOperationAct->setCheckable(true);
  m_algebricOperationAct->setChecked(true);
  connect(m_algebricOperationAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));

  m_colorConvertOperationAct = new QAction(tr("ColorConvertOperation"), this);
  m_colorConvertOperationAct->setCheckable(true);
  m_colorConvertOperationAct->setChecked(true);
  connect(m_colorConvertOperationAct, SIGNAL(changed()), this, SLOT(updateToolBoxDocks()));
  
  m_guiMode= new QAction(tr("Graphical Interface Icon Mode"),this);
  m_guiMode->setCheckable(true);
  m_guiMode->setChecked(true);
  changeGIMode();
  connect(m_guiMode, SIGNAL(changed()), this, SLOT(changeGIMode()));
  
  
}

void UserInterface::createOperationAction() {
  createAffineTransformationOperationAction();
  createColorConvertOperationAction();
  createConvolveOperationAction();
  createAlgebricOperationAction();
}

void UserInterface::createAffineTransformationOperationAction() {
  m_rescaleAct = new QAction(tr("Rescale"), this);
  m_rescaleAct->setEnabled(false);
  connect(m_rescaleAct, SIGNAL(triggered()), this, SLOT(rescale()));
}

void UserInterface::createColorConvertOperationAction() {
  m_greyScaleAct = new QAction(tr("Grey Scale"), this);
  m_greyScaleAct->setEnabled(false);
  connect(m_greyScaleAct, SIGNAL(triggered()), this, SLOT(greyScale()));

  m_colorConvertAct = new QAction(tr("ColorConvert"), this);
  m_colorConvertAct->setEnabled(false);
  connect(m_colorConvertAct, SIGNAL(triggered()), this, SLOT(colorConvert()));
}

void UserInterface::createConvolveOperationAction() {
  m_increaseContrastAct = new QAction(tr("Increase Contrast"), this);
  m_increaseContrastAct->setEnabled(false);
  connect(m_increaseContrastAct, SIGNAL(triggered()), this, SLOT(increaseContrast()));

  m_averageBlurAct = new QAction(tr("Blur"), this);
  m_averageBlurAct->setEnabled(false);
  connect(m_averageBlurAct, SIGNAL(triggered()), this, SLOT(averageBlur()));

  m_gaussianBlurAct = new QAction(tr("Gaussian Blur"), this);
  m_gaussianBlurAct->setEnabled(false);
  connect(m_gaussianBlurAct, SIGNAL(triggered()), this, SLOT(gaussianBlur()));

  m_leftEdgeStrengtheningAct = new QAction(tr("Left Edge Strenghtening"), this);
  m_leftEdgeStrengtheningAct->setEnabled(false);
  connect(m_leftEdgeStrengtheningAct, SIGNAL(triggered()), this, SLOT(leftEdgeStrengthening()));

  m_edgeDetectionAct = new QAction(tr("Edge Detection"), this);
  m_edgeDetectionAct->setEnabled(false);
  connect(m_edgeDetectionAct, SIGNAL(triggered()), this, SLOT(edgeDetection()));

  m_repulsingAct = new QAction(tr("Repulsing"), this);
  m_repulsingAct->setEnabled(false);
  connect(m_repulsingAct, SIGNAL(triggered()), this, SLOT(repulsing()));

  m_convolveAct = new QAction(tr("Convolve"), this);
  m_convolveAct->setEnabled(false);
  connect(m_convolveAct, SIGNAL(triggered()), this, SLOT(convolve()));
}

void UserInterface::createAlgebricOperationAction() {}

void UserInterface::createHelpAction() {
  m_aboutAct = new QAction(tr("&About"), this);
  connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));
  
  m_aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(m_aboutQtAct, SIGNAL(triggered()),m_QApplication, SLOT(aboutQt()));
}
