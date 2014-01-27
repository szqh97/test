#include <iostream>
#include <string>
#include "Typelist.h"
using namespace std;

struct Widget 
{
    int i;
};

template <class Tlist, template<class> class Unit>
class GenScatterHierarchy;

// GenScatterHierarchy specialization: TypeList to Unit
template <class T1, class T2, template <class> class Unit>
//class GenScatterHierarchy <TYPELIST_2(T1, T2), Unit>
class GenScatterHierarchy <Typelist<T1, T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>
    , public GenScatterHierarchy<T2, Unit>
{
    public:
    GenScatterHierarchy() {cout << "GenScatterHierarchy <Typelist<T1, T2>, Unit>: public..." << endl;}
};

// pass an atomic type (nontypelist) to Unit
template <class AtomicType, template <class> class Unit>
class GenScatterHierarchy : public Unit <AtomicType>
{
    public:
    GenScatterHierarchy(){cout << "GenScatterHierarchy : public Unit <AtomicType>" << endl; }
};

// Do nothing for NullType
template <template <class> class Unit>
class GenScatterHierarchy<NullType, Unit>
{
    public:
    GenScatterHierarchy(){cout << "GenScatterHierarchy<NullType, Unit>" << endl;}
};

template <class T>
struct Holder
{
    T value_;
};

int main ( int argc, char *argv[] )
{
    typedef GenScatterHierarchy<
            TYPELIST_3(int, string, Widget), 
            Holder> 
        WidgetInfo;
    WidgetInfo obj;

     
    return 0;
}			/* ----------  end of function main  ---------- */
