#include "ImageViewer.hh"

#include "Utils.hh"
#include "../model/Picture.hh"


ImageViewer::ImageViewer(Picture* picture) {
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

ImageViewer::~ImageViewer() {}

/** Methodes internes */
void ImageViewer::scaleImage(double factor) {}
