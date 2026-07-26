#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "editpage.h"
#include "mainpage.h"

class MainWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);

 private slots:
  void goto_edit_tab();
  void goto_main_tab();

 private:
  QVBoxLayout* layout_;
  QTabWidget* tabs_;
  MainPage* mainPage_;
  EditPage* editPage_;

  void setup_pages();
  void set_editor_for_new_task(Task& task);
};

#endif  // !MAINWINDOW_H
