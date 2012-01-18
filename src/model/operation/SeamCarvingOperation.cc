#include "SeamCarvingOperation.hh"

#include <cmath>
#include "PixelMod.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
SeamCarvingOperation::SeamCarvingOperation(Picture* picture) :
  m_picture(picture),
  m_pictureData(new Matrix<unsigned int>(picture->getData())),
  m_width(m_pictureData->getWidth()),
  m_height(m_pictureData->getHeight()),
  m_gradient(createGradientMatrix()),
  m_minimumPath(createMinimumPath()),
  m_targetWidth(m_width),
  m_targetHeight(m_height)
{
  // initializeMinimumPathX();
  // initializeMinimumPathY();
}

SeamCarvingOperation::~SeamCarvingOperation() {}


/** Accesseurs */
void SeamCarvingOperation::setTargetWidth(int targetWidth) { m_targetWidth = targetWidth; }

void SeamCarvingOperation::setTargetHeight(int targetHeight) { m_targetHeight = targetHeight; }


/** Methodes */
Matrix<unsigned int>* SeamCarvingOperation::updatePreview() {
  
  while (m_width > m_targetWidth) {
    delete m_gradient;
    m_gradient = createGradientMatrix();
    initializeMinimumPathX();
    deleteRow();
  }
  // for (int k = 0; k < height - m_targetHeight; k++) {
  //   initializeMinimumPathY();
  //   deleteLine();
  // }

  Matrix<unsigned int>* preview = new Matrix<unsigned int>(m_width, m_height);
  for (int i = 0; i < m_width; i++) {
    for (int j = 0; j < m_height; j++) {
      preview->setValue(i, j, m_pictureData->getValue(i, j));
    }
  }

  return preview;
}

Picture* SeamCarvingOperation::applyOperation() {
  return m_picture;
}


/** Methodes internes */
SeamCarvingOperation::Path** SeamCarvingOperation::createMinimumPath() {
  m_minimumPath = new Path*[m_width];
  for (int i = 0; i < m_width; i++) m_minimumPath[i] = new Path[m_height];
  return m_minimumPath;
}

unsigned int** SeamCarvingOperation::createGradientMatrix() {
  int sobelX[3][3] = {{  1,  2,  1}, {  0,  0,  0}, { -1, -2, -1}};
  int sobelY[3][3] = {{  1,  0, -1}, {  2,  0, -2}, {  1,  0, -1}};

  m_gradient = new unsigned int*[m_width];
  for (int i = 0; i < m_width; i++) {
    m_gradient[i] = new unsigned int[m_height];
    for (int j = 0; j < m_height; j++) {
      int gradientX = 0, gradientY = 0;
      for (int i2 = 0; i2 < 3; i2++)
	for (int j2 = 0; j2 < 3; j2++) {
          unsigned int color = m_pictureData->getValue((i - 1 + i2 + m_width) % m_width, (j - 1 + j2 + m_height) % m_height);
          int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
	  gradientX += intensity * sobelX[i2][j2];
	  gradientY += intensity * sobelY[i2][j2];
	}
      m_gradient[i][j] = gradientX * gradientX + gradientY * gradientY;
    }
  }
  return m_gradient;
}

void SeamCarvingOperation::initializeMinimumPathX() {
  for (int j = 0; j < m_height; j++) {
    m_minimumPath[0][j].m_pathValueX = m_gradient[0][j];
    m_minimumPath[0][j].m_previousX = -1;
  }
  for (int i = 1; i < m_width; i++) {
    for (int j = 0; j < m_height; j++) {
      if (j-1 >= 0 && m_minimumPath[i-1][j-1].m_pathValueX < m_minimumPath[i-1][m_minimumPath[i][j].m_previousX].m_pathValueX) m_minimumPath[i][j].m_previousX = j-1;
      if (j+1 < m_height && m_minimumPath[i-1][j+1].m_pathValueX < m_minimumPath[i-1][m_minimumPath[i][j].m_previousX].m_pathValueX) m_minimumPath[i][j].m_previousX = j+1;
      m_minimumPath[i][j].m_pathValueX = m_minimumPath[i-1][m_minimumPath[i][j].m_previousX].m_pathValueX + m_gradient[i][j];
    }
  }
}

void SeamCarvingOperation::initializeMinimumPathY() {
  for (int i = 0; i < m_width; i++) {
    m_minimumPath[i][0].m_pathValueY = m_gradient[i][0];
    m_minimumPath[i][0].m_previousY = -1;
  }
  for (int j = 1; j < m_height; j++) {
    for (int i = 0; i < m_width; i++) {
      if (i-1 >= 0 && m_minimumPath[i-1][j-1].m_pathValueY < m_minimumPath[m_minimumPath[i][j].m_previousY][j-1].m_pathValueY) m_minimumPath[i][j].m_previousY = i-1;
      if (i+1 < m_width && m_minimumPath[i+1][j-1].m_pathValueY < m_minimumPath[m_minimumPath[i][j].m_previousY][j-1].m_pathValueY) m_minimumPath[i][j].m_previousY = i+1;
      m_minimumPath[i][j].m_pathValueY = m_minimumPath[m_minimumPath[i][j].m_previousY][j-1].m_pathValueY + m_gradient[i][j];
    }
  }
}

void SeamCarvingOperation::deleteRow() {
  
  // recherche du chemin de plus faible poids
  int yPath = 0;
  for (int i = 1; i < m_width; i++)
    if (m_minimumPath[i][m_height-1].m_pathValueY < m_minimumPath[yPath][m_height-1].m_pathValueY) 
      yPath = i;

  // suppression du chemin par copie de la partie haute de l'image
  m_width--;
  int yPathTmp = yPath;
  for (int j = m_height-1; j >= 0; j--) {
    for (int i = yPathTmp; i < m_width; i++) m_pictureData->setValue(i, j, m_pictureData->getValue(i+1, j));
    yPathTmp = m_minimumPath[yPathTmp][j].m_previousY;
  }
  
  // mise a jour du gradient des points voisins du chemin
  yPathTmp = yPath;
  for (int j = m_height-1; j >= 0; j--) {
    for (int i = yPathTmp-1; i <= yPathTmp+1; i++) 
      if (0 <= i && i < m_width && 0 <= j && j < m_height)
	m_gradient[i][j] = updateGradient(i, j);
    for (int i = yPathTmp+2; i < m_width; i++) if (0 <= i && i < m_width && 0 <= j && j < m_height) m_gradient[i][j] = m_gradient[i+1][j];
    yPathTmp = m_minimumPath[yPathTmp][j].m_previousY;
  }

  // mise a jour des chemins
  
}

void SeamCarvingOperation::deleteLine() {
}

inline unsigned int SeamCarvingOperation::updateGradient(int i, int j) {
  int sobelX[3][3] = {{  1,  2,  1}, {  0,  0,  0}, { -1, -2, -1}};
  int sobelY[3][3] = {{  1,  0, -1}, {  2,  0, -2}, {  1,  0, -1}};
  int gradientX = 0, gradientY = 0;
  for (int i2 = 0; i2 < 3; i2++)
    for (int j2 = 0; j2 < 3; j2++) {
      int x = (i - 1 + i2 + m_width) % m_width;
      int y = (j - 1 + j2 + m_height) % m_height;
      unsigned int color = m_pictureData->getValue(x, y);
      int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
      gradientX += intensity * sobelX[i2][j2];
      gradientY += intensity * sobelY[i2][j2];
    }
  // double alpha = atan((double)gradientY/(double)gradientX);
  return gradientX * gradientX + gradientY * gradientY;
}

