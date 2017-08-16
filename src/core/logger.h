#ifndef SRC_CORE_LOGGER_H_
#define SRC_CORE_LOGGER_H_

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/file.h>
#include <stdarg.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <mutex>
#include <map>

namespace aql_profile {

class Logger {
 public:
  typedef std::recursive_mutex mutex_t;

  template <typename T> Logger& operator<<(const T& m) {
    std::ostringstream oss;
    oss << m;
    if (!streaming_)
      Log(oss.str());
    else
      Put(oss.str());
    streaming_ = true;
    return *this;
  }

  typedef void (*manip_t)();
  Logger& operator<<(manip_t f) {
    f();
    return *this;
  }

  static void begm() { Instance().messaging_ = true; }
  static void endl() { Instance().ResetStreaming(); }

  static const std::string& LastMessage() {
    Logger& logger = Instance();
    std::lock_guard<mutex_t> lck(mutex_);
    return logger.message_[GetTid()];
  }

  static Logger& Instance() {
    std::lock_guard<mutex_t> lck(mutex_);
    if (instance_ == NULL) instance_ = new Logger();
    return *instance_;
  }

  static void Destroy() {
    std::lock_guard<mutex_t> lck(mutex_);
    if (instance_ != NULL) delete instance_;
    instance_ = NULL;
  }

 private:
  static uint32_t GetPid() { return syscall(__NR_getpid); }
  static uint32_t GetTid() { return syscall(__NR_gettid); }

  Logger() : file_(NULL), dirty_(false), streaming_(false), messaging_(false) {
    const char* path = getenv("HSA_VEN_AMD_AQLPROFILE_LOG");
    if (path != NULL) {
      file_ = fopen("/tmp/aql_profile_log.txt", "a");
    }
    ResetStreaming();
  }

  ~Logger() {
    if (file_ != NULL) {
      if (dirty_) Put("\n");
      fclose(file_);
    }
  }

  void ResetStreaming() {
    std::lock_guard<mutex_t> lck(mutex_);
    if (messaging_) {
      message_[GetTid()] = "";
    }
    messaging_ = false;
    streaming_ = false;
  }

  void Put(const std::string& m) {
    std::lock_guard<mutex_t> lck(mutex_);
    if (messaging_) {
      message_[GetTid()] += m;
    }
    if (file_ != NULL) {
      dirty_ = true;
      flock(fileno(file_), LOCK_EX);
      fprintf(file_, "%s", m.c_str());
      fflush(file_);
      flock(fileno(file_), LOCK_UN);
    }
  }

  void Log(const std::string& m) {
    const time_t rawtime = time(NULL);
    tm tm_info;
    localtime_r(&rawtime, &tm_info);
    char tm_str[26];
    strftime(tm_str, 26, "%Y-%m-%d %H:%M:%S", &tm_info);
    std::ostringstream oss;
    oss << "\n<" << tm_str << std::dec << " pid" << GetPid() << " tid" << GetTid() << "> " << m;
    Put(oss.str());
  }

  FILE* file_;
  bool dirty_;
  bool streaming_;
  bool messaging_;

  static mutex_t mutex_;
  static Logger* instance_;
  std::map<uint32_t, std::string> message_;
};

}  // namespace aql_profile

#define ERR_LOGGING                                                                                \
  (aql_profile::Logger::Instance() << aql_profile::Logger::endl                                    \
                                   << "Error: " << __FUNCTION__                                    \
                                   << "(): " << aql_profile::Logger::begm)
#define INFO_LOGGING                                                                               \
  (aql_profile::Logger::Instance() << aql_profile::Logger::endl                                    \
                                   << "Info: " << __FUNCTION__                                     \
                                   << "(): " << aql_profile::Logger::begm)

#endif  // SRC_CORE_LOGGER_H_
