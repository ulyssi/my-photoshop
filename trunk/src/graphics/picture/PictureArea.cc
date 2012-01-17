#include "PictureArea.hh"
#include "PictureModifier.hh"
#include "PictureViewer.hh"
#include "PictureModifier.hh"
#include "SelectionTool.hh"

PictureArea::PictureArea(PictureModifier* p){
  m_pictureModifier=p;
  m_Scene=new QGraphicsScene(this);
  m_Scene->setBackgroundBrush(QColor(128, 128, 128, 255));
  m_Scene->setForegroundBrush(QColor(255, 255, 255, 0));
  setScene(m_Scene);
  m_pictureViewer = new PictureViewer(p) ;
  m_proxy = m_Scene->addWidget(m_pictureViewer);
  m_selectionTool = new SelectionTool(m_proxy);
  setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  up = new QPoint(0,0);
  down = new QPoint(0,0);
  cliked=false;
  ctrl=false;
  show();
}

PictureArea::~PictureArea(){}

void PictureArea::refresh(){
  m_pictureViewer->refresh();
  this->repaint();
  QSize size= m_pictureViewer->sizeHint();
  setSceneRect ( (qreal) 0, (qreal) 0, (qreal) size.width(), (qreal) size.height() );
  resize(size.width(),size.height());
} 


#include <iostream>
void PictureArea::keyPressEvent ( QKeyEvent * event ){
  if (event->modifiers()==Qt::ControlModifier)
   ctrl= true;
   
}
void PictureArea::keyReleaseEvent ( QKeyEvent * event ) {

  if (event->modifiers()==Qt::ControlModifier)
    ctrl= false;
}
void PictureArea::mouseDoubleClickEvent ( QMouseEvent * event ){}

void PictureArea::mouseMoveEvent ( QMouseEvent * event ){
  if(cliked){
    //std::cout<<"mousemoved clicked"<<std::endl;
    down->setX(event->x());
    down->setY(event->y());
    if(down->x()<up->x()&&down->y()<up->y())
      m_selectionTool->setRect(down->x(),down->y(),(up->x()-down->x()),(up->y()-down->y()));
    else if(down->x()<up->x())
      m_selectionTool->setRect(down->x(),up->y(),(up->x()-down->x()),(down->y()-up->y()));
    else if(down->y()<up->y())
      m_selectionTool->setRect(up->x(),down->y(),(down->x()-up->x()),(up->y()-down->y()));
    else
      m_selectionTool->setRect(up->x(),up->y(),(down->x()-up->x()),(down->y()-up->y()));
  }
}



void PictureArea::mousePressEvent ( QMouseEvent * event ){
  //std::cout<<"mousepressed envent"<<std::endl;
  up->setX(event->x());
  up->setY(event->y());
  cliked=true;
  
}
void PictureArea::mouseReleaseEvent ( QMouseEvent * event ){
   cliked=false;
   //std::cout<<"mouserealsed"<<std::endl;
 
}

void PictureArea::wheelEvent ( QWheelEvent * event ){
  if(ctrl)
    {
        QSize size= m_pictureViewer->sizeHint();
	setSceneRect ( (qreal) 0, (qreal) 0, (qreal) size.width()*0.5, (qreal) size.height()*0.5 );
	resize(size.width(),size.height());
	//std::cout<<"ctrl+wheel"<<std::endl;
    }
}
