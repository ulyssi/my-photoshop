#include "PictureArea.hh"

#include "PictureViewer.hh"
#include "PictureModifier.hh"



/** Constructeurs et destructeur */
PictureArea::PictureArea(PictureModifier* pictureModifier) :
  m_pictureViewer(new PictureViewer(pictureModifier->getPicture()))
{
  setWidget(m_pictureViewer);
}

PictureArea::~PictureArea() {}
