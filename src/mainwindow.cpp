#include "mainwindow.h"

#include <qlogging.h>

#include <QApplication>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QtCore>

#include "appstyle.h"
#include "duedatepicker.h"
#include "oclero/qlementine/Common.hpp"
#include "task.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // TODO: add to ui in the future. dont know where for now.
  {
    QPushButton* exit_button = new QPushButton("Exit", this);
    connect(exit_button, &QPushButton::clicked, &QApplication::exit);
    exit_button->setProperty("role", "primary");
  }

  {
    QSlider* s = new QSlider(Qt::Horizontal, this);
    s->setMinimum(0);
    s->setMaximum(100);
    ui->statusArea->layout()->addWidget(s);

    connect(s, &QSlider::valueChanged, [this, s]() {
      ui->progressBar->upd((qreal)s->value() / s->maximum());
    });
  }

  // TODO: select last edited task as the default one
  if (!taskStore_.tasks().empty()) {
    select_task(taskStore_.tasks().size() - 1);
  }

  setup_navigation();
  connect_edit_buttons();
  setup_labels();
  setup_task_panel();
  populate_tables(taskStore_);

  qDebug() << "MainWindow created";
}

MainWindow::~MainWindow() {
  // Make sure that everything is loaded on disk before closing the app
  taskStore_.save();
}

QTableWidget* MainWindow::table(TableType type) {
  switch (type) {
    case TableType::Overdue:
      return ui->overdueTable;
    case TableType::Completed:
      return ui->completedTable;
    case TableType::Today:
      return ui->todayTable;
    case TableType::Upcoming:
      return ui->upcomingTable;
    default:
      return nullptr;
  }
}

void MainWindow::setup_task_panel() {
  saveTimer_.setSingleShot(true);
  saveTimer_.setInterval(AUTOSAVE_INTERVAL_MS);

  connect(&saveTimer_, &QTimer::timeout, this, [this]() { taskStore_.save(); });

  connect(ui->addTaskButton, &QPushButton::clicked, this,
          [this]() { add_new_task(); });

  connect(ui->taskNameEdit, &QLineEdit::textEdited, this,
          [this](const QString& text) {
            update_selected_task_title(text);
            refresh_task_in_focus();
          });

  connect(ui->dueDateButton, &QToolButton::clicked, this,
          [this]() { toggle_due_date_picker(); });

  connect(ui->additionalInfoTextEdit, &QTextEdit::textChanged, this,
          [this]() { update_selected_task_additional_info(); });

  connect(ui->checkDone, &QCheckBox::checkStateChanged, this,
          &MainWindow::on_task_state_change);
}

void MainWindow::show_task_in_right_panel(const Task& task) {
  ui->taskNameEdit->setText(task.title);
  ui->checkDone->setChecked(task.done);
  ui->additionalInfoTextEdit->setText(task.description);
  ui->createdTimeTitle->setText(AppStyle::format_task_date(task.creationDate));

  refresh_selected_task_due_date(task);
  if (dueDatePicker_) {
    dueDatePicker_->set_due_date(task.dueDate);
  }
}

void MainWindow::update_selected_task_due_date(const QDateTime& dueDate) {
  if (!isTaskSelected()) return;

  const auto index = selectedTaskIndex_.value();
  Task task = taskStore_.tasks().at(index);
  task.dueDate = dueDate;

  taskStore_.update_task(index, std::move(task));
  refresh_selected_task_due_date(taskStore_.tasks().at(index));
  schedule_save();
}

void MainWindow::clear_selected_task_due_date() {
  if (!isTaskSelected()) return;

  const auto index = selectedTaskIndex_.value();
  Task task = taskStore_.tasks().at(index);
  task.dueDate = QDateTime{};

  taskStore_.update_task(index, std::move(task));
  refresh_selected_task_due_date(taskStore_.tasks().at(index));
  schedule_save();
}

void MainWindow::toggle_due_date_picker() {
  if (!isTaskSelected()) return;

  ensure_due_date_picker();

  if (dueDatePicker_->isVisible()) {
    dueDatePicker_->hide();
  } else {
    show_due_date_picker();
  }
}

