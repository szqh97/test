#include <iostream>
#include <string>

#include <boost/regex.hpp>

using namespace std;
using namespace boost;

int main()
{
#if 0
    //问号(?)表示之前的可以选择
    std::string phone =
        "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    boost::regex r(phone);
    //代替
    std::string fmt("$2.$5.$7");
    std::string number("(908)555-1800");

#endif
    std::string exp = "keyPeele";

    //boost::regex r("[.*]\\{2,\\}");
    boost::regex r("[\\s]+", boost::regex::perl);
    std::cout << regex_replace(exp, r, " ") << std::endl;
#if 0
    boost::regex reg("(Colo)(u)(r)", boost::regex::icase|boost::regex::perl);
    std::string s="Colour, colours, color, colourize";
    s=boost::regex_replace(s,reg,"$1$3");
    std::cout << s;

#endif

}

