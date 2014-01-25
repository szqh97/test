#include <iostream>
#include <string>
#include <typeinfo>
#include "Typelist.h"
using namespace std;

struct Widget 
{
//    int i;
};

template <class T>
struct Holder
{
    T value_;
};

template <class Tlist, template<class> class Unit>
class GenScatterHierarchy;

// GenScatterHierarchy specialization: TypeList to Unit
template <class T1, class T2, template <class> class Unit>
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
    GenScatterHierarchy(){cout << "GenScatterHierarchy : public Unit <" << typeid(AtomicType).name()<< ">" << endl; }
};

// Do nothing for NullType
template <template <class> class Unit>
class GenScatterHierarchy<NullType, Unit>
{
    public:
    GenScatterHierarchy(){cout << "GenScatterHierarchy<NullType, Unit>" << endl;}
};

// Access a base class by type name
template <class T, class TList, template<class>class Unit>
Unit<T>& Field(GenScatterHierarchy<TList, Unit>& obj)
{
    return obj;
}

template <int v>
struct Int2Type
{
    enum {value = v};
};

template <class TList, template <class> class Unit>
Unit<TList::Head>& FieldHelper(GenScatterHierarchy<TList,Unit>& obj, Int2Type<0>)
{
    GenScatterHierarchy<TList::Head, Unit>& leftBase = obj;
    return leftBase;
}

template <int i, class TList, template<class>class Unit>
Unit<TypeAt<Tlist, index>::Result>& FieldHelper(GenScatterHierarchy<TList,  Unit>& obj, Int2Type<i>)
{
    GenScatterHierarchy<TList::Tail, Unit>& rightBase = obj;
    return FieldHelper(rightBase, Int2Type<i-1>());
}
template<int i, class TList, template <class>class Unit>
Unit<TypeAt<TList, index>::Result >&
Field(GenScatterHierarchy<TList, Unit>& obj)
{
    return FieldHelper(obj, Int2Type<i>());
}


int main ( int argc, char *argv[] )
{
    typedef GenScatterHierarchy<
            TYPELIST_3(int, char, Widget), 
            Holder> 
        WidgetInfo;
    WidgetInfo obj;
    cout << sizeof(Holder<Widget>) << endl;
    cout << "sizeof(obj) " << sizeof(obj) << endl;
    char name = (static_cast<Holder<char>&>(obj)).value_;

     
    return 0;
}			/* ----------  end of function main  ---------- */
