#include <iostream>
#include <string>
#include <future>
#include <thread>
struct X {
    void foo (int n, const std::string s) {
        std::cout << n << std::ends << s << std::endl;
    }
    std::string bar(const std::string s) {
        return s;
    }
};
struct Y {
    double operator() (double d ) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout <<  d << std::endl;
        return d;
    }
};

int main()
{
    X x;
    auto f1 =  std::async(&X::foo, &x, 42, "hello");
    auto f2 = std::async(&X::bar, x, "goodbye");
    f1.wait();
    std::cout << f2.get() << std::endl;

    Y y;
    auto f3 = std::async(Y(), 3.141);

    std::cout << f3.get() << std::endl;
    auto f4 = std::async(std::ref(y), 2.718);
    std::cout << f4.get() << std::endl;


    return 0;
}


