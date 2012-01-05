#ifndef _PICTURE_AREA_HH_
#define _PICTURE_AREA_HH_

#include <QScrollArea>

class PictureViewer;
class PictureModifier;


class PictureArea : public QScrollArea { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  PictureArea(PictureModifier*);
  ~PictureArea();

private:

  /** Attributs */
  PictureViewer* m_pictureViewer;

};

#endif
