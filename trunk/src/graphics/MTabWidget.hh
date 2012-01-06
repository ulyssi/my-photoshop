#ifndef _MTabWidget_
#define _MTabWidget_

#include <QTabWidget>
#include <QTabBar>
#include <QWidget>


class MTabWidget : public QTabWidget {Q_OBJECT
public :

  MTabWidget (QWidget * parent = 0 );
  ~MTabWidget ();
  //override private methode from QTabWidget
  QTabBar* tabBar();

public slots :

  void myItemChangeSlot(int index);

private :

};
#endif
