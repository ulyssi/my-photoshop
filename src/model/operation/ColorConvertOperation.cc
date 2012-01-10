#include "ColorConvertOperation.hh"

#include "Tracing.hh"
#include "PixelMod.hh"

#include <iostream>

/** Constructeurs et destructeur */
ColorConvertOperation::ColorConvertOperation(Matrix<double>* application) :
  m_application(application)
{}

ColorConvertOperation::~ColorConvertOperation() {}


/** Methodes */
Tracing* ColorConvertOperation::doOperation(Tracing* tracing) {
    // std::cout << "Width = " << tracing->getWidth() << std::endl;
    // unsigned int** data = tracing->getData();
    // for (int i = 0; i < tracing->getWidth(); i++)
    //   for (int j = 0; j < tracing->getHeight(); j++) {
    // 	int red = PixelMod::getRed(data[i][j]);
    // 	int green = PixelMod::getGreen(data[i][j]);
    // 	int blue = PixelMod::getBlue(data[i][j]);
    // 	data[i][j] = PixelMod::createRGB(PixelMod::threshold(m_application->getValue(0, 0) * red +
    // 							     m_application->getValue(0, 1) * green + 
    // 							     m_application->getValue(0, 2) * blue),
    // 					 PixelMod::threshold(m_application->getValue(1, 0) * red + 
    // 							     m_application->getValue(1, 1) * green + 
    // 							     m_application->getValue(1, 2) * blue),
    // 					 PixelMod::threshold(m_application->getValue(2, 0) * red + 
    // 							     m_application->getValue(2, 1) * green + 
    // 							     m_application->getValue(2, 2) * blue),
    // 					 PixelMod::getAlpha(data[i][j]));
    //   }
  //  }
  return tracing;
}

Operation* ColorConvertOperation::clone() { return NULL; }



