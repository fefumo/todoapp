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

  create_button = new QPushButton("create", this);
  delete_button = new QPushButton("delete", this);
  edit_button = new QPushButton("edit", this);

  create_button->setProperty("role", "primary");
  delete_button->setProperty("role", "danger");

  layout->addWidget(create_button);
  layout->addWidget(edit_button);

  layout->addStretch();

  layout->addWidget(delete_button);

  connect(create_button, &QPushButton::clicked, this,
          &EditButtonsWidget::create_task_requested);

  connect(delete_button, &QPushButton::clicked, this,
          &EditButtonsWidget::delete_task_requested);

  hide_function_buttons();
}

void EditButtonsWidget::hide_function_buttons() {
  create_button->hide();
  delete_button->hide();
}

void EditButtonsWidget::show_function_buttons() {
  create_button->show();
  delete_button->show();
}
