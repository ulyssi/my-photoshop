#include "SeamCarvingOperation.hh"

#include <cmath>
#include "PixelMod.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
SeamCarvingOperation::SeamCarvingOperation(Picture* picture) :
  m_picture(picture),
  m_pictureData(picture->getData()),
  m_widthInit(m_picture->getWidth()),
  m_heightInit(m_picture->getHeight()),
  m_widthTarget(m_widthInit),
  m_heightTarget(m_heightInit),
  m_width(m_widthInit),
  m_height(m_heightInit),
  m_data(createData()),
  m_iteration(0)
{
  refreshData();
  refreshGradient();
  refreshMinimumPathV();

}

SeamCarvingOperation::~SeamCarvingOperation() {}


/** Accesseurs */
void SeamCarvingOperation::setTargetWidth(int widthTarget) { m_widthTarget = widthTarget; }

void SeamCarvingOperation::setTargetHeight(int heightTarget) { m_heightTarget = heightTarget; }


/** Methodes */
#include <cmath>
Matrix<unsigned int>* SeamCarvingOperation::updatePreview() {

  // refreshGradient();
  // refreshMinimumPathV();

  int level = m_widthTarget - m_widthInit;
  
  while (m_iteration < fabs(level)) {
    computeRemoveRow(m_iteration);
    m_iteration++;
  }

  
  // TEST [ affichage de l'image initiale avec marqueur ]
  Matrix<unsigned int>* preview = new Matrix<unsigned int>(m_widthInit, m_heightInit);
  for (int i = 0; i < m_widthInit; i++) {
    for (int j = 0; j < m_heightInit; j++) {
      if (m_data->getValue(i, j)->mask != 0) preview->setValue(i, j, PixelMod::createRGB(255, 0, 0));
      else preview->setValue(i, j, m_data->getValue(i, j)->color);
    }
  }

  // Matrix<unsigned int>* preview = new Matrix<unsigned int>(m_widthTarget, m_heightTarget);
  // for (int i = 0; i < m_widthInit; i++) {
  //   int nbPixelX = 0;
  //   for (int j = 0; j < m_heightInit; j++) {
  //     // preview->setValue(i, j, PixelMod::createGrayScale(PixelMod::threshold(m_data->getValue(i, j)->gradient)));
  //     if (m_data->getValue(i, j)->mask == 0) {
  //       preview->setValue(nbPixelX, j, m_data->getValue(i, j)->color);
  //       nbPixelX++;
  //     }
  //   }
  // }
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
  m_data = new Matrix<Point*>(m_widthInit, m_heightInit);
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++) {
      Point* point = new Point;
      point->color = m_pictureData->getValue(i, j);
      point->gradient = 0;
      point->pathValue = 0;
      point->mask = 0;
      point->previous = NULL;
      point->next = NULL;
      point->north = NULL;
      point->south = NULL;
      point->east = NULL;
      point->west = NULL;
      m_data->setValue(i, j, point);
    }
  return m_data;
}
 

void SeamCarvingOperation::refreshData() { 
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++) {
      Point* point = m_data->getValue(i, j);
      if (j == 0) point->north = NULL;
      else point->north = m_data->getValue(i, j-1);

      if (j == m_heightInit-1) point->south = NULL;
      else point->south = m_data->getValue(i, j+1);

      if (i == m_widthInit-1) point->east = NULL;
      else point->east = m_data->getValue(i+1, j);
      
      if (i == 0) point->west = NULL;
      else point->west = m_data->getValue(i-1, j);
    }
}

void SeamCarvingOperation::refreshGradient() {
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++)
      updateGradient(m_data->getValue(i, j));
}

void SeamCarvingOperation::refreshMinimumPathH() {
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++)
      updateMinimumPathH(m_data->getValue(i, j));
}

void SeamCarvingOperation::refreshMinimumPathV() {
  for (int j = 0; j < m_heightInit; j++)
    for (int i = 0; i < m_widthInit; i++)
      updateMinimumPathV(m_data->getValue(i, j));
}

