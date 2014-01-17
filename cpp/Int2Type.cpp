#include <iostream>
using namespace std;

template <int v>
struct Int2Type
{
    enum { value = v};
};

template <class T, bool isPolymorphic>
class NiftyContainer
{
private:
    void DoSomething(T *pObj, Int2Type<true>)
    {
        cout << "Int2Type <true> " << endl;
    }
    
    void DoSomething(T *pObjg, Int2Type<false>)
    {
        cout << "Int2Type <false>" << endl;
    }
public:
    void DoSomething(T* pObj)
    {
        DoSomething(pObj, Int2Type<isPolymorphic>());
    }

};


int main ( int argc, char *argv[] )
{
    Int2Type<0> I0;
    int i = 1;
    NiftyContainer<int, false> f;
    f.DoSomething(&i);
    NiftyContainer<int, true> t;
    t.DoSomething(&i);
    return 0;
}			/* ----------  end of function main  ---------- */

