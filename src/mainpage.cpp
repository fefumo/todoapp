#include "mainpage.h"
#include <qtablewidget.h>

MainPage::MainPage(QWidget *parent) : QWidget{parent} {
  // create a table with one column
  QTableWidget *table = new QTableWidget(this);
  table->setColumnCount(1);
}
