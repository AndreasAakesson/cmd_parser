/**

  This file is a part of cmd_parser.

  Copyright 2015 Andreas Åkesson

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**/

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <string>
#include <ostream>
#include <functional>

namespace cmd_parser {

using CommandArg  = std::vector<std::string>;
using CommandFunc = std::function<void(CommandArg&)>;

class Command {
public:
  explicit Command(const std::string& name, CommandFunc func,
                   const std::string& help, const int args = 0) :
    name_ {name},
    func_ {func},
    help_ {help},
    args_ {args}
  {}

  void exec(CommandArg& args)
  { func_(args); }
  
  const std::string& name() const noexcept
  { return name_; }

  const std::string& help() const noexcept
  { return help_; }

  int args() const noexcept
  { return args_; }

private:
  /* Command name */
  const std::string name_;

  /* Command function to execute */
  CommandFunc func_;

  /* Help/usage text */
  const std::string help_;

  /* Required number of arguments */
  const int args_;
}; //< class Command

inline std::ostream& operator<<(std::ostream& streamer, const Command& command) {
    return streamer << command.name() << "\t\t" << command.help();
}

inline bool operator==(const Command& lhs, const Command& rhs) noexcept {
  return lhs.name() == rhs.name();
}

inline bool operator!=(const Command& lhs, const Command& rhs) noexcept {
  return lhs.name() not_eq rhs.name();
}

} //< namespace cmd_parser

#endif //< COMMAND_HPP
