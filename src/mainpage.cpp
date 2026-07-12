#include "mainpage.h"

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qvariant.h>

#include <QHBoxLayout>
#include <QListView>
#include <QStandardItemModel>

#include "editbuttonswidget.h"
// #include "task.h"

void MainPage::delete_task() {
  QItemSelectionModel* selectionModel = list_view->selectionModel();
  if (!selectionModel->hasSelection()) {
    qDebug() << "in MainPage::delete_task(): no items selected";
    return;
  }
  const QModelIndex index = selectionModel->currentIndex();
  QStandardItem* item = model->itemFromIndex(index);
  qDebug() << "removing row " << item->row() << ", index: " << index;
  model->removeRows(item->row(), 1, index.parent());
}

MainPage::MainPage(QWidget* parent) : QWidget{parent} {
  setObjectName("mainPage");
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QHBoxLayout(this);

  EditButtonsWidget* edit_buttons = new EditButtonsWidget();
  edit_buttons->setMinimumWidth(150);
  edit_buttons->setMaximumWidth(190);

  connect(edit_buttons, &EditButtonsWidget::create_task_requested, this,
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

  list_view = new QListView(this);
  list_view->setObjectName("taskList");
  list_view->setModel(model);

  connect(edit_buttons, &EditButtonsWidget::delete_task_requested, this,
          &MainPage::delete_task);

  layout->addWidget(list_view, 1);
  layout->addWidget(edit_buttons, 0);
}
