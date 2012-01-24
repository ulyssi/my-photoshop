#include <QApplication>
#include <QPixmap>
#include "graphics/UserInterface.hh"

int main(int argc, char **argv) {
  QApplication application(argc, argv);
  application.setWindowIcon(QPixmap("logo.png"));
  QClipboard* m_clipboard= QApplication::clipboard();
  UserInterface userInterface(&application ,m_clipboard );
  userInterface.show();
  return application.exec();
}
