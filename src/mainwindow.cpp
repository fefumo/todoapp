#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QTabBar>
#include <QTabWidget>
#include <QVBoxLayout>

#include "editpage.h"
#include "mainpage.h"

void MainWindow::goto_edit_tab() { tabs_->setCurrentWidget(editPage_); }

void MainWindow::setup_pages() {
  tabs_ = new QTabWidget(this);

  tabs_->tabBar()->setDocumentMode(true);
  tabs_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  mainPage_ = new MainPage(tabs_);
  editPage_ = new EditPage(tabs_, mainPage_->getModel());

  tabs_->addTab(mainPage_, "main");
  tabs_->addTab(editPage_, "edit");
  connect(mainPage_, &MainPage::create_task_requested, this,
          &MainWindow::goto_edit_tab);

  connect(mainPage_, &::MainPage::edit_task_requested, this,
          [this](const QModelIndex& index) {
            editPage_->editTask(index);
            goto_edit_tab();
          });
}

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  layout_ = new QVBoxLayout(this);
  layout_->setContentsMargins(0, 0, 0, 0);

  setup_pages();

  QPushButton* exit_button = new QPushButton("Exit", this);
  connect(exit_button, &QPushButton::clicked, &QApplication::exit);
  exit_button->setProperty("role", "primary");

  layout_->addWidget(tabs_);
  layout_->addWidget(exit_button);
}
