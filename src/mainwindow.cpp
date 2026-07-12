#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QTabBar>
#include <QTabWidget>
#include <QVBoxLayout>

#include "editpage.h"
#include "mainpage.h"

void MainWindow::goto_edit_tab() { tabs->setCurrentWidget(edit_page); }

void MainWindow::setup_pages() {
  tabs = new QTabWidget(this);

  tabs->tabBar()->setDocumentMode(true);
  tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  main_page = new MainPage(tabs);
  edit_page = new EditPage(tabs);

  tabs->addTab(main_page, "main");
  tabs->addTab(edit_page, "edit");
  connect(main_page, &MainPage::create_task_requeted, this,
          &MainWindow::goto_edit_tab);
}

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  setup_pages();

  QPushButton* exit_button = new QPushButton("Exit", this);
  connect(exit_button, &QPushButton::clicked, &QApplication::exit);

  layout->addWidget(tabs);
  layout->addWidget(exit_button);
}
