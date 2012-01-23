#ifndef _SEAM_CARVING_OPERATION_HH_
#define _SEAM_CARVING_OPERATION_HH_

#include "Matrix.hh"

class Picture;


class SeamCarvingOperation {

public:
  
  /** Constructeurs et destructeur */
  SeamCarvingOperation(Picture*);
  ~SeamCarvingOperation();

  /** Predicats */
  bool invariant();

  /** Accesseurs */
  void setTargetWidth(int);
  void setTargetHeight(int);

  /** Methodes */
  Matrix<unsigned int>* updatePreview();
  Picture* applyOperation();

private:

  /** Structure interne */
  // typedef struct Path {
  //   unsigned int m_pathValue;
  //   int m_previous;
  // } Path;

  typedef struct Point {
    unsigned int color;
    unsigned int gradient;
    unsigned int pathValue;
    bool modify, deleted;
    Point *previous, *next;
    Point *north, *south, *east, *west;
  } Point;

  /** Accesseurs internes */
  inline Point* getNorthFrom(Point*);
  inline Point* getSouthFrom(Point*);
  inline Point* getEastFrom(Point*);
  inline Point* getWestFrom(Point*);
  inline Point* getNorthWestFrom(Point*);
  inline Point* getNorthEastFrom(Point*);
  inline Point* getSouthWestFrom(Point*);
  inline Point* getSouthEastFrom(Point*);
  
  /** Methodes internes */
  Matrix<Point*>* createData();
  Point** createIndexH();
  Point** createIndexV();
  void initializeData();
  void initializeGradient2();
  void initializeMinimumPathH2();
  void initializeMinimumPathV2();
  void updateIndexH();
  void updateIndexV();
  inline void updateGradient(Point*);
  inline void updateMinimumPathH(Point*);
  inline void updateMinimumPathV(Point*);
  void deleteRow();
  void newRow();
  void deleteLine();
  void newLine();

  // Path** createMinimumPathH();
  // Path** createMinimumPathV();
  // unsigned int** createGradientMatrix();
  // void initializeGradientMatrix();
  // void initializeMinimumPathH();
  // void initializeMinimumPathV();
  // void deleteLine();
  // void deleteRow();
  // inline void updateMinimumPathH(int, int);
  // inline void updateMinimumPathV(int, int);
  // inline void updateGradient(int, int);

  /** Attributs */
  Picture* m_picture;
  // Matrix<unsigned int>* m_pictureData;
  // unsigned int** m_gradient;
  // Path **m_minimumPathH, **m_minimumPathV;
  // int *m_pathH, *m_pathV;
  int m_widthInit, m_heightInit;
  int m_widthTarget, m_heightTarget;
  int m_widthMax, m_heightMax;
  int m_width, m_height;
  // int m_sobelX[3][3];
  // int m_sobelY[3][3];

  Matrix<Point*>* m_dataInit;
  Point **m_indexH, **m_indexV;
  
};

#endif
