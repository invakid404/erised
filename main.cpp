#include <QApplication>
#include "widget/widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow main_window;
    main_window.showFullScreen();

    auto w = erised::widget::instantiate_from_dynamic_lib("./libqt_shared_lib_test");
    w->setParent(&main_window);
    w->show();

    return QApplication::exec();
}
