#ifndef _TRACING_HH_
#define _TRACING_HH_

#include <QString>
#include <QImage>

#include "Matrix.hh"
#include "PixelMod.hh"


class Tracing : public Matrix<unsigned int> {

public:
  
  /* Constructeurs et destructeur */
  Tracing(int, int, int offX = 0, int offY = 0);
  Tracing(Matrix<unsigned int>*, int offX = 0, int offY = 0, float alpha = 1);
  ~Tracing();
  
  /** Accesseurs */
  int getIndex();
  int getOffX();
  int getOffY();
  float getAlpha(); 
  PixelMod::Type getType();
  
  /** Mutateurs */
  void setIndex(int);
  void setOffX(int);
  void setOffY(int);
  void setAlpha(float);

private:

  /** Attributs */
  QString m_name;
  int m_index;
  int m_offX;
  int m_offY;
  float m_alpha;

};

#endif
