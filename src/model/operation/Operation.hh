#ifndef _OPERATION_HH_
#define _OPERATION_HH_

#include "../Matrix.hh"
#include <vector>

class Picture;
class Tracing;


class Operation {

public:

  /** Constructeurs et destructeur */
  Operation();
  Operation(Picture *);
  Operation(Operation*,Picture *);
  ~Operation();

  /** Accesseurs */
  // Operation* getPreviousOperation();
  // Matrix<unsigned int>* getPictureData();
  // Matrix<unsigned int>* getPreviewData();

  /** Methodes */
  Matrix<unsigned int>* updatePreview();
  Picture* applyOperation();
  virtual Matrix<unsigned int>* updateInternalPreview();
  virtual Picture* applyInternalOperation();

  Picture* applyOn(Picture*);
  Tracing* applyOn(Tracing*);

  Picture* doOperation(Picture*);
  //virtual Tracing* doOperation(Tracing*) = 0;
  //virtual Operation* clone() = 0;

protected:
  Picture* m_picture;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;
private:

  /** Attributs */

  Operation* m_operation;
  std::vector<Tracing*>m_prev;
  std::vector<Tracing*>m_toBdel;

};

#endif
