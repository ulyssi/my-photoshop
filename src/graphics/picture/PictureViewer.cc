#include "PictureViewer.hh"

#include <QPixmap>
#include "PictureModifier.hh"


PictureViewer::PictureViewer(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier)
{
  refreshData();
  refresh();
}

PictureViewer::~PictureViewer() {}


/** Predicats */
// bool PictureViewer::isZoomInEnabled() { return scaleFactor < 3.0; }

// bool PictureViewer::isZoomOutEnabled() { return scaleFactor > 0.333; }


/** Accesseurs */

#include <iostream>
/** Methodes */
 void PictureViewer::zoomIn() { 
   m_qImage=m_qImage.scaled((int)m_qImage.width()*1.25,(int)m_qImage.height()*1.25);
   resize(m_qImage.width(), m_qImage.height());
   setPixmap(QPixmap::fromImage((const QImage&)(m_qImage)));
   tmp=true;
 }

// void PictureViewer::zoomOut() { m_pictureModifier.scaleImage(0.8); }

// void PictureViewer::normalSize() {
//   adjustSize();
//   m_scaleFactor = 1.0;
// }

// void PictureViewer::fitSize() {
//   scrollArea->setWidgetResizable(fitToWindow);
// }


void PictureViewer::refresh() {
  refreshData();
  std::cout << "refeshing cout"<<std::endl;
  resize(m_qImage.width(), m_qImage.height());
  setPixmap(QPixmap::fromImage((const QImage&)(m_qImage)));

}


void PictureViewer::refreshData(){
  m_qImage=m_pictureModifier->getImage()->scaled(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
}

/** Methodes internes */
// void PictureViewer::scaleImage(double scaleFactor) {
//   m_scaleFactor *= scaleFactor;
//   imageLabel->resize(m_scaleFactor * pixmap()->size());

//   adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
//   adjustScrollBar(scrollArea->verticalScrollBar(), factor);
// }
