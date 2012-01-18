#include "PictureViewer.hh"
#include "PictureModifier.hh"


PictureViewer::PictureViewer(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier){ 
  refreshData();
  refresh();
  m_scaleFactor=1.0;
}

PictureViewer::~PictureViewer() {}

/** Methodes */
void PictureViewer::scaleImage(double scaleFactor){
  m_qImage=m_qImage.scaled((int)m_qImage.width()*scaleFactor,(int)m_qImage.height()*scaleFactor);
  resize(m_qImage.width(), m_qImage.height());
  setPixmap(QPixmap::fromImage((const QImage&)(m_qImage)));
}


void PictureViewer::zoomIn() { 
  m_scaleFactor=m_scaleFactor+0.25;
}

void PictureViewer::zoomOut() { 
  m_scaleFactor=m_scaleFactor-0.25;
}


void PictureViewer::refresh() {
  refreshData();
  scaleImage(m_scaleFactor);
}


void PictureViewer::refreshData(){
  m_qImage=m_pictureModifier->getImage()->scaled(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
  resize(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
}

/** Methodes internes */
// void PictureViewer::scaleImage(double scaleFactor) {
//   m_scaleFactor *= scaleFactor;
//   imageLabel->resize(m_scaleFactor * pixmap()->size());

//   adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
//   adjustScrollBar(scrollArea->verticalScrollBar(), factor);
// }

/** Predicats */
// bool PictureViewer::isZoomInEnabled() { return scaleFactor < 3.0; }

// bool PictureViewer::isZoomOutEnabled() { return scaleFactor > 0.333; }


/** Accesseurs */
// void PictureViewer::zoomOut() { m_pictureModifier.scaleImage(0.8); }

// void PictureViewer::normalSize() {
//   adjustSize();
//   m_scaleFactor = 1.0;
// }

// void PictureViewer::fitSize() {
//   scrollArea->setWidgetResizable(fitToWindow);
// }
