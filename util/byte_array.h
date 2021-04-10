//
// Created by inva on 4/11/21.
//

#ifndef ERISED_BYTE_ARRAY_H
#define ERISED_BYTE_ARRAY_H

#include <QByteArray>

namespace erised::util::byte_array {
QVector<QByteArray> split_to_views(const QByteArray &in, const QByteArray &sep, Qt::SplitBehavior behavior) {
    if (sep.isEmpty()) return {in};

    QVector<QByteArray> ret;
    ret.reserve((behavior == Qt::KeepEmptyParts) ? 1 + (in.size() / sep.size()) : 1 + (in.size() / (sep.size() + 1)));

    int head = 0;
    while (head < in.size()) {
        int end = in.indexOf(sep, head);
        if (end < 0) end = in.size();

        auto part = QByteArray::fromRawData(in.constData() + head, end - head);
        if (!part.isEmpty() || behavior == Qt::KeepEmptyParts) ret += part;

        head = end + sep.size();
    }

    return ret;
}
}  // namespace erised::util::byte_array

#endif  // ERISED_BYTE_ARRAY_H
