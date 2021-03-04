//
// Created by inva on 3/3/21.
//

#ifndef ERISED_HANDLER_H
#define ERISED_HANDLER_H

#include <QString>
#include <QWebSocket>
#include <QtCore/QObject>

namespace erised::server {
class handler_t {
    Q_GADGET
public:
    enum packet_t { SYSTEM_INFO = 0, UPDATE, SIZE };
    Q_ENUM(packet_t);

    static void process_new_connection(QWebSocket*);
    void process_packet(QString const&);

    static auto& get_instance() {
        static handler_t instance;
        return instance;
    }

    handler_t(handler_t const&) = delete;
    void operator=(handler_t const&) = delete;

private:
    handler_t();

    static QString build_system_info_packet();
    static QString build_global_update_packet();

    std::array<std::function<void(QJsonValue const&)>, SIZE> handlers;
};
}  // namespace erised::server

#endif  // ERISED_HANDLER_H
