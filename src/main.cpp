#include <QApplication>

#include "appstyle.h"
#include "mainwindow.h"
#include "oclero/qlementine/style/QlementineStyle.hpp"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  // AppStyle::apply(a);
  auto style = new oclero::qlementine::QlementineStyle(&a);
  QApplication::setStyle(style);

  MainWindow w;
  w.show();
  return QApplication::exec();
}
