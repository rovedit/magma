#include "Assertions.hh"
#include "Logger.hh"

void mg_detail::report_assertion(const char* expression, const char* message, const char* file, int line) {
  SPDLOG_CRITICAL("Assertion Failure: {0}, message: '{1}', in file {2}, in line {3}\n", expression, message, file, line);
}
