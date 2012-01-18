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

class PictureArea: public QGraphicsView { Q_OBJECT
public: 
  PictureArea(PictureModifier*);
  ~PictureArea();
  void refresh();
private:
  /**Attributes**/
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
  void setDownCoordinate(QMouseEvent*);
  void setSelection();
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
