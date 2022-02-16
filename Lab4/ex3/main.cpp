#include <iostream>

#include "util.h"
#include "stuff.h"

int main()
{
    std::cout << "Hello World " << std::endl;
    std::cout << "Hello World " << util::GetAnswer() << std::endl;
    std::cout << "Hello World 2 " << util::GetOtherAnswer() << std::endl;
}
