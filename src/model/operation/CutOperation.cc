#include "CutOperation.hh"
#include <iostream>
#include <vector>
#include <QImage>
#include "Picture.hh"
#include "Tracing.hh"
#include "MergeOperation.hh"

using namespace std;
/** Constructeurs et destructeur */
CutOperation::CutOperation() {}

CutOperation::~CutOperation() {}


/** Methodes */
void CutOperation::doOperation(Picture* picture,int x0,int y0, int x1,int y1,QClipboard *clipboard) {
  vector<Tracing *>tracings = picture->getTracingList();
  vector<Tracing *>::iterator it= tracings.begin();
  vector<Tracing *>trForClipboard = vector<Tracing*>();
  std::cout<<x0<<" "<<x1<<" "<<y0<<" "<<y1<<std::endl;
  Tracing * cTracing;
  while(it<tracings.end()){
    cTracing=(*it);
    if(cTracing->isSelected()){
      Tracing *tr=new Tracing(x1-x0,y1-y0);
      for(int i=x0;i<x1;i++)
	for(int j=y0;j<y1;j++){
	  int xtr=i-cTracing->getOffX();
	  int ytr=j-cTracing->getOffY();
	  if(xtr>=0&&xtr<cTracing->getWidth() &&ytr>=0&&ytr<cTracing->getHeight()){
	    tr->setValue(i-x0,j-y0,cTracing->getValue(xtr,ytr));
	    cTracing->setValue(xtr,ytr,(unsigned int)0x0);
	  }
	  else
	    tr->setValue(i-x0,j-y0,(unsigned int)0x0);
      }
      if(trForClipboard.empty())
	trForClipboard.reserve(1);
      trForClipboard.push_back(tr);
    }
    it++;
  }
  MergeOperation *mo=new MergeOperation();
  Matrix<unsigned int>*tmp= mo->doOperation(trForClipboard);
  QImage img=QImage(tmp->getWidth(),tmp->getHeight(),QImage::Format_ARGB32);
  cout<<"tmmp:"<<tmp->getWidth()<<"x"<<tmp->getHeight()<<endl;
  for(int i=0;i<tmp->getWidth();i++)
    for(int j=0;j<tmp->getHeight();j++){
      img.setPixel(i,j,(uint) tmp->getValue(i,j));

    }
  clipboard->setImage(img);
  

  
}






/** Methodes internes */

 

