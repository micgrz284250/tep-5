//
// Created by mkgrz on 19.11.2025.
//

#include "console.h"
#include "tree.h"
#include "parser.h"
#include <iostream>

using namespace std;

void console::run() {
    string input;

    tree *tre = NULL; // NOLINT(*-use-nullptr)

    bool running = true;

    while (running) {
        cout << ">";
        getline(cin, input);

        if (input == "exit") {
            running = false;
            if (tre != NULL) delete tre; // NOLINT(*-use-nullptr)
        }
        if (input.substr(0,5) == "enter" && input.length() > 5) {
            string str_arg = input.substr(6);
            const string *arg = parser::parse(str_arg);
            const int arg_length = parser::string_table_length(str_arg);
            delete tre;
            tre = new tree(arg, arg_length);
            delete[] arg;
        }
        if (input.substr(0, 5) == "print") {
            if (tre != NULL) tre->print(); // NOLINT(*-use-nullptr)
        }
        if (input.substr(0, 4) == "vars") {
            if (tre != NULL) tre->print_variables(); // NOLINT(*-use-nullptr)
            cout << endl;
        }
        if (input.substr(0, 4) == "comp" && input.length() > 4) {
            if (tre != NULL) { // NOLINT(*-use-nullptr)
                string str_arg = input.substr(5);
                string *arg = parser::parse(str_arg);
                const int arg_length = parser::string_table_length(str_arg);
                cout << tre->compile(arg, arg_length) << endl;
                cout << endl;
                delete[] arg;
            }
        }
        if (input.substr(0, 4) == "join" && input.length() > 4) {
            if (tre != NULL) { // NOLINT(*-use-nullptr)
                string str_arg = input.substr(5);
                const string *arg = parser::parse(str_arg);
                const int arg_length = parser::string_table_length(str_arg);
                tree other = tree(arg, arg_length);
                *tre = *tre + other;
                delete[] arg;
            }
        }
    }
}