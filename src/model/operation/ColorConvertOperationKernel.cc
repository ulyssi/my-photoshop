#include "ColorConvertOperation.hh"


Matrix<double>* ColorConvertOperation::createIdentityKernel() {
  Matrix<double>* kernel = new Matrix<double>(4, 4);
  double data[4][4] = {
    { 1.00 , 0.00 , 0.00 , 0.00 },
    { 0.00 , 1.00 , 0.00 , 0.00 },
    { 0.00 , 0.00 , 1.00 , 0.00 },
    { 0.00 , 0.00 , 0.00 , 1.00 }
  };
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return kernel;
}

Matrix<double>* ColorConvertOperation::createGreyScaleKernel() { 
  Matrix<double>* kernel = new Matrix<double>(4, 4);
  double data[4][4] = {
    { 0.30 , 0.59 , 0.11 , 0.00 },
    { 0.30 , 0.59 , 0.11 , 0.00 },
    { 0.30 , 0.59 , 0.11 , 0.00 },
    { 0.00 , 0.00 , 0.00 , 1.00 }
  };
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      kernel->setValue(i, j, (double)data[i][j]);
  return kernel;
}

Matrix<double>* ColorConvertOperation::createSepiaKernel() { return createIdentityKernel(); }
