#ifndef  _test_command_H_
#define  _test_command_H_

class Application;
class Command
{
    public:
        virtual ~Command ();   
        virtual void Execute() = 0;
    protected:
        Command () = default;       

};

class OpenCommand: public Command
{
    public:
        OpenCommand (Application*);                             /* constructor      */
        virtual void Execute();
        OpenCommand ( const OpenCommand &other );   /* copy constructor */
        ~OpenCommand ();                            /* destructor       */

        OpenCommand& operator = ( const OpenCommand &other ); /* assignment operator */

    protected:

    private:

}; /* -----  end of class OpenCommand  ----- */


#endif   
