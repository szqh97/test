#include <boost/scoped_array.hpp>
int main(int argc, char *argv[])
{
    boost::scoped_array<int> p {new int[2]};
    *p.get() = 1;
    p[1] = 2;
    return 0;
}
