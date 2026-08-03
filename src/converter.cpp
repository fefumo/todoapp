#include "converter.h"
#include <qlogging.h>

QJsonObject task_to_json(const Task& task) {
  return {
      {"title", task.title},
      {"description", task.description},
      {"dueDate", task.dueDate.toString(Qt::ISODate)},
      {"done", task.done},
  };
}

std::optional<Task> task_from_json(const QJsonObject& object) {
  if (!object.contains("title") || !object.contains("description") ||
      !object.contains("done") || !object.contains("dueDate")) {
    // qDebug() << "object: " << object;
    // qDebug() << object.contains("title");
    // qDebug() << object.contains("done");
    // qDebug() << object.contains("description");
    // qDebug() << object.contains("due");
    return std::nullopt;
  }
  Task task;
  task.title = object.value("title").toString();
  task.description = object.value("description").toString();
  task.dueDate =
      QDateTime::fromString(object.value("dueDate").toString(), Qt::ISODate);
  task.done = object.value("done").toBool();
  qDebug() << "created task from json: " << task.title << task.description << task.dueDate << task.done;

  if (!task.dueDate.isValid()) return std::nullopt;
  return task;
}
