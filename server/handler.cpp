//
// Created by inva on 3/3/21.
//

#include "handler.h"

#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMetaEnum>
#include <QRegularExpression>

erised::server::handler_t::handler_t() {
    this->handlers[packet_t::UPDATE] = [&](auto const& payload) {
        QMainWindow* main_window;
        for (auto& top_level_widget : QApplication::topLevelWidgets()) {
            main_window = qobject_cast<QMainWindow*>(top_level_widget);
            if (main_window) {
                break;
            }
        }

        auto obj = payload.toArray();
        for (auto val : obj) {
            auto curr = val.toObject();
            auto pos = curr.value("pos").toObject();

            auto widget = main_window->findChild<QWidget*>(curr.value("name").toString());

            widget->move(pos.value("x").toInt(), pos.value("y").toInt());
        }
    };
}

void erised::server::handler_t::process_new_connection(QWebSocket* socket) {
    QMainWindow* main_window;
    for (auto& top_level_widget : QApplication::topLevelWidgets()) {
        main_window = qobject_cast<QMainWindow*>(top_level_widget);
        if (main_window) {
            break;
        }
    }

    auto system_info_packet = QJsonObject();
    system_info_packet["type"] = packet_t::SYSTEM_INFO;

    auto system_info_payload = QJsonObject();

    auto main_window_size = main_window->size();

    auto system_info_resolution = QJsonObject();
    system_info_resolution["x"] = main_window_size.width();
    system_info_resolution["y"] = main_window_size.height();

    system_info_payload["resolution"] = system_info_resolution;

    system_info_packet["payload"] = system_info_payload;

    socket->sendTextMessage(QJsonDocument(system_info_packet).toJson());

    auto update_packet = QJsonObject();
    update_packet["type"] = packet_t::UPDATE;

    auto update_payload = QJsonArray();

    for (auto& top_level_widget : QApplication::topLevelWidgets()) {
        if (auto* window = qobject_cast<QMainWindow*>(top_level_widget)) {
            for (auto& widget : window->findChildren<QWidget*>(QRegularExpression("erised_"))) {
                auto widget_info = QJsonObject();
                widget_info["name"] = widget->objectName();

                auto widget_pos = widget->mapToGlobal(widget->rect().topLeft());

                auto widget_pos_info = QJsonObject();
                widget_pos_info["x"] = widget_pos.x();
                widget_pos_info["y"] = widget_pos.y();
                widget_info["pos"] = widget_pos_info;

                update_payload.append(widget_info);
            }
        }
    }

    update_packet["payload"] = update_payload;

    socket->sendTextMessage(QJsonDocument(update_packet).toJson());
}

void erised::server::handler_t::process_packet(const QString& packet_data) {
    auto json_data = QJsonDocument::fromJson(packet_data.toLocal8Bit());
    auto json_obj = json_data.object();

    auto packet_type = json_obj.value("type").toInt();
    auto packet_payload = json_obj.value("payload");

    this->handlers[packet_type](packet_payload);
}
