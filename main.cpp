#include <iostream>

#include "my_smart_pointer.h"
#include "simple_testing_class.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    my_smart_pointer<int> smrt(new int(5));
    my_smart_pointer<int> smrt_2(smrt);

    simple_testing_class stp = simple_testing_class(10);

    simple_testing_class stp2 = std::move(stp);

    return 0;
}
