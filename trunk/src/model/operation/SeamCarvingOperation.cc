#include "SeamCarvingOperation.hh"

#include <cmath>
#include "PixelMod.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
SeamCarvingOperation::SeamCarvingOperation(Picture* picture) :
  m_picture(picture),
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
  initializeData();
  initializeGradient2();
}

SeamCarvingOperation::~SeamCarvingOperation() {}


/** Accesseurs */
void SeamCarvingOperation::setTargetWidth(int widthTarget) { m_widthTarget = widthTarget; }

void SeamCarvingOperation::setTargetHeight(int heightTarget) { m_heightTarget = heightTarget; }


/** Methodes */
Matrix<unsigned int>* SeamCarvingOperation::updatePreview() {

  // std::cout << "Invariant avant = " << invariant() << std::endl;
  
  if (m_width != m_widthTarget) {
    initializeMinimumPathV2();
    while (m_widthTarget < m_width) deleteRow();
    while (m_width < m_widthTarget && m_width < m_widthInit) newRow();
  }
    
  // if (m_height != m_heightTarget) {
  //   initializeMinimumPathH2();
  //   while (m_heightTarget < m_height) deleteLine();
  //   while (m_height < m_heightTarget && m_height < m_heightInit) newLine();
  // }

  // std::cout << "Invariant apres = " << invariant() << std::endl;

  Matrix<unsigned int>* preview = new Matrix<unsigned int>(m_width, m_height);
  // for (int i = 0; i < m_width; i++) {
  //   Point *pi = m_indexH[i];
  //   Point *pj = pi;
  //   for (int j = 0; j < m_height; j++) {
  //     if (pj == NULL) preview->setValue(i, j, PixelMod::createRGB(0, 0, 0));
  //     else {
  // 	if (pj->modify) preview->setValue(i, j, PixelMod::createRGB(255, 0, 0));
  // 	else preview->setValue(i, j, pj->color);
  //       pj = pj->south;
  //     }
  //   }
  // }
  
  for (int j = 0; j < m_height; j++) {
    Point *pj = m_indexV[j];
    Point *pi = pj;
    for (int i = 0; i < m_width; i++) {
      if (pi == NULL) preview->setValue(i, j, PixelMod::createRGB(0, 0, 0));
      else {
  	if (pi->modify) preview->setValue(i, j, PixelMod::createRGB(255, 0, 0));
  	else preview->setValue(i, j, pi->color);
        pi = pi->east;
      }
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
      point->modify = false;
      point->deleted = false;
      point->gradient = 0;
      point->pathValue = 0;
      point->previous = NULL;
      point->next = NULL;
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
    for (int i = 0; i < m_width && point != NULL; i++) {
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
  while (pCur != NULL) {
    if (pMin == NULL || pCur->pathValue < pMin->pathValue) pMin = pCur;
    pCur = pCur->east;
  }
  
  // suppression du chemin
  pCur = pMin;
  for (int j = m_height-1; j >= 0; j--) {
    Point *pPrec = NULL;
    
    if (pCur == NULL) {
      std::cout << "ERROR_3 : ligne " << j << std::endl;
    }
    else {
      if (pCur->deleted) std::cout << "ERROR_4" << std::endl;
      else pCur->deleted = true;
      pPrec = pCur->previous;
    }
    Point *pGauche = getWestFrom(pCur), *pDroit = getEastFrom(pCur);
    Point *pHautGauche = getNorthWestFrom(pCur), *pHaut = getNorthFrom(pCur), *pHautDroit = getNorthEastFrom(pCur);
    
    // Chainage laterale
    if (pDroit != NULL) pDroit->west = pGauche;
    if (pGauche != NULL) pGauche->east = pDroit;
    else {
      if (pCur == NULL) { std::cout << "ERROR_1" << std::endl; }
      else {
	if (m_indexV[j] == pCur) m_indexV[j] = pDroit;
	else std::cout << "ERROR_2" << std::endl;
      }
    }

    // Chainage haut
    if (pPrec == NULL) {
      int k = 0;
      while (k < m_width && m_indexH[k] != pCur) k++;
      while (k < m_width-1) { m_indexH[k] = m_indexH[k+1]; k++; }
      m_indexH[k] = pCur;
    }
    else if (pPrec == pHautGauche) {
      pGauche->north = pHaut;
      pHaut->south = pGauche;
    }
    else if (pPrec == pHautDroit) {
      pDroit->north = pHaut;
      pHaut->south = pDroit;
    }
    
    // tracer du chemin en rouge
    // pCur->modify = true;
    pCur = pPrec;
  }

  // mise a jour des gradients locaux
  pCur = pMin;
  for (int j = 0; j < m_height && pCur != NULL; j++) {
    Point *pGauche = getWestFrom(pCur), *pDroit = getEastFrom(pCur);
    
    if (pGauche != NULL) {
      // pGauche->modify = true;
      updateGradient(pGauche);
      if (pGauche->west != NULL) {
	// pGauche->west->modify = true;
	updateGradient(pGauche->west);
      }
    }
    
    if (pDroit != NULL) {
      // pDroit->modify = true;
      updateGradient(pDroit);
      if (pDroit->east != NULL) {
	// pDroit->east->modify = true;
	updateGradient(pDroit->east);
      }
    }
    
    pCur = pCur->previous;
  }

  // mise a jour des chemins
  Point *pInf = m_indexH[m_width-1]->west, *pSup = m_indexH[m_width-1]->east;
  for (int j = 0; j < m_height; j++) {
    Point* inf = pInf, *sup = pSup;
    if (inf == NULL) inf = m_indexV[j];
    if (sup != NULL) sup = sup->east;
    for (Point* pCur = inf; pCur != sup; pCur = pCur->east) {
      updateMinimumPathV(pCur);
      // pCur->modify = true;
    }
    pInf = getSouthWestFrom(pInf);
    pSup = getSouthEastFrom(pSup);
  }

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

bool SeamCarvingOperation::invariant() {
  if (m_indexH[0] != m_indexV[0]) {
    std::cout << "m_indexH / m_indexV error" << std::endl;
    return false;
  }
  Point* ref = m_indexH[0];
  for (int i = 0; i < m_width; i++) {
    if (m_indexH[i] != ref) {
      std::cout << "m_indexH error" << std::endl;
      return false;
    }
    ref = ref->east;
  }
  ref = m_indexV[0];
  for (int j = 0; j < m_height; j++) {
    if (m_indexV[j] != ref) {
      std::cout << "m_indexV error" << std::endl;
      return false;
    }
    ref = ref->south;
  }
  Point *pi = m_indexH[0];
  for (int i = 0; i < m_width; i++) {
    if (pi == NULL) {
      std::cout << "pi NULL error" << std::endl;
      return false;
    }
    else {
      Point *pj = pi;
      for (int j = 0; j < m_height; j++) {
        if (pj == NULL) {
          std::cout << "pj NULL error" << std::endl;
          return false;
        }
        else {
          pj = pj->south;
        }
      }
      pi = pi->east;
    }
  }
  
  return true;
}
