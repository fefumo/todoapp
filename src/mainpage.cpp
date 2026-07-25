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
  if (!_selectionModel->hasSelection()) {
    qDebug() << "in MainPage::delete_task(): no items selected";
    return;
  }
  const QModelIndex index = _selectionModel->currentIndex();
  QStandardItem* item = _model->itemFromIndex(index);
  qDebug() << "removing row " << item->row() << ", index: " << index;
  _model->removeRows(item->row(), 1, index.parent());
}

void MainPage::check_selection() {
  // TODO:: that slot is being called too much. i have to think about a better
  // solution (somehow get a signal for when there is no selection)
  if (_selectionModel->hasSelection()) {
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

  _layout = new QHBoxLayout(this);

  _editButtons = new EditButtonsWidget();
  _editButtons->setMinimumWidth(150);
  _editButtons->setMaximumWidth(190);

  connect(_editButtons, &EditButtonsWidget::create_task_requested, this,
          &MainPage::create_task_requested);

  _model = new QStandardItemModel(0, 1, this);

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
  _model->appendRow(item);

  _listView = new QListView(this);
  _listView->setObjectName("taskList");
  _listView->setModel(_model);

  _selectionModel = _listView->selectionModel();

  connect(_editButtons, &EditButtonsWidget::delete_task_requested, this,
          &MainPage::delete_task);

  _layout->addWidget(_listView, 1);
  _layout->addWidget(_editButtons, 0);

  connect(_selectionModel, &QItemSelectionModel::selectionChanged, this,
          &MainPage::check_selection);

  connect(this, &MainPage::items_selected, _editButtons,
          &EditButtonsWidget::show_function_buttons);

  connect(this, &MainPage::items_not_selected, _editButtons,
          &EditButtonsWidget::hide_function_buttons);

  connect(_listView, &QListView::doubleClicked, this,
          &MainPage::edit_task_requested);
}
