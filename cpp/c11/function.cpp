#include <iostream>
#include <functional>
void foo(const std::string& s)
{
    std::cout << s << std::endl;
}
int main()
{
    void (*pFunc)(const std::string&) = foo;
    pFunc("bar");

    std::function
    return 0;
}
