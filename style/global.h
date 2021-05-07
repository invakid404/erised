//
// Created by inva on 5/7/21.
//

#ifndef ERISED_GLOBAL_H
#define ERISED_GLOBAL_H

#include <QApplication>
#include <QDir>
#include <QFontDatabase>

namespace erised::style {
inline auto set_global_style(QApplication& app) {
    QDir fonts_dir(":/fonts");

    auto font_files = fonts_dir.entryInfoList(QDir::Files);
    for (auto& font_file : font_files) {
        QFontDatabase::addApplicationFont(font_file.absoluteFilePath());
    }

    QFont default_font("Poppins", 50);
    QApplication::setFont(default_font);
}
}  // namespace erised::style

#endif  // ERISED_GLOBAL_H
