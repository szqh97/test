#include <boost/phoenix/phoenix.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace boost::phoenix;
using namespace std;
bool is_odd(int i )
{
    return i % 2 == 1;
}

struct is_odd_impl {
    typedef bool result_type;
    template <typename T>
        bool operator()(T t) const {return t % 2 == 1;}
};
boost::phoenix::function<is_odd_impl> is_odd2;

int main()
{
    
    std::vector<int> v{1, 2, 3, 4, 5};
    std::cout << std::count_if(v.begin(), v.end(), is_odd) << std::endl;

    auto lambda = [](int i){return i % 2 == 1;};
    std::cout << std::count_if(v.begin(), v.end(), lambda) << std::endl;

    using namespace boost::phoenix::placeholders;
    auto phoenix = arg1 % 2 == 1;
    std::cout << std::count_if(v.begin(), v.end(), phoenix) << std::endl;

    auto phoenix2 = arg1 > val(2) && arg1 % val(2) == val(1);
    std::cout << std::count_if(v.begin(), v.end(), phoenix2) << std::endl;
    cout << arg1(1,2,3,4,5) << endl;
    cout << arg2(1,2,3,4,5) << endl;
    cout << arg3(1,2,3,4,5) << endl;

    cout << count_if(v.begin(), v.end(), is_odd2(arg1)) << endl;

    BOOST_PHOENIX_ADAPT_FUNCTION(bool, is_odd3, is_odd, 1);
    cout << count_if(v.begin(), v.end(), bind(is_odd, arg1)) << endl;


    return 0;
}

