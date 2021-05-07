//
// Created by inva on 5/7/21.
//

#ifndef ERISED_HTTP_H
#define ERISED_HTTP_H

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace erised::util::http {
inline auto get_page(QUrl const& url) {
    QNetworkAccessManager network_manager;

    QNetworkRequest api_request;

    api_request.setUrl(url);
    api_request.setRawHeader("User-Agent", "Erised (erised.tk)");

    QNetworkReply* api_response = network_manager.get(api_request);

    QEventLoop loop;

    QObject::connect(api_response, SIGNAL(finished()), &loop, SLOT(quit()));
    QObject::connect(api_response, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));

    loop.exec();

    return api_response->readAll();
}
}  // namespace erised::util::http

#endif  // ERISED_HTTP_H
