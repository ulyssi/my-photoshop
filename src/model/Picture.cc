#include <Qstring>
#include "Picture.hh"
#include "FileManager.hh"
using namespace std;

  Picture::Picture(Qstring &path){
    m_path = path;
    image=FileManager::loadQ(m_path);
  }

Qimage& Picture::getImage(){
  return image;
}

