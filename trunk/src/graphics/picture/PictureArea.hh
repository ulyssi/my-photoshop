#ifndef _PICTURE_AREA_HH
#define _PICTURE_AREA_HH

#include <QRubberBand>
#include <QMouseEvent>
#include <QGraphicsScene>
class PictureModifier;
#include "MRubberBand.hh"
#include "PictureViewer.hh"

class PictureArea: public PictureViewer{ Q_OBJECT
public: 
  PictureArea(PictureModifier*);
  ~PictureArea();
  /** Override from Qwidget**/
  void  mousePressEvent(QMouseEvent *event);
  void  mouseMoveEvent(QMouseEvent *event);
  void  mouseReleaseEvent(QMouseEvent *event);

/** attributs **/
  MRubberBand* m_rubberBand;
  QPoint m_origin;


};

#endif
