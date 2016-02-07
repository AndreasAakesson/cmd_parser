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

using namespace std;

namespace cmd_parser {
///////////////////////////////////////////////////////////////////////////////
void CommandParser::exec(int argc, char** argv) {
	CommandArg args;

	// Skip first argument, since it will be the name of the program
	for(int i {1}; i < argc; ++i) {
		args.push_back(argv[i]);
	}

	exec(args);
}

///////////////////////////////////////////////////////////////////////////////
Command& CommandParser::find(const string& name) noexcept {
	for(auto& command : commands_) {
		if(command.name() == name)
			return command;
	}

	return default_command_;
}

///////////////////////////////////////////////////////////////////////////////
void CommandParser::exec(CommandArg& args) {
		
	// TODO: Make prettier, store args & make functions, use references, compare with iterators/pointers (not strings)
	if(args.empty()) {
		usage();
		return;
	}

	decltype(auto) cmd = find(args.front());

	// If command is found, remove first arg
	if(cmd not_eq default_command_) {
		args.erase(args.begin());
	}

	// If not enough args
	if(cmd.args() > args.size()) {
		usage(cmd);
	} else {
		cmd.exec(args);
	}
}

///////////////////////////////////////////////////////////////////////////////
void CommandParser::usage() {
	cout << "\nUSAGE:\n\n";

	for(const auto& command : commands_) {
		cout << "\t" << command << "\n\n";
	}

	cout << "Default: \n\t" << default_command_ << "\n\n";
}

///////////////////////////////////////////////////////////////////////////////
void CommandParser::usage(const std::string& command) {
	cout << find(command) << '\n';
}

///////////////////////////////////////////////////////////////////////////////
void CommandParser::usage(Command& command) {
	cout << command << '\n';
}

} //< namespace cmd_parser
