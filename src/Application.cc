#include <QApplication>
#include <QPixmap>
#include "graphics/UserInterface.hh"
#include <sys/resource.h>

int main(int argc, char **argv) {
  setpriority(PRIO_PROCESS, 0,19);
  QApplication application(argc, argv);
  application.setWindowIcon(QPixmap("Icon/Logo.png"));
  QClipboard* m_clipboard= QApplication::clipboard();
  UserInterface userInterface(&application ,m_clipboard );
  userInterface.show();
  return application.exec();
}
