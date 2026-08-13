#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // TODO: add to ui in the future. dont know where for now.
  QPushButton* exit_button = new QPushButton("Exit", this);
  connect(exit_button, &QPushButton::clicked, &QApplication::exit);
  exit_button->setProperty("role", "primary");

  QSlider* s = new QSlider(Qt::Horizontal, this);
  s->setMinimum(0);
  s->setMaximum(100);
  ui->statusArea->layout()->addWidget(s);
  connect(s, &QSlider::valueChanged, [this, s]() {
    ui->progressBar->upd((qreal)s->value() / s->maximum());
  });

  qDebug() << "MainWindow created";
}
