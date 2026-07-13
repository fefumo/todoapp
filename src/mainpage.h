#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <qlistview.h>
#include <qstandarditemmodel.h>

#include <QHBoxLayout>
#include <QWidget>

#include "editbuttonswidget.h"

class MainPage : public QWidget {
  Q_OBJECT
 public:
  explicit MainPage(QWidget* parent = nullptr);

 signals:
  void create_task_requested();
  void items_selected();
  void items_not_selected();

 private slots:
  void delete_task();
  void check_selection();

 private:
  QHBoxLayout* layout;
  EditButtonsWidget* editButtons;
  QStandardItemModel* model;
  QListView* listView;
  QItemSelectionModel* selectionModel;
};

#endif  // MAINPAGE_H
