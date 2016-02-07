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

#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include "command.hpp"

namespace cmd_parser {

using Commands = std::vector<Command>;

class CommandParser {
public:
  explicit CommandParser(const Command& def_command) noexcept:
    default_command_ {def_command}
  {}

  /* Add command to command list */
  CommandParser& add(const Command& command)
  { commands_.push_back(command); return *this; }

  /* Same arguments as main */
  void exec(int, char**);

  void exec(CommandArg&);

  /* For printing */
  void usage();
  void usage(const std::string&);
  void usage(const Command&);
private:
   /* Fallback command - executed when command isnt found. */
  Command default_command_;

  Commands commands_;

  /* Find command by name */
  Command& find(const std::string&) noexcept;
}; //< class CommandParser
} //< namespace cmd_parser

#endif //< COMMAND_PARSER_HPP
