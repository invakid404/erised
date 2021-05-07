//
// Created by inva on 5/7/21.
//

#ifndef ERISED_GLOBAL_H
#define ERISED_GLOBAL_H

#include <QApplication>
#include <QFontDatabase>

namespace erised::style {
inline auto set_global_style(QApplication& app) {
    QFontDatabase::addApplicationFont(":/fonts/Poppins-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Poppins-SemiBold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Poppins-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Poppins-ExtraBold.ttf");

    QFont default_font("Poppins");
    QApplication::setFont(default_font);
}
}  // namespace erised::style

#endif  // ERISED_GLOBAL_H
