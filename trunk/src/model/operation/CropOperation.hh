#ifndef _CROPOPERATION_HH_
#define _CROPOPERATION_HH_

#include <QClipboard>
#include "Picture.hh"
class Picture;


class CropOperation  {
public:
  CropOperation();
  
  ~CropOperation();

  void doOperation(Picture* ,int ,int , int ,int) ;
  

};
#endif
