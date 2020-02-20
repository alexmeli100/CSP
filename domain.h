#ifndef CSP_DOMAIN_H
#define CSP_DOMAIN_H

#include <vector>
#include <range/v3/all.hpp>


namespace csp {
    template <typename VAL>
    class Domain {
    public:
        explicit Domain(std::vector<VAL> &values) : values(values) {};

        constexpr int size() {
            return values.size();
        }

        constexpr bool is_empty() {
            return values.size() == 0;
        }

        bool contains(VAL &value) {
            return ranges::find(values, value) != ranges::end(value);
        }

        bool operator==(Domain<VAL> &d) {
            return values == d.values;
        }

        VAL operator[](int index) const {
            return values[index];
        }

        VAL &operator[](int index) {
            return values[index];
        }


    private:
        std::vector<VAL> values;
    };
}


#endif //CSP_DOMAIN_H
