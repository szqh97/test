#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class T>
string int2string(const T& value) {
    stringstream s ;
    s << value;
    return s.str();
}
int main()
{
    uint64_t ts = 1471935057;
    ts = ts<<32;
    ts = ts|12;

    cout << ts << endl;
    cout << (ts & 0xffffffff) << endl;

    cout << int2string(3.4) << endl;

    string value = "1469158647.1.0.222";
    cout << string(value, 15) << endl;
    cout << string(value, 11, 1) << endl;
    cout << string(value, 13, 1) << endl;
    return 0;
}

