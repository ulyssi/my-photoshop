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

 Tracing* MergeOperation::doOperation(std::vector<Tracing*> tracingList) {
   
   Tracing * t1=tracingList[0];
   
   Tracing * tmp=NULL;
   for(int id=1;id<tracingList.size();id++){ 
     t1=doOperation(t1,tracingList[id]);
     if(tmp!=NULL)
       delete tmp;
     tmp=t1;
   }
   return t1;
 }

Operation* MergeOperation::clone() { return NULL; }


/** Methodes internes */
Tracing* MergeOperation::doOperation(Tracing* t1, Tracing* t2) {
 
  Tracing *rslt=new Tracing((t1->getWidth()>t2->getWidth())?(t1->getWidth()) : (t2->getWidth()),(t1->getHeight()>t2->getHeight())?(t1->getHeight()) : (t2->getHeight()));
  
unsigned int val=0;
//:TODO prendre en compte les offsets 
  for(int i=0;i<rslt->getWidth();i++)
    for(int j=0;j<rslt->getHeight();j++){
      if(i<t1->getWidth()&& j<t1->getHeight()){
	if(i<t2->getWidth()&& j<t2->getHeight()){
	  /**merge here*/
	  int p1=t1->getValue(i,j);
	  int p2=t2->getValue(i,j);
	  float a1=getAlpha(p1,t1->getAlpha());
	  float a2=getAlpha(p2,t2->getAlpha());
	  val=combineAlpha(a1,a2)|combineRed(p1,p2,a2)|combineGreen(p1,p2,a2)|combineBlue(p1,p2,a2);

	}
	else{
	  val=t1->getValue(i,j);
	  /*todo normaliser la transparence*/
	}

      }
      else if(i<t2->getWidth()&& j<t2->getHeight()){
	  /*todo normaliser la transparence*/
	  val=t2->getValue(i,j);
	
      }
      else{
	val=0;
      }
      rslt->setValue(i,j,(unsigned int)val);
    }
  
  
  return rslt;
}
