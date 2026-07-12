#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <qlistview.h>
#include <qstandarditemmodel.h>

#include <QWidget>

class MainPage : public QWidget {
  Q_OBJECT
 public:
  explicit MainPage(QWidget* parent = nullptr);

 signals:
  void create_task_requested();

 private slots:
  void delete_task();

 private:
  QStandardItemModel* model;
  QListView* list_view;
};

#endif  // MAINPAGE_H
