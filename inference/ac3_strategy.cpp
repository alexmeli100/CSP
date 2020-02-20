//
// Created by Alex on 2/19/2020.
//

#include "ac3_strategy.h"

namespace csp {
    template<is_var VAR, typename VAL>
    void AC3Strategy<VAR, VAL>::apply(CSP<VAR, VAL> &csp) {
        std::deque<VAR> queue(csp.get_variables());
        reduce_domains(&queue, &csp);
    }

    template<is_var VAR, typename VAL>
    void AC3Strategy<VAR, VAL>::apply(CSP<VAR, VAL> &csp, Assignment<VAR, VAL> assign, VAR var) {
        auto domain = csp.get_domain(var);
        VAL value = assign.get_value(var);
        assert(domain.contains(value));

        if (domain.size() > 1) {
            std::deque<VAR> queue;
            queue.push_back(var);
            csp.set_domain(var, Domain<VAL>(value));
            reduce_domains(queue, csp);
        }
    }

    template<is_var VAR, typename VAL>
    void AC3Strategy<VAR, VAL>::reduce_domains(std::deque<VAR> &queue, CSP<VAR, VAL> &csp) {
        while (!queue.empty()) {
            auto var = queue.front();
            queue.pop_front();

            for (auto &cons: csp.get_constraints(var)) {
                auto neighbor = csp.get_neighbor(var, cons);

                if (neighbor && revise(neighbor, var, cons, csp)) {
                    if (csp.get_domain(*neighbor).is_empty())
                        return;

                    queue.push_back(*neighbor);
                }
            }
        }
    }

    template<is_var VAR, typename VAL>
    bool AC3Strategy<VAR, VAL>::revise(VAR &xi, VAR &xj, Constraint<VAR, VAL> &cons, CSP<VAR, VAL> &csp) {
        auto curr_domain = csp.get_domain(xi);
        std::vector<VAL> new_values(curr_domain.size());
        Assignment<VAR, VAL> assign;

        for (auto vi: curr_domain) {
            assign.add(xi, vi);

            bool b = ranges::any_of(csp.get_domain(xj), [&assign, xj, cons](auto &vj) {
                assign.add(xj, vj);
                return cons.is_satisfiedwith(assign);
            });

            if (b)
                new_values.push_back(vi);
        }

        if (new_values.size() < curr_domain.size()) {
            csp.set_domain(xi, Domain<VAL>(new_values));
            return true;
        }

        return false;
    }
}

