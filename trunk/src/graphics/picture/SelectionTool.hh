#ifndef _SELECTION_TOOL_HH
#define _SELECTION_TOOL_HH
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QRectF>

class SelectionTool: public QGraphicsRectItem { 
public:
  SelectionTool ( QGraphicsItem * parent = 0 );
  ~SelectionTool();
  /** override methode from QGraphicsItem**/
  void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
private :
  QColor* m_fontColor;
  QBrush* my_brush;
  QPen* my_borderPen;
};
#endif
