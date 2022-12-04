#include <QApplication>
#include "zmeyka.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Zmeyka window;
  window.setWindowTitle("Zmeyka");
  window.show();
  return app.exec();
}
