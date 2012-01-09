#include "PictureViewer.hh"

#include "Utils.hh"
#include "Picture.hh"


PictureViewer::PictureViewer(Picture* picture) {
  // m_imageLabel->setBackgroundRole(QPalette::Base);
  // m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  setPixmap(Utils::QPixmapFrom(picture));
  // m_imageLabel->setScaledContents(true);
  //m_imageLabel->adjustSize();
  // setBackgroundRole(QPalette::Dark);
  // setWidget(m_imageLabel);
}

PictureViewer::~PictureViewer() {}

/** Methodes internes */
void PictureViewer::scaleImage(double factor) {}
