#include "SeamCarvingOperation.hh"

#include "PixelMod.hh"
#include "Picture.hh"
#include "Tracing.hh"


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
  m_dataV(createData()),
  m_iteration(0),
  m_iterationV(0),
  m_pathValue(new int[m_widthInit])
{
  refreshData();
  refreshGradient();

  refreshDataV();
  refreshGradientV();
}

SeamCarvingOperation::~SeamCarvingOperation() {}


/** Accesseurs */
void SeamCarvingOperation::setTargetWidth(int widthTarget) { m_widthTarget = widthTarget; }

void SeamCarvingOperation::setTargetHeight(int heightTarget) { m_heightTarget = heightTarget; }


/** Methodes */
#include <iostream>
Matrix<unsigned int>* SeamCarvingOperation::updatePreview() {

  // TEST [ affichage de l'image initiale avec marqueur ]
  // refreshMinimumPathH(); computeRemoveLine(m_iteration+1);
  // refreshMinimumPathV(); computeRemoveRow(m_iteration+1);
  // Matrix<unsigned int>* preview = new Matrix<unsigned int>(m_widthInit, m_heightInit);
  // for (int i = 0; i < m_widthInit; i++) {
  //   for (int j = 0; j < m_heightInit; j++) {
  //     if (m_data->getValue(i, j)->test) {
  //       preview->setValue(i, j, PixelMod::createRGB(255, 0, 0));
  //       m_data->getValue(i, j)->test = false;
  //     }
  //     else preview->setValue(i, j, m_data->getValue(i, j)->color);
  //   }
  // }

  if (m_widthInit != m_widthTarget) return updatePreviewHorizontal();
  if (m_heightInit != m_heightTarget) return updatePreviewVertical();
  return m_pictureData;
}

Matrix<unsigned int>* SeamCarvingOperation::updatePreviewHorizontal() {
  int level = 0;
  bool copy = true;
  if (m_widthTarget < m_widthInit) {
    copy = false;
    level = m_widthInit - m_widthTarget;
  }
  else level = m_widthTarget - m_widthInit;

  refreshMinimumPathV();
  while (m_iteration < level) m_pathValue[m_iteration-1] = computeRemoveRow(++m_iteration);

  // unsigned int sum = 0;
  // for (int i = 0; i < level; i++) sum += m_pathValue[i];
   
  // double* coef = new double[level];
  // for (int i = 0; i < level; i++) coef[i] = ((double)m_pathValue[i]) / ((double)sum);
  // for (int i = 0; i < level-1; i++) {
  //   coef[i] /= coef[i+1];
  //   std::cout << coef[i] << " ";
  // }
  // std::cout << std::endl;
  //   //   coef[i-1] = ((double)m_pathValue[i]) * coef[i] / ((double)m_pathValue[i-1]);

  Matrix<unsigned int>* preview = new Matrix<unsigned int>(m_widthTarget, m_heightTarget);
  for (int j = 0; j < m_heightInit; j++) {
    m_width = 0;
    // int insert = 0;
    for (int i = 0; i < m_widthInit; i++) {
      if (copy) {
        preview->setValue(m_width++, j, m_data->getValue(i, j)->color);
        if (0 < m_data->getValue(i, j)->mask && m_data->getValue(i, j)->mask <= level) {
	  // int k = 0;
          // while (level > insert && k < floor((double)level * coef[m_data->getValue(i, j)->mask-1]+0.5)) {
            preview->setValue(m_width++, j, m_data->getValue(i, j)->color);
	  //   insert++;
	  // }
	}
      }
      else if (m_data->getValue(i, j)->mask == 0 || level < m_data->getValue(i, j)->mask)
        preview->setValue(m_width++, j, m_data->getValue(i, j)->color);
    }
  }

  return preview;
}

