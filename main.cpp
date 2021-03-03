#include <QApplication>

#include "server/server.h"
#include "widget/widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Start web socket server
    auto server = new erised::server(1337, true, &a);
    QObject::connect(server, &erised::server::closed, &a, &QApplication::quit);

    // Create main window
    QMainWindow main_window;
    main_window.showFullScreen();

    // Load all widgets in current workdir
    auto widgets = erised::widget::load_all_in_directory(QDir("."));
    for (auto &widget : widgets) {
        widget->setParent(&main_window);
        widget->show();
    }

    return QApplication::exec();
}
