#include <iostream>
#include <boost/bind.hpp>
#include <boost/bind/apply.hpp>
#include <boost/ref.hpp>
#include <algorithm>
#include <boost/shared_ptr.hpp>
using  namespace std;


int f(int a, int b )
{
    return a + b;
}

int  g(int a, int b, int c)
{
    return a + b + c;
}

int f_ptr(int* a , int* b)
{
    return *a + *b;
}

struct F
{
    int operator() (int a, int b ){return a - b;}
    bool operator() (long a , long b) {return a == b;}
};

struct F2 
{
    int s;
    typedef void result_type;
    void operator()(int x){s+=x;}
};


struct X
{
    bool f(int x)
    {
        std::cout << "in Struct X: " << x << std::endl;
        return true;
    }
};

void print_info(int x)
{
    std::cout << "print : " << x << std::endl;
}

int main()
{
    int i = 1;
    int j = 3;
    cout << std::bind2nd(std::ptr_fun(f), 4)(11) << endl;
    cout << boost::bind(f, 100, 200)() << endl;
    cout << boost::bind<int>(g, _1, 9, _1)(10) << endl;
    cout << boost::bind(f ,boost::cref(i), 1)() <<endl;
    cout << boost::bind<int>(f_ptr,&i,&j)() <<endl;

    F sf;
    int x = 104;

    cout << bind<int>(sf, _1, _1)(x)<< endl;

    x = 8;
    cout << bind(std::less<int>(), _1, 9)(x) << endl;

    F2 f2={0};
    int a[] = {1,2,3};
    std::for_each(a, a+3, boost::bind(boost::ref(f2), _1));
    cout << f2.s << endl;

    X sx;
    shared_ptr<X> p(new X);

    boost::bind(&X::f, boost::ref(sx), _1)(i); //sx.f(i)
    boost::bind(&X::f, &sx, _1)(i); //(&sx)->f(i)
    boost::bind(&X::f, sx, _1)(i);  //(internal copy of sx).f(i)
    boost::bind(&X::f, p, _1)(i);  //(internal copy of p)->f(i)

    typedef void(*pf)(int);
    std::vector<pf> v;

    for (int i = 0; i < 9; ++i) 
    {
        v.push_back(print_info);
    }

    std::for_each(v.begin(), v.end(), boost::bind(boost::apply<void>(), _1, 5));


    
    return 0;
}

