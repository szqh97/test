#include <iostream>
#include <string>
#include <regex>

int main()
{
    const std::regex r("/");
    std::string orgins  = "teamtalk/data/";
    std::string replace = "\\\\";
    std::string newstr = std::regex_replace(orgins, r, replace);
    std::cout << newstr << std::endl;

    
    return 0;
}
