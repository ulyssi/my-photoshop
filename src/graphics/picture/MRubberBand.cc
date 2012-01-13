#include "MRubberBand.hh"

#include <QPalette>
MRubberBand::MRubberBand(QRubberBand::Shape shape ,QWidget* widget):
QRubberBand(shape,widget)
{
  m_border_color = QColor(255, 255, 255,255);
  m_background_color = QColor(0, 0, 0,255);
  QPalette palette;
  palette.setBrush( QPalette::WindowText, QBrush( Qt::red ) );
  setPalette(palette); 
  setStyleSheet("selection-background-color: yellow");
  setAutoFillBackground (false);
  setWindowOpacity ( (qreal) 1.0 );
}

MRubberBand::~MRubberBand(){
}
#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
void MRubberBand::paintEvent( QPaintEvent* event ){
 
  QStylePainter painter(this);
  QStyleOptionFocusRect option;
  option.initFrom( this );
  painter.drawControl(QStyle::CE_FocusFrame, option);
  
  // QPen pen = QPen(m_background_color);
  //  //pen.setWidth(2);
  //  // pen.setStyle(Qt::DashLine);
  // QBrush brush = QBrush(m_background_color,Qt::DiagCrossPattern);
  // painter.begin(this);
 
  // painter.setBackgroundMode(Qt::OpaqueMode);
  // std::cout<<"backgroundMode"<<painter.backgroundMode()<<std::endl;
  // painter.setBackground(brush);
  // painter.setPen(pen);
  // //painter.setOpacity((qreal)1.0);
  // painter.setBrush(brush);
  painter.fillRect(event->rect(),m_background_color);

  // //  painter.drawRect(event->rect());
  // painter.end();
}

