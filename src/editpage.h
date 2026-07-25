#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QCheckBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QWidget>

class EditPage : public QWidget {
  Q_OBJECT
 public:
  explicit EditPage(QWidget* parent = nullptr,
                    QStandardItemModel* model = nullptr);
  void editTask(const QModelIndex& index);

 private slots:
  void saveTask();

 signals:

 private:
  QStandardItemModel* model_;
  QLineEdit* titleEdit_;
  QPlainTextEdit* descriptionEdit_;
  QDateTimeEdit* dueDateEdit_;
  QCheckBox* doneCheckbox_;
  QPushButton* saveButton_;

  QPersistentModelIndex currentIndex_;
};

#endif  // EDITPAGE_H
