#include "Utils.hh"


const QPixmap& Utils::QPixmapFrom(Picture* picture) {
  return QPixmap::fromImage(picture->getImage());
}
