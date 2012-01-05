#include "ImageViewer.hh"

#include "Utils.hh"
#include "../model/Picture.hh"


ImageViewer::ImageViewer(Picture* picture) {
  m_imageLabel = new QLabel;
  // m_imageLabel->setBackgroundRole(QPalette::Base);
  // m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  // m_imageLabel->setScaledContents(true);
  
  m_imageLabel->setPixmap(Utils::QPixmapFrom(picture));

  // setBackgroundRole(QPalette::Dark);
  setWidget(m_imageLabel);
}

ImageViewer::~ImageViewer() {}

/** Methodes internes */
void ImageViewer::scaleImage(double factor) {}
