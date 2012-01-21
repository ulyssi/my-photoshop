#include "SeamCarvingOperation.hh"

#include <cmath>
#include "PixelMod.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
SeamCarvingOperation::SeamCarvingOperation(Picture* picture) :
  m_picture(picture),
  // m_pictureData(new Matrix<unsigned int>(m_picture->getData())),
  // m_gradient(createGradientMatrix()),
  // m_minimumPathH(createMinimumPathH()),
  // m_minimumPathV(createMinimumPathV()),
  // m_pathH(new int[m_width]),
  // m_pathV(new int[m_height]),
  m_widthInit(m_picture->getWidth()),
  m_heightInit(m_picture->getHeight()),
  m_widthTarget(m_widthInit),
  m_heightTarget(m_heightInit),
  m_widthMax(m_widthInit),
  m_heightMax(m_heightInit),
  m_width(m_widthInit),
  m_height(m_heightInit),
  m_dataInit(createData()),
  m_indexH(createIndexH()),
  m_indexV(createIndexV())
{
  // m_sobelX[0][0] =  1; m_sobelX[0][1] =  2; m_sobelX[0][2] =  1;
  // m_sobelX[1][0] =  0; m_sobelX[1][1] =  0; m_sobelX[1][2] =  0;
  // m_sobelX[2][0] = -1; m_sobelX[2][1] = -2; m_sobelX[2][2] = -1;

  // m_sobelY[0][0] =  1; m_sobelY[0][1] =  0; m_sobelY[0][2] = -1;
  // m_sobelY[1][0] =  2; m_sobelY[1][1] =  0; m_sobelY[1][2] = -2;
  // m_sobelY[2][0] =  1; m_sobelY[2][1] =  0; m_sobelY[2][2] = -1;

  initializeData();
  initializeGradient2();

  // initializeGradientMatrix();
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

void SeamCarvingOperation::setTargetWidth(int widthTarget) { m_widthTarget = widthTarget; }

void SeamCarvingOperation::setTargetHeight(int heightTarget) { m_heightTarget = heightTarget; }


/** Methodes */
#include <iostream>
#include <cmath>

Matrix<unsigned int>* SeamCarvingOperation::updatePreview() {
  
  if (m_width != m_widthTarget) {
    initializeMinimumPathV2();
    while (m_widthTarget < m_width) deleteRow();
    while (m_width < m_widthTarget && m_width < m_widthInit) newRow();
  }
    
  if (m_height != m_heightTarget) {
    initializeMinimumPathH2();
    while (m_heightTarget < m_height) deleteLine();
    while (m_height < m_heightTarget && m_height < m_heightInit) newLine();
  }

  Matrix<unsigned int>* preview = new Matrix<unsigned int>(m_width, m_height);
  for (int i = 0; i < m_width; i++) {
    Point* point = m_indexH[i];
    for (int j = 0; j < m_height && point != NULL; j++) {
      preview->setValue(i, j, point->color);
      point = getSouthFrom(point);
    }
  }

  return preview;
}

Picture* SeamCarvingOperation::applyOperation() {
  return m_picture;
}


/** Accesseurs internes */
inline SeamCarvingOperation::Point* SeamCarvingOperation::getNorthFrom(Point* point) {
  if (point != NULL) return point->north;
  return NULL;
}

inline SeamCarvingOperation::Point* SeamCarvingOperation::getSouthFrom(Point* point) {
  if (point != NULL) return point->south;
  return NULL;
}

inline SeamCarvingOperation::Point* SeamCarvingOperation::getEastFrom(Point* point) {
  if (point != NULL) return point->east;
  return NULL;
}

inline SeamCarvingOperation::Point* SeamCarvingOperation::getWestFrom(Point* point) {
  if (point != NULL) return point->west;
  return NULL;
}

inline SeamCarvingOperation::Point* SeamCarvingOperation::getNorthEastFrom(Point* point) {
  return getEastFrom(getNorthFrom(point));
}

inline SeamCarvingOperation::Point* SeamCarvingOperation::getNorthWestFrom(Point* point) {
  return getWestFrom(getNorthFrom(point));
}

inline SeamCarvingOperation::Point* SeamCarvingOperation::getSouthEastFrom(Point* point) {
  return getEastFrom(getSouthFrom(point));
}

inline SeamCarvingOperation::Point* SeamCarvingOperation::getSouthWestFrom(Point* point) {
  return getWestFrom(getSouthFrom(point));
}


/** Methodes internes */
Matrix<SeamCarvingOperation::Point*>* SeamCarvingOperation::createData() {
  Matrix<unsigned int>* colorData = m_picture->getData();
  m_dataInit = new Matrix<Point*>(m_widthInit, m_heightInit);
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++) {
      Point* point = new Point;
      point->color = colorData->getValue(i, j);
      point->gradient = 0;
      point->pathValue = 0;
      point->previous = NULL;
      point->north = NULL;
      point->south = NULL;
      point->east = NULL;
      point->west = NULL;
      m_dataInit->setValue(i, j, point);
    }
  return m_dataInit;
}

