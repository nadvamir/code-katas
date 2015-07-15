#include "gmock/gmock.h"

#include <cstring>
#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>

#include "include/CodeLineCounter.h"

using namespace testing;
using namespace std;

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

TEST(ACodeLineCounter, DoesNotCountLinesThatJustHaveOneLineComments) {
    string input = 
        "int i = 0;// comment\n"
        " \t  // comment too\n"
        "int j = 1;";
    stringstream ss(input);
    CodeLineCounter subject(ss);

    ASSERT_THAT(subject.lineCount(), Eq(2));
}
