#pragma once

#include <string>

namespace stem {

class Exception : public std::exception {
protected:
  /// @brief The error message string
  std::string _message;

public:
  /// @brief Return the error message
  /// @return The error string
  const char *what() const throw();
};

} // namespace stem