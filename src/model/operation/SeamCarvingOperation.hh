#ifndef _SEAM_CARVING_OPERATION_HH_
#define _SEAM_CARVING_OPERATION_HH_

#include "Matrix.hh"

class Picture;


class SeamCarvingOperation {

public:
  
  /** Constructeurs et destructeur */
  SeamCarvingOperation(Picture*);
  ~SeamCarvingOperation();

  /** Accesseurs */
  void setTargetWidth(int);
  void setTargetHeight(int);

  /** Methodes */
  Matrix<unsigned int>* updatePreview();
  Picture* applyOperation();

private:

  /** Structure interne */
  typedef struct Path {
    unsigned int m_pathValueX, m_pathValueY;
    int m_previousX;
    int m_previousY;
  } Path;

  /** Methodes internes */
  Path** createMinimumPath();
  unsigned int** createGradientMatrix();
  void initializeMinimumPathX();
  void initializeMinimumPathY();
  void deleteLine();
  void deleteRow();
  unsigned int inline updateGradient(int, int);

  /** Attributs */
  Picture* m_picture;
  Matrix<unsigned int>* m_pictureData;
  int m_width, m_height;
  unsigned int** m_gradient;
  Path** m_minimumPath;
  int m_targetWidth, m_targetHeight;

};

#endif
