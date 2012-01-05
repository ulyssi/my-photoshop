#ifndef _PICTURE_HH_
#define _PICTURE_HH_
#include <QString>
#include <QImage>
#include <vector>
#include <iostream>
#include "Tracing.hh"
using namespace std;

class Picture {
  
public:

  /** Constructeurs et destructeur */
  Picture(QString);
  ~Picture();

  /** Accesseurs */
  QString getPath();
  QString getName();
  int getWidth();
  int getHeight();
  QImage& getImage();
  vector<Tracing*>& getListTracing();
  
  void setName(string);
  
private:
  /** Methodes Chargement et Sauvegarde des QImages */
  QImage loadQImage(QString&);
  bool saveQImage(QString&, QImage);
  /** Methodes de conversion QImage/format interne */
  
  /** Attributs */
  QString m_path;
  QString m_name;
  vector<Tracing *> m_listTracing;
  int m_width;
  int m_height;
  QImage m_image;
  
};

#endif
