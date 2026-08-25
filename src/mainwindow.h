#pragma once

#include <QTimer>
#include <optional>

#include "task.h"
#include "taskstore.h"
#include "ui_mainwindow.h"

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

  TaskStore taskStore_;
  QTimer saveTimer_;  // for debouncing autosave logic
  std::optional<std::size_t> selectedTaskIndex_;
};
