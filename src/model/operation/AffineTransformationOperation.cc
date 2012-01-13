#include "AffineTransformationOperation.hh"

#include "Picture.hh"
#include "PixelMod.hh"
#include <cmath>
#include <iostream>


/** Constructeurs et destructeur */
AffineTransformationOperation::AffineTransformationOperation(Picture* picture, Operation* operation) :
  m_operation(operation),
  m_picture(picture),
  m_scaleX(1.0),
  m_scaleY(1.0),
  m_alpha(0.0),
  m_x0(0.0),
  m_y0(0.0),
  m_cosAlpha(1.0),
  m_sinAlpha(0.0),
  m_pictureData(NULL),
  m_previewData(NULL),
  m_mapping(new Matrix<double>(3, 3)),
  m_mappingInv(new Matrix<double>(3, 3)),
  m_defaultColor(PixelMod::createRGB(0, 0, 0, PixelMod::TRANSLUCID))
{
  m_pictureData = m_picture->getData();
}

AffineTransformationOperation::~AffineTransformationOperation() {
  if (m_previewData != NULL) delete m_previewData;
  if (m_pictureData != NULL) delete m_pictureData;
  if (m_mappingInv != NULL) delete m_mappingInv;
  if (m_mapping != NULL) delete m_mapping;
}


/** Accesseurs */
Picture* AffineTransformationOperation::getPicture() { return m_picture; }

PixelMod::Type AffineTransformationOperation::getInputType() { return PixelMod::COLOR; }

PixelMod::Type AffineTransformationOperation::getOutputType() { 
  // if (m_operation != NULL) return m_operation->getOutType();
  return PixelMod::COLOR; 
}




/** Methodes */
Matrix<unsigned int>* AffineTransformationOperation::preview(double scaleX, double scaleY, double alpha, int centerX, int centerY) {
  // if (m_operation != NULL) m_pictureData = m_operation->preview();
 
  m_scaleX = scaleX;
  m_scaleY = scaleY;
  m_alpha = alpha;
  m_x0 = (double)centerX;
  m_y0 = (double)centerY;
  m_cosAlpha = cos(m_alpha);
  m_sinAlpha = sin(m_alpha);
  
  double mappingData[3][3] = {
    { m_scaleX * m_cosAlpha, -m_scaleY * m_sinAlpha, -m_x0 * m_cosAlpha + m_y0 * m_sinAlpha + m_x0 },
    { m_scaleX * m_sinAlpha, m_scaleY * m_cosAlpha, -m_x0 * m_sinAlpha - m_y0 * m_cosAlpha + m_y0 },
    { 0, 0, 1 }
  };
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      m_mapping->setValue(i, j, mappingData[i][j]);

  createPreview();
  
  for (int i = 0; i < m_previewData->getWidth(); i++)
    for (int j = 0; j < m_previewData->getHeight(); j++) {
      double x = 0, y = 0;
      double vector[3] = { (double)i, (double)j, 1.0 };
      for (int c = 0; c < 3; c++) {
	x += m_mappingInv->getValue(0, c) * vector[c];
        y += m_mappingInv->getValue(1, c) * vector[c];
      }
      m_previewData->setValue(i, j, bilinearInterpolation(x, y));
    }
  
  return m_previewData; 
}

Picture* AffineTransformationOperation::apply(double, double, double , int, int, Interpolation) { 
  return m_picture; 
}


/**Methodes internes */
unsigned int AffineTransformationOperation::bilinearInterpolation(double px, double py){
  double fracX,fracY,ifracX,ifracY;
  int xfl,yfl,xcl,ycl;
  unsigned int pix[4];
  unsigned int alpha,red,green,blue;


  xfl=(int)floor(px);
  yfl=(int)floor(py);
  //condition a verifier
  if(xfl>=m_pictureData->getWidth()||yfl>=m_pictureData->getHeight()||xfl<0||yfl<0){
    return m_defaultColor;
  }

  xcl=xfl+1;
  ycl=yfl+1;
  
  if(xcl>=m_pictureData->getWidth())xcl=xfl;
  if(ycl>=m_pictureData->getHeight())ycl=yfl;
  
  pix[0]=m_pictureData->getValue(xfl,yfl);
  pix[1]=m_pictureData->getValue(xcl,yfl);
  pix[2]=m_pictureData->getValue(xfl,ycl);
  pix[3]=m_pictureData->getValue(xcl,ycl);
  
  fracX=px-double(xfl);
  fracY=py-double(yfl);
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

 
 alpha=(unsigned int) floor(((double(PixelMod::getAlpha(pix[0]))*ifracX)+
	   (double(PixelMod::getAlpha(pix[1]))*fracX))*ifracY+
	((double(PixelMod::getAlpha(pix[2]))*ifracX)+
	 (double(PixelMod::getAlpha(pix[3]))*fracX))*fracY);
  
  
 return(unsigned int) ((alpha<<24)|(red<<16)|(green<<8)|(blue));
}


void AffineTransformationOperation::createPreview() {
  int limits[4][3] = {{ 0, 0, 1 },
                      { m_pictureData->getWidth()-1, 0, 1 },
                      { m_pictureData->getWidth()-1, m_pictureData->getHeight()-1, 1 },
                      { 0, m_pictureData->getHeight()-1, 1 }};
  int minX, minY, maxX, maxY;
  for (int p = 0; p < 4; p++) {
    double x = 0, y = 0;
    for (int i = 0; i < 3; i++) {
      x += m_mapping->getValue(0, i) * (double)limits[p][i];
      y += m_mapping->getValue(1, i) * (double)limits[p][i];
    }
    if (p == 0) {
      minX = maxX = x;
      minY = maxY = y;
    }
    else {
      if (x < minX) minX = x; else if (maxX < x) maxX = x;
      if (y < minY) minY = y; else if (maxY < y) maxY = y;
    }
  }

  if (m_previewData != NULL) delete m_previewData;
  m_previewData = new Matrix<unsigned int>(maxX - minX, maxY - minY);

  double mappingDataInv[3][3] = {
    { m_cosAlpha / m_scaleX, m_sinAlpha / m_scaleX, (m_cosAlpha * (minX - m_x0) + m_sinAlpha * (minY - m_y0) + m_x0) / m_scaleX },
    { -m_sinAlpha / m_scaleY, m_cosAlpha / m_scaleY, (m_sinAlpha * (m_x0 - minX) + m_cosAlpha * (minY - m_y0) + m_y0) / m_scaleY },
    { 0, 0, 1 }
  };

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      m_mappingInv->setValue(i, j, mappingDataInv[i][j]);
}


