#ifndef _TRACING_HH_
#define _TRACING_HH_

#include <QString>
#include <QImage>

#include "Matrix.hh"
#include "PixelMod.hh"


class Tracing : public Matrix<unsigned int> {
private:
  QString m_name;
  int m_index;
  int m_offX;
  int m_offY;
  int m_alpha;


public:
  /*constructeur destructeur*/
  Tracing(int, int, int offX = 0, int offY = 0);
  Tracing(QImage, int offX = 0, int offY = 0);
  ~Tracing();
  
  /*accesseurs*/
  int getIndex();
  int getOffX();
  int getOffY();
  int getAlpha(); 
  PixelMod::Type getType();
  
  /*mutateurs*/
  void setIndex(int);
  void setOffX(int);
  void setOffY(int);
  void setAlpha(int);


};

#endif
