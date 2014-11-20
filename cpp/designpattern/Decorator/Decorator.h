#ifndef _DECORATOR_H_
#define _DECORATOR_H_

//Component抽象类，定义该类对象的接口
class Component
{
public:
    virtual ~Component();
    virtual void Operation()=0;
protected:
    Component();
};

//ConcreteDecorator：具体的Component对象，可以给该对象动态 添加职责
class ConcreteComponent:public Component
{
public:
    ConcreteComponent();
    ~ConcreteComponent();
    virtual void Operation();
};

//Decorator：装饰抽象类，继承自Component
class Decorator:public Component
{
public:
    Decorator(Component* com);
    virtual ~Decorator();
    virtual void Operation();
protected:
    Component* _com;
};

//ConcreteDecorator就是具体的装饰对象之一，起到给Component添加职责的功能
class ConcreteDecoratorA:public Decorator
{
public:
    ConcreteDecoratorA(Component* com);
    ~ConcreteDecoratorA();
    virtual void Operation();
    void AddBehavorA();
};

//ConcreteDecorator就是具体的装饰对象之二，起到给Component添加职责的功能
class ConcreteDecoratorB:public Decorator
{
public:
    ConcreteDecoratorB(Component* com);
    ~ConcreteDecoratorB();
    virtual void Operation();
    void AddBehavorB();
};

//ConcreteDecorator就是具体的装饰对象之三，起到给Component添加职责的功能
class ConcreteDecoratorC:public Decorator
{
public:
    ConcreteDecoratorC(Component* com);
    ~ConcreteDecoratorC();
    virtual void Operation();
    void AddBehavorC();
};

//ConcreteDecorator就是具体的装饰对象之四，起到给Component添加职责的功能
class ConcreteDecoratorD:public Decorator
{
public:
    ConcreteDecoratorD(Component* com);
    ~ConcreteDecoratorD();
    virtual void Operation();
    void AddBehavorD();
};

//只添加一种装饰，则不用抽象出装饰基类
class DecoratorOnlyOne:public Component
{
public:
    DecoratorOnlyOne(Component* com);
    ~DecoratorOnlyOne();
    virtual void Operation();
    void AddBehavor();
private:
    Component* _com;
};

//如果只有一个ConcreteComponent类而没有抽象的Component类，那么Decorator类可以是ConcreteComponent的一个子类。
//略
#endif
