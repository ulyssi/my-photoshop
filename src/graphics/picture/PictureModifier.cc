#include "PictureModifier.hh"

#include "UserInterface.hh"
#include "TracingManager.hh"
#include "PictureViewer.hh"
#include "Histogram.hh"
#include "Previewer.hh"
#include "Picture.hh"
#include "Matrix.hh"
#include "ToolBoxChooser.hh"
#include "AffineOperationChooser.hh"
#include "ConvolveOperationChooser.hh"
#include "ColorConvertOperationChooser.hh"
#include "PictureArea.hh"

/** Constructeurs et destructeur */
PictureModifier::PictureModifier(Picture* picture, UserInterface* userInterface) :
  TabPanel(userInterface),
  m_picture(picture),
  m_image(new QImage(m_picture->getWidth(), m_picture->getHeight(), QImage::Format_ARGB32))
{
  m_userInterface=userInterface;
  setTabName(m_picture->getName());
  refreshData();
  m_pictureArea = new PictureArea(this,userInterface);
  setWidget(m_pictureArea);
  refresh();
}

PictureModifier::~PictureModifier() {}


/** Accesseurs */
QImage* PictureModifier::getImage() { return m_image; }

Picture* PictureModifier::getPicture() { return m_picture;}

QClipboard* PictureModifier::getClipBoard(){return m_userInterface->getClipBoard();}

PictureArea * PictureModifier::getPictureArea(){return m_pictureArea;}

/** Mutateurs */
void PictureModifier::notifyCurrent() {
  getUserInterface()->getPreviewer()->setPictureModifier(this);
  getUserInterface()->getToolBoxChooser()->setPictureModifier(this);
  getUserInterface()->getAffineOperationChooser()->setPictureModifier(this);
  getUserInterface()->getConvolveOperationChooser()->setPictureModifier(this);
  getUserInterface()->getColorConvertOperationChooser()->setPictureModifier(this);
  getUserInterface()->getHistogram()->setPictureModifier(this);
  getUserInterface()->getTracingManager()->setPictureModifier(this);
  getUserInterface()->update();
}


/** Methodes */
Picture* PictureModifier::getSelectedPicture() { return getPicture(); }

void PictureModifier::refreshData() {
  Matrix<unsigned int>* pictureData = m_picture->getData();
  if (pictureData->getWidth() != m_image->width() || pictureData->getHeight() != m_image->height()) {
    delete m_image;
    m_image = new QImage(pictureData->getWidth(), pictureData->getHeight(), QImage::Format_ARGB32);
  }
  for (int i = 0; i < pictureData->getWidth(); i++)
    for (int j = 0; j < pictureData->getHeight(); j++)
      m_image->setPixel(i, j, (uint)pictureData->getValue(i, j));

}

void PictureModifier::refresh() {
  refreshData();
  m_pictureArea->refresh();
  getUserInterface()->getHistogram()->refresh();
  getUserInterface()->getPreviewer()->refresh();
  getUserInterface()->getTracingManager()->refresh();
  getUserInterface()->getToolBoxChooser()->refresh();

}

void PictureModifier::keyPressEvent(QKeyEvent* event){
  m_pictureArea->keyPressEvent(event);
} 

void PictureModifier::keyReleaseEvent ( QKeyEvent * event ) {
  m_pictureArea->keyReleaseEvent(event);
}



void PictureModifier::zoomIn(){
  m_pictureArea->zoomIn();
  refresh();
}
void PictureModifier::zoomOut(){
  m_pictureArea->zoomOut();
  refresh();
}  
void PictureModifier::normalSize(){
  m_pictureArea->normalSize();
  refresh();
}
void PictureModifier::fitToWindow(){
  m_pictureArea->fitToWindow();
  refresh();
}


void PictureModifier:: copy(){
  m_pictureArea->copy();
}		
void PictureModifier:: paste(){
  m_pictureArea->paste();
}
void PictureModifier:: cut(){
  m_pictureArea->cut();
  this->refresh();
}

void PictureModifier::crop(){
  m_pictureArea->crop();
  this->refresh();
}

bool PictureModifier::enableMove(){
  m_pictureArea->enableMove();
 
  return true;
}
void PictureModifier::disableMove(){
  m_pictureArea->disableMove();
}

bool PictureModifier::enableSelection(){
  m_pictureArea->enableSelection();
  return true;
}
void PictureModifier::disableSelection(){
  m_pictureArea->disableSelection();
}
