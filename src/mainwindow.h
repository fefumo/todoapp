#pragma once

#include <QDateTime>
#include <QTimer>
#include <optional>

#include "task.h"
#include "taskstore.h"
#include "ui_mainwindow.h"

class DueDatePicker;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  enum NavigationIndexes { TASKS = 0, CALENDAR, HISTORY, PROJECTS };
  Ui::MainWindow* ui;

  void set_editor_for_new_task(Task& task);

  void setup_navigation();
  void setup_labels();
  void connect_edit_buttons();

  void setup_task_panel();
  void add_new_task();
  void select_task(std::size_t index);
  void show_task_in_right_panel(const Task& task);
  void update_selected_task_title(const QString& title);
  void schedule_save();

  void update_selected_task_due_date(const QDateTime& dueDate);
  void clear_selected_task_due_date();
  void refresh_due_date_field(const Task& task);
  void toggle_due_date_picker();
  void show_due_date_picker();
  void ensure_due_date_picker();
  bool isTaskSelected() {
    return selectedTaskIndex_.has_value() ? true : false;
  }

  TaskStore taskStore_;
  QTimer saveTimer_;  // for debouncing autosave logic
  std::optional<std::size_t> selectedTaskIndex_;
  DueDatePicker* dueDatePicker_ = nullptr;
};
