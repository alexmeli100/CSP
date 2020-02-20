#ifndef CSP_AC3_STRATEGY_H
#define CSP_AC3_STRATEGY_H

#include <deque>
#include "inference_strategy.h"

namespace csp {
    template<is_var VAR, typename VAL>
    class AC3Strategy : public InferenceStrategy<VAR, VAL> {
    public:
        void apply(CSP<VAR, VAL> &csp);

        void apply(CSP<VAR, VAL> &csp, Assignment<VAR, VAL> assign, VAR var);

    private:
        void reduce_domains(std::deque<VAR> &queue, CSP<VAR, VAL> &csp);

        bool revise(VAR &xi, VAR &xj, Constraint<VAR, VAL> &cons, CSP<VAR, VAL> &csp);
    };


}


#endif //CSP_AC3_STRATEGY_H
