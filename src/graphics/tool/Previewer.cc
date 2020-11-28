#include "Previewer.hh"

#include "../picture/PictureModifier.hh"
#include "../../model/Picture.hh"


/** Constructeurs et destructeur */
Previewer::Previewer() :
  m_pictureModifier(NULL),
  m_picture(NULL),
  m_data(NULL),
  m_imageLabel(new QLabel())
{
  setAccessibleName(tr("Preview"));
  setWidget(m_imageLabel);
}

Previewer::~Previewer() {}


/** Mutateurs */
void Previewer::setPictureModifier(PictureModifier* pictureModifier) {
  setPicture(NULL);
  m_pictureModifier = pictureModifier;
  if (m_pictureModifier != NULL) refresh();
}

void Previewer::setPicture(Picture* picture) {
  setData(NULL);
  m_picture = picture;
  if (m_picture != NULL) refresh();
}

void Previewer::setData(Matrix<unsigned int>* data) {
  m_data = data;
  if (m_data != NULL) refresh();
}


/** Predicats */
bool Previewer::isEnabled() {
  return (m_pictureModifier != NULL || m_picture != NULL || m_data != NULL);
}


/** Methodes */
void Previewer::refresh() {
  Matrix<unsigned int>* data = NULL;
  if (m_data != NULL) data = m_data;
  else if (m_picture != NULL) data = m_picture->getData();
  else if (m_pictureModifier != NULL) data = m_pictureModifier->getPicture()->getData();

  if (data != NULL) {
    int width = data->getWidth(), height = data->getHeight();
    QImage image(width, height, QImage::Format_ARGB32);
    for (int i = 0; i < width; i++)
      for (int j = 0; j < height; j++)
    	image.setPixel(i, j, data->getValue(i,j));
    m_imageLabel->setPixmap(QPixmap::fromImage(image));
    m_imageLabel->resize(width, height);
  }
}
