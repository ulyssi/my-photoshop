#ifndef _CUTOPERATION_HH_
#define _CUTOPERATION_HH_

#include <QClipboard>
#include "Operation.hh"
class Picture;


class CutOperation  {
public:
  CutOperation();
  
  ~CutOperation();

  void doOperation(Picture* ,int ,int , int ,int ,QClipboard *) ;
  

};
#endif
