#include <iostream>
#include <vector>
using namespace std;

template <class T, class U>
class Conversion
{
    typedef char Small;
    class Big { char dummy[2];};
    static Small Test(U);
    static Big Test(...);
    static T MakeT();
public:
    enum { exists  = 
            sizeof(Test(MakeT())) == sizeof(Small) };
};


int main ( int argc, char *argv[] )
{
#if 1
    cout << Conversion<double, int>::exists << " " 
        << Conversion<char, char*>::exists << " "
        << Conversion<size_t, vector<int> >::exists << endl;
#endif
    return 0;
}			/* ----------  end of function main  ---------- */
