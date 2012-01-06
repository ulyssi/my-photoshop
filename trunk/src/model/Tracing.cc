#include "Tracing.hh"


/** constructeur destructeur */
Tracing::Tracing(int width,int height, int offX, int offY) :
  Matrix<unsigned int>(width, height),
  m_index(0),
  m_offX(offX),
  m_offY(offY),
  m_alpha(0)
{}

Tracing::Tracing(QImage source, int offX, int offY) :
  Matrix<unsigned int>(source.width(), source.height()),
  m_index(0),
  m_offX(offX),
  m_offY(offY),
  m_alpha(0)
{
  for(int i = 0; i < getWidth();i++)
    for(int j = 0; j < getHeight();j++)
      setValue(i, j, (unsigned int)source.pixel(i,j));
}

Tracing::~Tracing() {}


/** accesseurs */
int Tracing::getIndex(){return m_index;}
  
int Tracing::getOffX(){return m_offX;}

int Tracing::getOffY(){return m_offY;}

int Tracing::getAlpha(){return m_alpha;}


/** mutateurs */

void Tracing::setIndex(int index){m_index = index;}

void Tracing::setOffX(int val){m_offX = val;}

void Tracing::setOffY(int val){ m_offY = val;}

void Tracing::setAlpha(int val){m_alpha = val;} 

/** predicat */
PixelMod::Type Tracing::getType(){
  PixelMod::Type result = PixelMod::BINARY;
  int i=0, j=0;
  while (result != PixelMod::COLOR && j < getHeight()) {
    result = PixelMod::max(result, PixelMod::getTypeFromRGB(getValue(i,j)));
    if (++i > getWidth()) { i = 0; j++; }
  } 
  return result;
}
