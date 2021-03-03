//
// Created by inva on 3/3/21.
//

#ifndef ERISED_LOADER_H
#define ERISED_LOADER_H

#include <QPluginLoader>
#include <QtWidgets>

#include "interface.h"

namespace erised::widget::loader {
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
