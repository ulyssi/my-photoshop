#include "Tracing.hh"


/** constructeur destructeur */
Tracing::Tracing(int width, int height, int offX, int offY) :
  Matrix<unsigned int>(width, height),
  m_index(0),
  m_offX(offX),
  m_offY(offY),
  m_alpha(1.0),
  m_prevAlpha(1.0),
  m_name(),
  m_visible(true),
  m_selected(false)
{}

Tracing::Tracing(Matrix<unsigned int>* source, int offX, int offY, float alpha) :
  Matrix<unsigned int>(source),
  m_index(0),
  m_offX(offX),
  m_offY(offY),
  m_alpha(alpha),
  m_prevAlpha(1.0),
  m_name(),
  m_visible(true),
  m_selected(false)  
{}



Tracing::~Tracing() {}


/** accesseurs */
int Tracing::getIndex(){return m_index;}
  
int Tracing::getOffX(){return m_offX;}

int Tracing::getOffY(){return m_offY;}

float Tracing::getAlpha(){  return m_alpha;}

PixelMod::Type Tracing::getType(){
  PixelMod::Type result = PixelMod::BINARY;
  int i=0, j=0;
  while (result != PixelMod::COLOR && j < getHeight()) {
    result = PixelMod::max(result, PixelMod::getTypeFromRGB(getValue(i,j)));
    if (++i >= getWidth()) { i = 0; j++; }
  } 
  return result;
}
QString Tracing::getName(){return m_name;}

bool Tracing::isVisible(){return m_visible;}

bool Tracing::isSelected(){return m_selected;}

/** mutateurs */

void Tracing::setIndex(int index){m_index = index;}

void Tracing::setName(QString name){m_name=QString(name);}

void Tracing::setOffX(int val){m_offX = val;}

void Tracing::setOffY(int val){ m_offY = val;}

void Tracing::setAlpha(float val){
  m_prevAlpha=m_alpha;
  m_alpha = val;} 

void Tracing::resetAlpha(){ m_alpha=m_prevAlpha;}

void Tracing::setVisible(bool val){m_visible=val;}

void Tracing::setSelected(bool val){m_selected=val;}
