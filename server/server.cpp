//
// Created by inva on 2/28/21.
//

#include "server.h"

#include <QWebSocket>
#include <QWebSocketServer>

QT_USE_NAMESPACE

erised::server::server(quint16 port, bool debug, QObject *parent) : QObject(parent), web_socket_server(
        new QWebSocketServer(QStringLiteral("Erised"), QWebSocketServer::NonSecureMode, this)), debug(debug) {
    if (this->web_socket_server->listen(QHostAddress::Any, port)) {
        if (this->debug) {
            qDebug() << "Server listening on port" << port;
        }

        connect(this->web_socket_server, &QWebSocketServer::newConnection, this, &server::on_new_connection);
        connect(this->web_socket_server, &QWebSocketServer::closed, this, &server::closed);
    }
}

erised::server::~server() {
    if (this->debug) {
        qDebug() << "Server shutting down";
    }

    this->web_socket_server->close();

    qDeleteAll(this->clients.begin(), this->clients.end());
}

void erised::server::on_new_connection() {
    auto *socket = this->web_socket_server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &server::process_text_message);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &server::process_binary_message);
    connect(socket, &QWebSocket::disconnected, this, &server::socket_disconnected);

    this->clients << socket;
}

void erised::server::process_text_message(QString const& message) {
    auto* client = qobject_cast<QWebSocket*>(sender());
    if (this->debug) {
        qDebug() << "Message received:" << message;
    }

    if (client) {
        client->sendTextMessage(message.toUpper());
    }
}

void erised::server::process_binary_message(QByteArray const& message) {
    auto* client = qobject_cast<QWebSocket*>(sender());
    if (this->debug) {
        qDebug() << "Binary message received:" << message;
    }

    if (client) {
        client->sendBinaryMessage(message);
    }
}

void erised::server::socket_disconnected() {
    auto* client = qobject_cast<QWebSocket*>(sender());
    if (this->debug) {
        qDebug() << "Socket disconnected:" << client;
    }

    if (client) {
        this->clients.removeAll(client);
        client->deleteLater();
    }
}