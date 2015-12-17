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

using Func = cmd_parser::CommandFunc;
using Args = cmd_parser::CommandArg;

using namespace cmd_parser;
using namespace std;

int main(int argc, char** argv) {

	/* Default argument */
	Func func = [](Args argz) { cout << "Default command executed with argument: " << argz[0] << endl; };
	Command default_cmd("default", func, "This is the default (fallback) command.", 1);

	/* Command with capture by reference */
	string secret_word = "chicken";
	func = [&secret_word](Args argz) { 
		string answer = (argz[0].compare(secret_word) == 0) ? "true" : "false";
		cout << "Your guess was: " << answer << endl;
	};
	Command guess("guess", func, "Guess the secret word! (HINT: It's 'chicken')", 1);

	/* Command with no required arguments */
	func = [](Args argz){ cout << "I don't care about your arguments. " << endl; };
	Command none("none", func, "A command with no required arguments.");

	/* Command with 3 required arguments */
	func = [](Args argz){ cout << "Arguments: " << argz[0] << "\t" << argz[1] << "\t" << argz[2] << endl; };
	Command many("many", func, "A command with 3 required arguments", 3);

	CommandParser parser(default_cmd);	
	parser.add(guess);
	parser.add(none);
	parser.add(many);
	parser.exec(argc, argv);

	return 0;
} 