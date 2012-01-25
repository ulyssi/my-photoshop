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

Matrix<double>* ConvolveOperation::createGaussianBlurKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 1.00 , 2.00 , 1.00 },
                       { 2.00 , 4.00 , 2.00 },
                       { 1.00 , 2.00 , 1.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
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
  return kernel;
}

Matrix<double>* ConvolveOperation::createLeftEdgeStrengtheningKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , 0.00 , 0.00 },
                       { -1.00 , 1.00 , 0.00 },
                       { 0.00 , 0.00 , 0.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return kernel;
}

Matrix<double>* ConvolveOperation::createRepulsingKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -2.00 , -1.00 , 0.00 },
		       { -1.00 , 1.00 , 1.00 },
                       { 0.00 , 1.00 , 2.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return kernel;
}

Matrix<double>* ConvolveOperation::createIncreaseContrastKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , -1.00 , 0.00 },
                       { -1.00 , 5.00 , -1.00 },
                       { 0.00 , -1.00 , 0.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return kernel;
}

Matrix<double>* ConvolveOperation::createSobelXKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 1.00 , 0.00 , -1.00 },
                       { 2.00 , 0.00 , -2.00 },
                       { 1.00 , 0.00 , -1.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return kernel;
}

Matrix<double>* ConvolveOperation::createSobelYKernel(int w, int h) {
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 1.00 , 2.00 , 1.00 },
                       { 0.00 , 0.00 , 0.00 },
                       { -1.00 , -2.00 , -1.00 }};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return kernel;
}
