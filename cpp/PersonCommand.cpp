#include <iostream>
#include <string>
using namespace std;
class Person;
class Command
{
public:
    Command(Person *obj = NULL, void(Person:: *meth)() = NULL)
    {
        object = obj;
        method = meth;
    }
    void execute()
    {
        (object->*method)();
    }

private:
    // 1.Create a class that encapsulates an object and memberfunction
    // a pointer to a member function (the attribute's name is 'method'
    Person *object;
    void (Person:: *method)();

};

class Person
{
    public:
    Person(string n, Command c ): cmd(c)
    {
        name = n;
    }

    void talk()
    {
        cout << name << " is talking." << endl;
        cmd.execute();
    }
    void passOn()
    {
        cout << name  << " is passing on" << endl;
        cmd.execute();
    }
    void gossip()
    {
        cout << name << " is gossing." << endl;
        cmd.execute();
    }
    void listen()
    {
        cout << name << " is listening" << endl;
    }

    private:
        string name;
        
        // cmd is a 'black box', it is a method invocation
        // promoted to 'full obj et status'
        Command cmd;

};


int main ( int argc, char *argv[] )
{
    Person wilma ("Wilma", Command());
    Person betty ("Betty", Command(&wilma, &Person::listen));
    Person barney ("Barney", Command(&betty, &Person::gossip));
    Person fred ("Fred", Command(&barney, &Person::passOn));
    fred.talk();


    return 0;
}			/* ----------  end of function main  ---------- */
