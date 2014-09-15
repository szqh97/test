#include <iostream>
#include "httpclient.h"
#include <string>
using namespace std;
int main ( int argc, char *argv[] )
{
    CHttpClient client = CHttpClient();
    string strUrl = "http://192.168.1.249:80/TVAds/videocapture";
    string strInfo = "{\"type\":\"video\", \"channelUuid\":\"3cea531a-276b-11e4-be49-fa163e2df9cc\", \"beginTimestamp\": 1402531298947, \"endTimestamp\":1402531398947}";
    string strResp;
    client.Post(strUrl, strInfo, strResp);
    cout << strInfo << endl << strResp <<endl;



    return 0;
}			/* ----------  end of function main  ---------- */

