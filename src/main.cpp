#include <QApplication>

#include "appstyle.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  AppStyle::apply(a);

  MainWindow w;
  w.show();
  return QApplication::exec();
}
