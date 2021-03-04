//
// Created by inva on 3/4/21.
//

#ifndef ERISED_WINDOW_H
#define ERISED_WINDOW_H

#include <QMainWindow>

namespace erised::util {
/*
 * `get_main_window` is a utility function, which returns a pointer to the `QMainWindow` instance.
 * Return value is `nullptr` if such an instance doesn't exist.
 */
inline auto get_main_window() -> QMainWindow* {
    for (auto& top_level_widget : QApplication::topLevelWidgets()) {
        auto curr = qobject_cast<QMainWindow*>(top_level_widget);
        if (curr) {
            return curr;
        }
    }

    return nullptr;
}
}  // namespace erised::util

#endif  // ERISED_WINDOW_H
