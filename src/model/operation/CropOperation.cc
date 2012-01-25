#include "CropOperation.hh"
#include <iostream>
#include <vector>
#include <QImage>
#include "Picture.hh"
#include "Tracing.hh"
#include "MergeOperation.hh"

using namespace std;
/** Constructeurs et destructeur */
CropOperation::CropOperation() {}

CropOperation::~CropOperation() {}


/** Methodes */
void CropOperation::doOperation(Picture* picture,int x0,int y0, int x1,int y1) {
  vector<Tracing *>tracings = picture->getTracingList();
  vector<Tracing *>::iterator it= tracings.begin();
 
  Tracing * cTracing;
  while(it<tracings.end()){
    cTracing=(*it);
    if(cTracing->isSelected()){
      Tracing *tr=new Tracing(x1-x0,y1-y0,0,0,cTracing->getAlpha());
      tr->setSelected(true);
      tr->setVisible(cTracing->isVisible());
      for(int i=x0;i<x1;i++)
	for(int j=y0;j<y1;j++){
	  int xtr=i-cTracing->getOffX();
	  int ytr=j-cTracing->getOffY();
	  if(xtr>=0&&xtr<cTracing->getWidth() &&ytr>=0&&ytr<cTracing->getHeight()){
	    tr->setValue(i-x0,j-y0,cTracing->getValue(xtr,ytr));
	    
	  }
	  else
	    tr->setValue(i-x0,j-y0,(unsigned int)0x0);
	}
      int id=cTracing->getIndex();
      picture->removeTracing(id);
      picture->insertTracing(tr,id);
    }
    it++;
  }
  picture->refresh();
}








 

