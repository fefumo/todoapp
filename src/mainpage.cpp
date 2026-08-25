#include "mainpage.h"

#include <qlogging.h>

#include <QDir>
#include <QFile>
#include <QHeaderView>
#include <QJsonArray>
#include <QSaveFile>
#include <QStandardPaths>

#include "converter.h"
#include "editbuttonswidget.h"

// DEPRECATED
// void MainPage::delete_task() {
//   const int row = table_->currentRow();
//
//   if (row < 0) {
//     qDebug() << "delete_task(): no task selected";
//     return;
//   }
//
//   const auto index = static_cast<std::size_t>(row);
//
//   if (index > tasks_.size()) {
//     qWarning() << "delete_task(): invalid row:" << row
//                << " tasks_size:" << tasks_.size();
//     return;
//   }
//
//   tasks_.erase(tasks_.begin() + row);
//   table_->removeRow(row);
//
//   qDebug() << "Removed task at row" << row;
// }

// push back to vector, add task to the table
// DEPRECATED
// void MainPage::add_task(Task task) {
//   tasks_.push_back(std::move(task));
//
//   const Task& addedTask = tasks_.back();
//   const int row = table_->rowCount();
//
//   table_->insertRow(row);
//
//   table_->setItem(row, 0, new QTableWidgetItem(addedTask.title));
//
//   table_->setItem(
//       row, 1,
//       new QTableWidgetItem(addedTask.dueDate.toString("yyyy-MM-dd HH:mm")));
//
//   table_->setItem(row, 2,
//                   new QTableWidgetItem(addedTask.done ? "Done" : "Not
//                   Done"));
//
//   // set each item to be uneditable
//   for (auto i = 0; i < table_->columnCount(); i++) {
//     auto item = table_->item(row, i);
//     item->setFlags(item->flags() ^ Qt::ItemFlag::ItemIsEditable);
//   }
//
//   qDebug() << "New template task was added to the table_ at idx(row)" << row;
// }

// update vector, table, and appData
// DEPRECATED
// void MainPage::update_task(Task task) {
//   if (!lastEditIndex_) {
//     qDebug() << "last_edit_index_ is invalid";
//     return;
//   }
//
//   if (lastEditIndex_ > tasks_.size()) {
//     qDebug() << "last_edit_index_ > tasks_.size()";
//     return;
//   }
//
//   Task& cur_task = tasks_[lastEditIndex_.value()];
//   cur_task = std::move(task);
//   qDebug() << "Updated task" << lastEditIndex_.value() << ":" <<
//   cur_task.title; update_table_row(lastEditIndex_.value());
//   // save_tasks(TASKS_FILE_PATH);
//   lastEditIndex_.reset();
// }
//
void MainPage::update_table_row(std::size_t index) {
  if (index >= tasks_.size()) {
    return;
  }
  const Task& task = tasks_[index];
  const int row = static_cast<int>(index);
  table_->item(row, 0)->setText(task.title);
  table_->item(row, 1)->setText(task.dueDate.toString("yyyy-MM-dd HH:mm"));
  table_->item(row, 2)->setText(task.done ? "Done" : "Not Done");
  qDebug() << "Updated table row " << index;
}

void MainPage::on_edit_task_requested() {
  if (table_->selectionModel()->selectedRows().size() != 1) {
    qDebug() << "tried to edit more than one row (task)";
    lastEditIndex_.reset();
    return;
  }

  lastEditIndex_ = table_->currentRow();

  if (!lastEditIndex_) {
    qDebug() << "last_edit_index_ is invalid while editing task";
    lastEditIndex_.reset();
    return;
  }

  const size_t index = static_cast<size_t>(table_->currentRow());
  Task& task = tasks_[index];
  qDebug() << "Editing task" << index << ":" << task.title;
  emit edit_task_requested(task);
}

void MainPage::update_last_edit_index() {}

MainPage::MainPage(QWidget* parent) : QWidget{parent} {
  setObjectName("mainPage");
  setAttribute(Qt::WA_StyledBackground, true);

  layout_ = new QHBoxLayout(this);

  create_table();
  // if (!load_tasks(TASKS_FILE_PATH)) {
  //   qWarning() << "Tasks could not be loaded";
  // }
  create_edit_buttons();
  create_connections();

  qDebug() << "mainpage created";
}

