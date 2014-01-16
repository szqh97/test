#include <iostream>
using namespace std;
template <class Window, class Controller>
class Widget
{

    public:
        Window w;
        Controller c;
};


int main ( int argc, char *argv[] )
{
    Widget<int, float> ww;
    return 0;
}			/* ----------  end of function main  ---------- */

