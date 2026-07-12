#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

class MainPage : public QWidget {
  Q_OBJECT
 public:
  explicit MainPage(QWidget* parent = nullptr);

 signals:
  void create_task_requeted();
};

#endif  // MAINPAGE_H
