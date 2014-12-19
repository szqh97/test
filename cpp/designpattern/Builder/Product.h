
#ifndef  _Product_H_
#define  _Product_H_
#include <iostream>
#include <string>
using std::string;
class Product 
{
public:
    virtual void setHeadColor(const string color) = 0;
    virtual void setBodyColor(const string color) = 0;
    virtual void setFootColor(const string color) = 0;
    void showProduct();
protected:
    string head, body, foot;
};
class ProdcutOne: public Product
{
public:
    void setHeadColor(const string color );
    void setBodyColor(const string color );
    void setFootColor(const string color );
};

class ProdcutTwo: public Product
{
public:
    void setHeadColor(const string color );
    void setBodyColor(const string color );
    void setFootColor(const string color );
};

class ProdcutThree: public Product
{
public:
    void setHeadColor(const string color );
    void setBodyColor(const string color );
    void setFootColor(const string color );
};
#endif   /* ----- #ifndef _Product_H_  ----- */
