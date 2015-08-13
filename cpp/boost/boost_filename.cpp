/*
 * g++ --std=c++11 -g  boost_filename.cpp  -lboost_filesystem -lboost_system -lboost_date_time
 */
#include <stdio.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/system/system_error.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
int main()
{
    
    boost::filesystem::path path("/usr/local/include"); // random pathname
    bool result = boost::filesystem::is_directory(path);  
    std::cout << "is regular file: " << boost::filesystem::is_regular_file(path) << std::endl;
    printf("Path is a directory : %d\n", result);

    boost::filesystem::path::iterator pi = path.begin();
    while (pi != path.end())
    {
        std::cout << *pi << std::endl;
        ++pi;
    }

    try
    {
        boost::filesystem::path src_path("/usr/tetetet");
        boost::filesystem::path dst_path("/xxxxx");
        boost::filesystem::rename(src_path, dst_path);
    }
    catch(boost::filesystem::filesystem_error err)
    {
        std::cout << err.what() << std::endl;
    }

    // get the size of file 
    boost::filesystem::path tmp_csv("/tmp/2015-01-01_2015-02-01_ugchybrid_0801142143.csv");
    uintmax_t  u_file_size = boost::filesystem::file_size(tmp_csv);
    std::cout << boost::filesystem::file_size(tmp_csv) << std::endl;

    // test space info 
    boost::filesystem::space_info file_space_info  = boost::filesystem::space(tmp_csv);
    std::cout << "available: " << file_space_info.available << ", capacity: " << file_space_info.capacity << ", free: " << file_space_info.free << std::endl;

    // test last write time and print the time by boost
    std::time_t last_modify_time = boost::filesystem::last_write_time(tmp_csv);
    std::cout << "the last write time is: " << last_modify_time<< std::endl;
    std::cout << boost::posix_time::to_simple_string(boost::posix_time::from_time_t(last_modify_time)) << std::endl;
    std::cout << boost::posix_time::to_iso_string(boost::posix_time::from_time_t(last_modify_time)) << std::endl;
    std::cout << boost::posix_time::to_iso_extended_string(boost::posix_time::from_time_t(last_modify_time)) << std::endl;

    boost::system::error_code err_code;

    std::cout << "create directory: " << boost::filesystem::create_directory("/tmp/test_boost", err_code) << std::endl;
    std::cout << "create directory err code: " << err_code << std::endl;


    return 0;
}
