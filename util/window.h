//
// Created by inva on 3/4/21.
//

#ifndef ERISED_WINDOW_H
#define ERISED_WINDOW_H

#include <QMainWindow>

namespace erised::util {
inline auto get_main_window() -> QMainWindow* {
    for (auto& top_level_widget : QApplication::topLevelWidgets()) {
        auto curr = qobject_cast<QMainWindow*>(top_level_widget);
        if (curr) {
            return curr;
        }
    }

    return nullptr;
}
}

#endif  // ERISED_WINDOW_H
