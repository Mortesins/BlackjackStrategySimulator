#include <exception>
#include <string>

class TableError
    : public std::exception
{
  protected:
    std::string message;
  public:
    TableError(std::string msg) { message = msg; }

    const char * what () const throw () {
        return message.c_str();
    }
};