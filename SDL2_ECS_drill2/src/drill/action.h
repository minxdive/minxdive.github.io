#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
  std::string name;
  std::string type;
public:
  Action() { }
  Action(const std::string& na, const std::string& ty) : name(na), type(ty) { }
  const std::string& get_name() const { return name; }
  const std::string& get_type() const { return type; }
};

#endif