#include "Histogram.hh"

#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <cmath>

#include "PictureModifier.hh"
#include "Tracing.hh"
#include "Picture.hh"
#include "PixelMod.hh"


/** Constructeurs et destructeurs */
Histogram::Histogram(PictureModifier* pictureModifier) :
  m_bInf(0),
  m_bSup(0),
  m_pictureModifier(pictureModifier),
  m_radioButtonRGB(new QRadioButton(tr("RGB"))),
  m_radioButtonYUV(new QRadioButton(tr("YUV"))),
  m_comboBoxLayer(new QComboBox),
  m_sliderInf(new QSlider(Qt::Horizontal)),
  m_sliderSup(new QSlider(Qt::Horizontal)),
  m_applyRescale(new QPushButton(QString("Apply Rescale"))),
  m_applyEqualization(new QPushButton(QString("Apply Equalization"))),
  m_histogramLabel(new QLabel),
  m_histogramImage(new QImage(PixelMod::nbValue, 100, QImage::Format_ARGB32))
{
  setAccessibleName(tr("Histogram"));
  
  m_radioButtonRGB->setChecked(true);
  m_radioButtonYUV->setEnabled(false);
  refreshComboBoxLayer();
  refresh();
  m_sliderInf->setRange(0, +255);
  m_sliderSup->setRange(0, +255);
  m_sliderInf->setValue(0);
  m_sliderSup->setValue(255);
  
  connect(m_radioButtonRGB, SIGNAL(clicked()), this, SLOT(refreshComboBoxLayer()));
  connect(m_radioButtonYUV, SIGNAL(clicked()), this, SLOT(refreshComboBoxLayer()));
  connect(m_comboBoxLayer, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshImage()));
  connect(m_sliderInf, SIGNAL(valueChanged(int)), this, SLOT(sliderInfChanged(int)));
  connect(m_sliderSup, SIGNAL(valueChanged(int)), this, SLOT(sliderSupChanged(int)));
  connect(m_applyRescale, SIGNAL(clicked()), this, SLOT(applyHistogramCrop()));
  connect(m_applyEqualization, SIGNAL(clicked()), this, SLOT(applyHistogramEqualization()));

  m_histogramLabel->setPixmap(QPixmap::fromImage((const QImage&)(*m_histogramImage)));

  QHBoxLayout* selectLayout = new QHBoxLayout;
  selectLayout->addWidget(m_radioButtonRGB);
  selectLayout->addWidget(m_radioButtonYUV);
  selectLayout->addWidget(m_comboBoxLayer);
  
  QVBoxLayout *slider = new QVBoxLayout;
  slider->addWidget(m_sliderInf);
  slider->addWidget(m_sliderSup);
  
  QHBoxLayout* button = new QHBoxLayout;
  button->addWidget(m_applyRescale);
  button->addWidget(m_applyEqualization);
  
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addLayout(selectLayout);
  layout->addWidget(m_histogramLabel);
  layout->addLayout(slider);
  layout->addLayout(button);
  
  setLayout(layout);
}

Histogram::~Histogram() {}


/** Mutateurs */
void Histogram::setPictureModifier(PictureModifier* pictureModifier) { 
  m_pictureModifier = pictureModifier; 
  refresh();
}


/** Predicats */
bool Histogram::isEnabled() { return QWidget::isEnabled() && m_pictureModifier != NULL; }


/** Methodes */
void Histogram::refresh() {
  bool rgb = m_radioButtonRGB->isChecked();
  refreshData(rgb);
  if (m_pictureModifier != NULL) {
    Tracing* tracing = m_pictureModifier->getPicture()->getBackground();

    int nbPixel = tracing->getWidth() * tracing->getHeight();
    int min[3] = { nbPixel };
    int max[3] = { 0 };
    int amplitude[3];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 256; j++) {
	if (max[i] < m_histogramData[i][j]) max[i] = m_histogramData[i][j];
	if (min[i] > m_histogramData[i][j]) min[i] = m_histogramData[i][j];
      }
      amplitude[i] = max[i] - min[i];
    }
  
    if (m_pictureModifier != NULL) {
      int seuil[3];
      for (int i = 0; i < 256; i++) {
	for (int j = 0; j < 3; j++) seuil[j] = (m_histogramData[j][i] - min[j]) * 100 / amplitude[j];
	for (int j = 0; j < 100; j++) {
	  int color[3] = { 255, 255, 255 };
	  for (int k = 0; k < 3; k++)
	    if ((m_comboBoxLayer->currentIndex() != k && m_comboBoxLayer->currentIndex() < 3) || j < 100 - seuil[2-k]) color[2-k] = 0;
	  
	  if (color[0] + color[1] + color[2] == 0) m_histogramImage->setPixel(i, j, PixelMod::createRGB(0, 0, 0, PixelMod::TRANSLUCID));
	  else m_histogramImage->setPixel(i, j, PixelMod::createRGB(color[2], color[1], color[0]));
	}
      }
      m_histogramLabel->setPixmap(QPixmap::fromImage((const QImage&)(*m_histogramImage)));
    }
  }
}


