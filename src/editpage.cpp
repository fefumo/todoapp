#include "editpage.h"

#include <qabstractitemmodel.h>
#include <qboxlayout.h>
#include <qnamespace.h>

#include "mainpage.h"

void EditPage::editTask(const QModelIndex& index) {
  if (!index.isValid()) return;

  currentIndex_ = index;
  titleEdit_->setText(index.data(Qt::DisplayRole).toString());
  descriptionEdit_->setPlainText(index.data(DescriptionRole).toString());
  dueDateEdit_->setDate(index.data(DueDateRole).toDate());
  doneCheckbox_->setChecked(index.data(Qt::CheckStateRole).toInt() ==
                             Qt::Checked);
}

EditPage::EditPage(QWidget* parent, QStandardItemModel* model)
    : QWidget{parent},
      model_{model},
      titleEdit_(new QLineEdit(this)),
      descriptionEdit_(new QPlainTextEdit(this)),
      dueDateEdit_(new QDateTimeEdit(this)),
      doneCheckbox_(new QCheckBox("Done", this)),
      saveButton_(new QPushButton("Save", this)) {
  setObjectName("editPage");
  setAttribute(Qt::WA_StyledBackground, true);

  auto* layout = new QVBoxLayout(this);

  layout->addWidget(titleEdit_);
  layout->addWidget(descriptionEdit_);
  layout->addWidget(dueDateEdit_);
  layout->addWidget(doneCheckbox_);
  layout->addWidget(saveButton_);

  connect(saveButton_, &QPushButton::clicked, this, &EditPage::saveTask);
}

void EditPage::saveTask() {
  if (!currentIndex_.isValid()) return;
  model_->setData(currentIndex_, titleEdit_->text(), Qt::DisplayRole);
  model_->setData(currentIndex_, descriptionEdit_->toPlainText(),
                  DescriptionRole);
  model_->setData(currentIndex_, dueDateEdit_->dateTime(), DueDateRole);
  model_->setData(currentIndex_,
                  doneCheckbox_->isChecked() ? Qt::Checked : Qt::Unchecked,
                  Qt::CheckStateRole);
}
