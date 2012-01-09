#ifndef _MTabWidget_
#define _MTabWidget_

#include <QTabWidget>
#include <QTabBar>
#include <QWidget>
#include <QPushButton>
#include <QList>
class MPushButton;

class MTabWidget : public QTabWidget {Q_OBJECT
public :
  MTabWidget (QWidget * parent = 0 );
  ~MTabWidget ();
  /** Override public Methode */
  int addTab ( QWidget * page, const QString & label );
  int addTab ( QWidget * page, const QIcon & icon, const QString & label );
  /**override private methode from QTabWidget */
  QTabBar* tabBar();
public slots :
  void createAddTab();
  void myItemChangeSlot(int index);
  QPushButton* createCloseButton();
  void fermerOnglet(int);
private :
  QPushButton* m_pushButton; 
  QList <MPushButton*> m_listpushbutton;
};
#endif
