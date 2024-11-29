#include "shutdown.h"

void shutdown(const std::string& error_message)
{
  throw std::runtime_error{error_message};
}
void shutdown(const std::string& error_message, const char* const& get_error)
{
  std::string msg = error_message + get_error;
  throw std::runtime_error{msg};
}