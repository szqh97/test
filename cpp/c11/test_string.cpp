#include <iostream>
#include <string>
int main()
{
    std::string strname = "dj352801";

    uint32_t uid = 0;
    std::string::size_type pos = strname.find_first_not_of("dj");
    std::cout << "pos: " << pos << std::endl;
    if (pos != std::string::npos)
    {
          std::string s(strname, pos, strname.length() - 1);
          uid = atoi(s.c_str());
          std::cout << uid << std::endl;
		
    }

    strname = "&dj:{xxxxxxxxxx}:dj&";
    std::string s(strname, 4, strname.length() - 8);
    std::cout << s << std::endl;
    std::cout <<strname.find_first_of("&dj:") << std::endl;
    std::cout <<strname.find_last_of(":dj&") << std::endl;
    std::string ss=":dj&";
    std::cout << strname.length() -1 << std::endl;

    std::string strValue = "1471935057.1.0.22";
    strValue.replace(0, 10, std::string s("1469158647"));
    std::cout << strValue <<std::endl;
    return 0;
}
