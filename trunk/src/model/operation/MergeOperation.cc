#include "MergeOperation.hh"
#include <iostream>
#include "Picture.hh"
#include "Tracing.hh"

using namespace std;
/** Constructeurs et destructeur */
MergeOperation::MergeOperation() {}

MergeOperation::~MergeOperation() {}


/** Methodes */
Picture* MergeOperation::doOperation(Picture* picture) {
  return picture;
}

Picture* MergeOperation::doOperation(Picture** pictureList, int nbPicture) {
  for (int i = 0; i < nbPicture; i++) pictureList[i] = doOperation(pictureList[i]);
  return pictureList[0];
}

Tracing* MergeOperation::doOperation(Tracing* tracing) { return tracing; }

Matrix<unsigned int>* MergeOperation::doOperation(std::vector<Tracing*> tracingList) {
  

  
 
  int width=0;
  int height=0;
  for(int id=0;id<tracingList.size();id++){ 
    Tracing * cTracing=tracingList[id];
    if(width<cTracing->getWidth()+cTracing->getOffX())
      width=cTracing->getWidth()+cTracing->getOffX();
    if(height<cTracing->getHeight()+cTracing->getOffY())
      height=cTracing->getHeight()+cTracing->getOffY();
  }
  Matrix<unsigned int>*rslt=new Matrix<unsigned int>(width,height);
  rslt->initialize(((unsigned int)0));
  for(int id=0;id<tracingList.size();id++){ 
    doOperation(rslt,tracingList[id]);
    
  }
  return rslt;
}

Operation* MergeOperation::clone() { return NULL; }


/** Methodes internes */
Matrix<unsigned int>* MergeOperation::doOperation(Matrix<unsigned int>*rslt, Tracing* t2) {
  unsigned int val=0;
  //:TODO prendre en compte les offsets 
  for(int i=0;i<t2->getWidth();i++)
    for(int j=0;j<t2->getHeight();j++){
      /**merge here*/
      int p1=rslt->getValue(i+t2->getOffX(),j+t2->getOffY());
      int p2=t2->getValue(i,j);
      float a1=getAlpha(p1,1);
      float a2=getAlpha(p2,t2->getAlpha());
      val=combineAlpha(a1,a2)|combineRed(p1,p2,a2)|combineGreen(p1,p2,a2)|combineBlue(p1,p2,a2);
      rslt->setValue(i+t2->getOffX(),j+t2->getOffY(),(unsigned int)(val)); 
      
      
      
    }
  return rslt;
 
}
