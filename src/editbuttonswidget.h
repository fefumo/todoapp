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
  QPushButton* create_button;
  QPushButton* delete_button;
  QPushButton* edit_button;

 signals:
  void create_task_requested();
};

#endif  // EDITBUTTONSWIDGET_H
