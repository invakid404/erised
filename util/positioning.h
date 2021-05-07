//
// Created by inva on 5/7/21.
//

#ifndef ERISED_POSITIONING_H
#define ERISED_POSITIONING_H

#include <QJsonDocument>
#include <QJsonObject>

#include "http.h"

namespace erised::util {
class positioning_t {
    Q_GADGET
public:
    auto get_position_data() { return this->curr_position; }

    static positioning_t& the() {
        static positioning_t instance;
        return instance;
    }

    positioning_t(positioning_t const&) = delete;
    void operator=(positioning_t const&) = delete;

private:
    positioning_t() { this->get_location_by_ip(); }

    void get_location_by_ip() {
        auto api_url = QUrl("https://ipapi.co/json");
        auto api_response_data = http::get_page(api_url);

        auto api_response_json = QJsonDocument::fromJson(api_response_data).object();

        this->curr_position = {.country = api_response_json.value("country").toString(),
                               .city = api_response_json.value("city").toString(),
                               .latitude = api_response_json.value("latitude").toDouble(),
                               .longitude = api_response_json.value("longitude").toDouble()};
    }

    struct position_data {
        QString country;
        QString city;
        double latitude;
        double longitude;
    } curr_position;
};
}  // namespace erised::util

#endif  // ERISED_POSITIONING_H
