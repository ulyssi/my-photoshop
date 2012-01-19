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
  m_minimumPath(createMinimumPath()),
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
  
  while (m_width > m_targetWidth) {
    initializeMinimumPathV();
    deleteRow();
  }
  
  while (m_height > m_targetHeight) {
    initializeMinimumPathH();
    deleteLine();
  }
  
  // for (int k = 0; k < height - m_targetHeight; k++) {
  //   initializeMinimumPathY();
  //   deleteLine();
  // }

  return new Matrix<unsigned int>(m_width, m_height, m_pictureData->getData());
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
  int xFinal = 0;
  for (int i = 1; i < m_width; i++)
    if (m_minimumPath[i][m_height-1].m_pathValueV < m_minimumPath[xFinal][m_height-1].m_pathValueV) 
      xFinal = i;

  // mise a jour des donnees de l'image
  m_width--;
  int xTmp = xFinal;
  for (int j = m_height-1; j >= 0; j--) {
    for (int i = xTmp; i < m_width; i++) {
      pictureData[i][j] = pictureData[i+1][j];
      m_gradient[i][j] = m_gradient[i+1][j];
    }
    xTmp = m_minimumPath[xTmp][j].m_previousV;
  }

  // mise a jour des gradients locaux
  xTmp = xFinal;
  for (int j = m_height-1; j >= 0; j--) {
    for (int i = xTmp-2; i <= xTmp+2; i++)
      if (0 <= i && i < m_width) 
	updateGradient(i, j);
    xTmp = m_minimumPath[xTmp][j].m_previousV;
  }
}

void SeamCarvingOperation::deleteLine() {
  unsigned int** pictureData = m_pictureData->getData();

  // recherche du chemin de plus faible poids
  int yFinal = 0;
  for (int j = 1; j < m_height; j++)
    if (m_minimumPath[m_width-1][j].m_pathValueH < m_minimumPath[m_width-1][yFinal].m_pathValueH) 
      yFinal = j;

  // mise a jour des donnees de l'image
  m_height--;
  int yTmp = yFinal;
  for (int i = m_width-1; i >= 0; i--) {
    for (int j = yTmp; j < m_height; j++) {
      pictureData[i][j] = pictureData[i][j+1];
      m_gradient[i][j] = m_gradient[i][j+1];
    }
    yTmp = m_minimumPath[i][yTmp].m_previousH;
  }

  // mise a jour des gradients locaux
  yTmp = yFinal;
  for (int i = m_width-1; i >= 0; i--) {
    for (int j = yTmp-2; j <= yTmp+2; j++)
      if (0 <= j && j < m_height) 
	updateGradient(i, j);
    yTmp = m_minimumPath[i][yTmp].m_previousH;
  }
}

inline void SeamCarvingOperation::updateMinimumPathH(int i, int j) {
  if (i == 0) {
    m_minimumPath[0][j].m_pathValueH = m_gradient[0][j];
    m_minimumPath[0][j].m_previousH = -1;
  }
  else {
    m_minimumPath[i][j].m_previousH = j;
    if (j-1 >= 0 && m_minimumPath[i-1][j-1].m_pathValueH < m_minimumPath[i-1][m_minimumPath[i][j].m_previousH].m_pathValueH) 
      m_minimumPath[i][j].m_previousH = j-1;
    if (j+1 < m_height && m_minimumPath[i-1][j+1].m_pathValueH < m_minimumPath[i-1][m_minimumPath[i][j].m_previousH].m_pathValueH)
      m_minimumPath[i][j].m_previousH = j+1;
    m_minimumPath[i][j].m_pathValueH = m_minimumPath[i-1][m_minimumPath[i][j].m_previousH].m_pathValueH + m_gradient[i][j];
  }
}

inline void SeamCarvingOperation::updateMinimumPathV(int i, int j) {
  if (j == 0) {
    m_minimumPath[i][0].m_pathValueV = m_gradient[i][0];
    m_minimumPath[i][0].m_previousV = -1;
  }
  else {
    m_minimumPath[i][j].m_previousV = i;
    if (i-1 >= 0 && m_minimumPath[i-1][j-1].m_pathValueV < m_minimumPath[m_minimumPath[i][j].m_previousV][j-1].m_pathValueV) 
      m_minimumPath[i][j].m_previousV = i-1;
    if (i+1 < m_width && m_minimumPath[i+1][j-1].m_pathValueV < m_minimumPath[m_minimumPath[i][j].m_previousV][j-1].m_pathValueV)
      m_minimumPath[i][j].m_previousV = i+1;
    m_minimumPath[i][j].m_pathValueV = m_minimumPath[m_minimumPath[i][j].m_previousV][j-1].m_pathValueV + m_gradient[i][j];
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
