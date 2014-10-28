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
    string strInfo = "{\"type\":\"video\", \"channelUuid\":\"3cea531a-276b-11e4-be49-fa163e2df9cc\", \"beginTimestamp\": 1402531298947, \"endTimestamp\":1402531398947}";
    string strResp;
    cout << "POST ret: " << client.Post(strUrl, strInfo, strResp) << endl;
    cout << strInfo << endl << strResp <<endl;
    curl_global_cleanup();

    strUrl = "http://192.168.1.52:8080/metaServer/api/channel";
    strInfo = "";
    cout << "GET ret : " << client.Get(strUrl, strResp) << endl;
    cout << strResp << endl;


    return 0;
}			/* ----------  end of function main  ---------- */

