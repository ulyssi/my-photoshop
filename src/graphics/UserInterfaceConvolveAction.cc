#include "UserInterface.hh"

#include "ConvolveOperation.hh"
#include "TabWidget.hh"
#include "TabPanel.hh"
#include "Picture.hh"


/** Slots */
void UserInterface::sobelX() {
  double data[3][3] = {{ 1.00 , 0.00 , -1.00 },
                       { 2.00 , 0.00 , -2.00 },
                       { 1.00 , 0.00 , -1.00 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}

void UserInterface::sobelY() {
  double data[3][3] = {{ 1.00 , 2.00 , 1.00 },
                       { 0.00 , 0.00 , 0.00 },
                       { -1.00 , -2.00 , -1.00 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}

void UserInterface::increaseContrast() {
  double data[3][3] = {{ 0.00 , -1.00 , 0.00 },
                       { -1.00 , 5.00 , -1.00 },
                       { 0.00 , -1.00 , 0.00 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}

void UserInterface::averageBlur() {
  double data[3][3] = {{ 1.00 , 1.00 , 1.00 },
                       { 1.00 , 1.00 , 1.00 },
                       { 1.00 , 1.00 , 1.00 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}

void UserInterface::gaussianBlur() {
  double data[3][3] = {{ 1.00 , 2.00 , 1.00 },
                       { 2.00 , 4.00 , 2.00 },
                       { 1.00 , 2.00 , 1.00 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}

void UserInterface::leftEdgeStrengthening() {
  double data[3][3] = {{ 0.00 , 0.00 , 0.00 },
                       { -1.00 , 1.00 , 0.00 },
                       { 0.00 , 0.00 , 0.00 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}

void UserInterface::edgeDetection() {
  double data[3][3] = {{ 0.00 , 1.00 , 0.00 },
                       { 1.00 , -4.00 , 1.00 },
                       { 0.00 , 1.00 , 0.00 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}

void UserInterface::repulsing() {
  double data[3][3] = {{ -2.00 , -1.00 , 0.00 },
                       { -1.00 , 1.00 , 1.00 },
                       { 0.00 , 1.00 , 2.00 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}

void UserInterface::convolve() {
  double data[3][3] = {{ 0.00 , 1.0 , 0.00 },
                       { 1.0 , -4, 1.0},
                       { 0.00 , 1.0 , 0.0 }};
  
  Matrix<double>* application = new Matrix<double>(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      application->setValue(i, j, (double)data[i][j]);
  
  convolveOperation(application);
  delete application;
}


/** Methodes internes */
void UserInterface::convolveOperation(Matrix<double>* application) {
  TabPanel* panel = m_viewTabWidget->getTabPanel();
  Picture* picture = panel->getSelectedPicture();
  ConvolveOperation* op = new ConvolveOperation(picture);
  op->setKernel(application);
  picture = op->applyOperation();
  delete op;
  picture->refresh();
  panel->refresh();
}

