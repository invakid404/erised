//
// Created by inva on 3/3/21.
//

#include "handler.h"

#include <QJsonDocument>
#include <QJsonObject>

auto erised::server::handler_t::process_packet(const QString &packet_data) -> QString {
    auto json_data = QJsonDocument::fromJson(packet_data.toLocal8Bit());
    auto json_obj = json_data.object();

    auto packet_type = json_obj.value("type").toInt();
    auto packet_payload = json_obj.value("payload");

    auto response_obj = QJsonObject();

    response_obj["success"] = true;

    switch (packet_type) {
        case 0:
            response_obj["payload"] = packet_payload.toString().toUpper();
            break;
        case 1:
            response_obj["payload"] = packet_payload.toString().toLower();
            break;
        default:
            response_obj["success"] = false;
            break;
    }

    return QJsonDocument(response_obj).toJson();
}
