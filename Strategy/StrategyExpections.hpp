#include <exception>
#include <string>

class StrategyError
    : public std::exception
{
  protected:
    std::string message;
  public:
    StrategyError(std::string msg) { message = msg; }

    const char * what () const throw () {
        return message.c_str();
    }
};