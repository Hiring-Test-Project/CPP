#include "sum_amounts.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {

int g_failed = 0;

sum_amounts::Obligation ob(std::uint64_t id, std::uint64_t amount_due, std::uint64_t priority) {
    return sum_amounts::Obligation{id, amount_due, priority};
}

sum_amounts::Line line(std::uint64_t id, std::uint64_t applied) {
    return sum_amounts::Line{id, applied};
}

void expect_settlement(
    const char* name,
    std::uint64_t payment,
    const std::vector<sum_amounts::Obligation>& obligations,
    const std::vector<sum_amounts::Line>& lines,
    std::uint64_t unapplied) {
    try {
        sum_amounts::Settlement got = sum_amounts::settle(payment, obligations);
        if (got.unapplied != unapplied || got.lines.size() != lines.size()) {
            std::cerr << "FAIL: " << name << "\n";
            ++g_failed;
            return;
        }
        for (std::size_t i = 0; i < lines.size(); ++i) {
            if (got.lines[i].id != lines[i].id || got.lines[i].applied != lines[i].applied) {
                std::cerr << "FAIL: " << name << " line " << i << "\n";
                ++g_failed;
                return;
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "FAIL: " << name << " threw " << ex.what() << "\n";
        ++g_failed;
    }
}

void expect_duplicate(
    const char* name,
    std::uint64_t payment,
    const std::vector<sum_amounts::Obligation>& obligations) {
    try {
        sum_amounts::settle(payment, obligations);
        std::cerr << "FAIL: " << name << " did not throw\n";
        ++g_failed;
    } catch (const std::invalid_argument&) {
    } catch (const std::exception& ex) {
        std::cerr << "FAIL: " << name << " threw " << ex.what() << "\n";
        ++g_failed;
    }
}

}  // namespace

int main() {
    expect_settlement("empty", 100, {}, {}, 100);
    expect_settlement(
        "pays in full",
        500,
        {ob(1, 100, 1), ob(2, 40, 3), ob(3, 60, 2)},
        {line(1, 100), line(2, 40), line(3, 60)},
        300);
    expect_settlement(
        "higher priority first",
        60,
        {ob(1, 80, 1), ob(2, 50, 9), ob(3, 25, 9)},
        {line(1, 0), line(2, 50), line(3, 10)},
        0);
    expect_settlement(
        "same priority",
        10,
        {ob(1, 50, 1), ob(2, 30, 1), ob(3, 20, 1)},
        {line(1, 10), line(2, 0), line(3, 0)},
        0);
    expect_settlement(
        "spills to next priority",
        120,
        {ob(1, 100, 1), ob(2, 40, 5), ob(3, 60, 5)},
        {line(1, 20), line(2, 40), line(3, 60)},
        0);
    expect_duplicate("duplicate id", 5, {ob(1, 10, 1), ob(1, 4, 2)});

    if (g_failed != 0) {
        std::cerr << g_failed << " failed\n";
        return 1;
    }
    std::cout << "ok\n";
    return 0;
}
