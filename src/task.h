#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QObject>
#include <QString>

class Task : public QObject {
  Q_OBJECT
 public:
  explicit Task(QObject* parent = nullptr);

  QString name;
  QDateTime date;

 signals:
};

#endif  // TASK_H
