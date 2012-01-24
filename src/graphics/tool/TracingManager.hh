#ifndef _TRACING_MANAGER_HH_
#define _TRACING_MANAGER_HH_
#include "Tracing.hh"
#include <QLabel>
#include <QScrollArea>
#include <QCheckBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <vector>

class PictureModifier;
class SignalManager;
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
  void paste();
  void move(int,int);
  void addSelected(int);
  
  void removeSelected(int);
  bool isSelected(int);
  void toGuiIcon(); 
  
  /**SLOTS*/
private slots:
  void add();
  void up();
  void down();
  void merge();
  void remove();
  void rename();
  void label_R(int);
private:

 
  /** Attributs */
  PictureModifier* m_pictureModifier;/*do not destroy*/
  QLabel * m_header;/*destroy*/
  QGridLayout * m_grid;/*destroy*/
  QHBoxLayout * m_foot;/*destroy*/
  QVBoxLayout* m_vLayout;/*destroy*/
  int m_lastIndex;
  int m_indexOfHead;
  int m_tobeSet;
  std::vector<int>* m_selected;/*destroy*/
  std::vector<SignalManager *>*m_signalManagers;/*destroy + SMs*/
  QPushButton* m_add;
  QPushButton* m_merge;
  QPushButton* m_up;
  QPushButton* m_down;
  QPushButton* m_remove;
  QPushButton* m_rename;
  /**Methodes internes*/

  void paintEvent(QPaintEvent*);
  void buildHead(int);
  void buildLine(Tracing *,int);
  void buildButtons();
 
  void deleteHead();
  void normaliseOffs(std::vector<Tracing*>);
  int * getminOffs(std::vector<Tracing*>);  
};

class SignalManager:public QObject{ Q_OBJECT
  
public:
  SignalManager(Tracing *,PictureModifier*,TracingManager *);
  ~SignalManager();
  /**Public Methods**/
  
 private slots: 
  void setAlpha(int);
  void setVisible(int);
  void setSelected(int);
  void setName_tmp(QString);
  void setName();
  
signals:
  void textSet(int id);

private:
  /** attributs*/
  PictureModifier *m_pictureMod;/*do not destroy*/
  Tracing *m_tracing;/*do not destroy*/
  TracingManager *m_tracingManager;/*do not destroy*/
  double m_V;
  double m_prevV;
  QString m_name;

  
};

#endif
