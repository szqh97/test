#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
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

    std::string url = "ed2k://|file|Thomas.-.Newman.%5B007%E5%B9%BD%E7%81%B5%E5%85%9A.-.Spectre%5D.%E4%B8%93%E8%BE%91.%28MP3%29.rar|250628225|81347d39ead465175661a77785b5e668|/";
    vector<string> strvec;
    boost::split(strvec, url,  boost::algorithm::is_any_of("://"));
    //string prefix = boost::to_lower_copy(*strvec.begin());
    boost::to_lower(*strvec.begin());


    cout << boost::equals(*strvec.begin(), "ed2k") << endl;

    cout << strvec[0] << std::endl;



    vector<string> sstrvec;
    boost::split(sstrvec, url, boost::algorithm::is_any_of("|"));
    cout << "fields size is: " << sstrvec.size() << endl;
    cout << sstrvec[4] << endl;
    string ss = boost::to_upper_copy(sstrvec[4]);
    cout << "xxxxx " << ss <<endl;


    cout << "-----------------------------------------" << endl;

    std::string exp = "Key  Peele";

    vector<string> keysplited;
    boost::split(keysplited, exp, boost::algorithm::is_any_of(" "));
    cout << boost::join(keysplited, ".*") << endl;



    cout << "-----------------------------------------manget-----------------------------------------"<< endl;

    std::string manget_url = "magnet:?xt=urn:btih:e14aba3cae1fe69d71cbdacc1239aab3a36258aa&dn=The.Fairly.OddParents.5.Seasons&tr=udp%3A%2F%2Ftracker.openbittorrent.com%3A80&tr=udp%3A%2F%2Ftracker.publicbt.com%3A80&tr=udp%3A%2F%2Ftracker.istole.it%3A6969&tr=udp%3A%2F%2Ftracker.ccc.de%3A80";
    vector<std::string>().swap(strvec);
    boost::split(strvec, manget_url, boost::algorithm::is_any_of("&"));
    std::string magnet_prex = strvec.front();
    cout << magnet_prex << endl;
    vector<std::string>().swap(strvec);
    boost::split(strvec, magnet_prex, boost::algorithm::is_any_of(":"));
    cout << strvec.back() << endl;
    








    return 0;
}
