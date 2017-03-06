#include <iostream>
#include <unordered_map>
int main()
{
    
    std::unordered_map<std::string, std::string> u;
    u["test"] = "kkkkk";
    u["test2"] = "kkkk";
    if (u.find("foo") != u.end()) {
    std::string v = u["foo"];
    std::cout << v <<std::endl;
    }
    else {
        std::cout << "not found it" <<std::endl;
    }
    auto it = u.find("test");
    std::string v2 = u["test"];
    u.erase(it);
    std::cout << v2 << std::endl;

    return 0;
}
