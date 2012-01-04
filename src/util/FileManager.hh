#include <Qstring>
#include <Qimage>

namespace FileManager{
  /*todo changer qimage vers format interne */
Public:
  Qimage loadQ( Qstring & path);
  void saveQ(Qstring & path, Qimage im);

  /*  "conversion Qimage->structure interne:"
  
  for(int i=0; i<image.height(); ++i){
    for(int j=0; j<image.width(); ++j){
      QRgb CouleurPoint = image.pixel(i,j);
      int alpha = QRgb::qAlpha(CouleurPoint); ???
      int qRed(CouleurPoint); ????
      int qGreen(CouleurPoint);
      int qBlue(CouleurPoint);
    }
  }

  "conversion structure interne -> Qimage"
  "cré
  "pour chaque itération"
  
  */

}
