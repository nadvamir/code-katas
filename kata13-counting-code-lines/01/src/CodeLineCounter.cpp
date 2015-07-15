#include <cstring>
#include <cctype>
#include <iostream>
#include <algorithm>

#include "include/CodeLineCounter.h"

using namespace std;

int CodeLineCounter::lineCount() {
    string line;
    int lc = 0;
    while (getline(is_, line)) {
        if (containsCode(line)) ++lc;
    }
    return lc;
}

bool CodeLineCounter::containsCode(string line) {
    string::iterator it = line.begin();
    string::iterator end = line.end();

    if (size_t commentPos = line.find("//") != string::npos) {
        end = line.begin() + commentPos;
    }

    for (; it != end; ++it) {
        if (!isspace(*it)) {
            return true;
        }
    }
    return false;
}