void MainWindow::show_due_date_picker() {
  if (!isTaskSelected()) return;

  ensure_due_date_picker();

  const auto& task = taskStore_.tasks().at(selectedTaskIndex_.value());
  dueDatePicker_->set_due_date(task.dueDate);
  dueDatePicker_->adjustSize();

  const QPoint position =
      ui->dueDateButton->mapToGlobal(QPoint(0, ui->dueDateButton->height()));

  dueDatePicker_->move(position);
  dueDatePicker_->show();
  dueDatePicker_->raise();
  dueDatePicker_->activateWindow();
}

void MainWindow::ensure_due_date_picker() {
  if (dueDatePicker_) {
    return;
  }

  dueDatePicker_ = new DueDatePicker(this);

  connect(dueDatePicker_, &DueDatePicker::due_date_selected, this,
          [this](const QDateTime& dueDate) {
            update_selected_task_due_date(dueDate);
            refresh_task_in_focus();
          });

  connect(dueDatePicker_, &DueDatePicker::due_date_clear_button_clicked, this,
          [this]() {
            clear_selected_task_due_date();
            refresh_task_in_focus();
            dueDatePicker_->hide();
          });
}

void MainWindow::refresh_selected_task_due_date(const Task& task) {
  if (task.dueDate.isValid()) {
    if (ui->dueTitle->isHidden()) ui->dueTitle->show();
    ui->dueDateButton->setText(AppStyle::format_task_date(task.dueDate));
  } else {
    if (!ui->dueTitle->isHidden()) ui->dueTitle->hide();
    ui->dueDateButton->setText("Click to set due date");
  }
}

void MainWindow::update_selected_task_additional_info() {
  if (!isTaskSelected()) return;

  const auto index = selectedTaskIndex_.value();
  Task task = taskStore_.tasks().at(index);
  task.description = ui->additionalInfoTextEdit->toPlainText();

  taskStore_.update_task(index, std::move(task));
  schedule_save();
}

void MainWindow::add_new_task() {
  Task task = TaskStore::dummy_task();

  const auto newIndex = taskStore_.tasks().size();
  taskStore_.add_task(task);
  select_task(newIndex);
  schedule_save();

  ui->taskNameEdit->setFocus();
}

void MainWindow::select_task(std::size_t index) {
  selectedTaskIndex_ = index;
  Task task = taskStore_.tasks().at(index);
  show_task_in_right_panel(task);
  refresh_task_in_focus();
  refresh_stats();
  qDebug() << "Selected task" << taskStore_.tasks().at(index).title << "("
           << index << ")";
}

void MainWindow::refresh_task_in_focus() {
  if (!selectedTaskIndex_.has_value()) return;

  auto task = taskStore_.tasks().at(selectedTaskIndex_.value());

  ui->curTaskName->setText(task.title);

  if (task.dueDate.isNull()) {
    ui->curDueDate->setText("No due date set");
  } else {
    ui->curDueDate->setText(AppStyle::format_task_date(task.dueDate));
  }

  ui->curSubtaskNum->setText(
      "0");  // Placeholder. Subtasks are not implemented yet
}

void MainWindow::refresh_stats() {
  const size_t done_today = taskStore_.get_done_today();
  const size_t left_today = taskStore_.get_left_today();

  ui->doneNum->setText(QString::number(done_today));
  ui->leftNum->setText(QString::number(left_today));

  qDebug() << "set text to " << done_today << "," << left_today;
}

void MainWindow::on_task_state_change(Qt::CheckState state) {
  if (!isTaskSelected()) return;

  auto t = taskStore_.tasks().at(selectedTaskIndex_.value());

  t.done = state == Qt::CheckState::Checked ? true : false;

  taskStore_.update_task(selectedTaskIndex_.value(), t);
  refresh_stats();
  taskStore_.save();
}

