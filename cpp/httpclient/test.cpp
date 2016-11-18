#include <iostream>
#include "httpclient.h"
#include <curl/curl.h>
#include <string>
using namespace std;
int main ( int argc, char *argv[] )
{
    
    curl_global_init(CURL_GLOBAL_ALL);
    CHttpClient client = CHttpClient();
    string strUrl = "http://192.168.1.249:80/TVAds/videocapture";
    //strUrl = "http://app-test.kaipao.cc/v1/user/loginv";

    string strInfo = "u=18814842159&p=111111&sign=42557FBC90E10CAD27FAC0F9D8BA94E9";
    string strResp;
    cout << "POST ret: " << client.Post(strUrl, strInfo, strResp) << endl;
    cout << strInfo << endl << strResp <<endl;
    curl_global_cleanup();



    return 0;
}			/* ----------  end of function main  ---------- */

