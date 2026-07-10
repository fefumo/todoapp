#include "editbuttonswidget.h"

#include <QPushButton>
#include <qboxlayout.h>

EditButtonsWidget::EditButtonsWidget(QWidget *parent) : QWidget{parent} {
  auto *layout = new QVBoxLayout(this);

  create_button = new QPushButton("create", this);
  delete_button = new QPushButton("delete", this);
  edit_button = new QPushButton("edit", this);

  layout->addWidget(create_button);
  layout->addWidget(delete_button);
  layout->addWidget(edit_button);
}
