#include <iostream>

#include "my_smart_pointer.h"
#include "simple_testing_class.h"
#include "tep_3/parser.h"
#include "tep_3/tree.h"

int main() {
    my_smart_pointer<int> smrt(new int(5));
    my_smart_pointer<int> smrt_2(smrt);

    std::string input_str = "+ 1 2";
    std::string *input = parser::parse(input_str);
    int input_len = parser::string_table_length(input_str);
    std::cout << input_len << std::endl;

    tree other_tree(input, input_len);
    tree my_tree(std::move(other_tree));


    delete[] input;
    return 0;
}
