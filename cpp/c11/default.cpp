#include <iostream>

using namespace std;

class X{

public:
    X() = default;
    X(const X&);
    X& operator=(const X&);
    ~X() = default;
};

X::X(const X& ) = default;

X& X::operator=(const X&) = default;
