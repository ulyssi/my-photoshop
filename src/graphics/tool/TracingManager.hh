#ifndef _TRACING_MANAGER_HH_
#define _TRACING_MANAGER_HH_
#include "Tracing.hh"
#include <QLabel>
#include <QScrollArea>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <vector>

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
  
  void addSelected(int);
  
  void removeSelected(int);
  
  
  /**SLOTS*/
private slots:
  void add();
  void up();
  void down();
  void merge();
private:

 
  /** Attributs */
  PictureModifier* m_pictureModifier;
  QLabel * m_header;
  QHBoxLayout * m_foot;
  QVBoxLayout* m_vLayout;
  int m_lastIndex;
  std::vector<int>* m_selected;

  /**Methodes */
  void buildHead();
  void buildLine(Tracing *);
  void buildFoot();
  void initSpin(QSpinBox *);
  

};

class SignalManager:public QObject{ Q_OBJECT
  
public:
  SignalManager(Tracing *,PictureModifier*,TracingManager *);
  ~SignalManager();
 private slots: 
  void setAlpha(int);
  void setVisible(int);
  void setSelected(int);
private:
  /** attributs*/
  PictureModifier *m_pictureMod;
  Tracing *m_tracing;
  TracingManager *m_tracingManager;
  double m_V;
  double m_prevV;
  
};

#endif
