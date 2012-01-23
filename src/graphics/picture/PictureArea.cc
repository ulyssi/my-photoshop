#include "PictureArea.hh"
#include "PictureModifier.hh"
#include "PictureViewer.hh"
#include "PictureModifier.hh"
#include "SelectionTool.hh"
#include "UserInterface.hh"

PictureArea::PictureArea(PictureModifier* p,UserInterface* userinterface){
  m_userInterface = userinterface;
  m_pictureModifier=p;
  m_Scene=new QGraphicsScene(this);
  m_Scene->setBackgroundBrush(QColor(128, 128, 128, 0));
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

/** Puclic Methodes**/

void PictureArea::refresh(){
  m_pictureViewer->refresh();
  this->repaint();
  setSceneRect ( (qreal) 0, (qreal) 0, (qreal) m_pictureViewer->width(), (qreal) m_pictureViewer->height() );
  resize(m_pictureViewer->width()+5,m_pictureViewer->height()+5);
} 

/** getters **/
PictureViewer* PictureArea::getPictureViewer(){
  return m_pictureViewer;
}


/** Private Methodes **/
void PictureArea::setDownCoordinate(QMouseEvent* event){
  down->setX(event->x());
  down->setY(event->y());
  if(down->x()>m_pictureViewer->width())
    down->setX(m_pictureViewer->width());
  else if (down->x()<0)
    down->setX(0);
  if(down->y()>m_pictureViewer->height())
    down->setY(m_pictureViewer->height());
  else if (down->y()<0)
    down->setY(0);
}

void PictureArea::setDownCoordinate(double x , double y){
  std::cout<<"down coordinate resize"<<y<<std::endl;
  down->setX(x);
  down->setY(y);
  if(double(down->x())>m_pictureViewer->width())
    down->setX(m_pictureViewer->width());
  else if (down->x()<0)
    down->setX(0);
  if(double(down->y())>m_pictureViewer->height())
    down->setY(m_pictureViewer->height());
  else if (down->y()<0)
    down->setY(0);
}

void PictureArea::setUpCoordinate(double x , double y){
  up->setX(x);
  up->setY(y);
  if(up->x()>m_pictureViewer->width())
    up->setX(m_pictureViewer->width());
  else if (up->x()<0)
    up->setX(0);
  if(up->y()>m_pictureViewer->height())
    up->setY(m_pictureViewer->height());
  else if (up->y()<0)
    up->setY(0);

}

void PictureArea::refreshCoordinate(double resize){
  refresh();
  this->resize(m_pictureViewer->width(),m_pictureViewer->height());
  setDownCoordinate(int(double(down->x())*resize),int(double(down->y())*resize));
  setUpCoordinate(int(double (up->x())*resize),int(double(up->y())*resize));
  setSelection();
  this->repaint();

}




void PictureArea::fitToWindow(){
  refreshCoordinate(m_pictureViewer->fitToWindow(parentWidget()->size()));
}
void PictureArea::zoomIn(){
  refreshCoordinate(m_pictureViewer->zoomIn());
}
void PictureArea::zoomOut(){
  refreshCoordinate(m_pictureViewer->zoomOut());
}
void PictureArea::normalSize(){
  refreshCoordinate(m_pictureViewer->normalSize());
}




void PictureArea::setSelection(){
  if(down->x()<up->x()&&down->y()<up->y())
    m_selectionTool->setRect(down->x(),down->y(),(up->x()-down->x()),(up->y()-down->y()));
  else if(down->x()<up->x())
    m_selectionTool->setRect(down->x(),up->y(),(up->x()-down->x()),(down->y()-up->y()));
  else if(down->y()<up->y())      
    m_selectionTool->setRect(up->x(),down->y(),(down->x()-up->x()),(up->y()-down->y()));
  else
    m_selectionTool->setRect(up->x(),up->y(),(down->x()-up->x()),(down->y()-up->y()));
}



/** Public Slots **/
void PictureArea::keyPressEvent ( QKeyEvent * event ){
  if (event->modifiers()==Qt::ControlModifier)
    ctrl= true;
}

void PictureArea::keyReleaseEvent ( QKeyEvent * event ) {
  ctrl= false;
}


void PictureArea::mouseDoubleClickEvent ( QMouseEvent * event ){
  QImage t =m_pictureViewer->getImage().copy(up->x(),up->y(),down->x()-up->x(),down->y()-up->y());
  m_userInterface->getClipBoard()->setImage(((const QImage&)t),QClipboard::Clipboard);
  //m_selectionTool->hide();
}
#include <iostream>
void PictureArea::mouseMoveEvent ( QMouseEvent * event ){
  if(cliked){
    setDownCoordinate(event);
    setSelection();
  }
}

void PictureArea::mousePressEvent ( QMouseEvent * event ){
  up->setX(event->x());
  up->setY(event->y());
  //m_selectionTool->show();
  cliked=true;
}
void PictureArea::mouseReleaseEvent ( QMouseEvent * event ){
  cliked=false;
 
}

void PictureArea::wheelEvent ( QWheelEvent * event ) {
  QGraphicsView::wheelEvent(event); 
  int numDegrees = event->delta() / 8;
  if(ctrl==true){  
    if (numDegrees>0)
      zoomIn();
    else
      zoomOut();
    refresh();
  }
}

#include <iostream>

void PictureArea::copy(){
  QImage image;
  if(up->x()<down->x()&&up->y()<down->y())
    image=m_pictureViewer->getImage().copy(up->x(),up->y(),down->x()-up->x(),down->y()-up->y());
  else if(up->x() > down->x()&& up->y()<down->y())
    image=m_pictureViewer->getImage().copy(down->x(),up->y(),up->x()-down->x(),down->y()-up->y());
  else if(up->x() < down->x() &&  up->y()>down->y())
    image=m_pictureViewer->getImage().copy(up->x(),down->y(),down->x()-up->x(),up->y()-down->y());
  else if(up->x()>down->x()&& up->y()>down->y()){
    image=m_pictureViewer->getImage().copy(down->x(),down->y(),up->x()-down->x(),up->y()-down->y());
  }
  m_userInterface->getClipBoard()->setImage(((const QImage&)image),QClipboard::Clipboard);
}	



void PictureArea::paste(){


}
void PictureArea::cut(){


}
