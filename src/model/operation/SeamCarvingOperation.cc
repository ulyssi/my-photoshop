#include "SeamCarvingOperation.hh"

#include <cmath>
#include "PixelMod.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
SeamCarvingOperation::SeamCarvingOperation(Picture* picture) :
  m_picture(picture),
  m_pictureData(new Matrix<unsigned int>(m_picture->getData())),
  m_width(m_pictureData->getWidth()),
  m_height(m_pictureData->getHeight()),
  m_gradient(createGradientMatrix()),
  m_minimumPathH(createMinimumPathH()),
  m_minimumPathV(createMinimumPathV()),
  m_pathH(new int[m_width]),
  m_pathV(new int[m_height]),
  m_targetWidth(m_width),
  m_targetHeight(m_height)
{
  m_sobelX[0][0] =  1; m_sobelX[0][1] =  2; m_sobelX[0][2] =  1;
  m_sobelX[1][0] =  0; m_sobelX[1][1] =  0; m_sobelX[1][2] =  0;
  m_sobelX[2][0] = -1; m_sobelX[2][1] = -2; m_sobelX[2][2] = -1;

  m_sobelY[0][0] =  1; m_sobelY[0][1] =  0; m_sobelY[0][2] = -1;
  m_sobelY[1][0] =  2; m_sobelY[1][1] =  0; m_sobelY[1][2] = -2;
  m_sobelY[2][0] =  1; m_sobelY[2][1] =  0; m_sobelY[2][2] = -1;

  initializeGradientMatrix();
}

SeamCarvingOperation::~SeamCarvingOperation() {}


/** Accesseurs */
// void SeamCarvingOperation::setPicture(Picture* picture) {
//   if (picture != m_picture) {
//     delete m_pictureData;
//     delete m_gradient;
//     delete m_minimumPath;
//     m_picture = picture;
//     m_pictureData = new Matrix<unsigned int>(m_picture->getData());
//     m_width(m_pictureData->getWidth());
//     m_height(m_pictureData->getHeight());
//     m_gradient(createGradientMatrix());
//     m_minimumPath(createMinimumPath());
//     initializeGradientMatrix();
//   }
// }

void SeamCarvingOperation::setTargetWidth(int targetWidth) { m_targetWidth = targetWidth; }

void SeamCarvingOperation::setTargetHeight(int targetHeight) { m_targetHeight = targetHeight; }


/** Methodes */
Matrix<unsigned int>* SeamCarvingOperation::updatePreview() {
  
  initializeMinimumPathV();
  while (m_width > m_targetWidth) {
    deleteRow();
  }
  
  while (m_height > m_targetHeight) {
    initializeMinimumPathH();
    deleteLine();
  }
  
  return new Matrix<unsigned int>(m_width, m_height, m_pictureData->getData());
}

Picture* SeamCarvingOperation::applyOperation() {
  return m_picture;
}


/** Methodes internes */
SeamCarvingOperation::Path** SeamCarvingOperation::createMinimumPathH() {
  m_minimumPathH = new Path*[m_width];
  for (int i = 0; i < m_width; i++) m_minimumPathH[i] = new Path[m_height];
  return m_minimumPathH;
}

SeamCarvingOperation::Path** SeamCarvingOperation::createMinimumPathV() {
  m_minimumPathV = new Path*[m_width];
  for (int i = 0; i < m_width; i++) m_minimumPathV[i] = new Path[m_height];
  return m_minimumPathV;
}

unsigned int** SeamCarvingOperation::createGradientMatrix() {
  m_gradient = new unsigned int*[m_width];
  for (int i = 0; i < m_width; i++) {
    m_gradient[i] = new unsigned int[m_height];
    for (int j = 0; j < m_height; j++) updateGradient(i, j);
  }
  return m_gradient;
}

void SeamCarvingOperation::initializeGradientMatrix() {
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      updateGradient(i, j);
}

void SeamCarvingOperation::initializeMinimumPathH() {
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      updateMinimumPathH(i, j);
}

void SeamCarvingOperation::initializeMinimumPathV() {
  for (int j = 0; j < m_height; j++)
    for (int i = 0; i < m_width; i++)
      updateMinimumPathV(i, j);
}

void SeamCarvingOperation::deleteRow() {
  unsigned int** pictureData = m_pictureData->getData();

  // recherche du chemin de plus faible poids
  int xFinal = 0, xInit;
  for (int i = 1; i < m_width; i++)
    if (m_minimumPathV[i][m_height-1].m_pathValue < m_minimumPathV[xFinal][m_height-1].m_pathValue) 
      xFinal = i;
  m_pathV[m_height-1] = xFinal;
  for (int j = m_height-1; j > 0; j--) m_pathV[j-1] = m_minimumPathV[m_pathV[j]][j].m_previous;
  m_width--;
  
  // mise a jour des donnees de l'image
  for (int j = 0; j < m_height; j++)
    for (int i = m_pathV[j]; i < m_width; i++) {
      pictureData[i][j] = pictureData[i+1][j];
      m_gradient[i][j] = m_gradient[i+1][j];
      m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i+1][j].m_pathValue;
      m_minimumPathV[i][j].m_previous = m_minimumPathV[i+1][j].m_previous-1;
    }
  
  // mise a jour des gradients locaux
  for (int j = 0; j < m_height; j++)
    for (int i = m_pathV[j]-1; i <= m_pathV[j]+1; i++)
      if (0 <= i && i < m_width)
	updateGradient(i, j);

  // mise a jour des chemins
  int xMin = m_pathV[0], xMax = m_pathV[0]+1;
  for (int j = 0; j < m_height; j++) {
    int min = xMin-1, max = xMax+1;
    for (int i = xMin; i < xMax; i++) {
      unsigned int pathValue = m_minimumPathV[i][j].m_pathValue;
      updateMinimumPathV(i, j);
      if (pathValue != m_minimumPathV[i][j].m_pathValue) {
      	if (min == xMin-1) min = i-2;
      	max = i+3;
      }
    }
    if (min < 0) xMin = 0; else xMin = min;
    if (max > m_width) xMax = m_width; else xMax = max;
  }

  // initializeMinimumPathV();
}

