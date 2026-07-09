#include "editpage.h"

#include <QPlainTextEdit>

EditPage::EditPage(QWidget *parent) : QWidget{parent} {
  QPlainTextEdit *text_editor = new QPlainTextEdit(this);
}
