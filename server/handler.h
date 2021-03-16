//
// Created by inva on 3/3/21.
//

#ifndef ERISED_HANDLER_H
#define ERISED_HANDLER_H

#include <QString>
#include <QWebSocket>
#include <QtCore/QObject>

namespace erised::server {
/*
 * `handler_t` is a singleton, responsible for handling websocket communication and packets.
 */
class handler_t {
    Q_GADGET
public:
    enum packet_t { SYSTEM_INFO = 1, UPDATE, SIZE };
    Q_ENUM(packet_t);

    enum websocket_state_t { UNAUTHENTICATED = 1, AUTHENTICATED };
    Q_ENUM(websocket_state_t);

    /*
     * `process_new_connection` sends initial info to a new websocket, e.g. the system's resolution, widgets, etc.
     */
    void process_new_connection(QWebSocket*);

    /*
     * `process_packet` parses an incoming packet and invokes the proper packet handler.
     */
    void process_packet(QWebSocket*, QString const&);

    /*
     * `get_instance` returns a global instance of `handler_t`.
     */
    static auto& get_instance() {
        static handler_t instance;
        return instance;
    }

    handler_t(handler_t const&) = delete;
    void operator=(handler_t const&) = delete;

private:
    handler_t();

    /*
     * `build_system_info_packet` gathers information about the system and builds a `SYSTEM_INFO` packet.
     */
    static QString build_system_info_packet();

    /*
     * `build_global_update_packet` builds an `UPDATE` packet, containing information about all loaded widgets.
     */
    static QString build_global_update_packet();

    QMap<QWebSocket*, websocket_state_t> websocket_states;

    typedef std::function<void(QWebSocket*, QJsonValue const&)> packet_handler_t;

    /*
     * `handlers` is an array of handler functions for all recognized packet types.
     */
    std::array<packet_handler_t, SIZE> handlers;
};
}  // namespace erised::server

#endif  // ERISED_HANDLER_H
