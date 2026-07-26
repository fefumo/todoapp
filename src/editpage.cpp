#include "editpage.h"

EditPage::EditPage(QWidget* parent)
    : QWidget{parent},
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

  connect(saveButton_, &QPushButton::clicked, this,
          [this]() { emit task_saved(task_from_widgets()); });
}

Task EditPage::task_from_widgets() const {
  return Task{titleEdit_->text(), descriptionEdit_->toPlainText(),
              dueDateEdit_->dateTime(), doneCheckbox_->isChecked()};
}

void EditPage::set_task(Task& task) {
  titleEdit_->setText(task.title);
  descriptionEdit_->setPlainText(task.description);
  dueDateEdit_->setDateTime(task.dueDate);
  doneCheckbox_->setCheckState(task.done ? Qt::CheckState::Checked
                                         : Qt::CheckState::Unchecked);
}
