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

  typedef struct Point {
    unsigned int color, gradient, pathValue;
    int mask;
    Point *previous, *next;
    Point *north, *south, *east, *west;
    // bool test;
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
  
  void refreshData();
  void refreshGradient();
  void refreshMinimumPathH();
  void refreshMinimumPathV();

  inline void updateGradient(Point*);
  inline void updateMinimumPathH(Point*);
  inline void updateMinimumPathV(Point*);

  unsigned int computeRemoveRow(int);
  unsigned int computeRemoveLine(int);

  /** Attributs */
  Picture* m_picture;
  Matrix<unsigned int>* m_pictureData;
  int m_widthInit, m_heightInit;
  int m_widthTarget, m_heightTarget;
  int m_width, m_height;
  Matrix<Point*>* m_data;
  int m_iteration;
  int* m_pathValue;

};

#endif
