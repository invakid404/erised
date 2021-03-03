//
// Created by inva on 2/28/21.
//

#ifndef ERISED_SERVER_H
#define ERISED_SERVER_H

#include <QAbstractSocket>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QObject>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)

QT_FORWARD_DECLARE_CLASS(QWebSocket)

namespace erised {
class server : public QObject {
    Q_OBJECT
public:
    explicit server(quint16 port, bool debug = false,
                    QObject *parent = nullptr);

    ~server() override;
Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void on_new_connection();
    void process_text_message(QString const &);
    void process_binary_message(QByteArray const &);
    void socket_disconnected();

private:
    QWebSocketServer *web_socket_server;
    QList<QWebSocket *> clients;

    bool debug;
};
}  // namespace erised

#endif  // ERISED_SERVER_H
