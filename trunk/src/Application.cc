#include <QApplication>

#include "graphics/UserInterface.hh"

int main(int argc, char **argv) {
  QApplication application(argc, argv);
  UserInterface userInterface;
  userInterface.show();
  return application.exec();
}
