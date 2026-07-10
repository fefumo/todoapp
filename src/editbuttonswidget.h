#ifndef EDITBUTTONSWIDGET_H
#define EDITBUTTONSWIDGET_H

#include <QPushButton>
#include <QWidget>

class EditButtonsWidget : public QWidget {
  Q_OBJECT
public:
  explicit EditButtonsWidget(QWidget *parent = nullptr);

public slots:
  // void clicked(const QModelIndex &index);

private:
  QPushButton *create_button;
  QPushButton *delete_button;
  QPushButton *edit_button;

signals:
};

#endif // EDITBUTTONSWIDGET_H
