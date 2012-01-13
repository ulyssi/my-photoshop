#include "PictureArea.hh"


PictureArea::PictureArea(PictureModifier* p):
  PictureViewer(p){
  m_rubberBand= new MRubberBand(QRubberBand::Rectangle,this);
}

PictureArea::~PictureArea(){}



#include  <iostream>
void PictureArea::mousePressEvent(QMouseEvent *event){
   m_origin = event->pos();
     if (!m_rubberBand)
         m_rubberBand = new MRubberBand(QRubberBand::Rectangle, this);
     m_rubberBand->setGeometry(QRect(m_origin, QSize()));
     m_rubberBand->show();

}

void PictureArea::mouseMoveEvent(QMouseEvent *event){
  m_rubberBand->setGeometry(QRect(m_origin, event->pos()).normalized());
}

void PictureArea::mouseReleaseEvent(QMouseEvent *event){
 
     // determine selection, for example using QRect::intersects()
     // and QRect::contains().
 }
