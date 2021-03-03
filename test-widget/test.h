//
// Created by inva on 3/3/21.
//

#ifndef ERISED_TEST_H
#define ERISED_TEST_H

#include <widget/interface.h>

#include <QObject>
#include <QPushButton>
#include <QtPlugin>

class test : public QObject, erised::widget::widget_t {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tk.erised.Erised.TestWidget" FILE "test-widget.json")
    Q_INTERFACES(widget_t)
public:
    QWidget* instantiate_widget() override {
        auto* button = new QPushButton("Hello, world!");
        connect(button, &QPushButton::released, [&]() { qDebug() << "Hello from the widget!"; });

        return button;
    }
};

#endif  // ERISED_TEST_H
