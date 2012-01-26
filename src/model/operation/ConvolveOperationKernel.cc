#include "ConvolveOperation.hh"


/** Identity operator */
Matrix<double>* ConvolveOperation::createIdentityKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(width, height);
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      if (i == width / 2 && j == height / 2) kernel->setValue(i, j, 1.0);
      else kernel->setValue(i, j, 0.0);
  return kernel;
}


/** Blur operator */
Matrix<double>* ConvolveOperation::createAverageBlurKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(width, height);
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      kernel->setValue(i, j, 1.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createGaussianBlurKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  double pi = 4.0 * atan(1.0);
  double sigma = 1.55 - ((double)w+(double)h)/10.0;
  
  Matrix<double>* kernel = new Matrix<double>(width, height); 
  for (double i = 0; i < width; i++)
    for (double j = 0; j < height; j++)
      kernel->setValue(i, j, 100.0*((1.0/(2.0*pi*pow(sigma,2.0)))*exp(-(pow(fabs(i-(double)(width/2)),2.0)+pow(fabs(j-(double)(height/2)),2.0))/(2.0*pow(sigma, 2.0)))));
  return kernel;
}


/** Improve picture */ 
Matrix<double>* ConvolveOperation::createIncreaseContrastKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , -1.00 , 0.00 },
                       { -1.00 , 5.00 , -1.00 },
                       { 0.00 , -1.00 , 0.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createSharpnessKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -1.00 , -1.00 , -1.00 },
                       { -1.00 , 9.00 , -1.00 },
                       { -1.00 , -1.00 , -1.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createUnsharpKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -1.00 , -1.00 , -1.00 },
                       { -1.00 , 17.00 , -1.00 },
                       { -1.00 , -1.00 , -1.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createStampingKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -2.00 , 0.00 , 0.00 },
                       { 0.00 , 1.00 , 0.00 },
                       { 0.00 , 0.00 , 2.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createRepulsingKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -2.00 , -1.00 , 0.00 },
		       { -1.00 , 1.00 , 1.00 },
                       { 0.00 , 1.00 , 2.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}


/** Laplacian operator */
Matrix<double>* ConvolveOperation::createLaplacianKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , -1.00 , 0.00 },
                       { -1.00 , 4.00 , -1.00 },
                       { 0.00 , -1.00 , 0.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createLaplacianBisKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -1.00 , -1.00 , -1.00 },
                       { -1.00 , 8.00 , -1.00 },
                       { -1.00 , -1.00 , -1.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createLaplacianOfGaussianKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(5, 5);
  double data[5][5] = {{  0.00 ,  0.00 , -1.00 ,  0.00 ,  0.00 },
		       {  0.00 , -1.00 , -2.00 , -1.00 ,  0.00 },
		       { -1.00 , -2.00 , 16.00 , -2.00 , -1.00 },
		       {  0.00 , -1.00 , -2.00 , -1.00 ,  0.00 },
		       {  0.00 ,  0.00 , -1.00 ,  0.00 ,  0.00 }};
  for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}


/** Sobel operator */
Matrix<double>* ConvolveOperation::createGradientXKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 1);
  double data[1][3] = {{  1.00 ,  0.00 , -1.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 1; j++) kernel->setValue(i, j, data[j][i]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createGradientYKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(1, 3);
  double data[3][1] = {{  1.00 },
		       {  0.00 }, 
		       { -1.00 }};
  for (int i = 0; i < 1; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[j][i]);
  kernel->resize(width, height, 0.0);
  return kernel;
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


/** Edge strengthening operator */
Matrix<double>* ConvolveOperation::createNorthEdgeStrengtheningKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , -1.00 , 0.00 },
                       { 0.00 ,  1.00 , 0.00 },
                       { 0.00 ,  0.00 , 0.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createSouthEdgeStrengtheningKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 ,  0.00 , 0.00 },
                       { 0.00 ,  1.00 , 0.00 },
                       { 0.00 , -1.00 , 0.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createEastEdgeStrengtheningKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 0.00 , 0.00 ,  0.00 },
                       { 0.00 , 1.00 , -1.00 },
                       { 0.00 , 0.00 ,  0.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createWestEdgeStrengtheningKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{  0.00 , 0.00 , 0.00 },
                       { -1.00 , 1.00 , 0.00 },
                       {  0.00 , 0.00 , 0.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}


/** Line detection operator */
Matrix<double>* ConvolveOperation::createLineDetectionHorizontalKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -1.00 , 2.00 , -1.00 },
                       { -1.00 , 2.00 , -1.00 },
                       { -1.00 , 2.00 , -1.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createLineDetectionVerticalKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -1.00 , -1.00 , -1.00 },
                       { 2.00 , 2.00 , 2.00 },
                       { -1.00 , -1.00 , -1.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createLineDetectionNorthEastKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ -1.00 , -1.00 , 2.00 },
                       { -1.00 , 2.00 , -1.00 },
                       { 2.00 , -1.00 , -1.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

Matrix<double>* ConvolveOperation::createLineDetectionSouthEastKernel(int w, int h) {
  int width = 1 + 2 * w, height = 1 + 2 * h;
  Matrix<double>* kernel = new Matrix<double>(3, 3);
  double data[3][3] = {{ 2.00 , -1.00 , -1.00 },
                       { -1.00 , 2.00 , -1.00 },
                       { -1.00 , -1.00 , 2.00 }};
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) kernel->setValue(i, j, data[i][j]);
  kernel->resize(width, height, 0.0);
  return kernel;
}

