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

 private:
  QList<Task> _notes;
  QVBoxLayout* _layout;
  QTabWidget* _tabs;
  MainPage* _main_page;
  EditPage* _edit_page;

  void setup_pages();
};

#endif  // !MAINWINDOW_H
