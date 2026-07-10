#ifndef NOTE_H
#define NOTE_H

#include <QDateTime>
#include <QObject>
#include <QString>

class Note : public QObject {
  Q_OBJECT
public:
  explicit Note(QObject *parent = nullptr);

  QString name;
  QDateTime date;

signals:
};

#endif // NOTE_H
