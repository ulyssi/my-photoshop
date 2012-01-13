#include "Previewer.hh"

#include <QVBoxLayout>

#include "PictureModifier.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
Previewer::Previewer() :
  m_pictureModifier(NULL),
  m_picture(NULL),
  m_data(NULL),
  m_imageLabel(new QLabel())
{
  setAccessibleName(tr("Preview"));
  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(m_imageLabel);
  setLayout(layout);
}

Previewer::~Previewer() {}


/** Methodes */
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

void Previewer::refresh() {
  Matrix<unsigned int>* data = NULL;
  if (m_pictureModifier != NULL) data = m_pictureModifier->getPicture()->getData();
  else if (m_picture != NULL) data = m_picture->getData();
  else data = m_data;

  if (data != NULL) {
    int width = data->getWidth(), height = data->getHeight();
    QImage image(width, height, QImage::Format_ARGB32);
    for (int i = 0; i < width; i++)
      for (int j = 0; j < height; j++)
    	image.setPixel(i, j, data->getValue(i,j));
    m_imageLabel->setPixmap(QPixmap::fromImage(image));
    m_imageLabel->resize(width, height);
    resize(width, height);
    ((QWidget*)parent())->resize(width, height);
  }
}
