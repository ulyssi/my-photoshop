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
  std::vector<Tracing*>& getTracingList();
  Matrix<unsigned int>* getData();
  Tracing* getBackground();
 
  /** Methodes */
  void addTracing(Tracing*);
  void insertTracing(Tracing*, int);
  void removeTracing(int);
  void removeTracing(Tracing*);
  void swapTracing(int,int);
  void refresh();
  bool saveQImage(QString&, QImage);
  void normaliseOffs(std::vector<Tracing*>);
  int * getminOffs(std::vector<Tracing*>);    
private:

  /** Methodes Chargement et Sauvegarde des QImages */
  QImage loadQImage(QString&);
  
  /** Attributs */
  QString m_path;
  QString m_name;
  Matrix<unsigned int>* m_data;
  std::vector<Tracing*> m_tracingList;

};

#endif
