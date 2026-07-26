#ifndef EDITBUTTONSWIDGET_H
#define EDITBUTTONSWIDGET_H

#include <QModelIndex>
#include <QPushButton>
#include <QWidget>

class EditButtonsWidget : public QWidget {
  Q_OBJECT
 public:
  explicit EditButtonsWidget(QWidget* parent = nullptr);

 private:
  QPushButton* createButton_;
  QPushButton* deleteButton_;
  QPushButton* editButton_;
  bool buttonsShown_;

 signals:
  void create_task_requested();
  void delete_task_requested();
  void edit_task_requested();

 public slots:
  void hide_function_buttons();
  void show_function_buttons();
};

#endif  // EDITBUTTONSWIDGET_H