SeamCarvingOperation::Point** SeamCarvingOperation::createIndexH() {
  m_indexH = new Point*[m_widthInit];
  for (int i = 0; i < m_widthInit; i++) m_indexH[i] = m_dataInit->getValue(i, 0);
  return m_indexH;
}

SeamCarvingOperation::Point** SeamCarvingOperation::createIndexV() {
  m_indexV = new Point*[m_heightInit];
  for (int j = 0; j < m_heightInit; j++) m_indexV[j] = m_dataInit->getValue(0, j);
  return m_indexV;
}

void SeamCarvingOperation::initializeData() {
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++) {
      Point* point = m_dataInit->getValue(i, j);
      if (j > 0) point->north = m_dataInit->getValue(i, j-1);
      if (j < m_heightInit-1) point->south = m_dataInit->getValue(i, j+1);
      if (i < m_widthInit-1) point->east = m_dataInit->getValue(i+1, j);
      if (i > 0) point->west = m_dataInit->getValue(i-1, j);
    }
}

void SeamCarvingOperation::initializeGradient2() {
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++)
      updateGradient(m_dataInit->getValue(i, j));
}

void SeamCarvingOperation::initializeMinimumPathH2() {
  for (int i = 0; i < m_width; i++) {
    Point* point = m_indexH[i];
    while (point != NULL) {
      updateMinimumPathH(point);
      point = point->south;
    }
  }
}

void SeamCarvingOperation::initializeMinimumPathV2() {
  for (int j = 0; j < m_height; j++) {
    Point* point = m_indexV[j];
    while (point != NULL) {
      updateMinimumPathV(point);
      point = point->east;
    }
  }
}

void SeamCarvingOperation::updateIndexH() {
  if (m_widthMax < m_widthTarget) {
    Point** index = new Point*[m_widthTarget];
    for (int i = 0; i < m_widthMax; i++) index[i] = m_indexH[i];
    for (int i = m_widthMax; i < m_widthTarget; i++) index[i] = NULL;
    m_widthMax = m_widthTarget;
    delete m_indexH;
    m_indexH = index;
  }
}

void SeamCarvingOperation::updateIndexV() {
  if (m_heightMax < m_heightTarget) {
    Point** index = new Point*[m_heightTarget];
    for (int j = 0; j < m_heightMax; j++) index[j] = m_indexV[j];
    for (int j = m_heightMax; j < m_heightTarget; j++) index[j] = NULL;
    m_heightMax = m_heightTarget;
    delete m_indexV;
    m_indexV = index;
  }
}

inline void SeamCarvingOperation::updateGradient(Point* point) {
  Point* p = NULL;
  int gradientX = 0, gradientY = 0;

  if ((p = getNorthEastFrom(point)) != NULL) {
    unsigned int color = p->color;
    int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
    gradientX -= intensity;
    gradientY += intensity;
  }
  
  if ((p = getNorthFrom(point)) != NULL) {
    unsigned int color = p->color;
    int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
    gradientY += 2 * intensity;
  }

  if ((p = getNorthWestFrom(point)) != NULL) {
    unsigned int color = p->color;
    int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
    gradientX += intensity;
    gradientY += intensity;
  }

  if ((p = getEastFrom(point)) != NULL) {
    unsigned int color = p->color;
    int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
    gradientX -= 2 * intensity;
  }

  if ((p = getWestFrom(point)) != NULL) {
    unsigned int color = p->color;
    int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
    gradientX += 2 * intensity;
  }

  if ((p = getSouthEastFrom(point)) != NULL) {
    unsigned int color = p->color;
    int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
    gradientX -= intensity;
    gradientY -= intensity;
  }
  
  if ((p = getSouthFrom(point)) != NULL) {
    unsigned int color = p->color;
    int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
    gradientY -= 2 * intensity;
  }

  if ((p = getSouthWestFrom(point)) != NULL) {
    unsigned int color = p->color;
    int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
    gradientX += intensity;
    gradientY -= intensity;
  }

  // double alpha = atan((double)gradientY/(double)gradientX);
  point->gradient = gradientX * gradientX + gradientY * gradientY;
}

