#include "SeamCarvingOperation.hh"

#include <cmath>
#include "PixelMod.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
SeamCarvingOperation::SeamCarvingOperation(Picture* picture) :
  m_picture(picture),
  m_pictureData(new Matrix<unsigned int>(picture->getData())),
  m_gradient(createGradientMatrix()),
  m_minimumPath(createMinimumPath()),
  m_targetSizeX(m_pictureData->getWidth()),
  m_targetSizeY(m_pictureData->getHeight())
{
  initializeMinimumPathX();
  initializeMinimumPathY();
}

SeamCarvingOperation::~SeamCarvingOperation() {}


/** Accesseurs */
void SeamCarvingOperation::setTargetSizeX(int targetSizeX) { m_targetSizeX = targetSizeX; }
void SeamCarvingOperation::setTargetSizeY(int targetSizeY) { m_targetSizeY = targetSizeY; }


/** Methodes */
Matrix<unsigned int>* SeamCarvingOperation::updatePreview() {
  int width = m_pictureData->getWidth(), height = m_pictureData->getHeight();
  
  int yPath = 0;
  for (int i = 1; i < width; i++) {
    if (m_minimumPath[i][height-1].m_pathValueY < m_minimumPath[yPath][height-1].m_pathValueY) yPath = i;
  }

  for (int j = height-1; j > 0; j--) {
    m_pictureData->setValue(yPath, j, PixelMod::createRGB(255, 0, 0));
    yPath = m_minimumPath[yPath][j].m_previousY;
  }
  m_pictureData->setValue(yPath, 0, PixelMod::createRGB(255, 0, 0));
  
  return m_pictureData;
}

Picture* SeamCarvingOperation::applyOperation() {
  return m_picture;
}


/** Methodes internes */
SeamCarvingOperation::Path** SeamCarvingOperation::createMinimumPath() {
  int width = m_pictureData->getWidth(), height = m_pictureData->getHeight();
  
  m_minimumPath = new Path*[width];
  for (int i = 0; i < width; i++) {
    m_minimumPath[i] = new Path[height];
    for (int j = 0; j < height; j++) {
      if (i == 0) {
	m_minimumPath[i][j].m_pathValueX = m_gradient[i][j];
	m_minimumPath[i][j].m_previousX = -1;
      }
      else {
	m_minimumPath[i][j].m_pathValueX = 0;
	m_minimumPath[i][j].m_previousX = i;
      }

      if (j == 0) {
	m_minimumPath[i][j].m_pathValueY = m_gradient[i][j];
	m_minimumPath[i][j].m_previousY = -1;
      }
      else {
	m_minimumPath[i][j].m_pathValueY = 0;
	m_minimumPath[i][j].m_previousY = j;
      }
    }
  }

  return m_minimumPath;
}

unsigned int** SeamCarvingOperation::createGradientMatrix() {
  int width = m_pictureData->getWidth(), height = m_pictureData->getHeight();
  int sobelX[3][3] = {{  1,  2,  1}, {  0,  0,  0}, { -1, -2, -1}};
  int sobelY[3][3] = {{  1,  0, -1}, {  2,  0, -2}, {  1,  0, -1}};

  m_gradient = new unsigned int*[width];
  for (int i = 0; i < width; i++) {
    m_gradient[i] = new unsigned int[height];
    for (int j = 0; j < height; j++) {
      int gradientX = 0, gradientY = 0;
      for (int i2 = 0; i2 < 3; i2++)
	for (int j2 = 0; j2 < 3; j2++) {
          unsigned int color = m_pictureData->getValue((i + i2 + width) % width, (j + j2 + height) % height);
          int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
	  gradientX += intensity * sobelX[i2][j2];
	  gradientY += intensity * sobelY[i2][j2];
	}
      // double alpha = atan((double)gradientY/(double)gradientX);
      m_gradient[i][j] = gradientX * gradientX + gradientY * gradientY;
    }
  }
  return m_gradient;
}

void SeamCarvingOperation::initializeMinimumPathX() {
  int width = m_pictureData->getWidth(), height = m_pictureData->getHeight();
  for (int i = 1; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (j-1 >= 0 && m_minimumPath[i-1][j-1].m_pathValueX < m_minimumPath[i-1][m_minimumPath[i][j].m_previousX].m_pathValueX) m_minimumPath[i][j].m_previousX = j-1;
      if (j+1 < height && m_minimumPath[i-1][j+1].m_pathValueX < m_minimumPath[i-1][m_minimumPath[i][j].m_previousX].m_pathValueX) m_minimumPath[i][j].m_previousX = j+1;
      m_minimumPath[i][j].m_pathValueX = m_minimumPath[i-1][m_minimumPath[i][j].m_previousX].m_pathValueX + m_gradient[i][j];
    }
  }
}

void SeamCarvingOperation::initializeMinimumPathY() {
  int width = m_pictureData->getWidth(), height = m_pictureData->getHeight();
  for (int j = 1; j < height; j++) {
    for (int i = 0; i < width; i++) {
      if (i-1 >= 0 && m_minimumPath[i-1][j-1].m_pathValueY < m_minimumPath[m_minimumPath[i][j].m_previousY][j-1].m_pathValueY) m_minimumPath[i][j].m_previousY = i-1;
      if (i+1 < width && m_minimumPath[i+1][j-1].m_pathValueY < m_minimumPath[m_minimumPath[i][j].m_previousY][j-1].m_pathValueY) m_minimumPath[i][j].m_previousY = i+1;
      m_minimumPath[i][j].m_pathValueY = m_minimumPath[m_minimumPath[i][j].m_previousY][j-1].m_pathValueY + m_gradient[i][j];
    }
  }
}
