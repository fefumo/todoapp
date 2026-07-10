#include "mainwindow.h"
#include "editpage.h"
#include "mainpage.h"

#include <QTabBar>
#include <QTabWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0, 0, 0, 0);

  QTabWidget *tab_widget = new QTabWidget(this);
  main_layout->addWidget(tab_widget);

  // TODO: put the tab setup in a different function
  tab_widget->tabBar()->setDocumentMode(true);
  tab_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  MainPage *main_page = new MainPage(tab_widget);
  tab_widget->addTab(main_page, "main");
  tab_widget->addTab(new EditPage(tab_widget), "edit");
}
