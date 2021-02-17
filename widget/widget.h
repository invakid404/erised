//
// Created by inva on 2/17/21.
//

#ifndef ERISED_WIDGET_H
#define ERISED_WIDGET_H

#include <QtWidgets>

namespace erised {
    typedef QWidget *(*create_widget_func)();

    auto instantiate_widget_from_dynamic_lib(const QString &library_name) -> QWidget * {
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
