#include "HistogramModifier.hh"

#include <QString>
#include "PictureModifier.hh"
#include "Tracing.hh"
#include "Picture.hh"
#include "PixelMod.hh"

HistogramModifier::HistogramModifier(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier),
  m_histogramMulti(new QImage(256, 100, QImage::Format_ARGB32)),
  m_histogramRed(new QImage(256, 100, QImage::Format_ARGB32)),
  m_histogramGreen(new QImage(256, 100, QImage::Format_ARGB32)),
  m_histogramBlue(new QImage(256, 100, QImage::Format_ARGB32))
{
  refresh();
}

HistogramModifier::~HistogramModifier() {}


void HistogramModifier::refresh(){
  Tracing* tracing = m_pictureModifier->getPicture()->getBackground();  
  for (int i = 0; i < 256; i++) {
    m_histogramRedD[i] = 0;
    m_histogramGreenD[i] = 0;
    m_histogramBlueD[i] = 0;
  }
    
  for(int i = 0; i < tracing->getWidth(); i++) {
    for(int j = 0; j < tracing->getHeight(); j++) {
      unsigned int rgb = tracing->getValue(i,j); 
      m_histogramRedD[PixelMod::getRed(rgb)]++;
      m_histogramBlueD[PixelMod::getBlue(rgb)]++;
      m_histogramGreenD[PixelMod::getGreen(rgb)]++;
    }
  }
  
  int nbPixel = tracing->getWidth() * tracing->getHeight();
  int minRed = 255, minGreen = 255, minBlue = 255;
  int maxRed = 0, maxGreen = 0, maxBlue = 0;
  
  for (int i = 0; i < 256; i++) {
    if (maxRed < m_histogramRedD[i]) maxRed = m_histogramRedD[i]; 
    if (maxGreen < m_histogramGreenD[i]) maxGreen = m_histogramGreenD[i]; 
    if (maxBlue < m_histogramBlueD[i]) maxBlue = m_histogramBlueD[i]; 
    
    if (minRed > m_histogramRedD[i]) minRed = m_histogramRedD[i]; 
    if (minGreen > m_histogramGreenD[i]) minGreen = m_histogramGreenD[i]; 
    if (minBlue > m_histogramBlueD[i]) minBlue = m_histogramBlueD[i]; 
  }
  
  int amplitudeRed = (maxRed - minRed);
  int amplitudeGreen = (maxGreen - minGreen);
  int amplitudeBlue = (maxBlue - minBlue);
      
  for (int i = 0; i < 256; i++) {
    int red = m_histogramRedD[i] * amplitudeRed / 100;
    int green = m_histogramGreenD[i] * amplitudeGreen / 100;
    int blue = m_histogramBlueD[i] * amplitudeBlue / 100;

    for (int j = 0; j < 100; j++) {
      if (j * amplitudeRed / 100 < red) red = 0;
      if (j * amplitudeGreen / 100 < green) green = 0;
      if (j * amplitudeBlue / 100 < blue) blue = 0;
	
      red = PixelMod::threshold(red);
      green = PixelMod::threshold(green);
      blue = PixelMod::threshold(blue);
      
      m_histogramMulti->setPixel(i, j, PixelMod::createRGB(red,green,blue));
      m_histogramRed->setPixel(i, j, PixelMod::createRGB(red, 0, 0));
      m_histogramGreen->setPixel(i, j, PixelMod::createRGB(0, green, 0));
      m_histogramBlue->setPixel(i, j, PixelMod::createRGB(0, 0, blue));
    }
  }
    
  setPixmap(QPixmap::fromImage((const QImage&)(*m_histogramRed)));
}