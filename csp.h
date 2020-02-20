#ifndef CSP_CSP_H
#define CSP_CSP_H

#include <vector>
#include <unordered_map>
#include <optional>
#include "domain.h"
#include "constraint.h"

namespace csp {
    template <is_var VAR, typename VAL>
    class CSP {
    public:
        CSP() = default;

        CSP(const CSP &csp) : variables(csp.variables), domains(csp.domains), constraints(csp.constraints),
                              var_indexhash(csp.var_indexhash), cnet() {}

        void add_variable(const VAR &var);

        std::vector<VAR> get_variables();

        int index_of(const VAR &var);

        Domain<VAR> get_domain(const VAR &var);

        void set_domain(const VAR &var, Domain<VAL> domain);

        bool remove_value_from_domain(const VAR &var, const VAL &val);

        void add_constraint(Constraint<VAR, VAL> &constraint);

        bool remove_constraint(const Constraint<VAR, VAL> &constraint);

        auto get_constraints();

        auto get_constraints(const VAR &var);

        auto get_neighbor(const VAR &var, const Constraint<VAR, VAL> &constraint);

    private:
        std::vector<VAR> variables;
        std::vector<VAL> domains;
        std::vector<Constraint<VAR, VAL>> constraints{};
        std::unordered_map<Variable, int> var_indexhash;
        std::unordered_map<Variable, std::vector<Constraint<VAR, VAL>>> cnet;
    };


}




#endif //CSP_CSP_H
