#include <iostream>
#include <vector>
using namespace std;

class Number
{
    public:
        void dubble(int &value)
        {
            value *= 2;
        }
};

class Command
{
    public:
        virtual void execute(int &value) = 0;
};

class SimpleCommand: public Command
{

    private:
        typedef void (Number:: *Action)(int &);
        Number *receiver;
        Action action;
    public:
        SimpleCommand(Number *rec, Action act)
        {
            receiver = rec;
            action = act;
        }

        void execute(int &value)
        {
            (receiver->*action) (value);
        }

};

class MacroCommand: public Command
{
    public:
        void add(Command *cmd)
        {
            clist.push_back(cmd);
        }
        void execute(int &num)
        {
            for (int i = 0; i < clist.size(); ++i)
            {
                clist[i]->execute(num);
            }
        }
    private:
        vector<Command*> clist;
};

int main ( int argc, char *argv[] )
{
    Number object;
    Command *commands[3];
    SimpleCommand s(&object, &Number::dubble);
    commands[0] = &s;

    MacroCommand two;
    two.add(commands[0]);
    two.add(commands[0]);
    commands[1] = &two;

    MacroCommand four; 
    four.add(&two);
    four.add(&two);
    commands[2] = &four;

    int num, index;
    while (true)
    {
        cout << "Enter number selection(0= 2x 1 = 4x 2 = 16x): ";
        cin >> num >> index;
        commands[index]->execute(num);
        cout << "   "  << num << endl;
    }

    return 0;
}			/* ----------  end of function main  ---------- */

