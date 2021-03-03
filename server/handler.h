//
// Created by inva on 3/3/21.
//

#ifndef ERISED_HANDLER_H
#define ERISED_HANDLER_H

#include <QString>

namespace erised::server {
class handler_t {
public:
    auto process_packet(QString const&) -> QString;

    static auto& get_instance() {
        static handler_t instance;
        return instance;
    }

    handler_t(handler_t const&) = delete;
    void operator=(handler_t const&) = delete;

private:
    handler_t() = default;
};
}  // namespace erised::server

#endif  // ERISED_HANDLER_H
