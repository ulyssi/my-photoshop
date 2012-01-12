#include "Histogram.hh"

#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "PictureModifier.hh"
#include "Tracing.hh"
#include "Picture.hh"
#include "PixelMod.hh"


/** Constructeurs et destructeurs */
Histogram::Histogram(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier),
  m_radioButtonRGB(new QRadioButton(tr("RGB"))),
  m_radioButtonYUV(new QRadioButton(tr("YUV"))),
  m_comboBoxLayer(new QComboBox),
  m_histogramLabel(new QLabel),
  m_histogramImage(new QImage(PixelMod::nbValue, 100, QImage::Format_ARGB32))
{
  setAccessibleName(tr("Histogram"));
  
  m_radioButtonRGB->setChecked(true);
  m_radioButtonYUV->setEnabled(false);
  refreshComboBoxLayer();
  refresh();

  connect(m_radioButtonRGB, SIGNAL(clicked()), this, SLOT(refreshComboBoxLayer()));
  connect(m_radioButtonYUV, SIGNAL(clicked()), this, SLOT(refreshComboBoxLayer()));
  connect(m_comboBoxLayer, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshImage()));

  m_histogramLabel->setPixmap(QPixmap::fromImage((const QImage&)(*m_histogramImage)));

  QHBoxLayout* selectLayout = new QHBoxLayout;
  selectLayout->addWidget(m_radioButtonRGB);
  selectLayout->addWidget(m_radioButtonYUV);
  selectLayout->addWidget(m_comboBoxLayer);
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addLayout(selectLayout);
  layout->addWidget(m_histogramLabel);

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
	    if ((m_comboBoxLayer->currentIndex() != k && m_comboBoxLayer->currentIndex() < 3) || j < 100 - seuil[k]) color[k] = 0;
	  
	  if (color[0] + color[1] + color[2] == 0) m_histogramImage->setPixel(i, j, PixelMod::createRGB(0, 0, 0, PixelMod::TRANSLUCID));
	  else m_histogramImage->setPixel(i, j, PixelMod::createRGB(color[0], color[1], color[2]));
	}
      }
      m_histogramLabel->setPixmap(QPixmap::fromImage((const QImage&)(*m_histogramImage)));
    }
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
