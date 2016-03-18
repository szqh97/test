#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;

int main( int argc, char * argv[] )
{
    //string exp = "Key   Peele";
    string exp = "The Game Key.and.        his.girlfriend;.Keegan.and.Jordan.                            havin.2014.HDTV.XviD-LOL[VTV].mp4";
    exp = string(" ") + exp + " ";
    printf("exp 1 [%s]\n", exp.c_str());

    //while(strstr(exp.c_str(), "  ") != NULL) {
    //    boost::algorithm::replace_all(exp, "  ", " ");
    //}
    printf("exp 2 [%s]\n", exp.c_str());

    boost::regex r("[\\s]+", boost::regex::perl);
    exp = boost::regex_replace(exp, r, " ");

    boost::algorithm::replace_all(exp, " ", ".*");
    printf("exp 3 [%s]\n", exp.c_str());
 
    boost::regex reg(exp, boost::regex::icase| boost::regex::sed);
    boost::cmatch m;

    //string dstr = "Key.and.Peele.Season.3.Episode.13.Keegan.gets.distracted.while.on.the.phone.with.his.girlfriend;.Keegan.and.Jordan.havin.2014.HDTV.XviD-LOL[VTV].mp4";
    string dstr = "The Game Key.and.        his.girlfriend;.Keegan.and.Jordan.                            havin.2014.HDTV.XviD-LOL[VTV].mp4";
    printf("str  [%s]\n", dstr.c_str());

    if(boost::regex_match(dstr.c_str(), m, reg)){
        printf("match\n");
    }
    else {
        printf("not match\n");
    }



    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;

    //string e = "The.*Game.*Key.and..*his.girlfriend;.Keegan.and.Jordan..*havin.2014.HDTV.XviD-LOL[VTV].mp4";
    //string  e= "The Game Key.and.        his.girlfriend;.Keegan.and.Jordan.                            havin.2014.HDTV.XviD-LOL[VTV].mp4 ";
    //string e= ".*The.*Game.*Key\\.and\\..*his\\.girlfriend;\\.Keegan\\.and\\.Jordan\\..*havin\\.2014\\.HDTV\\.XviD-LOL[VTV]\\.mp4.*";
    //string dst = " The Game Key.and.        his.girlfriend;.Keegan.and.Jordan.                            havin.2014.HDTV.XviD-LOL[VTV].mp4 ";

    string e= ".*The.*Game.*Key.and..*his.girlfriend;.Keegan.and.Jordan..*havin.\\{\\}2014.HDTV.XviD-\\(\\)LOL\\[VTV\\].mp?4?+.*";
    string dst = "The Game Key.and.        his.girlfriend;.Keegan.and.Jordan.                            havin.{}2014.HDTV.XviD-()LOL[VTV].mp?4?+";
    boost::regex rr(e, boost::regex::perl);

    boost::smatch sm;
    if (boost::regex_match(dst, sm, rr))
    {
        cout << "match" << endl;
    }
    else {
        cout << "no match" << endl;
    }
    cout << sm.size() << endl;
}