Matrix<unsigned int>* SeamCarvingOperation::updatePreviewVertical() {
  int level = 0;
  bool copy = true;
  if (m_heightTarget < m_heightInit) {
    copy = false;
    level = m_heightInit - m_heightTarget;
  }
  else level = m_heightTarget - m_heightInit;

  refreshMinimumPathH();  
  while (m_iterationV < level) m_pathValue[m_iterationV-1] = computeRemoveLine(++m_iterationV);
  
  Matrix<unsigned int>* preview = new Matrix<unsigned int>(m_widthTarget, m_heightTarget);
  for (int i = 0; i < m_widthInit; i++) {
    m_height = 0;
    for (int j = 0; j < m_heightInit; j++) {
      if (copy) {
        preview->setValue(i, m_height++, m_dataV->getValue(i, j)->color);
        if (0 < m_dataV->getValue(i, j)->mask && m_dataV->getValue(i, j)->mask <= level)
          preview->setValue(i, m_height++, m_dataV->getValue(i, j)->color);
      }
      else if (m_dataV->getValue(i, j)->mask == 0 || level < m_dataV->getValue(i, j)->mask)
        preview->setValue(i, m_height++, m_dataV->getValue(i, j)->color);
    }
  }

  return preview;
}

Picture* SeamCarvingOperation::applyOperation() {
  m_pictureData = m_picture->getData();
  m_picture->getBackground()->setData(updatePreview());
  m_picture->refresh();
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
  Matrix<Point*>* data = new Matrix<Point*>(m_widthInit, m_heightInit);
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++)
      data->setValue(i, j, new Point);
  return data;
}
 

void SeamCarvingOperation::refreshData() { 
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++) {
      Point* point = m_data->getValue(i, j);
      point->color = m_pictureData->getValue(i, j);
      point->gradient = 0;
      point->pathValue = 0;
      point->mask = 0;
      point->previous = NULL;
      point->next = NULL;
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

void SeamCarvingOperation::refreshDataV() { 
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++) {
      Point* point = m_dataV->getValue(i, j);
      point->color = m_pictureData->getValue(i, j);
      point->gradient = 0;
      point->pathValue = 0;
      point->mask = 0;
      point->previous = NULL;
      point->next = NULL;
      if (j == 0) point->north = NULL;
      else point->north = m_dataV->getValue(i, j-1);

      if (j == m_heightInit-1) point->south = NULL;
      else point->south = m_dataV->getValue(i, j+1);

      if (i == m_widthInit-1) point->east = NULL;
      else point->east = m_dataV->getValue(i+1, j);
      
      if (i == 0) point->west = NULL;
      else point->west = m_dataV->getValue(i-1, j);      // point->test = false;
    }
}

void SeamCarvingOperation::refreshGradient() {
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++)
      updateGradient(m_data->getValue(i, j));
}

void SeamCarvingOperation::refreshGradientV() {
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++)
      updateGradient(m_dataV->getValue(i, j));
}

void SeamCarvingOperation::refreshMinimumPathH() {
  for (int i = 0; i < m_widthInit; i++)
    for (int j = 0; j < m_heightInit; j++)
      updateMinimumPathH(m_dataV->getValue(i, j));
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

unsigned int SeamCarvingOperation::computeRemoveRow(int iteration) {
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

    // Chainage vertical
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
    } 
    else pInit = pCur;
    pCur->mask = iteration;
  }

  // mise a jour des gradients locaux
  for (Point *pCur = pMin; pCur != NULL; pCur = pCur->previous) {
    Point *pPrec = pCur->previous, *pNext = pCur->next;
    Point *pGauche = getWestFrom(pCur), *pDroit = getEastFrom(pCur);

    if (pGauche != NULL) {
      // pGauche->test = true;
      updateGradient(pGauche);
      Point *pHautGauche = getNorthWestFrom(pCur), *pBasGauche = getSouthWestFrom(pCur);
      if (pGauche->west != NULL && ((pPrec != NULL && pPrec == pHautGauche) || (pNext != NULL && pNext == pBasGauche))) {
        // pGauche->west->test = true;
        updateGradient(pGauche->west);
      }
    }
    
    if (pDroit != NULL) {
      // pDroit->test = true;
      updateGradient(pDroit);
      Point *pHautDroit = getNorthEastFrom(pCur), *pBasDroit = getSouthEastFrom(pCur);
      if (pDroit->east != NULL && ((pPrec != NULL && pPrec == pHautDroit) || (pNext != NULL && pNext == pBasDroit))) {
        // pDroit->east->test = true;
        updateGradient(pDroit->east);
      }
    }
  }

  // mise a jour des chemins
  Point *pInf = getWestFrom(pInit), *pSup = getEastFrom(pInit);
  for (Point* pCur = pInit; pCur != NULL; pCur = pCur->next) {
    Point* inf = pInf, *sup = pSup;
    for (Point* point = pCur->west; point != getWestFrom(pInf); point = point->west) {
      unsigned int pathValue = point->pathValue;
      updateMinimumPathV(point);
      // point->test = true;
      if (point->pathValue != pathValue) inf = point;
    }
    pInf = getSouthWestFrom(inf);

    for (Point* point = pCur->east; point != getEastFrom(pSup); point = point->east) {
      unsigned int pathValue = point->pathValue;
      updateMinimumPathV(point);
      // point->test = true;
      if (point->pathValue != pathValue) sup = point;
    }
    pSup = getSouthEastFrom(sup);
  }
  return pMin->pathValue;
}

