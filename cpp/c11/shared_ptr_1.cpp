#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;
class Foo
{
public:
    void print()
    {
        cout << "foo::print" << endl;
    }
};

void dowork1()
{
    shared_ptr<Foo> sp1(new Foo);
    sp1->print();
    cout << "sp1 pointer: " << sp1.get() << std::endl;

    shared_ptr<Foo> sp2(sp1);
    sp2->print();
    shared_ptr<Foo> sp3(sp2);
    cout << "sp1 pointer: " << sp1.get() << endl;
    cout << "sp2 pointer: " << sp2.get() << endl;
    cout << "sp3 pointer: " << sp3.get() << endl;

    cout << "counter sp1: " << sp1.use_count() << endl;
    cout << "counter sp2: " << sp2.use_count() << endl;
    cout << "counter sp3: " << sp3.use_count() << endl;

    sp1.reset();
    cout << "counter sp1: " << sp1.use_count() << endl;
    cout << "counter sp2: " << sp2.use_count() << endl;
    cout << "counter sp3: " << sp3.use_count() << endl;

    sp1->print();
    cout << "counter sp1: " << sp1.use_count() << endl;
    cout << "counter sp2: " << sp2.use_count() << endl;
    cout << "counter sp3: " << sp3.use_count() << endl;

    sp2.reset();
    cout << "counter sp1: " << sp1.use_count() << endl;
    cout << "counter sp2: " << sp2.use_count() << endl;
    cout << "counter sp3: " << sp3.use_count() << endl;

}

void dowork_autoptr()
{
    auto_ptr<Foo> ap1(new Foo);
    ap1->print();
    cout << "ap1 pointer: " << ap1.get() << endl;

    shared_ptr<Foo> sp1(move(ap1));
    sp1->print();
    cout << "ap1 pointer: " << ap1.get() << endl;
    cout << "sp1 pointer: " << sp1.get() << endl;
}

class FooHandler
{
public:
    static Foo* alloc()
    {
        Foo* f = new Foo;
        cout << "a new foo was created " << endl;
        return f;
    }

    static void free(Foo* f)
    {
        delete f;
        cout << "foo destroyed" << endl;
    }
};

void dowork_deleter()
{
    std::shared_ptr<Foo> ptr(FooHandler::alloc(), &FooHandler::free);
    ptr->print();
}

void dowork_get()
{
    shared_ptr<Foo> sp(new Foo);
    Foo* f = sp.get();
    if (f)
    {
        f->print();
    }
}

class PtrUtil
{
public:
    static void is_empty(shared_ptr<string> ptr)
    {
        if(ptr)
            cout << "not empyty" << endl;
        else
            cout << "is empyt" << endl;
    }

};

void doempty()
{
    shared_ptr<string> sp1;
    shared_ptr<string>sp2(new string("demon"));
    PtrUtil::is_empty(sp1);
    PtrUtil::is_empty(sp2);

    sp1.swap(sp2);
    PtrUtil::is_empty(sp1);
    PtrUtil::is_empty(sp2);

}


shared_ptr<int> double_it (const shared_ptr<int>& sp)
{
    *sp *= 2;
    return sp;
}

void dowork_vector()
{
    vector<shared_ptr<int> > numbers;
    numbers.push_back(shared_ptr<int> (new int(1)));
    numbers.push_back(shared_ptr<int> (new int(2)));
    numbers.push_back(shared_ptr<int> (new int(3)));
    cout << "initially " << endl;

    for (vector<shared_ptr<int> >::const_iterator it = numbers.begin(); it != numbers.end(); ++it)
    {
        cout << **it << "(counter = " << (*it).use_count() << ")" << endl;
    }
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), double_it);
    cout << "after transformation " << endl;
    for (vector<shared_ptr<int>>::const_iterator it = numbers.begin(); it != numbers.end(); ++it)
    {
        cout << **it << "(counter = " << (*it).use_count() << ")" << endl;
    }



}
int main ( int argc, char *argv[] )
{
    cout << "===== in dowork1 =====" << endl;
    dowork1();

    cout << "===== in dowork_autoptr =====" << endl;
    dowork_autoptr();

    cout << "===== in dowork_deleter =====" << endl;
    dowork_deleter();

    cout << "===== in dowork_get =====" << endl;
    dowork_get();

    cout << "===== in doempty =====" << endl;
    doempty();

    cout << "===== do dowork_vector =====" << endl;
    dowork_vector() ;

    std::shared_ptr<int> p (NULL);
    if (!p.get()) cout << "KKKKKKKKKKKKKKKK" << endl;
    return 0;
}			/* ----------  end of function main  ---------- */


