//
// Created by inva on 3/3/21.
//

#ifndef ERISED_HANDLER_H
#define ERISED_HANDLER_H

#include <QString>
#include <QtCore/QObject>

namespace erised::server {
class handler_t {
    Q_GADGET
public:
    enum packet_t { UPDATE = 0, SIZE };
    Q_ENUM(packet_t);

    auto process_packet(QString const&) -> void;

    static auto& get_instance() {
        static handler_t instance;
        return instance;
    }

    handler_t(handler_t const&) = delete;
    void operator=(handler_t const&) = delete;

private:
    handler_t();

    std::array<std::function<void(QJsonValue const&)>, SIZE> handlers;
};
}  // namespace erised::server

#endif  // ERISED_HANDLER_H
