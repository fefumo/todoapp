#include "editpage.h"

#include <qabstractitemmodel.h>
#include <qboxlayout.h>
#include <qnamespace.h>

#include "mainpage.h"

void EditPage::editTask(const QModelIndex& index) {
  if (!index.isValid()) return;

  _current_index = index;
  _title_edit->setText(index.data(Qt::DisplayRole).toString());
  _description_edit->setPlainText(index.data(DescriptionRole).toString());
  _due_date_edit->setDate(index.data(DueDateRole).toDate());
  _done_checkbox->setChecked(index.data(Qt::CheckStateRole).toInt() ==
                             Qt::Checked);
}

EditPage::EditPage(QWidget* parent, QStandardItemModel* model)
    : QWidget{parent},
      _model{model},
      _title_edit(new QLineEdit(this)),
      _description_edit(new QPlainTextEdit(this)),
      _due_date_edit(new QDateTimeEdit(this)),
      _done_checkbox(new QCheckBox("Done", this)),
      _save_button(new QPushButton("Save", this)) {
  setObjectName("editPage");
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QVBoxLayout(this);

  layout->addWidget(_title_edit);
  layout->addWidget(_description_edit);
  layout->addWidget(_due_date_edit);
  layout->addWidget(_done_checkbox);
  layout->addWidget(_save_button);

  connect(_save_button, &QPushButton::clicked, this, &EditPage::saveTask);
}

void EditPage::saveTask() {
  if (!_current_index.isValid()) return;
  _model->setData(_current_index, _title_edit->text(), Qt::DisplayRole);
  _model->setData(_current_index, _description_edit->toPlainText(),
                  DescriptionRole);
  _model->setData(_current_index, _due_date_edit->dateTime(), DueDateRole);
  _model->setData(_current_index,
                  _done_checkbox->isChecked() ? Qt::Checked : Qt::Unchecked,
                  Qt::CheckStateRole);
}
