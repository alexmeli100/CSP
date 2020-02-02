#include <string>

#ifndef CSP_VARIABLE_H
#define CSP_VARIABLE_H


class Variable {
public:
    explicit Variable(std::string &name): name(name){};

    [[nodiscard]] std::string getName() const { return name; }

    bool operator==(std::string &s) { return name == s; }

private:
    std::string name;
};


#endif //CSP_VARIABLE_H
