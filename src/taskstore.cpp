#include "taskstore.h"

#include <qlogging.h>

#include <QJsonArray>
#include <QJsonObject>
#include <QSaveFile>
#include <QStandardPaths>

#include "converter.h"

TaskStore::TaskStore(QObject* parent) : QObject(parent), done_(0), left_(0) {
  load();
  count_done_tasks();
}

const std::vector<Task>& TaskStore::tasks() const { return tasks_; }

void TaskStore::count_done_tasks() {
  if (tasks_.empty()) return;
  for (auto t : tasks_) {
    if (t.done)
      done_++;
    else
      left_++;
  }
}

void TaskStore::syncStats(Task& task, size_t index) {
  bool prevStateOfTask = tasks_.at(index).done;
  bool newStateOfTask = task.done;
  qDebug() << "syncing, prev:" << prevStateOfTask << "new: " << newStateOfTask;
  if (prevStateOfTask != newStateOfTask) {
    // 1 - previously was not done. now done
    if (prevStateOfTask == false) {
      done_++;
      left_--;
      // 2 - task was done but now isnt
    } else {
      done_--;
      left_++;
    }
  }
}

const QString TaskStore::tasks_file_path() const {
  const QString dir =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

  if (!QDir().mkpath(dir)) {
    qWarning() << "Could not create application data directory: " << dir;
  }

  return QDir(dir).filePath("tasks.json");
}

void TaskStore::add_task(Task task) {
  qDebug() << "Adding task " << task.title;
  tasks_.emplace_back(std::move(task));
  emit tasks_changed();
}

void TaskStore::update_task(std::size_t index, Task task) {
  syncStats(task, index);
  tasks_.at(index) = std::move(task);
  qDebug() << "Updated task" << index << ":" << tasks_.at(index).title;
  emit task_changed(index);
}

void TaskStore::delete_task(std::size_t index) {
  qDebug() << "Deleting task: " << index << "(" << tasks_.at(index).title
           << ")";
  tasks_.erase(tasks_.begin() + index);
  emit tasks_changed();
}

bool TaskStore::save() const {
  QJsonArray taskArray;

  for (const Task& task : tasks_) {
    taskArray.append(task_to_json(task));
  }

  const QJsonObject rootObject{
      {"version", 1},
      {"tasks", taskArray},
  };

  const QByteArray jsonData =
      QJsonDocument(rootObject).toJson(QJsonDocument::Indented);

  QSaveFile file(tasks_file_path());

  if (!file.open(QIODevice::WriteOnly)) {
    qWarning() << "Could not open tasks file for writing:"
               << file.errorString();
    return false;
  }

  if (file.write(jsonData) != jsonData.size()) {
    qWarning() << "Could not write all task data:" << file.errorString();

    file.cancelWriting();
    return false;
  }

  if (!file.commit()) {
    qWarning() << "Could not commit tasks file:" << file.errorString();
    return false;
  }

  qDebug() << "Flushed tasks to disk";
  return true;
}

bool TaskStore::load() {
  QFile file(tasks_file_path());

  if (!file.exists()) return true;
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Can't open tasks file: " << file.errorString();
  }
  const QByteArray data = file.readAll();
  QJsonParseError parseError;
  const QJsonDocument document = QJsonDocument::fromJson(data, &parseError);

  if (parseError.error != QJsonParseError::NoError) {
    qWarning() << "Can't convert from json: " << parseError.errorString();
    return false;
  }
  if (!document.isObject()) {
    qWarning() << "Tasks file does not contain a json object";
    return false;
  }

  const QJsonObject root = document.object();
  // qDebug() << "JsonRoot: " << root;
  const QJsonValue tasksValue = root.value("tasks");
  // qDebug() << "root.value(): " << tasksValue;
  std::vector<Task> loadedTasks;

  for (const QJsonValue& value : tasksValue.toArray()) {
    if (!value.isObject()) {
      qWarning() << "Invalid task entry";
      return false;
    }
    // qDebug() << "jsonValue: " << value;

    std::optional<Task> task = task_from_json(value.toObject());

    if (!task.has_value()) {
      qWarning() << "Couldn't deserialze task";
      return false;
    }

    loadedTasks.push_back(std::move(task.value()));
  }

  for (Task& task : loadedTasks) {
    add_task(task);
  }

  qDebug() << "Loaded existing tasks (" << tasks_.size() << ") from disk";
  return true;
}
