#include "PictureButton.hh"

#include "PictureModifier.hh"


/*Constructeur et destructeur */
PictureButton::PictureButton(PictureModifier *pictureModifier) :
  PictureViewer(pictureModifier->getPicture()),
  m_pictureModifier(pictureModifier)
{}

PictureButton::~PictureButton() {}

