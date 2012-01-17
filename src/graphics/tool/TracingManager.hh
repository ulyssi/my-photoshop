#ifndef _TRACING_MANAGER_HH_
#define _TRACING_MANAGER_HH_
#include "Tracing.hh"
#include <QLabel>
#include <QScrollArea>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>

class PictureModifier;

class TracingManager : public QScrollArea { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  TracingManager(PictureModifier* = NULL);
  ~TracingManager();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);

  /** Predicats */
  bool isEnabled();
  
  /** Methodes */
  void refresh();

private slots:
 void openTracing();

private:

 
  /** Attributs */
  PictureModifier* m_pictureModifier;
  QLabel * m_header;
  QPushButton * m_foot;
  QVBoxLayout* m_vLayout;
  int m_lastIndex;
 
  /**Methodes */
  void initSpin(QSpinBox *);
  
  
  

};

class SignalManager:public QObject{ Q_OBJECT
  
public:
  SignalManager(Tracing *,PictureModifier*);
  ~SignalManager();
 private slots: 
  void setAlpha(int);
private:
  /** attributs*/
  PictureModifier *m_pictureMod;
  Tracing *m_tracing;
};


#endif
