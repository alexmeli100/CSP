#ifndef CSP_CSP_H
#define CSP_CSP_H

#include <vector>
#include <unordered_map>
#include "domain.h"
#include "constraint.h"

namespace csp {
    template <is_var VAR, typename VAL>
    class CSP {
    private:
        std::vector<VAR> variables;
        std::vector<VAL> domains;
        std::vector<Constraint<VAR, VAL>> constraints{};
        std::unordered_map<Variable, int> var_indexhash;
    };
}




#endif //CSP_CSP_H