void MainPage::create_table() {
  table_ = new QTableWidget(0, 3, this);
  table_->setObjectName("taskTable");
  // table_->setShowGrid(false);
  // table_->verticalHeader()->setVisible(false);

  table_->setHorizontalHeaderLabels({"Task", "Due date", "Status"});

  table_->setSelectionBehavior(QAbstractItemView::SelectRows);
  table_->setSelectionMode(QAbstractItemView::SingleSelection);

  auto* header = table_->horizontalHeader();
  header->setSectionResizeMode(0, QHeaderView::Stretch);
  header->setSectionResizeMode(1, QHeaderView::ResizeToContents);
  header->setSectionResizeMode(2, QHeaderView::ResizeToContents);

  // table_->setSelectionModel(selectionModel_);
  qDebug() << "table created";
  // table_->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
  layout_->addWidget(table_);
}

void MainPage::create_edit_buttons() {
  editButtons_ = new EditButtonsWidget();
  editButtons_->setMinimumWidth(150);
  editButtons_->setMaximumWidth(190);
  layout_->addWidget(editButtons_, 0);
}

void MainPage::create_connections() {
  connect(
      editButtons_, &EditButtonsWidget::create_task_requested, this, [this]() {
        Task t = {"Title", "Description", QDateTime::currentDateTime(), false};
        lastEditIndex_ = table_->rowCount();
        add_task(t);
        // save_tasks(TASKS_FILE_PATH);
        emit create_task_requested(t);
      });

  connect(editButtons_, &EditButtonsWidget::edit_task_requested, this,
          &MainPage::on_edit_task_requested);

  connect(editButtons_, &EditButtonsWidget::delete_task_requested, this,
          &MainPage::delete_task);

  connect(table_, &QTableWidget::itemClicked, editButtons_,
          &EditButtonsWidget::show_function_buttons);

  connect(table_, &QTableWidget::itemDoubleClicked, this,
          &MainPage::on_edit_task_requested);
}

// DEPRECATED
// bool MainPage::save_tasks(const QString& filepath) const {
//   QJsonArray taskArray;
//
//   for (const Task& task : tasks_) {
//     taskArray.append(task_to_json(task));
//   }
//
//   const QJsonObject rootObject{
//       {"version", 1},
//       {"tasks", taskArray},
//   };
//
//   const QByteArray jsonData =
//       QJsonDocument(rootObject).toJson(QJsonDocument::Indented);
//
//   QSaveFile file(filepath);
//
//   if (!file.open(QIODevice::WriteOnly)) {
//     qWarning() << "Could not open tasks file for writing:"
//                << file.errorString();
//     return false;
//   }
//
//   if (file.write(jsonData) != jsonData.size()) {
//     qWarning() << "Could not write all task data:" << file.errorString();
//
//     file.cancelWriting();
//     return false;
//   }
//
//   if (!file.commit()) {
//     qWarning() << "Could not commit tasks file:" << file.errorString();
//     return false;
//   }
//
//   return true;
// }

// DEPRECATED
// bool MainPage::load_tasks(const QString& filepath) {
//   QFile file(filepath);
//
//   if (!file.exists()) return true;
//   if (!file.open(QIODevice::ReadOnly)) {
//     qWarning() << "Can't open tasks file: " << file.errorString();
//   }
//   const QByteArray data = file.readAll();
//   QJsonParseError parseError;
//   const QJsonDocument document = QJsonDocument::fromJson(data, &parseError);
//
//   if (parseError.error != QJsonParseError::NoError) {
//     qWarning() << "Can't convert from json: " << parseError.errorString();
//     return false;
//   }
//   if (!document.isObject()) {
//     qWarning() << "Tasks file does not contain a json object";
//     return false;
//   }
//
//   const QJsonObject root = document.object();
//   // qDebug() << "JsonRoot: " << root;
//   const QJsonValue tasksValue = root.value("tasks");
//   // qDebug() << "root.value(): " << tasksValue;
//   std::vector<Task> loadedTasks;
//
//   for (const QJsonValue& value : tasksValue.toArray()) {
//     if (!value.isObject()) {
//       qWarning() << "Invalid task entry";
//       return false;
//     }
//     // qDebug() << "jsonValue: " << value;
//
//     std::optional<Task> task = task_from_json(value.toObject());
//
//     if (!task.has_value()) {
//       qWarning() << "Couldn't deserialze task";
//       return false;
//     }
//
//     loadedTasks.push_back(std::move(task.value()));
//   }
//   tasks_.clear();
//   table_->setRowCount(0);
//
//   for (Task& task : loadedTasks) {
//     add_task(task);
//   }
//   return true;
// }
