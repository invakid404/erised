//
// Created by inva on 4/11/21.
//

#ifndef ERISED_RANDOM_H
#define ERISED_RANDOM_H

#include <QString>

namespace erised::util::random {
class random_t {
public:
    using result_type = uint32_t;

    random_t() : rand_dev{fopen("/dev/urandom", "rb")} {
        if (!rand_dev) qFatal("Failed to open /dev/urandom");
    }

    ~random_t() { fclose(rand_dev); }

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }

    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    result_type operator()() const {
        result_type buf = 0;
        if (fread(&buf, sizeof(buf), 1, this->rand_dev) != 1) qFatal("Read /dev/urandom error");

        return buf;
    }

private:
    FILE *rand_dev;
};

inline uint32_t rand(const uint32_t min = 0, const uint32_t max = std::numeric_limits<uint32_t>::max()) {
    static random_t layer;

    std::uniform_int_distribution<uint32_t> uniform(min, max);

    return uniform(layer);
}
}  // namespace erised::util::random

#endif  // ERISED_RANDOM_H
