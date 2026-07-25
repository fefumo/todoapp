#include "editbuttonswidget.h"

#include <QPushButton>
#include <QVBoxLayout>

// TODO: create a `select from filesystem` button, which handles .md, .txt and
// maybe some other type of text (depending on the editPage's editor settings)

// TODO: if the item(aka task) is not selected in the view, hide delete and edit
// buttons

// TODO: think of the way the tasks have to be stored, whther like actual files,
// or like db items or whatever
EditButtonsWidget::EditButtonsWidget(QWidget* parent) : QWidget{parent} {
  setObjectName("editButtonsWidget");
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QVBoxLayout(this);

  createButton_ = new QPushButton("create", this);
  deleteButton_ = new QPushButton("delete", this);
  editButton_ = new QPushButton("edit", this);

  createButton_->setProperty("role", "primary");
  deleteButton_->setProperty("role", "danger");

  layout->addWidget(createButton_);
  layout->addWidget(editButton_);

  layout->addStretch();

  layout->addWidget(deleteButton_);

  connect(createButton_, &QPushButton::clicked, this,
          &EditButtonsWidget::create_task_requested);

  connect(deleteButton_, &QPushButton::clicked, this,
          &EditButtonsWidget::delete_task_requested);

  hide_function_buttons();
}

void EditButtonsWidget::hide_function_buttons() {
  createButton_->hide();
  deleteButton_->hide();
}

void EditButtonsWidget::show_function_buttons() {
  createButton_->show();
  deleteButton_->show();
}
