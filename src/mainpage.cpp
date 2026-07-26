#include "mainpage.h"

#include <qlogging.h>

#include <QHBoxLayout>
#include <QHeaderView>
#include <QListView>
#include <QStandardItemModel>

#include "editbuttonswidget.h"

void MainPage::delete_task() {
  const int row = table_->currentRow();

  if (row < 0) {
    qDebug() << "delete_task(): no task selected";
    return;
  }

  const auto index = static_cast<std::size_t>(row);

  if (index > tasks_.size()) {
    qWarning() << "delete_task(): invalid row:" << row
               << " tasks_size:" << tasks_.size();
    return;
  }

  tasks_.erase(tasks_.begin() + row);
  table_->removeRow(row);

  qDebug() << "Removed task at row" << row;
}

void MainPage::add_task_to_table(Task task) {
  tasks_.push_back(std::move(task));

  const Task& addedTask = tasks_.back();
  const int row = table_->rowCount();

  table_->insertRow(row);

  table_->setItem(row, 0, new QTableWidgetItem(addedTask.title));

  table_->setItem(
      row, 1,
      new QTableWidgetItem(addedTask.dueDate.toString("yyyy-MM-dd HH:mm")));

  table_->setItem(row, 2,
                  new QTableWidgetItem(addedTask.done ? "Done" : "Not Done"));
  qDebug() << "New template task was added to the table_ at idx(row)" << row;
}

void MainPage::update_task(Task task) {
  if (!lastEditIndex_) {
    qDebug() << "last_edit_index_ is invalid";
    return;
  }

  if (lastEditIndex_ > tasks_.size()) {
    qDebug() << "last_edit_index_ > tasks_.size()";
    return;
  }

  Task& cur_task = tasks_[lastEditIndex_.value()];
  cur_task = std::move(task);
  qDebug() << "Updated task" << lastEditIndex_.value() << ":" << cur_task.title;
  update_table_row(lastEditIndex_.value());
  lastEditIndex_.reset();
}

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

void MainPage::on_edit_task_requeted() {
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
  create_edit_buttons();

  connect(
      editButtons_, &EditButtonsWidget::create_task_requested, this, [this]() {
        Task t = {"Title", "Description", QDateTime::currentDateTime(), false};
        lastEditIndex_ = table_->rowCount();
        add_task_to_table(t);
        emit create_task_requested(t);
      });

  connect(editButtons_, &EditButtonsWidget::edit_task_requested, this,
          &MainPage::on_edit_task_requeted);

  connect(editButtons_, &EditButtonsWidget::delete_task_requested, this,
          &MainPage::delete_task);

  connect(table_, &QTableWidget::itemClicked, editButtons_,
          &EditButtonsWidget::show_function_buttons);
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