inline void SeamCarvingOperation::updateMinimumPathH(Point* point) {
  point->previous = NULL;
  point->pathValue = point->gradient;
  Point* previous[3] = { getNorthWestFrom(point),
                         getWestFrom(point),
                         getSouthWestFrom(point)
  };
  for (int i = 0; i < 3; i++)
    if (previous[i] != NULL && (point->previous == NULL || previous[i]->pathValue < point->previous->pathValue))
      point->previous = previous[i];
  if (point->previous != NULL) point->pathValue += point->previous->pathValue;
}

inline void SeamCarvingOperation::updateMinimumPathV(Point* point) {
  point->previous = NULL;
  point->pathValue = point->gradient;
  Point* previous[3] = { getNorthWestFrom(point),
                         getNorthFrom(point),
                         getNorthEastFrom(point)
  };
  for (int i = 0; i < 3; i++)
    if (previous[i] != NULL && (point->previous == NULL || previous[i]->pathValue < point->previous->pathValue))
      point->previous = previous[i];
  if (point->previous != NULL) point->pathValue += point->previous->pathValue;
}

void SeamCarvingOperation::deleteRow() {
  
  // recherche du chemin de plus faible poids
  Point *pMin = NULL, *pCur = m_indexV[m_height-1];
  for (int i = 0; i < m_width && pCur != NULL; i++) {
    if (pMin == NULL || pCur->pathValue < pMin->pathValue) pMin = pCur;
    pCur = pCur->east;
  }
  
  // tracer du chemin en rouge
  pCur = pMin;
  for (int j = 0; j < m_height && pCur != NULL; j++) {
    pCur->color = PixelMod::createRGB(255, 0, 0);
    // Point* pNext = pCur;
    pCur = pCur->previous;
    // if (pCur != NULL) pCur->next = pNext;
  }
  
  // suppression du chemin

  // int xFinal = 0, xInit;
  // for (int i = 1; i < m_width; i++)
  //   if (m_minimumPathV[i][m_height-1].m_pathValue < m_minimumPathV[xFinal][m_height-1].m_pathValue) 
  //     xFinal = i;
  // m_pathV[m_height-1] = xFinal;
  // for (int j = m_height-1; j > 0; j--) m_pathV[j-1] = m_minimumPathV[m_pathV[j]][j].m_previous;
  // m_width--;
  
//   // mise a jour des donnees de l'image
//   for (int j = 0; j < m_height; j++)
//     for (int i = m_pathV[j]; i < m_width; i++) {
//       pictureData[i][j] = pictureData[i+1][j];
//       m_gradient[i][j] = m_gradient[i+1][j];
//       m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i+1][j].m_pathValue;
//       m_minimumPathV[i][j].m_previous = m_minimumPathV[i+1][j].m_previous-1;
//     }
  
//   // mise a jour des gradients locaux
//   for (int j = 0; j < m_height; j++)
//     for (int i = m_pathV[j]-1; i <= m_pathV[j]+1; i++)
//       if (0 <= i && i < m_width)
// 	updateGradient(i, j);

//   // mise a jour des chemins
//   int xMin = m_pathV[0], xMax = m_pathV[0]+1;
//   for (int j = 0; j < m_height; j++) {
//     int min = xMin-1, max = xMax+1;
//     for (int i = xMin; i < xMax; i++) {
//       unsigned int pathValue = m_minimumPathV[i][j].m_pathValue;
//       updateMinimumPathV(i, j);
//       if (pathValue != m_minimumPathV[i][j].m_pathValue) {
//       	if (min == xMin-1) min = i-2;
//       	max = i+3;
//       }
//     }
//     if (min < 0) xMin = 0; else xMin = min;
//     if (max > m_width) xMax = m_width; else xMax = max;
//   }
  m_width--;
}

