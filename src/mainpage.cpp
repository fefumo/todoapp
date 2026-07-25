#include "mainpage.h"

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qvariant.h>
#include <qdatetime.h>
#include <qnamespace.h>

#include <QHBoxLayout>
#include <QListView>
#include <QStandardItemModel>

#include "editbuttonswidget.h"
// #include "task.h"

void MainPage::delete_task() {
  // TODO: delete multiple selected items
  if (!selectionModel_->hasSelection()) {
    qDebug() << "in MainPage::delete_task(): no items selected";
    return;
  }
  const QModelIndex index = selectionModel_->currentIndex();
  QStandardItem* item = model_->itemFromIndex(index);
  qDebug() << "removing row " << item->row() << ", index: " << index;
  model_->removeRows(item->row(), 1, index.parent());
}

void MainPage::check_selection() {
  // TODO:: that slot is being called too much. i have to think about a better
  // solution (somehow get a signal for when there is no selection)
  if (selectionModel_->hasSelection()) {
    qDebug() << "emitting items_selected";
    emit items_selected();
  } else {
    qDebug() << "emitting items_not_selected";
    emit items_not_selected();
  }
}

MainPage::MainPage(QWidget* parent) : QWidget{parent} {
  setObjectName("mainPage");
  setAttribute(Qt::WA_StyledBackground, true);

  layout_ = new QHBoxLayout(this);

  editButtons_ = new EditButtonsWidget();
  editButtons_->setMinimumWidth(150);
  editButtons_->setMaximumWidth(190);

  connect(editButtons_, &EditButtonsWidget::create_task_requested, this,
          &MainPage::create_task_requested);

  model_ = new QStandardItemModel(0, 1, this);

  // for (int i = 1; i < 5; i++) {
  //   // TODO: create Item from Task object?
  //   // Task* task = new Task();
  //   // smth like QStandardItem* item = new QStandardItem(task);?
  //   // or maybe subclass from standarditem idk...
  //
  //   _model->appendRow(new QStandardItem(QString(QString::number(i) +
  //   "item")));
  // }

  Task* task = new Task({"someTitle", "something here",
                         QDateTime(QDate(2026, 07, 20), QTime(14, 58, 34))});
  auto* item = new QStandardItem();
  item->setData(task->title, Qt::DisplayRole);
  item->setData(task->description, DescriptionRole);
  item->setData(task->dueDate, DueDateRole);
  item->setCheckable(true);
  item->setCheckState(task->done ? Qt::Checked : Qt::Unchecked);
  model_->appendRow(item);

  listView_ = new QListView(this);
  listView_->setObjectName("taskList");
  listView_->setModel(model_);

  selectionModel_ = listView_->selectionModel();

  connect(editButtons_, &EditButtonsWidget::delete_task_requested, this,
          &MainPage::delete_task);

  layout_->addWidget(listView_, 1);
  layout_->addWidget(editButtons_, 0);

  connect(selectionModel_, &QItemSelectionModel::selectionChanged, this,
          &MainPage::check_selection);

  connect(this, &MainPage::items_selected, editButtons_,
          &EditButtonsWidget::show_function_buttons);

  connect(this, &MainPage::items_not_selected, editButtons_,
          &EditButtonsWidget::hide_function_buttons);

  connect(listView_, &QListView::doubleClicked, this,
          &MainPage::edit_task_requested);
}
