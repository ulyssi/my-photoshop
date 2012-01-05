#include <QApplication>

#include "graphics/UserInterface.hh"

int main(int argc, char **argv) {
  QApplication application(argc, argv);
  application.setStyle("windows");
  UserInterface userInterface;
  userInterface.show();
  return application.exec();
}
