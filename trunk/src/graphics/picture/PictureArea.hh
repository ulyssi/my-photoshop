#ifndef _PICTURE_AREA_HH
#define _PICTURE_AREA_HH


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
class PictureModifier;
class PictureViewer;


class PictureArea: public QGraphicsView { Q_OBJECT
public: 
  PictureArea(PictureModifier*);
  ~PictureArea();
  void refresh();
private:
  /**Attributes**/
  QGraphicsScene *m_Scene;
  PictureViewer* m_pictureViewer;
  QGraphicsRectItem* m_selectionTool;
  QGraphicsProxyWidget* m_proxy;
};

#endif
