#pragma once

#include <QDateTime>
#include <QTimer>
#include <optional>

#include "task.h"
#include "taskstore.h"
#include "ui_mainwindow.h"
#define AUTOSAVE_INTERVAL_MS 500

class DueDatePicker;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  enum class TableType {
    Overdue,
    Today,
    Upcoming,
    Completed,
  };

  QTableWidget* table(TableType type);

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
  bool isTaskSelected() {
    return selectedTaskIndex_.has_value() ? true : false;
  }

  void schedule_save();

  // TodayPage
  void populate_tables(const TaskStore& ts);
  void add_item(QTableWidget* table, QTableWidgetItem* item);
  void refresh_tables();                                // TODO:
  void swap_items(QTableWidget* t1, QTableWidget* t2);  // TODO:

  void refresh_stats();
  void refresh_task_in_focus();
  void on_task_state_change(Qt::CheckState state);

  // RIGHT PANEL
  void show_task_in_right_panel(const Task& task);
  // Task title
  void update_selected_task_title(const QString& title);

  // Due date
  void refresh_selected_task_due_date(const Task& task);
  void update_selected_task_due_date(const QDateTime& dueDate);
  void clear_selected_task_due_date();
  // Due date picker
  void toggle_due_date_picker();
  void show_due_date_picker();
  void ensure_due_date_picker();

  // Additional info
  void update_selected_task_additional_info();

  TaskStore taskStore_;
  QTimer saveTimer_;  // for debouncing autosave logic
  std::optional<std::size_t> selectedTaskIndex_;
  DueDatePicker* dueDatePicker_ = nullptr;  // lazy load
};
