#include "gmock/gmock.h"

#include <cstring>
#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace testing;
using namespace std;

class CodeLineCounter {
    istream& is_;
public:
    CodeLineCounter(istream& is) : is_(is) {}

    int lineCount() {
        string line;
        int lc = 0;
        while (getline(is_, line)) {
            if (containsCode(line)) ++lc;
        }
        return lc;
    }

private:
    bool containsCode(string line) {
        string::iterator it = line.begin();
        for (; it != line.end(); ++it) {
            if (!isspace(*it)) {
                return true;
            }
        }
        return false;
    }
};

TEST(ACodeLineCounter, TellsLineCountWhenALineIsCode) {
    string input = "int i = 0";
    stringstream ss(input);
    CodeLineCounter subject(ss);

    ASSERT_THAT(subject.lineCount(), Eq(1));
}

TEST(ACodeLineCounter, TellsLineCountWhenAllLinesAreCode) {
    string input = 
        "int i = 0;\n"
        "int j = 1;";
    stringstream ss(input);
    CodeLineCounter subject(ss);

    ASSERT_THAT(subject.lineCount(), Eq(2));
}

TEST(ACodeLineCounter, DoesNotCountEmptyLines) {
    string input = 
        "int i = 0;\n"
        "\n"
        "int j = 1;";
    stringstream ss(input);
    CodeLineCounter subject(ss);

    ASSERT_THAT(subject.lineCount(), Eq(2));
}

TEST(ACodeLineCounter, DoesNotCountLinesContainingJustWhitespaceCharacters) {
    string input = 
        "int i = 0;\n"
        " \t  \n"
        "int j = 1;";
    stringstream ss(input);
    CodeLineCounter subject(ss);

    ASSERT_THAT(subject.lineCount(), Eq(2));
}
