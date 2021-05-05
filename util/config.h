//
// Created by inva on 5/5/21.
//

#ifndef ERISED_CONFIG_H
#define ERISED_CONFIG_H

#include <QSettings>

#include "password.h"

namespace erised::util::config {
const auto default_password = QStringLiteral("admin");

const auto password_key = "authentication/password";

inline auto set_password(QString const& password) {
    auto settings = QSettings();
    qDebug() << settings.fileName();

    auto password_hash = password::generate(password.toLocal8Bit());
    settings.setValue("authentication/password", password_hash);
}

inline auto get_password() {
    auto settings = QSettings();
    auto password_value = settings.value(password_key);

    // If default password hasn't been initialized yet
    if (password_value.isNull()) {
        auto default_password_hash = password::generate(default_password.toLocal8Bit());

        password_value.setValue(default_password_hash);
        settings.setValue(password_key, password_value);
    }

    return password_value.toByteArray();
}
}  // namespace erised::util::config

#endif  // ERISED_CONFIG_H
