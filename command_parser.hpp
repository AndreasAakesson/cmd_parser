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


#include <vector>
#include <string>
#include "command.hpp"

namespace cmd_parser {

class CommandParser {
	/* Fallback command - executed when command isnt found. */
	Command defaultCommand_;
	std::vector<Command> commands;

public:
	CommandParser(Command defCommand) : defaultCommand_(defCommand) {}

	/* Add command to command list */
	inline void add(Command c) {
		commands.push_back(c);
	}

	/* Find command by name */
	Command find(const std::string name);

	void exec(CommandArg args);
	/* Same arguments as main */
	void exec(int argc, char** argv);

	/* For printing */
	void usage();
	void usage(const std::string command);
	void usage(const Command c);
};

}
