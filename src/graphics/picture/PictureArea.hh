#ifndef _PICTURE_AREA_HH
#define _PICTURE_AREA_HH
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QPoint>
#include <QMouseEvent>

class PictureModifier;
class PictureViewer;
class SelectionTool;
class UserInterface;
class PictureArea: public QGraphicsView { Q_OBJECT
public: 
  PictureArea(PictureModifier*,UserInterface*);
  ~PictureArea();
  void refresh();
  /**getters**/
  PictureViewer* getPictureViewer();
  void fitToWindow();
  void zoomIn();
  void zoomOut();
  void normalSize();
  void copy();	
  void paste();
  void cut();
private:
  /**Attributes**/
  UserInterface* m_userInterface;
  PictureModifier* m_pictureModifier;
  QGraphicsScene *m_Scene;
  PictureViewer* m_pictureViewer;
  SelectionTool* m_selectionTool;
  QGraphicsProxyWidget* m_proxy;
  QPoint *up,*down;
  bool cliked;	
  bool ctrl;
  int m_numDegrees;
  
  /**Methodes **/
  void setDownCoordinate(double,double);
  void setUpCoordinate(double x , double y);
  void setDownCoordinate(QMouseEvent*);
  void setSelection();
  void refreshCoordinate(double);
				
public slots:
  /** SLOTS**/
  void 	keyPressEvent ( QKeyEvent * event );
  void 	keyReleaseEvent ( QKeyEvent * event );
  void 	mouseDoubleClickEvent ( QMouseEvent * event );
  void 	mouseMoveEvent ( QMouseEvent * event );
  void 	mousePressEvent ( QMouseEvent * event );
  void 	mouseReleaseEvent ( QMouseEvent * event );    
  void 	wheelEvent ( QWheelEvent * event );

};

#endif
