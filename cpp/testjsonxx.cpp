#include "jsonxx.h"
#include <iostream>
#include <time.h>
#include <regex>
#include <iterator>
#include <string>
#include <sstream>

int main()
{
    time_t now;
    time(&now);
    jsonxx::Object  body;
    body << "title" << "kkkkk";
    body << "ticker" << "test ticker";
    body << "ts" <<now;
    jsonxx::Object response;
    std::string bbb = body.json();
    std::regex r("\n\t");
    std::string out;
    std::regex_replace(std::back_inserter(out), bbb.begin(), bbb.end(), r, "");
    std::cout << out << std::endl;
    response << "body" << bbb;

    std::cout << bbb << std::endl;
    bbb = "\"from_id\":" + std::to_string(43) + ", from_uid" + std::to_string(11);
    jsonxx::Object c;
    c.parse(bbb);
    std::cout << bbb << std::endl;
    if (c.has<jsonxx::Number>("kkk"))
    {

    int id = c.get<jsonxx::Number>("kkk");
    }





    return 0;
}
