#include "editpage.h"

#include <QPlainTextEdit>

EditPage::EditPage(QWidget *parent) : QWidget{parent} {
  setObjectName("editPage");
  setAttribute(Qt::WA_StyledBackground, true);
  QPlainTextEdit *text_editor = new QPlainTextEdit(this);
}
