#ifndef _CONVOLVE_OPERATION_HH_
#define _CONVOLVE_OPERATION_HH_

#include "Operation.hh"
#include "PixelMod.hh"
#include "Matrix.hh"

class Picture;
class Tracing;


class ConvolveOperation {

public:

  /** Type internes */
  enum Operator { TIMES_OPERATOR, MEDIAN_OPERATOR, MAX_OPERATOR, MIN_OPERATOR };
  enum EdgeControl { EXTEND_EDGE, CROP_EDGE, WRAP_EDGE };

  /** Constructeurs et destructeur */
  ConvolveOperation(Picture*, Operation* = 0);
  ~ConvolveOperation();

  /** Accesseurs */
  Picture* getPicture();
  PixelMod::Type getInputType();
  PixelMod::Type getOutputType();

  /** Mutateurs */
  void setKernel(Matrix<double>*);
  void setRGBA(bool, bool, bool, bool);
  void setRed(bool);
  void setGreen(bool);
  void setBlue(bool);
  void setAlpha(bool);
  void setEdgeControl(EdgeControl);
  void setOperator(Operator);

  /** Methodes */
  Matrix<unsigned int>* updatePreview();
  Picture* applyOperation();

  /** Methodes de classe */
  static Matrix<double>* createIdentityKernel(int = 1, int = 1);
  
  static Matrix<double>* createAverageBlurKernel(int = 1, int = 1);
  static Matrix<double>* createGaussianBlurKernel(int = 1, int = 1, double = 1.0);

  static Matrix<double>* createEdgeDetectionKernel(int = 1, int = 1);
  static Matrix<double>* createLeftEdgeStrengtheningKernel(int = 1, int = 1);
  static Matrix<double>* createRepulsingKernel(int = 1, int = 1);
  static Matrix<double>* createIncreaseContrastKernel(int = 1, int = 1);

  static Matrix<double>* createSobelXKernel(int = 1, int = 1);
  static Matrix<double>* createSobelYKernel(int = 1, int = 1);
  static Matrix<double>* stamping(int = 1, int = 1);

private:

  /** Methodes internes */
  inline unsigned int timesOperator(int, int);
  inline unsigned int medianOperator(int, int);
  inline unsigned int maxOperator(int, int);
  inline unsigned int minOperator(int, int);
  inline unsigned int getPixelColor(int, int);
  inline unsigned int getSum(unsigned int);
  
  /** Attributs */
  Operation* m_operation;
  Picture* m_picture;
  Matrix<double>* m_kernel;
  bool m_red, m_green, m_blue, m_alpha;
  double m_convolutionCoef;
  unsigned int m_decalage;
  int m_startI2, m_startJ2, m_endI2, m_endJ2;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;
  EdgeControl m_edgeControl;
  Operator m_operator;

};

#endif