void SeamCarvingOperation::newRow() {
  m_width++;
}

void SeamCarvingOperation::deleteLine() {
  m_height--;
}

void SeamCarvingOperation::newLine() {
  m_height++;
}

// SeamCarvingOperation::Path** SeamCarvingOperation::createMinimumPathH() {
//   m_minimumPathH = new Path*[m_width];
//   for (int i = 0; i < m_width; i++) m_minimumPathH[i] = new Path[m_height];
//   return m_minimumPathH;
// }

// SeamCarvingOperation::Path** SeamCarvingOperation::createMinimumPathV() {
//   m_minimumPathV = new Path*[m_width];
//   for (int i = 0; i < m_width; i++) m_minimumPathV[i] = new Path[m_height];
//   return m_minimumPathV;
// }

// unsigned int** SeamCarvingOperation::createGradientMatrix() {
//   m_gradient = new unsigned int*[m_width];
//   for (int i = 0; i < m_width; i++) {
//     m_gradient[i] = new unsigned int[m_height];
//     for (int j = 0; j < m_height; j++) updateGradient(i, j);
//   }
//   return m_gradient;
// }

// void SeamCarvingOperation::initializeGradientMatrix() {
//   for (int i = 0; i < m_width; i++)
//     for (int j = 0; j < m_height; j++)
//       updateGradient(i, j);
// }

// void SeamCarvingOperation::initializeMinimumPathH() {
//   for (int i = 0; i < m_width; i++)
//     for (int j = 0; j < m_height; j++)
//       updateMinimumPathH(i, j);
// }

// void SeamCarvingOperation::initializeMinimumPathV() {
//   for (int j = 0; j < m_height; j++)
//     for (int i = 0; i < m_width; i++)
//       updateMinimumPathV(i, j);
// }

// void SeamCarvingOperation::deleteRow() {
//   unsigned int** pictureData = m_pictureData->getData();

//   // recherche du chemin de plus faible poids
//   int xFinal = 0, xInit;
//   for (int i = 1; i < m_width; i++)
//     if (m_minimumPathV[i][m_height-1].m_pathValue < m_minimumPathV[xFinal][m_height-1].m_pathValue) 
//       xFinal = i;
//   m_pathV[m_height-1] = xFinal;
//   for (int j = m_height-1; j > 0; j--) m_pathV[j-1] = m_minimumPathV[m_pathV[j]][j].m_previous;
//   m_width--;
  
//   // mise a jour des donnees de l'image
//   for (int j = 0; j < m_height; j++)
//     for (int i = m_pathV[j]; i < m_width; i++) {
//       pictureData[i][j] = pictureData[i+1][j];
//       m_gradient[i][j] = m_gradient[i+1][j];
//       m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i+1][j].m_pathValue;
//       m_minimumPathV[i][j].m_previous = m_minimumPathV[i+1][j].m_previous-1;
//     }
  
//   // mise a jour des gradients locaux
//   for (int j = 0; j < m_height; j++)
//     for (int i = m_pathV[j]-1; i <= m_pathV[j]+1; i++)
//       if (0 <= i && i < m_width)
// 	updateGradient(i, j);

//   // mise a jour des chemins
//   int xMin = m_pathV[0], xMax = m_pathV[0]+1;
//   for (int j = 0; j < m_height; j++) {
//     int min = xMin-1, max = xMax+1;
//     for (int i = xMin; i < xMax; i++) {
//       unsigned int pathValue = m_minimumPathV[i][j].m_pathValue;
//       updateMinimumPathV(i, j);
//       if (pathValue != m_minimumPathV[i][j].m_pathValue) {
//       	if (min == xMin-1) min = i-2;
//       	max = i+3;
//       }
//     }
//     if (min < 0) xMin = 0; else xMin = min;
//     if (max > m_width) xMax = m_width; else xMax = max;
//   }

//   // initializeMinimumPathV();
// }

// void SeamCarvingOperation::deleteLine() {
//   unsigned int** pictureData = m_pictureData->getData();

//   // recherche du chemin de plus faible poids
//   int yFinal = 0;
//   for (int j = 1; j < m_height; j++)
//     if (m_minimumPathH[m_width-1][j].m_pathValue < m_minimumPathH[m_width-1][yFinal].m_pathValue) 
//       yFinal = j;

