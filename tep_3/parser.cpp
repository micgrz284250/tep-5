#include "parser.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string *parser::parse(string &input) {
    while (input.find("  ") != string::npos) {
        input.erase(input.find("  "), 1);
    }

    if (input[input.length()-1] == ' ') input.erase(input.length()-1);
    if (input[0] == ' ') input.erase(0, 1);

    int table_len = static_cast<int>(count(input.begin(), input.end(), ' ') + 1);
    string *table = new string[table_len];

    stringstream ss(input);
    string token;
    int i = 0;
    while (getline(ss, token, ' ')) {
        table[i++] = token;
    }

    return table;
}

int parser::string_table_length(string &input) {
    while (input.find("  ") != string::npos) {
        input.erase(input.find("  "), 1);
    }

    return static_cast<int>(count(input.begin(), input.end(), ' ') + 1);
}

string parser::variable_parse(const string &input) {
    string result;
    for (int i = 0; i < input.length(); i++) {
        const int char_int = input[i];
        if ((48 <= char_int && char_int <= 57) || (65 <= char_int && char_int <= 90) || (97 <= char_int && char_int <= 122)) {
            result += input[i];
        }
        else {
            cout << "Error: remove character " << input[i] << endl;
        }
    }
    return result;
}

bool parser::is_variable(const string &input) {
    for (int i = 0; i < input.length(); i++) {
        const char char_int = input[i];
        if ((65 <= char_int && char_int <= 90) || (97 <= char_int && char_int <= 122)) return true;
    }
    return false;
}