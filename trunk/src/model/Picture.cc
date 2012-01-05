// attention pas de destructeur... à voir


#include "Picture.hh"
#include "util/FileManager.hh"

using namespace std;

Picture::Picture(QString path) :
  m_path(path),
  m_listTracing(3)
{
  m_name = m_path.right(m_path.lastIndexOf("/"));
  m_image = loadQImage(m_path);
  m_width = m_image.width();
  m_height = m_image.height();
  cout << "je ne sias pas encore si je suis une bite\n";
  m_listTracing.push_back(new Tracing(m_image));
  cout << "je suis une bite\n";
}

QString Picture::getPath(){return m_path;}
QString Picture::getName(){return m_name;}
int Picture::getWidth(){return m_width;}
int Picture::getHeight(){return m_height;}
QImage& Picture::getImage(){return m_image;}
vector<Tracing*>& Picture::getListTracing(){return m_listTracing;}

// Charge une image à partir de son path
QImage Picture::loadQImage(QString& path){
  QImage temp = QImage(path);
  if(temp.isNull()) cout << "Error image.format -> QImage" << endl;
  return temp;
}

// sauvegarde une image à partir de son path, return true si succes
bool Picture::saveQImage(QString& path, QImage image){
    return image.save(path);
}
