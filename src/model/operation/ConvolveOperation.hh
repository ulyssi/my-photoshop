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

private:

  /** Methodes internes */
  inline unsigned int getPixelColor(int, int);

  /** Attributs */
  Operation* m_operation;
  Picture* m_picture;
  Matrix<double>* m_kernel;
  bool m_red, m_green, m_blue, m_alpha;
  Matrix<unsigned int>* m_pictureData;
  Matrix<unsigned int>* m_previewData;
  EdgeControl m_edgeControl;

};

#endif
