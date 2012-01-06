#ifndef _TRACING_HH_
#define _TRACING_HH_

#include <QString>
#include <QImage>
// ajouter un pointeur vers l'image parente
class Tracing{
private:
  QString m_name;
  int m_index;
  int m_width;
  int m_height;
  int m_offX;
  int m_offY;
  int m_alpha;
  unsigned int** m_data;

// ajouter l'index par défaut dans le constructeur de tracing
public:
  /*constructeur destructeur*/
  Tracing(int, int, int offX = 0, int offY = 0);
  Tracing(QImage, int offX = 0, int offY = 0);
  ~Tracing();
  
  /*accesseurs*/
  int getIndex();
  int getWidth();
  int getHeight();
  int getOffX();
  int getOffY();
  int getAlpha(); 
  unsigned int getPix(int x,int y);
  
  /*mutateurs*/
  //void setWidth(int);
  //void setHeight(int);
  void setIndex(int);
  void setOffX(int);
  void setOffY(int);
  void setAlpha(int);
  void setPix(int x,int y,unsigned int val);


};

#endif
