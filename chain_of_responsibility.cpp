#include <iostream>
#include <regex>
#include <string>

class StringValidator
{
 public:
    virtual ~StringValidator() {};
    virtual StringValidator* setNext(StringValidator* nextValidator) = 0;
    virtual std::string validate(std::string) = 0;
};

class BaseValidator : public StringValidator
{
protected:
    StringValidator* next = nullptr;

public:
    BaseValidator(/* args */);
    virtual ~BaseValidator() { delete next;};

    virtual StringValidator* setNext(StringValidator* nextValidator) override
    {
        next = nextValidator;
        return next;
    }
    virtual std::string validate(std::string testString) override
    {
        if(this->next)
        {
            return this->next->validate(testString);
        }

        return "Success!";
    }
};

class NotEmptyValidator : public BaseValidator
{
public:
    NotEmptyValidator() {}

    virtual std::string validate(std::string testString) override
    {
        puts("Checking if empty...")
        if(testString.empty)
        {
            return "Please enter a value";
        }

        return BaseValidator::validate(testString);
    }
};

class LengthValidator : public BaseValidator
{
    int minLength;
public:
    LengthValidator(int minLength) : minLength(minLength) {}

    virtual std::string validate(std::string testString) override
    {
        puts("Checking string length...")
        if(testString.length() < minLength)
        {
            return "Please enter a value longer than " +
                std::to_string(minLength);
        }

        return BaseValidator::validate(testString);
    }
};

class RegexValidator : public BaseValidator
{
    std::string patternName;
    std::string regexString;
public:
    RegexValidator(std::string patternName, std::string regexString) : 
                    patternName(patternName), regexString(regexString) {}

    virtual std::string validate(std::string testString) override
    {
        puts("Checking regex match...")
        if(!std::regtex_match(testString,
            std::regex(regexString)))
        {
            return "The value entered dows not match the proper format for a " +
                patternName;
        }

        return BaseValidator::validate(testString);
    }
};

bool in_array(const std::string& value, const std::vector<std::string>& array)
{
    return std::find(array.begin(), array.end(),value) != array.end();
}

class HistoryValidator : public BaseValidator
{
    std::vector<std::string> historyItems;
public:
    HistoryValidator(std::vector<std::string> historyItems) : 
                    historyItems(historyItems) {}

    virtual std::string validate(std::string testString) override
    {
        puts("Checking if string has been used before...")

        if(in_array(testString, historyItems))
        {
            return "Please enter a value here that you haven't entered before";
        }

        return BaseValidator::validate(testString);
    }
};

int main()
{
    StringValidator* emailValidator = new BaseValidator();
    emailValidator->setNext(new NotEmptyValidator())
                  ->setNext(new RegexValidator("email address",
                                                "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\W+([-.]\\w+)*$"));

    std::cout << "Checking Email ---------------------\n";
    std::cout << "Input: \n" << emailValidator->validate("") << "\n\n";
    std::cout << "Input: shaun\n" << emailValidator->validate("shaun") << "\n\n";
    std::cout << "Input: shaun@test.com\n" << emailValidator->validate("shaun@test.com") << "\n\n";

    delete emailValidator;
    
    return 0;
}