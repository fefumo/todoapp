#include "appstyle.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFont>
#include <QHash>
#include <QIODevice>
#include <QString>

#include "oclero/qlementine/style/QlementineStyle.hpp"

namespace {
void replaceThemeTokens(QString& stylesheet) {
  const QHash<QString, QString> tokens{
      {"{{background}}", "#08152c"}, {"{{surface}}", "#0d2041"},
      {"{{border}}", "#294b72"},     {"{{text}}", "#fffefa"},
      {"{{muted}}", "#9fe1f4"},      {"{{accent}}", "#4dc9c0"},
      {"{{danger}}", "#fab1bc"},
  };

  for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
    stylesheet.replace(it.key(), it.value());
  }

  if (stylesheet.contains("{{")) {
    qWarning() << "Unresolved stylesheet token";
  }
}
}  // namespace

namespace AppStyle {

bool apply(QApplication& application) {
  QFont font("JetBrains Mono");
  font.setPointSize(15);
  application.setFont(font);

  QFile file(":/styles/app.qss");

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Could not load stylesheet:" << file.errorString();
    return false;
  }

  QString stylesheet = QString::fromUtf8(file.readAll());

  replaceThemeTokens(stylesheet);
  application.setStyleSheet(stylesheet);

  return true;
}

void set_label_role(QLabel* label, oclero::qlementine::TextRole role) {
  auto* style =
      qobject_cast<oclero::qlementine::QlementineStyle*>(qApp->style());
  if (!style) return;

  label->setFont(style->fontForTextRole(role));
  label->setPalette(style->paletteForTextRole(role));
}

}  // namespace AppStyle
