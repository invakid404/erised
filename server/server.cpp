//
// Created by inva on 2/28/21.
//

#include "server.h"

#include <QWebSocket>
#include <QWebSocketServer>

#include "handler.h"

QT_USE_NAMESPACE

erised::server::server_t::server_t(quint16 port, bool debug, QObject* parent)
    : QObject(parent),
      web_socket_server(new QWebSocketServer(QStringLiteral("Erised"), QWebSocketServer::NonSecureMode, this)),
      debug(debug) {
    if (this->web_socket_server->listen(QHostAddress::Any, port)) {
        if (this->debug) {
            qDebug() << "Server listening on port" << port;
        }

        connect(this->web_socket_server, &QWebSocketServer::newConnection, this, &server_t::on_new_connection);
        connect(this->web_socket_server, &QWebSocketServer::closed, this, &server_t::closed);
    }
}

erised::server::server_t::~server_t() {
    if (this->debug) {
        qDebug() << "Server shutting down";
    }

    this->web_socket_server->close();

    qDeleteAll(this->clients.begin(), this->clients.end());
}

void erised::server::server_t::broadcast_text_message(const QString& message, QWebSocket* sender) {
    for (auto& client : this->clients) {
        if (sender == client) {
            continue;
        }

        client->sendTextMessage(message);
    }
}

void erised::server::server_t::on_new_connection() {
    auto* socket = this->web_socket_server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &server_t::process_text_message);
    connect(socket, &QWebSocket::disconnected, this, &server_t::socket_disconnected);

    this->clients << socket;

    // Send full info to the newly connected socket
    handler_t::get_instance().process_new_connection(socket);
}

void erised::server::server_t::process_text_message(QString const& message) {
    auto* client = qobject_cast<QWebSocket*>(sender());
    if (this->debug) {
        qDebug() << "Message received:" << message;
    }

    if (client) {
        // Broadcast the packet to all clients
        this->broadcast_text_message(message, client);

        handler_t::get_instance().process_packet(client, message);
    }
}

void erised::server::server_t::socket_disconnected() {
    auto* client = qobject_cast<QWebSocket*>(sender());
    if (this->debug) {
        qDebug() << "Socket disconnected:" << client;
    }

    if (client) {
        handler_t::get_instance().socket_disconnected(client);

        this->clients.removeAll(client);
        client->deleteLater();
    }
}
