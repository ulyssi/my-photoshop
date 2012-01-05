#include "PictureViewer.hh"

#include "Utils.hh"
#include "Picture.hh"


PictureViewer::PictureViewer(Picture* picture) {
  // setPixmap(Utils::QPixmapFrom(picture));
  setPixmap(QPixmap::fromImage(QImage("image.jpg")));
  // m_imageLabel = new QLabel;
  // m_imageLabel->setBackgroundRole(QPalette::Base);
  // m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  // m_imageLabel->setPixmap(Utils::QPixmapFrom(picture));
  // m_imageLabel->setScaledContents(true);
  //m_imageLabel->adjustSize();
  // setBackgroundRole(QPalette::Dark);
  // setWidget(m_imageLabel);
 
}

PictureViewer::~PictureViewer() {}

/** Methodes internes */
void PictureViewer::scaleImage(double factor) {}
