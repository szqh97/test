#ifndef  _builder_H_
#define  _builder_H_
#include <string>
#include "Product.h"
using namespace std;

class Builder
{
    public:
        Builder ();     
        virtual void buildPartHead(const string str = "pre-define") = 0;
        virtual void buildPartBody(const string str = "pre-define") = 0;
        virtual void buildPartFoot(const string str = "pre-define") = 0;
        Product* getProduct() ;
    protected:
        Product* product;
};


class Builder_KindOne: public Builder
{
    public:
        Builder_KindOne ();    
        void buildPartHead(const string str = "red.Head");
        void buildPartBody(const string str = "blue.Body");
        void buildPartFoot(const string str = "black.Foot");
        //Product* getProduct();
    protected:
    private:

}; /* -----  end of class Builder_KindOne  ----- */

class Builder_KindTwo: public Builder
{
    public:
        Builder_KindTwo ();    
        void buildPartHead(const string str = "blue.Head");
        void buildPartBody(const string str = "black.Body");
        void buildPartFoot(const string str = "red.Foot");
        //Product* getProduct();
    protected:
    private:

}; /* -----  end of class Builder_KindOne  ----- */

class Builder_KindThree: public Builder
{
    public:
        Builder_KindThree ();    
        void buildPartHead(const string str = "black.Head");
        void buildPartBody(const string str = "red.Body");
        void buildPartFoot(const string str = "blue.Foot");
        //Product* getProduct();
    protected:
    private:

}; /* -----  end of class Builder_KindOne  ----- */

#endif   /* ----- #ifndef _builder_H_  ----- */
