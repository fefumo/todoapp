#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "note.h"
#include <QList>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

private:
  QList<Note> notes;
  QVBoxLayout *layout;
  QTabWidget *tabs;
  void setup_pages();
};

#endif // !MAINWINDOW_H
