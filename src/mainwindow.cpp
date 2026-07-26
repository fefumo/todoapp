#include "mainwindow.h"

#include <QApplication>

#include "editpage.h"
#include "mainpage.h"

void MainWindow::goto_edit_tab() { tabs_->setCurrentWidget(editPage_); }
void MainWindow::goto_main_tab() { tabs_->setCurrentWidget(mainPage_); }

void MainWindow::set_editor_for_new_task(Task& task) {
  editPage_->set_task(task);
  goto_edit_tab();
}

void MainWindow::setup_pages() {
  tabs_ = new QTabWidget(this);

  tabs_->tabBar()->setDocumentMode(true);
  tabs_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  mainPage_ = new MainPage(tabs_);
  editPage_ = new EditPage(tabs_);

  tabs_->addTab(mainPage_, "main");
  tabs_->addTab(editPage_, "edit");

  connect(mainPage_, &MainPage::create_task_requested, this,
          &MainWindow::set_editor_for_new_task);

  connect(editPage_, &EditPage::task_saved, this, [this](Task edited_task) {
    mainPage_->update_task(std::move(edited_task));
    goto_main_tab();
  });

  connect(mainPage_, &MainPage::edit_task_requested, this,
          &MainWindow::set_editor_for_new_task);
}

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  layout_ = new QVBoxLayout(this);
  layout_->setContentsMargins(0, 0, 0, 0);

  setup_pages();
  qDebug() << "pages created";

  QPushButton* exit_button = new QPushButton("Exit", this);
  connect(exit_button, &QPushButton::clicked, &QApplication::exit);
  exit_button->setProperty("role", "primary");

  layout_->addWidget(tabs_);
  layout_->addWidget(exit_button);
  qDebug() << "MainWindow created";
}
