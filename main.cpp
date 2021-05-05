#include <QApplication>

#include "server/server.h"
#include "util/config.h"
#include "widget/loader.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QApplication::setOrganizationName("erised");

    // Start web socket server
    auto server = new erised::server::server_t(1337, true, &a);
    QObject::connect(server, &erised::server::server_t::closed, &a, &QApplication::quit);

    // Create main window
    QMainWindow main_window;
    main_window.showMaximized();

    // Load all widgets in current workdir
    auto widgets = erised::widget::loader::load_all_in_directory(QDir("./test-widget"));
    for (auto &widget : widgets) {
        widget->setParent(&main_window);
        widget->setObjectName(QString("erised_") + widget->metaObject()->className());
        widget->move(150, 200);

        widget->show();
    }

    return QApplication::exec();
}
