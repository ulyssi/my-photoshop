#include "PictureArea.hh"
#include "PictureModifier.hh"
#include "PictureViewer.hh"
#include "PictureModifier.hh"
#include "SelectionTool.hh"
#include "UserInterface.hh"
#include "TracingManager.hh"
#include "CutOperation.hh"
#include "CopyOperation.hh"
#include "CropOperation.hh"
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
  m_fit=false;
  m_indSelect=false;
  m_indMove=false;
  m_selectionTool->hide();
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

/** Setter**/

void PictureArea::enableSelection(){
  m_selectionTool->show();
  m_indSelect=true;
}

void PictureArea::disableSelection(){
  m_selectionTool->hide();
  m_indSelect=false;
}

void PictureArea::enableMove(){
  setCursor(Qt::SizeAllCursor);
  m_indMove=true;
}

void PictureArea::disableMove(){
  setCursor(Qt::ArrowCursor);
  m_indMove=false;
}

void PictureArea::fitToWindow(){
  if (!m_fit){
    refreshCoordinate(m_pictureViewer->fitToWindow(parentWidget()->size()));
    m_fit=true;
  }
}
void PictureArea::normalSize(){
  m_fit=false;
  refreshCoordinate(m_pictureViewer->normalSize());
}

void PictureArea::zoomIn(){
  m_fit=false;
  down->setX(down->x()/m_pictureViewer->getScale());
  down->setY(down->y()/m_pictureViewer->getScale());
  up->setX(up->x()/m_pictureViewer->getScale());
  up->setY(up->y()/m_pictureViewer->getScale());
  m_pictureViewer->zoomIn();
  down->setX(down->x()*m_pictureViewer->getScale());
  down->setY(down->y()*m_pictureViewer->getScale());
  up->setX(up->x()*m_pictureViewer->getScale());
  up->setY(up->y()*m_pictureViewer->getScale());
  setSelection();
  refresh();
}
void PictureArea::zoomOut(){
  m_fit=false;
  
  down->setX(down->x()/m_pictureViewer->getScale());
  down->setY(down->y()/m_pictureViewer->getScale());
  up->setX(up->x()/m_pictureViewer->getScale());
  up->setY(up->y()/m_pictureViewer->getScale());
  m_pictureViewer->zoomOut();
  down->setX(down->x()*m_pictureViewer->getScale());
  down->setY(down->y()*m_pictureViewer->getScale());
  up->setX(up->x()*m_pictureViewer->getScale());
  up->setY(up->y()*m_pictureViewer->getScale());
  setSelection();
  refresh();
 

}

void PictureArea::copy(){
  CopyOperation* copy=new CopyOperation();
  QImage image;
  std::cout<<m_pictureViewer->getScale()<<std::endl;
  if(up->x()<down->x()&&up->y()<down->y())
    copy->copyOperation(m_pictureModifier->getPicture(), up->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), down->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), m_userInterface->getClipBoard());
  else if(up->x() > down->x()&& up->y()<down->y())
    copy->copyOperation(m_pictureModifier->getPicture(), down->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), up->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), m_userInterface->getClipBoard());
  else if(up->x() < down->x() &&  up->y()>down->y())
    copy->copyOperation(m_pictureModifier->getPicture(), up->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), down->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), m_userInterface->getClipBoard());
  else if(up->x()>down->x()&& up->y()>down->y())
    copy->copyOperation(m_pictureModifier->getPicture(), down->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), up->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), m_userInterface->getClipBoard());
  
}

void PictureArea::paste(){
  m_userInterface->getTracingManager()->paste();

}
#include <iostream>
void PictureArea::cut(){
  CutOperation* cut =new CutOperation();
  QImage image;
  if(up->x()<down->x()&&up->y()<down->y())
    cut->doOperation(m_pictureModifier->getPicture(), up->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), down->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), m_userInterface->getClipBoard());
  else if(up->x() > down->x()&& up->y()<down->y())
    cut->doOperation(m_pictureModifier->getPicture(), down->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), up->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), m_userInterface->getClipBoard());
  else if(up->x() < down->x() &&  up->y()>down->y())
    cut->doOperation(m_pictureModifier->getPicture(), up->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), down->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), m_userInterface->getClipBoard());
  else if(up->x()>down->x()&& up->y()>down->y())
    cut->doOperation(m_pictureModifier->getPicture(), down->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), up->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), m_userInterface->getClipBoard());
  m_pictureModifier->getPicture()->refresh();
  refresh();
}