//   // mise a jour des donnees de l'image
//   m_height--;
//   int yTmp = yFinal;
//   for (int i = m_width-1; i >= 0; i--) {
//     for (int j = yTmp; j < m_height; j++) {
//       pictureData[i][j] = pictureData[i][j+1];
//       m_gradient[i][j] = m_gradient[i][j+1];
//     }
//     yTmp = m_minimumPathH[i][yTmp].m_previous;
//   }

//   // mise a jour des gradients locaux
//   yTmp = yFinal;
//   for (int i = m_width-1; i >= 0; i--) {
//     for (int j = yTmp-2; j <= yTmp+2; j++)
//       if (0 <= j && j < m_height) 
// 	updateGradient(i, j);
//     yTmp = m_minimumPathH[i][yTmp].m_previous;
//   }
// }

// inline void SeamCarvingOperation::updateMinimumPathH(int i, int j) {
//   if (i == 0) {
//     m_minimumPathH[0][j].m_pathValue = m_gradient[0][j];
//     m_minimumPathH[0][j].m_previous = -1;
//   }
//   else {
//     unsigned int k = m_gradient[i][j];
//     unsigned int kSide = k;
//     m_minimumPathH[i][j].m_previous = j;
//     m_minimumPathH[i][j].m_pathValue = m_minimumPathH[i-1][j].m_pathValue + k;
//     if (j-1 >= 0 && m_minimumPathH[i-1][j-1].m_pathValue + kSide < m_minimumPathH[i-1][m_minimumPathH[i][j].m_previous].m_pathValue) {
//       m_minimumPathH[i][j].m_previous = j-1;
//       m_minimumPathH[i][j].m_pathValue = m_minimumPathH[i-1][j-1].m_pathValue + kSide;
//     }
//     if (j+1 < m_height && m_minimumPathH[i-1][j+1].m_pathValue < m_minimumPathH[i-1][m_minimumPathH[i][j].m_previous].m_pathValue) {
//       m_minimumPathH[i][j].m_previous = j+1;
//       m_minimumPathH[i][j].m_pathValue = m_minimumPathH[i-1][j+1].m_pathValue + kSide;
//     }
//   }
// }

// inline void SeamCarvingOperation::updateMinimumPathV(int i, int j) {
//   if (j == 0) {
//     m_minimumPathV[i][0].m_pathValue = m_gradient[i][0];
//     m_minimumPathV[i][0].m_previous = -1;
//   }
//   else {
//     unsigned int k = m_gradient[i][j];
//     unsigned int kSide = k;
//     m_minimumPathV[i][j].m_previous = i;
//     m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i][j-1].m_pathValue + k;
//     if (i-1 >= 0 && m_minimumPathV[i-1][j-1].m_pathValue < m_minimumPathV[m_minimumPathV[i][j].m_previous][j-1].m_pathValue) {
//       m_minimumPathV[i][j].m_previous = i-1;
//       m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i-1][j-1].m_pathValue + kSide;
//     }
//     if (i+1 < m_width && m_minimumPathV[i+1][j-1].m_pathValue < m_minimumPathV[m_minimumPathV[i][j].m_previous][j-1].m_pathValue) {
//       m_minimumPathV[i][j].m_previous = i+1;
//       m_minimumPathV[i][j].m_pathValue = m_minimumPathV[i+1][j-1].m_pathValue + kSide;
//     }
//   }
// }

// inline void SeamCarvingOperation::updateGradient(int i, int j) {
//   int gradientX = 0, gradientY = 0;
//   for (int i2 = 0; i2 < 3; i2++)
//     for (int j2 = 0; j2 < 3; j2++) {
//       int x = (i - 1 + i2 + m_width) % m_width;
//       int y = (j - 1 + j2 + m_height) % m_height;
//       unsigned int color = m_pictureData->getValue(x, y);
//       int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
//       gradientX += intensity * m_sobelX[i2][j2];
//       gradientY += intensity * m_sobelY[i2][j2];
//     }
//   // double alpha = atan((double)gradientY/(double)gradientX);
//   m_gradient[i][j] = gradientX * gradientX + gradientY * gradientY;
// }
