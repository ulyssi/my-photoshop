#include <QApplication>

#include "graphics/UserInterface.hh"

int main(int argc, char **argv) {
  QApplication qtApp(argc, argv);
  UserInterface userInterface;
  userInterface.show();
  return qtApp.exec();
}
