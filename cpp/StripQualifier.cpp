#include <iostream>
using namespace std;
template <typename T>
class TypeTraits
{
    private :
        template <class U> struct unConst
        {
            typedef U Result;
        };
        template <class U> struct unConst<const U>
        {
            typedef u Result;
        };
    public:
        typedef typename unConst<T>::Result NonConstType;
};

int main ( int argc, char *argv[] )
{

    return 0;
}			/* ----------  end of function main  ---------- */

