#include <iostream>
#include <boost/regex.hpp>
using namespace std;

int main(int argc, char *argv[])
{
    boost::smatch matches;

    //string seedurl = "http://aaaaletorrenty.pl/download.php?id=c4d8ce7b45295e2a7028c60b8b390a6319a32a2a&f=FutileStruggles+Brielleas+Blackmail+Blunder-Part+1+HD+%5BHD-720p%5D.torrent";
    string seedurl = "http://itorrents.org/torrent/7E78D74BDCE89A8EA2F2A98D560F833BA6042727.torrent?title=%5BKaTorrents.space%5Dnurarihyon.no.mago.nura.rise.of.the.yokai.clan.dual.audio.720p";
    //seedurl = "ABCD";
    boost::regex reg("[a-fA-F0-9]{40, 40}", boost::regex::perl);
    //boost::regex reg("A.C", boost::regex_constants::perl);
    //string reg = "[a-fA-F0-9]";
    bool b = boost::regex_search(seedurl, matches, reg);
    cout << matches.size() << endl;
    cout << matches[0] << endl;
    cout << b << endl;
    return 0;
}
