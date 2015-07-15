#include <cstring>
#include <iostream>

class CodeLineCounter {
    std::istream& is_;
public:
    CodeLineCounter(std::istream& is) : is_(is) {}

    int lineCount();

private:
    bool containsCode(std::string line);
};


