#include "Utils.hh"
#include <iostream>
//atention lle retour du Qpixmap se fait par copie... 
QPixmap Utils::QPixmapFrom(Picture* picture) {	
  return QPixmap::fromImage(picture->getImage());
}
