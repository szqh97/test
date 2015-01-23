#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main ( int argc, char *argv[] )
{
    vector<int> iv;
    iv.push_back(1);
    iv.push_back(2);
    iv.push_back(3);
    for_each(iv.begin(), iv.end(), [](int val){cout << val << endl;});
    return 0;
}			/* ----------  end of function main  ---------- */

