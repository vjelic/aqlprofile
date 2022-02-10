#ifndef SRC_CORE_AQL_PROFILE_EXCEPTION_H_
#define SRC_CORE_AQL_PROFILE_EXCEPTION_H_

#include <string.h>

#include <sstream>
#include <string>

namespace aql_profile {

class aql_profile_exc_msg : public std::exception {
 public:
  explicit aql_profile_exc_msg(const std::string& msg) : str_(msg) {}
  virtual const char* what() const throw() { return str_.c_str(); }

 protected:
  std::string str_;
};

template <typename T>
class aql_profile_exc_val : public std::exception {
 public:
  aql_profile_exc_val(const std::string& msg, const T& val) {
    std::ostringstream oss;
    oss << msg << "(" << val << ")";
    str_ = oss.str();
  }
  virtual const char* what() const throw() { return str_.c_str(); }

 protected:
  std::string str_;
};
}  // namespace aql_profile

#endif  // SRC_CORE_AQL_PROFILE_EXCEPTION_H_
