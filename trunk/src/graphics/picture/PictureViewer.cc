#include "PictureViewer.hh"

#include "Utils.hh"
#include "Picture.hh"


PictureViewer::PictureViewer(Picture* picture) {
  setPixmap(Utils::QPixmapFrom(picture));
}

PictureViewer::~PictureViewer() {}


/** Predicats */
// bool PictureViewer::isZoomInEnabled() { return scaleFactor < 3.0; }

// bool PictureViewer::isZoomOutEnabled() { return scaleFactor > 0.333; }


/** Accesseurs */


/** Methodes */
// void PictureViewer::zoomIn() { scaleImage(1.25); }

// void PictureViewer::zoomOut() { scaleImage(0.8); }

// void PictureViewer::normalSize() {
//   adjustSize();
//   m_scaleFactor = 1.0;
// }

// void PictureViewer::fitSize() {
//   scrollArea->setWidgetResizable(fitToWindow);
// }


/** Methodes internes */
// void PictureViewer::scaleImage(double scaleFactor) {
//   m_scaleFactor *= scaleFactor;
//   imageLabel->resize(m_scaleFactor * pixmap()->size());

//   adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
//   adjustScrollBar(scrollArea->verticalScrollBar(), factor);
// }
