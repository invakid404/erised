#include <QApplication>
#include "widget/widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto w = erised::instantiate_widget_from_dynamic_lib("libqt_shared_lib_test");
    w->show();

    return QApplication::exec();
}