void Histogram::equalization() {
  if (m_pictureModifier != NULL) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 256; j++)
	m_cumulativeHistogram[i][j] = 0;
      
    //calcul de l'histogramme cumulé
    int kRed, kGreen, kBlue;
    for(int i=0; i<256; i++){
      kRed = 0;
      kGreen = 0;
      kBlue = 0;
      for(int j=0; j <= i ; j++){
	kRed += m_histogramData[PixelMod::RED][j];
	kGreen += m_histogramData[PixelMod::GREEN][j];
	kBlue += m_histogramData[PixelMod::BLUE][j];
      }
      m_cumulativeHistogram[PixelMod::RED][i] = kRed;
      m_cumulativeHistogram[PixelMod::GREEN][i] = kGreen;
      m_cumulativeHistogram[PixelMod::BLUE][i] = kBlue;
    } 
    
    //egalisation de l'image
    Tracing* tracing = m_pictureModifier->getPicture()->getBackground();
    float nbPixel = tracing->getWidth() * tracing->getHeight();
    unsigned int couleur;
    for(int i=0; i < tracing->getHeight(); i++){
      for(int j=0; j < tracing->getWidth(); j++){
	couleur = tracing->getValue(j,i);
	tracing->setValue(j,
			  i,
			  PixelMod::createRGB(PixelMod::threshold(floor((255.0*(m_cumulativeHistogram[PixelMod::RED][PixelMod::getRed(couleur)]))/ nbPixel)),
					      PixelMod::threshold(floor((255.0*(m_cumulativeHistogram[PixelMod::GREEN][PixelMod::getGreen(couleur)]))/ nbPixel)),
					      PixelMod::threshold(floor((255.0*(m_cumulativeHistogram[PixelMod::BLUE][PixelMod::getBlue(couleur)]))/ nbPixel)),
					      PixelMod::getAlpha(couleur)));
					    
      }
    }
    //refresh de l'image et de l'histogramme
    m_pictureModifier->getPicture()->refresh();
    m_pictureModifier->refresh();
  }
}



void Histogram::crop(int bInf, int bSup) {
  double L = bSup - bInf;
  unsigned int couleur;
  if (m_pictureModifier != NULL) {
    Tracing* tracing = m_pictureModifier->getPicture()->getBackground();
    for(int i=0; i < tracing->getHeight(); i++){
      for(int j=0; j < tracing->getWidth(); j++){
	couleur = tracing->getValue(j,i);
	tracing->setValue(j,i, PixelMod::createRGB(PixelMod::threshold(floor((255.0*(PixelMod::getRed(couleur) - bInf))/ L)),
						   PixelMod::threshold(floor((255.0*(PixelMod::getGreen(couleur) - bInf))/ L)),
						   PixelMod::threshold(floor((255.0*(PixelMod::getBlue(couleur) - bInf))/ L)),
						   PixelMod::getAlpha(couleur)));
      }
    }
    m_pictureModifier->getPicture()->refresh();
    m_pictureModifier->refresh();
  }
}




void Histogram::refreshData(bool rgb) {
  for (int i = 0; i < 3; i++)
      for (int j = 0; j < 256; j++)
	m_histogramData[i][j] = 0;

  if (m_pictureModifier != NULL) {
    Tracing* tracing = m_pictureModifier->getPicture()->getBackground();
    for(int i = 0; i < tracing->getWidth(); i++) {
      for(int j = 0; j < tracing->getHeight(); j++) {
	unsigned int color = tracing->getValue(i,j);
	if (PixelMod::getAlpha(color) != PixelMod::TRANSLUCID) {
	  if (rgb) {
	    m_histogramData[PixelMod::RED][PixelMod::getRed(color)]++;
	    m_histogramData[PixelMod::GREEN][PixelMod::getGreen(color)]++;
	    m_histogramData[PixelMod::BLUE][PixelMod::getBlue(color)]++;
	  }
	  else {
	    m_histogramData[PixelMod::LUMA][PixelMod::getLuma(color)]++;
	    m_histogramData[PixelMod::CHROMINANCE_U][PixelMod::getChrominanceU(color)]++;
	    m_histogramData[PixelMod::CHROMINANCE_V][PixelMod::getChrominanceV(color)]++;
	  }
	}
      }
    }
  }
}


/** Slots */
void Histogram::refreshComboBoxLayer() {
  m_comboBoxLayer->clear();
  if (m_radioButtonRGB->isChecked()) {
    m_comboBoxLayer->addItem(tr("Red"));
    m_comboBoxLayer->addItem(tr("Green"));
    m_comboBoxLayer->addItem(tr("Blue"));
    m_comboBoxLayer->addItem(tr("Red Green Blue"));
  }
  else {
    m_comboBoxLayer->addItem(tr("Luma"));
    m_comboBoxLayer->addItem(tr("Chrominance U"));
    m_comboBoxLayer->addItem(tr("Chrominance V"));
  }
  refresh();
}

void Histogram::refreshImage() {
  refresh();
}

void Histogram::sliderInfChanged(int i){
  m_bInf = i;
  if(m_bInf > m_bSup){
    m_bSup = m_bInf;
    m_sliderSup->setValue(m_bSup);
  }
}

void Histogram::sliderSupChanged(int i){
  m_bSup = i;  
  if(m_bSup < m_bInf){
    m_bInf = m_bSup;
    m_sliderInf->setValue(m_bInf);
  }
}

void Histogram::applyHistogramCrop(){
    crop(m_bInf,m_bSup);
}

void Histogram::applyHistogramEqualization(){
    equalization();
}