#include "PictureArea.hh"
#include "PictureModifier.hh"
#include "PictureViewer.hh"
#include "PictureModifier.hh"

PictureArea::PictureArea(PictureModifier* p){
  m_pictureModifier=p;
  m_Scene=new QGraphicsScene(this);
  m_Scene->setBackgroundBrush(QColor(128, 128, 128, 255));
  m_Scene->setForegroundBrush(QColor(255, 255, 255, 0));
  setScene(m_Scene);
  m_pictureViewer = new PictureViewer(p) ;
  m_proxy = m_Scene->addWidget(m_pictureViewer);
  m_selectionTool = new QGraphicsRectItem(m_proxy);
  setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  //m_Scene->add
  show();
}

PictureArea::~PictureArea(){}

void PictureArea::refresh(){
  m_pictureViewer->refresh();
  this->repaint();
  QSize size= m_pictureViewer->sizeHint();
  setSceneRect ( (qreal) 0, (qreal) 0, (qreal) size.width(), (qreal) size.height() );
  resize(size.width(),size.height());
  
  // m_pictureModifier->setFocus();
  // m_pictureModifier->ensureWidgetVisible(this);
  //m_pictureModifier->ensureVisible(size.height(),size.width());
} 
