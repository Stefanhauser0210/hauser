#pragma once
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Logger
{
    extern const std::shared_ptr<spdlog::logger> logger;
    extern const std::shared_ptr<spdlog::logger> debug_logger;
}

