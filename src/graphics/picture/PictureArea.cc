#include "PictureArea.hh"
#include "PictureModifier.hh"
#include "PictureViewer.hh"

PictureArea::PictureArea(PictureModifier* p){
  m_Scene=new QGraphicsScene(this);
  m_Scene->setBackgroundBrush(QColor(255, 255, 255, 0));
  m_Scene->setForegroundBrush(QColor(255, 255, 255, 0));
  setScene(m_Scene);
  m_pictureViewer = new PictureViewer(p) ;
  m_proxy = m_Scene->addWidget(m_pictureViewer);
  setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    
  show();
}

PictureArea::~PictureArea(){}

void PictureArea::refresh(){
  m_pictureViewer->refresh();
  this->repaint();
  QSize size= m_pictureViewer->sizeHint();
  setSceneRect ( (qreal) 0, (qreal) 0, (qreal) size.width(), (qreal) size.height() );
  adjustSize();
} 
