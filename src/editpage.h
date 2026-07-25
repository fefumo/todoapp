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
  QStandardItemModel* _model;
  QLineEdit* _title_edit;
  QPlainTextEdit* _description_edit;
  QDateTimeEdit* _due_date_edit;
  QCheckBox* _done_checkbox;
  QPushButton* _save_button;

  QPersistentModelIndex _current_index;
};

#endif  // EDITPAGE_H
