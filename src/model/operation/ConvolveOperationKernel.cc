#include "ConvolveOperation.hh"


Matrix<double>* ConvolveOperation::createIdentityKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(width, height);
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      if (i == width / 2 && j == height / 2) kernel->setValue(i, j, 1.0);
      else kernel->setValue(i, j, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createAverageBlurKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(width, height);
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      kernel->setValue(i, j, 1.0);
  return kernel;
}
// généraliser
Matrix<double>* ConvolveOperation::createGaussianBlurKernel(int w, int h, double sigma) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  double pi = 4.0 * atan(1.0);
  Matrix<double>* kernel = new Matrix<double>(width, height);
  for (double i = 0; i < width; i++)
    for (double j = 0; j < height; j++)
      kernel->setValue(i, j, 100.0*((1.0/(2.0*pi*pow(sigma,2.0)))*exp(-(pow(i,2.0)+pow(j,2.0))/(2.0*pow(sigma, 2.0)))));
  return kernel;
}

Matrix<double>* ConvolveOperation::createEdgeDetectionKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , 1.00 , 0.00 },
                       { 1.00 , -4.00 , 1.00 },
                       { 0.00 , 1.00 , 0.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return Matrix<double>::centrer(w, h, kernel);
}

Matrix<double>* ConvolveOperation::createLeftEdgeStrengtheningKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , 0.00 , 0.00 },
                       { -1.00 , 1.00 , 0.00 },
                       { 0.00 , 0.00 , 0.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return Matrix<double>::centrer(w, h, kernel);
}

Matrix<double>* ConvolveOperation::createRepulsingKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -2.00 , -1.00 , 0.00 },
		       { -1.00 , 1.00 , 1.00 },
                       { 0.00 , 1.00 , 2.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return Matrix<double>::centrer(w, h, kernel);
}

Matrix<double>* ConvolveOperation::createIncreaseContrastKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , -1.00 , 0.00 },
                       { -1.00 , 5.00 , -1.00 },
                       { 0.00 , -1.00 , 0.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return Matrix<double>::centrer(w, h, kernel);
}


Matrix<double>* ConvolveOperation::createSobelXKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(width, height);
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      kernel->setValue(i, j, 0);
  
  double coef = 1.0;
  for(int i = 0; i < height; i++){
    kernel->setValue(0, i, coef);
    kernel->setValue(width-1, i, -coef);
    if(i <= height/2){
      coef = 2 * coef;
    } else {
      coef = coef/2;
    }
  }
  return kernel;
}

Matrix<double>* ConvolveOperation::createSobelYKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(width, height);
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      kernel->setValue(i, j, 0);
  
  double coef = 1.0;
  for(int i = 0; i < width; i++){
    kernel->setValue(i, 0, coef);
    kernel->setValue(i, height-1, -coef);
    if(i <= width/2){
      coef = 2 * coef;
    } else {
      coef = coef/2;
    }
  }
  return kernel;
}


/////////////////////////////////:new convolve operations