void SeamCarvingOperation::deleteLine() {
  unsigned int** pictureData = m_pictureData->getData();

  // recherche du chemin de plus faible poids
  int yFinal = 0;
  for (int j = 1; j < m_height; j++)
    if (m_minimumPathH[m_width-1][j].m_pathValue < m_minimumPathH[m_width-1][yFinal].m_pathValue) 
      yFinal = j;

  // mise a jour des donnees de l'image
  m_height--;
  int yTmp = yFinal;
  for (int i = m_width-1; i >= 0; i--) {
    for (int j = yTmp; j < m_height; j++) {
      pictureData[i][j] = pictureData[i][j+1];
      m_gradient[i][j] = m_gradient[i][j+1];
    }
    yTmp = m_minimumPathH[i][yTmp].m_previous;
  }

  // mise a jour des gradients locaux
  yTmp = yFinal;
  for (int i = m_width-1; i >= 0; i--) {
    for (int j = yTmp-2; j <= yTmp+2; j++)
      if (0 <= j && j < m_height) 
	updateGradient(i, j);
    yTmp = m_minimumPathH[i][yTmp].m_previous;
  }
}

inline void SeamCarvingOperation::updateMinimumPathH(int i, int j) {
  if (i == 0) {
    m_minimumPathH[0][j].m_pathValue = m_gradient[0][j];
    m_minimumPathH[0][j].m_previous = -1;
  }
  else {
    unsigned int k = m_gradient[i][j];
    unsigned int kSide = k;
    m_minimumPathH[i][j].m_previous = j;
    m_minimumPathH[i][j].m_pathValue = m_minimumPathH[i-1][j].m_pathValue + k;
    if (j-1 >= 0 && m_minimumPathH[i-1][j-1].m_pathValue + kSide < m_minimumPathH[i-1][m_minimumPathH[i][j].m_previous].m_pathValue) {
      m_minimumPathH[i][j].m_previous = j-1;
      m_minimumPathH[i][j].m_pathValue = m_minimumPathH[i-1][j-1].m_pathValue + kSide;
    }
    if (j+1 < m_height && m_minimumPathH[i-1][j+1].m_pathValue < m_minimumPathH[i-1][m_minimumPathH[i][j].m_previous].m_pathValue) {
      m_minimumPathH[i][j].m_previous = j+1;
      m_minimumPathH[i][j].m_pathValue = m_minimumPathH[i-1][j+1].m_pathValue + kSide;
    }
  }
}

inline void SeamCarvingOperation::updateMinimumPathV(int i, int j) {
  if (j == 0) {
    m_minimumPathV[i][0].m_pathValue = m_gradient[i][0];
    m_minimumPathV[i][0].m_previous = -1;
  }
  else {
    unsigned int k = m_gradient[i][j];
    unsigned int kSide = k;
    m_minimumPathV[i][j].m_previous = i;
    m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i][j-1].m_pathValue + k;
    if (i-1 >= 0 && m_minimumPathV[i-1][j-1].m_pathValue < m_minimumPathV[m_minimumPathV[i][j].m_previous][j-1].m_pathValue) {
      m_minimumPathV[i][j].m_previous = i-1;
      m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i-1][j-1].m_pathValue + kSide;
    }
    if (i+1 < m_width && m_minimumPathV[i+1][j-1].m_pathValue < m_minimumPathV[m_minimumPathV[i][j].m_previous][j-1].m_pathValue) {
      m_minimumPathV[i][j].m_previous = i+1;
      m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i+1][j-1].m_pathValue + kSide;
    }
  }
}

inline void SeamCarvingOperation::updateGradient(int i, int j) {
  int gradientX = 0, gradientY = 0;
  for (int i2 = 0; i2 < 3; i2++)
    for (int j2 = 0; j2 < 3; j2++) {
      int x = (i - 1 + i2 + m_width) % m_width;
      int y = (j - 1 + j2 + m_height) % m_height;
      unsigned int color = m_pictureData->getValue(x, y);
      int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
      gradientX += intensity * m_sobelX[i2][j2];
      gradientY += intensity * m_sobelY[i2][j2];
    }
  // double alpha = atan((double)gradientY/(double)gradientX);
  m_gradient[i][j] = gradientX * gradientX + gradientY * gradientY;
}

// inline void updatePixel(int i, int j, 
