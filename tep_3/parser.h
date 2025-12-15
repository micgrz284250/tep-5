//
// Created by mkgrz on 15.11.2025.
//

#ifndef TEP_3_PARSER_H
#define TEP_3_PARSER_H
#include <string>

using namespace std;

class parser {
public:
    static string *parse(string &input);

    static int string_table_length(string &input);

    static string variable_parse(const string &input);

    static bool is_variable(const string &input);
};


#endif //TEP_3_PARSER_H