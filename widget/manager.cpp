//
// Created by inva on 5/7/21.
//

#include "manager.h"

#include <QPluginLoader>

widget_t *erised::widget::manager_t::load_widget_from_file(QString const &file_name) {
    QPluginLoader loader(file_name);
    auto *instance = loader.instance();
    if (instance) {
        auto interface = qobject_cast<widget_t *>(instance);
        if (interface) {
            auto iid = loader.metaData().value("IID").toString();
            this->loaded_widgets[iid] = interface;

            return interface;
        }

        loader.unload();
    }

    return nullptr;
}
QList<widget_t *> manager_t::load_all_in_directory(const QDir &directory) {
    auto res = QList<widget_t *>();

    auto shared_libs = directory.entryInfoList(QDir::Files);
    for (auto &file_info : shared_libs) {
        auto file_path = file_info.absoluteFilePath();

        auto instance = this->load_widget_from_file(file_path);
        if (!instance) {
            continue;
        }

        res << instance;
    }

    return res;
}
