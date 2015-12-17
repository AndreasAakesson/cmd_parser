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


#include "command_parser.hpp"
#include <iostream>

using namespace cmd_parser;
using namespace std;

Command CommandParser::find(const string name) {
	for(auto c : commands) {
		if(c.name() == name)
			return c;
	}
	return defaultCommand_;
}

void CommandParser::exec(vector<string> args) {
		
	// TODO: Make prettier, store args & make functions, use references, compare with iterators/pointers (not strings)
	if(args.empty()) {
		usage();
		return;
	}

	auto cmd = find(args[0]);
	// if command is found, remove first arg
	if(cmd.name() != defaultCommand_.name())
		args.erase(args.begin());

	// if not enough args
	if(cmd.args() > args.size()) {
		usage(cmd);
	} else {
		cmd.exec(args);	
	}
}

void CommandParser::exec(int argc, char** argv) {
	vector<string> args;
	// Skip first argument, since it will be the name of the program
	for(int i = 1; i < argc; i++)
		args.push_back(argv[i]);

	exec(args);
}

void CommandParser::usage() {
	cout << endl << "USAGE:" << endl << endl;
	for(auto c : commands) {
		cout << "\t" << c << endl << endl;
	}
	cout << "Default: " << endl << "\t" << defaultCommand_ << endl << endl;
}

void CommandParser::usage(const std::string command) {
	cout << find(command) << endl;
}

void CommandParser::usage(const Command c) {
	cout << c << endl;
}