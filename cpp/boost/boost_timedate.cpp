#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>


int main ( int argc, char *argv[] )
{
    // strTime is like '20150803'
    std::string strTime = boost::gregorian::to_iso_string(boost::gregorian::day_clock::local_day());
    std::cout << strTime << std::endl;

    // strTime is 20150813T110915
    strTime = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());
    std::cout << strTime << std::endl;

    // strTime is 2015-08-13 11:16:07
    strTime.replace(4, 0, std::string("-"));
    strTime.replace(7, 0, std::string("-"));

    int nPos = strTime.find('T');
    strTime.replace(nPos, 1, std::string(" "));
    strTime.replace(nPos + 3, 0, std::string(":"));
    strTime.replace(nPos + 6, 0, std::string(":"));
    std::cout << strTime << std::endl;

    boost::posix_time::ptime time_now, time_now1;
    boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;

    time_now = boost::posix_time::microsec_clock::universal_time();

    boost::this_thread::sleep(boost::posix_time::millisec(1000));

    time_now1 = boost::posix_time::microsec_clock::universal_time();
    time_elapse = time_now1 - time_now;
    int ticks = time_elapse.ticks();

    std::cout << "ticks is: " << ticks << ", seconds is: " << time_elapse.total_seconds() << std::endl;

    return 0;
}			/* ----------  end of function main  ---------- */

