#include "SelectionTool.hh"

#include <QPainter>
#include <QGraphicsItem>
#include <QColor>
SelectionTool::SelectionTool ( QGraphicsItem * parent):
  QGraphicsRectItem(parent)
{
  m_fontColor=new QColor(255,255,255,128);
  my_brush = new QBrush((const QColor&)*m_fontColor,Qt::SolidPattern); 
  my_borderPen = new QPen(Qt::DashDotLine);
}

SelectionTool::~SelectionTool()
{}

#include<iostream>
void SelectionTool::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget ) {
 
  painter->setPen((const QPen&)*my_borderPen);
  painter->setBrush((const QBrush& )*my_brush);
  
  painter->drawRect(rect());
  
  
}

