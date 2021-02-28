#include <QApplication>
#include "widget/widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow main_window;
    main_window.showFullScreen();

    auto widgets = erised::widget::load_all_in_directory(QDir("."));
    for (auto& widget : widgets) {
        widget->setParent(&main_window);
        widget->show();
    }

    return QApplication::exec();
}
