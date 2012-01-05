#ifndef _TRACING_HH_
#define _TRACING_HH_

#include <QString>
#include <QImage>

class Tracing{
private:
  QString m_name;
  int m_width;
  int m_height;
  int m_offX;
  int m_offY;
  int m_alpha;
  unsigned int** m_data;
  

public:
  /*constructeur destructeur*/
  Tracing(int,int);
  Tracing(QImage);
  ~Tracing();
  
  /*accesseurs*/
  int getWidth();
  int getHeight();
  int getOffX();
  int getOffY();
  int getAlpha(); 
  unsigned int getPix(int x,int y);
  
  /*mutateurs*/
  //void setWidth(int);
  //void setHeight(int);
  void setOffX(int);
  void setOffY(int);
  void setAlpha(int);
  void setPix(int x,int y,unsigned int val);


};

#endif
