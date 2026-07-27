#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDateTime>
#include <QHBoxLayout>
#include <QListView>
#include <QTableWidget>
#include <QWidget>

#include "editbuttonswidget.h"

struct Task {
  QString title;
  QString description;
  QDateTime dueDate;
  bool done;
};

class MainPage : public QWidget {
  Q_OBJECT
 public:
  explicit MainPage(QWidget* parent = nullptr);
  void update_task(Task task);
  void update_table_row(std::size_t index);

 signals:
  void create_task_requested(Task& task);
  void edit_task_requested(Task& task);
  void items_selected();
  void items_not_selected();

 private slots:
  void delete_task();
  void add_task_to_table(Task task);
  void on_edit_task_requested();

 private:
  std::vector<Task> tasks_;
  std::optional<std::size_t> lastEditIndex_;

  QHBoxLayout* layout_;
  QTableWidget* table_;
  EditButtonsWidget* editButtons_;

  void create_table();
  void create_edit_buttons();
  void update_last_edit_index();
  void create_connections();
};

#endif  // MAINPAGE_H
