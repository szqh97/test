#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <iostream>


int greet(int i, const char *name)
{

    std::cout << name << "'id is :" << i << std::endl;
    return i * 10;
}

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;
    def ("greet", greet,
            boost::python::args("id", "name"), "Hello worrr!");
}
