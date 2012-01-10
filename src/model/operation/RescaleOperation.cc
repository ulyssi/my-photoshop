

#include "Tracing.hh"
#include "Matrix.hh"
#include <math.h>
#include <iostream>
#include "RescaleOperation.hh"
#include "PixelMod.hh"

  /** Constructeurs et destructeur */
RescaleOperation::RescaleOperation(int nX,int nY):
  m_nX(nX),
  m_nY(nY)
{}
RescaleOperation::~RescaleOperation(){}

  /** Methodes */
Tracing* RescaleOperation::doOperation(Tracing* tr){
  std::cout<<"rescaling to  "<<m_nX<<"x"<<m_nY<<std::endl;
    
  Matrix<unsigned int> *rslt= new Matrix<unsigned int>(m_nX,m_nY);
  double fX=double(tr->getWidth())/double(m_nX);
  double fY=double(tr->getHeight())/double(m_nY);
   int xfl,yfl,xcl,ycl;
   double fracX,fracY,ifracX,ifracY;
  unsigned int red,blue,green;
  unsigned int pix[4];
 
  /*
  unsigned int pix;
  for (int i = 0; i < rslt->getWidth(); i++)  
    for (int j = 0; j <rslt->getHeight(); j++){
      pix=tr->getValue(floor(double(i)*fX),floor(double(j)*fY));  
      rslt->setValue((int)i,(int)j,(unsigned int)pix);
      }*/
  
  for(int i=0;i<m_nX;i++)
    for(int j=0;j<m_nY;j++){
      xfl=(int)floor(double(i)*fX);
      yfl=(int)floor(double(j)*fY);

      xcl=xfl+1;
      ycl=yfl+1;

      if(xcl>=tr->getWidth())xcl=xfl;
      if(ycl>=tr->getHeight())ycl=yfl;

      pix[0]=tr->getValue(xfl,yfl);
      pix[1]=tr->getValue(xcl,yfl);
      pix[2]=tr->getValue(xfl,ycl);
      pix[3]=tr->getValue(xcl,ycl);

      fracX=double(i)*fX-double(xfl);
      fracY=double(j)*fY-double(yfl);
      ifracY=1.0-fracY;
      ifracX=1.0-fracX;
      
      red=(unsigned int) floor(((double(PixelMod::getRed(pix[0]))*ifracX)+
	   (double(PixelMod::getRed(pix[1]))*fracX))*ifracY+
	((double(PixelMod::getRed(pix[2]))*ifracX)+
	 (double(PixelMod::getRed(pix[3]))*fracX))*fracY);
   
     green=(unsigned int) floor(((double(PixelMod::getGreen(pix[0]))*ifracX)+
	   (double(PixelMod::getGreen(pix[1]))*fracX))*ifracY+
	((double(PixelMod::getGreen(pix[2]))*ifracX)+
	 (double(PixelMod::getGreen(pix[3]))*fracX))*fracY);

blue=(unsigned int) floor(((double(PixelMod::getBlue(pix[0]))*ifracX)+
	   (double(PixelMod::getBlue(pix[1]))*fracX))*ifracY+
	((double(PixelMod::getBlue(pix[2]))*ifracX)+
	 (double(PixelMod::getBlue(pix[3]))*fracX))*fracY);

      rslt->setValue(i,j,(0xff<<24)|(red<<16)|(green<<8)|(blue));
    }
  tr->setData(rslt);
  delete rslt;
  std::cout<<"rescale done\n"<<std::endl;
  return tr;
}

Operation* RescaleOperation::clone(){
  return NULL;
}