unsigned int SeamCarvingOperation::computeRemoveLine(int iteration) {
  // recherche du chemin de plus faible poids
  Point *pMin = NULL;
  for (int j = 0; j < m_heightInit; j++)
    if (m_dataV->getValue(m_widthInit-1, j)->mask == 0)
      if (pMin == NULL || m_dataV->getValue(m_widthInit-1, j)->pathValue < pMin->pathValue)
        pMin = m_dataV->getValue(m_widthInit-1, j);

  // suppression du chemin
  Point* pInit = NULL;
  for (Point* pCur = pMin; pCur != NULL; pCur = pCur->previous) {
    Point *pPrec = pCur->previous;
    Point *pBas = getSouthFrom(pCur), *pHaut = getNorthFrom(pCur);
    Point *pHautGauche = getNorthWestFrom(pCur), *pGauche = getWestFrom(pCur), *pBasGauche = getSouthWestFrom(pCur);
    
    // Chainage vertical
    if (pHaut != NULL) pHaut->south = pBas;
    if (pBas != NULL) pBas->north = pHaut;

    // Chainage lateral
    if (pPrec != NULL) {
      if (pPrec == pBasGauche) {
    	pBas->west = pGauche;
    	pGauche->east = pBas;
      }
      else if (pPrec == pHautGauche) {
    	pHaut->west = pGauche;
    	pGauche->east = pHaut;
      }
      pPrec->next = pCur;
    } 
    else pInit = pCur;
    pCur->mask = iteration;
  }

  // mise a jour des gradients locaux
  for (Point *pCur = pMin; pCur != NULL; pCur = pCur->previous) {
    Point *pPrec = pCur->previous, *pNext = pCur->next;
    Point *pBas = getSouthFrom(pCur), *pHaut = getNorthFrom(pCur);

    if (pBas != NULL) {
      // pBas->test = true;
      updateGradient(pBas);
      Point *pBasGauche = getSouthWestFrom(pCur), *pBasDroit = getSouthEastFrom(pCur);
      if (pBas->south != NULL && ((pPrec != NULL && pPrec == pBasGauche) || (pNext != NULL && pNext == pBasDroit))) {
        // pBas->south->test = true;
        updateGradient(pBas->south);
      }
    }
    
    if (pHaut != NULL) {
      // pHaut->test = true;
      updateGradient(pHaut);
      Point *pHautGauche = getNorthWestFrom(pCur), *pHautDroit = getNorthEastFrom(pCur);
      if (pHaut->north != NULL && ((pPrec != NULL && pPrec == pHautGauche) || (pNext != NULL && pNext == pHautDroit))) {
        // pHaut->north->test = true;
        updateGradient(pHaut->north);
      }
    }
  }

  // mise a jour des chemins
  Point *pInf = getSouthFrom(pInit), *pSup = getNorthFrom(pInit);
  for (Point* pCur = pInit; pCur != NULL; pCur = pCur->next) {
    Point* inf = pInf, *sup = pSup;
    for (Point* point = pCur->south; point != getSouthFrom(pInf); point = point->south) {
      unsigned int pathValue = point->pathValue;
      updateMinimumPathH(point);
      // point->test = true;
      if (point->pathValue != pathValue) inf = point;
    }
    pInf = getSouthEastFrom(inf);
    
    for (Point* point = pCur->north; point != getNorthFrom(pSup); point = point->north) {
      unsigned int pathValue = point->pathValue;
      updateMinimumPathH(point);
      // point->test = true;
      if (point->pathValue != pathValue) sup = point;
    }
    pSup = getNorthEastFrom(sup);
  }
  return pMin->pathValue;
}
