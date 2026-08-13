#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // TODO: add to ui in the future. dont know where for now.
  QPushButton* exit_button = new QPushButton("Exit", this);
  connect(exit_button, &QPushButton::clicked, &QApplication::exit);
  exit_button->setProperty("role", "primary");

  qDebug() << "MainWindow created";
}
