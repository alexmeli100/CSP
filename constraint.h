#ifndef CSP_CONSTRAINT_H
#define CSP_CONSTRAINT_H

#include <vector>
#include "assignment.h"

namespace csp {
    template <is_var VAR, typename VAL>
    class Constraint {
    public:
        virtual std::vector<VAR> get_scope() = 0;
        virtual bool is_satisfiedwith(const Assignment<VAR, VAL> &assignment) = 0;
    };
}

#endif //CSP_CONSTRAINT_H
