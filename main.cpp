#include <iostream>

#include "my_smart_pointer.h"
#include "simple_testing_class.h"
#include "tep_3/parser.h"
#include "tep_3/tree.h"

int main() {
    my_smart_pointer<int> smrt(new int(5));
    my_smart_pointer<int> smrt2(new int(67));
    my_smart_pointer<int> smrt2_1(smrt2);
    my_smart_pointer<std::string> smrt3(new std::string("Hello World"));

    std::cout << *smrt << std::endl;
    std::cout << *smrt2 << std::endl;
    std::cout << *smrt2_1 << std::endl;
    std::cout << *smrt3 << std::endl;
    std::cout << std::endl;

    my_smart_pointer<int> smrt1_move(std::move(smrt));
    std::cout << *smrt1_move << std::endl;
    std::cout << std::endl;

    my_smart_pointer<int> smrt2_move(new int(68));
    std::cout << *smrt2_move << std::endl;
    smrt2_move = std::move(smrt2);
    std::cout << *smrt2_move << std::endl;

    my_smart_pointer<std::string> smrt3_move(new std::string("Hello World_move"));
    my_smart_pointer<std::string> smrt3_move_2(new std::string("Hello World_move_2"));
    std::cout << *smrt3 << std::endl;
    std::cout << *smrt3_move << std::endl;
    std::cout << *smrt3_move_2 << std::endl;

    smrt3_move = std::move(smrt3);
    smrt3_move_2 = std::move(smrt3_move);
    std::cout << *smrt3_move_2 << std::endl;

    // for testing
    // std::string input_str = "+ 1 2";
    // std::string *input = parser::parse(input_str);
    // int input_len = parser::string_table_length(input_str);
    // std::cout << input_len << std::endl;
    //
    // tree other_tree(input, input_len);
    // other_tree.print();
    // tree my_tree(std::move(other_tree));
    // my_tree.print();
    // other_tree.print();
    //
    // delete[] input;
    return 0;
}
