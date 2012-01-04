#include "ImageViewer.hh"

ImageViewer::ImageViewer() {
  m_imageLabel = new QLabel;
  m_imageLabel->setBackgroundRole(QPalette::Base);
  m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  m_imageLabel->setScaledContents(true);

  setBackgroundRole(QPalette::Dark);
  setWidget(m_imageLabel);
}

ImageViewer::~ImageViewer() {}

/** Methodes internes */
void ImageViewer::scaleImage(double factor) {}
