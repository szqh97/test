#include <iostream>
#include <unordered_map>
#include <memory>
int main()
{
    std::unordered_map<std::string, std::string> h;
    h["kkk"] = "kk";
    h["t"] = "t";
    h["t12"] = "t";
    auto it = h.find("tm");
    if (it == h.end()) std::cout << "NNNNNN" << std::endl;
    std::cout << h.size() << std::endl;
    std::cout << h.size() << std::endl;
    std::cout << h["t"] << std::endl;


    return 0;
}
