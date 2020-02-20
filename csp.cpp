#include "csp.h"
#include "range/v3/action/remove.hpp"

namespace csp {
    template<is_var VAR, typename VAL>
    void CSP<VAR, VAL>::add_variable(const VAR &var) {
        if (!var_indexhash.contains(var)) {
            Domain<VAL> domain(std::vector<VAL>{});
            variables.push_back(var);
            domains.push_back(domain);
            var_indexhash.insert({var, variables.size() - 1});
            cnet.insert(var, std::vector<Constraint<VAR, VAL>>{});
        }
    }

    template<is_var VAR, typename VAL>
    std::vector<VAR> CSP<VAR, VAL>::get_variables() {
        return variables;
    }

    template<is_var VAR, typename VAL>
    int CSP<VAR, VAL>::index_of(const VAR &var) {
        return var_indexhash.at(var);
    }

    template<is_var VAR, typename VAL>
    Domain<VAR> CSP<VAR, VAL>::get_domain(const VAR &var) {
        return domains[index_of(var)];
    }

    template<is_var VAR, typename VAL>
    void CSP<VAR, VAL>::set_domain(const VAR &var, Domain<VAL> domain) {
        domains[index_of(var)] = domain;
    }

    template<is_var VAR, typename VAL>
    bool CSP<VAR, VAL>::remove_value_from_domain(const VAR &var, const VAL &val) {
        auto curr_domain = get_domain(var);
        std::vector<VAL> values(curr_domain.size());

        for (auto v: curr_domain) {
            if (v != val)
                values.push_back(v);
        }

        if (values.size() < curr_domain.size()) {
            set_domain(var, Domain<VAL>(values));
            return true;
        }

        return false;
    }

    template<is_var VAR, typename VAL>
    void CSP<VAR, VAL>::add_constraint(Constraint<VAR, VAL> &constraint) {
        constraints.push_back(constraint);
        ranges::for_each(constraint.get_scope(), [this, constraint](auto &var) { cnet.at(var).push_back(constraint); });
    }

    template<is_var VAR, typename VAL>
    bool CSP<VAR, VAL>::remove_constraint(const Constraint<VAR, VAL> &constraint) {
        auto s = constraints.size();
        constraints = ranges::actions::remove(constraints, constraint);

        if (s != constraints.size()) {
            ranges::for_each(constraint.get_scope(), [this, constraint](auto &var) {
                cnet[var] = ranges::actions::remove(cnet.at(var), constraint);
            });
            return true;
        }

        return false;
    }

    template<is_var VAR, typename VAL>
    auto CSP<VAR, VAL>::get_constraints() {
        return constraints;
    }

    template<is_var VAR, typename VAL>
    auto CSP<VAR, VAL>::get_constraints(const VAR &var) {
        return cnet.at(var);
    }

    template<is_var VAR, typename VAL>
    auto CSP<VAR, VAL>::get_neighbor(const VAR &var, const Constraint<VAR, VAL> &constraint) {
        auto scope = constraint.get_scope();

        if (scope.size() == 2) {
            return var == scope[0] ? std::optional(scope[1]) : std::optional(scope[0]);
        }

        return std::nullopt;
    }


}