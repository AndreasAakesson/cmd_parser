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

#include <iostream>

#include "command_parser.hpp"

using Args = cmd_parser::CommandArg;
using Func = cmd_parser::CommandFunc;

using namespace std;
using namespace cmd_parser;

int main(int argc, char** argv) {

  /**
   *  Default argument
   *
   *  example $test
   *
   *  Will fail to find the command with the name "test" and instead use $test as an argument.
   */
  Func func = [](auto& args) { cout << "Default command executed with argument: " << args.front() << '\n'; };
  Command default_cmd {"default", func, "This is the default (fallback) command.", 1};

  /**
   *  Command with capture by reference
   *
   *  example guess $myGuess
   *
   *  Will try to match $myGuess with "secret_word" and will output the result of the guess.
   */
  string secret_word {"chicken"};
  func = [&secret_word](auto& args) {
    string answer = (args.front().compare(secret_word) == 0) ? "correct" : "incorrect";
    cout << "Your guess was " << answer << '\n';
  };
  Command guess {"guess", func, "Guess the secret word! (HINT: It's 'chicken')", 1};

  /**
   *  Command with no required arguments
   *
   *  example none
   *
   *  Will execute the command "none", even if there is no argument
   */
  func = [](auto& args) { cout << "I don't care about your arguments.\n"; };
  Command none {"none", func, "A command with no required arguments."};

  /**
   *  Command with 3 required arguments
   *
   *  example many $one $two $three
   *
   *  If not enough arguments (3), the command wont be executed, and it will instead output the help text of the command.
   */
  func = [](auto& args) { cout << "Arguments: " << args[0] << "\t" << args[1] << "\t" << args[2] << '\n'; };
  Command many {"many", func, "A command with 3 required arguments", 3};

  CommandParser parser {default_cmd};
  parser.add(guess)
        .add(none)
        .add(many)
        .exec(argc, argv);
}
