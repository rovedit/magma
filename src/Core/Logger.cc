#include "Logger.hh"
#include <spdlog/spdlog.h>

void mg::init_logger() {
# if(SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE)
  spdlog::set_level(spdlog::level::trace);
# elif(SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG)
  spdlog::set_level(spdlog::level::debug);
# endif
}