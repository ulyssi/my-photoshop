#include "FileManager.hh"
#include <Qstring>
#include <Qimage>
using namespace std;
namespace FileManager{
  /*todo changer qimage vers format interne */
Public:
  Qimage loadQ(Qstring & path){
    return new QImage(path);
  }
  bool saveQ(Qstring & path, Qimage im){
    return im.save(path);
    
  }
  

}
