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
#include <iostream>
#include <functional>

namespace cmd_parser {

using CommandArg = std::vector<std::string>;
using CommandFunc = std::function<void(CommandArg)>;

class Command {
	/* Command name */
	std::string name_;
	/* Command function to execute */
	CommandFunc func_;
	/* Help/usage text */
	std::string help_;
	/* Required number of arguments */
	int args_;

public:
	Command(std::string name, CommandFunc func, std::string help, int args = 0) 
		: name_(name), func_(func), help_(help), args_(args) {}

	inline void exec(CommandArg args) {
		func_(args);
	}
	
	inline std::string const name() {
		return name_;
	}

	inline std::string const help() {
		return help_;
	}

	inline int const args() {
		return args_;
	}

	friend std::ostream& operator<<(std::ostream& s, Command c) {
		s << c.name_ << "\t\t" << c.help_;
		return s;
	}
};

}

