#include "sum_amounts.hpp"

#include <stdexcept>

namespace sum_amounts {

Settlement settle(std::uint64_t, const std::vector<Obligation>&) {
    throw std::logic_error("not implemented");
}

}  // namespace sum_amounts
