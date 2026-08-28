#pragma once

#include <QDateTime>
#include <QFrame>
#include <QHideEvent>

#include "ui_duedatepicker.h"

namespace Ui {
class DueDatePicker;
}

class DueDatePicker : public QFrame {
  Q_OBJECT

 public:
  explicit DueDatePicker(QWidget* parent = nullptr);
  ~DueDatePicker();

  void set_due_date(const QDateTime& dueDate);

 signals:
  void due_date_selected(const QDateTime& dueDate);
  void due_date_clear_button_clicked();

 private:
  Ui::DueDatePicker* ui;
};
