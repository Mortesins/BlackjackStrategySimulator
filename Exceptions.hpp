#include <exception>
#include <string>

class BaseException
    : public std::exception
{
  protected:
    std::string message;
  public:
    BaseException(std::string msg) { message = msg; }

    const char * what () const throw () {
        return message.c_str();
    }
};

class TableError
    : public BaseException
{
  public:
    TableError(std::string msg) : BaseException(msg) {}
};

class ActionConversionError
    : public BaseException
{
  public:
    ActionConversionError(std::string msg) : BaseException(msg) {}
};

class CardConversionError
    : public BaseException
{
  public:
    CardConversionError(std::string msg) : BaseException(msg) {}
};