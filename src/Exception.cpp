#include <stem/Exception.hpp>

namespace stem {

const char *Exception::what() const throw() {
  return _message.c_str();
}

} // namespace stem
