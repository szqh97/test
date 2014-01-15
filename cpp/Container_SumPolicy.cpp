#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <typeinfo>
#include <iostream>
using namespace std;

template <typename T> 
class ElementT;

template <class T>
class ElementT<vector<T> >
{
    public:
        typedef T Type;
        static T zero(){return 0;}
};

template <class T>
class ElementT<list<T> >
{
    public:
        typedef T Type;
        static T zero(){return 0;}
};

template <class T>
class ElementT<stack<T> >
{
    public:
        typedef T Type;
        static T zero(){return 0;}
};

template <class T>
void printElementType(T const& c)
{
    cout << "Container of " << typeid(typename ElementT<T>::Type).name()
         << " elements." << endl; 
}

template <class C>
typename ElementT<C>::Type SumOfElemnet(C const &c)
{
    typedef typename ElementT<C>::Type Type;
    //Type total = Type();
    Type total = ElementT<C>::zero();
    typename C::const_iterator it = c.begin();
    for (; it != c.end(); ++it)
    {
        total += *it;
    }
    return total;
}


int main ( int argc, char *argv[] )
{
    stack <bool> s;
    printElementType(s);
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    int r = SumOfElemnet(v);
    cout << "The result of SumOfElemnet is " << r << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
