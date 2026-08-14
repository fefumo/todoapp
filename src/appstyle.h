#pragma once

#include <qapplication.h>
#include <qlabel.h>

#include "oclero/qlementine/Common.hpp"

class QApplication;

namespace AppStyle {

bool apply(QApplication& application);
void set_label_role(QLabel* label, oclero::qlementine::TextRole role);

}  // namespace AppStyle
