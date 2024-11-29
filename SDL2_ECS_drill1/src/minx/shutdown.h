#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <string>
#include <stdexcept>

void shutdown(const std::string& error_message);
void shutdown(const std::string& error_message, const char* const& get_error);

#endif