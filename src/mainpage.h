#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDateTime>
#include <QHBoxLayout>
#include <QListView>
#include <QStandardItemModel>
#include <QWidget>

#include "editbuttonswidget.h"

class MainPage : public QWidget {
  Q_OBJECT
 public:
  explicit MainPage(QWidget* parent = nullptr);
  QStandardItemModel* getModel() { return _model; }

 signals:
  void create_task_requested();
  void items_selected();
  void items_not_selected();
  void edit_task_requested(const QModelIndex& index);

 private slots:
  void delete_task();
  void check_selection();

 private:
  QHBoxLayout* _layout;
  EditButtonsWidget* _editButtons;
  QStandardItemModel* _model;
  QListView* _listView;
  QItemSelectionModel* _selectionModel;
};

struct Task {
  QString title;
  QString description;
  QDateTime dueDate;
  bool done = false;
};

enum TaskRole : int {
  DescriptionRole = Qt::UserRole + 1,
  DueDateRole,
};

#endif  // MAINPAGE_H
