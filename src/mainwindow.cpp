#include "mainwindow.h"
#include "editpage.h"
#include "mainpage.h"

#include <QTabBar>
#include <QTabWidget>
#include <QVBoxLayout>

void MainWindow::setup_pages() {
  tabs = new QTabWidget(this);

  tabs->tabBar()->setDocumentMode(true);
  tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  MainPage *main_page = new MainPage(tabs);
  EditPage *edit_page = new EditPage(tabs);
  tabs->addTab(main_page, "main");
  tabs->addTab(edit_page, "edit");
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0, 0, 0, 0);

  setup_pages();
  main_layout->addWidget(tabs);
}
