//
// Created by inva on 3/3/21.
//

#ifndef ERISED_TEST_H
#define ERISED_TEST_H

#include <widget/interface.h>

#include <QDebug>
#include <QObject>
#include <QPushButton>
#include <QtPlugin>

/*
 * This is a minimal example of an Erised widget.
 * The `test` class extends `QObject` and `widget_t`.
 * Refer to the Qt Plugins documentation for details on the specific macros and general structure of plugins.
 */
class test : public QObject, erised::widget::widget_t {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tk.erised.Erised.TestWidget" FILE "test-widget.json")
    Q_INTERFACES(widget_t)
public:
    /*
     * Returns a basic `QPushButton`, which prints a hello message when clicked.
     */
    QWidget* instantiate_widget() override {
        auto* button = new QPushButton("Hello, world!");
        connect(button, &QPushButton::released, [&]() { qDebug() << "Hello from the widget!"; });

        return button;
    }
};

#endif  // ERISED_TEST_H
