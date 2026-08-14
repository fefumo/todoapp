#include "mainwindow.h"

#include <qapplication.h>

#include "appstyle.h"
#include "oclero/qlementine/Common.hpp"

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

  connect(ui->tasksButton, &QPushButton::clicked, this, [this]() {
    ui->centralStack->setCurrentIndex(NavigationIndexes::TASKS);
  });

  connect(ui->calendarButton, &QPushButton::clicked, this, [this]() {
    ui->centralStack->setCurrentIndex(NavigationIndexes::CALENDAR);
  });

  connect(ui->historyButton, &QPushButton::clicked, this, [this]() {
    ui->centralStack->setCurrentIndex(NavigationIndexes::HISTORY);
  });

  connect(ui->projectsButton, &QPushButton::clicked, this, [this]() {
    ui->centralStack->setCurrentIndex(NavigationIndexes::PROJECTS);
  });

  // --- LABELS ---
  // left
  AppStyle::set_label_role(ui->navigationTitle,
                           oclero::qlementine::TextRole::H2);
  AppStyle::set_label_role(ui->projectsTitle, oclero::qlementine::TextRole::H4);
  // cetner
  // todaypage
  AppStyle::set_label_role(ui->todayPageTitle,
                           oclero::qlementine::TextRole::H2);

  AppStyle::set_label_role(ui->statsForTodayTitle,
                           oclero::qlementine::TextRole::H4);
  AppStyle::set_label_role(ui->doneTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->leftTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->statsOverdueTitle,
                           oclero::qlementine::TextRole::H5);

  AppStyle::set_label_role(ui->curFocusTitle, oclero::qlementine::TextRole::H4);
  AppStyle::set_label_role(ui->curTaskTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->curDueTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->curSubtasksLeftTitle,
                           oclero::qlementine::TextRole::H5);

  AppStyle::set_label_role(ui->overdueTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->todayTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->upcomingTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->completedTitle,
                           oclero::qlementine::TextRole::H5);

  // right
  AppStyle::set_label_role(ui->taskName, oclero::qlementine::TextRole::H2);

  AppStyle::set_label_role(ui->projectNameTitle,
                           oclero::qlementine::TextRole::Caption);
  AppStyle::set_label_role(ui->createdTitle,
                           oclero::qlementine::TextRole::Caption);
  AppStyle::set_label_role(ui->createdTimeTitle,
                           oclero::qlementine::TextRole::Caption);

  AppStyle::set_label_role(ui->additionalInfoTitle,
                           oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->subtasksTitle, oclero::qlementine::TextRole::H5);

  AppStyle::set_label_role(ui->timerTitle, oclero::qlementine::TextRole::H2);

  qDebug() << "MainWindow created";
}
