//
// Created by inva on 3/3/21.
//

#ifndef ERISED_TEST_H
#define ERISED_TEST_H

#include <widget/interface.h>

#include <QLabel>
#include <QObject>
#include <QTime>
#include <QTimer>
#include <QtPlugin>
#include <chrono>

class hello_widget : public QObject, erised::widget::widget_t {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tk.erised.Erised.HelloWidget" FILE "hello-widget.json")
    Q_INTERFACES(widget_t)
public:
    void update_label() {
        auto curr_greeting = QString();
        auto curr_time = QTime::currentTime();

        if (curr_time >= QTime(4, 0, 0) && curr_time < QTime(12, 0, 0)) {
            curr_greeting = "Good morning!";
        } else if (curr_time >= QTime(12, 0, 0) && curr_time < QTime(17, 0, 0)) {
            curr_greeting = "Good afternoon!";
        } else if (curr_time >= QTime(17, 0, 0) && curr_time < QTime(23, 0, 0)) {
            curr_greeting = "Good evening!";
        } else {
            curr_greeting = "What are you doing up at this hour?";
        }

        this->hello_label->setText(curr_greeting);
        this->hello_label->adjustSize();
    }

    /*
     * Returns a `QLabel`, which displays a message according to what time it is.
     */
    QWidget* instantiate_widget() override {
        this->hello_label = new QLabel();

        this->hello_label->setAlignment(Qt::AlignTop);
        this->hello_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

        this->update_label();

        auto timer = new QTimer();
        timer->setInterval(std::chrono::minutes(1));

        connect(timer, &QTimer::timeout, this, &hello_widget::update_label);

        return this->hello_label;
    }

private:
    QLabel* hello_label;
};

#endif  // ERISED_TEST_H
