#pragma once

#include <QDateTime>
#include <QDir>
#include <QString>

struct Task {
  QString title;
  QString description;
  QDateTime dueDate;
  QDateTime creationDate;
  bool done;
};
