#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpage.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);

 private slots:

 private:
  enum NavigationIndexes { TASKS = 0, CALENDAR, HISTORY, PROJECTS };
  Ui::MainWindow* ui;

  void set_editor_for_new_task(Task& task);
};

#endif  // !MAINWINDOW_H