void PictureArea::crop(){
  CropOperation* crop =new CropOperation;
  QImage image;
  if(up->x()<down->x()&&up->y()<down->y())
    crop->doOperation(m_pictureModifier->getPicture(), up->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), down->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale());
  else if(up->x() > down->x()&& up->y()<down->y())
    crop->doOperation(m_pictureModifier->getPicture(), down->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale(), up->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale());
  else if(up->x() < down->x() &&  up->y()>down->y())
    crop->doOperation(m_pictureModifier->getPicture(), up->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), down->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale());
  else if(up->x()>down->x()&& up->y()>down->y())
    crop->doOperation(m_pictureModifier->getPicture(), down->x()/m_pictureViewer->getScale(), down->y()/m_pictureViewer->getScale(), up->x()/m_pictureViewer->getScale(), up->y()/m_pictureViewer->getScale());
  m_selectionTool->hide();
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

void PictureArea::refreshCoordinate(double resize){
  refresh();
  this->resize(m_pictureViewer->width(),m_pictureViewer->height());
  setDownCoordinate(int(double(down->x())*resize),int(double(down->y())*resize));
  setUpCoordinate(int(double (up->x())*resize),int(double(up->y())*resize));
  setSelection();
  this->repaint();
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
  m_selectionTool->hide();
}

void PictureArea::mouseMoveEvent ( QMouseEvent * event ){
  
  if(event->x()<m_pictureViewer->width()&&event->y()<m_pictureViewer->height()){
    /** print the pixel info**/
    QString m_string;
    QString m_coord;
    m_string.append("x: ");
    m_coord.setNum(event->x());
    m_string=m_string+m_coord;
    m_string.append("  y: ");
    m_coord.setNum(event->y());
    m_string=m_string+m_coord;
    unsigned int pixel = m_pictureViewer->getImage().pixel(event->x(),event->y());
    m_string.append("   RGB :  R:");
    m_coord.setNum(PixelMod::getRed(pixel)); //int
    m_string=m_string+m_coord;
    m_string.append("  G:");
    m_coord.setNum(PixelMod::getGreen(pixel)); //int
    m_string=m_string+m_coord;
    m_string.append("  B:"); 
    m_coord.setNum(PixelMod::getBlue(pixel)); //int
    m_string=m_string+m_coord;
    m_string.append("  YUV :  Y:");
    m_coord.setNum(PixelMod::getLuma(pixel),'g',6); 
    m_string=m_string+m_coord;
    m_string.append("  U:");
    m_coord.setNum(PixelMod::getChrominanceU(pixel),'g',6);
    m_string=m_string+m_coord;
    m_string.append("  V:"); 
    m_coord.setNum(PixelMod::getChrominanceV(pixel),'g',6);
    m_string=m_string+m_coord;
    m_userInterface->print(m_string);
    
    if(cliked){
      setCursor(Qt::SizeFDiagCursor);
      setDownCoordinate(event);
      setSelection();
      m_selectionTool->show();
    }
    else if (m_indMove)
      setDownCoordinate(event);
  }
 
}

void PictureArea::mousePressEvent ( QMouseEvent * event ){
  down->setY(event->y());
  down->setX(event->x());
  
  if (m_indMove){
    up->setX(event->x());
    up->setY(event->y());
  }
  else if(m_indSelect){
    up->setX(event->x());
    up->setY(event->y());
    setSelection();
    m_selectionTool->show();
    cliked=true;
  }
}
void PictureArea::mouseReleaseEvent ( QMouseEvent * event ){
  if(m_indSelect){
    setCursor(Qt::ArrowCursor);
    cliked=false;
  }
  if (m_indMove)
    m_userInterface->getTracingManager()->move(down->x()-up->x(),down->y()-up->y());
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



