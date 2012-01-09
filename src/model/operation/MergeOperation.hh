#ifndef _MERGE_OPERATION_HH_
#define _MERGE_OPERATION_HH_

#include <math.h>

#include "Operation.hh"
#include "PixelMod.hh"

class Picture;
class Tracing;

class MergeOperation : public Operation {

public:

  /** Constructeurs et destructeurs */
  MergeOperation();
  ~MergeOperation();

  /** Methodes */
  Picture* doOperation(Picture*);
  Picture* doOperation(Picture**, int);

  Tracing* doOperation(Tracing*);
  // Tracing* doOperation(std::vector<Tracing*>);
  Operation* clone();

private:

  /** Methodes internes */
  Tracing* doOperation(Tracing*, Tracing*);

  // inline  unsigned int combineAlpha(float a1,float a2) {
  //   return ((unsigned int)(floor((a1+a2-(a1*a2))*255.0f+0.5f)))<<24; 
  // }
  
  // inline unsigned int combineRed(unsigned int p1,unsigned int p2, float a2) {
  //   return ((unsigned int)(floor(float(PixelMod::getRed(p1))*(1.0f-a2)+float(PixelMod::getRed(p2))*a2+0.5)))<<16;
  // }

  // inline unsigned int combineBlue(unsigned int p1,unsigned int p2, float a2){
  //   return (unsigned int) floor(float(PixelMod::getBlue(p1))*(1.0f-a2)+float(PixelMod::getBlue(p2))*a2+0.5f);
  // }

  // inline unsigned int combineGreen(unsigned int p1,unsigned int p2, float a2) {
  //   return ((unsigned int)floor(float(PixelMod::getGreen(p1))*(1.0f-a2)+float(PixelMod::getGreen(p2))*a2+0.5f))<<8;
  // }

  // inline float getAlpha(unsigned int p, float a){
  //   return (float)(PixelMod::getAlpha(p))*a/255.0f;
  // }

};

#endif
