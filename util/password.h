//
// Created by inva on 4/10/21.
//

#ifndef ERISED_PASSWORD_H
#define ERISED_PASSWORD_H

#include <openssl/evp.h>

#include "byte_array.h"
#include "random.h"

namespace erised::util::password {
const int hash_iterations = 100000;
const auto hash_method = EVP_sha512();

/*
 * Constant-time comparison to prevent timing attacks
 * Taken from https://crackstation.net/hashing-security.htm
 */
inline bool slow_equals(const QByteArray &a, const QByteArray &b) {
    const int len_a = a.length();
    const int len_b = b.length();

    int diff = len_a ^ len_b;
    for (int i = 0; i < len_a && i < len_b; ++i) diff |= a[i] ^ b[i];

    return diff == 0;
}

inline QByteArray generate(const QByteArray &password) {
    std::array<uint32_t, 4> salt{{erised::util::random::rand(), erised::util::random::rand(),
                                  erised::util::random::rand(), erised::util::random::rand()}};

    std::array<unsigned char, 64> out_buf{};
    int hmac_res =
        PKCS5_PBKDF2_HMAC(password.constData(), password.size(), reinterpret_cast<const unsigned char *>(salt.data()),
                          static_cast<int>(sizeof(salt[0]) * salt.size()), hash_iterations, hash_method,
                          static_cast<int>(out_buf.size()), out_buf.data());

    if (hmac_res != 1) return {};

    auto salt_view = QByteArray::fromRawData(reinterpret_cast<const char *>(salt.data()),
                                             static_cast<int>(sizeof(salt[0]) * salt.size()));
    auto out_buf_view =
        QByteArray::fromRawData(reinterpret_cast<const char *>(out_buf.data()), static_cast<int>(out_buf.size()));

    return salt_view.toBase64() + ':' + out_buf_view.toBase64();
}

inline bool verify(const QByteArray &secret, const QByteArray &password) {
    const QVector<QByteArray> list = erised::util::byte_array::split_to_views(secret, ":", Qt::SkipEmptyParts);
    if (list.size() != 2) return false;

    const QByteArray salt = QByteArray::fromBase64(list[0]);
    const QByteArray key = QByteArray::fromBase64(list[1]);

    std::array<unsigned char, 64> outBuf{};
    const int hmacResult = PKCS5_PBKDF2_HMAC(
        password.constData(), password.size(), reinterpret_cast<const unsigned char *>(salt.constData()), salt.size(),
        hash_iterations, hash_method, static_cast<int>(outBuf.size()), outBuf.data());

    if (hmacResult != 1) return false;

    const QByteArray outBufView =
        QByteArray::fromRawData(reinterpret_cast<const char *>(outBuf.data()), static_cast<int>(outBuf.size()));

    return slow_equals(key, outBufView);
}
}  // namespace erised::util::password

#endif  // ERISED_PASSWORD_H
