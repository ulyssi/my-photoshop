#include <Qstring>
#include <Qimage>

namespace FileManager{
  /*todo changer qimage vers format interne */
Public:
  Qimage loadQ( Qstring & path);
  void saveQ(Qstring & path, Qimage im);

  /*
  //conversion Qimage->structure interne:
  for(int i=0; i<image.height(); ++i){
    for(int j=0; j<image.width(); ++j){
      QRgb CouleurPoint = image.pixel(i,j);
      int alpha = QRgb::qAlpha(CouleurPoint); ???
      int qRed(CouleurPoint); ????
      int qGreen(CouleurPoint);
      int qBlue(CouleurPoint);
      //attribuer couleur structure
    }
  }

  //conversion structure interne -> Qimage
  
  //inutile de passer par des variables intermédiaire...
  length = ;//hauteur de l'image
  width = ; //largeur de l'image
  // création d'une nouvelle Qimage si necessaire sinon modif directement
   
  for(i=0; i<length; ++i){
    for(j=0; j<width; ++j){
      QRgb CouleurPoint = new QRgb(red, 
				   green, 
				   blue, 
				   alpha);
      image.setpixel(i,j,(unsigned int)CouleurPoint);
      delete(CouleurPoint);
    }
  }
  */

}
