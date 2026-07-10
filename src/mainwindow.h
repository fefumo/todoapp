#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "note.h"
#include <QList>
#include <QWidget>
#include <qlist.h>

class MainWindow : public QWidget {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

private:
  QList<Note> notes;
};

#endif // !MAINWINDOW_H
