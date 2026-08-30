#pragma once

#include <QObject>

#include "task.h"

#define TASKS_FILE_PATH tasks_file_path()

class TaskStore : public QObject {
  Q_OBJECT

 public:
  explicit TaskStore(QObject* parent = nullptr);

  static Task dummy_task() {
    return Task{.title = "New task",
                .description = "",
                .dueDate = QDateTime{},
                .creationDate = QDateTime::currentDateTime(),
                .done = false};
  }

  const std::vector<Task>& tasks() const;

  void add_task(Task task);
  void update_task(std::size_t index, Task task);
  void delete_task(std::size_t index);

  bool load();
  bool save() const;

  size_t get_done_today() { return done_; }
  size_t get_left_today() { return left_; }

  const QString tasks_file_path() const;
  void syncStats(Task& task, size_t index);

 private:
  std::vector<Task> tasks_;
  size_t done_;
  size_t left_;

  void count_done_tasks();

 signals:
  void tasks_changed();
  void task_changed(std::size_t index);
};
