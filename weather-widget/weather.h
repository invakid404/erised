//
// Created by inva on 3/3/21.
//

#ifndef ERISED_TEST_H
#define ERISED_TEST_H

#include <util/http.h>
#include <util/positioning.h>
#include <widget/interface.h>

#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QtPlugin>

#include "icons.h"

class weather_widget : public QObject, erised::widget::widget_t {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tk.erised.Erised.WeatherWidget" FILE "weather-widget.json")
    Q_INTERFACES(widget_t)
public:
    /*
     * Figures out which city is the closest to the current location.
     */
    auto fetch_location() {
        auto location = erised::util::positioning_t::the().get_position_data();

        auto location_query = QString("https://www.metaweather.com/api/location/search/?lattlong=%1,%2")
                                  .arg(QString::number(location.latitude), QString::number(location.longitude));

        auto location_response = erised::util::http::get_page(QUrl(location_query));
        auto location_response_json = QJsonDocument::fromJson(location_response).array();

        return location_response_json[0].toObject().value("woeid").toInt();
    }

    /*
     * Updates the weather data from the API.
     */
    auto fetch_weather() {
        auto location_id = this->fetch_location();

        auto weather_query =
            QStringLiteral("https://www.metaweather.com/api/location/%1/").arg(QString::number(location_id));

        auto weather_response = erised::util::http::get_page(QUrl(weather_query));
        auto weather_response_json = QJsonDocument::fromJson(weather_response).object();

        auto consolidated_weather = weather_response_json.value("consolidated_weather").toArray();
        assert(consolidated_weather.size() >= weather_size);

        for (auto i = 0; i < weather_size; ++i) {
            auto current_data = consolidated_weather[i].toObject();

            this->current_weather[i] = weather_data{.state = current_data.value("weather_state_name").toString(),
                                                    .min_temp = current_data.value("min_temp").toDouble(),
                                                    .max_temp = current_data.value("max_temp").toDouble()};
        }
    }

    /*
     * Returns a `QWidget`, which is a container for all of the weather-related content.
     */
    QWidget* instantiate_widget() override {
        this->fetch_weather();

        auto container = new QWidget();
        auto layout = new QHBoxLayout(container);

        for (auto& curr_weather_entry : this->current_weather) {
            auto content = QStringLiteral("%1° / %2°")
                               .arg(QString::number(curr_weather_entry.min_temp, 'f', 0),
                                    QString::number(curr_weather_entry.max_temp, 'f', 0));

            auto weather_entry = new QWidget();
            auto weather_entry_layout = new QVBoxLayout(weather_entry);

            auto icon_filename = icon_map[curr_weather_entry.state];
            auto icon_pixmap = QPixmap(QStringLiteral(":/icons/%1").arg(icon_filename));

            auto icon_label = new QLabel();

            icon_label->setFixedSize(100, 100);
            icon_label->setPixmap(icon_pixmap);
            icon_label->setScaledContents(true);

            weather_entry_layout->addWidget(icon_label);

            auto temp_label = new QLabel(content);

            temp_label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
            temp_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            temp_label->adjustSize();

            weather_entry_layout->addWidget(temp_label);

            layout->addWidget(weather_entry);
        }

        return container;
    }

private:
    const static int weather_size = 5;

    struct weather_data {
        QString state;
        double min_temp;
        double max_temp;
    } current_weather[weather_size];
};

#endif  // ERISED_TEST_H
