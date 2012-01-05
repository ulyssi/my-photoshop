#include "FileManager.hh"

#include <QString>
#include <QImage>

/*todo changer qimage vers format interne */
QImage FileManager::loadQ(QString& path){
  return QImage(path);
}
  
bool FileManager::saveQ(QString& path, QImage im){
  //penser à completer le format si necessaire... surcharge
  // de la methode saveQ
  return im.save(path);
}
