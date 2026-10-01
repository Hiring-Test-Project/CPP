#pragma once

#include <cstdint>
#include <vector>

namespace sum_amounts {

struct Obligation {
    std::uint64_t id;
    std::uint64_t amount_due;
    std::uint64_t priority;
};

struct Line {
    std::uint64_t id;
    std::uint64_t applied;
};

struct Settlement {
    std::vector<Line> lines;
    std::uint64_t unapplied;
};

Settlement settle(std::uint64_t payment, const std::vector<Obligation>& obligations);

}  // namespace sum_amounts
