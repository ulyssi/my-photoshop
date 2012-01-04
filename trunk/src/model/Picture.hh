#ifndef _PICTURE_HH_
#define _PICTURE_HH_

#include <QString>
#include <QImage>

using namespace std;

class Picture {
  
public:

  /** Constructeurs et destructeur */
  Picture(QString&);
  ~Picture();

  /** Accesseurs */
  QImage& getImage();

private:

  /** Attributs */
  QString& m_path;
  QImage image;
};

#endif
