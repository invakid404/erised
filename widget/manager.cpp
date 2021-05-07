//
// Created by inva on 5/7/21.
//

#include "manager.h"

#include <QPluginLoader>

QWidget *erised::widget::manager_t::load_widget_from_file(QString const &file_name) {
    QPluginLoader loader(file_name);
    auto *instance = loader.instance();
    if (instance) {
        auto interface = qobject_cast<widget_t *>(instance);
        if (interface) {
            auto iid = loader.metaData().value("IID").toString();
            this->loaded_widgets[iid] = interface;

            auto widget_instance = interface->instantiate_widget();

            widget_instance->setParent(erised::util::get_main_window());
            widget_instance->show();

            return widget_instance;
        }

        loader.unload();
    }

    return nullptr;
}
QList<QWidget *> manager_t::load_all_in_directory(const QDir &directory) {
    auto res = QList<QWidget *>();

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
