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
     * The `library_name` must either represent a file in LD_PRELOAD_PATH (on Unix) or be an absolute path.
     */
    auto instantiate_from_dynamic_lib(const QString &library_name) -> QWidget * {
        QLibrary library(library_name);
        if (!library.load()) {
            qDebug() << library.errorString();
            return nullptr;
        }

        auto create_func = (create_widget_func) library.resolve("create_widget");
        if (!create_func) {
            qDebug() << "Failed to resolve create_widget function";
            return nullptr;
        }

        return create_func();
    }
}

#endif //ERISED_WIDGET_H
