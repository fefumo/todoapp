#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QTabBar>
#include <QTabWidget>
#include <QVBoxLayout>

#include "editpage.h"
#include "mainpage.h"

void MainWindow::goto_edit_tab() { _tabs->setCurrentWidget(_edit_page); }

void MainWindow::setup_pages() {
  _tabs = new QTabWidget(this);

  _tabs->tabBar()->setDocumentMode(true);
  _tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  _main_page = new MainPage(_tabs);
  _edit_page = new EditPage(_tabs, _main_page->getModel());

  _tabs->addTab(_main_page, "main");
  _tabs->addTab(_edit_page, "edit");
  connect(_main_page, &MainPage::create_task_requested, this,
          &MainWindow::goto_edit_tab);

  connect(_main_page, &::MainPage::edit_task_requested, this,
          [this](const QModelIndex& index) {
            _edit_page->editTask(index);
            goto_edit_tab();
          });
}

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  _layout = new QVBoxLayout(this);
  _layout->setContentsMargins(0, 0, 0, 0);

  setup_pages();

  QPushButton* exit_button = new QPushButton("Exit", this);
  connect(exit_button, &QPushButton::clicked, &QApplication::exit);
  exit_button->setProperty("role", "primary");

  _layout->addWidget(_tabs);
  _layout->addWidget(exit_button);
}
