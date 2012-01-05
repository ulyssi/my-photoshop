#include "Utils.hh"

//atention lle retour du Qpixmap se fait par copie... 
QPixmap Utils::QPixmapFrom(Picture* picture) {
  return QPixmap::fromImage(picture->getImage());
}
