#include "Logger.h"

const std::shared_ptr<spdlog::logger> Logger::logger = spdlog::stdout_color_st("atomaton_logger");
const std::shared_ptr<spdlog::logger> Logger::debug_logger = spdlog::stderr_color_st("atomaton_debug");