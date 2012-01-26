#include "Operation.hh"

#include "Picture.hh"
#include "Tracing.hh"
#include "MergeOperation.hh"
#include <iostream>

/** Constructeurs et destructeur */
// Mettre la picture en param

Operation::Operation() :
  m_operation(NULL),
  m_picture(NULL)
{}

Operation::Operation(Picture * picture) :
  m_operation(NULL),
  m_picture(picture)
{}

Operation::Operation(Operation* operation,Picture *picture) :
  m_operation(operation),
  m_picture(picture)
{}

Operation::~Operation() {
  std::vector<Tracing*>::iterator it=m_prev.begin();
  while(it<m_prev.end()){
    delete(*it);
    it++;
  }
  
  
}


/** Methodes */
Matrix<unsigned int>* Operation::updatePreview() {
   // lister les tracings selectionnée
   // appele la methode updateInternalPreview en changeant m_pictureData avec les données du calque courant
   // merger les Matrix<unsigned int> resultante sans oublié les calques visible mais non selectionné de l'image
   // retourné la preview correspondant a cette fusion
  std::vector<Tracing*> list=m_picture->getTracingList();
  std::vector<Tracing*>::iterator it=list.begin();
  while(it<list.end()){
    if(m_prev.empty())
      m_prev.reserve(1);
    m_pictureData = (Matrix<unsigned int>*)(*it);
    //m_previewData = new Matrix<unsigned int>(m_pictureData->getWidth(),m_pictureData->getHeight());
   
    //std::cout<<"burerum"<<m_previewData->getWidth()<<"x"<<m_previewData->getHeight();
    int normX=0;
    int normY=0;
    Tracing * tr;
    if((*it)->isSelected()){
      updateInternalPreview();
      normX=((*it)->getWidth()-m_previewData->getWidth())/2;
      normY=((*it)->getHeight()-m_previewData->getHeight())/2;
      tr=new Tracing(m_previewData);
      delete(m_previewData);   
    
     
     
    }
    else{
      tr=new Tracing(m_pictureData);
    }
    
    tr->setVisible((*it)->isVisible());
    tr->setSelected((*it)->isSelected());
    tr->setOffX((*it)->getOffX()+normX);
    tr->setOffY((*it)->getOffY()+normY);
     
    
    m_prev.push_back(tr);
     
    it++;
  }
  m_picture->normaliseOffs(m_prev);
  MergeOperation *mo = new MergeOperation();
  m_previewData= mo->doOperation(m_prev);
  /*it=list.begin();
  while(it<list.end()){
    if((*it)->isSelected())
      delete(*it);
      it++;*/
 
  return m_previewData;
}

  



   
Matrix<unsigned int>* Operation::updateInternalPreview(){std::cout<<"should not come here"<<std::endl;return NULL;}
Picture* Operation::applyInternalOperation(){std::cout<<"should not come here"<<std::endl;return NULL;}
   

Picture* Operation::applyOperation(){
  updatePreview(); 
  std::cout<<"applying1"<<std::endl;
  if(!m_prev.empty()){
    std::cout<<"applying"<<std::endl;
    std::vector<Tracing*> list=m_picture->getTracingList();
    std::vector<Tracing*>::iterator it=list.begin();
    std::vector<Tracing*>::iterator itsel=m_prev.begin();
    while(it<list.end()&&itsel<m_prev.end()){
      if((*it)->isSelected()){
	(*it)->setData((Matrix<unsigned int>*)(*itsel));
	(*it)->setOffX((*itsel)->getOffX());
	(*it)->setOffY((*itsel)->getOffY());
	(*it)->setVisible((*itsel)->isVisible());
	delete(*itsel);
      }
      it++;
      itsel++;
    }
    m_picture->normaliseOffs(list);
  }
 
  return m_picture;
}




Picture* Operation::applyOn(Picture* picture) {
  if (m_operation != NULL) picture = m_operation->applyOn(picture);
  return doOperation(picture);
}

Tracing* Operation::applyOn(Tracing* tracing) {
  if (m_operation != NULL) tracing = m_operation->applyOn(tracing);
  return tracing; //doOperation(tracing);
}

Picture* Operation::doOperation(Picture* picture) {
  Tracing* background = picture->getBackground();
  //doOperation(background);
  return picture;
}

//Picture* Operation::doOperation(Tracing * tr){return tr;}

// rgb2 = { r2, g2, b2, a2 } t2
// rgb1 = { r1, g1, b1, a1 } t1 

// rgb2 = { r2, g2, b2, (a2 / 255) * t2 = a2. }
// rgb1 = { r1, g1, b1, (a1 / 255) * t1 = a1. }

// rgb3 = { r1 * (1 - a2.) + r2 * a2., , , (a1. + a2. - a1. * a2.) * 255 } 

// rgbResult(rgb1, rgb2) = { r1 * (1 - a2.) + r2 * a2., , , (a1. + a2. - a1. * a2.) * 255 } 
