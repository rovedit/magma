// Small wrapper for the spdlogger
#pragma once
#include "defines.hh"

#define SPDLOG_ACTIVE_LEVEL MAGMA_LOG_LEVEL
#include <spdlog/spdlog.h>

namespace mg
{
  void init_logger();
}

