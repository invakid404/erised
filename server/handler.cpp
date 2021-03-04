//
// Created by inva on 3/3/21.
//

#include "handler.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>

erised::server::handler_t::handler_t() {
    this->handlers[packet_t::UPDATE] = [&](auto const& payload) { qDebug() << "Received update packet" << payload; };
}

auto erised::server::handler_t::process_packet(const QString& packet_data) -> void {
    auto json_data = QJsonDocument::fromJson(packet_data.toLocal8Bit());
    auto json_obj = json_data.object();

    auto packet_type = json_obj.value("type").toInt();
    auto packet_payload = json_obj.value("payload");

    this->handlers[packet_type](packet_payload);
}
