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
    unsigned int m_pathValueH, m_pathValueV;
    int m_previousH, m_previousV;
  } Path;

  /** Methodes internes */
  Path** createMinimumPath();
  unsigned int** createGradientMatrix();
  void initializeGradientMatrix();
  void initializeMinimumPathH();
  void initializeMinimumPathV();
  void deleteLine();
  void deleteRow();
  inline void updateMinimumPathH(int, int);
  inline void updateMinimumPathV(int, int);
  inline void updateGradient(int, int);

  /** Attributs */
  Picture* m_picture;
  Matrix<unsigned int>* m_pictureData;
  int m_width, m_height;
  unsigned int** m_gradient;
  Path** m_minimumPath;
  int m_targetWidth, m_targetHeight;
  int m_sobelX[3][3];
  int m_sobelY[3][3];

};

#endif
