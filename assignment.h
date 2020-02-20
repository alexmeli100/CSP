#ifndef CSP_ASSIGNMENT_H
#define CSP_ASSIGNMENT_H

#include <vector>
#include <unordered_map>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/view.hpp>
#include "variable.h"

namespace csp {
    template <typename T>
    concept is_var = std::is_base_of<Variable, T>::value;

    template <is_var VAR, typename VAL>
    class Constraint;

    template <is_var VAR, typename VAL>
    class Assignment {
    public:
        Assignment() = default;
        Assignment(const Assignment &ass) : value_map(ass.value_map) {}

        auto get_variables() {
            return value_map | ranges::views::keys;
        }

        auto get_value(const VAL &k) {
            return value_map[k];
        }

        auto add(VAR &k, VAL &v) {
            return value_map.insert({k, v});
        }

        auto remove(const VAR &k) {
            auto v = get_value();
            value_map.erase(k);

            return v;
        }

        constexpr bool contains(VAR &k) {
            return value_map.contains(k);
        }

        bool is_complete(std::vector<VAR> &vars) {
            return ranges::all_of(vars, &contains);
        }

        bool is_consistent(std::vector<Constraint<VAR, VAL>> &constraints) {
            return ranges::all_of(constraints, [this](auto &cons) { return cons.is_satisfiedwith(this); });
        }

    private:
        std::unordered_map<VAR, VAL> value_map;
    };
}


#endif //CSP_ASSIGNMENT_H