void MainWindow::update_selected_task_title(const QString& title) {
  if (!isTaskSelected()) return;

  Task task = taskStore_.tasks().at(selectedTaskIndex_.value());
  task.title = title;
  taskStore_.update_task(selectedTaskIndex_.value(), std::move(task));
  schedule_save();
}

// Has to be called after every keystroke for debouncing
void MainWindow::schedule_save() { saveTimer_.start(); }

void MainWindow::setup_navigation() {
  connect(ui->tasksButton, &QPushButton::clicked, this, [this]() {
    ui->centralStack->setCurrentIndex(NavigationIndexes::TASKS);
  });

  connect(ui->calendarButton, &QPushButton::clicked, this, [this]() {
    ui->centralStack->setCurrentIndex(NavigationIndexes::CALENDAR);
  });

  connect(ui->historyButton, &QPushButton::clicked, this, [this]() {
    ui->centralStack->setCurrentIndex(NavigationIndexes::HISTORY);
  });

  connect(ui->projectsButton, &QPushButton::clicked, this, [this]() {
    ui->centralStack->setCurrentIndex(NavigationIndexes::PROJECTS);
  });
}

void MainWindow::connect_edit_buttons() {
  connect(ui->deleteTaskButton, &QPushButton::clicked, this, [this]() {});
  connect(ui->editTaskButton, &QPushButton::clicked, this, [this]() {});
}

void MainWindow::populate_tables(const TaskStore& ts) {
  for (auto task : ts.tasks()) {
    QTableWidgetItem* item = new QTableWidgetItem(task.title);

    const QDate dueDate = task.dueDate.date();
    const QDate today = QDate::currentDate();

    if (task.done) {
      add_item(table(TableType::Completed), item);
    } else if (task.dueDate.isNull() || dueDate == today) {
      add_item(table(TableType::Today), item);
    } else if (dueDate > today) {
      add_item(table(TableType::Upcoming), item);
    } else {
      add_item(table(TableType::Overdue), item);
    }
    qDebug() << "Put task" << task.title << "to the table";
  }
}

void MainWindow::add_item(QTableWidget* table, QTableWidgetItem* item) {
  table->setColumnCount(1);
  const int row = table->rowCount();
  table->insertRow(row);
  table->setItem(row, 0, item);
}

void MainWindow::setup_labels() {
  // left
  AppStyle::set_label_role(ui->navigationTitle,
                           oclero::qlementine::TextRole::H2);
  AppStyle::set_label_role(ui->projectsTitle, oclero::qlementine::TextRole::H4);
  // cetner
  // todaypage
  AppStyle::set_label_role(ui->todayPageTitle,
                           oclero::qlementine::TextRole::H2);

  AppStyle::set_label_role(ui->overallStatsTitle,
                           oclero::qlementine::TextRole::H4);
  AppStyle::set_label_role(ui->doneTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->leftTitle, oclero::qlementine::TextRole::H5);

  AppStyle::set_label_role(ui->curFocusTitle, oclero::qlementine::TextRole::H4);
  AppStyle::set_label_role(ui->curTaskTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->curDueTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->curSubtasksLeftTitle,
                           oclero::qlementine::TextRole::H5);

  AppStyle::set_label_role(ui->overdueTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->todayTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->upcomingTitle, oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->completedTitle,
                           oclero::qlementine::TextRole::H5);

  // right
  // AppStyle::set_label_role(ui->taskName, oclero::qlementine::TextRole::H2);

  AppStyle::set_label_role(ui->projectNameTitle,
                           oclero::qlementine::TextRole::Caption);
  AppStyle::set_label_role(ui->createdTitle,
                           oclero::qlementine::TextRole::Caption);
  AppStyle::set_label_role(ui->createdTimeTitle,
                           oclero::qlementine::TextRole::Caption);

  AppStyle::set_label_role(ui->additionalInfoTitle,
                           oclero::qlementine::TextRole::H5);
  AppStyle::set_label_role(ui->subtasksTitle, oclero::qlementine::TextRole::H5);

  AppStyle::set_label_role(ui->timerTitle, oclero::qlementine::TextRole::H2);
}
