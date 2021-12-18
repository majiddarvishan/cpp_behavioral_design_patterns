#include <iostream>

class GreetingCardTemplate
{
    protected:
        virtual std::string intro(const std::string& to)
        {
            return "Dear " + to + ",\n";
        }

        virtual std::string occasion()
        {
            return "Just writng to say hi! Hope all is well with you.";
        }

        virtual std::string closing(const std::string& from)
        {
            return "Sincerely,\n" + from + "\n";
        }

    public:
        std::string generate(const std::string& to, const std::string& from)
        {
            return intro(to) + occasion() + closing(from);
        }
};

class BirtdayCardTemplate : public GreetingCardTemplate
{
    protected:
        std::string intro(const std::string& to) override
        {
            return to + "!!!\n";
        }

        std::string occasion() override
        {
            return "Happy new year";
        }
};

class NewYearsCardTemplate : public GreetingCardTemplate
{
    protected:
        std::string occasion() override
        {
            return "Happy birthday";
        }
};

int main()
{
    GreetingCardTemplate gct;
    BirtdayCardTemplate bct;
    NewYearsCardTemplate nct;

    gct.generate("Bob", "Jane");
    bct.generate("Bob", "Jane");
    nct.generate("Bob", "Jane");

    return 0;
}