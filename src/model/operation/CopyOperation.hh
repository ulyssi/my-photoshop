#ifndef _COPY_OPERATION_HH
#define _COPY_OPERATION_HH

#include <QClipboard>
#include <vector>
#include <QImage>
class Picture;
class CopyOperation  {
public:
  CopyOperation();
  
  ~CopyOperation();

  void copyOperation(Picture* ,int ,int , int ,int ,QClipboard *) ;
  

};
#endif
