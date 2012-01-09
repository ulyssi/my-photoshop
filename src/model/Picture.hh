#ifndef _PICTURE_HH_
#define _PICTURE_HH_

#include <QString>
#include <QImage>
#include <vector>
#include <iostream>

#include "Matrix.hh"

class Tracing;

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
  std::vector<Tracing*>& getListTracing();
  Matrix<unsigned int>* getData();
 
  /** Methodes */
  void addTracing(Tracing*);
  void insertTracing(Tracing*, int);
  void removeTracing(int);
  void removeTracing(Tracing*);
  void refresh();
  
private:
  /** Methodes Chargement et Sauvegarde des QImages */
  QImage loadQImage(QString&);
  bool saveQImage(QString&, QImage);
  
  /** Attributs */
  QString m_path;
  QString m_name;
  Matrix<unsigned int>* m_data;
  std::vector<Tracing *> m_listTracing;
};

#endif
