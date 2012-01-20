#include "SelectionTool.hh"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QColor>

SelectionTool::SelectionTool ( QGraphicsItem * parent):
  QGraphicsRectItem(parent){
  m_fontColor=new QColor(128,128,128,100);
  my_brush = new QBrush((const QColor&)*m_fontColor,Qt::SolidPattern); 
  my_borderPen = new QPen(Qt::DashDotLine);
}

SelectionTool::~SelectionTool()
{}

void SelectionTool::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget ) {
  painter->setPen((const QPen&)*my_borderPen);
  painter->setBrush((const QBrush& )*my_brush);
  painter->drawRect(rect());
}
