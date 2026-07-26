#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QCheckBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

#include "mainpage.h"

class EditPage : public QWidget {
  Q_OBJECT
 public:
  explicit EditPage(QWidget* parent = nullptr);
  void set_task(Task& task);

 signals:
  void task_saved(Task task);

 private:
  QLineEdit* titleEdit_;
  QPlainTextEdit* descriptionEdit_;
  QDateTimeEdit* dueDateEdit_;
  QCheckBox* doneCheckbox_;
  QPushButton* saveButton_;

  Task task_from_widgets() const;
};

#endif  // EDITPAGE_H
