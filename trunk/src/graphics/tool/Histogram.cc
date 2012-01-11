#include "Histogram.hh"

#include <QString>
#include "PictureModifier.hh"
#include "Tracing.hh"
#include "Picture.hh"
#include "PixelMod.hh"


/** Constructeurs et destructeurs */
Histogram::Histogram(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier),
  m_histogramMulti(new QImage(256, 100, QImage::Format_ARGB32)),
  m_histogramRed(new QImage(256, 100, QImage::Format_ARGB32)),
  m_histogramGreen(new QImage(256, 100, QImage::Format_ARGB32)),
  m_histogramBlue(new QImage(256, 100, QImage::Format_ARGB32))
{
  setAccessibleName(QString("Histogram"));
  refresh();
}

Histogram::~Histogram() {}


/** Predicats */
bool Histogram::isEnabled() { return QLabel::isEnabled() && m_pictureModifier != NULL; }


/** Mutateurs */
void Histogram::setPictureModifier(PictureModifier* pictureModifier) { 
  m_pictureModifier = pictureModifier; 
  refresh();
}


/** Methodes */
void Histogram::refresh() {
  if (m_pictureModifier != NULL) {
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
    int minRed = nbPixel, minGreen = nbPixel, minBlue = nbPixel;
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
      int seuilRed = (m_histogramRedD[i] - minRed) * 100 / amplitudeRed;
      int seuilGreen = (m_histogramGreenD[i] - minGreen) * 100 / amplitudeGreen;
      int seuilBlue = (m_histogramBlueD[i] - minBlue) * 100 / amplitudeBlue;

      for (int j = 0; j < 100; j++) {
        int red = 255, green = 255, blue = 255;
        if (j < 100 - seuilRed) red = 0;
        if (j < 100 - seuilGreen) green = 0; 
        if (j < 100 - seuilBlue) blue = 0; 

        if (red == 0 && green == 0 && blue == 0) 
          m_histogramMulti->setPixel(i, j, PixelMod::createRGB(red, green, blue, 50));
        else 
          m_histogramMulti->setPixel(i, j, PixelMod::createRGB(red, green, blue, 255));
        m_histogramRed->setPixel(i, j, PixelMod::createRGB(red, 0, 0));
        m_histogramGreen->setPixel(i, j, PixelMod::createRGB(0, green, 0));
        m_histogramBlue->setPixel(i, j, PixelMod::createRGB(0, 0, blue));
      }
    }
  }
  else {
      for (int i = 0; i < 256; i++) 
        for (int j = 0; j < 100; j++)
          m_histogramMulti->setPixel(i, j, PixelMod::createRGB(0, 0, 0, 50));
  }
  setPixmap(QPixmap::fromImage((const QImage&)(*m_histogramMulti)));
  
}
