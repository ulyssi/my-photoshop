#include "PictureViewer.hh"

#include "Utils.hh"
#include "Picture.hh"


PictureViewer::PictureViewer(Picture* picture) {
  setPixmap(Utils::QPixmapFrom(picture));
}

PictureViewer::~PictureViewer() {}

/** Methodes internes */
void PictureViewer::scaleImage(double factor) {}
