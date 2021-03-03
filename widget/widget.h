//
// Created by inva on 2/17/21.
//

#ifndef ERISED_WIDGET_H
#define ERISED_WIDGET_H

#include <QtWidgets>

namespace erised::widget {
typedef QWidget *(*create_widget_func)();

/*
 * Returns an instance of a widget, implemented in a dynamic/shared library.
 * Return value is nullptr if an error occurs.
 * The `library_name` mustn't contain an extension.
 * The `library_name` must either represent a filename in LD_PRELOAD_PATH (on Unix) or be a path.
 */
auto instantiate_from_dynamic_lib(QString const &library_name) -> QWidget * {
    QLibrary library(library_name);
    if (!library.load()) {
        qDebug() << library.errorString();
        return nullptr;
    }

    auto create_func = (create_widget_func)library.resolve("create_widget");
    if (!create_func) {
        qDebug() << "Failed to resolve create_widget function";
        return nullptr;
    }

    return create_func();
}

/*
 * Returns a list of widgets, implemented in dynamic/shared libraries in the specified `directory`.
 */
auto load_all_in_directory(QDir const &directory) {
    auto res = QList<QWidget *>();

    auto shared_libs = directory.entryInfoList(QDir::Files);
    for (auto &file_info : shared_libs) {
        auto file_path = file_info.filePath();

        auto instance = instantiate_from_dynamic_lib(file_path);
        if (!instance) {
            continue;
        }

        res << instance;
    }

    return res;
}
}  // namespace erised::widget

#endif  // ERISED_WIDGET_H