inline void SeamCarvingOperation::updateGradient(Point* point) {
  int sobelX[3][3] = {{ 1 , 0 ,-1 }, { 2 , 0 ,-2 }, { 1 , 0 ,-1 }};
  int sobelY[3][3] = {{ 1 , 2 , 1 }, { 0 , 0 , 0 }, {-1 ,-2 ,-1 }};
  Point* area[3][3] = {
    { getNorthWestFrom(point) , getNorthFrom(point) , getNorthEastFrom(point) },
    { getWestFrom(point)      , NULL                , getEastFrom(point)      },
    { getSouthWestFrom(point) , getSouthFrom(point) , getSouthEastFrom(point) }
  };

  int gradientX = 0, gradientY = 0;
  for (int i = 0; i < 3; i++) 
    for (int j = 0; j < 3; j++)
      if (area[i][j] != NULL) {
        unsigned int color = area[i][j]->color;
        int intensity = PixelMod::getRed(color) + PixelMod::getGreen(color) + PixelMod::getBlue(color);
        gradientX += sobelX[i][j] * intensity;
        gradientY += sobelY[i][j] * intensity;
      }
  
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

void SeamCarvingOperation::computeRemoveRow(int iteration) {

  // recherche du chemin de plus faible poids
  Point *pMin = NULL;
  for (int i = 0; i < m_widthInit; i++)
    if (m_data->getValue(i, m_heightInit-1)->mask == 0)
      if (pMin == NULL || m_data->getValue(i, m_heightInit-1)->pathValue < pMin->pathValue)
  	pMin = m_data->getValue(i, m_heightInit-1);


  // suppression du chemin
  Point* pInit = NULL;
  for (Point* pCur = pMin; pCur != NULL; pCur = pCur->previous) {
    Point *pPrec = pCur->previous;
    Point *pGauche = getWestFrom(pCur), *pDroit = getEastFrom(pCur);
    Point *pHautGauche = getNorthWestFrom(pCur), *pHaut = getNorthFrom(pCur), *pHautDroit = getNorthEastFrom(pCur);
    
    // Chainage lateral
    if (pDroit != NULL) pDroit->west = pGauche;
    if (pGauche != NULL) pGauche->east = pDroit;

    // Chainage haut
    if (pPrec != NULL) {
      if (pPrec == pHautGauche) {
    	pGauche->north = pHaut;
    	pHaut->south = pGauche;
      }
      else if (pPrec == pHautDroit) {
    	pDroit->north = pHaut;
    	pHaut->south = pDroit;
      }
      pPrec->next = pCur;
      pInit = pCur;
    }
    pCur->mask = iteration;
  }

  // mise a jour des gradients locaux
  for (Point *pCur = pMin; pCur != NULL; pCur = pCur->previous) {
    Point *pGauche = getWestFrom(pCur), *pDroit = getEastFrom(pCur);
    if (pGauche != NULL) {
      // pGauche->mask = iteration;
      updateGradient(pGauche);
      if (pGauche->west != NULL) {
        // pGauche->west->mask = iteration;
        updateGradient(pGauche->west);
      }
    }
    
    if (pDroit != NULL) {
      // pDroit->mask = iteration;
      updateGradient(pDroit);
      if (pDroit->east != NULL) {
        // pDroit->east->mask = iteration;
        updateGradient(pDroit->east);
      }
    }
  }

  // mise a jour des chemins
  Point *pInf = getWestFrom(pInit), *pSup = getEastFrom(pInit);
  for (int j = 1; j < m_height; j++) {
    Point* inf = pInf, *sup = pSup;
    if (inf == NULL) inf = m_data->getValue(0, j);
    if (sup != NULL) sup = sup->east;
    for (Point* pCur = inf; pCur != sup; pCur = pCur->east) {
      // pCur->mask = iteration;
      updateMinimumPathV(pCur);
    }
    pInf = getSouthWestFrom(pInf);
    pSup = getSouthEastFrom(pSup);
  }
}

void SeamCarvingOperation::computeRemoveLine(int iteration) {
  m_height--;
}
