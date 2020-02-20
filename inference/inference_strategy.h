#ifndef CSP_INFERENCE_STRATEGY_H
#define CSP_INFERENCE_STRATEGY_H

#include "../csp.h"

namespace csp {
    template<is_var VAR, typename VAL>
    class InferenceStrategy {
    public:
        virtual void apply(CSP<VAR, VAL> &csp) = 0;

        virtual void apply(CSP<VAR, VAL> &csp, Assignment<VAR, VAL> ass, VAR var) = 0;
    };
}

#endif //CSP_INFERENCE_STRATEGY_H
