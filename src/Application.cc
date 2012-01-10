#include <QApplication>

#include "graphics/UserInterface.hh"

int main(int argc, char **argv) {
  QApplication application(argc, argv);
  //[WINDOWS] application->setStyle("windows");
  UserInterface userInterface(&application);
  userInterface.show();
  return application.exec();
}
