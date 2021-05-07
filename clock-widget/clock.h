//
// Created by inva on 3/3/21.
//

#ifndef ERISED_CLOCK_H
#define ERISED_CLOCK_H

#include <widget/interface.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QTimer>
#include <QtPlugin>

class clock_widget : public QObject, erised::widget::widget_t {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tk.erised.Erised.ClockWidget" FILE "clock-widget.json")
    Q_INTERFACES(widget_t)
public:
    /*
     * Returns a `QLabel` with the text set to the current time.
     * A `QTimer` is responsible for updating the text every second.
     */
    QWidget* instantiate_widget() override {
        auto set_time = [&]() {
            auto curr_time = QTime::currentTime().toString();
            this->clock_label->setText(curr_time);
            this->clock_label->adjustSize();
        };

        this->clock_label = new QLabel("");

        this->clock_label->setAlignment(Qt::AlignTop);
        this->clock_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

        auto clock_font = this->clock_label->font();
        clock_font.setPointSize(50);
        this->clock_label->setFont(clock_font);

        set_time();

        this->clock_timer = new QTimer(this);
        this->clock_timer->setInterval(1000);

        connect(this->clock_timer, &QTimer::timeout, set_time);

        this->clock_timer->start();

        return clock_label;
    }

private:
    QLabel* clock_label;
    QTimer* clock_timer;
};

#endif  // ERISED_CLOCK_H
