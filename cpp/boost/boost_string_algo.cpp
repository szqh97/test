#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;


bool is_executable(std::string& filename)
{
    return boost::iends_with(filename, ".exe") || boost::iends_with(filename, ".com");
}

int main()
{
    std::string str1("   command.com    ");
    boost::to_upper(str1);
    std::cout << str1 << std::endl;

    boost::trim(str1);
    std::cout << str1 << std::endl;
    
    std::string str2 = boost::to_lower_copy(boost::ireplace_first_copy(str1, "hello", "goodbye"));
    std::cout << str2 << std::endl;
    cout << str1 << (is_executable(str1)? " is": " is not") << " an executable" <<endl;
    
    str2 = boost::trim_left_copy(str1);
    string str3 = boost::trim_right_copy(str2);
    cout << str3 <<endl;






    return 0;
}
