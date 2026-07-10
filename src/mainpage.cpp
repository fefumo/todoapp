#include "mainpage.h"
#include "editbuttonswidget.h"
#include <qboxlayout.h>
#include <qlistview.h>
#include <qstandarditemmodel.h>
#include <qtablewidget.h>

MainPage::MainPage(QWidget *parent) : QWidget{parent} {

  auto *layout = new QHBoxLayout(this);

  EditButtonsWidget *edit_buttons = new EditButtonsWidget();

  QStandardItemModel *model = new QStandardItemModel(0, 0, this);
  for (int i = 1; i < 5; i++) {
    model->appendRow(new QStandardItem(QString(QString::number(i) + " item")));
  }

  QListView *list_view = new QListView(this);
  list_view->setModel(model);

  layout->addWidget(list_view);
  layout->addWidget(edit_buttons);
}
