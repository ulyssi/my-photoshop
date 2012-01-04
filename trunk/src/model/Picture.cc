#include "Picture.hh"

#include <QString>

#include "FileManager.hh"

using namespace std;

Picture::Picture(QString &path) :
  m_path(path)
{
  image = FileManager::loadQ(m_path);
}

QImage& Picture::getImage() {
  return image;
}

