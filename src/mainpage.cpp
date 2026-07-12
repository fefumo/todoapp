#include "mainpage.h"

#include <QHBoxLayout>
#include <QListView>
#include <QStandardItemModel>

#include "editbuttonswidget.h"

MainPage::MainPage(QWidget* parent) : QWidget{parent} {
  setObjectName("mainPage");
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QHBoxLayout(this);

  EditButtonsWidget* edit_buttons = new EditButtonsWidget();
  edit_buttons->setMinimumWidth(150);
  edit_buttons->setMaximumWidth(190);

  connect(edit_buttons, &EditButtonsWidget::create_task_requested, this,
          &MainPage::create_task_requeted);

  QStandardItemModel* model = new QStandardItemModel(0, 1, this);
  for (int i = 1; i < 5; i++) {
    model->appendRow(new QStandardItem(QString(QString::number(i) + " item")));
  }

  QListView* list_view = new QListView(this);
  list_view->setObjectName("taskList");
  list_view->setModel(model);

  layout->addWidget(list_view, 1);
  layout->addWidget(edit_buttons, 0);
}
