#include "editbuttonswidget.h"

#include <QPushButton>
#include <QVBoxLayout>

EditButtonsWidget::EditButtonsWidget(QWidget *parent) : QWidget{parent} {
  setObjectName("editButtonsWidget");
  setAttribute(Qt::WA_StyledBackground, true);

  auto *layout = new QVBoxLayout(this);

  create_button = new QPushButton("create", this);
  delete_button = new QPushButton("delete", this);
  edit_button = new QPushButton("edit", this);

  create_button->setProperty("role", "primary");
  delete_button->setProperty("role", "danger");

  layout->addWidget(create_button);
  layout->addWidget(edit_button);

  layout->addStretch();

  layout->addWidget(delete_button);
}
