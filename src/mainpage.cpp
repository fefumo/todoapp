#include "mainpage.h"

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qvariant.h>

#include <QHBoxLayout>
#include <QListView>
#include <QStandardItemModel>

#include "editbuttonswidget.h"
// #include "task.h"

void MainPage::delete_task() {
  // TODO: delete multiple selected items
  if (!selectionModel->hasSelection()) {
    qDebug() << "in MainPage::delete_task(): no items selected";
    return;
  }
  const QModelIndex index = selectionModel->currentIndex();
  QStandardItem* item = model->itemFromIndex(index);
  qDebug() << "removing row " << item->row() << ", index: " << index;
  model->removeRows(item->row(), 1, index.parent());
}

void MainPage::check_selection() {
  // TODO:: that slot is being called too much. i have to think about a better
  // solution (somehow get a signal for when there is no selection)
  if (selectionModel->hasSelection()) {
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

  layout = new QHBoxLayout(this);

  editButtons = new EditButtonsWidget();
  editButtons->setMinimumWidth(150);
  editButtons->setMaximumWidth(190);

  connect(editButtons, &EditButtonsWidget::create_task_requested, this,
          &MainPage::create_task_requested);

  model = new QStandardItemModel(0, 1, this);

  for (int i = 1; i < 5; i++) {
    // TODO: create Item from Task object?
    // Task* task = new Task();
    // smth like QStandardItem* item = new QStandardItem(task);?
    // or maybe subclass from standarditem idk...
    model->appendRow(new QStandardItem(QString(QString::number(i) + " item")));
    // model->appendRow();
  }

  listView = new QListView(this);
  listView->setObjectName("taskList");
  listView->setModel(model);

  selectionModel = listView->selectionModel();

  connect(editButtons, &EditButtonsWidget::delete_task_requested, this,
          &MainPage::delete_task);

  layout->addWidget(listView, 1);
  layout->addWidget(editButtons, 0);

  connect(selectionModel, &QItemSelectionModel::selectionChanged, this,
          &MainPage::check_selection);

  connect(this, &MainPage::items_selected, editButtons,
          &EditButtonsWidget::show_function_buttons);

  connect(this, &MainPage::items_not_selected, editButtons,
          &EditButtonsWidget::hide_function_buttons);
}
