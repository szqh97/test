#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;


string trim(const string& str)
{
    string::size_type pos = str.find_first_not_of(' ');
    if (pos == string::npos)
    {
        return str;
    }
    string::size_type pos2 = str.find_last_not_of(' ');
    if (pos2 != string::npos)
    {
        return str.substr(pos, pos2 - pos + 1);
    }
    return str.substr(pos);
}

int split(const string& str, vector<string>& ret_, string sep = ",")
{
    if (str.empty())
    {
        return 0;
    }

    string tmp;
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
            ret_.push_back(tmp);
            tmp.clear();
        }
    }
    return 0;
}

string replace(const string& str, const string& src, const string& dest)
{
    string ret;

    string::size_type pos_begin = 0;
    string::size_type pos       = str.find(src);
    while (pos != string::npos)
    {
        cout <<"replacexxx:" << pos_begin <<" " << pos <<"\n";
        ret.append(str.data() + pos_begin, pos - pos_begin);
        ret += dest;
        pos_begin = pos + 1;
        pos       = str.find(src, pos_begin);
    }
    if (pos_begin < str.length())
    {
        ret.append(str.begin() + pos_begin, str.end());
    }
    return ret;
}

string join(const vector<string> &vec, const string sep = ",")
{
    string ret;
    for(int i = 0; i < vec.size(); i++)
    {
        string s = vec[i];
        if (i != vec.size() - 1)
        {
            s += sep;
        }
        ret += s;
    }
    return ret;
}

int main ( int argc, char *argv[] )
{
    string ss = "./a/b/c/d/e/sss.ll.cmk";
    vector<string> vt;
    split(ss, vt, "/");
    for (vector<string>::const_iterator it = vt.begin(); it != vt.end(); ++it)
    {
        cout << *it << " , " ;
    }
    cout << "-------_" << endl;
    vt.pop_back();
    cout << join(vt, "#") << endl;
    std::wstring ws = L"数第一个字节的首字符为非";
    std::string s= "数第一个字节的首字符为非";
    cout << s.substr(0, 3) << endl;
    cout << s.substr(0, 4) << endl;
    std::string ttt = "andriod";
    if (ttt == "andriod")
    {
        std::cout << "KKKKKKKKKKKKK" << std::endl;
    }
    return 0;
}			/* ----------  end of function main  ---------- */
