#include "PictureButton.hh"

/*Constructeur et destructeur */
PictureButton::PictureButton(PictureModifier *pictureModifier) :
  ImageViewer(pictureModifier->getPicture()),
  m_pictureModifier(pictureModifier)
{}

PictureButton::~PictureButton() {}

// PictureButton& PictureButton::operator=(const PictureButton&) {}
