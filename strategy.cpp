#include <iostream>

class GreetingStrategy 
{
    public:
        virtual ~GreetingStrategy() {}
        virtual void great(const std::string& name) = 0;
};

class FormalGreetingStrategy : public GreetingStrategy
{
    public:
        virtual void great(const std::string& name) 
        {
            std::cout<<"\nGood morning " << name << ", how do you do?\n";
        }
};

class NormalGreetingStrategy : public GreetingStrategy
{
    public:
        virtual void great(const std::string& name) 
        {
            std::cout<<"\nHi " << name << ", how are you?\n";
        }
};

class InformalGreetingStrategy : public GreetingStrategy
{
    public:
        virtual void great(const std::string& name) 
        {
            std::cout<<"\nHey " << name << ", what's up?\n";
        }
};

class Person
{
    GreetingStrategy* greetingStrategy;
    public:
        Person(GreetingStrategy* greetingStrategy) : greetingStrategy(greetingStrategy) {}
        ~Person() { delete greetingStrategy}

        void great(const std::string& name)
        {
            greetingStrategy->great(name);
        }
};

int main()
{
    Person businessPerson(new FormalGreetingStrategy());
    Person normalPerson(new NormalGreetingStrategy());

    std::cout<<"The business person says: ";
    businessPerson.great("business");

    std::cout<<"The normal person says: ";
    normalPerson.great("normal");

    return 0;
}