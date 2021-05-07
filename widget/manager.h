//
// Created by inva on 5/7/21.
//

#ifndef ERISED_MANAGER_H
#define ERISED_MANAGER_H

#include <QPluginLoader>
#include <QtWidgets>

#include "interface.h"

namespace erised::widget {
class manager_t {
public:
    widget_t *load_widget_from_file(QString const &);

    QList<widget_t *> load_all_in_directory(QDir const &);

    static manager_t &the() {
        static manager_t instance;

        return instance;
    }

    manager_t(manager_t const &) = delete;

    void operator=(manager_t const &) = delete;

private:
    manager_t() = default;

    QMap<QString, widget_t *> loaded_widgets;
};
}  // namespace erised::widget

#endif  // ERISED_MANAGER_H
