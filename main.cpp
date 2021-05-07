#include <QApplication>

#include "server/server.h"
#include "style/global.h"
#include "widget/manager.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    erised::style::set_global_style(a);

    // Start web socket server
    auto server = new erised::server::server_t(1337, true, &a);
    QObject::connect(server, &erised::server::server_t::closed, &a, &QApplication::quit);

    // Create main window
    QMainWindow main_window;
    main_window.showMaximized();

    // Load all widgets in current workdir
    auto widgets = erised::widget::manager_t::the().load_all_in_directory(QDir("./clock-widget"));

    return QApplication::exec();
}
