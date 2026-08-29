#include "duedatepicker.h"

#include <QDateTime>

DueDatePicker::DueDatePicker(QWidget* parent)
    : QFrame(parent), ui(new Ui::DueDatePicker) {
  ui->setupUi(this);
  setWindowFlag(Qt::Popup);

  connect(ui->todayButton, &QPushButton::clicked, this, [this]() {
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
    emit due_date_selected(
        QDateTime(ui->calendarWidget->selectedDate(), ui->timeEdit->time()));
  });

  connect(ui->clearButton, &QPushButton::clicked, this,
          [this]() { emit due_date_clear_button_clicked(); });

  // TODO: completely get rid of done button (automatic saving of what user has
  // selected)
  connect(ui->doneButton, &QPushButton::clicked, this, [this]() {
    const auto date = ui->calendarWidget->selectedDate();
    const auto time = ui->timeEdit->time();
    emit due_date_selected(QDateTime(date, time));
  });
}

void DueDatePicker::set_due_date(const QDateTime& dueDate) {
  const auto effectiveDate =
      dueDate.isValid() ? dueDate : QDateTime::currentDateTime();

  ui->calendarWidget->setSelectedDate(effectiveDate.date());
  ui->timeEdit->setTime(effectiveDate.time());
}

DueDatePicker::~DueDatePicker() { delete ui; }
