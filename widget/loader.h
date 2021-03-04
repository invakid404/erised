//
// Created by inva on 3/3/21.
//

#ifndef ERISED_LOADER_H
#define ERISED_LOADER_H

#include <QPluginLoader>
#include <QtWidgets>

#include "interface.h"

namespace erised::widget::loader {
/*
 * `load_widget_from_file` returns an instance of a `QWidget`, implemented by an Erised widget.
 * Return value is `nullptr` if an error occurs or an unknown file is passed as an argument.
 * To be loadable, `file_name` must have a valid suffix in accordance with the platform.
 */
inline auto load_widget_from_file(QString const& file_name) -> QWidget* {
    QPluginLoader loader(file_name);
    auto* instance = loader.instance();
    if (instance) {
        auto interface = qobject_cast<widget_t*>(instance);
        if (interface) {
            return interface->instantiate_widget();
        }

        loader.unload();
    }

    return nullptr;
}

/*
 * `load_all_in_directory` returns a list of `QWidget` instances, implemented by widgets in the given `directory`.
 */
inline auto load_all_in_directory(QDir const& directory) {
    auto res = QList<QWidget*>();

    auto shared_libs = directory.entryInfoList(QDir::Files);
    for (auto& file_info : shared_libs) {
        auto file_path = file_info.absoluteFilePath();

        auto instance = load_widget_from_file(file_path);
        if (!instance) {
            continue;
        }

        res << instance;
    }

    return res;
}
}  // namespace erised::widget::loader

#endif  // ERISED_LOADER_H
